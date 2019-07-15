#include "bst.c"
#include <stdlib.h>
#include <stdio.h>

int main()
{
  char value[] = {1, 2, 3, 4, 5, 6};

  int count = sizeof(value) / sizeof(char);

  BiTNode root;

  for (int i = 0; i < count; i++)
  {
    if (i == 0)
    {
      root.data = value[i];
      root.lChild = NULL;
      root.rChild = NULL;
    }
    else
    {
      Insert(&root, value[i]);
    }
  }

  PreOrder(&root);

  return 0;
}