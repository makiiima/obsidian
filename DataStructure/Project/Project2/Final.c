#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define _DEBUG_
int N;
int miss=0;
int missnum;
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

//return the maximum of three
int max(int n1,int n2,int n3)
{
    if(n1>=n2&&n1>=n3)
        return n1;
    if(n2>=n1&&n2>=n3)
        return n2;
    return n3;
}
//test if test case in each order is valid
//h1 is the head of test case of in-order
//h2 is the head of test case of pre-order
//h3 is the head of test case of post-order
//l is the length of test case
int test(int h1,int h2,int h3,int l)
{
    if(l==0)    return 1;
    for(int l1=0;l1<l;l1++)
    {
        int l2=l-1-l1;
        int n1=0,n2=0,n3=0,cnt=0;
        if(in[h1+l1]>0)
            n1=in[h1+l1],cnt++;
        if(pre[h2]>0)
            n2=pre[h2],cnt++;
        if(post[h3+l-1]>0)
            n3=post[h3+l-1],cnt++;
        if((n1*n2!=0&&n1!=n2)||(n1*n3!=0&&n1!=n3)||(n2*n3!=0&&n2!=n3))
            continue;

        missnum=max(n1,n2,n3);
        if(cnt==0)//n1,n2,n3 is all '-'
        {
            if(miss==0)
                continue;
            if(miss==1)//n1,n2,n3 is exactly the missed number
            {
                fin[h1+l1]=missnum;
                fpre[h2]=missnum;
                fpost[h3+l-1]=missnum;
                miss--;
            }
        }
        else
        {
            if(cnt!=frequency[missnum-1])
                continue;
            fin[h1+l1]=missnum;
            fpre[h2]=missnum;
            fpost[h3+l-1]=missnum;

        }
        int flag1=test(h1,h2+1,h3,l1);
        int flag2=test(h1+l1+1,h2+l1+1,h3+l1,l2);
        if(!cnt)
            miss=1;
        if(flag1&&flag2)
            return 1;
    }
    return 0;
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
    scanf("%d ", &N);
    store(pre, in, post);
    // 3 linked list to store the given information


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
    int res=test(0,0,0,N);
    if(!res)
    {
        printf("Impossible");
        return 0;
    }
#ifdef _DEBUG_
    printf("Here is your stored information:\n");
    printf("in:\t");
    printlist(in);
    printf("pre:\t");
    printlist(pre);
    printf("post:\t");
    printlist(post);
    printf("The frequency is:\n");
    printlist(frequency);
    for(int i=0;i<N;i++){
        printf("%d ",frequency[i]);
    }
    printf("\n");
    printf("Heer is your final lists:\n");
    printf("fin:\t");
    printlist(fin);
    printf("fpre:\t");
    printlist(fpre);
    printf("fpost:\t");
    printlist(fpost);
#endif

    return 0;
}