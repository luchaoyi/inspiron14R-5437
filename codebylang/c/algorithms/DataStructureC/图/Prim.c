
#define  INFINITY 10000 //�����

int MinEdge(PshorEdge shortEdge,vertexNum)
{
    int temp=INFINITY ;
    int j=-1;
/*
	Ҳ���ұߵĹ���
	���������ұ�
*/
}
void Prim(MGraph G)
{
	//��С���������ʾ����ҳ�������̱߽�ͼ���е�����
	
    //��ʼ����������
    //��������洢��̱��ڽӵ��Ȩֵ
    //i��������Ҫi-1��������
    for(i=1;i<G.vertex;i++)
    {
        shortEdge[i].lowcost=G.arc[0][i];

        shortEdge[i].adjvex=0;//��ʼ��V0��ʼ
    }
    shorEdge[0].lowcast=0;//��ǰ����뼯�ϼ���Լ���·��Ϊ0

    for(i=1;i<G.vertex;i++) //i��������Ҫi-1��������
    {
            k=MinEdge(shorEdge,vertexNum);//Ѱ�����
            shorEdge[k].lowcast=0;//��ǰ����뼯�ϼ���Լ���·��Ϊ0

            //�������ϵ�ǰ����
            //���ڼ��ϼ����µ���ǰΪ���·�����ԱȽ������µ�·�������̵�����
            //��������
           for(j=1;j<G.vertex;j++)
            if(G.arc[k][j]<shortEdge[j].lowcost)//�¼���㵽��������
            {
                    shortEdge[j].lowcost=G.arc[k][j];
                    shortEdge[j].adjex=k;//��������˵�����ĵ� j->k�ٽ� һ����̱�
                    
            }
    }




}
