//
#include "stdafx.h"
#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include "kruskal.h"
using namespace std; 
#define INT_MAX 10000
#define MAX 20

int adjNode[MAX];//Kruscal���������,����0��ʾ��δ�������ʹ�,��0ֵ��ʾ�������Ľڵ��±ꡣ


int _tmain(int argc, _TCHAR* argv[])
{
	Algraph gra;
	MGraph_L G;
	int data[7][7]={{INT_MAX,28,INT_MAX,INT_MAX,INT_MAX,10,INT_MAX},
					{28,INT_MAX,16,INT_MAX,INT_MAX,INT_MAX,14},
					{INT_MAX,16,INT_MAX,12,INT_MAX,INT_MAX,INT_MAX},
					{INT_MAX,INT_MAX,12,INT_MAX,22,INT_MAX,18},
					{INT_MAX,INT_MAX,INT_MAX,22,INT_MAX,25,24},
					{10,INT_MAX,INT_MAX,INT_MAX,25,INT_MAX,INT_MAX},
					{INT_MAX,14,INT_MAX,18,24,INT_MAX,INT_MAX}};
	CreatMGraph_L(G,*data,7);//����ͼ���ڽӾ����ʾ
	CreatAdj(gra,G);

	cout<<"Kruscal:"<<endl;
	Kruscal_Arc(G,gra);
	return 0;
}
