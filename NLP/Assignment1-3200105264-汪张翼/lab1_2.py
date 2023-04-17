"""
导入必要的库
"""
import math
import numpy as np
import pandas as pd
import os
import math
import random
import codecs
from pathlib import Path
import mindspore
import mindspore.dataset as ds
import mindspore.nn as nn
from mindspore import Tensor
from mindspore import context
from mindspore.train.model import Model
from mindspore.nn.metrics import Accuracy
from mindspore.train.serialization import load_checkpoint, load_param_into_net
from mindspore.train.callback import ModelCheckpoint, CheckpointConfig, LossMonitor, TimeMonitor
from mindspore.ops import operations as ops
from easydict import EasyDict as edict


cfg = edict({  # 进行超参数的设置
    'name': 'movie review',
    'pre_trained': False,  # 不使用原先模型训练
    'num_classes': 2,
    'batch_size': 64,
    'epoch_size': 4,
    'weight_decay': 3e-5,
    'data_path': './data/',
    'device_target': 'Ascend',
    'device_id': 0,
    'keep_checkpoint_max': 1,
    'checkpoint_path': './ckpt/train_textcnn-4_149.ckpt',
    'word_len': 51,
    'vec_length': 40
})
context.set_context(mode=context.GRAPH_MODE, device_target=cfg.device_target, device_id=cfg.device_id)


class Generator():
    def __init__(self, input_list):
        self.input_list=input_list
    def __getitem__(self,item):
        return (np.array(self.input_list[item][0],dtype=np.int32),
                np.array(self.input_list[item][1],dtype=np.int32))
    def __len__(self):
        return len(self.input_list)


class MovieReview:
    '''
    影评数据集
    '''
    def __init__(self, root_dir, maxlen, split):
        '''
        input:
            root_dir: 影评数据目录
            maxlen: 设置句子最大长度
            split: 设置数据集中训练/评估的比例
        '''
        self.path = root_dir
        self.feelMap = {
            'neg':0,
            'pos':1
        }
        self.files = []

        self.doConvert = False
        
        mypath = Path(self.path)
        if not mypath.exists() or not mypath.is_dir():
            print("please check the root_dir!")
            raise ValueError

        # 在数据目录中找到文件
        for root,_,filename in os.walk(self.path):
            for each in filename:
                self.files.append(os.path.join(root,each))
            break

        # 确认是否为两个文件.neg与.pos
        if len(self.files) != 2:
            print("There are {} files in the root_dir".format(len(self.files)))
            raise ValueError

        # 读取数据
        self.word_num = 0
        self.maxlen = 0
        self.minlen = float("inf")
        self.maxlen = float("-inf")
        self.Pos = []
        self.Neg = []
        for filename in self.files:
            f = codecs.open(filename, 'r')
            ff = f.read()
            file_object = codecs.open(filename, 'w', 'utf-8')
            file_object.write(ff)
            self.read_data(filename)
        self.PosNeg = self.Pos + self.Neg

        self.text2vec(maxlen=maxlen)
        self.split_dataset(split=split)

    def read_data(self, filePath):

        with open(filePath,'r') as f:
            
            for sentence in f.readlines():
                sentence = sentence.replace('\n','')\
                                    .replace('"','')\
                                    .replace('\'','')\
                                    .replace('.','')\
                                    .replace(',','')\
                                    .replace('[','')\
                                    .replace(']','')\
                                    .replace('(','')\
                                    .replace(')','')\
                                    .replace(':','')\
                                    .replace('--','')\
                                    .replace('-',' ')\
                                    .replace('\\','')\
                                    .replace('0','')\
                                    .replace('1','')\
                                    .replace('2','')\
                                    .replace('3','')\
                                    .replace('4','')\
                                    .replace('5','')\
                                    .replace('6','')\
                                    .replace('7','')\
                                    .replace('8','')\
                                    .replace('9','')\
                                    .replace('`','')\
                                    .replace('=','')\
                                    .replace('$','')\
                                    .replace('/','')\
                                    .replace('*','')\
                                    .replace(';','')\
                                    .replace('<b>','')\
                                    .replace('%','')
                sentence = sentence.split(' ')
                sentence = list(filter(lambda x: x, sentence))
                if sentence:
                    self.word_num += len(sentence)
                    self.maxlen = self.maxlen if self.maxlen >= len(sentence) else len(sentence)
                    self.minlen = self.minlen if self.minlen <= len(sentence) else len(sentence)
                    if 'pos' in filePath:
                        self.Pos.append([sentence,self.feelMap['pos']])
                    else:
                        self.Neg.append([sentence,self.feelMap['neg']])

    def text2vec(self, maxlen):
        '''
        将句子转化为向量
        '''
        self.Vocab = dict()

        for SentenceLabel in self.Pos+self.Neg:
            vector = [0]*maxlen
            for index, word in enumerate(SentenceLabel[0]):
                if index >= maxlen:
                    break
                if word not in self.Vocab.keys():
                    self.Vocab[word] = len(self.Vocab)
                    vector[index] = len(self.Vocab) - 1
                else:
                    vector[index] = self.Vocab[word]
            SentenceLabel[0] = vector
        self.doConvert = True

    def split_dataset(self, split):
        '''
        分割为训练集与测试集
        '''
        trunk_pos_size = math.ceil((1-split)*len(self.Pos))
        trunk_neg_size = math.ceil((1-split)*len(self.Neg))
        trunk_num = int(1/(1-split))
        pos_temp=list()
        neg_temp=list()
        for index in range(trunk_num):
            pos_temp.append(self.Pos[index*trunk_pos_size:(index+1)*trunk_pos_size])
            neg_temp.append(self.Neg[index*trunk_neg_size:(index+1)*trunk_neg_size])
        self.test = pos_temp.pop(2)+neg_temp.pop(2)
        self.train = [i for item in pos_temp+neg_temp for i in item]

        random.shuffle(self.train)

    def get_dict_len(self):
        '''
        获得数据集中文字组成的词典长度
        '''
        if self.doConvert:
            return len(self.Vocab)
        else:
            print("Haven't finished Text2Vec")
            return -1

    def create_train_dataset(self, epoch_size, batch_size):
        dataset = ds.GeneratorDataset(
                                        source=Generator(input_list=self.train), 
                                        column_names=["data","label"], 
                                        shuffle=False
                                        )
        dataset=dataset.batch(batch_size=batch_size,drop_remainder=True)
        dataset=dataset.repeat(epoch_size)
        return dataset

    def create_test_dataset(self, batch_size):
        dataset = ds.GeneratorDataset(
                                        source=Generator(input_list=self.test), 
                                        column_names=["data","label"], 
                                        shuffle=False
                                        )
        dataset=dataset.batch(batch_size=batch_size,drop_remainder=True)
        return dataset

