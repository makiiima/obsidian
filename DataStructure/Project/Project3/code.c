#include<stdio.h>
#include<stdlib.h>

// #define DEBUG

#define MAXSIZE 1000
int s[MAXSIZE][MAXSIZE];
int d[MAXSIZE][MAXSIZE];
int test[MAXSIZE];
int n,m,k;

void input()
{
    scanf("%d %d",&n,&m);
    int t1,t2,tmp_s,tmp_d;
    for(int i=0;i<m;i++)
    {
        scanf("%d %d %d %d",&t1,&t2,&tmp_s,&tmp_d);
        s[t1][t2]=tmp_s;
        d[t1][t2]=tmp_d;
    }
    scanf("%d",&k);
    for(int i=0;i<k;i++)
        scanf("%d",&test[i]);
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
    printf("d matrix is:\n");
    for(int i=0;i<n;i++)
    {
        printf("\n");
        for(int j=0;j<n;j++)
        {
            printf("%d ",d[i][j]);
        }
    }
    printf("test list is:\n");
    for(int i=0;i<k;i++)
    {
        printf("%d ",test[i]);
    }
}
#endif

int judge(int t1, int t2)
{
    
}

int main()
{
    input();
#ifdef DEBUG
    debugforinput();    
#endif
}