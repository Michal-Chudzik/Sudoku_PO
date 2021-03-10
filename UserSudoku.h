#pragma once
#include "Sudoku.h"
#include "stale.h"
#include "poli.h"

class UserSudoku :public Sudoku {
	int plansza_poprawna[N][N];
	int plansza_zero[N][N];
	int user_input[N][N];
public:
	UserSudoku();
	void sudokuGen(int);
	int checkTab(int, int);
	virtual void setTab(int, int, int);
	void sudokuPrint();
	void openFile(int);
	void saveFile(int);
	int checkUserSudoku();
};