instance = MovieReview(root_dir=cfg.data_path, maxlen=cfg.word_len, split=0.9)
dataset = instance.create_train_dataset(batch_size=cfg.batch_size,epoch_size=cfg.epoch_size)
batch_num = dataset.get_dataset_size()
vocab_size=instance.get_dict_len()
print("vocab_size:{0}".format(vocab_size))
item =dataset.create_dict_iterator()

"""
设置学习率
warm-up一般大小适中
shrink一般很小
normal_run一般较大
"""
learning_rate = []
warm_up = [1e-3 / math.floor(cfg.epoch_size / 5) * (i + 1) for _ in range(batch_num) 
           for i in range(math.floor(cfg.epoch_size / 5))]
shrink = [1e-3 / (16 * (i + 1)) for _ in range(batch_num) 
          for i in range(math.floor(cfg.epoch_size * 3 / 5))]
normal_run = [1e-3 for _ in range(batch_num) for i in 
              range(cfg.epoch_size - math.floor(cfg.epoch_size / 5) 
                    - math.floor(cfg.epoch_size * 2 / 5))]
learning_rate = learning_rate + warm_up + normal_run + shrink


def _weight_variable(shape, factor=0.01):
    init_value = np.random.randn(*shape).astype(np.float32) * factor
    return Tensor(init_value)


def make_conv_layer(kernel_size):
    weight_shape = (96, 1, *kernel_size)
    weight = _weight_variable(weight_shape)
    return nn.Conv2d(in_channels=1, out_channels=96, kernel_size=kernel_size, padding=1,
                     pad_mode="pad", weight_init=weight, has_bias=True)


class TextCNN(nn.Cell):
    def __init__(self, vocab_len, word_len, num_classes, vec_length):
        super(TextCNN, self).__init__()
        self.vec_length = vec_length
        self.word_len = word_len
        self.num_classes = num_classes

        self.unsqueeze = ops.ExpandDims()
        self.embedding = nn.Embedding(vocab_len, self.vec_length, embedding_table='normal')

        self.slice = ops.Slice()
        self.layer1 = self.make_layer(kernel_height=3)
        self.layer2 = self.make_layer(kernel_height=4)
        self.layer3 = self.make_layer(kernel_height=5)

        self.concat = ops.Concat(1)

        self.fc = nn.Dense(96*3, self.num_classes)
        self.drop = nn.Dropout(keep_prob=0.5)
        self.print = ops.Print()
        self.reducemean = ops.ReduceMax(keep_dims=False)
        
    def make_layer(self, kernel_height):
        return nn.SequentialCell(
            [
                make_conv_layer((kernel_height,self.vec_length)),
                nn.ReLU(),
                nn.MaxPool2d(kernel_size=(self.word_len-kernel_height+1,1)),
            ]
        )

    def construct(self,x):
        x = self.unsqueeze(x, 1)
        x = self.embedding(x)
        x1 = self.layer1(x)
        x2 = self.layer2(x)
        x3 = self.layer3(x)

        x1 = self.reducemean(x1, (2, 3))
        x2 = self.reducemean(x2, (2, 3))
        x3 = self.reducemean(x3, (2, 3))

        x = self.concat((x1, x2, x3))
        x = self.drop(x)
        x = self.fc(x)
        return x


