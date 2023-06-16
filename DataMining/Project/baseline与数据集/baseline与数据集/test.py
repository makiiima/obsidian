
# 加载数据
train_df = pd.read_csv(os.path.join(data_dir, 'train.csv'))
stores_df = pd.read_csv(os.path.join(data_dir, 'stores.csv'))
test_df = pd.read_csv(os.path.join(data_dir, 'test.csv'))
oil_df = pd.read_csv(os.path.join(data_dir, 'oil.csv'))
holiday_df = pd.read_csv(os.path.join(data_dir, 'holiday_events.csv'))

# 将日期转换为datetime类型
train_df['date'] = pd.to_datetime(train_df['date'])
test_df['date'] = pd.to_datetime(test_df['date'])
oil_df['date'] = pd.to_datetime(oil_df['date'])
holiday_df['date'] = pd.to_datetime(holiday_df['date'])

# 将油价数据加入到训练数据中
train_df = pd.merge(train_df, oil_df, on='date', how='left')
test_df = pd.merge(test_df, oil_df, on='date', how='left')

# 将节假日数据加入到训练数据中
train_df = pd.merge(train_df, holiday_df, on='date', how='left')
test_df = pd.merge(test_df, holiday_df, on='date', how='left')

# 特征工程
train_df['month'] = train_df['date'].dt.month
train_df['day'] = train_df['date'].dt.day
train_df['dayofweek'] = train_df['date'].dt.dayofweek
train_df['is_promotion'] = train_df['onpromotion'].apply(lambda x: 1 if x else 0)
train_df['is_holiday'] = train_df['type'].apply(lambda x: 1 if x == 'Holiday' else 0)

test_df['month'] = test_df['date'].dt.month
test_df['day'] = test_df['date'].dt.day
test_df['dayofweek'] = test_df['date'].dt.dayofweek
test_df['is_promotion'] = test_df['onpromotion'].apply(lambda x: 1 if x else 0)
test_df['is_holiday'] = test_df['type'].apply(lambda x: 1 if x == 'Holiday' else 0)

# 训练模型
from sklearn.ensemble import RandomForestRegressor

X_train = train_df[['store_nbr', 'family', 'month', 'day', 'dayofweek', 'is_promotion', 'is_holiday', 'dcoilwtico']]
y_train = train_df['sales']
X_test = test_df[['store_nbr', 'family', 'month', 'day', 'dayofweek', 'is_promotion', 'is_holiday', 'dcoilwtico']]

rf = RandomForestRegressor(n_estimators=100, max_depth=10, random_state=42)
rf.fit(X_train, y_train)

# 预测销量
y_pred = rf.predict(X_test)

# 输出结果
output = pd.DataFrame({'id': test_df['id'], 'sales': y_pred})
output.to_csv('submission_baseline.csv', index=False)