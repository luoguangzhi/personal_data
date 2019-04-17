/*************************************************************************
  > File Name: Tree.c
  > Author: HY
  > Mail: 617365925@qq.com
  > Created Time: 2017年01月19日 星期四 09时34分22秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;
typedef struct bitnode
{
	ElementType data;
	struct bitnode *lchild;
	struct bitnode *rchild;
}BitNode;
/*
   循环输入数据，如果输入的数据是0，就结束循环，返回树的根，否则创建节点，将数据放到节点中保存并将节点插入二叉排序树，
   如果树是一颗空树，那么来的这个节点就是树的根，否则从根开始遍历并进行如下判断：

   如果我的值比这个节点的值小，而这个节点的左子树又是空的，那么我的保存值的节点就成为这个节点的左子树；
   否则再以左子树为标准进行比较；

   大的情况同理；

   如果相等就释放这个节点，因为二叉排序树不存在值相等的节点

   以上如果成功插入和释放后请记得break；
   */

	BitNode*
CreateTree()
{
	BitNode *root = NULL;
	BitNode *p = NULL;
	ElementType x;

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
	if(root) //递归一定要有归的地方，如果是叶子节点的左右子树再次调用这个函数的时候就可以不用打印了，直接返回
	{
		mid_order(root->lchild);
		printf("%d\t",root->data);
		mid_order(root->rchild);
	}
}

void pre_order(BitNode *root)
{

}

void post_order(BitNode *root)
{

}
BitNode *Delete_x(BitNode *root,ElementType x)
{
	BitNode *r = root;
	BitNode *pre = NULL;

	while(r)  //找要删除的那个节点的位置
	{
		if(r->data == x) //找到了跳出去
			break;
		else if(r->data > x) //我的比你的小，遍历你的左
		{
			pre = r;
			r = r->lchild;
		}
		else  //我的比你的大
		{
			pre = r;
			r = r->rchild;
		}
	}

	if(r == NULL) //遍历完了都没有找到
		return root;

	if(r->lchild == NULL && r->rchild == NULL) //左右子树均为空
	{
		if(r == root) //要删除的这个就是根
		{
			free(r);
			r = NULL;
			return NULL;
		}
		else
		{
			if(pre->lchild == r) //要删除的节点是父节点的左子树
			{
				pre->lchild = NULL;
				free(r);
				r = NULL;
			}
			else //要删除的节点是父节点的右子树
			{
				pre->rchild = NULL;
				free(r);
				r = NULL;
			}
		}
	}
	else if(r->rchild == NULL || r->lchild == NULL) //左右子树均不为空
	{
		if(r == root)//要删除的是根
		{
			if(r->lchild)
			{
				root = r->lchild;
				r->lchild = NULL;
			}
			else
			{
				root = r->rchild;
				r->rchild = NULL;
			}
			free(r);
			return root;
		}
		if(r == pre->lchild) //要删除的节点是父节点的左子树
		{
			if(r->lchild) //要删除节点还存在一个左子树
			{
				pre->lchild = r->lchild;
				r->lchild = NULL;
			}
			else //要删除节点还存在一个右子树
			{
				pre->lchild = r->rchild;
				r->rchild = NULL;
			}
			free(r);
			r = NULL;
		}
		else //要删除的节点是父节点的右子树
		{
			if(r->lchild)
			{
				pre->rchild = r->lchild;
				r->lchild = NULL;
			}
			else
			{
				pre->rchild = r->rchild;
				r->rchild = NULL;
			}
			free(r);
			r = NULL;
		}
	}
	else //左右子树均不为空
	{
		/*
			找到要删除节点的左子树s，如果存在右子树，一直往右边右走，直到右子树为空，因为左子树的右子树(的右子树……)的值是最接近于
			根的数，直接用他的值来替换要删除节点的值，然后把s的左子树接回s的父节点，s是左就接回左，s是右就接回右
		*/
		BitNode *p = r;
		BitNode *s = p->lchild;

		while(s->rchild)  //找左子树的最右子树
		{
			p = s;
			s = s->rchild;
		}

		r->data = s->data; //替换要删除节点的值

		if(p == r) //要删除节点的左子树不存在右子树
			p->lchild = s->lchild;
		else //至少执行了while循环一次
			p->rchild = s->lchild;

		s->lchild = NULL;
		free(s);
		s = NULL;
	}
	return root;
}
int main(int argc,char *argv[])
{
	BitNode *root =CreateTree();
	mid_order(root);
	printf("\n");
	ElementType x;
	scanf("%d",&x);

	root = Delete_x(root,x);
	mid_order(root);
	printf("\n");
	return 0;
}
