# %% [markdown]
# ## MindSpore-GCN-论文分类
# ### 1. 下载源码和数据至本地容器
# 
# 因为notebook是挂载在obs上，运行的容器实例不能直接读取操作obs上的文件，需下载至容器本地环境中

# %%


# %% [markdown]
# ### 2. 导入依赖库

# %%
import os
# os.environ['DEVICE_ID']='7'

import time
import argparse
import numpy as np

from mindspore import nn
from mindspore import Tensor
from mindspore import context
from mindspore.ops import operations as P
from mindspore.nn.layer.activation import get_activation
from easydict import EasyDict as edict

from src.gcn import glorot, LossAccuracyWrapper, TrainNetWrapper
from src.dataset import get_adj_features_labels, get_mask
from graph_to_mindrecord.writer import run

# %%
context.set_context(mode=context.GRAPH_MODE,device_target="Ascend", save_graphs=False)

# %% [markdown]
# ### 3. 定义参数配置

# %%
dataname = 'cora'
datadir_save = './data_mr'
datadir = os.path.join(datadir_save, dataname)
cfg = edict({
    'SRC_PATH': './data',
    'MINDRECORD_PATH': datadir_save,
    'DATASET_NAME': dataname,  # citeseer,cora
    'mindrecord_partitions':1,
    'mindrecord_header_size_by_bit' : 18,
    'mindrecord_page_size_by_bit' : 20,

    'data_dir': datadir,
    'seed' : 123,
    'train_nodes_num':140,
    'eval_nodes_num':500,
    'test_nodes_num':1000
})

# %% [markdown]
# ### 4. 转换数据格式为mindrecord

# %%
# 转换数据格式
print("============== Graph To Mindrecord ==============")
run(cfg)

# %% [markdown]
# ### 5. 定义GCN网络参数

# %%
class ConfigGCN():
    learning_rate = 0.01
    epochs = 200
    hidden1 = 16
    dropout = 0.5
    weight_decay = 5e-4
    early_stopping = 10

# %% [markdown]
# ### 6. 定义GCN网络结构

# %%
class GraphConvolution(nn.Cell):
    """
    GCN graph convolution layer.

    Args:
        feature_in_dim (int): The input feature dimension.
        feature_out_dim (int): The output feature dimension.
        dropout_ratio (float): Dropout ratio for the dropout layer. Default: None.
        activation (str): Activation function applied to the output of the layer, eg. 'relu'. Default: None.

    Inputs:
        - **adj** (Tensor) - Tensor of shape :math:`(N, N)`.
        - **input_feature** (Tensor) - Tensor of shape :math:`(N, C)`.

    Outputs:
        Tensor, output tensor.
    """

    def __init__(self,
                 feature_in_dim,
                 feature_out_dim,
                 dropout_ratio=None,
                 activation=None):
        super(GraphConvolution, self).__init__()
        self.in_dim = feature_in_dim
        self.out_dim = feature_out_dim
        self.weight_init = glorot([self.out_dim, self.in_dim])
        self.fc = nn.Dense(self.in_dim,
                           self.out_dim,
                           weight_init=self.weight_init,
                           has_bias=False)
        self.dropout_ratio = dropout_ratio
        if self.dropout_ratio is not None:
            self.dropout = nn.Dropout(keep_prob=1-self.dropout_ratio)
        self.dropout_flag = self.dropout_ratio is not None
        self.activation = get_activation(activation)
        self.activation_flag = self.activation is not None
        self.matmul = P.MatMul()

    def construct(self, adj, input_feature):
        dropout = input_feature
        if self.dropout_flag:
            dropout = self.dropout(dropout)

        fc = self.fc(dropout)
        output_feature = self.matmul(adj, fc)

        if self.activation_flag:
            output_feature = self.activation(output_feature)
        return output_feature


class GCN(nn.Cell):
    """
    GCN architecture.

    Args:
        config (ConfigGCN): Configuration for GCN.
        adj (numpy.ndarray): Numbers of block in different layers.
        feature (numpy.ndarray): Input channel in each layer.
        output_dim (int): The number of output channels, equal to classes num.
    """

    def __init__(self, config, adj, feature, output_dim):
        super(GCN, self).__init__()
        self.adj = Tensor(adj)
        self.feature = Tensor(feature)
        input_dim = feature.shape[1]
        self.layer0 = GraphConvolution(input_dim, config.hidden1, activation="relu", dropout_ratio=config.dropout)
        self.layer1 = GraphConvolution(config.hidden1, output_dim, dropout_ratio=None)

    def construct(self):
        output0 = self.layer0(self.adj, self.feature)
        output1 = self.layer1(self.adj, output0)
        return output1

# %% [markdown]
# ### 7. 定义训练、评估函数

# %%
def train_eval(args_opt):
    """Train model."""
    np.random.seed(args_opt.seed)
    config = ConfigGCN()
    adj, feature, label = get_adj_features_labels(args_opt.data_dir)

    nodes_num = label.shape[0]
    train_mask = get_mask(nodes_num, 0, args_opt.train_nodes_num)
    eval_mask = get_mask(nodes_num, args_opt.train_nodes_num, args_opt.train_nodes_num + args_opt.eval_nodes_num)
    test_mask = get_mask(nodes_num, nodes_num - args_opt.test_nodes_num, nodes_num)

    class_num = label.shape[1]
    gcn_net = GCN(config, adj, feature, class_num)
    gcn_net.add_flags_recursive(fp16=True)

    eval_net = LossAccuracyWrapper(gcn_net, label, eval_mask, config.weight_decay)
    test_net = LossAccuracyWrapper(gcn_net, label, test_mask, config.weight_decay)
    train_net = TrainNetWrapper(gcn_net, label, train_mask, config)

    loss_list = []
    for epoch in range(config.epochs):
        t = time.time()

        train_net.set_train()
        train_result = train_net()
        train_loss = train_result[0].asnumpy()
        train_accuracy = train_result[1].asnumpy()

        eval_net.set_train(False)
        eval_result = eval_net()
        eval_loss = eval_result[0].asnumpy()
        eval_accuracy = eval_result[1].asnumpy()

        loss_list.append(eval_loss)
        if epoch%10==0:
            print("Epoch:", '%04d' % (epoch), "train_loss=", "{:.5f}".format(train_loss),
                "train_acc=", "{:.5f}".format(train_accuracy), "val_loss=", "{:.5f}".format(eval_loss),
                "val_acc=", "{:.5f}".format(eval_accuracy), "time=", "{:.5f}".format(time.time() - t))

        if epoch > config.early_stopping and loss_list[-1] > np.mean(loss_list[-(config.early_stopping+1):-1]):
            print("Early stopping...")
            break

    t_test = time.time()
    test_net.set_train(False)
    test_result = test_net()
    test_loss = test_result[0].asnumpy()
    test_accuracy = test_result[1].asnumpy()
    print("Test set results:", "loss=", "{:.5f}".format(test_loss),
          "accuracy=", "{:.5f}".format(test_accuracy), "time=", "{:.5f}".format(time.time() - t_test))

# %% [markdown]
# ### 8. 启动训练、评估

# %%
#训练
print("============== Starting Training ==============")
train_eval(cfg)

# %%



