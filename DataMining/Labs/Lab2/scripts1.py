import pandas as pd
import numpy as np

# 读取train.csv文件
data = pd.read_csv('data/train.csv')

# 随机分割数据集
train_data = data.sample(frac=0.8, random_state=42)  # 80%的数据作为训练集
validate_data = data.drop(train_data.index)  # 剩余的数据作为验证集

# 选择数值型属性
num_cols = data.select_dtypes(include=np.number).columns

# 保留数值型属性并保存到CSV文件
train_data_num = train_data[num_cols]
validate_data_num = validate_data[num_cols]

train_data_num.to_csv('train_num.csv', index=False)
validate_data_num.to_csv('validate_num.csv', index=False)
