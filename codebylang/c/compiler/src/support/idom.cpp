N = 1

int dfnum[MAX];
int parent[MAX];
int vertxt[MAX]; //第N个访问的节点是?

int ancestor[MAX];
int best[MAX];

// parent is p, visit n 
void DFS(node p, node n) {
	if dfnum[n] == 0 {
		dfnum[n] = N;
		vertex[N] = n;
		parent[n] = p;
		N +=1;
		for n的每一个后继w:
			DFS(n ,w)
	}
}

// 带路径压缩的
// v -->a -->aa
// 将v的祖先直接指向到aa
// best[v] 标记的是从v->ancestor[v]路径上dfnum[semi[]]最小的节点
// 更新ancestor[v] 为aa的同时,需要将路径v->a和 a->aa之间选择一个更小的更新到best[v]
void AncestorWithLowestSemi(v) {
	a = ancestor[v];
	if ancestor[a] != none
		b = AncestorWithLowestSemi(a);
	    ancestor[v] = ancestor[a];
	// b vs best[v]
	if dfnum[semi[b]] < dfnum[semi[best[v]]]
		best[v] = b
	return best[v]
}

// link ancestro[i]构成并查集
void Link(node p, node n) {
	ancestor[n] = p;
	best[n] = n;
}

void LTIDom() {
	bucket = [[]...];

	DFS(none ,root);
	// dfnum reverse preorder 遍历, 因为semi/idom都需要沿dfs tree回溯(逆dfs先序),因此逆先序保证parent节点的semi已经计算过
	for i = N - 1 : 1:
		n = vertex[i];
		p = parent[n];
		for v in precessor(n)：
			//init s', 对于孤儿节点semi and idom is self
			s' = v
			if dfnum[v] <= dfnum[n]:
				s'= v
			else s' = semi[AncestorWithLowestSemi(v)]  //从v回溯到达v的旁路path节点的dfs路径找dfnum(semi(u))最小节点u
			if dfnum[s'] < dfnum[s]:
				s = s'
		semi[n] = s

		bucket[s] = bucket[s] U {n};  // 记录了s sdom的所有节点
		Link(p, n); //将已经计算处semi的节点沿着dfs tree link起来
		//link 链路是节点n的一系列已经计算出semi的祖先节点

		// p sdom v是之前已经发现的，但没有立即计算idom
		// 直到Link(p,n)后计算idom
		// idom计算被延后

		for v in bucket[p]: // p sdom v      
			y = AncestorWithLowestSemi(v);  //从v沿着link寻找v dfs生成树路径一系列祖先节点寻找dfnum(semi())最小的节点
			if semi[y] = semi[v]:
				idom[v] = p //idom[v] = semi[v]
			else
				samedom[v] = y    //记录idom[v] = idom[y]的关系，因为此时idom[y]还没有计算出来
								// 因为倒着算此时idom[y]还没有算出来
								//
	for i = 1 to N-1:
		n = vertex[i]
		if samedom[n] != none:
			idom[n] = idom[samedom[n]]

/*
		for v in bucket[p]: // p sdom v      // 公式上表示从v找到semi(v), 在v-semi(v)之间的节点的semi, semi(v) is  v的祖先节点之一，因此可以沿着link搜索
			y = AncestorWithLowestSemi(v);  //从v沿着link寻找v dfs生成树路径一系列祖先节点寻找dfnum最小的节点
			if semi[y] = semi[v]:
				idom[v] = p
			else
				idom[v] = y    // 优化实现使用idom计算samedom关系

	for i = 1 to N-1:
		n = vertex[i]
		if idom[n] != semi[n]:
			idom[n] = idom[idom[n]]
 
*/

}


void SemiNCA() {
	// LT的求sdom
	DFS(none ,root);
	// dfnum reverse preorder 遍历, 因为semi/idom都需要沿dfs tree回溯(逆dfs先序),因此逆先序保证parent节点的semi已经计算过
	for i = N - 1 : 1:
		n = vertex[i];
		p = parent[n];
		for v in precessor(n)：
			//init s', 对于孤儿节点semi and idom is self
			s' = v
			if dfnum[v] <= dfnum[n]:
				s'= v
			else s' = semi[AncestorWithLowestSemi(v)]  //从v回溯到达v的旁路path节点的dfs路径找dfnum(semi(u))最小节点u
			if dfnum[s'] < dfnum[s]:
				s = s'
		semi[n] = s

		bucket[s] = bucket[s] U {n};  // 记录了s sdom的所有节点
		Link(p, n); //将已经计算处semi的节点沿着dfs tree link起来
		//link 链路是节点n的一系列已经计算出semi的祖先节点

	//Fast Idom的改进
	//注意此迭代时自顶向下的生成idom tree使用先序
	//preorder
	//idom tree的顶点dfs序号都是从小到达的，semi(v)一定时v的父节点因此dfnum序号绝对大于v
	//因此从小的向上找到第一个小于d等于semi(v)的即是NCA
	//特殊有序号的树的NCA不需要使用普通方法
	for i = 1 : N-1:
		v = vertext[i]
		while dfnum[idom[v]] > dfnum[semi[v]]:
			idom(v) = idom[idom[v]]
}

// -------------------------------------
//基于数据流迭代改进的快速算法
//思想使用idom节点到根的路径代表dom集合
//数据流dom集合的交集表现为路径上的公共祖先
//--------------------------------------

int IDoms[MAX];
int RPO[MAX];

void FastIdom() {
	for all b in blocks:
		IDoms[b] = none;
	IDom[b0] = b0;
	Changed = true;
	while(Changed) {
		Changed =false
		for i in RPO { // RPO顺序遍历
			b =blocks[RPO[i]];
			p'= b的前驱中已经处理过计算出来Idom的节点第一个
			NewIdom = IDoms[p']
			for p in b的其它前驱 {
				if IDoms[p] != none:
					NewIdom = Intersect(p, NewIdom)
			}
			if IDoms[b] != NewIdom:
				IDoms[b] = NewIdom;
				Changed = true;
		}
	}
}

//从某节点到根表示一个集合，则集合的交集表示为LCA/NCA
// 最简单的LCA算法, 没有level ,利用RPO顺序，交替上升
// 有level的LCA搜索速度更快不用交替,而是上升到同一个level以后一起上升，还可以二分搜索
void InterSect(i, j) {
	f1 = i;
	f2 = j;
	while(f1 != f2) {
		while(RPO(f1) > RPO(f2))
			f1 = IDoms[f1];
		while(RPO(f2) > RPO(f1))
			f2 = IDoms[f2]
	}
	return f1 
}
