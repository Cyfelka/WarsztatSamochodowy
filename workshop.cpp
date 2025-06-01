#include "headers.h"
#include <limits>
#include <iomanip>

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
    cout << "\nStan dostepnosci terminow:\n\n";
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
