#include "dul.h"
#include <stdlib.h>

void InitList(DuLinkList L)
{ /* 产生空的双向循环链表L */
  L = (DuLinkList)malloc(sizeof(DuLNode));
  if (L)
    L->next = L->prior = L;
  else
    printf("初始化链表失败\n");
}

void DestroyList(DuLinkList L)
{
  DuLinkList q, p = L->next; /* p指向第一个结点 */
  while (p != L)             /* p没到表头 */
  {
    q = p->next;
    free(p);
    p = q;
  }
  free(L);
  L = NULL;
}

int ListLength(DuLinkList L)
{ /* 初始条件：L已存在。操作结果： */
  int i = 0;
  DuLinkList p = L->next; /* p指向第一个结点 */
  while (p != L)          /* p没到表头 */
  {
    i++;
    p = p->next;
  }

  return i;
}
