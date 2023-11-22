#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node {
  int Coefficient;
  int Exponent;
  PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read();        /* details omitted */
void Print(Polynomial p); /* details omitted */
Polynomial Add(Polynomial a, Polynomial b);

int main() {
  Polynomial a, b, s;
  a = Read();
  b = Read();
  s = Add(a, b);
  Print(s);
  return 0;
}

/* Your function will be put here */

Polynomial Add(Polynomial a, Polynomial b) {
  Polynomial s = (Polynomial)malloc(sizeof(struct Node));
  s->Next = NULL;
  Polynomial curr_a = a->Next;
  Polynomial curr_b = b->Next;
  Polynomial curr_s = s;
  while (curr_a || curr_b) {
    if (curr_b == NULL ||
        (curr_a != NULL && curr_a->Exponent > curr_b->Exponent)) {
      Polynomial tmp = (Polynomial)malloc(sizeof(struct Node));
      tmp->Exponent = curr_a->Exponent;
      tmp->Coefficient = curr_a->Coefficient;
      curr_s->Next = tmp;
      curr_a = curr_a->Next;
      curr_s = curr_s->Next;
    } else if (curr_a == NULL ||
               (curr_b != NULL && curr_a->Exponent < curr_b->Exponent)) {
      Polynomial tmp = (Polynomial)malloc(sizeof(struct Node));
      tmp->Exponent = curr_b->Exponent;
      tmp->Coefficient = curr_b->Coefficient;
      curr_s->Next = tmp;
      curr_b = curr_b->Next;
      curr_s = curr_s->Next;
    } else {
      Polynomial tmp = (Polynomial)malloc(sizeof(struct Node));
      if (curr_a->Coefficient + curr_b->Coefficient != 0) {
        tmp->Exponent = curr_a->Exponent;
        tmp->Coefficient = curr_a->Coefficient + curr_b->Coefficient;
        curr_s->Next = tmp;
        curr_a = curr_a->Next;
        curr_b = curr_b->Next;
        curr_s = curr_s->Next;
      } else {
        curr_a = curr_a->Next;
        curr_b = curr_b->Next;
      }
    }
  }
  curr_s->Next = NULL;
  return s;
}
