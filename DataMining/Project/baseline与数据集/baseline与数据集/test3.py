import os
import numpy as np
import pandas as pd
import xgboost as xgb
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error

# 加载数据
data_dir = 'store-sales-time-series-forecasting'
train_df = pd.read_csv(os.path.join(data_dir, 'train.csv'))
stores_df = pd.read_csv(os.path.join(data_dir, 'stores.csv'))
test_df = pd.read_csv(os.path.join(data_dir, 'test.csv'))
oil_df = pd.read_csv(os.path.join(data_dir, 'oil.csv'))
holidays_df = pd.read_csv(os.path.join(data_dir, 'holidays_events.csv'))

# 合并数据集
train_df = train_df.merge(stores_df, on='store_nbr', how='left')
train_df = train_df.merge(oil_df, on='date', how='left')
train_df = train_df.merge(holidays_df, on='date', how='left')

# 处理缺失值
train_df.fillna(train_df.mean(), inplace=True)

# 特征编码
label_encoder = LabelEncoder()
train_df['family_encoded'] = label_encoder.fit_transform(train_df['family'])
train_df['is_holiday'] = train_df['type'].apply(lambda x: 1 if x == 'Holiday' else 0)

# 划分训练集和测试集
X = train_df[['store_nbr', 'family_encoded', 'dcoilwtico', 'is_holiday']]
y = train_df['sales']
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 定义XGBoost模型
model = xgb.XGBRegressor(learning_rate=0.1, n_estimators=100, max_depth=3)

# 训练模型
model.fit(X_train, y_train)

# 预测
y_pred = model.predict(X_test)

# 评估模型
mse = mean_squared_error(y_test, y_pred)
rmse = np.sqrt(mse)
print('Root Mean Squared Error:', rmse)
