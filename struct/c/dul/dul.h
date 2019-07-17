#ifndef __DUL_H__
#define __DUL_H__

#define __AUTHOR__ "caiwenhui"

typedef int ElemType;

typedef struct DuLNode
{
  ElemType data;
  struct DuLNode *prior, *next;
} DuLNode, *DuLinkList;

#endif