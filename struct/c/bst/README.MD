编译共享动态库

```
gcc -shared -fPIC bst.c -o libbst.so
```

设置动态库环境变量`LD_LIBRARY_PATH`

```
export LD_LIBRARY_PATH=`pwd`
```

编译可执行文件

```
gcc -std=c99 main.c libbst.so -o bst
```

运行主文件

```
./bst
```
