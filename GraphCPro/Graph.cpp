#include<iostream>
#include"Graph.h"
using namespace std;
extern Graph m_Graph;
//初始化图
int Init()
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			m_Graph.m_aAdjMatrix[i][j] = 0;	//邻接矩阵置零
		}
		m_Graph.m_nVexNum = 0;				//景点数目置零
	}
	return 1;
}
//将顶点添加到数组中
int InsertVex(Vex sVex)
{
	//顶点已满
	if (m_Graph.m_nVexNum == 20)
		return 0;
	//
	m_Graph.m_aVexs[m_Graph.m_nVexNum++] = sVex;
	return 1;
}
//将边保存到邻接矩阵中
int InsertEdge(Edge sEdge)
{
	//下标越界
	if (sEdge.vex1<0 || sEdge.vex1 >= 20 || sEdge.vex2<0 || sEdge.vex2 >= 20)
		return 0;
	m_Graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_Graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;

	return 1;
}

//查询指定顶点信息
Vex GetVex(int nVex)
{
	return m_Graph.m_aVexs[nVex];
}

//查询与指定顶点相连的边
int FindEdge(int nVex, Edge aEdge[])
{
	int flag = 0;  //与景点n相邻的边的条数
				   //便利整个图的邻接矩阵
	for (int j = 0; j < 20; j++) {
		if (m_Graph.m_aAdjMatrix[nVex][j] != 0 && nVex != j) {
			aEdge[flag].vex1 = nVex;
			aEdge[flag].vex2 = j;
			aEdge[flag].weight = m_Graph.m_aAdjMatrix[nVex][j];
			flag++;
		}
	}
	return flag;
}

//获取当前顶点数
int GetVexnum() {
	return m_Graph.m_nVexNum;
}

//实现图的深度优先搜索遍历
void DFS(int nVex, bool bVisited[], int & nIndex, PathList & pList)
{
	bVisited[nVex] = true;				//改为已访问
	pList->vexs[nIndex++] = nVex;		//访问顶点nVex并赋值给链表，然后索引值自加

										//判断所有的顶点是否都已经被访问过									
	int v_num = 0;
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		//如果当前i节点被访问过，则V-Num自加
		if (bVisited[i])
			v_num++;
	}

	//所有的顶点都已经被访问过,新增链表结点,保存此次的路径。必须保存，不然在后续的递归中会存在重复使用的vex，导致有的路径结点中vex没有值
	if (v_num == m_Graph.m_nVexNum)
	{
		//创建一个新链表，将当前的pList中的数据保存起来
		pList->next = new Path;
		for (int i = 0; i<m_Graph.m_nVexNum; i++)
		{
			pList->next->vexs[i] = pList->vexs[i];
		}
		pList = pList->next;		//pList指针继续往下移动，寻找下一条路径
		pList->next = NULL;			//next赋值为空
	}
	//并没有全部访问，则进行寻找下一个相邻节点的操作
	else
	{
		for (int i = 0; i<m_Graph.m_nVexNum; i++)
		{
			//如果i是nVex的的邻接点  并且未被访问
			if (!bVisited[i] && m_Graph.m_aAdjMatrix[nVex][i]>0)
			{
				DFS(i, bVisited, nIndex, pList);			//递归调用DFS
				bVisited[i] = false;						//改为未访问，回退
				nIndex--;									//索引值减一
			}
		}
	}
}

