
//kruskal�㷨�Ա߲���
//���ñ߼�����洢
#define MAX_V  M //������
#define MAX_E  N //������


//�洢������ṹ
struct EdgeType
{
    int from,to,weight;

};

typedef struct
{
    DataType vertex[MAX_V];
    EdgeType  edge[MAX_E];
    int vertexNum,edgeNum;//������������
}EdgeGraph;

/// ///�Ա߼����鴦��ǰ��Ȩ���򣬿ɼӿ��ٶ�
//parent�����ʾ���˫�׽ڵ�

int Findroot(int parent[],int v)
    {

        if(parent[v]>-1)//˵�����и��ڵ�
            return parent[v];
        else
            return v;
    }

void Kruskal(EdgeGraph G)
{
    for(i=0;i<G.vertexNum;i++)
        parent[i]=-1;//��ʼ��
    for(num=0,i=0;i<G.edgeNum;i++)
    {
        vertex1=Findroot(parent,G.edge[i].from);
        vertex2=Findroot(parent,G.edge[i].to); //Ѱ����С�߸��ڵ�

        if(vertex1!=vertex2)//λ�ڲ�ͬ�������������
            //if== ��ͬ���ڵ�����������ֻ�
        {
            //���Ӵ˱�
            //����߻��ӡ��

            parent[vertex2]=vertex1;
            num++;
            if(num==n-1) break; //n�Ķ�������������Ҫ n-1����

        }


    }

}


