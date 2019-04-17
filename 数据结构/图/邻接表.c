/*************************************************************************
	> File Name: 邻接表.c
	> Author: luoguangzhi
	> Mail: 676638449@qq.com 
	> Created Time: 2017年02月07日 星期二 20时48分10秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 1024
typedef int Adjtype
typedef char Vtype

typedef struct v_node
{
	int num;
	Vtype v;
	Adjtype A;
	Adj_v *next;
}V_Node;

typedef struct graph
{
	V_Node *a[max];
	int Vexnum;  //顶点个数
	int Adjnum;  //边的个数
}Graph;

void Creatgraph()
{
	Graph *g=(Graph*)malloc(sizeof(Graph));
}
int main(int argc,char *argv[])
{
	return 0;
}

