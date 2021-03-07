// Trie tree 字典树
int MAXN = 500000;
int next[MAXN][26], cnt; // 用类似链式前向星的方式存图，next[i][c]表示i号点所连、存储字符为c+'a'的点的编号
void init() // 初始化
{
    memset(next, 0, sizeof(next)); // 全部重置为0，表示当前点没有存储字符
    cnt = 1;
}
void insert(const string &s) // 插入字符串
{
    int cur = 1;
    for (auto c : s)
    {
        // 尽可能重用之前的路径，如果做不到则新建节点
		// 每插入一个新的节点编号递增一次
        if (!next[cur][c - 'a']) 
            next[cur][c - 'a'] = ++cnt; 
        cur = next[cur][c - 'a']; // 继续向下
    }
}

// 方便查询前缀/字符串是否存在，常用于搜索引擎词频统计，统计排序大量字符串
// 查询字符串存在需要一个exist['叶子'] = true, 使用叶子节点代表整个字符串
bool find_prefix(const string& s) {
	int cur = 1;
	for (auto c : s) {
		if !next([cur][c - 'a'] return false;
		cur = next[cur][c - 'a'];
	}
	return true;
}

// suffix tree
// 后缀树将字符串的所有后缀生成一个compacted-trie tree
//按定义的标准构造过程
//1. 生成字符串A的所有后缀
//2.利用所有后缀集合构造trie
//3.压缩trie得到compacted-trie 
 
//压缩简单，仅有一个孩子的字符节点可以压缩将子节点压缩到到此父节点
//考虑直接构造compacted trie, 分裂法，当不匹配时才分裂

// 若字符串B是A的子串，则B必为A后缀的前缀，B和A的几个后缀串匹配则重复出现几次
