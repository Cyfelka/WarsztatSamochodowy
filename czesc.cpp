#include "headers.h"
#include <limits>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;



Czesc::Czesc() : nazwa(""), ilosc(0), cena(0.0) {};
vector<Czesc> Czesc::stworzListeCzesci() {
    vector<Czesc> lista;
    char odpowiedz = 't';
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "\nCzy chcesz dodac czesc? (t/n): ";
        cin >> odpowiedz;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (odpowiedz == 'n' || odpowiedz == 'N') {
            break;
        }
        else if (odpowiedz == 't' || odpowiedz == 'T') {
            Czesc c;

            cout << "Podaj nazwe czeci: ";
            getline(cin, c.nazwa);

            cout << "Podaj ilosc (liczba calkowita >= 0): ";
            while (!(cin >> c.ilosc) || c.ilosc < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Nieprawidlowa wartosc. Podaj liczbe calkowita >= 0: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Podaj cene (np. 49.99): ";
            while (!(cin >> c.cena) || c.cena < 0.0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Nieprawidlowa wartosc. Podaj cene >= 0.0: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            lista.push_back(c);
        }
        else {
            cout << "Niepoprawna odpowiedz. Wpisz 't' (tak) lub 'n' (nie).\n";
        }
    }
// test
    return lista;


}
void Czesc::wyswietlListeCzesci(const vector<Czesc>& lista) {
    cout << "\n=== Lista Czesci ===\n";
    cout << left << setw(20) << "Nazwa"
        << setw(10) << "Ilosc"
        << setw(10) << "Cena"
        << endl;
    cout << string(50, '-') << endl;
    for (const auto& c : lista) {
        cout << left << setw(20) << c.nazwa
            << setw(10) << c.ilosc
            << setw(10) << fixed << setprecision(2) << c.cena
            << endl;
    }
}

string Czesc::getNazwa() const {
    return nazwa;
}

double Czesc::getIlosc() const {
    return ilosc;
}

double Czesc::getCena() const {
    return cena;
}

double Czesc::koszt() const {
    return ilosc * cena;
}
