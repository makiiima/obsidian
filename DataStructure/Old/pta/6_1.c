#include<stdlib.h>
#define ElementType int
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data; /* 存储结点数据 */
    PtrToNode   Next; /* 指向下一个结点的指针 */
};
typedef PtrToNode List; /* 定义单链表类型 */

//your code here
List Reverse(List L)
{
    PtrToNode l1,l2,tmp,p;
    p=L;
    int n=-1;
    while(p!=NULL){
        p=p->Next;
        n++;
    }
    l2=(PtrToNode)malloc(sizeof(struct Node));
    p=l2;
    l2->Next=NULL;
    for(int i=0;i<n;i++){
        tmp=(PtrToNode)malloc(sizeof(struct Node));
        tmp->Next=NULL;
        p->Next=tmp;
        p=p->Next;
    }
    p=L;
    int lst[n];
    int i=0;
    while(p->Next!=NULL)
    {
        p=p->Next;
        lst[i]=p->Data;
        i++;
    }
    i--;
    p=l2;
    while(p->Next!=NULL)
    {
        p->Data=lst[i];
        p=p->Next;
        i--;
    }
    return l2;
}

int main(){
    List L1,L2,p;
    L1=(PtrToNode)malloc(sizeof(struct Node));
    p=L1;
    p->Next=NULL;
    for(int i=0;i<5;i++){
        PtrToNode tmp;
        tmp=(PtrToNode)malloc(sizeof(struct Node));
        tmp->Next=NULL;
        tmp->Data=i;
        p->Next=tmp;
        p=p->Next;
    }
    L2=Reverse(L1);
    return 0;
}