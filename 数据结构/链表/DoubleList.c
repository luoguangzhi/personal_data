/*************************************************************************
	> File Name: DoubleList.c
	> Author: HY
	> Mail: 617365925@qq.com 
	> Created Time: 2017年01月17日 星期二 14时00分26秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;
typedef struct node
{
	ElementType data;
	struct node* prev;
	struct node* next;
}Node;
Node *CreateList()
{
	Node *head,*tail,*p;
	head = tail = p = NULL;
	ElementType x;
	while(1)
	{
		scanf("%d",&x);
		if(x == 0)
			break;

		p = (Node *)malloc(sizeof(Node));
		p->data = x;
		p->prev = p->next = NULL;

		if(head == NULL)
		{
			head = tail = p;
		}
		else
		{
			Node *r = head;

			while(r)
			{
				if(r->data > x)
					break;
				r = r->next;
			}
			if(r == head)
			{
				head->prev = p;
				p->next = head;
				head = p;
			}
			else if(r == NULL)
			{
				tail->next = p;
				p->prev = tail;
				tail = p;
			}
			else
			{
				r->prev->next = p;
				p->next = r;
				p->prev = r->prev;
				r->prev = p;
			}

		}

	}
	return head;

}
Node *find_last(Node *list)
{
	while(list->next)
	{
		list = list->next;
	}
	return list;
}
Node *Delete_all_x(Node *list,ElementType x)
{
	Node *r = list;
	Node *tail = find_last(list);
	while(r)
	{
		if(r->data == x)
		{
			if(r == list)
			{
				while(r->data == x && r->next != NULL)
				{
					list = list->next;
					r->next = list->prev = NULL;
					free(r);
					r = list;
				}
				if(r->data == x && r->next == NULL)
				{
					free(r);
					r = NULL;
					return NULL;
				}
			}
			else if(r == tail)
			{
				r->prev->next = NULL;
				r->prev = NULL;
				free(r);
				r = NULL;
			}
			else
			{
				Node *p = r->next;
				r->prev->next = r->next;
				r->next->prev = r->prev;
				r->prev = r->next = NULL;
				free(r);
				r = p;
			}
		}
		else
		{
			r = r->next;
		}
	}

	return list;
}
void PrintList(Node *list)
{
	while(list)
	{
		printf("%d\t",list->data);
		list = list->next;
	}
	printf("\n");
}


int main(int argc,char *argv[])
{
	Node *list = CreateList();
	PrintList(list);

	ElementType x;
	scanf("%d",&x);
	list = Delete_all_x(list,x);
	PrintList(list);
	return 0;
}
