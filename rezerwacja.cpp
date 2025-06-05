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

    cout << "Co robimy z samochodem:\n";
    cout << "  1. Tylko kosztorys\n";
    cout << "  2. Naprawa\n";
    cout << "Podaj wybor (1 lub 2): ";
	int wybor2 = 0;
    while (!(cin >> wybor2) || (wybor2 != 1 && wybor2 != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nieprawidlowy wybor. Wpisz 1 lub 2: ";
    }
    if (wybor2==1)
    {
        czyTylkoKosztorys = 1;
    }
  else
  { czyTylkoKosztorys=0;
    kosztorys = new Kosztorys(Rezerwacja::getOpisUsterki());
  }
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
    cout<<"\033[32m"<<terminRezerwacji->getData()<<" - Zarezerwowany\033[0m";
    cout << "\n=========================================\n";
    if (daneSamochodu->getStatus() == 1) {
        cout << "\033[32mSamochod jest gotowy do odbioru.\033[0m\n";
    }
    else {
        cout << "\033[33mSamochod nie jest jeszcze gotowy do odbioru.\033[0m\n";
    }
    if (kosztorys != nullptr) {
		cout << "\n--- Kosztorys ---\n";
		kosztorys->wyswietlKosztorys();
	}
	else {
		cout << "Brak kosztorysu.\n";
	}
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

  void Rezerwacja::naprawSamochod() const {
  char odpowiedz = 't';
  string nazwa;
  double cena, ilosc, wh;
  while (true) {
    cout << "Czy dodac czesci? (t/n)\n";
    cin >> odpowiedz;
    if (odpowiedz == 'n' || odpowiedz == 'N') break;
    if (odpowiedz == 't' || odpowiedz == 'T') {
      cout << "Podaj nazwe czesci\n";
      cin >> nazwa;
      cout << "Podaj ilosc czesci\n";
      cin >> ilosc;
      cout << "Podaj cene czesci\n";
      cin >> cena;
      kosztorys->dodajCzesc(nazwa, ilosc, cena);
    }
    else cout << "Nie ma takiej odpowiedzi\n";
  }
  cout << "Podaj liczbe roboczogodzin\n";
  cin >> wh;
  kosztorys->dodajGodziny(wh);
  kosztorys->kosztCzesci();
  kosztorys->kosztRobocizny();
  kosztorys->kosztCalkowity();
  kosztorys->wyswietlKosztorys(); //debug
  daneSamochodu->setNaprawiony();
}

