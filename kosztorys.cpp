#include "headers.h"
#include <limits>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

Kosztorys::Kosztorys(const string& opis, double godziny, double stawka)
    : opisUsterki(opis), liczbaGodzin(godziny), stawkaGodzinowa(stawka) {}
Kosztorys::Kosztorys(const string& opis, const vector<Czesc>& czesci, double godziny)
	: opisUsterki(opis), czesci(czesci), liczbaGodzin(godziny), stawkaGodzinowa(41.90) {
}

void Kosztorys::dodajCzesc(const std::string& nazwa, double cena, double ilosc) {
    czesci.push_back({nazwa, cena, ilosc});
}

double Kosztorys::kosztCzesci() const {
    double suma = 0.0;
    for (const auto& czesc : czesci) {
        suma += czesc.getCena();
    }
    return suma;
}

double Kosztorys::kosztRobocizny() const {
    return liczbaGodzin * stawkaGodzinowa;
}

double Kosztorys::kosztCalkowity() const {
    return kosztCzesci() + kosztRobocizny();
}

void Kosztorys::wyswietlKosztorys() const {
    cout << "=== Kosztorys naprawy ===\n";
    cout << "Opis usterki: " << opisUsterki << "\n\n";

    cout << "Czesci:\n";
    for (const auto& czesc : czesci) {
        cout << " - " << czesc.getNazwa()
                  << " x" << czesc.getIlosc()
                  << " @ " << fixed << setprecision(2)
                  << czesc.getCena() << " zl = "
                  << czesc.koszt() << " zl\n";
    }

    cout << "\nRobocizna: " << liczbaGodzin << " godz x "
              << stawkaGodzinowa << " zl = "
              << kosztRobocizny() << " zl\n";

    cout << "\nLaczny koszt: " << kosztCalkowity() << " zl\n";
}