#include "travelTree.h"

BitNode*
CreateTree()
{
	BitNode *root = NULL;
	BitNode *p = NULL;
	Type x;

	while(1)
	{
		scanf("%d",&x);
		if(x == 0)
			break;

		p = (BitNode *)malloc(sizeof(BitNode));
		p->data = x;
		p->lchild = p->rchild = NULL;

		if(root == NULL)
		{
			root = p;
		}
		else
		{
			BitNode *r = root;
			while(r)
			{
				if(r->data > x)  //�ҵı����С
				{
					if(r->lchild == NULL) //������Ϊ��
					{
						r->lchild = p;
						break;
					}
					else //�ں����������бȽ�
					{
						r = r->lchild;
					}
				}
				else if(r->data < x)
				{
					if(r->rchild == NULL)
					{
						r->rchild = p;
						break;
					}
					else
					{
						r = r->rchild;
					}
				}
				else  //ֵ�Ѿ��������У�����ڵ�����ͷ���
				{
					free(p);
					p = NULL;
					break;
				}
			}
		}
	}
	return root;
}

void mid_order(BitNode *root)
{
	BitNode *r=root;
	if(r == NULL)
		return;
	Stack *s=InitStack();
	while(1)
	{
		while(r != NULL)
		{
			Push(s,r);
			r=r->lchild;
		}
		if(StackEmpty(s))
			break;
		r = Pop(s);
		printf("%d\t",r->data);
		r=r->rchild;
	}
	
	
}

void pre_order(BitNode *root)
{
	BitNode *r=root;
	if(r == NULL)
		return;
	Stack *s=InitStack();
	while(1)
	{
		while(r!=NULL)
		{
			printf("%d\t",r->data);
			Push(s,r);
			r=r->lchild;
		}
		if(StackEmpty(s))
			break;
		r = Pop(s);
		r = r->rchild;
	}
	return;
}

void post_order(BitNode *root)
{
	BitNode *r=root;
	if(r == NULL)
		return;
	Stack *s=InitStack();
	
}

int main(int argc,char *argv[])
{
	BitNode *root =CreateTree();
	mid_order(root);
	printf("\n");
	return 0;
}
