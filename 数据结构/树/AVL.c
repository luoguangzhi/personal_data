/*************************************************************************
	> File Name: AVL.c
	> Author: HY
	> Mail: 617365925@qq.com 
	> Created Time: 2017年01月19日 星期四 14时49分44秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define MAX(a,b) (a)>(b)?(a):(b)
typedef int ElementType; 
typedef struct bitnode
{
	ElementType data;
	struct bitnode *lchild,*rchild;
	int bf;//叶子节点的bf值为1
}BitNode;

int Height(BitNode *r)
{
	if(r)
		return r->bf;
	else
		return 0;
}
BitNode *LL(BitNode *k1)
{
	BitNode *k2 = k1->lchild;
	k1->lchild = k2->rchild;
	k2->rchild = k1;

	k1->bf = MAX(Height(k1->lchild),Height(k1->rchild)) + 1;
	k2->bf = MAX(Height(k2->lchild),Height(k2->rchild)) + 1;

	return k2;
}

BitNode *RR(BitNode *k1)
{
	BitNode *k2 = k1->rchild;
	k1->rchild = k2->lchild;
	k2->lchild = k1;

	k1->bf = MAX(Height(k1->lchild),Height(k1->rchild)) + 1;
	k2->bf = MAX(Height(k2->lchild),Height(k2->rchild)) + 1;

	return k2;
}

BitNode *LR(BitNode *k1)
{
	k1->lchild = RR(k1->lchild);
	return LL(k1);
}

BitNode *RL(BitNode *k1)
{
	k1->rchild = LL(k1->rchild);
	return RR(k1);
}

BitNode *Insert(BitNode *root,ElementType x)
{
	if(root == NULL)
	{
		BitNode *p = (BitNode *)malloc(sizeof(BitNode));
		p->data = x;
		p->lchild = p->rchild = NULL;
		p->bf = 1;
		root = p;
	}
	else
	{
		if(x < root->data)
		{
			root->lchild = Insert(root->lchild,x);
			root->bf = MAX(Height(root->lchild),Height(root->rchild)) + 1;

			if(Height(root->lchild) - Height(root->rchild) > 1)
			{
				if(x < root->lchild->data)
					root = LL(root);
				else
					root = LR(root);
			}
			
		}
		else
		{
			root->rchild = Insert(root->rchild,x);
			root->bf = MAX(Height(root->lchild),Height(root->rchild)) + 1;

			if(Height(root->rchild) - Height(root->lchild) > 1)
			{
				if(x > root->rchild->data)
					root = RR(root);
				else
					root = RL(root);
			}
		}
	}
	return root;
}


void mid_order(BitNode *r)
{
	if(r)
	{
		mid_order(r->lchild);
		printf("%d\t",r->data);
		mid_order(r->rchild);
	}
}
int main(int argc,char *argv[])
{
	ElementType x;
	BitNode *r = NULL;
	while(1)
	{
		scanf("%d",&x);
		if(x == 0)
			break;

		r = Insert(r,x);
	}
	mid_order(r);
	printf("\n");
	return 0;
}
