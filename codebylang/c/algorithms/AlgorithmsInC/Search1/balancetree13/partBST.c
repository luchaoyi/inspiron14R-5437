
/*
	平衡一颗二叉树可以 利用划分 递归的将二叉树划分将中值放在根节点
*/

link balanceR(link h)
{
	if(h->N<2) return h;
	
	h=partR(h,h->N/2);
	
	//划分R调整树
	
	//向下递归
	//对子树做同样的动作
	h->l=balanceR(h->l);
	h->r=balanceR(h->r);
	
	return h;
}

