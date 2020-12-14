
//根据跳转指令标识basic block首指令
void MarkFirst() {
	for (auto& code: codes) {
		if (code.isJmp() || code.isJcond()) {
			code.setFirst();
			code.next()->setFirst(); 
		}
	}
}

class Block {
public:
	list<Inst*> insts; //指令序列
	list<Block*> prevs; //<-
	list<Block*> succs; //->
	
	Block(list<Inst*> &codes) {
		for(auto& code : codeList) {
			code.block = this; //记录指令所在block
			insts.push_back(code);
		}
	}

};

class DFG {
public:
	vector<Inst*> codeList; //构造流图的中间代码
	vector<Block*> blocks;
}

createBlocks() {
	vector<Inst*> tmpList;
	for(auto& code : codeList) {
		if(code.isFirst()) {
			blocks.push_back(new Block(tmpList));
			tmpList.clear();
		}
		tmpList.push_back(code);
	}
	blocks.push_back(new Block(tmpList)); //最后一块
}

//block -> DFG 
void linkBlock() {
	// 遍历生成的block
	for (auto& block : blocks) {
		Inst* last_inst = block.insts.back(); //获取块最后一条指令，寻找跳转目标
		if (last_inst.isJmp() || last_inst.isJcond()) {
			//new Block时每条指令都知道自己所属基本块，因此根据跳转目标指令可查到目标基本块
			Block *tar = last_inst.getTarget().Block();
			tar->prevs.push_back(block);
			block.succs.push_back(*tar); 
	} else {
		//顺序后面
		block.succs.push_back(block.next());
		block.next().prevs.push_back(block);
	}
}

//根据变量活跃性构造冲突图，然后图着色
//从度最大的节点开始着色，贪心算法,不能着色的节点不需spill到内存
struct Node {
	Var* var;
	int degree;
	int color; //节点颜色
	Set exColors;  //节点排斥的颜色集合,某节点着色会导致所有邻接节点排斥此颜色
	Vector<Node*> links;
};

//peephole 是模式匹配，滑动窗口滑过指令序列，在每个窗口内寻找预定义的模式，匹配后转换指令
