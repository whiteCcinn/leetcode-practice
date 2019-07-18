#include <stdio.h>

int Fib(int N)
{
  if (N < 2)
  {
    return N;
  }
  int prev = 0, current = 1;
  for (int i = 0; i < N - 1; i++)
  {
    int sum = prev + current;
    prev = current;
    current = sum;
  }

  return current;
}

int main()
{
  int n = 30;

  int ret = Fib(n);

  printf("n = %d , 结果：%d\n", n, ret);
}