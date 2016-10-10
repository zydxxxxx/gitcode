#include"basic.h"
#include<iostream>
#include<time.h>
using namespace std;
const char *file[10] = {
	"uniprot150m.txt",
	"uniprot100m.txt",
	"vchocyc.txt",
	"uniprot22m.txt",
	"uniprot100m.txt",
	"uniprot150m.txt",
	"test2.txt",                       //text3数据集和ppt稍有改变
	"citeseer.txt",
	"citeseerx.txt",
	"cit-Patents.txt",
};
int main()
{
	clock_t start, end, cost;
	string infile = "E:dataset\\graphf\\";
	infile.append(file[0]);
	CGraph G1(infile);
	start = clock();
//	G1.DFS();
//	G1.dfs();
	G1.BFS();
//	G1.BFS_self();
//	G1.bfs();
	end = clock();
	cost = end - start;
	cout << cost << "ms";
	system("pause");
	return 0;
}