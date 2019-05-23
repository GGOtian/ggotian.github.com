#include<iostream>
#include <fstream>
#include"Graph.h"
#include"Tourism.h"
using namespace std;

//m_Graphͼ�ṹ�Ѿ����������ж��壬�˴�������
extern Graph m_Graph;

//����1����ȡ�ļ���������������ͼ
int CreateGraph() {
	cout << "=====�������㾰��ͼ=====" << endl;

	Init();			//��ʼ��ͼ

	//��ȡVex.txt�ļ��������е�����ͨ�� ����Vex ���ص� ͼm_Graph ��
	ifstream VexFile("Vex.txt");

	//������ļ�ʧ�ܣ���ʾ������Ϣ������
	if (!VexFile) {
		cout << "Vex.txt�ļ���ʧ�ܣ����飡" << endl;
		return 0;
	}

	//��������һ��Char���������������ʱ�����Vex.txt��ȡ��һ������
	char num[2];
	char name[20];
	char desc[1024];
	Vex sVex;
	//���ж�ȡVex.txt�ļ��е�����
	VexFile.getline(num, 2);		//����һ�е����ݶ���������
	cout << "������Ŀ��" << atoi(num) << endl;//aoti���ַ���ת����������
	cout << "�������������������㡪��������������" << endl;
	cout << "���\t��������\t��������" << endl;
	while (VexFile.getline(num, 2)) {
		sVex.num = atoi(num);
		VexFile.getline(name, 20);
		strcpy(sVex.name, name);

		VexFile.getline(desc, 1024);
		strcpy(sVex.desc, desc);

		//��Ŀǰ����Vex ��Ϣ���
		cout << sVex.num << "\t" << sVex.name << "\t\t" << sVex.desc << endl;

		//���������ͼ�в����ݷ���ֵ���д�����ʾ
		if (!InsertVex(sVex)) {
			cout << "��������ʧ�ܣ�" << endl;
			continue;
		}
	}
	VexFile.close();

	FILE *EdgeFile = fopen("Edge.txt","r");
	if (!EdgeFile) {
		cout << "Edge.txt�ļ���ʧ�ܣ����飡" << endl;
		return 0;
	}
	cout << "-----��-----" << endl;
	Edge sEdge;
	while (fscanf(EdgeFile, "%d\t%d\t%d\n", &sEdge.vex1, &sEdge.vex2, &sEdge.weight) != -1)
	{
		cout << "<" << sEdge.vex1 << "," << sEdge.vex2 << ">  " << sEdge.weight << endl;
		//������
		if (!InsertEdge(sEdge))
		{
			cout << "����·����Ϣʧ�ܣ�" << endl;
			continue;
		}
	}
	fclose(EdgeFile);

	cout << endl;
	return 1;
}

/*
void SearchGraph() {
int k;
int x = 0;
Vex vex[20];
Edge Edge[20];
CGraph graph;
ifstream f1("Vex.txt");
f1 >> graph.VexNum;
graph.m[20][20];
for (int i = 0; i < 20; i++) {
for (int j = 0; j <= 20; j++) {
graph.m[i][j] = 0;
}
}
for (int j = 0; j < graph.VexNum; j++) {
f1 >> graph.Vexs[j].num;
f1 >> graph.Vexs[j].name;
f1 >> graph.Vexs[j].desc;
}
ifstream f2("Edge.txt");
for (int j = 0; j < 20; j++) {
f2 >> Edge[j].vex1;
f2 >> Edge[j].vex2;
f2 >> Edge[j].weight;
x++;
if (f2.peek() == EOF) break;
}
for (int j = 0; j < x; j++) {
graph.m[Edge[j].vex1][Edge[j].vex2] = Edge[j].weight;
}
cout << "----��ѯ������Ϣ----" << endl;
for (int j = 0; j < graph.VexNum; j++) {
cout << graph.Vexs[j].num << "--" << graph.Vexs[j].name << endl;
}
cout << "������Ҫ��ѯ�ľ����ţ�";
cin >> k;
cout << graph.Vexs[k].name << endl;
cout << graph.Vexs[k].desc << endl;
cout << "----�ܱ߾���----" << endl;
for (int j = 0; j < x; j++) {
if (graph.m[j][k] != 0)		cout << graph.Vexs[k].name << "-->" << graph.Vexs[j].name << graph.m[j][k] << endl;
if (graph.m[k][j] != 0)		cout << graph.Vexs[k].name << "-->" << graph.Vexs[j].name << graph.m[k][j] << endl;
}

};*/

