#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include <string>
//定义景点（图的顶点）
struct Vex
{
	int num;					//景点的编号
	char name[20];				//景点的名称
	char desc[1024]; 			//景点的描述
};

//定义道路信息（图的边）
struct Edge
{
	int vex1;					//边的第一个顶点
	int vex2;					//边的第二个顶点
	int weight;					//权值，即两个相邻景点的距离
};

//定义图
struct Graph
{
	int m_aAdjMatrix[20][20];   //采用邻接矩阵的形式储存
	Vex m_aVexs[20];            //顶点数组
	int m_nVexNum;              //景点的数目
};

//搜索路径
typedef struct Path
{
	int vexs[20];				//保存的一条完整的路径
	Path *next;					//下一条路径
}*PathList;

int Init();
int InsertVex(Vex sVex);
int InsertEdge(Edge sEdge);
Vex GetVex(int nVex);
int FindEdge(int nVex, Edge aEdge[]);
int GetVexnum();
void DFS(int nVex, bool bVisited[], int &nIndex, PathList &pList);
void DFSTraverse(int nVex, PathList &pList);
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);
int FindMinTree(struct Edge aPath[]);
#endif
