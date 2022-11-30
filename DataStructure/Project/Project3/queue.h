typedef struct{
    int data[MAXSIZE];
    int top;
    int rear;
}queue;

int is_empty(queue q);
int front(queue q);
int pop(queue q);
int push(queue q, int n);
