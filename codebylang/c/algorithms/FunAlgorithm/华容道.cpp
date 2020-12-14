typedef struct tagWARRIOR
{
	//2*2 1*2,2*1,1*1
	WARRIOR_TYPE type;//类型
	//左，上位置
	int left;
	int top;
}WARRIOR;

struct HRD_GAME_STATE 
{
	char board[HRD_BOARD_HEIGHT][HRD_BOARD_WIDTH];	
	std::vector<WARRIOR> heroes;
	MOVE_ACTION move; //动作
	int step; //移动次数
	HRD_GAME_STATE *parent;//上一个状态局
}

typedef struct tagMOVE_ACTION
{
	int heroIdx; //hero index 
	int dirIdx; //移动方向
}MOVE_ACTION;


/*
zobrist哈希算法:判断棋局重复
hash指纹,快速判重
1.对棋盘最小单位的每个状态分配随机编码值
2.对指定棋局，每个单位上状态编码值做xor运算 -->get一个hash值
hash值是所有格子xor产生的所以任意小状态改变都会改变最终结果
A^B^B=A  1001^1100=0101^1100=1001 
镜像棋局，对掉左右hash值相同
*/
