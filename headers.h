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

};

class Klient {
	string imie;
	string nazwisko;
	int nrTelefonu;
public:
	//Klient();
	
};

class KlientBiz:public Klient {
	int nip;
	string nazwaFirmy;
	string adres;
public:
	//KlientBiz();
	
};

class Rezerwacja {
	Klient* daneKlienta;
	Samochod* daneSamochodu;
	Termin terminRezerwacji;
	bool czyBiznesowy;
public:
	//Rezerwacja();
	

};




#endif