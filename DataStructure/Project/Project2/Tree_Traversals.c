#include<stdio.h>
#include<stdlib.h>
// #define _DEBUG_
typedef struct tNode{
    char data;
    struct tNode* left;
    struct tNode* right;
}tNode;
typedef tNode* tree;

typedef struct lNode{
    char data;
    struct lNode* next;
}lNode;
typedef lNode* list;
//make a new tree node
tNode* newtNode(char data)
{
    tNode* p;
    p=(tNode*)malloc(sizeof(tNode));
    p->data=data;
    p->left=NULL;
    p->right=NULL;
    return p;
}

//make a new list node
lNode* newlNode(char data)
{
    lNode* p;
    p=(lNode*)malloc(sizeof(lNode));
    p->data=data;
    p->next=NULL;
    return p;
}

//make an empty list
list makelist()
{
    lNode* p;
    p=(lNode*)malloc(sizeof(lNode));
    p->next=NULL;
    return p;
}

//append a node after a list
lNode* append(list l,char data)
{
    lNode* p=l;
    while(p->next!=NULL)
        p=p->next;
    p->next=newlNode(data);
    return l;
}

//print a tree in pre-order
void printPre(tree t)
{
    if(t==NULL) return;
    printf("%d ",t->data);
    printPre(t->left);
    printPre(t->right);
}

//print a tree in in-order
void printIn(tree t)
{
    if(t==NULL) return;
    printIn(t->left);
    printf("%d ",t->data);
    printIn(t->right);
}

//print a tree in post-order
void printPost(tree t)
{
    if(t==NULL) return;
    printPre(t->left);
    printPre(t->right);
    printf("%d ",t->data);
}

//print a list
void printlist(list l)
{
    list p;
    p=l;
    while(p=p->next)printf("%c ",p->data);
    printf("\n");
}

tree fromPreIn(char* pre,char* in)
{

}

//store the input information in 3 linked lists
void store(list pre, list in, list post, int N)
{
    for(int i=0;i<N;i++)
    {
        char data;
        scanf("%c ",&data);
        append(in,data);
    }
    for(int i=0;i<N;i++)
    {
        char data;
        scanf("%c ",&data);
        append(pre,data);
    }
    for(int i=0;i<N;i++)
    {
        char data;
        scanf("%c ",&data);
        append(post,data);
    }
}

int main()
{
    int N;
    scanf("%d \n",&N);
    list pre,in,post,p;
    pre=makelist();
    in=makelist();
    post=makelist();
    store(pre,in,post,N);
    //3 linked list to store the given information   

    #ifdef _DEBUG_
    printf("Here is your stored information:\n");
    printlist(in);
    printlist(pre);
    printlist(post);
    #endif
    
    

}