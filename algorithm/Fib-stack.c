#include <stdio.h>

int Fib(int N)
{
  if (N == 1 || N == 2)
  {
    return 1;
  }
  return Fib(N - 1) + Fib(N - 2);
}

int main()
{
  int n = 30;

  int ret = Fib(n);

  printf("n = %d , 结果：%d\n", n, ret);
}