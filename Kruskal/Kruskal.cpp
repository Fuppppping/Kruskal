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

//���������������������������������ڽӾ����塭��������������
typedef struct 
{
	int adj;
	int weight;//����Ȩֵ
}AdjMatrix[MAX][MAX];

typedef struct 
{
	char vexs[20];
	int vexNum,arcNum;
	AdjMatrix adjMatrix;
}MGraph_L;

typedef struct node//�����
{
	int adjvex;//�ڽӵ���
	struct node *next;//����
	int weight;
}EdgeNode;

typedef struct
{
	//�������
	char vertex;//������
	EdgeNode *firstEdge;//�߱�ͷָ��
}VertexNode;

typedef struct//ͼ�Ķ���
{
	VertexNode vertices[MAX];
	int vexNum,arcNum;
	int kind;
}Algraph;

//������������������������������������������������������
typedef struct Arc
{
	int pre;//����һ���
	int next;//����һ���
	int weight;//����Ȩ
	bool isVisited;//��ǻ��Ƿ񱻷��ʹ�
}Edg;

int CreatMGraph_L(MGraph_L &G,int* data,int dim)//����ͼ���ڽӾ����ʾ
{
	G.vexNum=7;
	G.arcNum=9;
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j!=G.vexNum;++j)
		{ 
			G.adjMatrix[i][j].weight=INT_MAX;
		}
			
		_itoa_s( i, &G.vexs[i],8,10);

		for(int j=0;j<dim;j++)
		{
			if(data[dim*i+j]<INT_MAX)
			{
				G.adjMatrix[i][j].weight=data[dim*i+j];
				G.adjMatrix[j][i].weight=data[dim*i+j];
			}
		}
	}
	return G.vexNum;
}

void CreatAdj(Algraph &gra,MGraph_L G)//���ڽӱ�洢ͼ
{
	EdgeNode *arc;
	for(int i=0;i<G.vexNum;++i)
	{
		gra.vertices[i].vertex=G.vexs[i];
		gra.vertices[i].firstEdge=NULL;
	}
	for(int i=0;i<G.vexNum;++i)
	{
		for(int j=0;j<G.vexNum;++j)
		{
			if(gra.vertices[i].firstEdge==NULL)
			{
				if(G.adjMatrix[i][j].weight>0&&G.adjMatrix[i][j].weight<INT_MAX&&j<G.vexNum)
				{
					arc=new EdgeNode();
					arc->adjvex=j;
					arc->weight=G.adjMatrix[i][j].weight;
					arc->next=NULL;
					gra.vertices[i].firstEdge=arc;
				}
			}
			else
			{
				if(G.adjMatrix[i][j].weight>0&&G.adjMatrix[i][j].weight<INT_MAX&&j<G.vexNum)
				{
					arc=new EdgeNode();
					arc->adjvex=j;
					arc->weight=G.adjMatrix[i][j].weight;
					arc->next=gra.vertices[i].firstEdge;
					gra.vertices[i].firstEdge=arc;
				}
			}
		}
	}
	gra.vexNum=G.vexNum;
	gra.arcNum=G.arcNum;
}



int Find(int adjNode[],int f)//��δ�����ʹ��Ļ����±�
{
	while(adjNode[f]>0)
	{
		f=adjNode[f];
	}
	return f;
}

void Kruscal_Arc(MGraph_L G,Algraph gra)
{ 
	//��ʼ��edgs����
	Edg edgs[20];
	int k=0;
	for(int i=0;i<G.vexNum;++i)
	{
		for(int j=i;j<G.vexNum;++j)
		{
			if(G.adjMatrix[i][j].weight<INT_MAX)
			{
				edgs[k].pre=i;
				edgs[k].next=j;
				edgs[k].weight=G.adjMatrix[i][j].weight;
				edgs[k].isVisited=false;
				++k;
			}
		}
	}

	int preMIN,nextMIN,weightMIN,indexMIN,begG,endG;
	for(int i=0;i<gra.arcNum;++i)
		adjNode[i]=0; 
	for(int j=0;j<G.arcNum;++j)
	{
		//Ѱ��weightֵ��С��edges,������С��
		weightMIN=INT_MAX;
		for(int i=0;i<G.arcNum;++i)
		{
			if(!edgs[i].isVisited&&edgs[i].weight<weightMIN)
			{
				weightMIN=edgs[i].weight;
				preMIN=edgs[i].pre;
				nextMIN=edgs[i].next;
				indexMIN=i;
			}
		}
		
		begG=Find(adjNode,preMIN);
		endG=Find(adjNode,nextMIN); 
		edgs[indexMIN].isVisited=true;
		if(begG!=endG)//������ͨ��ͼ
		{
			for(int i=0;i<gra.vexNum;i++)
			{
				cout<<i<<":"<<adjNode[i]<<", ";
			}
			
			adjNode[begG]=endG;//���begG���ڽӽڵ�ΪendG
			/*cout<<begG<<","<<endG<<endl;*/
			cout<<"("<<preMIN<<","<<nextMIN<<")"<<weightMIN;
			cout<<endl;
		}
	}
}

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
