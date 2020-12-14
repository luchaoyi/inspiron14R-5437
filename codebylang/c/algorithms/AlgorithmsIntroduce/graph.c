//单源点s最短路径
//松弛操作
def relax(u,v,w):
	if v.d>u.d+w(u,v)
		v.d=u.d+w(u,v)
		v.via=u


def bellman-ford(G,w,s):
	//最短路径是简单路径，不走环路所以s->任意v点最短路径最多经过所有点(|G.V|个点),即|G.V|-1条边
	//因此松弛|G.V-1|次
	for i=1 to |G.V|-1:
		for edge in G.E:
			relax(e.u,e.v,w)
	//检查，如果松弛后还存在更短，则存在负环路
	for edge in G.E:
		if v.d > u.d + w(u,v)
			return false
	return true

//差分约束可以根据约束列出一张图来
//找出图中最短路径权则为差分约束满足解
