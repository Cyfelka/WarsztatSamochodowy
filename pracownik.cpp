#include "headers.h"
#include <limits>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

Pracownik::Pracownik(const string& imie, const string& nazwisko, int wiek)
    : imie(imie), nazwisko(nazwisko), wiek(wiek) {}


Mechanik::Mechanik(const string& imie, const string& nazwisko, int wiek)
    : Pracownik(imie, nazwisko, wiek) {}

Ksiegowy::Ksiegowy(const string& imie, const string& nazwisko, int wiek)
    : Pracownik(imie, nazwisko, wiek) {}

string pobierzDzisiejszaDate() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    ostringstream ss;
    ss << put_time(now, "%Y-%m-%d");
    return ss.str();
}

Paragon Ksiegowy::wystawParagon(const Kosztorys& kosztorys) const {
    return Paragon(pobierzDzisiejszaDate(), kosztorys);
}

Faktura Ksiegowy::wystawFakture(const Kosztorys& kosztorys, int nip) const {
    return Faktura(pobierzDzisiejszaDate(), kosztorys, nip);
}
