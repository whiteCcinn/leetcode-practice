#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *longestCommonPrefix(char **strs, int strSize)
{

  char *str = (char *)malloc(sizeof(char) * 100);

  strcpy(str, strs[0]);

  // 拿第8-10行代表和第13行比较，如果写法如下的话：
  // char *str = strs[0];
  // 全局数据区和栈区的字符串（也包括其他数据）有读取和写入的权限，而常量区的字符串（也包括其他数据）只有读取权限，没有写入权限。
  // 所以直接指向的时候，第30行将会报段错误

  int i, j;

  if (strSize == 0)
  {
    return "";
  }

  for (i = 1; i < strSize; i++)
  {
    j = 0;
    while (str[j] && strs[i][j] && str[j] == strs[i][j])
    {
      j++; //避免数组溢出并判断下一个元素是否相同
    }
    str[j] = '\0'; //字符串结束符只输出前面对应相同的
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
