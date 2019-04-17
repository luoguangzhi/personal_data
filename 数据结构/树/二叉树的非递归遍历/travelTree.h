#ifndef _TRAVELTREE_H_
#define _TRAVELTREE_H_

#include<stdio.h>
#include<stdlib.h>



typedef int Type;
typedef struct bitnode
{
	Type data;
	struct bitnode *lchild;
	struct bitnode *rchild;
}BitNode;

#include "Stack.h"

BitNode* CreateTree();
void mid_order(BitNode *root);
void pre_order(BitNode *root);
void post_order(BitNode *root);

#endif