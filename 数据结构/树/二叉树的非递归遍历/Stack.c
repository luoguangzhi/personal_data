#include "Stack.h"

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

void Push(Stack *s,BitNode* x)
{
	if(!StackFull(s))
		s->array[++s->top] = x;//其他返回值的情况最好也判断一下
}

BitNode* Pop(Stack *s)
{
	if(!StackEmpty(s))
		return s->array[s->top--];
}

/*
 * void Pop(Stack *s,BitNode* *e)
 * {
 *	if(!StackEmpty(s))
 *		*e = s->array[s->top];
 *		s->top--;
 * }
 */

BitNode* GetTop(Stack *s)
{
	//if(s)
	if(!StackEmpty(s))
		return s->array[s->top];
}
void ClearStack(Stack *s)
{
	//if(s)
	s->top = -1;
}

void DestroyStack(Stack *s)
{
	//if(s)
	free(s);
}
