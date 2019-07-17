#include "hashtable.c"

int main()
{
  initHashTable();
  char *keys[] = {"caiwenhui", "caiwenhu", "caiwenhui", "caiwenhui1"};
  int values[] = {25, 26, 24, 27};

  int count = sizeof(values) / sizeof(int);

  int ret = 1;
  int pos = 0;
  for (int i = 0; i < count; i++)
  {
    ret = set(keys[i], values[i]);
    printf("ret = %d\n", ret);
    if (!ret)
    {
      pos = hash(keys[i]) % SIZE;
      printf("main:  pos = %d\n", pos);
      print_hash_node(pos);
      pHashNode pHN = get(keys[i]);

      if (NULL != pHN)
      {
        printf("Got it: key:%s, value: %d\n", pHN->pkey, pHN->value);
      }
    }
  }

  pHashNode pHN2 = delete ("caiwenhui");
  if (pHN2 == NULL)
  {
    printf("找不到对应的key，删除失败\n");
  }
  else
  {
    printf("删除key=%s,value=%d\n", pHN2->pkey, pHN2->value);
  }

  set("caiwenhui", 18);
  pos = hash("caiwenhui") % SIZE;
  print_hash_node(pos);

  return 0;
}