"""
设置模型的优化器与损失函数等内容
"""
net = TextCNN(vocab_len=instance.get_dict_len(), word_len=cfg.word_len, 
              num_classes=cfg.num_classes, vec_length=cfg.vec_length)
opt = nn.Adam(filter(lambda x: x.requires_grad, net.get_parameters()), 
              learning_rate=learning_rate, weight_decay=cfg.weight_decay)
loss = nn.SoftmaxCrossEntropyWithLogits(sparse=True)
model = Model(net, loss_fn=loss, optimizer=opt, metrics={'acc': Accuracy()})
config_ck = CheckpointConfig(save_checkpoint_steps=int(cfg.epoch_size*batch_num/2), keep_checkpoint_max=cfg.keep_checkpoint_max)
time_cb = TimeMonitor(data_size=batch_num)
ckpt_save_dir = "./ckpt"
ckpoint_cb = ModelCheckpoint(prefix="train_textcnn", directory=ckpt_save_dir, config=config_ck)
loss_cb = LossMonitor()

"""
进行模型训练
"""
model.train(cfg.epoch_size, dataset, callbacks=[time_cb, ckpoint_cb, loss_cb])

"""
进行测试评估
"""
checkpoint_path = './ckpt/train_textcnn-4_596.ckpt'
dataset = instance.create_test_dataset(batch_size=cfg.batch_size)
opt = nn.Adam(filter(lambda x: x.requires_grad, net.get_parameters()), 
              learning_rate=0.001, weight_decay=cfg.weight_decay)
loss = nn.SoftmaxCrossEntropyWithLogits(sparse=True)
net = TextCNN(vocab_len=instance.get_dict_len(),word_len=cfg.word_len,
                  num_classes=cfg.num_classes,vec_length=cfg.vec_length)

if checkpoint_path is not None:
    param_dict = load_checkpoint(checkpoint_path)
    print("load checkpoint from [{}].".format(checkpoint_path))
else:
    param_dict = load_checkpoint(cfg.checkpoint_path)
    print("load checkpoint from [{}].".format(cfg.checkpoint_path))

load_param_into_net(net, param_dict)
net.set_train(False)
model = Model(net, loss_fn=loss, metrics={'acc': Accuracy()})

acc = model.eval(dataset)
print("accuracy: ", acc)
def preprocess(sentence):
    sentence = sentence.lower().strip()
    sentence = sentence.replace('\n','')\
                                    .replace('"','')\
                                    .replace('\'','')\
                                    .replace('.','')\
                                    .replace(',','')\
                                    .replace('[','')\
                                    .replace(']','')\
                                    .replace('(','')\
                                    .replace(')','')\
                                    .replace(':','')\
                                    .replace('--','')\
                                    .replace('-',' ')\
                                    .replace('\\','')\
                                    .replace('0','')\
                                    .replace('1','')\
                                    .replace('2','')\
                                    .replace('3','')\
                                    .replace('4','')\
                                    .replace('5','')\
                                    .replace('6','')\
                                    .replace('7','')\
                                    .replace('8','')\
                                    .replace('9','')\
                                    .replace('`','')\
                                    .replace('=','')\
                                    .replace('$','')\
                                    .replace('/','')\
                                    .replace('*','')\
                                    .replace(';','')\
                                    .replace('<b>','')\
                                    .replace('%','')\
                                    .replace("  "," ")
    sentence = sentence.split(' ')
    maxlen = cfg.word_len
    vector = [0]*maxlen
    for index, word in enumerate(sentence):
        if index >= maxlen:
            break
        if word not in instance.Vocab.keys():
            print(word,"单词未出现在字典中")
        else:
            vector[index] = instance.Vocab[word]
    sentence = vector

    return sentence

"""
测试函数
"""
def inference(review_en):
    review_en = preprocess(review_en)
    input_en = Tensor(np.array([review_en]).astype(np.int32))  # 数据预处理
    output = net(input_en)  # 放入模型进行训练
    if np.argmax(np.array(output[0])) == 1:
        print("Positive comments")
    else:
        print("Negative comments")

review_en = "the movie is so boring"  # 测试文本
inference(review_en)  # 得出结果为 Negative comments
