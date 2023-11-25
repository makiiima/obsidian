#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int data[1000];
  int top;
} stack;

stack *createStack() {
  stack *s = (stack *)malloc(sizeof(stack));
  s->top = -1;
  return s;
}

void push(stack *s, int num) {
  s->top += 1;
  s->data[s->top] = num;
}

int pop(stack *s) {
  if (s->top < 0) {
    return -1;
  }
  int num = s->data[s->top];
  s->top -= 1;
  return num;
}

int main() {
  stack *s1 = createStack();
  stack *s2 = createStack();
  int n, num, time;
  scanf("%d\n", &n);
  char op;
  for (int i = 0; i < n; i += 1) {
    time = 0;
    scanf(" %c", &op);
    if (op == 'I') {
      scanf(" %d", &num);
      push(s1, num);
      time++;
    } else if (op == 'O') {
      if (s2->top == -1) {   // 如果s2为空
        if (s1->top == -1) { // 如果s1也为空
          printf("ERROR\n");
        } else {
          while (s1->top != -1) { // 将s1中的所有元素转移到s2
            push(s2, pop(s1));
            time += 2; // 每转移一个元素，时间增加2（pop和push各1单位时间）
          }
        }
      }
      if (s2->top != -1) { // 现在s2不为空，可以从s2出队
        printf("%d %d\n", pop(s2), time + 1); // 出队一个元素，时间再加1
      }
    }
  }

  return 0;
}
