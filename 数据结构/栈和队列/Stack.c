/*************************************************************************
	> File Name: Stack.c
	> Author: HY
	> Mail: 617365925@qq.com 
	> Created Time: 2017年01月18日 星期三 09时15分03秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define MAX 1024
typedef int ElementType;
typedef struct stack
{
	int top;
	ElementType array[MAX];//
}Stack;

Stack *InitStack()
{
	//static Stack s;
	//s.top = -1;
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->top = -1;
	return s;
}

int StackEmpty(Stack *s)
{
	if(s)
	{
	if(s->top == -1)
		return 1;
	else
		return 0;
	}
	return -1;
}

int StackFull(Stack *s)
{
	if(s)
	{
	if(s->top == MAX-1)
		return 1;
	else
		return 0;
	}
	return -1;
}
int StackLength(Stack *s)
{
	//if(s)
	return s->top+1;
}

void Push(Stack *s,ElementType x)
{
	if(!StackFull(s))
		s->array[++s->top] = x;//其他返回值的情况最好也判断一下
}

ElementType Pop(Stack *s)
{
	if(!StackEmpty(s))
		return s->array[s->top--];
}

/*
 * void Pop(Stack *s,ElementType *e)
 * {
 *	if(!StackEmpty(s))
 *		*e = s->array[s->top];
 *		s->top--;
 * }
 */

ElementType GetTop(Stack *s)
{
	//if(s)
	if(!StackEmpty(s))
		return s->array[s->top];
}
void ClearStack(Stack *s)
{
	//if(s)
	s->to;p = -1;
}

void DestroyStack(Stack *s)
{
	//if(s)
	free(s);
}
int main(int argc,char *argv[])
{
	Stack *s = InitStack();
	ElementType x;
	
	while(1)
	{
		scanf("%d",&x);
		if(x == 0)
			break;
		Push(s,x);
	}
	/*
	while(StackEmpty(s) == 0)
	{
		x = Pop(s);
		printf("%d\t",x);
	}
	*/
	int length = StackLength(s);
	printf("length = %d\n",length);

	x = GetTop(s);
	printf("x = %d\n",x);
	printf("\n");
	return 0;
}
