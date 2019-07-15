#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

BiTree Insert(BiTree T, int x)
{
  if (T == NULL)
  {
    BiTree bst = (BiTree)malloc(sizeof(BiTree));
    bst->data = x;
    bst->lChild = NULL;
    bst->rChild = NULL;

    T = bst;
  }

  if (T->data > x)
  {
    T->lChild = Insert(T->lChild, x);
  }

  if (T->data < x)
  {
    T->rChild = Insert(T->rChild, x);
  }

  return T;
}

//中序遍历二叉查找树
//打印的应该是一个递增的序列
void MiddleOrder(BiTree T)
{
  if (T == NULL)
  {
    return;
  }
  else
  {

    MiddleOrder(T->lChild);
    printf("%d ", T->data);
    MiddleOrder(T->rChild);
  }
}

//先序遍历二叉查找树
//因为先序遍历+中序遍历 可以唯一确定一棵树，等下可以验证树是否正确
void PreOrder(BiTree T)
{

  if (T == NULL)
  {
    return;
  }
  else
  {

    printf("%d ", T->data);
    PreOrder(T->lChild);
    PreOrder(T->rChild);
  }
}