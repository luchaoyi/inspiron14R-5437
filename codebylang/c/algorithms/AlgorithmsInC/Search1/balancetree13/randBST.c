/*
	随机化思想：引入随机决策可以降低奇葩的情况导致最坏结果发生的可能性
	对于运行不稳定的算法引入随机性是很有必要的
	
	
*/

/*
	随机决定在叶子节点插入或在根插入,随机BST还可以将输入序列打乱避免极端情况
*/
link insertR(link h,Item item)
{
	Key v=getkey(item), t = getkey(h->item); 
	
	if(h==z) return NEW(item,z,z,l);
	
	//随机决策
	if(rand<RAND_MAX/(h->N+1))
		return insertT(h,item);
	
	//*******************
	if(v<t) h->l = insertR(h->l,item);
	
	if(v>t) h->r = insertR(h->r,item);
	
	(h->N)++; return h;
	
	//*******************
}

void STinsert()
{
	head = insertR(head,item);
}





