## 哈希表

```
gcc -shared -fPIC hashtable.c -o libhashtable.so && gcc -std=c99 main.c libhashtable.so -o main && ./main
```

## 结果

```
hash表当前位置没有元素，可以直接插入
ret = 0
main:  pos = 539
Position:539, key:caiwenhui, value:25
Got it: key:caiwenhui, value: 25
hash表当前位置没有元素，可以直接插入
ret = 0
main:  pos = 717
Position:717, key:caiwenhu, value:26
Got it: key:caiwenhu, value: 26
hash表当前有元素
hash表找到了对应的key：caiwenhui，重新赋值
ret = 0
main:  pos = 539
Position:539, key:caiwenhui, value:24
Got it: key:caiwenhui, value: 24
hash表当前位置没有元素，可以直接插入
ret = 0
main:  pos = 127
Position:127, key:caiwenhui1, value:27
Got it: key:caiwenhui1, value: 27
删除key=caiwenhui,value=24
hash表当前位置没有元素，可以直接插入
Position:539, key:caiwenhui, value:18
```
