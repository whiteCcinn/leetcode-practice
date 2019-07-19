#include <stdio.h>

int min(int value1, int value2)
{
  if (value1 >= value2)
  {
    return value2;
  }
  return value1;
}

int coinChange(int *coins, int coinsSize, int amount)
{
  int maxSize = amount + 1;
  int dp[maxSize];
  dp[0] = 0;
  int coin;
  for (int c = 1; c < maxSize; c++)
  {
    dp[c] = maxSize;
  }
  for (int i = 1; i <= amount; i++)
  {
    for (int ii = 0; ii < coinsSize; ii++)
    {
      coin = coins[ii];
      if (coin <= i)
      {
        dp[i] = min(dp[i], dp[i - coin] + 1);
      }
    }
  }
  return dp[amount] > amount ? -1 : dp[amount];
}
int main()
{
  int coins[] = {1, 2, 5};

  int count = sizeof(coins) / sizeof(int);

  int amount = 11;

  int ret = coinChange(coins, count, amount);

  printf("期待结果为3，实际结果：%d\n", ret);
}