#include<stdio.h>
#include<stdlib.h>
// #define DEBUG

#define INF 0x7fffffff
#define MAXSIZE 1000

int s[MAXSIZE][MAXSIZE];
int d[MAXSIZE][MAXSIZE];
int test[MAXSIZE];
int n,m,k;
int in[MAXSIZE];
int in_cp[MAXSIZE];
int in_queue[MAXSIZE];

typedef struct{
    int data[MAXSIZE];
    int top;
    int rear;
}queue;

int is_empty(queue q)
{
    return (q.top==q.rear);
}

int front(queue q)
{
    return q.data[q.top];
}

int pop(queue q)
{
    if (is_empty(q)){
        return -1;
    }
    else
    {
        q.top++;
        return q.data[q.top-1];
    }
}

int push(queue q, int n)
{
    if(q.rear>=MAXSIZE-1){
        return -1;
    }
    else
    {
        q.rear++;
        q.data[q.rear]=n;
        return 1;
    }
}

typedef struct lnode* list;
typedef struct lnode{
    int data;
    struct lnode* next;
}lnode;

list make_empty()
{
    lnode* head=malloc(sizeof(lnode));
    head->next=NULL;
    return head;
}

list append(list l,int n)
{
    lnode* p=l; 
    while(!p){
        p=p->next;
    }
    lnode* new=malloc(sizeof(lnode));
    new->next=NULL;
    new->data=n;
    p->next=new;
    return l;
}


void init()
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            s[i][j] = INF;
            d[i][j] = INF;
        }
}

void input()
{
    scanf("%d %d",&n,&m);
    int t1,t2,tmp_s,tmp_d;
    init();
    for(int i=0;i<m;i++)
    {
        scanf("%d %d %d %d",&t1,&t2,&tmp_s,&tmp_d);
        s[t1][t2]=tmp_s;
        d[t1][t2]=tmp_d;
        in[t2]++;
        in_cp[t2]++;
    }
    scanf("%d",&k);
    for(int i=0;i<k;i++)
        scanf("%d",&test[i]);
}

void output()
{
    if(judge())
        printf("Okay.\n");
    else
        printf("Impossible.\n");
    for(int i=0; i<k;i++)
    {
        if (in[test[i]]==0)
            printf("You may take test %d directly.\n",test[i]);
        else
            output_path(test[i]);
    }
}

#ifdef DEBUG
void debugforinput()
{
    printf("s matrix is:\n");
    for(int i=0;i<n;i++)
    {
        printf("\n");
        for(int j=0;j<n;j++)
        {
            printf("%d ",s[i][j]);
        }
    }
    printf("\nd matrix is:\n");
    for(int i=0;i<n;i++)
    {
        printf("\n");
        for(int j=0;j<n;j++)
        {
            printf("%d ",d[i][j]);
        }
    }
    printf("\ntest list is:\n");
    for(int i=0;i<k;i++)
    {
        printf("%d ",test[i]);
    }
}
#endif

int judge()
{
    queue q;
    int num=0;
    //enqueue all nodes that indegree==0
    for(int i=0;i<n;i++)
    {
        if (in[i]==0)
        {
            in_queue[i]=1;
            push(q,i);
        }
    }
}

int main()
{
    input();

#ifdef DEBUG
    debugforinput();    
#endif

    return 0;
}