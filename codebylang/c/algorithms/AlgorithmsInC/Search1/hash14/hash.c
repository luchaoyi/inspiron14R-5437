/**
 *动态散列时每当表半满则加倍表长
 * 重新散列
 *
 * */

void STinsert(Item item)
{
	Key v = key(item);

	int i = hash(v,M);
	while(!null(i)) i=(i+1) % M; // 线性探测
	
	st[i] = item;

	if(N++>= M/2) expand();
}


void expand()
{
	int i ;
	Item *t =st;

	init(M+M);

	for (i=0;i<M/2;i++)
		if(key(t(i) !=ket(Nullitem))
				STinsert(t(i));

	
	free(t);

}


