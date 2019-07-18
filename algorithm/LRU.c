#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct LRUEntryStruct
{
  int key;
  int value;

  struct LRUEntryStruct *hashPrev;
  struct LRUEntryStruct *hashNext;

  struct LRUEntryStruct *linkPrev;
  struct LRUEntryStruct *linkNext;

} LRUEntry;

typedef struct LRUStruct
{
  int capacity;
  LRUEntry **hashMap;

  LRUEntry *linkHead;
  LRUEntry *linkTail;
  int linkSize;

} LRUCache;

LRUCache *lRUCacheCreate(int capacity)
{
  LRUCache *cache = NULL;
  if (NULL == (cache = (LRUCache *)malloc(sizeof(LRUCache))))
  {
    printf("LRU结构，申请内存空间失败\n");

    return NULL;
  }
  memset(cache, 0, sizeof(*cache));
  cache->capacity = capacity;
  cache->hashMap = (LRUEntry **)malloc(sizeof(LRUEntry) * capacity);
  cache->linkSize = 0;

  if (NULL == cache->hashMap)
  {
    free(cache);
    printf("HashTable 申请内存空间失败\n");

    return NULL;
  }

  memset(cache->hashMap, 0, sizeof(LRUEntry *) * capacity);
  cache->linkHead = cache->linkTail = NULL;

  return cache;
}

static unsigned int hashKey(LRUCache *cache, int key)
{
  unsigned int len = key;
  unsigned int b = 1;
  unsigned int a = 2;
  unsigned int hash = 0;
  unsigned int i = 0;
  for (i = 0; i < len; key++, i++)
  {
    hash = hash * a + key;
    a = a * b;
  }
  return key % (cache->capacity);
}

int lRUCacheGet(LRUCache *obj, int key)
{
  int index = hashKey(obj, key);
  LRUEntry *entry = obj->hashMap[index];

  while (entry)
  {
    if (entry->key == key)
    {
      // 根据LRU要求，把该值移动到链表头:
      // step1. 移除解除
      // step2. 在头部插入

      if (obj->linkSize == 0)
      {
        return -1;
      }

      // 实现step1.
      if (entry == obj->linkHead && entry == obj->linkTail)
      {
        // 单节点链表
        obj->linkHead = obj->linkTail = NULL;
      }
      else if (entry == obj->linkHead)
      {
        // 删除的是头节点
        obj->linkHead = entry->linkNext;
        obj->linkHead->linkPrev = NULL;
      }
      else if (entry == obj->linkTail)
      {
        // 删除尾节点
        obj->linkTail = entry->linkPrev;
        obj->linkTail->linkNext = NULL;
      }
      else
      {
        // 中间节点
        entry->linkPrev->linkNext = entry->linkNext;
        entry->linkNext->linkPrev = entry->linkPrev;
      }
      obj->linkSize--;

      // 实现step2. 将节点插入链表头
      if (obj->linkHead == NULL && obj->linkTail == NULL)
      {
        obj->linkHead = obj->linkTail = entry;
      }
      else
      {
        entry->linkNext = obj->linkHead;
        entry->linkPrev = NULL;
        obj->linkHead->linkPrev = entry;
        obj->linkHead = entry;
      }
      obj->linkSize++;

      return entry->value;
    }

    entry = entry->hashNext;
  }

  return -1;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
  /**
   *  step1. 从LRU中找是否存在
   */

  int ret = lRUCacheGet(obj, key);

  LRUEntry *entry;

  if (ret == -1)
  {
    entry = (LRUEntry *)malloc(sizeof(LRUEntry));
    if (NULL == entry)
    {
      printf("缓存节点申请空间失败\n");

      return;
    }

    memset(entry, 0, sizeof(*entry));
    entry->key = key;
    entry->value = value;
    entry->linkNext = entry->linkPrev = entry->hashNext = entry->hashPrev = NULL;

    LRUEntry *removeEntry = NULL;
    obj->linkSize++;

    if (obj->linkSize > obj->capacity)
    {
      // 缓存满了，需要淘汰缓存中最久没有被使用的数据单元
      removeEntry = obj->linkTail;

      // 1. 淘汰双链表数据单元
      // 2. 淘汰hashtable的数据单元

      // step1.
      if (removeEntry == obj->linkHead && removeEntry == obj->linkTail)
      {
        // 单节点链表
        obj->linkHead = obj->linkTail = NULL;
      }
      else if (removeEntry == obj->linkHead)
      {
        // 删除的是头节点
        obj->linkHead = removeEntry->linkNext;
        obj->linkHead->linkPrev = NULL;
      }
      else if (removeEntry == obj->linkTail)
      {
        // 删除尾节点
        obj->linkTail = removeEntry->linkPrev;
        obj->linkTail->linkNext = NULL;
      }
      else
      {
        // 中间节点
        removeEntry->linkPrev->linkNext = removeEntry->linkNext;
        removeEntry->linkNext->linkPrev = removeEntry->linkPrev;
      }
      obj->linkSize--;

      // step2.
      LRUEntry *n = obj->hashMap[hashKey(obj, removeEntry->key)];
      while (n)
      {
        if (n->key == removeEntry->key)
        {
          // 不是哈希链表的头节点
          if (n->hashPrev)
          {
            n->hashPrev->hashNext = n->hashNext;
          }
          else // 如果是哈希链表头节点
          {
            obj->hashMap[hashKey(obj, removeEntry->key)] = n->hashNext;
          }
          // 不是哈希链表为节点
          if (n->hashNext)
          {
            n->hashNext->hashPrev = n->hashPrev;
          }
          break;
        }
        n = n->hashNext;
      }

      free(removeEntry);
      removeEntry = NULL;
    }

    // 将节点插入链表头
    if (obj->linkHead == NULL && obj->linkTail == NULL)
    {
      obj->linkHead = obj->linkTail = entry;
    }
    else
    {
      entry->linkNext = obj->linkHead;
      entry->linkPrev = NULL;
      obj->linkHead->linkPrev = entry;
      obj->linkHead = entry;
    }

    // 将节点插入哈希链表
    LRUEntry *hp = obj->hashMap[hashKey(obj, entry->key)];
    if (hp != NULL)
    {
      entry->hashNext = hp;
      hp->hashPrev = entry;
    }

    obj->hashMap[hashKey(obj, entry->key)] = entry;
  }
  else // 如果已存在
  {
    // 找到entry
    entry = obj->hashMap[hashKey(obj, key)];
    while (entry)
    {
      if (entry->key == key)
      {
        entry->value = value;
        break;
      }
      entry = entry->hashNext;
    }

    // 实现step1.
    if (entry == obj->linkHead && entry == obj->linkTail)
    {
      // 单节点链表
      obj->linkHead = obj->linkTail = NULL;
    }
    else if (entry == obj->linkHead)
    {
      // 删除的是头节点
      obj->linkHead = entry->linkNext;
      obj->linkHead->linkPrev = NULL;
    }
    else if (entry == obj->linkTail)
    {
      // 删除尾节点
      obj->linkTail = entry->linkPrev;
      obj->linkTail->linkNext = NULL;
    }
    else
    {
      // 中间节点
      entry->linkPrev->linkNext = entry->linkNext;
      entry->linkNext->linkPrev = entry->linkPrev;
    }
    obj->linkSize--;

    // 实现step2. 将节点插入链表头
    if (obj->linkHead == NULL && obj->linkTail == NULL)
    {
      obj->linkHead = obj->linkTail = entry;
    }
    else
    {
      entry->linkNext = obj->linkHead;
      entry->linkPrev = NULL;
      obj->linkHead->linkPrev = entry;
      obj->linkHead = entry;
    }
    obj->linkSize++;
  }

  return;
}

