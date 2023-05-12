# %%
import moxing as mox
mox.file.copy_parallel(src_url="obs://liyunfan-nlp/nlp/word_embedding/corpus.txt", dst_url='corpus.txt')

# %%
from multiprocessing import cpu_count
from gensim.models import Word2Vec
from gensim.models import KeyedVectors

# %%
corpus_file = "corpus.txt"
out_embedding_file = "embedding.txt"

# %%
?Word2Vec

# %%
model = Word2Vec(corpus_file = corpus_file, vector_size=100, window=5, min_count=5, workers=cpu_count(),sg=1)
model.wv.save_word2vec_format(out_embedding_file, binary=False)

# %%
word2vec_model = KeyedVectors.load_word2vec_format("embedding.txt")

# %%
word2vec_model['中国']

# %%
testwords = ['金融','喜欢','中国','北京']
for word in testwords:
    res = word2vec_model.most_similar(word)
    print(word)
    print(res)

# %%
mox.file.copy_parallel(src_url="embedding.txt", dst_url="obs://liyunfan-nlp/nlp/word_embedding/embedding.txt")


