#include<stdio.h>
#include<stdlib.h>

int n;
int q[110];

int judge(int k, int i, int j)
{
  int t = q[k];
  if( t > 0 )
  {
    if( t == i || t == j)
      return 1;
    return 0;
  }

  t = -t;
  if( t == i || t == j)
    return 0;
  return 1;
}

int main()
{
  scanf("%d");
}
