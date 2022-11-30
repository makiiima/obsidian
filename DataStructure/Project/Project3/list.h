typedef struct lnode* list;
typedef struct lnode{
    int data;
    list* next;
}lnode;

list make_empty();
list append(list l,int n);
list delete(list l, int n);


