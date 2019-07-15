#include <bst.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool isUnivalTree(BiTree root)
{
  bool left_correct = (root->lChild == NULL || (root->data == root->lChild->data && isUnivalTree(root->lChild)));

  bool right_correct = (root->rChild == NULL || (root->data == root->rChild->data && isUnivalTree(root->rChild)));

  return left_correct && right_correct;
}

int main()
{
  int value1[] = {4, 2, 7, 1, 3, 6, 9};
  int value2[] = {1, 1, 1, 1, 1, 1, 1};

  int count = sizeof(value1) / sizeof(int);

  BiTNode root1;
  BiTNode root2;

  for (int i = 0; i < count; i++)
  {
    if (i == 0)
    {
      root1.data = value1[i];
      root1.lChild = NULL;
      root1.rChild = NULL;

      root2.data = value2[i];
      root2.lChild = NULL;
      root2.rChild = NULL;
    }
    else
    {
      Insert(&root1, value1[i]);
      Insert(&root2, value2[i]);
    }
  }

  printf("value1 不是单值二叉树，期待结果为0，实际结果为：%d\n", isUnivalTree(&root1));
  printf("value2 是单值二叉树，期待结果为1，实际结果为：%d\n", isUnivalTree(&root2));

  printf("\n");
  return 0;
}