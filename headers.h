#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <string>
	
using namespace std;


class Samochod{
	string marka;
	string model;
	int rocznik;
	string opisUsterki;
	bool status;
public:
	Samochod();
	void wyswietlDaneSamochodu();

};

class Termin {
	int data;
	bool dostepnosc;
public:
	Termin();
	Termin(int t, bool b);
	void wyswietlTermin()const;
	static void wyswietlTerminy(const Termin tab[], int n);
	bool czyDostepny() const { return dostepnosc; };
	void zarezerwuj();

};

class Klient {
	string imie;
	string nazwisko;
	int nrTelefonu;
public:
	Klient();
	void wypisz() const;
};

class KlientBiz:public Klient {
	int nip;
	string nazwaFirmy;
	string adres;
public:
	KlientBiz();
	void wypiszBiz() const;

};

class Rezerwacja {
	Klient* daneKlienta;
	Samochod* daneSamochodu;
	Termin* terminRezerwacji;
	bool czyBiznesowy;
	int idRezerwacji;
public:
	Rezerwacja();
	~Rezerwacja();
	void wypiszRezerwacje() const;
	void setTermin(Termin* t);
	

};




#endif