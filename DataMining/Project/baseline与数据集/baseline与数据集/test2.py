import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error
from sklearn.preprocessing import LabelEncoder

# 设置数据目录路径
data_dir = 'store-sales-time-series-forecasting'

# 读取训练数据、商店数据、测试数据和油价数据
train_df = pd.read_csv(os.path.join(data_dir, 'train.csv'))
stores_df = pd.read_csv(os.path.join(data_dir, 'stores.csv'))
test_df = pd.read_csv(os.path.join(data_dir, 'test.csv'))
oil_df = pd.read_csv(os.path.join(data_dir, 'oil.csv'))
holidays_df = pd.read_csv(os.path.join(data_dir, 'holidays_events.csv'))

# 合并油价数据到训练集和测试集
train_df = pd.merge(train_df, oil_df, on='date', how='left')
test_df = pd.merge(test_df, oil_df, on='date', how='left')

# 添加节假日特征
train_df['date'] = pd.to_datetime(train_df['date'])
train_df['is_holiday'] = train_df['date'].isin(holidays_df['date']).astype(int)
test_df['date'] = pd.to_datetime(test_df['date'])
test_df['is_holiday'] = test_df['date'].isin(holidays_df['date']).astype(int)

# 对family字段进行编码处理
label_encoder = LabelEncoder()
train_df['family_encoded'] = label_encoder.fit_transform(train_df['family'])
test_df['family_encoded'] = label_encoder.transform(test_df['family'])

# 填充缺失值
train_df.fillna(train_df.mean(), inplace=True)
test_df.fillna(test_df.mean(), inplace=True)

# 特征选择
features = ['store_nbr', 'family_encoded', 'dcoilwtico', 'is_holiday']
target = 'sales'

# 划分训练集和验证集
X_train, X_val, y_train, y_val = train_test_split(train_df[features], train_df[target], test_size=0.2, random_state=42)

# 随机森林回归模型
model = RandomForestRegressor(n_estimators=100, random_state=42)
model.fit(X_train, y_train)

# 预测验证集
y_val_pred = model.predict(X_val)

# 评估模型
mse = mean_squared_error(y_val, y_val_pred)
print('Mean Squared Error (Validation):', mse)

# 使用模型预测测试集
y_test_pred = model.predict(test_df[features])

# 保存结果到文件
output = pd.DataFrame({'id': test_df['id'], 'sales': y_test_pred})
output.to_csv('submission.csv', index=False)
