#ifndef __BST_H__
#define __BST_H__

#define __AUTHOR__ "caiwenhui"

typedef int elementType;

typedef struct BTNode
{

  elementType data;
  struct BTNode *lChild;
  struct BTNode *rChild;
} BiTNode, *BiTree;

BiTree Insert(BiTree T, int x);
void MiddleOrder(BiTree T);
void PreOrder(BiTree T);
#endif
