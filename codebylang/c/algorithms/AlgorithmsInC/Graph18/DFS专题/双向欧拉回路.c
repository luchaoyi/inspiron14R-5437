//邻接表


/*
核心思想:双向欧拉回路时采用DFS单向搜索一遍
然后在递归返回时按一种方式访问回边
1.忽略回链接访问下链接
或
2.忽略下链接访问回链接
这里采用了2
*/
struct node{int v; link next;}
typedef struct node *link;

struct graph{int V;int E;link *adj;} *Graph;

cnt=0 //标记数组和计数器 cnt==0 
int pre[G->V];//pre[i]=-1;

void DoubleRuler(Grapg G,Edge e) 
{
	link t;
	//v--->i1--->i2...>w;
	
	//
	printf(e->w);
	
	//递归时是正向走打印v--->w
	w=e.w;
	pre[w]=cnt++;//记录访问顺序
	
	
	for(t=G->adj[w];t!=NULL;t=t->next)
		if(pre[t->v]==-1)
		{
			DoubleRuler(G,EDGE(w,t->v));
		}
		
		//此时递归返回逆向走w->v
		//此时从w->v,在v搜索t下条路没有都 访问过即为回边
		//当此时pre[t->v]<pre[e.v] 时v-->t的道路为回链接（正向递归访问时t的访问次序在v之前）
		//为回链接即t在v访问前访问过
		//p64
		else if(pre[t->v]<pre[e.v])
		{
			printf(->t->v,->e.w);	
		}
		
		if(e.v!=e.w)
		printf(->e.v)
}



