#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <string>
#include <vector>	

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

class Czesc{
	string nazwa;
	double ilosc;
	double cena;
public:
	Czesc();
	Czesc(const string& nazwa, double ilosc, double cena);

    string getNazwa() const;
    double getIlosc() const;
    double getCena() const;
    double koszt() const;
	vector<Czesc> static stworzListeCzesci();
	void static wyswietlListeCzesci(const vector<Czesc>& lista);

};


class Kosztorys {
	string opisUsterki;
	vector<Czesc> czesci;
	int liczbaGodzin;
	double stawkaGodzinowa = 41.90;
public:
	Kosztorys(const string& opis, double godziny, double stawka);

	void dodajCzesc(const string& nazwa, double cena, int ilosc);
	double kosztCzesci() const;
	double kosztRobocizny() const;
	double kosztCalkowity() const;
	void wyswietlKosztorys() const;

};


#endif