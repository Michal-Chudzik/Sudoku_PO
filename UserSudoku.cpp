#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "UserSudoku.h"
#include "Sudoku.h"

UserSudoku::UserSudoku() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++){
			plansza_poprawna[i][j] = 0;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++){
			plansza_zero[i][j] = 0;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++){
			user_input[i][j] = 0;
		}
	}
}

//generator sudoku
void UserSudoku::sudokuGen(int n) {
	int check = 0;
	do {
		Sudoku::sudokuGenerator();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				plansza_poprawna[i][j] = Sudoku::getRandom(i, j);
			}
		}
		Sudoku::podmianaNaZero(n);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				plansza_zero[i][j] = Sudoku::getRandom(i, j);
			}
		}
		Sudoku::sudokuSolver();
		check = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (Sudoku::getRandom(i, j) != plansza_poprawna[i][j]) check++;
			}
		}
	} while (check != 0);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			user_input[i][j] = plansza_zero[i][j];
		}
	}

}

//sprawdzenie czy uzytkownik nie wpisuje w zajete pole
int UserSudoku::checkTab(int x, int y) {
	if (plansza_zero[x][y] == 0) return 1;
	else return 0;
}

//ustawienie liczby podanej przez uzytkownika na podanym polu
void UserSudoku::setTab(int x, int y, int liczba) {
	user_input[x][y] = liczba;
}

//wypis sudoku
void UserSudoku::sudokuPrint() {
	int r[N][N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			r[i][j] = user_input[i][j];
		}
	}
	int licz = 0;
	printf("\t\t    0 1 2   3 4 5   6 7 8   y\n");
	printf("\t\t  +-------+-------+-------+\n");
	for (int i = 0; i < N; i++) {
		licz++;
		if (licz % 4 != 0) {
			printf("\t\t%d | ", i);
			for (int j = 0; j < N; j++) {
				if (r[i][j] != 0) {
					printf("%d ", r[i][j]);
				}
				else {
					printf(". ");
				}
				if (j % 3 == 2) printf("| ");
			}
			printf("\n");
		}
		else {
			printf("\t\t  +-------+-------+-------+\n");
			i--;
		}
	}
	printf("\t\t  +-------+-------+-------+\n");
	printf("\t\tx");
}

//zapis stanu gry w podanym przez uzytkownika pliku
void UserSudoku::saveFile(int n) {
	char file_name[15];
	strcpy(file_name, Sudoku::getFileName(n));
	FILE* save;
	save = fopen(file_name, "w");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fprintf(save, "%d", user_input[i][j]);
		}
		fprintf(save, "%s", "\n");
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fprintf(save, "%d", plansza_poprawna[i][j]);
		}
		fprintf(save, "%s", "\n");
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fprintf(save, "%d", plansza_zero[i][j]);
		}
		fprintf(save, "%s", "\n");
	}
	fclose(save);
	std::cout << "\nKoniec Programu";
}

//odczyt zapisu gry
void UserSudoku::openFile(int n) {
	char file_name[15];
	strcpy(file_name, Sudoku::getFileName(n));
	FILE* save;
	char tmp[1];
	save = fopen(file_name, "r");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fscanf(save, "%c", &tmp);
			user_input[i][j] = atoi(tmp);
		}
		fscanf(save, "%c", &tmp);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fscanf(save, "%c", &tmp);
			plansza_poprawna[i][j] = atoi(tmp);
		}
		fscanf(save, "%c", &tmp);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fscanf(save, "%c", &tmp);
			plansza_zero[i][j] = atoi(tmp);
		}
		fscanf(save, "%c", &tmp);
	}
}

// sprawdzenie poprawnosci sudoku wpisywanego przez uzytkownika
int UserSudoku::checkUserSudoku() {
	int check = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (user_input[i][j] != plansza_poprawna[i][j]) {
				if (check == 0) {
					printf("Bledne liczby sa w okienkach o indeksach:\n");
				}
				printf("[%d][%d], ", i, j);
				check++;
				if (check % 9 == 0)putchar('\n');
			}
		}
	}
	if (check == 0) {
		printf("Gratuluje! udalo ci sie bezblednie rozwiazac sudoku!.\n");
		printf("Dziekuje za gre.");
		printf("\n\nKoniec programu.");
		return 0;
	}
	else {
		printf("\nNie zgadzalo sie %d liczb.", check);
		return 1;
	}
}
