#建立数学模型

typedef struct 
{
	int num;
	bool fixed;//状态,确定状态填数字，不确定有候选者列表 1:num 0:candidators 
	std::set<int> candidators;
}SUDOKU_CELL;

typedef struct 
{
	SUDOKU_CELL cells[SKD_ROW_LIMIT][SKD_COL_LIMIT];
	int fixed;//确定了的格子数目
}SUDOKU_GAME;

int SkipFixedCell(game,sp)
{
	//star 0 so -1
	int row=sp/SKD_COL_LIMIT -1;
	//从sp的下一个开始判断A
	//start 0 -->-1 next +1
	// col = sp%SKD_COL_LIMIT 
	int col=sp-row*SKD_COL_LIMIT; //(sp-row*SKD_COL_LIMIT-1+1)
	while(game[row][col].fixed==1)
	{
		sp++;
		col++;
		if(col>=SKD_COL_LIMIT)
		{
			col=0;
			row++;
		}
	}
	return sp;
}

void FindSudoKuSolution(SUDOKU_GAME *game,int sp)
{
	if(game->fixed == SKD_CELL_COUNT)
	{
		PrintResult(game);
		return ;
	}

	//指向要填入数字的单元格子,跳过填入数字的单元
	sp =SkipFixedCell(game,sp);
	if(sp>SKD_CELL_COUNT)
		return;

	int row=sp/SKD_COL_LIMIT -1;
	int col = sp%SKD_COL_LIMIT -1;

	SUDOKU_CELL * curCell = &game->cells[rwo][col];
	SUDOKU_GAME new state;

	std::set<int>::iterator it = curCell->candidators.begin();

	//在候选数中尝试数字
	//维护一个候选列表
	while(it!=curCell->candidators.end())
	{
		CopyGameState(game,&new_state);

		if(试数成功)
		{
			FindSudoKuSolution(&new_state,sp+1);
		}
		++it;
	}
}







