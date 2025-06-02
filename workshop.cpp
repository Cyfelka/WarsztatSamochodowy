#include "headers.h"
#include <limits>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

Samochod::Samochod() {
    cout << "Podaj marke: ";
    getline(cin, marka);

    cout << "Podaj model: ";
    getline(cin, model);

    cout << "Podaj rocznik (np. 2020): ";
    while (!(cin >> rocznik)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nieprawidlowy format. Podaj rocznik jako liczbe: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Podaj opis usterki: ";
    getline(cin, opisUsterki);

    status = 0;
}
void Samochod::wyswietlDaneSamochodu() {
    cout << "Marka: " << marka << endl;
    cout << "Model: " << model << endl;
    cout << "Rocznik: " << rocznik << endl;
    cout << "Opis usterki: " << opisUsterki << endl;
    cout << "Status: " << (status ? "Dostêpny" : "Niedostêpny") << endl;
};

Termin::Termin() : data(0), dostepnosc(false){}
Termin::Termin(int t, bool b) : data(t), dostepnosc(b){}
void Termin::wyswietlTermin()const {
    string tekst;
    if (dostepnosc) {
        tekst = to_string(data) + " - Dostepny";
    }
    else {
        tekst = to_string(data) + " - Niedostepny";
    }
    if (dostepnosc) {
        cout << "\033[32m"<< left << setw(20) << tekst << "\033[0m";                             
    }
    else {
        cout << "\033[31m"<< left << setw(20) << tekst<< "\033[0m";                             
    }
}
void Termin::wyswietlTerminy(const Termin tab[], int n) {
    const int perRow = 4;
    cout << "\nWybierz dostepny termin:\n\n";
    for (int i = 0; i < n; ++i) {
        tab[i].wyswietlTermin();
        if ((i + 1) % perRow == 0) {
            cout << "\n";
        }
    }
    if (n % perRow != 0) {
        cout << "\n";
    }
} 
void Termin::zarezerwuj() {
	if (dostepnosc) {
		dostepnosc = false;
		cout << "Termin " << data << " zosta³ zarezerwowany.\n";
	}
	else {
		cout << "Termin " << data << " jest ju¿ niedostêpny.\n";
	}
}

Klient::Klient() {
    cout << "Tworzenie klienta indywidualnego:\n";

    cout << "Podaj imiê: ";
    getline(cin, imie);

    cout << "Podaj nazwisko: ";
    getline(cin, nazwisko);

    cout << "Podaj numer telefonu: ";
    while (!(cin >> nrTelefonu)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nieprawid³owy format. Podaj numer telefonu (liczba): ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void Klient::wypisz() const {
    cout << "Klient indywidualny:\n";
    cout << "  Imiê: " << imie << "\n";
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

    cout << "Podaj nazwê firmy: ";
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

Rezerwacja::Rezerwacja() {
    srand(static_cast<unsigned>(time(nullptr)));
    idRezerwacji = rand() % 10 + 1;

    cout << "=== Tworzenie nowej rezerwacji (ID: " << idRezerwacji << ") ===\n";

    cout << "Wybierz typ klienta:\n";
    cout << "  1. Klient indywidualny\n";
    cout << "  2. Klient biznesowy\n";
    cout << "Podaj wybór (1 lub 2): ";
    int wybor = 0;
    while (!(cin >> wybor) || (wybor != 1 && wybor != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nieprawid³owy wybór. Wpisz 1 lub 2: ";
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
    cout << "Destruktor Rezerwacja (ID: " << idRezerwacji << ") – pamiêæ zwolniona.\n";
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
    cout << "\n--- Samochód ---\n";
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
        cout << "B³¹d: termin nie mo¿e byæ pusty lub niedostêpny.\n";
    }
}
