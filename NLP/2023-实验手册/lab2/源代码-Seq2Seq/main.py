# %% [markdown]
# ## 1.导入模块

# %%
import os
import numpy as np
import re
import sys
import random
import unicodedata
import math

from mindspore import Tensor, nn, Model, context
from mindspore.train.serialization import load_param_into_net, load_checkpoint
from mindspore.train.callback import LossMonitor, CheckpointConfig, ModelCheckpoint, TimeMonitor
from mindspore import dataset as ds
from mindspore.mindrecord import FileWriter
from mindspore import Parameter
from mindspore.nn.loss.loss import _Loss
from mindspore.ops import functional as F
from mindspore.ops import operations as P
from mindspore.common import dtype as mstype

# %%
context.set_context(mode=context.GRAPH_MODE, save_graphs=False, device_target='Ascend')

# %% [markdown]
# ## 2.数据预处理

# %% [markdown]
# ### 2.1数据预处理细节

# %%
#查看训练数据内容前10行内容
with open("./data/cmn_zhsim.txt", 'r', encoding='utf-8') as f:
        for i in range(10):
            print(f.readline())

# %%
EOS = "<eos>"
SOS = "<sos>"
MAX_SEQ_LEN=10

# %%
#我们需要将字符转化为ASCII编码
#并全部转化为小写字母，并修剪大部分标点符号
#除了(a-z, A-Z, ".", "?", "!", ",")这些字符外，全替换成空格
def unicodeToAscii(s):
    return ''.join(
        c for c in unicodedata.normalize('NFD', s)
        if unicodedata.category(c) != 'Mn'
    )

def normalizeString(s):
    s = s.lower().strip()
    s = unicodeToAscii(s)
    s = re.sub(r"([.!?])", r" \1", s)
    s = re.sub(r"[^a-zA-Z.!?]+", r" ", s)
    return s

# %%
def prepare_data(data_path, vocab_save_path, max_seq_len):
    with open(data_path, 'r', encoding='utf-8') as f:
        data = f.read()

    # 读取文本文件，按行分割，再将每行分割成语句对
    data = data.split('\n')

     # 截取前2000行数据进行训练
    data = data[:2000]

    # 分割每行中的中英文
    en_data = [normalizeString(line.split('\t')[0]) for line in data]

    ch_data = [line.split('\t')[1] for line in data]

    # 利用集合，获得中英文词汇表
    en_vocab = set(' '.join(en_data).split(' '))
    id2en = [EOS] + [SOS] + list(en_vocab)
    en2id = {c:i for i,c in enumerate(id2en)}
    en_vocab_size = len(id2en)
    # np.savetxt(os.path.join(vocab_save_path, 'en_vocab.txt'), np.array(id2en), fmt='%s')

    ch_vocab = set(''.join(ch_data))
    id2ch = [EOS] + [SOS] + list(ch_vocab)
    ch2id = {c:i for i,c in enumerate(id2ch)}
    ch_vocab_size = len(id2ch)
    # np.savetxt(os.path.join(vocab_save_path, 'ch_vocab.txt'), np.array(id2ch), fmt='%s')

    # 将句子用词汇表id表示
    en_num_data = np.array([[1] + [int(en2id[en]) for en in line.split(' ')] + [0] for line in en_data])
    ch_num_data = np.array([[1] + [int(ch2id[ch]) for ch in line] + [0] for line in ch_data])

    #将短句子扩充到统一的长度
    for i in range(len(en_num_data)):
        num = max_seq_len + 1 - len(en_num_data[i])
        if(num >= 0):
            en_num_data[i] += [0]*num
        else:
            en_num_data[i] = en_num_data[i][:max_seq_len] + [0]

    for i in range(len(ch_num_data)):
        num = max_seq_len + 1 - len(ch_num_data[i])
        if(num >= 0):
            ch_num_data[i] += [0]*num
        else:
            ch_num_data[i] = ch_num_data[i][:max_seq_len] + [0]
    
    
    np.savetxt(os.path.join(vocab_save_path, 'en_vocab.txt'), np.array(id2en), fmt='%s')
    
    np.savetxt(os.path.join(vocab_save_path, 'ch_vocab.txt'), np.array(id2ch), fmt='%s')

    return en_num_data, ch_num_data, en_vocab_size, ch_vocab_size

