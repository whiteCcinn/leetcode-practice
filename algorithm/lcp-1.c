#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *longestCommonPrefix(char **strs, int strSize)
{
  int i, j;

  if (strSize == 0)
  {
    return "";
  }

  char *str = (char *)malloc(sizeof(char) * 1000);

  strcpy(str, strs[0]);

  for (i = 1; i < strSize; i++)
  {
    j = 0;
    while (str[j] && strs[i][j] && str[j] == strs[i][j])
    {
      j++;
    }
    str[j] = '\0';
  }

  return str;
}

int main()
{
  char *strs[] = {"lees", "leetcode", "leet", "leets"};

  int size = sizeof(strs) / sizeof(char *);

  char *lcp;

  lcp = longestCommonPrefix(strs, size);

  printf("%s\n", lcp);

  return 0;
}
