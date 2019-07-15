#include <bst.h>
#include <stdlib.h>
#include <stdio.h>

BiTree invertTree(BiTree root)
{

  BiTree tmpNode;

  if (root)
  {
    tmpNode = invertTree(root->lChild);
    root->lChild = invertTree(root->rChild);
    root->rChild = tmpNode;
  }

  return root;
}

int main()
{
  // 构建二叉搜索树（这里也可以构建随便一颗无序树也可以）

  int value[] = {4, 2, 7, 1, 3, 6, 9};

  int count = sizeof(value) / sizeof(int);

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

  printf("原始顺序：\n");
  PreOrder(&root);

  // 开始翻转树
  invertTree(&root);

  printf("\n反转后顺序：\n");
  PreOrder(&root);

  printf("\n");
  return 0;
}