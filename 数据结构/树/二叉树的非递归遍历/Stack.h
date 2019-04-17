#ifndef _STACK_H_
#define _STACK_H_

#include<stdio.h>
#include<stdlib.h>
#include "travelTree.h"
#define MAX 1024
//typedef BitNode* BitNode*;


typedef struct stack
{
	int top;
	BitNode* array[MAX];
}Stack;

Stack *InitStack();
int StackEmpty(Stack *s);
int StackFull(Stack *s);
int StackLength(Stack *s);
void Push(Stack *s,BitNode* x);
BitNode* Pop(Stack *s);
BitNode* GetTop(Stack *s);
void ClearStack(Stack *s);
void DestroyStack(Stack *s);

#endif
