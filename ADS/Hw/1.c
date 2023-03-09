#include <stdio.h>
#include <stdlib.h>
 
#define Max(a,b) ( ( (a)>(b) )?(a):(b) )
typedef struct AvlNode * AvlTree;
typedef AvlTree Position;
struct AvlNode{
    int Data;
    int Level;
    AvlTree Left;
    AvlTree Right;
};
 
int Height(Position P);
 
Position LLRotation(Position A);
 
Position RRRotation(Position A);
 
Position LRRotation(Position A);
 
Position RLRotation(Position A);
 
AvlTree Insert(AvlTree T,int X);
 
 
int main()
{
    int N,v;
    AvlTree tree=NULL;
    scanf("%d",&N);
    while(N){
        scanf("%d",&v);
        tree=Insert(tree,v);
        N--;
    }
    printf("%d",tree->Data);
}
int Height(Position P)
{
    if(P==NULL) return -1;
    else return Max( Height(P->Left),Height(P->Right) )+1;
}
Position LLRotation(Position A)
{
    Position B=A->Left;
    A->Left=B->Right;
    B->Right=A;
    A->Level=Max(Height(A->Left),Height(A->Right))+1;
    B->Level=Max(Height(B->Left),Height(B->Right))+1;
    return B;
}
Position RRRotation(Position A)
{
    Position B=A->Right;
    A->Right=B->Left;
    B->Left=A;
    A->Level=Max(Height(A->Left),Height(A->Right))+1;
    B->Level=Max(Height(B->Left),Height(B->Right))+1;
    return B;
}
Position LRRotation(Position A)
{
    A->Left=RRRotation(A->Left);
    return LLRotation(A);
}
Position RLRotation(Position A)
{
    A->Right=LLRotation(A->Right);
    return RRRotation(A);
}
AvlTree Insert(AvlTree T,int X)
{
    if(T==NULL){
        T=(AvlTree)malloc(sizeof(struct AvlNode));
        T->Left=T->Right=NULL;
        T->Data=X;
        T->Level=0;
    }else if(X<T->Data){
        T->Left=Insert(T->Left,X);
        if( Height((T->Left))-Height(T->Right)==2 ){
            if(X<T->Left->Data)
                T=LLRotation(T);
            else
                T=LRRotation(T);
        }
    }else if(X>T->Data){
        T->Right=Insert(T->Right,X);
        if( Height((T->Right))-Height(T->Left)==2 ){
            if(X>T->Right->Data)
                T=RRRotation(T);
            else
                T=RLRotation(T);
        }
    }
    T->Level=Max( Height(T->Left),Height(T->Right) )+1;
    return T;
}
