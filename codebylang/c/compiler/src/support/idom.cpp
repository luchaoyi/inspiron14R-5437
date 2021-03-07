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
void Link(node p, node n) {
	ancestor[n] = p;
	best[n] = n;
}

void LTIDom() {
	bucket = [[]...];

	DFS(none ,root);
	// dfnum反序号遍历, 从后向前算
	for i = N - 1 : 1:
		n = vertex[i];
		p = parent[p];
		for v in precessor(n)：
			if dfnum[v] <= dfnum[n]:
				s'= v
			else s' = semi[AncestorWithLowestSemi(v)]  //从v起始的旁路回溯找dfnum最小的semi节点
			if dfnum[s'] < dfnum[s]:
				s = s'
		semi[n] = s

		bucket[s] = bucket[s] U {n};  // 记录了s sdom的所有节点
		Link(p, n);

		// p sdom v是之前已经发现的，但没有立即计算idom
		// 直到Link(p,n)后计算idom
		// idom计算被延后

		for v in bucket[p]: // p sdom v
			y = AncestorWithLowestSemi(v);  //从v-semi(v)的生成树路径上寻找dfnum最小的节点
			if semi[y] = semi[v]:
				idom[v] = p
			else
				samedom[v] = y    //记录idom[v] = idom[y]的关系，因为此时idom[y]还没有计算出来
								// 因为倒着算此时idom[y]还没有算出来
	for i = 1 to N-1:
		n = vertex[i]
		if samedom[n] != none:
			idom[n] = idom[samedom[n]]
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
