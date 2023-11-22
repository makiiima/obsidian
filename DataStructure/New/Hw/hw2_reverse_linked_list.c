#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
  ElementType Element;
  Position Next;
};

List Read();        /* details omitted */
void Print(List L); /* details omitted */
List Reverse(List L);

int main() {
  List L1, L2;
  L1 = Read();
  L2 = Reverse(L1);
  Print(L1);
  Print(L2);
  return 0;
}

/* Your function will be put here */

List Reverse(List L) {
  if (L == NULL) {
    return NULL;
  }
  List result = (List)malloc(sizeof(struct Node));
  result->Next = NULL;
  Position curr = L->Next;
  Position tmp = (Position)malloc(sizeof(struct Node));
  while (curr) {
    tmp = curr->Next;
    curr->Next = result->Next;
    result->Next = curr;
    curr = tmp;
  }
  L->Next = result->Next;
  return result;
}
