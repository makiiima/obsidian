/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *getRow(int rowIndex, int *returnSize) {
  returnSize = (int *)malloc(sizeof(int) * rowIndex + 1);
  if (rowIndex == 0) {
    returnSize[0] = 1;
  } else if (rowIndex == 1) {
    returnSize[0] = 1;
    returnSize[1] = 1;
  } else {
    returnSize[0] = 1;
    returnSize[rowIndex] = 1;
    int *tmp = getRow(rowIndex - 1, returnSize);
    for (int i = 1; i < rowIndex; i++) {
      returnSize[i] = tmp[i - 1] + tmp[i];
    }
  }
  return returnSize;
}
