import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, mean_squared_error
from sklearn.impute import SimpleImputer

# 读取train_num.csv和validate_num.csv文件
train_data = pd.read_csv('train_num.csv')
validate_data = pd.read_csv('validate_num.csv')

# 提取输入特征和标签
X_train = train_data.drop('SalePrice', axis=1)
y_train = train_data['SalePrice']
X_validate = validate_data.drop('SalePrice', axis=1)
y_validate = validate_data['SalePrice']

# 使用均值填充缺失值
imputer = SimpleImputer(strategy='mean')
X_train = imputer.fit_transform(X_train)
X_validate = imputer.transform(X_validate)

# 训练线性回归模型
model = LinearRegression()
model.fit(X_train, y_train)

# 在验证集上进行预测
y_pred = model.predict(X_validate)

# 计算MAE和RMSE
mae = mean_absolute_error(y_validate, y_pred)
rmse = mean_squared_error(y_validate, y_pred, squared=False)

# 打印预测误差
print("MAE:", mae)
print("RMSE:", rmse)
