import numpy as np           # 提供维度数组与矩阵运算
import copy                  # 从copy模块导入深度拷贝方法
import itertools
from board import Chessboard
def testlst(lst):
    chessboard = Chessboard(False)
    chessboard.boardInit(False)
    Queen_setRow = lst
    for i,item in enumerate(Queen_setRow):
        if chessboard.setQueen(i,item,False):
            continue
        else:
            break
    if Chessboard.isWin(chessboard):
        return True
    else:
        return False


lsts=list(itertools.permutations([0,1,2,3,4,5,6,7],8))
solutions =[]
for i in lsts:
    if testlst(i):
        solutions.append(list(i))
    else:
        continue

print(solutions)