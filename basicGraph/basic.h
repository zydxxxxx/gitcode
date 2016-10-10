#pragma once
#include<string>
#include<fstream>
#include <vector>
#include<iostream>
#include<time.h>
#include<stack>
#include<queue>
struct ArcNode{
	int adjvex;
	struct ArcNode *nextarc;
};
struct VNode{
	int data;
	int d;
	struct ArcNode *firstarc;
};
using namespace std;
class CGraph
{
private:
	struct VNode *adjlist;		//the vertex 结点的树组
	int *visit;                 //访问标记
	int n, e;					//the number of nodes
public:
	CGraph(string name);
	CGraph(){};
	void InitNode(string name);
	void dfs();
	void dfsvisit(VNode &u);
	void bfs(CGraph &G);
	void DFS();
	void DFS_self();
	void BFS();
	~CGraph(void);
};
CGraph::CGraph(string name)
{
	InitNode(name);
}
CGraph::~CGraph(void)
{
	struct ArcNode *pArcNode;
	struct ArcNode *pArcNode1;
	for (int i = 0; i<n; ++i)
	{
		pArcNode = adjlist[i].firstarc;
		while (pArcNode != NULL)
		{
			pArcNode1 = pArcNode;
			pArcNode = pArcNode1->nextarc;
			delete pArcNode1;
		}
	}
}

void CGraph::BFS()
{

	int *visit = new int[n];
	for (int i = 0; i<n; i++)
	{
		visit[i] = 0;
	}
	/*queue<int> q;    */                                         //注释部分为使用stl队列的代码
	int *qu;
	qu = new int[n+2];
	int front, rear;
	for (int i = 0; i<n; i++)
	{
		if (visit[i] == 0)
		{
		/*	q.push(i);*/
			front = 0;
			rear = 0;                                  //原来的速率为1100ms在此每次将队列进行初始化以后时间变成了708ms
			rear = (rear + 1) % n;
			qu[rear] = i;
			visit[i] = 1;
			int u;
			//while(!q.empty())
			while (front!=rear)
			{
				//u=q.front();
				//q.pop();
				front = (front + 1) % n;
				u = qu[front];		    
				for (ArcNode *p= adjlist[u].firstarc; p != NULL; p = p->nextarc)
				{
					if (visit[p->adjvex] == 0)
					{	
						visit[p->adjvex] = 1;
						//q.push(p->adjvex);
						rear = (rear + 1) % n;
						qu[rear] = p->adjvex;
					}
				}
			}
		}
	}
	delete qu;
}
void CGraph::DFS()
{
	//	std::stack <VNode> S;                            //注释部分为使用stl栈的代码
	visit = new int[n];
	for (int i = 0; i<n; i++)
	{
		visit[i] = 0;
	}
	//	VNode a;
	int a;
	int *stack = new int[n];
	int top = -1;
	for (int i = 0; i<n; i++)
	{
		//			S.push(adjlist[i]);
		stack[top++] = i;
		//			while(S.length!=-1)
		while (top != -1)
		{
			//	    a=S.top();
			//	    S.pop();
			//		visit[a.data]=1;
			a = stack[top--];
			visit[a] = 1;
			ArcNode *p;
			for (p = adjlist[a].firstarc; p != NULL; p = p->nextarc)
			{
				if (visit[p->adjvex] == 0)
			//		S.push(adjlist[p->adjvex]);
					stack[top++] = p->adjvex;
			}
		}
	}
}
void CGraph::dfs()
{
	visit = new int[n];
	int k = 0;
	while (k<n)
	{
		visit[k] = 0;
		k++;
	}
	for (k = 0; k<n; k++)
	{
		if (visit[k] == 0)
		{
			visit[adjlist[k].data] = 1;
			dfsvisit(adjlist[k]);
		}
	}
}
void CGraph::dfsvisit(VNode &u)
{
	
	for (ArcNode *p = u.firstarc; p != NULL; p = p->nextarc)
	{
		if (visit[p->adjvex] == 0)
		{

			visit[p->adjvex] = 1;
			dfsvisit(adjlist[p->adjvex]);
		}
	}
}
void CGraph::InitNode(string name)
{
	FILE *fp=fopen(name.c_str(), "r");
	fscanf(fp, "%d", &n);
	adjlist = new struct VNode[n];
	int i;
	for (int k = 0; k<n; k++)
	{
		adjlist[k].data = k;
		adjlist[k].firstarc = NULL;
	}
	while (fscanf(fp, "%d", &i) != EOF)
	{
		int k2;
		fscanf(fp, "%d", &k2);
		struct ArcNode *p;
		p = (struct ArcNode *)malloc(sizeof(struct ArcNode));
		p->adjvex = k2;
		p->nextarc = adjlist[i].firstarc;
		adjlist[i].firstarc = p;
	}
	visit = new int[n];
}
//void CGraph::BFS(){
//	queue<int> qu;//用来存储结点的队列;
//	//vector<int> test;//用来存储广度优先搜索的访问顺序;
//	//if (head!=NULL)
//	int *visit = new int[n];
//	for (int i = 0; i<n; i++)
//	{
//		visit[i] = 0;
//	}
//	for (int i = 0; i<n; ++i)
//	{
//		if (visit[i] == 0)
//		{
//			qu.push(i);
//			visit[i] = 1;
//			ArcNode *p;
//			while (!qu.empty()){
//				p = adjlist[qu.front()].firstarc;//我们需要的是即将出队列的那个元素;
//				qu.pop();
//				//cout<<qu.back()<<endl;//.back()函数返回的值为队列中的最后一个;
//				//	cout<<qu.front()<<endl;
//				while (p != NULL){
//					if (visit[p->adjvex] == 0)//当前顶点没有被访问过，进入队列;
//					{
//						qu.push(p->adjvex);
//						visit[p->adjvex] = 1;
//					}
//					p = p->nextarc;
//				}
//				//	test.push_back(qu.back());
//			}//while;
//		}//if;
//	}//for;
//	//for (int i = 0; i<n; ++i)
//	//{
//	//	if (visit == 0)
//	//	{
//	//		cout << "BFS有问题！！！" << i << endl;
//	//		system("pause");
//	//	}
//	//}
//}
//void CGraph::BFS_self(){
//	int* qu;
//	qu = new int[n + 2];
//	int *visit = new int[n];
//	for (int i = 0; i<n; i++)
//	{
//		visit[i] = 0;
//	}
//	for (int i = 0; i<n; ++i)
//	{
//		if (visit[i] == 0)
//		{
//			ArcNode* temp;
//			int j;//;
//			int rear = 0, front = 0;
//			rear = (rear + 1) % n;
//			qu[rear] = i;
//			visit[i] = 1;
//			while (front != rear){
//				front = (front + 1) % n;
//				j = qu[front];
//				temp = adjlist[j].firstarc;
//				while (temp != NULL){
//					if (visit[temp->adjvex] == 0)
//					{
//						visit[temp->adjvex] = 1;
//						rear = (rear + 1) % n;
//						qu[rear] = temp->adjvex;
//					}
//					temp = temp->nextarc;
//				}
//			}
//		}
//	}//for;
//	delete[] qu;
//}