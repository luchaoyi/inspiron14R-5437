

int Min(/////)
{
    temp =INIF;
    j;
    for()
    {
        if(temp>dist[i]&&dist!=0)
        {
            temp=dist[i];
            j=i;
        }
    }
    return j;
}
//vΪ��ʼ������ҳ�v->������������·��
void Dijkstra(MGraph G,int v)
{
    for(i=0;i<G.verNum;i++)
    {
        dist=G.arc[v][i];
        //
        if(dist[i]!=INIF)//�����ɵ���
        ///path����dist��Ӧ v ->i��·��
            path[i]="v->i";
        else
            path[i]=" ";
    }
    
    //path[i]�����v������ÿ��������·�� 

    for(num=1;num<G.vertexNum;num++)
    {
        k=Min(dist);//���������ҵ���С

        printf(path[k]);
        
        //ɨ��һ��dist����
        for(i=0;i<G.vertexNum;i++)
        {
            if(dist[i]>dist[k]+G.arc[k][i])//���ֱ�ӵ���>���ӵ����ӵ���˵���ǿ�ѧ��
            {
                //̰�Ĳ��Բ�������
                //��ǰ��������ͨ�����ڻ���

                dist[i]=dist[k]+G.arc[k][i];

                path[i]="v->k->i"
            }
        }
        dist[k]=0;//�������·�����뼯��
        /// �˴�������Min��������������disk[i]=0;
        ///if(temp>dist[i]&&dist!=0)
    }

}
