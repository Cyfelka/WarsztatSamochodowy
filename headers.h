#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <string>
	
using namespace std;
// Forward declarations of classes

class Samochod{
	string marka;
	string model;
	int rocznik;
	string opisUsterki;
	bool status;
public:
	Samochod();
	~Samochod();

};

class Termin {
	int data;
	bool dostepnosc;
public:
	Termin();
	~Termin();

};

class Klient {
	string imie;
	string nazwisko;
	int nrTelefonu;
public:
	Klient();
	~Klient();

};

class KlientBiz:public Klient {
	int nip;
	string nazwaFirmy;
	string adres;
public:
	KlientBiz();
	~KlientBiz();

};

class Rezerwacja {
	Klient* daneKlienta;
	Samochod* daneSamochodu;
	Termin terminRezerwacji;
	bool czyBiznesowy;
public:
	Rezerwacja();
	~Rezerwacja( );

};




#endif