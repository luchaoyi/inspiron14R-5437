/*
PAPER: A Linear Time Algothrim Place Phi
*/

struct DomNode {
	bool visited = false;
	bool is_alpha = false; //alpha节点是算法初始集合节点
	bool in_phi = false;
	int level = 0;
};

struct BankNode {
	Node* node;
	Bank* next;
};
BankNode banks[NumLevel];
CurrentLevel = NumLevel -1;
CurrentRoot = nullptr;
IDF=[];

InserNode(x) {
	//头插法
	x.next = banks[x.level];
	banks[x.level] = x;
}

GetNode() {
	if (banks[CurrentLevel] != nullptr) {
		//从头部删除要处理的节点
		x = banks[CurrentLevel];
		banks[Current] = x.next;
		return x
	}

	for i = CurrentLevel downto 1 {
		if (banks[CurrentLevel] != nullptr) {
			CurrentLevel = i;
			//从头部删除要处理的节点
			x = banks[CurrentLevel];
			banks[Current] = x.next;
			return x
		}
	}
}

Visit(x) {
	// x->y
	for y in Succ(x)
		if(x->y is Jedge) {
			if (y.level <= CurrentRoot.level)A {
				if (!y.in_phi)
					IDF = IDF union y;
					if !y.is_alpha:
						InsertNode(y)

			}
		} else {
			//x->y is Dom edge
			if (!y.visited) {
				y.visited = true;
				Visit(y);
			}
		}
}
/*
 算法计算的是给定一组节点集合Nodes_Alpha的IDF(Nodes_Alpha)
 */
Main(Nodes_Alpha) {
	// Nodes_Alpha is init set for compute df
	for x in Nodes_Alpha {
		x.is_alpha = true;
		InsertNode(x);
	}

   while (x = GetNode()) ！= nullptr {
	   CurrentRoot = x;
	   x.visited = true;
	   Visit(x)
   }
}
