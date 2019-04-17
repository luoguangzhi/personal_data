/*************************************************************************
  > File Name: graph.c
  > Author: HY
  > Mail: 617365925@qq.com 
  > Created Time: 2017年01月20日 星期五 08时58分22秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include "queue.h"
#define MAX 1024
#define VERYBIG 65535
typedef char Vtype;//顶点的数据类型
typedef int Adjtype;//领结矩阵的类型，其值就是边的权值的类型
typedef struct 
{
	Vtype V[MAX];//顶点的集合
	Adjtype A[MAX][MAX];//边的集合，二维数组表示
	int Vexnum;//顶点的个数
	int Adjnum;//边的个数
}Graph;

//在顶点集合中找有没有值为ch的顶点，以便确定在二维数组A中权值w的位置
int my_index(char v[],int num,char ch)
{
	int i;
	for(i = 0;i < num;i++)
	{
		if(v[i] == ch)
			return i;
	}
	return -1;
}

Graph * CreateGraph()
{
	Graph *g = (Graph *)malloc(sizeof(Graph));//申请一张空图
	g->Adjnum = 0;

	gets(g->V);//获取顶点的名字
	g->Vexnum = strlen(g->V); //顶点的个数

	int i,j; //为了填写无穷大方便，此时将所有元素都置为无穷大，如果两个顶点间可达，则再修改数据会比较方便
	for(i = 0;i < g->Vexnum;i++)
	{
		for(j = 0;j < g->Vexnum;j++)
		{
			g->A[i][j] = VERYBIG;
		}
	}

	char from,to;
	int w;

	while(1) //循环输入起点，终点和两点间的权值，约定以'#'作为结束
	{
		scanf("%c%c%d",&from,&to,&w);
		getchar();//接受上一次遗留下来的回车符
		if(from == '#')
			break;
		i = my_index(g->V,g->Vexnum,from);
		j = my_index(g->V,g->Vexnum,to);  //确定w所在的位置

		if(i != -1 && j != -1)//你输入的是有效数据
		{
			g->A[i][j] = w;
			g->Adjnum++; //边的个数增一
		}
	}
	return g;
}
void print_graph(Graph *g)
{
	int i,j;
	for(i = 0;i < g->Vexnum;i++) // 打印顶点的名字
	{
		printf("%c\t",g->V[i]);
	}
	printf("\n");

	for(i = 0;i < g->Vexnum;i++) //打印的边的信息
	{
		for(j = 0;j < g->Vexnum;j++)
		{
			if(g->A[i][j] == VERYBIG)
				printf("%c\t",052); //如果是无穷大，打印星号
			else
				printf("%d\t",g->A[i][j]);
		}
		printf("\n");
	}
}
int visited[MAX];//0表示未被访问过，1表示已经访问过


//遍历V这一行，如果有一个数不是无穷大，那么这个数就是和我相邻的第一个邻接点
int First(Graph *g,int v)
{
	int i;
	for(i = 0;i < g->Vexnum;i++) 
	{
		if(g->A[v][i] != VERYBIG)
			return i;
	}
	return -1;
}

int Next(Graph *g,int v,int c) //从图g的第v行的第c个元素开始找下一个邻接点
{
	int i;
	for(i = c;i < g->Vexnum;i++)
	{
		if(g->A[v][i] != VERYBIG)
			return i;
	}
	return -1;
}

void DFS(Graph *g,int v)
{
	printf("%c\t",g->V[v]);
	visited[v] = 1; //已经被访问过了
	int i;
	for(i = First(g,v);i != -1;i = Next(g,v,i+1))
	{
		if(visited[i] == 0)
			DFS(g,i);
	}
}
void DFSTravel(Graph *g)
{
	memset(visited,0,sizeof(visited));
	int i;
	for(i = 0;i <g->Vexnum;i++) //防止孤立"岛屿"的存在
	{
		if(visited[i] == 0)
			DFS(g,i);
	}
}

/*
	将未被访问过的节点入队，并致其已被访问过，然后将这个节点出队，寻找和这个节点相邻的未被访问的节点入队，直到
	队列对空为止
*/
void BFSTravel(Graph *g)
{
	Queue *q = InitQueue();
	Node *p = NULL;
	int data;
	int i,j;
	for(i = 0;i < g->Vexnum;i++)
	{	
		visited[i] = 0;
	}
	
	for(i = 0;i < g->Vexnum;i++)
	{
		if(visited[i] == 0)
		{
			printf("%c\t",g->V[i]);
			visited[i] = 1;
			EnQueue(q,i);
			
			while(q->first) //只要队列非空
			{
				 p = DeQueue(q);
				 if(p)
					data = p->data;
				for(j = First(g,data); j != -1;j = Next(g,data,j+1))
				{
					if(visited[j] == 0)
					{
						visited[j] = 1;
						printf("%c\t",g->V[j]);
						EnQueue(q,j);
					}
				}
			}
		}
	}
}

int s[MAX];
int dist[MAX];
char path[MAX][MAX] = {0};
void Dijkstra(Graph *g,int v)
{
	int i,j;
	for(i = 0;i < g->Vexnum;i++)
	{
		s[i] = 0; //最短路径开始时都是未被确定的
		dist[i] = g->A[v][i]; //最短路径是目前能够观察到的从v出发到其他顶点的距离
		path[i][0] = g->V[v];//起点坐标都是v
	}
	s[v] = 1; //V-V 已经已知最短路径
	
	int min;
	int u;//保存最短路径的下标
	
	for(i = 1;i < g->Vexnum;i++)
	{
		//表示在所有未求出的当前路径中找出一条最短的，其长度作为当前求出的最短路径。
		min = VERYBIG;
		for(j = 0;j < g->Vexnum;j++)
		{
			
			if(min > dist[j] && s[j] == 0)
			{
				min = dist[j];
				u = j;
			}
		}
		
		s[u] = 1; //最短路径已经确定
		path[u][strlen(path[u])] =g->V[u]; //放入终点坐标
		
		
		//对s[w] = 0 的w，如果dist[u] + <u,w>  < dist[w];
		//那么dist[w]被更新为 dist[w] = dist[u] + <u,w>;
		for(j = 0; j< g->Vexnum;j++)
		{
			if(s[j] == 0)
			{
				//如果此时最短路径和当前由这个u节点出发，从j节点的距离比直接从v出发要短，就更新
				if(dist[u]+g->A[u][j] < dist[j]) 
				{
					dist[j] = dist[u]+g->A[u][j] ;
					strcpy(path[j],path[u]);
				}
			}
		}
	}
	
	for(i = 0;i < g->Vexnum;i++)
	{
		for(j = 0;path[i][j] != '\0';j++)
		{
			printf("%c  ",path[i][j]);
		}
		printf("%d\n",dist[i]);
	}
}
int main(int argc,char *argv[])
{
	Graph *g = CreateGraph();
	print_graph(g);
	//BFSTravel(g);
	Dijkstra(g,0);
	return 0;
}
