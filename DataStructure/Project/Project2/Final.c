#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define _DEBUG_
int N;
int pre[MAXSIZE]={0};
int fpre[MAXSIZE]={0};
int in[MAXSIZE]={0};
int fin[MAXSIZE]={0};
int post[MAXSIZE]={0};
int fpost[MAXSIZE]={0};
int frequency[MAXSIZE]={0};
 
typedef struct tNode
{
    int data;
    struct tNode *left;
    struct tNode *right;
} tNode;
typedef tNode *tree;

// make a new tree node
tNode *newtNode(char data)
{
    tNode *p;
    p = (tNode *)malloc(sizeof(tNode));
    p->data = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

// print a tree in pre-order
void printPre(tree t)
{
    if (t == NULL)
        return;
    printf("%d ", t->data);
    printPre(t->left);
    printPre(t->right);
}

// print a tree in in-order
void printIn(tree t)
{
    if (t == NULL)
        return;
    printIn(t->left);
    printf("%d ", t->data);
    printIn(t->right);
}

// print a tree in post-order
void printPost(tree t)
{
    if (t == NULL)
        return;
    printPre(t->left);
    printPre(t->right);
    printf("%d ", t->data);
}

// store the input information in 3 arrays
void store(int pre[] , int in [] , int post[])
{
    char tmp;
    for(int i=0;i<N;i++)
    {
        scanf("%c ",&tmp);
        if(tmp=='-')
            in[i]=-1;
        else
        {
            in[i]=tmp-'0';
            frequency[in[i]-1]++;
        }
    }
    for(int i=0;i<N;i++)
    {
        scanf("%c ",&tmp);
        if(tmp=='-')
            pre[i]=-1;
        else
        {
            pre[i]=tmp-'0';
            frequency[pre[i]-1]++;
        }
    }
    for(int i=0;i<N;i++)
    {
        scanf("%c ",&tmp);
        if(tmp=='-')
            post[i]=-1;
        else
        {
            post[i]=tmp-'0';
            frequency[post[i]-1]++;
        }
    }
}

//test if test case in each order is valid
//h1 is the head of test case of in-order
//h2 is the head of test case of pre-order
//h3 is the head of test case of post-order
//l is the length of test case
int test(int h1,int h2,int h3,int l)
{
    if(l==0)    return 1;
    for(int l1=0;l1<l;l1++){
        int l2=l-1-l1;
         
    }
}
//print the information in the array
void printlist(int list[])
{
    for(int i=0;i<N;i++)
    {
        printf("%d ",list[i]);
    }
    printf("\n");
}
int main()
{
    scanf("%d\n", &N);
    store(pre, in, post);
    // 3 linked list to store the given information

    int miss=0;
    for(int i=0;i<N;i++)
    {
        if(frequency[i]==0)
            miss++;
    }
    if(miss>1)
    {
        printf("Impossible");
        return 0;
    }
#ifdef _DEBUG_
    printf("Here is your stored information:\n");
    printlist(in);
    printlist(pre);
    printlist(post);
    printlist(frequency);
    for(int i=0;i<20;i++){
        printf("%d ",in[i]);
    }
#endif

    return 0;
}