#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#define __AUTHOR__ "caiwenhui"

typedef struct HashTableNode
{
  char *pkey;
  int value;
  struct HashTableNode *prior, *next;
} HashNode, *pHashNode;

#define SIZE 1000

#endif