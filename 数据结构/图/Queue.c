/*************************************************************************
	> File Name: Queue.c
	> Author: HY
	> Mail: 617365925@qq.com 
	> Created Time: 2017年01月18日 星期三 11时16分55秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue * InitQueue()
{
	Queue *q =(Queue *)(malloc(sizeof(Queue)));
	q->first = q->last = NULL;
	q->count = 0;

	return q;
}

void EnQueue(Queue *q, ElementType x)
{
	if(q)
	{
		Node *p = (Node *)malloc(sizeof(Node));
		p->data = x;
		p->next = NULL;

		if(q->first == NULL)
		{
			q->first = q->last = p;
		}
		else
		{
			q->last->next = p;
			q->last = p;
		}
		q->count++;
	}
}

Node *DeQueue(Queue *q)
{
	if(q)
	{
		if(q->first != NULL)
		{
			Node *p = q->first;
			q->first = q->first->next;
			p->next = NULL;
			q->count--;
			return p;
		}
	}
	return NULL;
}

