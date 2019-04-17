/*************************************************************************
  > File Name: CircleList.c
  > Author: HY
  > Mail: 617365925@qq.com 
  > Created Time: 2017年01月17日 星期二 08时59分55秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;
typedef struct node
{
	ElementType data;
	struct node *next;
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

		p = (Node *)malloc(sizeof(*p));//申请节点并将数据保存
		p->data = x;
		p->next = NULL;

		if(head == NULL) //链表为空
		{
			head = tail = p;
			tail->next = head;
		}
		else
		{
#if 0 // 头插法
			p->next = head;
			head = p;
			tail->next = head;
#elif 0  //尾插法
			tail->next = p;
			tail = p;
			tail->next = head;
#else  //创建有序链表
			Node *r = head;
			Node *pre = tail; //头的前驱节点是尾

			//循环遍历找插入位置
			do
			{
				if(r->data > x)
					break;
				pre = r;
				r = r->next;
			}while(r != head);
			/*结束while循环有两种情况，第一种是r == head,第二种是r != head (遍历了整个链表或是第一次进来值就比链表的第一个节点的小)*/
			if(r != head)   //插入中间
			{
				pre->next = p;
				p->next = r;
			}
			else
			{
				/*
				 * 此时不能仅仅根据r 和 head 的值去判断到底应该采用头插法，尾插法，
				 * 但是我们可以根据x的值和头指针指向的节点的值的大小关系去判断
				 */
				if(x > r->data) //遍历了整个链表
				{
					tail->next = p;
					tail = p;
					tail->next = head;
				} 
				else //第一次进入就退出了
				{
					p->next = head;
					head = p;
					tail->next = head;
				}
			}

#endif
		}
	}
	return head;
}

void PrintList(Node *list)
{
	Node *r = list;
	if(list) //解决第一次进来为空的情况
	{
		do
		{
			printf("%d\t",list->data);
			list = list->next;
		}while(list != r ); 
		//根据实际情况分析此时只能采用do……while循环，且条件为 list != r, 要不就是最后一个打印不出或者是不能进入循环
	}
	printf("\n");

}
Node *find_last(Node *list) //查找链表的最后一个节点
{
	Node *r = list;
	do
	{	
		r = r->next;
	}while(r->next != list);
	return r;
}
/*
	循环遍历整个链表，找到值为x的节点，找到一个删除一个，否则往下寻找，直到遍历完整个链表为止。
	删除的时候请分为头，尾，中间，分别讨论
	
	注意：只剩下一个节点的时候请注意他的删除！！！此时容易出现段错误
	要想避免请创建一个带空节点(没有有用数据)的链表
	即创建时就让head 和 tail 指向这个节点，这个节点的数据可以是约定的结束符
	
	此函数只试用于循环有序链表的删除
*/
Node *Delete_all_x(Node *list,ElementType x)
{
	Node *r = list;
	Node *tail = find_last(list);
	Node *pre = tail;

	do
	{
		if(r->data == x)
		{
			if(r == list)
			{
				while(r->data == x && r->next != list)
				{
					list = list->next;
					pre->next = r->next;
					r->next = NULL;
					free(r);
					r = list;
				}
				if(r->data == x && r->next == list)
				{
					free(r);
					r = NULL;
					return NULL;
				}
			}
			else if(r == tail)
			{
				pre->next = list;
				r->next = NULL;
				free(r);
				r = list;
			}
			else
			{
				pre->next = r->next;
				r->next = NULL;
				free(r);
				r = pre->next;
			}
		}
		else
		{
			pre = r;
			r = r->next;
		}
	}while(r != list);

	return list;
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
