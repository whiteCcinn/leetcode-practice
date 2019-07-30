#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct HashTableNode
{
  char *pkey;
  int value;
  struct HashTableNode *prior, *next;
} HashNode, *pHashNode;

#define SIZE 1000

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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **subdomainVisits(char **cpdomains, int cpdomainsSize, int *returnSize)
{
  initHashTable();
  char *buff, *p, *pp;
  int count, ret;
  pHashNode pNode;
  for (int i = 0; i < cpdomainsSize; i++)
  {
    buff = cpdomains[i];

    p = strsep(&buff, ' '); // 统计次数
    count = atoi(p);        // 字符串转成int类型
    p = strsep(&buff, ' '); // 最低一级的子域名
    printf("%s\n", p);

    while (p != NULL)
    {
      pNode = get(p);
      if (pNode != NULL) // 已存在
      {
        count += pNode->value;
      }

      ret = set(p, count); // 记录最低一级的子域名
      if (ret != 0)
      {
        printf("%s\n", "Hashtable set error!");
        return NULL;
      }

      pp = strchr(p, '.'); // 找到第一次出现 '.' 字符串（包含）的后续子串
      while (NULL != pp)
      {
        pp = pp + 1; // 去除（包含）字符'.'
        pNode = get(pp);
        if (pNode != NULL) // 已存在
        {
          count += pNode->value;
        }

        set(pp, count); // 记录二级域名

        pp = strchr(pp, '.'); // 找到下一次出现 '.' 字符串（包含）的后续子串
      }

      p = strsep(&buff, ' ');
    }
  }

  char **ouput = (char **)malloc(sizeof(char *) * 100);
  for (int i = 0; i < 100; i++)
  {
    ouput[i] = (char *)malloc(sizeof(char) * 100);
  }

  int j = 0;
  HashNode *pHNode = NULL;
  char *domain;
  char sum[50];
  char **item = (char **)malloc(sizeof(char *) * 3);
  for (int ii = 0; ii < SIZE; ii++)
  {
    pHNode = hashtable[ii];
    if (pHNode != NULL)
    {
      domain = pHNode->pkey;
      sprintf(sum, "%d", pHNode->value);

      item[j] = (char *)malloc(sizeof(char) * 100);
      sprintf(item[j], "%s %s", sum, domain);

      printf("%s\n", item[j]);
      ouput[j] = item[j];
      j += 1;
    }
  }

  returnSize = &j;

  printf("%d\n", *returnSize);

  for (int i = 0; i < *returnSize; i++)
  {
    printf("%s\n", ouput[i]);
  }

  return ouput;
}

int main()
{
  char *p[1] = {"9001 discuss.leetcode.com"};

  int count = sizeof(p) / sizeof(char *);

  int *returnSize = (int *)malloc(sizeof(int));

  char **output;
  output = subdomainVisits(p, count, returnSize);

  for (int i = 0; i < *returnSize; i++)
  {
    printf("%s\n", output[i]);
  }
}