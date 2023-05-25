import pandas as pd
from sklearn.svm import SVC
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score
from sklearn.impute import SimpleImputer
from math import ceil

# 读取train_num.csv和validate_num.csv文件
train_data = pd.read_csv('train_num.csv')
validate_data = pd.read_csv('validate_num.csv')

# 离散化处理SalePrice
train_data['SalePrice'] = train_data['SalePrice'].apply(lambda x: ceil(x / 100000))
validate_data['SalePrice'] = validate_data['SalePrice'].apply(lambda x: ceil(x / 100000))

# 提取输入特征和标签
X_train = train_data.drop('SalePrice', axis=1)
y_train = train_data['SalePrice']
X_validate = validate_data.drop('SalePrice', axis=1)
y_validate = validate_data['SalePrice']

# 使用均值填充缺失值
imputer = SimpleImputer(strategy='mean')
X_train = imputer.fit_transform(X_train)
X_validate = imputer.transform(X_validate)

# 训练SVM模型
svm_model = SVC()
svm_model.fit(X_train, y_train)

# 在验证集上进行预测
y_pred_svm = svm_model.predict(X_validate)

# 计算SVM模型的正确率
accuracy_svm = accuracy_score(y_validate, y_pred_svm)

# 训练Logistic Regression模型
lr_model = LogisticRegression(max_iter=1000000, solver='lbfgs')
lr_model.fit(X_train, y_train)

# 在验证集上进行预测
y_pred_lr = lr_model.predict(X_validate)

# 计算Logistic Regression模型的正确率
accuracy_lr = accuracy_score(y_validate, y_pred_lr)

# 打印正确率
print("SVM Accuracy:", accuracy_svm)
print("Logistic Regression Accuracy:", accuracy_lr)