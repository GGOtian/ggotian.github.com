#pragma once
#ifndef TOURISM_H
#define TOURISM_H
//��ȡ�ļ���������������ͼ
int CreateGraph();

//��ѯָ��������Ϣ����ʾ�����ھ���ľ���
int GetSPotInfo();

//�õ����㵼��ͼ·�ߣ�����ʾ
void TravelPath();

//ͨ������ m_Graph()������ѯ�������������·���;��롣 
void FindShortPath(void);
//
void DesignPath(void);
#endif