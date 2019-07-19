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
  int dp[amount + 1];
  dp[0] = 0;
  for (int c = 1; c < amount + 1; c++)
  {
    dp[c] = amount + 1;
  }
  for (int i = 1; i <= amount; i++)
  {
    for (int j = 0; j < coinsSize; j++)
    {
      if (coins[j] <= i)
      {
        dp[i] = min(dp[i], dp[i - coins[j]] + 1);
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