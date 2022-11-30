#include<stdio.h>
#include<stdlib.h>
// #define DEBUG

#define INF 0x7fffffff
#define MAXSIZE 1000

#include"queue.h"
#include"list.h"

int s[MAXSIZE][MAXSIZE];
int d[MAXSIZE][MAXSIZE];
int test[MAXSIZE];
int n,m,k;
int in[MAXSIZE];
int in_cp[MAXSIZE];

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
    for(int i=0;i<n;i++)
    {
        if(in_cp[i]==0)
            push(q,i);
        int cnt=0;
        while(!is_empty(q))
        {
            int now=front(q);
            cnt++;
            pop(q);
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