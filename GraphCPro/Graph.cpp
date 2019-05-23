#include<iostream>
#include"Graph.h"
using namespace std;
extern Graph m_Graph;
//��ʼ��ͼ
int Init()
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			m_Graph.m_aAdjMatrix[i][j] = 0;	//�ڽӾ�������
		}
		m_Graph.m_nVexNum = 0;				//������Ŀ����
	}
	return 1;
}
//��������ӵ�������
int InsertVex(Vex sVex)
{
	//��������
	if (m_Graph.m_nVexNum == 20)
		return 0;
	//
	m_Graph.m_aVexs[m_Graph.m_nVexNum++] = sVex;
	return 1;
}
//���߱��浽�ڽӾ�����
int InsertEdge(Edge sEdge)
{
	//�±�Խ��
	if (sEdge.vex1<0 || sEdge.vex1 >= 20 || sEdge.vex2<0 || sEdge.vex2 >= 20)
		return 0;
	m_Graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_Graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;

	return 1;
}

//��ѯָ��������Ϣ
Vex GetVex(int nVex)
{
	return m_Graph.m_aVexs[nVex];
}

//��ѯ��ָ�����������ı�
int FindEdge(int nVex, Edge aEdge[])
{
	int flag = 0;  //�뾰��n���ڵıߵ�����
				   //��������ͼ���ڽӾ���
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

//��ȡ��ǰ������
int GetVexnum() {
	return m_Graph.m_nVexNum;
}

//ʵ��ͼ�����������������
void DFS(int nVex, bool bVisited[], int & nIndex, PathList & pList)
{
	bVisited[nVex] = true;				//��Ϊ�ѷ���
	pList->vexs[nIndex++] = nVex;		//���ʶ���nVex����ֵ������Ȼ������ֵ�Լ�

										//�ж����еĶ����Ƿ��Ѿ������ʹ�									
	int v_num = 0;
	for (int i = 0; i<m_Graph.m_nVexNum; i++)
	{
		//�����ǰi�ڵ㱻���ʹ�����V-Num�Լ�
		if (bVisited[i])
			v_num++;
	}

	//���еĶ��㶼�Ѿ������ʹ�,����������,����˴ε�·�������뱣�棬��Ȼ�ں����ĵݹ��л�����ظ�ʹ�õ�vex�������е�·�������vexû��ֵ
	if (v_num == m_Graph.m_nVexNum)
	{
		//����һ������������ǰ��pList�е����ݱ�������
		pList->next = new Path;
		for (int i = 0; i<m_Graph.m_nVexNum; i++)
		{
			pList->next->vexs[i] = pList->vexs[i];
		}
		pList = pList->next;		//pListָ����������ƶ���Ѱ����һ��·��
		pList->next = NULL;			//next��ֵΪ��
	}
	//��û��ȫ�����ʣ������Ѱ����һ�����ڽڵ�Ĳ���
	else
	{
		for (int i = 0; i<m_Graph.m_nVexNum; i++)
		{
			//���i��nVex�ĵ��ڽӵ�  ����δ������
			if (!bVisited[i] && m_Graph.m_aAdjMatrix[nVex][i]>0)
			{
				DFS(i, bVisited, nIndex, pList);			//�ݹ����DFS
				bVisited[i] = false;						//��Ϊδ���ʣ�����
				nIndex--;									//����ֵ��һ
			}
		}
	}
}

//������ȱ���
void DFSTraverse(int nVex, PathList & pList)
{
	int nIndex = 0;					//�������
	bool bVisited[20] = { false };  //���еľ�����ʼ��Ϊδ����
	DFS(nVex, bVisited, nIndex, pList);

}
int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]) {
	int nShortPath[20][20];       //�������·���������б�ʾ�յ㣬�б�ʾ����㵽�յ�����·����ÿһ��
	int nShortDistance[20];       //������̾��룬�������㵽��һ�������̾���
	bool aVisited[20];            //�ж�ĳ�����Ƿ��Ѿ����뵽���·����
	int v;                        //�������ѭ���У���ʾÿһ���ҵ��Ŀ��Լ��뼯�ϵĶ��㣬���Ѿ��ҵ��˴���㵽�ö�������·��

								  //��ʼ������
	for (v = 0; v<m_Graph.m_nVexNum; v++)
	{
		aVisited[v] = false;
		if (m_Graph.m_aAdjMatrix[nVexStart][v] != 0) {
			//��ʼ���ö��㵽�����������̾��룬Ĭ��Ϊ�������ľ���
			nShortDistance[v] = m_Graph.m_aAdjMatrix[nVexStart][v];
		}
		else {
			//�������v��nVexStart������������̾�������Ϊ���ֵ
			nShortDistance[v] = 0x7FFFFFFF;
		}
		nShortPath[v][0] = nVexStart;   //��ʼ��ΪnVexStart
										//��ʼ�����·��
		for (int w = 1; w < m_Graph.m_nVexNum; w++) {
			nShortPath[v][w] = -1;
		}
	}

	//��ʼ������nVexStart������뵽������
	aVisited[nVexStart] = true;
	int min;					//�ݴ�·������Сֵ
	for (int i = 1; i<m_Graph.m_nVexNum; i++)
	{
		min = 0x7FFFFFFF;
		bool bAdd = false;		//�ж��Ƿ��ж�����Լ��뼯��
		for (int w = 0; w<m_Graph.m_nVexNum; w++)
		{
			if (!aVisited[w] && nShortDistance[w]<min)
			{
				v = w;						//w�������nVexStart�������
				min = nShortDistance[w];	//w��nVexStart����̾���Ϊmin
				bAdd = true;
			}
		}
		//����û�ж�����Լ��뵽���ϣ�������ѭ��
		if (!bAdd) break;
		aVisited[v] = true;			//��w������뵽����
		nShortPath[v][i] = v;		//ÿ���ҵ����·���󣬾��൱�ڴ�Դ����������յ㣬����nShortPath[v][i]=v
		for (int w = 0; w<m_Graph.m_nVexNum; w++)
		{
			//��w��Ϊ���ɶ������nVexStartͨ��w��ÿ������ľ���
			if (!aVisited[w] && (min + m_Graph.m_aAdjMatrix[v][w]<nShortDistance[w]) && (m_Graph.m_aAdjMatrix[v][w]>0))
			{
				//���µ�ǰ���·��������
				nShortDistance[w] = min + m_Graph.m_aAdjMatrix[v][w];
				for (int i = 0; i < m_Graph.m_nVexNum; i++) {
					//���ͨ��w�ﵽ����i�ľ���Ƚ϶̣���w�����·�����Ƹ�i
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}

	int nIndex = 0;
	int nVex1 = nVexStart;
	//�����·������Ϊ�ߵĽṹ������
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
	//ͨ��Prim�㷨�����С������
	int length = GetVexnum();
	int index = 0;//��������Ԫ�ظ���
	bool visited[20] = { false };//��ʼ������Ϊ�ж��Ƿ񱻷���
								 //�����0��ʼ
	visited[0] = true;
	for (int i = 0; i < length; i++) {
		int min = 0x7FFFFFFF;
		int tempstart = 0;
		int tempend = 0;
		//��ȡ��ǰ���õ����Сֵ
		for (int j = 0; j < length; j++) {
			//�������ʣ���ѡ��
			if (visited[j] == true) {
				for (int k = 0; k < length; k++) {
					if ((m_Graph.m_aAdjMatrix[j][k] != 0) && (m_Graph.m_aAdjMatrix[j][k] < min) && (visited[k] == false)) {
						tempstart = j;
						tempend = k;
						min = m_Graph.m_aAdjMatrix[j][k];
					}
				}
			}
			//��������
		}
		visited[tempend] = true;
		aPath[index].vex1 = tempstart;
		aPath[index].vex2 = tempend;
		aPath[index].weight = m_Graph.m_aAdjMatrix[tempstart][tempend];
		index++;
		int flag = 0;//������־
		for (int l = 0; l < length; l++) {
			if (visited[l] == true) {
				flag++;
			}
		}
		if (flag == length) {
			//ȫ��Ԫ�ر�����
			break;
		}
	}
	return index;
}