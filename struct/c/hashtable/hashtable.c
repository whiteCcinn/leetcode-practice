#include "hashtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

pHashNode hashtable[SIZE];
int actualSize = 0;

void initHashTable()
{
  memset(hashtable, 0, sizeof(pHashNode) * SIZE);
}

int hash(char *key)
{
  unsigned int len = strlen(key);
  unsigned int b = 1;
  unsigned int a = 2;
  unsigned int hash = 0;
  unsigned int i = 0;
  for (i = 0; i < len; key++, i++)
  {
    hash = hash * a + (unsigned int)(*key);
    a = a * b;
  }

  return hash;
}

int set(char *key, int value)
{
  HashNode *pHarshNodeHead = NULL;
  HashNode *pNewNode = NULL;
  int pos = 0;

  if ((actualSize >= SIZE) || (NULL == key))
  {
    return -1;
  }

  pos = hash(key) % SIZE; //用这种方法计算key在哈希数组中对应的位置

  pHarshNodeHead = hashtable[pos];

  if (NULL == pHarshNodeHead)
  {
    printf("hash表当前位置没有元素，可以直接插入\n");
  }
  else
  {
    printf("hash表当前有元素\n");
  }

  while (pHarshNodeHead) // 如果这个位置对应的不是这一串中最后一个节点的话，那就要向后移动了
  {
    if (strcmp(pHarshNodeHead->pkey, key) == 0) //如果这个键值对已经存在，只更新键值即可
    {
      printf("hash表找到了对应的key：%s，重新赋值\n", key);

      pHarshNodeHead->value = value;

      return 0;
    }

    if (pHarshNodeHead->next == NULL)
    {
      break;
    }

    pHarshNodeHead = pHarshNodeHead->next; //向后移动,肯定会有NULL的时候
  }

  pNewNode = (HashNode *)malloc(sizeof(HashNode)); //申请一块HarshNode 大小的内存
  if (NULL == pNewNode)
  {
    return -1;
  }

  memset(pNewNode, 0, sizeof(HashNode));

  pNewNode->pkey = (char *)malloc(strlen(key) + 1); //申请一块key大小的内存

  if (NULL == pNewNode->pkey)
  {
    return -1;
  }

  memset(pNewNode->pkey, 0, strlen(key) + 1);

  strcpy(pNewNode->pkey, key); //将key的内容赋给 pNewNode -> key
  pNewNode->value = value;     //键值也复制过来

  pNewNode->next = NULL;            //由于是新节点，也是尾节点，所以pNext指向NULL
  pNewNode->prior = pHarshNodeHead; //由于是新节点，也是尾节点，所以pNext指向NULL

  pHarshNodeHead = pNewNode;

  hashtable[pos] = pHarshNodeHead; //最后一定要让数组中的这个位置指向这个头指针

  actualSize++;

  return 0;
}

//打印数组中对应的某个位置的那一串哈希值
void print_hash_node(int pos)
{
  HashNode *pHarshNodeHead = NULL;

  if (pos >= SIZE)
    return;

  pHarshNodeHead = hashtable[pos];

  if (NULL == pHarshNodeHead)
    printf("NULL == pHarshNodeHead\n");
  while (NULL != pHarshNodeHead)
  {
    printf("Position:%d, key:%s, value:%d \n", pos, pHarshNodeHead->pkey, pHarshNodeHead->value);
    pHarshNodeHead = pHarshNodeHead->next;
  }
}

// 根据键值key来查找对应的哈希节点
HashNode *get(char *key)
{
  int pos = 0;
  HashNode *pHarshHead = NULL;

  if (NULL == key)
  {
    return NULL;
  }

  pos = hash(key) % SIZE; //计算出在哈希数组中的位置

  pHarshHead = hashtable[pos];

  while (NULL != pHarshHead)
  {
    if (strcmp(key, pHarshHead->pkey) == 0) //找到了
      return pHarshHead;

    pHarshHead = pHarshHead->next; // 没有找到的话来到下一个节点
  }

  return NULL;
}

// 根据键值key来查找对应的哈希节点
HashNode *delete (char *key)
{
  int pos = 0;
  HashNode *pHarshHead = NULL;

  if (NULL == key)
  {
    return NULL;
  }

  pos = hash(key) % SIZE; //计算出在哈希数组中的位置

  pHarshHead = hashtable[pos];

  while (NULL != pHarshHead)
  {
    if (strcmp(key, pHarshHead->pkey) == 0)
    {
      if (pHarshHead->next != NULL && pHarshHead->prior != NULL)
      {
        pHarshHead->next->prior = pHarshHead->prior;
        pHarshHead->prior->next = pHarshHead->next;
      }

      actualSize--;
      hashtable[pos] = NULL;

      return pHarshHead;
    }

    pHarshHead = pHarshHead->next; // 没有找到的话来到下一个节点
  }

  return NULL;
}