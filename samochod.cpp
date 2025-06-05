#include "headers.hpp"
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
    cout << "Status: " << (status ? "Dostepny" : "Niedostepny") << endl;
};
