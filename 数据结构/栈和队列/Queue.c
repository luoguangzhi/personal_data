/*************************************************************************
	> File Name: Queue.c
	> Author: HY
	> Mail: 617365925@qq.com 
	> Created Time: 2017年01月18日 星期三 11时16分55秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;
typedef struct node
{
	ElementType data;
	struct node *next;
}Node;

typedef struct queue
{
	Node* first;
	Node* last;
	int count;
}Queue;//头节点

Queue * InitQueue()
{
	Queue *q =(Queue *)(malloc(sizeof(Queue)));
	q->first = q->last = NULL;
	q->count = 0;

	return q;
}

void EnQueue(Queue *q, ElementType x)
{
	//if(q)
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

Node *DeQueue(Queue *q)
{
	//if(q)
	if(q->first != NULL)
	{
		Node *p = q->first;
		q->first = q->first->next;
		p->next = NULL;
		q->count--;
		return p;
	}

	//return NULL;
}
void ClearQueue(Queue *q)
{
	if(q)
	{
		Node *p = NULL;
		while(q->first != NULL)
		{
			p = q->first;
			q->first = p->next;
			p->next = NULL;
			free(p);
		}
		p = NULL;
		q->last = NULL;
		q->count = 0;
	}
}
void DestroyQueue(Queue *q)
{
	if(q)
	{
		Node *p = NULL;
		while(q->first != NULL)
		{
			p = q->first;
			q->first = p->next;
			p->next = NULL;
			free(p);
		}
		free(q);
		q = p = NULL;
	}
}
int main(int argc,char *argv[])
{
	Queue *q = InitQueue();

	ElementType x;
	while(1)
	{
		scanf("%d",&x);
		if(x == 0)
			break;
		EnQueue(q,x);
	}

	Node *p = NULL;
	while(q->count != 0)
	{
		p = DeQueue(q);
		printf("%d\t",p->data);
	}
	printf("\n");
	return 0;
}
