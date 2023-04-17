"""
导入必要的库
"""
from multiprocessing import cpu_count
from gensim.models import Word2Vec
from gensim.models import KeyedVectors

corpus_file = "corpus.txt"  # 读取文本文件
out_embedding_file = "embedding.txt"  # 存储的词向量文件

"""
构建模型
"""
model = Word2Vec(corpus_file=corpus_file, vector_size=100, window=7, min_count=5, workers=cpu_count(), sg=1)
model.wv.save_word2vec_format(out_embedding_file, binary=False)
word2vec_model = KeyedVectors.load_word2vec_format("embedding.txt")

"""
进行相似度测试
"""
word = ['金融']
res = word2vec_model.most_similar(word)
print(word)
print(res)
