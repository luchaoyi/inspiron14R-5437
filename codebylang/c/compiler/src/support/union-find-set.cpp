// 并查集每个节点指向根节点
int fa[MAXN];
// rank 标识集合节点个数，合并将简单的合并到复杂的
int rank[MAXN]; 

// 初始都指向自身
void init(int n) {
	for i = 1 : n {
		fa[i] = i;
		rank[i] = 1;
	}
}

// 搜索到根节点，除了根节点指向自身
int find(int x) {
	Statck s = {};
	int i = fa[x];
	while (i != fa[i]) {
		s.push(i); //记录路径遍历点
		i = fa[i];
	}
	//路径压缩
	for j in s {
		fa[j] = i;
	}
	return i;
}

// merge by rank
void merge(int i, int j) {
	int x = find(i);
	int y = find(j);
	if x == y return;

	if (rank[x] <=  rank[y])
		fa[x] = y;
	else 
		fa[y] = x;
	// ==时 x合并到y 
	if (rank[x] == rank[y]) rank[y]++;
}
