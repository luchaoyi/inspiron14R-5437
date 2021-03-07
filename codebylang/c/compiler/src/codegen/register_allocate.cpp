//局部分配自定向下
struct Class {
	int Size; // Size个寄存器
	int Name[Size]; // Vreg Name
	int Next[Size]; //下一次使用处的距离
	int Free[Size]; // 物理寄存器使用状态
	
	int Statck[Size];
	int StackTop;
};

// 保证vr值在寄存器中
Ensure(vr, RegClass) {
	// vr已经分配了寄存器
	if (vr == RegClass.Name[Rx])
		return Rx;
	else 
	// 否则分配一个. 并生成移动值到Rx的代码
		Rx = Allocate(vr RegClass);
		emit code to move vr into Rx 
}

Allocate(vr, RegClass) {
	// 有空闲Reg 直接取
	if (RegClass.StackTop >= 0)  i = pop(RegClass);
	else {
		//没有空闲Reg, 选择一个占用淘汰
		//选择一个下一次使用距离最远的淘汰(最近不使用)
		i = j that max RegClass.Next[j]
		store j -> RAM
	}
	RegClass.Name[i] = vr; //vr占据寄存器i, 即vr 分配的寄存器位i
	RegClass.Next[i] = -1;
	RegClass.Free[i] = false;
};

// 释放第Rx寄存器
Free(Rx, RegClass) {
	RegClass.Name[Rx] = ""; //vr占据寄存器i, 即vr 分配的寄存器位i
	RegClass.Next[Rx] = +inf;
	RegClass.Free[Rx] = true;
	push(Rx, RegClass.Stack);
}

// 根据下一次引用距离为参考淘汰reg
// 反向遍历一遍可得到Dist(Vr)
 main {
	for op i in Block {
		op i is vri3 = vri1 op vri2;
		Rx = Ensure(vri1 , RegClass);
		Ry = Ensure(vri2 , RegClass);
		if vri1 is not need:
			Free(Rx, RegClass)
		if vri2 is not need:
			Free(Ry, RegClass)
		Rz = Allocate(vri3, RegClass); 
		Rewrite op Rz = Rx op Ry;
		// 为需要驻留z的已经分配的寄存器，写下一次引用位置距离，作为淘汰时的参考
		if vri1 is  need:
			RegClass.Next[Rx] = Dist(vri1); 
		if vri2 is  need:
			RegClass.Next[Rx] = Dist(vri2); 
		RegClass.Next[Rz] = Dist(vri3); 
	}
}
//==========================================
//全局分配
BuildConflictGraph(G={V, E}) {
	//每个活动范围一个节点，每个活动范围要分配一个寄存器
	For each LRi {
		G.V.append(ni);
	}

	for block in blocks {
		LiveNow = LiveOut(block); //block末尾的活跃变量
		for opi in block:
			opi is LRc = LRa, LRb; // 基本块内指令在求活跃范围是变量名字被重写为活动范围的名字

		// 根据定义一个在另一个的定义处活跃时有冲突
		// 对LRc定值处是LRc区间开始处，在此处依然活跃的活动区间和LRc有冲突
		for each LRi 属于LiveNow {
			G.E.append(Edge (LRc, LRi))
		}
		LiveNow.remove(LRc);
		LiveNow.append(LRa);
		LiveNow.append(LRb);
	}
}


BottomToTop(G = (V,E)) {

	while(true) {
		Stack= []
			while(V is not empty) {
				if (存在节点v 属于V的的度数 <k) {
					node = v;
				} else {
					node = Pick(G(V,E)); // 以某种外部条件选择一个受限节点删除, 逐出度量cost/degree
				}
				//从图删除v
				G.remove(v);
				// 度小的先入栈
				Stack.push(v);
			}

		while(Stack is not empty) {
			node = Stack.pop();
			// 重建图中选择着色
			insert node and its edges into G; //重建图
			Color(node); //着色
		}

		if (G图中都着色成功了){
			break;
		} else {
			逐出或拆分未着色的活动范围，降低冲突度,// 两一个角度逐出释放节点的颜色，使其它节点可着色
		}
	}
}
