import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_absolute_error, mean_squared_error
from sklearn.linear_model import LinearRegression
from sklearn.impute import SimpleImputer

# 读取训练集和验证集数据
train_data = pd.read_csv('train_num.csv')
validate_data = pd.read_csv('validate_num.csv')

# 提取特征和标签
X_train = train_data.drop('SalePrice', axis=1)
y_train = train_data['SalePrice']

X_val = validate_data.drop('SalePrice', axis=1)
y_val = validate_data['SalePrice']

# 处理缺失值
imputer = SimpleImputer(strategy='mean')
X_train_imputed = imputer.fit_transform(X_train)
X_val_imputed = imputer.transform(X_val)

# 构建LinearRegression模型
linear_regression_model = LinearRegression()

# 训练LinearRegression模型
linear_regression_model.fit(X_train_imputed, y_train)

# 在验证集上进行预测
y_pred = linear_regression_model.predict(X_val_imputed)

# 计算预测误差
mae = mean_absolute_error(y_val, y_pred)
rmse = mean_squared_error(y_val, y_pred, squared=False)

# 打印预测误差
print("MAE:", mae)
print("RMSE:", rmse)
