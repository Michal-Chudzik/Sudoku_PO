#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include "menu.h"
#include "Sudoku.h"

Menu::Menu() {}

//menu powitalne
int Menu::startMenu(){
	std::cout << "\t\tWitam w grze SUDOKU.\n\n";
	std::cout << "Czy chcesz odczytac zapis z poprzedniej gry? (0-nie, 1-tak)\n";
	std::cout << "Wybor: ";
	return kontrola<0, 1>();
}

//menu dotyczace otwarcia plikow z zapisu
int Menu::start() {

	int wybor = 0;
	while (wybor == 0) {
		std::cout << "Z ktorego pliku chcesz wziac zapis?(1-3)";
		std::cout << "Plik nr: ";
		int file_num = kontrola<1, 3>();
		int save;
		char file[15];
		if (file_num == 1) { strcpy(file, "file_save1.txt"); }
		else if (file_num == 2) { strcpy(file, "file_save2.txt"); }
		else if (file_num == 3) { strcpy(file, "file_save3.txt"); }
		std::ifstream in(file);
		int licznik = -1;
		if (in.good() && in.is_open()) {
			if (in.peek() == std::ifstream::traits_type::eof()) {
				save = 0;
			}
			else{
				save = 1;
				in.close();
			}
		}
		else {
			save = 0;
		}
		if (save == 0) {
			std::cout << "Brak zapisu w pliku nr " << file_num << '\n';
			std::cout << "Jesli chcesz wybrac inny plik wybierz 0\n";
			std::cout << "Jesli chcesz zaczac nowa gre wybierz 1\n";
			std::cout << "Jesli chcesz zakonczyc prace programu wybierz 2\n";
			std::cout << "Wybor: ";
			wybor = kontrola<0, 2>();
			switch (wybor) {
			case 0:
				break;
			case 1:
				return 4;
			case 2:
				return 0;
			}
		}
		else {

			return file_num;
		}
	}
}
void Menu::powo() {
	system("cls");
	std::cout << "\t\tPowodzenia!!!";
	Sleep(1500);
	system("cls");
}
void Menu::fill() {
	std::cout << "\nPodaj wspolrzedne w ktore chcesz wpisac liczbe. \nJesli chcesz zakonczyc gre wpisz w indeks X liczbe 16\n";
}
//uzupelnienie x
int Menu::fillMenuX() {
	std::cout << "x: ";
	int wpisana;
	while (scanf_s("%d", &wpisana) != 1 || wpisana < 0 || wpisana > 8 && wpisana!=16 || getchar() != '\n') {
		std::cout << "Bledny wybor, wybierz ponownie.\nWybor: ";
		while (getchar() != '\n');
	}
	return wpisana;
}
//uzupelnienie y
int Menu::fillMenuY() {
	std::cout << "y: ";
	return kontrola<0,8>();
}
//usupelnienie liczby
int Menu::fillMenuN(int x, int y) {
	printf("\nJaka chcesz wpisac liczbe w okienko %d, %d?\n", x, y);
	std::cout << "liczba: ";
	return kontrola<1,9>();
}
//pytanie o sprawdzenie poprawnosci uzupelnienia
int Menu::endCheck() {
	std::cout << "Czy chcesz sprawdzic poprawnosc uzupenionego sudoku?(0-nie 1-tak)\n";
	std::cout << "Wybor: ";
	return kontrola<0,1>();
}
//koniec 
int Menu::end() {
	std::cout << "\n\nDziekuje za gre, czy chcesz ja zapisac? (0-nie 1-tak)\n";
	std::cout << "Wybor: ";
	int save = kontrola<0,1>();
	if (save == 0) {
		std::cout << "\n\nKoniec programu.\n\n";
		return 0;
	}
	else {
		std::cout << "\nKtory plik chcesz wybrac do zapisu?(1-3)\n";
		std::cout << "plik nr: ";
		return kontrola<1,3>();
	}
}
