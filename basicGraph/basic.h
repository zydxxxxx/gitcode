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
	struct VNode *adjlist;		//the vertex ��������
	int *visit;                 //���ʱ��
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
	/*queue<int> q;    */                                         //ע�Ͳ���Ϊʹ��stl���еĴ���
	int *qu;
	qu = new int[n+2];
	int front, rear;
	for (int i = 0; i<n; i++)
	{
		if (visit[i] == 0)
		{
		/*	q.push(i);*/
			front = 0;
			rear = 0;                                  //ԭ��������Ϊ1100ms�ڴ�ÿ�ν����н��г�ʼ���Ժ�ʱ������708ms
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
	//	std::stack <VNode> S;                            //ע�Ͳ���Ϊʹ��stlջ�Ĵ���
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
//	queue<int> qu;//�����洢���Ķ���;
//	//vector<int> test;//�����洢������������ķ���˳��;
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
//				p = adjlist[qu.front()].firstarc;//������Ҫ���Ǽ��������е��Ǹ�Ԫ��;
//				qu.pop();
//				//cout<<qu.back()<<endl;//.back()�������ص�ֵΪ�����е����һ��;
//				//	cout<<qu.front()<<endl;
//				while (p != NULL){
//					if (visit[p->adjvex] == 0)//��ǰ����û�б����ʹ����������;
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
//	//		cout << "BFS�����⣡����" << i << endl;
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