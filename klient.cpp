#include "headers.hpp"
#include <limits>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;


Klient::Klient() {
    cout << "Tworzenie klienta indywidualnego:\n";

    cout << "Podaj imie: ";
    getline(cin, imie);

    cout << "Podaj nazwisko: ";
    getline(cin, nazwisko);

    cout << "Podaj numer telefonu: ";
    while (!(cin >> nrTelefonu)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nieprawidlowy format. Podaj numer telefonu (liczba): ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void Klient::wypisz() const {
    cout << "Klient indywidualny:\n";
    cout << "  Imie: " << imie << "\n";
    cout << "  Nazwisko: " << nazwisko << "\n";
    cout << "  Nr telefonu: " << nrTelefonu << "\n";
}

KlientBiz::KlientBiz() : Klient() {
    cout << "Dane klienta biznesowego (rozszerzenie):\n";

    cout << "Podaj NIP firmy: ";
    while (!(cin >> nip)) {
        cin.clear();
        cout << "Niepoprawny format. Podaj NIP (liczba): ";
    }

    cout << "Podaj nazwe firmy: ";
    getline(cin, nazwaFirmy);

    cout << "Podaj adres firmy: ";
    getline(cin, adres);

    cout << "Klient biznesowy utworzony.\n\n";
}
void KlientBiz::wypiszBiz() const {
    Klient::wypisz();

    cout << "  NIP: " << nip << "\n";
    cout << "  Nazwa firmy: " << nazwaFirmy << "\n";
    cout << "  Adres: " << adres << "\n";
}