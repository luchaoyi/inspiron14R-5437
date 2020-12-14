
/*
	查找的思想：有序有规律的查找容易，混乱的查找麻烦，所以若要追求查找速度
	应存储数据时应有规律的存储
	
	没有银弹，不要指望通用数据结构可以一劳永逸
	数据结构的设计应考虑应用场合的频率多的操作
	
	搜索：手指搜索，范围搜索，近邻搜索
*/


void STinit();
int STcount();
void STinsert(item);
item STsearch(key);
void STdelete(Item);
Item STselect(int);
void STsort(void(*visit)(Item));
