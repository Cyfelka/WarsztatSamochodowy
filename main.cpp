#include "headers.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>

using namespace std;


int main() {
	srand(static_cast<unsigned int>(time(0))); //test git repo
	Termin TablicaTerminowStyczen[31];
	for (int i = 0; i < 31; i++) {
		TablicaTerminowStyczen[i] = Termin(i + 1, rand() % 2);
	}

	vector<Rezerwacja*> wszystkieRezerwacje;
	
	//Samochod samochod1;
	//samochod1.wyswietlDaneSamochodu();

	cout << "=== Co dzis robimy ===\n";
	cout << "Wybierz, opcje:\n";
	cout << "  1. Rezerwacja terminu\n";
	cout << "  2. Status Naprawy pojazdu\n";
	cout << "=======================\n";
	cout << "  3. Sporzadz kosztorys\n";
	cout << "Podaj wybor (od 1 do ...): ";

	int wybor = 0;
	while (!(cin >> wybor) || (wybor != 1 && wybor != 2)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Nieprawidlowy wybor. Wpisz 1 lub 2: ";
	}

	switch (wybor)
	{
	case 1: {
		system("cls");
		Rezerwacja* rezerwacja1 = new Rezerwacja();
		Termin::wyswietlTerminy(TablicaTerminowStyczen, 31);
		cout << "Podaj numer terminu (1-31): ";
		int numerTerminu = 0;
		while (
			!(cin >> numerTerminu) || numerTerminu < 1 || numerTerminu > 31 || !TablicaTerminowStyczen[numerTerminu - 1].czyDostepny()
			) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Nieprawidlowy numer terminu lub termin niedostepny.\n";
			cout << "Wpisz ponownie liczbe od 1 do 31: ";
		}
		rezerwacja1->setTermin(&TablicaTerminowStyczen[numerTerminu - 1]);

		TablicaTerminowStyczen[numerTerminu - 1].zarezerwuj();

		rezerwacja1->wypiszRezerwacje();

		wszystkieRezerwacje.push_back(rezerwacja1);
		break;
	}
	case 2: {
		break;
	}
	case 3: {
		vector<Czesc> wszystkieCzesci=Czesc::stworzListeCzesci();
		break;
	}
	default:
		break;
	}
	for (Rezerwacja* r : wszystkieRezerwacje) {
		delete r;
	}
	wszystkieRezerwacje.clear();

	return 0;
}