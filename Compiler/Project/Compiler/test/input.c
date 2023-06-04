
int main(void)
{
  int a;
  a=250;
  int b;
  b=50;
  int temp;
  while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
  }
  printf("%d",a);
  return 0;
}