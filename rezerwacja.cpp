#include "headers.h"
#include <limits>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;


Rezerwacja::Rezerwacja() {
    srand(static_cast<unsigned>(time(nullptr)));
    idRezerwacji = rand() % 10 + 1;

    cout << "=== Tworzenie nowej rezerwacji (ID: " << idRezerwacji << ") ===\n";

    cout << "Wybierz typ klienta:\n";
    cout << "  1. Klient indywidualny\n";
    cout << "  2. Klient biznesowy\n";
    cout << "Podaj wybor (1 lub 2): ";
    int wybor = 0;
    while (!(cin >> wybor) || (wybor != 1 && wybor != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nieprawidlowy wybor. Wpisz 1 lub 2: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (wybor == 1) {
        czyBiznesowy = false;
        cout << "\n--- Dane klienta indywidualnego ---\n";
        daneKlienta = new Klient(); 
    }
    else {
        czyBiznesowy = true;
        cout << "\n--- Dane klienta biznesowego ---\n";
        daneKlienta = new KlientBiz();
    }

    cout << "\n--- Dane samochodu ---\n";
    daneSamochodu = new Samochod();
    terminRezerwacji = nullptr;
}
Rezerwacja::~Rezerwacja() {
    delete daneKlienta;
    delete daneSamochodu;
    cout << "Destruktor Rezerwacja (ID: " << idRezerwacji << ") - pamiec zwolniona.\n";
}

void Rezerwacja::wypiszRezerwacje() const {
    cout << "=== Podsumowanie rezerwacji (ID: " << idRezerwacji << ") ===\n";
    if (!czyBiznesowy) {
        daneKlienta->wypisz();
    }
    else {
        KlientBiz* kb = static_cast<KlientBiz*>(daneKlienta);
        kb->wypiszBiz();
    }
    cout << "\n--- Samochod ---\n";
    daneSamochodu->wyswietlDaneSamochodu();
    cout << "\n--- Termin ---\n";
    terminRezerwacji->wyswietlTermin();
    cout << "\n=========================================\n";
}
void Rezerwacja::setTermin(Termin* t) {
    if (t != nullptr && t->czyDostepny()) {
        terminRezerwacji = t;
    }
    else {
        cout << "Blad: termin nie moze byc pusty lub niedostepny.\n";
    }
}
int Rezerwacja::getTermin() {
	if (terminRezerwacji != nullptr) {
		return terminRezerwacji->getData();
	}
	else {
		cout << "Blad: Termin rezerwacji nie jest ustawiony.\n";
		return -1;
	}
}