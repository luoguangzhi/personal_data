#ifndef QUEUE_H
#define QUEUE_H
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

Queue * InitQueue();
void EnQueue(Queue *q, ElementType x);
Node *DeQueue(Queue *q);

#endif