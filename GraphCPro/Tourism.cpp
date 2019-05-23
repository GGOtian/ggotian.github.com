#include<iostream>
#include <fstream>
#include"Graph.h"
#include"Tourism.h"
using namespace std;

//m_Graph图结构已经在主函数中定义，此处调用他
extern Graph m_Graph;

//功能1：读取文件，创建景区景点图
int CreateGraph() {
	cout << "=====创建景点景区图=====" << endl;

	Init();			//初始化图

	//读取Vex.txt文件，将其中的数据通过 景点Vex 加载到 图m_Graph 中
	ifstream VexFile("Vex.txt");

	//如果打开文件失败，显示错误信息并返回
	if (!VexFile) {
		cout << "Vex.txt文件打开失败，请检查！" << endl;
		return 0;
	}

	//定义以下一个Char数组参数，用来暂时保存从Vex.txt读取的一行数据
	char num[2];
	char name[20];
	char desc[1024];
	Vex sVex;
	//逐行读取Vex.txt文件中的数据
	VexFile.getline(num, 2);		//将第一行的数据读出，丢掉
	cout << "景区数目：" << atoi(num) << endl;//aoti：字符串转换成整型数
	cout << "————————顶点————————" << endl;
	cout << "编号\t景区名称\t景区描述" << endl;
	while (VexFile.getline(num, 2)) {
		sVex.num = atoi(num);
		VexFile.getline(name, 20);
		strcpy(sVex.name, name);

		VexFile.getline(desc, 1024);
		strcpy(sVex.desc, desc);

		//将目前景点Vex 信息输出
		cout << sVex.num << "\t" << sVex.name << "\t\t" << sVex.desc << endl;

		//将景点插入图中并根据反馈值进行错误提示
		if (!InsertVex(sVex)) {
			cout << "新增景点失败！" << endl;
			continue;
		}
	}
	VexFile.close();

	FILE *EdgeFile = fopen("Edge.txt","r");
	if (!EdgeFile) {
		cout << "Edge.txt文件打开失败，请检查！" << endl;
		return 0;
	}
	cout << "-----边-----" << endl;
	Edge sEdge;
	while (fscanf(EdgeFile, "%d\t%d\t%d\n", &sEdge.vex1, &sEdge.vex2, &sEdge.weight) != -1)
	{
		cout << "<" << sEdge.vex1 << "," << sEdge.vex2 << ">  " << sEdge.weight << endl;
		//新增边
		if (!InsertEdge(sEdge))
		{
			cout << "新增路径信息失败！" << endl;
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
cout << "----查询景点信息----" << endl;
for (int j = 0; j < graph.VexNum; j++) {
cout << graph.Vexs[j].num << "--" << graph.Vexs[j].name << endl;
}
cout << "输入你要查询的景点编号：";
cin >> k;
cout << graph.Vexs[k].name << endl;
cout << graph.Vexs[k].desc << endl;
cout << "----周边景点----" << endl;
for (int j = 0; j < x; j++) {
if (graph.m[j][k] != 0)		cout << graph.Vexs[k].name << "-->" << graph.Vexs[j].name << graph.m[j][k] << endl;
if (graph.m[k][j] != 0)		cout << graph.Vexs[k].name << "-->" << graph.Vexs[j].name << graph.m[k][j] << endl;
}

};*/

//功能2：查询指定景点信息，显示到相邻景点的距离
int GetSPotInfo() {
	cout << "=====查询景点信息=====" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	//未创建图的时候
	if (nVexNum == 0) {
		cout << "请先创建图！" << endl;
		return 0;
	}
	//将景点信息列出来
	cout << "当前景区个数：" << m_Graph.m_nVexNum << endl;
	cout << "编号\t景点名称" << endl;
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "\t" << sVex.name << endl;
	}

	//提示用户根据编码查询
	cout << "\n请输入想要查询的景点编号：";
	int querynum;
	cin >> querynum;
	if (querynum<0 || querynum >= m_Graph.m_nVexNum)
		cout << "输入错误！" << endl;
	else
	{
		Vex sVex = GetVex(querynum);
		cout << "景点名称\t景点描述" << endl;
		cout << sVex.name << "\t\t" << sVex.desc << endl;

		//将周边景区同样输出
		cout << "-----周边景区-----" << endl;
		Edge aEdge[20];
		int EdgeNum = FindEdge(querynum, aEdge);   //周边景点的数目
		cout << "周边景区数目：" << EdgeNum << endl;
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


//功能3：得到景点导航图路线，并显示
void TravelPath()
{
	//先输出当前景点以及编号
	cout << "=====旅游景点导航=====" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "请先创建图！" << endl;
		return;
	}
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}

	//提示用户选择景点起点
	cout << "请输入想要起始点编号：";
	int startplace;		//起点编号
	cin >> startplace;
	//判断用户输入是否符合规范
	if (startplace<0 || startplace >= m_Graph.m_nVexNum)
	{
		cout << "输入错误！" << endl;
		return;
	}

	//查询从startplace开始的路径信息
	PathList pList = new Path;
	PathList pHead = pList;
	//得到路径信息
	DFSTraverse(startplace, pList);
	//输出路径信息
	cout << "供参考路线：" << endl;
	int i = 1;
	pList = pHead;			//头指针一直在，将其赋值给pList，用来遍历链表
	while (pList->next != NULL)
	{
		//输出一条路径信息
		Vex sVex = GetVex(pList->vexs[0]);
		cout << "路线" << i++ << "：" << sVex.name;
		for (int j = 1; j<m_Graph.m_nVexNum; j++)
		{
			sVex = GetVex(pList->vexs[j]);
			cout << "->" << sVex.name;
		}
		cout << endl;
		pList = pList->next;		//指针继续下移，遍历下一个结点
	}
	cout << endl;
	//指针做处理
	delete pList;
	pList = NULL;
	pHead = NULL;
}
//功能四：通过调用 FindShortPath 函数，查询起始景点到目的景点之间的的最短路径和最短距离
void FindShortPath(void) { 
	cout << "==========搜索最短路径==========" << endl;
	int nVexNum = m_Graph.m_nVexNum;
	if (nVexNum == 0) {
		cout << "请先创建图！" << endl;
		return;
	}
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		Vex sVex = GetVex(i);
		cout << i << "-" << sVex.name << endl;
	}
	//提示用户输入信息
	//输入两个景点的编号
	int nVexStart;
	int nVexEnd;
	int index;  //路径条数
	Edge aPath[20];
	cout << "请输入起点的编号：" << endl;
	cin >> nVexStart;
	cout << "请输入终点的编号：" << endl;
	cin >> nVexEnd;
	//搜索最短路径 
	index = FindShortPath(nVexStart,nVexEnd,aPath);
	//得到最短路径和最短距离
	int length = 0;						//最短路径总长度
	Vex sVex = GetVex(aPath[0].vex1);	//顶点信息（景点信息）

										//将最短路径输出，显示
	cout << "最短路径为：" << sVex.name;
	for (int i = 0; i < index; i++) {
		sVex = GetVex(aPath[i].vex2);
		cout << "->" << sVex.name;
		length += aPath[i].weight;
	}
	cout << endl;
	cout << "最短距离为：" << length << endl << endl;;

}
//通过调用 FindShortPath 函数，查询起始景点到目的景点之间的的最短路径和最短距离。
void DesignPath(void) {
	cout << "------铺设电路规划------" << endl;
	struct Edge Edges[20] = { 0 };
	int num = FindMinTree(Edges);
	int distance = 0;//总长度
	for (int i = 0; i < num; i++) {
		cout << m_Graph.m_aVexs[Edges[i].vex1].name << " - " << m_Graph.m_aVexs[Edges[i].vex2].name << " " << Edges[i].weight << "m" << endl;
		distance += Edges[i].weight;
	}
	cout << "铺设电路的总长度为：" << distance << "m" << endl;
}