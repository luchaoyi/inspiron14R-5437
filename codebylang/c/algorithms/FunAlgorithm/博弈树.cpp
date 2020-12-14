/*
棋类博弈:全信息(不存在信息不对称)，非偶然(理智行为，不存在失误运气),二人零和博弈.
MAX与MIN选择对自己最有利的局面.双方交替落子.
站在MAX角度，做极大极小值搜索,MAX交替选择极大极小值.
*/

//这一步选择最有利，这一步的局面评估来自与下一步评估最不利局面
//天然递归结构
//指定搜索深度，在时间与准确度之间折中
int MiniMax(node depth isMaxPlayer)
{
	//达到指定搜索深度
	if(depth==0)
	{
		return Evaluate(node);
	}
	int score=isMaxPlayer? -INF:INF;


	//每一个node代表折一个
	for_each(node 的子节点 child_node)
	{
		int value = MiniMax (child_node,depth-1,!isMaxPlayer);
		{
			if(isMaxPlayer)
				score=max(score,value);
			else
				score=min(score,value);
		}
	}

	return score;
}

//负极大搜索算法: 求极小值是，取反统一求极大值

int NegMax(node ,depth,color)
{
	//一个符号位指定+-
	if(depth==0)
		return color*Evaluate(node);

	int score = -INF;

	for_each(node每个子节点child_node)
	{
		int value = -NegaMax(child_node,depth-1,-color);
		score = max(score,value);
	}
	return score;
}


//alpha,beta剪枝通过提高下限剪枝
//得到的极大值若>alpha,
//beta最小值,降低beta 
//当节点alpha>=beta时该节点子节点评估不会对结果产生影响了.
//init alpha=-INF beta=INF 

int MinMax_AlphaBeta(node,depth,alpha,beta,isMaxPlayer)
{
	if(depth==0)
		return Evaluate(node);

	if(isMaxPlayer)
	{

		for_each(node每个子节点child_node)
		{
			int value=MinMax_AlphaBeta(node,alpha,beta,false);
			alpha=max(alpha,value);
			if(alpha>beta)
				break;
		}
		return alpha;
	}else
	{

		for_each(node每个子节点child_node)
		{
			int value=MinMax_AlphaBeta(node,alpha,beta,false);
			beta=min(beta,value);
			if(alpha>beta)
				break;
		}
		return beta;
	}
}

int NegMax_AlphaBeta(node,depth,color,alpha,beta)
{
	//一个符号位指定+-
	if(depth==0)
		return color*Evaluate(node);


	for_each(node每个子节点child_node)
	{
		//交替
		int value = -NegaMax(child_node,depth-1,-color,-beta,-alpha);
		alpha=max(alpha,value);
		if(alpha>=beta)
			break;
	}

	return score;
}

//递归穷举优化:1.记忆表 2.剪枝
//递归搜索增加置换表，将已经搜索过的信息存储在表中，下次搜索直接查表


