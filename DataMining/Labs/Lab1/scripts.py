import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns


data = pd.read_csv('data/train.csv')

# 将SalePrice按照10万为区间进行分组统计
bins = range(0, int(data['SalePrice'].max())+100000, 100000)
groups = pd.cut(data['SalePrice'], bins=bins).value_counts(sort=False)

# 绘制柱状图
plt.bar(range(len(groups)), groups.values)

# 设置x轴标签
plt.xticks(range(len(groups)), groups.index.astype(str), rotation=45)

# 设置图表标题和x轴标签
plt.title('SalePrice Distribution')
plt.xlabel('SalePrice Range (10K)')
plt.ylabel('Count')

# 显示图表
plt.savefig('SalePrice Distribution.png')

# 绘制散点图
plt.scatter(data['SalePrice'], data['GarageArea'])

# 设置图表标题和坐标轴标签
plt.title('SalePrice vs GarageArea')
plt.xlabel('SalePrice')
plt.ylabel('GarageArea')

# 显示图表
plt.savefig('SalePrice vs GarageArea.png')

# 按照BldgType分组，绘制箱线图
data.boxplot(column='SalePrice', by='BldgType', figsize=(8, 6))

# 设置图表标题和坐标轴标签
plt.title('SalePrice Distribution by BldgType')
plt.xlabel('BldgType')
plt.ylabel('SalePrice')

# 显示图表
plt.savefig('SalePrice Distribution by BldgType.png')

df = pd.read_csv('data/train.csv')
df = df[['SalePrice', 'OverallQual', 'GrLivArea', 'MSSubClass', 'LotArea', 'OverallCond', 'YearBuilt', 'YearRemodAdd', 'MasVnrArea', 'BsmtFinSF1', 'BsmtFinSF2', 'BsmtUnfSF', 'TotalBsmtSF', '1stFlrSF', '2ndFlrSF', 'LowQualFinSF', 'BsmtFullBath', 'BsmtHalfBath', 'FullBath', 'HalfBath', 
        'BedroomAbvGr', 'KitchenAbvGr', 'TotRmsAbvGrd', 'Fireplaces', 'GarageYrBlt', 'GarageCars', 'GarageArea', 'WoodDeckSF', 'OpenPorchSF', 'EnclosedPorch', '3SsnPorch', 'ScreenPorch', 'PoolArea', 'MiscVal', 'MoSold', 'YrSold']]

corrmat = df.corr()

f, ax = plt.subplots(figsize=(12, 9))


k = 11
cols = corrmat.nlargest(k, df.columns[0]).index
cm = np.corrcoef(df[cols].values.T)

hm = sns.heatmap(cm,
                 cbar=True,
                 annot=True,
                 square=True,
                 fmt=".3f",
                 vmin=0,             
                 vmax=1,
                 linewidths=.5,
                 cmap='Blues',
                 annot_kws={"size": 10},
                 xticklabels=cols,
                 yticklabels=cols)    


plt.savefig('corr.png')

