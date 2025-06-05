#include "headers.hpp"
#include <limits>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;


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
		cout << "Termin " << data << " zostal zarezerwowany.\n";
	}
	else {
		cout << "Termin " << data << " jest juz niedostepny.\n";
	}
}