// Tarjan算法
// q个查询，n个节点， dfs复杂度n, 查询复杂度q*1 => n + q
// LCA 在更低的深度相遇，

Query query[MAXN] // 查询关系 

int fa[MAXN]; //并查集
bool visited[MAXN]; //标记是否已经访问
void init () {
	for i = 1:MAXN {
		fa[i] = i;
		visited = false;
	}
}

// u is root 
// dfs遍历, i-j有查询关系，当处理完i时，查看是否已经处理完j, 若已经处理完，则i和j都已经dfs访问过,且j在i前面访问
// 若j is i的祖先，j不可能在i访问前被访问完
// 因此j is i的兄弟或兄弟孩子，沿着并查集向上找到共同的根, 因为i和j处于不同分支系，当访问到i时j的分支系应该已经全部处理完了(dfs特征)
// 因此沿着j向上找LCA
// 因为子节点处理完才会合并，因此dfs搜索下并查集找到的根是更深的根是LCA(即找到的节点是此节点的所有子树已经处理完，当找到root时所有子树已经处理完)
// 完成时间根晚于孩子，因此此算法保证了find的节点在更低深度
// 此算法不时两路向上找，而是先完成的j的并查集保存最低的fa[j]

// 此算法是离线算法，即所有查询提前知道，在dfs搜索中解答，若已经搜索完成则i-j查询，i和j的find(i) == find(j) = root节点
// 此时已经不能处理了，当dfs搜索完成时，只能i-j节点向上找，然后相遇 ,在线算法就是这样的思想
// dfs处理为节点标记深度，然后根据深度信息两个节点向上找, 找到LCA

int find(u) {
	while(fa[u] != u) u=fa[u];
	return u;  //还没有visited的节点fa[u] == u;
}

void Tarjan(u) {
	for v in edge[u] { // v时u的所有子节点
		Tarjan(v); // dfs
		visited[v] = true; // v访问完了
		fa[v] = u; //并查集，v指向u, 子指向父
	}

	 e in query[u] { // e时和u有查询关系的节点
		if (visited[e]) {
			query[u][e].result = find(e); // lca
		}
	}
 }

// 在线算法
// 如果节点w是节点u和节点v的最近公共祖先的话，让u往上走(depth(u)-depth(w))步，让v往上走(depth(v)-depth(w))步，都将走到节点w
// 倍增算法，在两个路径上利用二分搜索

Edge edge[MAXN]; // 边
// dfs过程中计算fa和dep
fa[MAXN][ceil(og2(MAXN))], dep[MAXN]; // fa的第二维大小不应小于log2(MAXN)
bool visted[MAXN];
void dfs(u, father, depth = 0) {
	if(visited[u]) return;

	visited[u] = true;
	fa[u][0] = father;
	for i = 1 : log2(depth) {
		fa[u][i] = fa[fa[u][i-1]][i-1]
	}

	for v in edge[u] { // v时u的所有子节点
		dfs(v, u, depth + 1);
	}
}

/*
 *why log2?
 *
 * fa[p][0] is p-father                       
 * fa[p][1] is p-father-father
 * fa[p][2] is p-father-father-father      
 *             4  3       2     1
 * fa[p][3] is p-father-father-father-father     
 *   		   5  4       3     2      1
 * 二分查找 
 *		2^K = 5
 *		2^（K-1） = 2
 *		2^（K-2） = 0
 *	K--相当于 K/=2
*/

int online_lca(p, q, root) {
	if(!preprocess) dfs(root, root);

	// 保证p深度更深
	if(dep[p] < dep[q]) swap(p ,q);
    // 调整p和q一样深
	while(dep[p] != dep[q])  {
		dis = dep[q]-dep[p];
		p = fa[p][log2(dis)];
	}

	if(p == q) return p;  //祖先关系
	//不同分支，现在处于相同depth,一起向上探索
	for (k = log2(dep[p]; k >= 0 ; k--) {
			if (fa[p][k] != fa[q][k]) { //不能等于，等于表示已经越过或恰好处于公共祖先位置，向上找最大步数保证恰好lca子节点的位置
				p = fa[p][k], q= fa[q][k];
			}
	}
	return fa[p][0];
}