void lRUCacheFree(LRUCache *obj)
{
  if (obj->linkSize == 0)
  {
    return;
  }

  LRUEntry *entry = obj->linkHead;
  while (entry)
  {
    LRUEntry *tmp = entry->linkNext;
    free(entry);
    entry = tmp;
  }
  obj->linkSize = 0;
}

void LRUCachePrint(LRUCache *obj)
{
  if (NULL == obj || 0 == obj->linkSize)
  {
    return;
  }
  fprintf(stdout, "\n>>>>>>>>>>>>>>>\n");
  fprintf(stdout, "cache (key data):\n");
  LRUEntry *entry = obj->linkHead;
  while (entry)
  {
    fprintf(stdout, "(%d, %d)", entry->key, entry->value);
    entry = entry->linkNext;
  }
  fprintf(stdout, "\n<<<<<<<<<<<<<<<\n");
}

void LRUCachePrint2(LRUCache *obj)
{
  if (NULL == obj || 0 == obj->linkSize)
  {
    return;
  }
  fprintf(stdout, "\n>>>>>>>>>>>>>>>\n");
  fprintf(stdout, "cache (key data):\n");
  LRUEntry *entry = obj->linkTail;
  while (entry)
  {
    fprintf(stdout, "(%d, %d)", entry->key, entry->value);
    entry = entry->linkPrev;
  }
  fprintf(stdout, "\n<<<<<<<<<<<<<<<\n");
}

int main()
{
  int capacity = 2;

  LRUCache *obj = lRUCacheCreate(capacity);

  int value;

  // leecode-test - 1
  lRUCachePut(obj, 2, 1);
  lRUCachePut(obj, 2, 2);

  value = lRUCacheGet(obj, 2);

  printf("leecode-test期待返回：2，实际返回值：%d\n", value);

  lRUCachePut(obj, 1, 1);
  lRUCachePut(obj, 4, 1);

  value = lRUCacheGet(obj, 2);

  printf("leecode-test期待返回：-1，实际返回值：%d\n", value);

  // leecode-test - 2
  lRUCachePut(obj, 2, 1);
  lRUCachePut(obj, 1, 1);
  lRUCachePut(obj, 2, 3);
  lRUCachePut(obj, 4, 1);

  value = lRUCacheGet(obj, 1);

  printf("leecode-test期待返回：-1，实际返回值：%d\n", value);

  value = lRUCacheGet(obj, 2);

  printf("leecode-test期待返回：3，实际返回值：%d\n", value);

  // 题目

  lRUCachePut(obj, 1, 1);

  lRUCachePut(obj, 2, 2);

  value = lRUCacheGet(obj, 1); // 返回1

  printf("期待返回：1，实际返回值：%d\n", value);

  lRUCachePut(obj, 3, 3); // 该操作会使得密钥 2 作

  value = lRUCacheGet(obj, 2); // 返回 -1(未找到)

  printf("期待返回：-1，实际返回值：%d\n", value);

  lRUCachePut(obj, 4, 4); // 该操作会使得密钥 1 作废

  value = lRUCacheGet(obj, 1); // 返回 -1(未找到)

  printf("期待返回：-1，实际返回值：%d\n", value);

  value = lRUCacheGet(obj, 3); // 返回 3

  printf("期待返回：3，实际返回值：%d\n", value);

  value = lRUCacheGet(obj, 4); // 返回 4

  printf("期待返回：4，实际返回值：%d\n", value);

  return 0;
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/