//����2����ѯָ��������Ϣ����ʾ�����ھ���ľ���
int GetSPotInfo() {
	cout << "=====��ѯ������Ϣ=====" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	//δ����ͼ��ʱ��
	if (nVexNum == 0) {
		cout << "���ȴ���ͼ��" << endl;
		return 0;
	}
	//��������Ϣ�г���
	cout << "��ǰ����������" << m_Graph.m_nVexNum << endl;
	cout << "���\t��������" << endl;
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "\t" << sVex.name << endl;
	}

	//��ʾ�û����ݱ����ѯ
	cout << "\n��������Ҫ��ѯ�ľ����ţ�";
	int querynum;
	cin >> querynum;
	if (querynum<0 || querynum >= m_Graph.m_nVexNum)
		cout << "�������" << endl;
	else
	{
		Vex sVex = GetVex(querynum);
		cout << "��������\t��������" << endl;
		cout << sVex.name << "\t\t" << sVex.desc << endl;

		//���ܱ߾���ͬ�����
		cout << "-----�ܱ߾���-----" << endl;
		Edge aEdge[20];
		int EdgeNum = FindEdge(querynum, aEdge);   //�ܱ߾������Ŀ
		cout << "�ܱ߾�����Ŀ��" << EdgeNum << endl;
		for (int i = 0; i<EdgeNum; i++)
		{
			Vex v1 = GetVex(aEdge[i].vex1);
			Vex v2 = GetVex(aEdge[i].vex2);
			cout << v1.name << "->" << v2.name << "  " << aEdge[i].weight << "m" << endl;
		}
	}
	cout << endl;
	return 1;
}


//����3���õ����㵼��ͼ·�ߣ�����ʾ
void TravelPath()
{
	//�������ǰ�����Լ����
	cout << "=====���ξ��㵼��=====" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "���ȴ���ͼ��" << endl;
		return;
	}
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}

	//��ʾ�û�ѡ�񾰵����
	cout << "��������Ҫ��ʼ���ţ�";
	int startplace;		//�����
	cin >> startplace;
	//�ж��û������Ƿ���Ϲ淶
	if (startplace<0 || startplace >= m_Graph.m_nVexNum)
	{
		cout << "�������" << endl;
		return;
	}

	//��ѯ��startplace��ʼ��·����Ϣ
	PathList pList = new Path;
	PathList pHead = pList;
	//�õ�·����Ϣ
	DFSTraverse(startplace, pList);
	//���·����Ϣ
	cout << "���ο�·�ߣ�" << endl;
	int i = 1;
	pList = pHead;			//ͷָ��һֱ�ڣ����丳ֵ��pList��������������
	while (pList->next != NULL)
	{
		//���һ��·����Ϣ
		Vex sVex = GetVex(pList->vexs[0]);
		cout << "·��" << i++ << "��" << sVex.name;
		for (int j = 1; j<m_Graph.m_nVexNum; j++)
		{
			sVex = GetVex(pList->vexs[j]);
			cout << "->" << sVex.name;
		}
		cout << endl;
		pList = pList->next;		//ָ��������ƣ�������һ�����
	}
	cout << endl;
	//ָ��������
	delete pList;
	pList = NULL;
	pHead = NULL;
}
//�����ģ�ͨ������ FindShortPath ��������ѯ��ʼ���㵽Ŀ�ľ���֮��ĵ����·������̾���
void FindShortPath(void) { 
	cout << "==========�������·��==========" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "���ȴ���ͼ��" << endl;
		return;
	}
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}
	//��ʾ�û�������Ϣ
	//������������ı��
	int nVexStart;
	int nVexEnd;
	int index;  //·������
	Edge aPath[20];
	cout << "���������ı�ţ�" << endl;
	cin >> nVexStart;
	cout << "�������յ�ı�ţ�" << endl;
	cin >> nVexEnd;
	//�������·�� 
	index = FindShortPath(nVexStart,nVexEnd,aPath);
	//�õ����·������̾���
	int length = 0;						//���·���ܳ���
	Vex sVex = GetVex(aPath[0].vex1);	//������Ϣ��������Ϣ��

										//�����·���������ʾ
	cout << "���·��Ϊ��" << sVex.name;
	for (int i = 0; i < index; i++) {
		sVex = GetVex(aPath[i].vex2);
		cout << "->" << sVex.name;
		length += aPath[i].weight;
	}
	cout << endl;
	cout << "��̾���Ϊ��" << length << endl << endl;;

}
//ͨ������ FindShortPath ��������ѯ��ʼ���㵽Ŀ�ľ���֮��ĵ����·������̾��롣
void DesignPath(void) {
	cout << "------�����·�滮------" << endl;
	struct Edge Edges[20] = { 0 };
	int num = FindMinTree(Edges);
	int distance = 0;//�ܳ���
	for (int i = 0; i < num; i++) {
		cout << m_Graph.m_aVexs[Edges[i].vex1].name << " - " << m_Graph.m_aVexs[Edges[i].vex2].name << " " << Edges[i].weight << "m" << endl;
		distance += Edges[i].weight;
	}
	cout << "�����·���ܳ���Ϊ��" << distance << "m" << endl;
}