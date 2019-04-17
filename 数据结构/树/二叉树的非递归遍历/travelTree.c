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
				if(r->data > x)  //我的比你的小
				{
					if(r->lchild == NULL) //左子树为空
					{
						r->lchild = p;
						break;
					}
					else //在和左子树进行比较
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
				else  //值已经存在树中，这个节点可以释放了
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
