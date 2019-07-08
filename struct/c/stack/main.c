#include <stdio.h>
#include "link/stack.h"

int main()
{
  //测试创建栈函数
  Stack *stack = CreateStack();
  printf("StackTopElement =  %d \n", GetTopElement(stack));

  //测试入栈函数
  PushStack(stack, 5);
  printf("StackTopElement =  %d \n", GetTopElement(stack));

  PushStack(stack, 6);
  printf("StackTopElement =  %d \n", GetTopElement(stack));

  PushStack(stack, 7);
  printf("StackTopElement =  %d \n", GetTopElement(stack));

  //测试出栈函数
  PopStack(stack);
  printf("StackTopElement =  %d \n", GetTopElement(stack));
  PopStack(stack);
  printf("StackTopElement =  %d \n", GetTopElement(stack));

  //测试清空栈函数
  StackEmpty(stack);
  printf("StackTopElement =  %d \n", GetTopElement(stack));

  //测试撤销栈函数
  DestoryStack(stack);

  return 0;
}
