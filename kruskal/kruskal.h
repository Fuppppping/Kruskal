#include <fstream>
#include <iostream>
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

typedef struct //ͼ���ڽӾ����ʾ
{
	char vexs[20];
	int vexNum,arcNum;
	AdjMatrix adjMatrix;
}Graph_AdjMatrix;

typedef struct node//�����
{
	int adjvex;//�ڽӵ���
	struct node *next;//����
	int weight;
}EdgeNode;

typedef struct//�������
{
	char vertex;//������
	EdgeNode *firstEdge;//�߱�ͷָ��
}VertexNode;

typedef struct//ͼ�Ķ���
{
	VertexNode vertices[MAX];
	int vexNum,arcNum;
	int kind;
}Graph;

//������������������������������������������������������
typedef struct Arc
{
	int pre;//����һ���
	int next;//����һ���
	int weight;//����Ȩ
	bool isVisited;//��ǻ��Ƿ񱻷��ʹ�
}Edg;

class Kruskal
{
private:
	ofstream fout;

public:
	
};


int Create_Graph_AdjMatrix(Graph_AdjMatrix &gam,int* data,int dim)//����ͼ���ڽӾ����ʾ
{
	gam.vexNum=7;
	gam.arcNum=9;
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j!=gam.vexNum;++j)
		{ 
			gam.adjMatrix[i][j].weight=INT_MAX;
		}
			
		_itoa_s( i, &gam.vexs[i],8,10);

		for(int j=0;j<dim;j++)
		{
			if(data[dim*i+j]<INT_MAX)
			{
				gam.adjMatrix[i][j].weight=data[dim*i+j];
				gam.adjMatrix[j][i].weight=data[dim*i+j];
			}
		}
	}
	return gam.vexNum;
}

void CreatAdj(Graph &gra,Graph_AdjMatrix gam)//���ڽӱ�洢ͼ
{
	EdgeNode *arc;
	for(int i=0;i<gam.vexNum;++i)
	{
		gra.vertices[i].vertex=gam.vexs[i];
		gra.vertices[i].firstEdge=NULL;
	}
	for(int i=0;i<gam.vexNum;++i)
	{
		for(int j=0;j<gam.vexNum;++j)
		{
			if(gra.vertices[i].firstEdge==NULL)
			{
				if(gam.adjMatrix[i][j].weight>0&&gam.adjMatrix[i][j].weight<INT_MAX&&j<gam.vexNum)
				{
					arc=new EdgeNode();
					arc->adjvex=j;
					arc->weight=gam.adjMatrix[i][j].weight;
					arc->next=NULL;
					gra.vertices[i].firstEdge=arc;
				}
			}
			else
			{
				if(gam.adjMatrix[i][j].weight>0&&gam.adjMatrix[i][j].weight<INT_MAX&&j<gam.vexNum)
				{
					arc=new EdgeNode();
					arc->adjvex=j;
					arc->weight=gam.adjMatrix[i][j].weight;
					arc->next=gra.vertices[i].firstEdge;
					gra.vertices[i].firstEdge=arc;
				}
			}
		}
	}
	gra.vexNum=gam.vexNum;
	gra.arcNum=gam.arcNum;
}



int Find(int adjNode[],int f)//��δ�����ʹ��Ļ����±�
{
	while(adjNode[f]>0)
	{
		f=adjNode[f];
	}
	return f;
}

void Kruscal_Arc(Graph_AdjMatrix gam,Graph gra)
{ 
	//��ʼ��edgs����
	Edg edgs[20];
	int k=0;
	for(int i=0;i<gam.vexNum;++i)
	{
		for(int j=i;j<gam.vexNum;++j)
		{
			if(gam.adjMatrix[i][j].weight<INT_MAX)
			{
				edgs[k].pre=i;
				edgs[k].next=j;
				edgs[k].weight=gam.adjMatrix[i][j].weight;
				edgs[k].isVisited=false;
				++k;
			}
		}
	}

	int preMIN,nextMIN,weightMIN,indexMIN,begG,endG;
	for(int i=0;i<gra.arcNum;++i)
		adjNode[i]=0; 
	for(int j=0;j<gam.arcNum;++j)
	{
		//Ѱ��weightֵ��С��edges,������С��
		weightMIN=INT_MAX;
		for(int i=0;i<gam.arcNum;++i)
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