# %%
#将处理后的数据保存为mindrecord文件，方便后续训练
def convert_to_mindrecord(data_path, mindrecord_save_path, max_seq_len):
    en_num_data, ch_num_data, en_vocab_size, ch_vocab_size = prepare_data(data_path, mindrecord_save_path, max_seq_len)

    # 输出前十行英文句子对应的数据
    for i in range(10):
        print(en_num_data[i])
    
    data_list_train = []
    for en, ch in zip(en_num_data, ch_num_data):
        en = np.array(en).astype(np.int32)
        ch = np.array(ch).astype(np.int32)
        data_json = {"encoder_data": en.reshape(-1),
                     "decoder_data": ch.reshape(-1)}
        data_list_train.append(data_json)
    
    data_list_eval = random.sample(data_list_train, 20)

    data_dir = os.path.join(mindrecord_save_path, "gru_train.mindrecord")
    writer = FileWriter(data_dir)
    schema_json = {"encoder_data": {"type": "int32", "shape": [-1]},
                   "decoder_data": {"type": "int32", "shape": [-1]}}
    writer.add_schema(schema_json, "gru_schema")
    writer.write_raw_data(data_list_train)
    writer.commit()

    data_dir = os.path.join(mindrecord_save_path, "gru_eval.mindrecord")
    writer = FileWriter(data_dir)
    writer.add_schema(schema_json, "gru_schema")
    writer.write_raw_data(data_list_eval)
    writer.commit()

    print("en_vocab_size: ", en_vocab_size)
    print("ch_vocab_size: ", ch_vocab_size)

    return en_vocab_size, ch_vocab_size

# %%
if not os.path.exists("./preprocess"):
    os.mkdir('./preprocess')
convert_to_mindrecord("./data/cmn_zhsim.txt", './preprocess', MAX_SEQ_LEN)

# %% [markdown]
# ## 3.训练过程

# %% [markdown]
# ### 3.1 超参数设置

# %%
from easydict import EasyDict as edict

# CONFIG
cfg = edict({
    'en_vocab_size': 1154,
    'ch_vocab_size': 1116,
    'max_seq_length': 10,
    'hidden_size': 1024,
    'batch_size': 16,
    'eval_batch_size': 1,
    'learning_rate': 0.001,
    'momentum': 0.9,
    'num_epochs': 15,
    'save_checkpoint_steps': 125,
    'keep_checkpoint_max': 10,
    'dataset_path':'./preprocess',
    'ckpt_save_path':'./ckpt',
    'checkpoint_path':'./ckpt/gru-15_125.ckpt'
})

# %% [markdown]
# ### 3.2 读取数据

# %%
def target_operation(encoder_data, decoder_data):
    encoder_data = encoder_data[1:]
    target_data = decoder_data[1:]
    decoder_data = decoder_data[:-1]
    return encoder_data, decoder_data, target_data

def eval_operation(encoder_data, decoder_data):
    encoder_data = encoder_data[1:]
    decoder_data = decoder_data[:-1]
    return encoder_data, decoder_data

def create_dataset(data_home, batch_size, repeat_num=1, is_training=True, device_num=1, rank=0):
    if is_training:
        data_dir = os.path.join(data_home, "gru_train.mindrecord")
    else:
        data_dir = os.path.join(data_home, "gru_eval.mindrecord")
    data_set = ds.MindDataset(data_dir, columns_list=["encoder_data","decoder_data"], 
                              num_parallel_workers=4,
                              num_shards=device_num, shard_id=rank)
    if is_training:
        operations = target_operation
        data_set = data_set.map(operations=operations, 
                                input_columns=["encoder_data","decoder_data"],
                    output_columns=["encoder_data","decoder_data","target_data"],
                    column_order=["encoder_data","decoder_data","target_data"])
    else:
        operations = eval_operation
        data_set = data_set.map(operations=operations, 
                                input_columns=["encoder_data","decoder_data"],
                   output_columns=["encoder_data","decoder_data"],
                   column_order=["encoder_data","decoder_data"])
    data_set = data_set.shuffle(buffer_size=data_set.get_dataset_size())
    data_set = data_set.batch(batch_size=batch_size, drop_remainder=True)
    data_set = data_set.repeat(count=repeat_num)
    return data_set

# %%
ds_train = create_dataset(cfg.dataset_path, cfg.batch_size)

# %% [markdown]
# ### 3.3 网络模型

# %%
def gru_default_state(batch_size, input_size, hidden_size, num_layers=1, bidirectional=False):
    '''Weight init for gru cell'''
    stdv = 1 / math.sqrt(hidden_size)
    weight_i = Parameter(Tensor(
        np.random.uniform(-stdv, stdv, (input_size, 3*hidden_size)).astype(np.float32)), 
                         name='weight_i')
    weight_h = Parameter(Tensor(
        np.random.uniform(-stdv, stdv, (hidden_size, 3*hidden_size)).astype(np.float32)), 
                         name='weight_h')
    bias_i = Parameter(Tensor(
        np.random.uniform(-stdv, stdv, (3*hidden_size)).astype(np.float32)), name='bias_i')
    bias_h = Parameter(Tensor(
        np.random.uniform(-stdv, stdv, (3*hidden_size)).astype(np.float32)), name='bias_h')
    return weight_i, weight_h, bias_i, bias_h

