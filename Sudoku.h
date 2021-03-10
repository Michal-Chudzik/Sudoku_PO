#pragma once
#include "stale.h"
#include "poli.h"

class Sudoku {
	int random_num[N][N];
	int przesuniecie;
	char file_save1[15];
	char file_save2[15];
	char file_save3[15];
public:
	Sudoku();
	~Sudoku();
	void firstRow();
	void moveRows(int, int);
	void rowColSwap();
	void podmianaNaZero(int);
	void sudokuSolver();
	void sudokuGenerator();
	int squareCheck(int, int, int);
	int rowCheck(int, int, int);
	int columnCheck(int, int, int);
	int getRandom(int, int);
	char* getFileName(int);
};
