#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Sudoku.h"
#include "stale.h"

Sudoku::Sudoku() 
: file_save1("file_save1.txt"), file_save2("file_save2.txt"), file_save3("file_save3.txt"), przesuniecie(0){
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
		{
			random_num[i][j] = 0;
		}
	}

}

Sudoku::~Sudoku(){

}

//losowanie pierwszego rzedu planszy
void Sudoku::firstRow() {
	for (int i = 0; i < N; i++) {
		while (Sudoku::random_num[0][i] == 0) {
			random_num[0][i] = rand() % 9 + 1;
			if (i == 0)break;
			for (int j = 0; j < N; j++) {
				if (random_num[0][j] == random_num[0][i] && i != j) {
					random_num[0][i] = 0;
					break;
				}
			}
		}
	}
}

//przesuniecie rzedow
void Sudoku::moveRows(int p, int j) {
	for (int i = 0; i < N; i++) {
		int prz = i + p;
		if (prz > 8) {
			prz = prz % 9;
		}
		random_num[j + 1][prz] = random_num[j][i];
	}
}

//podmiana losowa rzedow
void Sudoku::rowColSwap() {
	int tmp1 = 0, tmp2 = 0;
	for (int j = 0; j < N; j+=3){
		do {
			tmp1 = rand() % 3 + j;
			tmp2 = rand() % 3 + j;
		} while (tmp1 == tmp2);
		for (int i = 0; i < N; i++) {
			int tmp = random_num[tmp1][i];
			random_num[tmp1][i] = random_num[tmp2][i];
			random_num[tmp2][i] = tmp;
		}
	}
	for (int j = 0; j < N; j += 3) {
		do {
			tmp1 = rand() % 3 + j;
			tmp2 = rand() % 3 + j;
		} while (tmp1 == tmp2);
		for (int i = 0; i < N; i++) {
			int tmp = random_num[i][tmp1];
			random_num[i][tmp1] = random_num[i][tmp2];
			random_num[i][tmp2] = tmp;
		}
	}

}

//wpisanie zer w plansze jako puste pola
void Sudoku::podmianaNaZero(int n) {
	int liczby;
	if (n == 1) { liczby = 60; }
	else if (n == 2) { liczby = 50; }
	else if (n == 3) { liczby = 40; }
	else if (n == 4) { liczby = 35; }
	else if (n == 5) { liczby = 30; }
	for (int k = 0; k < 81-liczby; k++) {
		int i = rand() % 9;
		int j = rand() % 9;
		if (random_num[i][j] == 0) k--;
		else random_num[i][j] = 0;
	}
}

//sprawdzenie wygenerowanego sudoku czy jest prawidlowe
void Sudoku::sudokuSolver() {
	for (int z = 0; z < 6; z++){
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				int check = 0;
				int end;
				if (random_num[i][j] == 0) {								// jesli wpisana liczba nie jest zerem jest jej przypisywana kolejna liczba do sprawdzenia
					for (int k = 1; k < 10; k++) {
						int licz = k;
						random_num[i][j] = licz;
						int col = columnCheck(i, j, licz);
						int row = rowCheck(i, j, licz);
						int squ = squareCheck(i, j, licz);
						if (col*row*squ != 0) {
							end = licz;
							check++;
						}
					}
				if (check == 1) random_num[i][j] = end;
				else random_num[i][j] = 0;
				}
			}
		}
	}
}

//wygenerowanie calosci sudoku
void Sudoku::sudokuGenerator() {
	Sudoku::firstRow();
	for (int i = 0; i < 8; i++) {
		if (i == 2 || i == 5) { Sudoku::moveRows(1, i); }
		else { Sudoku::moveRows(3, i); }
	}
	Sudoku::rowColSwap();

}

int Sudoku::columnCheck(int i, int j, int licz) {
	for (int l = 0; l < N; l++) {
		if (i != l && random_num[i][j] == random_num[l][j]) {	//sprawdzanie poprawnosci w pionie
			licz = 0;
			random_num[i][j] = 0;
		}
	}
	return licz;
}

int Sudoku::rowCheck(int i, int j, int licz) {
	for (int l = 0; l < N; ++l) {
		if (j != l && random_num[i][j] == random_num[i][l]) {	//sprawdzanie poprawnosci w poziomie
			licz = 0;
			random_num[i][j] = 0;
		}
	}
	return licz;
}

// sprawdzenie poprawnosci kwadratu
/*
+--+--+--+
|00|01|02|
+--+--+--+
|10|11|12|
+--+--+--+
|20|21|22|
+--+--+--+
*/
int Sudoku::squareCheck(int i, int j, int licz) {
	int k;
	int m;
	if (i < 3 && j < 3)	{//jesli prawda to kwadrat 00
		k = 0;
		m = 0;
	}
	else if (i < 3 && j > 2 && j < 6)  {//jesli prawda to kwadrat 01
		k = 0;
		m = 3;
	}
	else if (i < 3 && j > 5) {//jesli prawda to kwadrat 02
		k = 0; 
		m = 6;
	}
	else if (i > 2 && i < 6 && j < 3) {//jesli prawda to kwadrat 10
		k = 3;
		m = 0;
	}
	else if (i > 2 && i < 6 && j > 2 && j < 6) {//jesli prawda to kwadrat 11
		k = 3;
		m = 3;
	}
	else if (i > 2 && i < 6 && j > 5) {//jesli prawda to kwadrat 12
		k = 3;
		m = 6;
	}
	else if (i > 5 && j < 3) {//jesli prawda to kwadrat 20
		k = 6;
		m = 0;
	}
	else if (i > 5 && j > 2 && j < 6) {//jesli prawda to kwadrat 21
		k = 6;
		m = 3;
	}
	else if (i > 5 && j > 5) { //jesli prawda to kwadrat 22
		k = 6;
		m = 6;
	}
	for (int l = k; l < k + 3; l++){
		for (int n = m; n < m + 3; n++){
			if (l == i && n == j) continue;
			else if (random_num[i][j] == random_num[l][n]) {
				licz = 0;
				random_num[i][j] = 0;
				return licz;
			}
		}
	}
	return licz;
}

//getter planszy
int Sudoku::getRandom(int i, int j) {
	return random_num[i][j];
}

//getter nazwy pliku
char* Sudoku::getFileName(int n) {
	char file_name[15];
	if (n == 1) strcpy(file_name, file_save1);
	else if (n == 2) strcpy(file_name, file_save2);
	else if (n == 3) strcpy(file_name, file_save3);
	return file_name;
}