//深度优先遍历
void DFSTraverse(int nVex, PathList & pList)
{
	int nIndex = 0;					//遍历深度
	bool bVisited[20] = { false };  //所有的景点起始均为未访问
	DFS(nVex, bVisited, nIndex, pList);

}
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]) {
	int nShortPath[20][20];       //保存最短路径，其中行表示终点，列表示从起点到终点的最短路径的每一步
	int nShortDistance[20];       //保存最短距离，保存从起点到任一顶点的最短距离
	bool aVisited[20];            //判断某顶点是否已经加入到最短路径中
	int v;                        //在下面的循环中，表示每一次找到的可以加入集合的顶点，即已经找到了从起点到该顶点的最短路径

								  //初始化工作
	for (v = 0; v<m_Graph.m_nVexNum; v++)
	{
		aVisited[v] = false;
		if (m_Graph.m_aAdjMatrix[nVexStart][v] != 0) {
			//初始化该顶点到其他顶点的最短距离，默认为两顶点间的距离
			nShortDistance[v] = m_Graph.m_aAdjMatrix[nVexStart][v];
		}
		else {
			//如果顶点v和nVexStart不相连，则最短距离设置为最大值
			nShortDistance[v] = 0x7FFFFFFF;
		}
		nShortPath[v][0] = nVexStart;   //起始点为nVexStart
										//初始化最短路径
		for (int w = 1; w < m_Graph.m_nVexNum; w++) {
			nShortPath[v][w] = -1;
		}
	}

	//初始化，将nVexStart顶点加入到集合中
	aVisited[nVexStart] = true;
	int min;					//暂存路径的最小值
	for (int i = 1; i<m_Graph.m_nVexNum; i++)
	{
		min = 0x7FFFFFFF;
		bool bAdd = false;		//判断是否还有顶点可以加入集合
		for (int w = 0; w<m_Graph.m_nVexNum; w++)
		{
			if (!aVisited[w] && nShortDistance[w]<min)
			{
				v = w;						//w顶点距离nVexStart顶点最近
				min = nShortDistance[w];	//w到nVexStart的最短距离为min
				bAdd = true;
			}
		}
		//若果没有顶点可以加入到集合，则跳出循环
		if (!bAdd) break;
		aVisited[v] = true;			//将w顶点加入到集合
		nShortPath[v][i] = v;		//每次找到最短路径后，就相当于从源点出发到了终点，所以nShortPath[v][i]=v
		for (int w = 0; w<m_Graph.m_nVexNum; w++)
		{
			//将w作为过渡顶点计算nVexStart通过w到每个顶点的距离
			if (!aVisited[w] && (min + m_Graph.m_aAdjMatrix[v][w]<nShortDistance[w]) && (m_Graph.m_aAdjMatrix[v][w]>0))
			{
				//更新当前最短路径及距离
				nShortDistance[w] = min + m_Graph.m_aAdjMatrix[v][w];
				for (int i = 0; i < m_Graph.m_nVexNum; i++) {
					//如果通过w达到顶点i的距离比较短，则将w的最短路径复制给i
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}

	int nIndex = 0;
	int nVex1 = nVexStart;
	//将最短路径保存为边的结构体数组
	for (int i = 1; i<m_Graph.m_nVexNum; i++)
	{
		if (nShortPath[nVexEnd][i] != -1)
		{
			aPath[nIndex].vex1 = nVex1;
			aPath[nIndex].vex2 = nShortPath[nVexEnd][i];
			aPath[nIndex].weight = m_Graph.m_aAdjMatrix[nVex1][aPath[nIndex].vex2];
			nVex1 = nShortPath[nVexEnd][i];
			nIndex++;
		}
	}

	return nIndex;
}

int FindMinTree(struct Edge aPath[]) {
	//通过Prim算法求得最小生成树
	int length = GetVexnum();
	int index = 0;//返回数组元素个数
	bool visited[20] = { false };//初始化，作为判断是否被访问
								 //假设从0开始
	visited[0] = true;
	for (int i = 0; i < length; i++) {
		int min = 0x7FFFFFFF;
		int tempstart = 0;
		int tempend = 0;
		//获取当前可用点的最小值
		for (int j = 0; j < length; j++) {
			//若被访问，则选择
			if (visited[j] == true) {
				for (int k = 0; k < length; k++) {
					if ((m_Graph.m_aAdjMatrix[j][k] != 0) && (m_Graph.m_aAdjMatrix[j][k] < min) && (visited[k] == false)) {
						tempstart = j;
						tempend = k;
						min = m_Graph.m_aAdjMatrix[j][k];
					}
				}
			}
			//更新内容
		}
		visited[tempend] = true;
		aPath[index].vex1 = tempstart;
		aPath[index].vex2 = tempend;
		aPath[index].weight = m_Graph.m_aAdjMatrix[tempstart][tempend];
		index++;
		int flag = 0;//跳出标志
		for (int l = 0; l < length; l++) {
			if (visited[l] == true) {
				flag++;
			}
		}
		if (flag == length) {
			//全部元素被访问
			break;
		}
	}
	return index;
}