class GRU(nn.Cell):
    def __init__(self, config, is_training=True):
        super(GRU, self).__init__()
        if is_training:
            self.batch_size = config.batch_size
        else:
            self.batch_size = config.eval_batch_size
        self.hidden_size = config.hidden_size
        self.weight_i, self.weight_h, self.bias_i, self.bias_h = \
            gru_default_state(self.batch_size, self.hidden_size, self.hidden_size)
        self.rnn = P.DynamicGRUV2()
        self.cast = P.Cast()

    def construct(self, x, hidden):
        x = self.cast(x, mstype.float16)
        y1, h1, _, _, _, _ = self.rnn(x, self.weight_i, self.weight_h, self.bias_i, self.bias_h, None, hidden)
        return y1, h1


class Encoder(nn.Cell):
    def __init__(self, config, is_training=True):
        super(Encoder, self).__init__()
        self.vocab_size = config.en_vocab_size
        self.hidden_size = config.hidden_size
        if is_training:
            self.batch_size = config.batch_size
        else:
            self.batch_size = config.eval_batch_size

        self.trans = P.Transpose()
        self.perm = (1, 0, 2)
        self.embedding = nn.Embedding(self.vocab_size, self.hidden_size)
        self.gru = GRU(config, is_training=is_training).to_float(mstype.float16)
        self.h = Tensor(np.zeros((self.batch_size, self.hidden_size)).astype(np.float16))

    def construct(self, encoder_input):
        embeddings = self.embedding(encoder_input)
        embeddings = self.trans(embeddings, self.perm)
        output, hidden = self.gru(embeddings, self.h)
        return output, hidden

class Decoder(nn.Cell):
    def __init__(self, config, is_training=True, dropout=0.1):
        super(Decoder, self).__init__()

        self.vocab_size = config.ch_vocab_size
        self.hidden_size = config.hidden_size
        self.max_len = config.max_seq_length

        self.trans = P.Transpose()
        self.perm = (1, 0, 2)
        self.embedding = nn.Embedding(self.vocab_size, self.hidden_size)
        self.dropout = nn.Dropout(1-dropout)
        self.attn = nn.Dense(self.hidden_size, self.max_len)
        self.softmax = nn.Softmax(axis=2)
        self.bmm = P.BatchMatMul()
        self.concat = P.Concat(axis=2)
        self.attn_combine = nn.Dense(self.hidden_size * 2, self.hidden_size)

        self.gru = GRU(config, is_training=is_training).to_float(mstype.float16)
        self.out = nn.Dense(self.hidden_size, self.vocab_size)
        self.logsoftmax = nn.LogSoftmax(axis=2)
        self.cast = P.Cast()

    def construct(self, decoder_input, hidden, encoder_output):
        embeddings = self.embedding(decoder_input)
        embeddings = self.dropout(embeddings)
        # calculate attn
        attn_weights = self.softmax(self.attn(embeddings))
        encoder_output = self.trans(encoder_output, self.perm)
        attn_applied = self.bmm(attn_weights, self.cast(encoder_output,mstype.float32))
        output =  self.concat((embeddings, attn_applied))
        output = self.attn_combine(output)


        embeddings = self.trans(embeddings, self.perm)
        output, hidden = self.gru(embeddings, hidden)
        output = self.cast(output, mstype.float32)
        output = self.out(output)
        output = self.logsoftmax(output)

        return output, hidden, attn_weights

class Seq2Seq(nn.Cell):
    def __init__(self, config, is_train=True):
        super(Seq2Seq, self).__init__()
        self.max_len = config.max_seq_length
        self.is_train = is_train

        self.encoder = Encoder(config, is_train)
        self.decoder = Decoder(config, is_train)
        self.expanddims = P.ExpandDims()
        self.squeeze = P.Squeeze(axis=0)
        self.argmax = P.ArgMaxWithValue(axis=int(2), keep_dims=True)
        self.concat = P.Concat(axis=1)
        self.concat2 = P.Concat(axis=0)
        self.select = P.Select()

    def construct(self, src, dst):
        encoder_output, hidden = self.encoder(src)
        decoder_hidden = self.squeeze(encoder_output[self.max_len-2:self.max_len-1:1, ::, ::])
        if self.is_train:
            outputs, _ = self.decoder(dst, decoder_hidden, encoder_output)
        else:
            decoder_input = dst[::,0:1:1]
            decoder_outputs = ()
            for i in range(0, self.max_len):
                decoder_output, decoder_hidden, _ = self.decoder(decoder_input, 
                                                                 decoder_hidden, encoder_output)
                decoder_hidden = self.squeeze(decoder_hidden)
                decoder_output, _ = self.argmax(decoder_output)
                decoder_output = self.squeeze(decoder_output)
                decoder_outputs += (decoder_output,)
                decoder_input = decoder_output
            outputs = self.concat(decoder_outputs)
        return outputs

