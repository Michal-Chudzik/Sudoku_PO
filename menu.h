#pragma once
#include "Sudoku.h"

class Menu:public Poli {
public:
	Menu();
	int startMenu();
	virtual int start();
	void fill();
	int fillMenuX();
	int fillMenuY();
	int fillMenuN(int, int);
	int endCheck();
	int end();
	template<int min, int max>
	int kontrola() {
		int wpisana;
		while (scanf_s("%d", &wpisana) != 1 || wpisana < min || wpisana > max || getchar() != '\n') {
			std::cout << "Bledny wybor, wybierz ponownie.\nWybor: ";
			while (getchar() != '\n');
		}
		return wpisana;
	}
	void powo();
};
