#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include <string>
//���徰�㣨ͼ�Ķ��㣩
struct Vex
{
	int num;					//����ı��
	char name[20];				//���������
	char desc[1024]; 			//���������
};

//�����·��Ϣ��ͼ�ıߣ�
struct Edge
{
	int vex1;					//�ߵĵ�һ������
	int vex2;					//�ߵĵڶ�������
	int weight;					//Ȩֵ�����������ھ���ľ���
};

//����ͼ
struct Graph
{
	int m_aAdjMatrix[20][20];   //�����ڽӾ������ʽ����
	Vex m_aVexs[20];            //��������
	int m_nVexNum;              //�������Ŀ
};

//����·��
typedef struct Path
{
	int vexs[20];				//�����һ��������·��
	Path *next;					//��һ��·��
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
