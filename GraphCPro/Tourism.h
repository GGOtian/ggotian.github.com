#pragma once
#ifndef TOURISM_H
#define TOURISM_H
//读取文件，创建景区景点图
int CreateGraph();

//查询指定景点信息，显示到相邻景点的距离
int GetSPotInfo();

//得到景点导航图路线，并显示
void TravelPath();

//通过调用 m_Graph()函数查询两个景点间的最短路径和距离。 
void FindShortPath(void);
//
void DesignPath(void);
#endif