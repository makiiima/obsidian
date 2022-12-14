#include <stdio.h>
#include <stdlib.h>
#define ElementType int

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

struct Node
{
    ElementType Element;
    Position Next;
};

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
Position Find(ElementType X, List L);
void Delete(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
Position Header(List L);
Position First(List L);
Position Advance(Position P);
ElementType Retrieve(Position P);

List MakeEmpty(List L)
{
    L=(struct Node*) malloc(sizeof(struct Node));
    L->Next=NULL;
    return L;
}

void append(List L,ElementType X)
{
    Position p;
    p=L;
    while(p->Next!=NULL){
        p=p->Next;
    }
    Position tmp;
    tmp=(Position)malloc(sizeof(struct Node));
    tmp->Next=NULL;
    tmp->Element=X;
    p=tmp;
}

int IsEmpty(List L)
{
    return L->Next == NULL;
}

int IsLast(Position P, List L)
{
    return P->Next == NULL;
}

Position Find(ElementType X, List L)
{
    Position P;
    P = L->Next;
    while (P != NULL && P->Element != X)
        P = P->Next;
    if (P->Next == NULL && P->Element != X)
        return NULL;
    return P;
}

void Delete(ElementType X, List L)
{
    Position P, TmpCell;
    P = FindPrevious(X, L);
    if (!IsLast(P, L))
    {
        TmpCell = P->Next;
        P->Next = TmpCell->Next;
        free(TmpCell);
    }
}

Position FindPrevious(ElementType X, List L)
{
    Position P;
    P = L;
    while (P->Next->Element != X && P->Next != NULL)
        P = P->Next;
    if (P->Next == NULL)
        return NULL;
    return P;
}

void Insert(ElementType X, List L, Position P)
{
    Position TmpCell;
    TmpCell = malloc(sizeof(struct Node));
    if (TmpCell == NULL)
        // FatalError("Out of space!");

    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}

void DeleteList(List L)
{
    Position p;
    p=L;
    while(L)
    {
        free(p);
        L=L->Next;
        p=L;
    }
    // wrong!! L was not freed
    // Position p,tmp;
    // p=L->Next;
    // L->Next=NULL;
    // while(p!=NULL)
    // {
    //     tmp=p->Next;
    //     free(p);
    //     p=tmp;
    // }
}

Position Header(List L)
{
    return L;    
}

Position First(List L)
{
    return L->Next;
}

Position Advance(Position P)
{
       
}
ElementType Retrieve(Position P);

int main()
{
    List lst;
    lst=(List)malloc(sizeof(struct Node));
    lst->Next=NULL;
    append(lst,1);
    return 0;
}
