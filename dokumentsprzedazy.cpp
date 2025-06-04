#include "headers.h"
#include <limits>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

DokumentSprzedazy::DokumentSprzedazy(const int data, double kwota)
    : dataWystawienia(data), kwota(kwota) {}

Paragon::Paragon(const int data, const Kosztorys& kosztorys)
    : DokumentSprzedazy(data, kosztorys.kosztCalkowity()) {}

void Paragon::drukuj() const {
    cout << "=== PARAGON ===\n";
    cout << "Data: " << dataWystawienia << "\n";
    cout << "Kwota: " << kwota << " zl\n";
    cout << "Dziekujemy za zakup!\n";
}


Faktura::Faktura(const int data, const Kosztorys& kosztorys, int nip)
    : DokumentSprzedazy(data, kosztorys.kosztCalkowity()), nip(nip) {}

void Faktura::drukuj() const {
    cout << "=== FAKTURA VAT ===\n";
    cout << "Data: " << dataWystawienia << "\n";
    cout << "NIP nabywcy: " << nip << "\n";
    cout << "Kwota brutto: " << kwota << " zl\n";
    cout << "Dziekujemy za skorzystanie z naszych uslug!\n";
}