#include <stdio.h>
#include <iostream>
#include <windows.h>
#include "menuNew.h"


template<int min, int max>
int kontrola() {
	int wpisana;
	while (scanf_s("%d", &wpisana) != 1 || wpisana < min || wpisana > max || getchar() != '\n') {
		std::cout << "Bledny wybor, wybierz ponownie.\nWybor: ";
		while (getchar() != '\n');
	}
	return wpisana;
}
int MenuNew::start() {
	std::cout << "Zaczynasz nowa gre.\n";
	std::cout << "Prosze wybierz poziom trudnosci od 1 do 5(1-latwy, 5-trudny)\n";
	std::cout << "Poziom trudnosci: ";
	int dif_lv = kontrola<1, 5>();
	return dif_lv;
}