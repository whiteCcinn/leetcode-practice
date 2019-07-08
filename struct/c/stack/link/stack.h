#ifndef  __STACK_H__
#define  __STACK_H__
 
typedef int DataType;
typedef struct node{
    DataType data;
    struct node * next;
}Stack;
 
Stack* CreateStack();            // 创建栈
void StackEmpty(Stack* );        // 清空栈
void DestoryStack(Stack*);       // 撤销(删除)栈
int IsEmpty(Stack*);             // 判空
int PushStack(Stack*, DataType); // 入栈
int PopStack(Stack*);            // 出栈
DataType GetTopElement(Stack*);  // 取栈顶元素
 
 
#endif