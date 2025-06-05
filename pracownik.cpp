#include "headers.h"
#include <limits>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
using namespace std;

Pracownik::Pracownik(const string& imie, const string& nazwisko, int wiek)
    : imie(imie), nazwisko(nazwisko), wiek(wiek) {}


Mechanik::Mechanik(const string& imie, const string& nazwisko, int wiek)
    : Pracownik(imie, nazwisko, wiek) {}

Ksiegowy::Ksiegowy(const string& imie, const string& nazwisko, int wiek)
    : Pracownik(imie, nazwisko, wiek) {}

//string pobierzDzisiejszaDate() {
//    time_t t = time(nullptr);
//    tm* now = localtime(&t);
//    ostringstream ss;
//    ss << put_time(now, "%Y-%m-%d");
//    return ss.str();
//}

Paragon Ksiegowy::wystawParagon(const Kosztorys& kosztorys, int obecnyCzas) const {
    return Paragon(obecnyCzas, kosztorys);
}

Faktura Ksiegowy::wystawFakture(const Kosztorys& kosztorys, int nip, int obecnyCzas) const {
    return Faktura(obecnyCzas, kosztorys, nip);
}Kosztorys Mechanik::sporzadzKosztorys(const string& opis) {
	double godziny = 0.0;
	cout << "Opis awari: " << opis << endl;
	cout << "Podaj liczbe godzin pracy: ";
	while (!(cin >> godziny) || godziny < 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Nieprawidlowa wartosc. Podaj liczbe >= 0: ";
	}
	vector	<Czesc> czesci = Czesc::stworzListeCzesci();
	Kosztorys kosztorys(opis, czesci, godziny);
	return kosztorys;
}
void Mechanik::naprawaPojazdu(vector<Rezerwacja*> wszystkieRezerwacje) {
	int temp = 0;
	for (int i = 0; i < wszystkieRezerwacje.size(); i++) {
		if (wszystkieRezerwacje[i]->getTermin() == obecnyCzas) {
			temp = i;
		}
	}
	if(temp!=0){
		wszystkieRezerwacje[temp]->wypiszRezerwacje();

		Kosztorys kosztorys = sporzadzKosztorys(wszystkieRezerwacje[temp]->getOpisUsterki());
		kosztorys.wyswietlKosztorys();
		wszystkieRezerwacje[temp]->setStatus(1);
		wszystkieRezerwacje[temp]->setKosztorys(&kosztorys);
	}
}