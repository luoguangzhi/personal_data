/*************************************************************************
	> File Name: LinkList.c
	> Author: HY
	> Mail: 617365925@qq.com 
	> Created Time: 2017年01月16日 星期一 09时51分52秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>

typedef int ElementType;//如果结构体的数据域更改类型，只需要更改这一句就可以了
typedef struct node
{
	ElementType data;//数据域
	struct node *next;//指针域
}Node; //将结构体类型名取别名为Node


/*
	循环从键盘输入数据，如果输入的数字是0，则结束循环，返回链表的头；
	否则创建节点，保存数据，然后将节点加入链表
	加入链表时请注意：如果链表为空，那么来的这个节点就是这个链表的头和尾，
	否则可采用头插法或是尾插法将节点加入链表
*/
Node *
CreateList()
{
	//创建一个空链表，每一次指向新建节点的指针P由于没有申请节点，所以让他等于NULL
	Node *head,*tail,*p;
	head = tail = p = NULL;
	ElementType x;

	while(1)
	{
		scanf("%d",&x);
		if(x == 0)
			break;

		p = (Node *)malloc(sizeof(Node));   //申请节点
		p->data = x; //保存数据
		p->next = NULL;

		/*加入链表*/
		if(head == NULL)  //链表为空
		{
			head = tail = p;
		}
		else
		{
#if 0   //头插法
			p->next = head;
			head = p;
#elif 0   //尾插法
			tail->next = p;
			tail = p;
#else  //创建一个有序链表
		/*
			在整个链表中查找插入位置(第一个比我大的数)，保留这个位置和前一个位置。
			然后根据这个位置去判断到底应该插入头，插入中间，还是插入尾巴
		*/
			Node *r = head;
			Node *pre = NULL;//pre始终指向查找位置的前一个位置，head没有前一个，所以初始值给NULL
			
			while(r)
			{
				if(r->data > p->data)//找到了插入位置
				{
					break;
				}
				else  //接着往下寻找
				{
					pre = r;
					r = r->next;
				}
			}
			
			/*
				如果循环遍历完了都没有找到一个比我大的，那么采用尾插法；
				如果一进来值就比我的大，采用头插法；
				否则采用插入中间的方式
			*/
			if(r == NULL) //遍历完了都没有找到
			{
				tail->next = p;
				tail = p;
			}
			else if(r == head) //pre == NULL  //循环只执行了一次
			{
				p->next = head;   p->next = r;
				head = p;
			}
			else  // 循环中途跳出来的
			{
				pre->next = p;
				p->next = r;
			}
#endif		
		}
	}
	return head;  //返回链表的头；
}

void
PrintList(Node *list)
{
	while(list) // 注意：根据分析，此时填入的是list，而不能是list->next,否则最后一个节点将打印不到
	{
		printf("%d\t",list->data);
		list = list->next;
	}
	printf("\n");
}

/*在链表list中查找值为num的节点，找到了返回1，没找到返回0*/
int 
find_num(Node *list,ElementType num)
{
	while(list)
	{
		if(list->data == num)
			return 1;
		list = list->next;
	}
	return 0;
}
/*在链表list中查找第n个节点，找到了返回这个节点的值，没有找到返回0*/
ElementType 
find_No(Node *list,int n)
{
	int count = 0;
	while(list)
	{
		if((++count) == n)
			return list->data;
		list = list->next;
	}
	return 0;
}

//在链表list中删除值为num的第一个节点，没有这个链表中没有值为num的节点，则返回原链表
Node *
Delete_num(Node *list, ElementType num)
{
	Node *r = list;
	Node *pre = NULL;
	
	while(r) //遍历整个链表，找值为num的节点
	{
		if(r->data == num)
		{
			break;
		}
		else
		{
			pre = r;
			r = r->next;
		}
	}
	
	if(r == NULL)  //没找到，返回原链表
		return list;

	if(r == list)  //要删除的是第一个节点
	{
		list = list->next;
		r->next = NULL;
		free(r);
		r = NULL;
	}
	else  //删除的是中间和尾巴
	{
		pre->next = r->next;
		r->next = NULL;
		free(r);
		r = NULL;
	}
	return list;
}
//在链表list中删除所有值为num的节点，没有这个链表中没有值为num的节点，则返回原链表
Node *
Delete_all(Node *list, ElementType num)
{
	Node *r = list;
	Node *pre = NULL;
	
	while(r)
	{
		if(r->data == num)
		{
			if(r == list)
			{
				list = list->next;
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
	}
	return list;
}
int 
main(int argc,char *argv[])
{
	Node *list = CreateList();
	PrintList(list);
	//int x;
	//scanf("%d",&x);
	/*
	int result = find_num(list,x);
	printf("%s\n",result?"YES":"No");
	*/

	ElementType result;
	/*
	result = find_No(list,x);
	if(result)
		printf("%d\n",result);
	else
		printf("No find\n");
	*/

	scanf("%d",&result);
	list = Delete_all(list,result);
	PrintList(list);
	return 0;
}
