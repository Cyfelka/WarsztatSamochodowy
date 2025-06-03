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
    cout << "Status: " << (status ? "Dost�pny" : "Niedost�pny") << endl;
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
		cout << "Termin " << data << " zosta� zarezerwowany.\n";
	}
	else {
		cout << "Termin " << data << " jest ju� niedost�pny.\n";
	}
}

Klient::Klient() {
    cout << "Tworzenie klienta indywidualnego:\n";

    cout << "Podaj imi�: ";
    getline(cin, imie);

    cout << "Podaj nazwisko: ";
    getline(cin, nazwisko);

    cout << "Podaj numer telefonu: ";
    while (!(cin >> nrTelefonu)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nieprawid�owy format. Podaj numer telefonu (liczba): ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void Klient::wypisz() const {
    cout << "Klient indywidualny:\n";
    cout << "  Imi�: " << imie << "\n";
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

    cout << "Podaj nazw� firmy: ";
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
    cout << "Podaj wyb�r (1 lub 2): ";
    int wybor = 0;
    while (!(cin >> wybor) || (wybor != 1 && wybor != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nieprawid�owy wyb�r. Wpisz 1 lub 2: ";
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
    cout << "Destruktor Rezerwacja (ID: " << idRezerwacji << ") � pami�� zwolniona.\n";
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
    cout << "\n--- Samoch�d ---\n";
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
        cout << "B��d: termin nie mo�e by� pusty lub niedost�pny.\n";
    }
}

Czesc::Czesc() : nazwa(""), ilosc(0), cena(0.0) {};
vector<Czesc> Czesc::stworzListeCzesci() {
    vector<Czesc> lista;
    char odpowiedz = 't';
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "\nCzy chcesz doda� cz��? (t/n): ";
        cin >> odpowiedz;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (odpowiedz == 'n' || odpowiedz == 'N') {
            break;
        }
        else if (odpowiedz == 't' || odpowiedz == 'T') {
            Czesc c;

            cout << "Podaj nazw� cz�ci: ";
            getline(cin, c.nazwa);

            cout << "Podaj ilo�� (liczba ca�kowita >= 0): ";
            while (!(cin >> c.ilosc) || c.ilosc < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Nieprawid�owa warto��. Podaj liczb� ca�kowit� >= 0: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Podaj cen� (np. 49.99): ";
            while (!(cin >> c.cena) || c.cena < 0.0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Nieprawid�owa warto��. Podaj cen� >= 0.0: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            lista.push_back(c);
        }
        else {
            cout << "Niepoprawna odpowied�. Wpisz 't' (tak) lub 'n' (nie).\n";
        }
    }
// test
    return lista;
}



