/*************************************************************************
  > File Name: Tree.c
  > Author: HY
  > Mail: 617365925@qq.com
  > Created Time: 2017��01��19�� ������ 09ʱ34��22��
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
   ѭ���������ݣ���������������0���ͽ���ѭ�����������ĸ������򴴽��ڵ㣬�����ݷŵ��ڵ��б��沢���ڵ���������������
   �������һ�ſ�������ô��������ڵ�������ĸ�������Ӹ���ʼ���������������жϣ�

   ����ҵ�ֵ������ڵ��ֵС��������ڵ�����������ǿյģ���ô�ҵı���ֵ�Ľڵ�ͳ�Ϊ����ڵ����������
   ��������������Ϊ��׼���бȽϣ�

   ������ͬ��

   �����Ⱦ��ͷ�����ڵ㣬��Ϊ����������������ֵ��ȵĽڵ�

   ��������ɹ�������ͷź���ǵ�break��
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
	if(root) //�ݹ�һ��Ҫ�й�ĵط��������Ҷ�ӽڵ�����������ٴε������������ʱ��Ϳ��Բ��ô�ӡ�ˣ�ֱ�ӷ���
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

	while(r)  //��Ҫɾ�����Ǹ��ڵ��λ��
	{
		if(r->data == x) //�ҵ�������ȥ
			break;
		else if(r->data > x) //�ҵı����С�����������
		{
			pre = r;
			r = r->lchild;
		}
		else  //�ҵı���Ĵ�
		{
			pre = r;
			r = r->rchild;
		}
	}

	if(r == NULL) //�������˶�û���ҵ�
		return root;

	if(r->lchild == NULL && r->rchild == NULL) //����������Ϊ��
	{
		if(r == root) //Ҫɾ����������Ǹ�
		{
			free(r);
			r = NULL;
			return NULL;
		}
		else
		{
			if(pre->lchild == r) //Ҫɾ���Ľڵ��Ǹ��ڵ��������
			{
				pre->lchild = NULL;
				free(r);
				r = NULL;
			}
			else //Ҫɾ���Ľڵ��Ǹ��ڵ��������
			{
				pre->rchild = NULL;
				free(r);
				r = NULL;
			}
		}
	}
	else if(r->rchild == NULL || r->lchild == NULL) //������������Ϊ��
	{
		if(r == root)//Ҫɾ�����Ǹ�
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
		if(r == pre->lchild) //Ҫɾ���Ľڵ��Ǹ��ڵ��������
		{
			if(r->lchild) //Ҫɾ���ڵ㻹����һ��������
			{
				pre->lchild = r->lchild;
				r->lchild = NULL;
			}
			else //Ҫɾ���ڵ㻹����һ��������
			{
				pre->lchild = r->rchild;
				r->rchild = NULL;
			}
			free(r);
			r = NULL;
		}
		else //Ҫɾ���Ľڵ��Ǹ��ڵ��������
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
	else //������������Ϊ��
	{
		/*
			�ҵ�Ҫɾ���ڵ��������s�����������������һֱ���ұ����ߣ�ֱ��������Ϊ�գ���Ϊ��������������(������������)��ֵ����ӽ���
			��������ֱ��������ֵ���滻Ҫɾ���ڵ��ֵ��Ȼ���s���������ӻ�s�ĸ��ڵ㣬s����ͽӻ���s���Ҿͽӻ���
		*/
		BitNode *p = r;
		BitNode *s = p->lchild;

		while(s->rchild)  //������������������
		{
			p = s;
			s = s->rchild;
		}

		r->data = s->data; //�滻Ҫɾ���ڵ��ֵ

		if(p == r) //Ҫɾ���ڵ��������������������
			p->lchild = s->lchild;
		else //����ִ����whileѭ��һ��
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
