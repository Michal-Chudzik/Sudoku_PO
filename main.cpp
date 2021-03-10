#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <crtdbg.h>
#include <iostream>
#include "Sudoku.h"
#include "stale.h"
#include "menu.h"
#include "UserSudoku.h"
#include "poli.h"
#include "menuNew.h"

#define pokiUzytkownikNieWpisze16 1



int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand((unsigned int)time(NULL));
	Sudoku* s1 = new Sudoku;
	Menu* m = new Menu;
	MenuNew* mn = new MenuNew;
	UserSudoku* us = new UserSudoku;
	Poli* p;
	int sav = m->startMenu();						//uzytkownik decyduje czy chce zaczac nowa gre czy otworzyc plik zapisu z poprzedniej rozgrywki
	if (sav == 0) {
		p = mn;
		int dif = p->start();						//pytanie o poziom trudnosci
		us->sudokuGen(dif);							//wygenerowanie sudoku o wybranym poziomie trudnosci
	}
	else {
		p = m;
		int file = p->start();						//zaczniecie gry z pliku zapisu jesli istnieje, metoda zwraca numer pliku badz inne instrukcje
		if (file == 0) {
			std::cout << "Koniec programu.";
			delete s1;
			delete m;
			delete mn;
			delete us;
			return 0;								//zakonczenie programu jesli uzytkownik tak zadecydowal
		}
		else if (file == 4) {
			p = mn;
			int dif=p->start();								//tworzenie nowej rozgrywki w razie braku plikow z zapisem 
			us->sudokuGen(dif);
		}
		else {
			us->openFile(file);						//otwarcie pliku z zapisem i wpisanie wartosci do odpowiednich tablic
		}
	}
	m->powo();
	while (pokiUzytkownikNieWpisze16) {				//petla bedzie obracana do momentu wpisania w indeks X liczby 16 ktora wychodzi z petli i przechodzi do zamykania programu
		us->sudokuPrint();							//wypis sudoku do konsoli
		int x = -1;
		int y = -1;
		int c = 0;
		m->fill();									
		do {
			x = m->fillMenuX();							//wprowadzenie zmiennej X przez uzytkownika
			if (x == 16) break;
			y = m->fillMenuY();						//wprowadzenie zmiennej Y przez uzytkownika
			c = us->checkTab(x, y);					//sprawdzenie czy uzytkownik nie wpisuje w odpowiednie miejsce
			if (c == 0) {
				std::cout << "Nie mozna wpisywac liczby w miejsce juz zajete\n";
			}
		} while (c == 0); 
		if (x == 16)break; 
		us->setTab(x, y, m->fillMenuN(x, y));		//wpisanie do tablicy liczb podanych przez uzytkownika
		system("cls");
	}
	int check = m->endCheck();						//zapytanie uzytkownika czy chce sprawdzic ilosc bledow w sudoku
	if (check == 1) {
		int en = us->checkUserSudoku();				//zostaje sprawdzona ilosc bledow i jesli bylo rozwiazane bezblednie program sie konczy
		if (en == 0) {
			delete s1;
			delete m;
			delete mn;
			delete us;
			return 0;
		}
	}
	int file = m->end();							//zapytanie uzytkownika czy chce zapisac i jesli tak w ktorym pliku chce dokonac zapisu
	if (file == 0) {								//uzytkownik nie chce zapisac stanu gry i konczy program
		delete s1;
		delete m;
		delete mn;
		delete us;
		return 0;
	}
	us->saveFile(file);								//zostaje zapisany stan gry w pliku ktory wskazal uzytkownik
	delete s1;
	delete m;
	delete mn;
	delete us;
}