class NLLLoss(_Loss):
    '''
       NLLLoss function
    '''
    def __init__(self, reduction='mean'):
        super(NLLLoss, self).__init__(reduction)
        self.one_hot = P.OneHot()
        self.reduce_sum = P.ReduceSum()

    def construct(self, logits, label):
        label_one_hot = self.one_hot(label, F.shape(logits)[-1], F.scalar_to_array(1.0), 
                                     F.scalar_to_array(0.0))
        #print('NLLLoss label_one_hot:',label_one_hot, label_one_hot.shape)
        #print('NLLLoss logits:',logits, logits.shape)
        #print('xxx:', logits * label_one_hot)
        loss = self.reduce_sum(-1.0 * logits * label_one_hot, (1,))
        return self.get_loss(loss)
    
class WithLossCell(nn.Cell):
    def __init__(self, backbone, config):
        super(WithLossCell, self).__init__(auto_prefix=False)
        self._backbone = backbone
        self.batch_size = config.batch_size
        self.onehot = nn.OneHot(depth=config.ch_vocab_size)
        self._loss_fn = NLLLoss()
        self.max_len = config.max_seq_length
        self.squeeze = P.Squeeze()
        self.cast = P.Cast()
        self.argmax = P.ArgMaxWithValue(axis=1, keep_dims=True)
        self.print = P.Print()

    def construct(self, src, dst, label):
        out = self._backbone(src, dst)
        loss_total = 0
        for i in range(self.batch_size):
            loss = self._loss_fn(self.squeeze(out[::,i:i+1:1,::]), 
                                 self.squeeze(label[i:i+1:1, ::]))
            loss_total += loss
        loss = loss_total / self.batch_size
        return loss

# %%
network = Seq2Seq(cfg)
network = WithLossCell(network, cfg)
optimizer = nn.Adam(network.trainable_params(), learning_rate=cfg.learning_rate, beta1=0.9, beta2=0.98)
model = Model(network, optimizer=optimizer)

# %% [markdown]
# ### 3.4 模型训练

# %%
loss_cb = LossMonitor()
config_ck = CheckpointConfig(save_checkpoint_steps=cfg.save_checkpoint_steps, keep_checkpoint_max=cfg.keep_checkpoint_max)
ckpoint_cb = ModelCheckpoint(prefix="gru", directory=cfg.ckpt_save_path, config=config_ck)
time_cb = TimeMonitor(data_size=ds_train.get_dataset_size())
callbacks = [time_cb, ckpoint_cb, loss_cb]

model.train(cfg.num_epochs, ds_train, callbacks=callbacks, dataset_sink_mode=True)

# %% [markdown]
# ## 4.推理部分

# %%
class InferCell(nn.Cell):
    def __init__(self, network, config):
        super(InferCell, self).__init__(auto_prefix=False)
        self.expanddims = P.ExpandDims()
        self.network = network

    def construct(self, src, dst):
        out = self.network(src, dst)
        return out

# %%
network = Seq2Seq(cfg,is_train=False)
network = InferCell(network, cfg)
network.set_train(False)
parameter_dict = load_checkpoint(cfg.checkpoint_path)
load_param_into_net(network, parameter_dict)
model = Model(network)

# %%
#打开词汇表
with open(os.path.join(cfg.dataset_path,"en_vocab.txt"), 'r', encoding='utf-8') as f:
    data = f.read()
en_vocab = list(data.split('\n'))

with open(os.path.join(cfg.dataset_path,"ch_vocab.txt"), 'r', encoding='utf-8') as f:
    data = f.read()
ch_vocab = list(data.split('\n'))

def translate(str_en):
    max_seq_len = 10
    str_vocab = normalizeString(str_en).split(' ')
    print("English",str(str_vocab))
    str_id = [[]]
    for i in str_vocab:
        str_id[0] += [en_vocab.index(i)]
   
    num = max_seq_len - len(str_id[0])
    if(num >= 0):
        str_id[0] += [0]*num
    else:
        str_id[0] = str_id[:max_seq_len] + [0]
    str_id = Tensor(np.array(str_id).astype(np.int32))
   
    out_id = Tensor(np.array([[1,0]]).astype(np.int32))
    
    output = network(str_id, out_id)
    out= ''
    for x in output[0].asnumpy():
        if x == 0:
            break
        out += ch_vocab[x]
    print("中文",out)

# %%
translate('i love tom')


