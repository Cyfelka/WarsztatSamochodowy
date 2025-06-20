#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <iostream>
#include <string>
#include <vector>	


using namespace std;

extern int obecnyCzas;
class Kosztorys;
class Rezerwacja;
//extern vector<Rezerwacja*> wszystkieRezerwacje;

class Samochod{
	string marka;
	string model;
	int rocznik;
	string opisUsterki;
	bool status;
  bool naprawiony = 0;
public:
	Samochod();
	void wyswietlDaneSamochodu();
	string getOpisUsterki() const { return opisUsterki; }
	void setStatus(bool s) { status = s; }
	bool getStatus() const { return status; }
  bool getNaprawiony() { return naprawiony;}
  void setNaprawiony() { naprawiony = 1; };

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
	int getData() const { return data; }

};

class Klient {
	string imie;
	string nazwisko;
	int nrTelefonu;
public:
	Klient();
	void wypisz() const;
	string getImie() const { return imie; }
	string getNazwisko() const { return nazwisko; }
  virtual ~Klient() {}
};

class KlientBiz:public Klient {
	int nip;
	string nazwaFirmy;
	string adres;
public:
	KlientBiz();
	void wypiszBiz() const;
  int getNIP() { return nip; }

};

class Rezerwacja {
	Klient* daneKlienta;
	Samochod* daneSamochodu;
	Termin* terminRezerwacji;
	bool czyBiznesowy;
	int idRezerwacji;
	bool czyTylkoKosztorys = false;
	Kosztorys* kosztorys;
  mutable bool oplacona = 0;
public:
	Rezerwacja();
	~Rezerwacja();
	void wypiszRezerwacje() const;
	void setTermin(Termin* t);
	int getTermin();
	string getOpisUsterki() const { return daneSamochodu->getOpisUsterki(); }
	int getIdRezerwacji() const { return idRezerwacji; }
	Klient* getDaneKlienta() const { return daneKlienta; }
	bool getTylkoKosztorys() const { return czyTylkoKosztorys; }
	void setStatus(bool s) { daneSamochodu->setStatus(s); }
	bool getStatus() const { return daneSamochodu->getStatus(); }
	void setKosztorys(Kosztorys* k) { kosztorys = k; }
  void naprawSamochod() const;
  void oplac() const;

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
	static vector<Czesc> stworzListeCzesci();
	static void wyswietlListeCzesci(const vector<Czesc>& lista);

};


class Kosztorys {
	string opisUsterki;
	vector<Czesc> czesci;
	double liczbaGodzin;
	double stawkaGodzinowa = 41.90;
public:
	Kosztorys(const string& opis, double godziny, double stawka);
	Kosztorys(const string& opis, const vector<Czesc>& czesci, double liczbaGodzin);
	Kosztorys(const string& opis);

	void dodajCzesc(const string& nazwa, double cena, double ilosc);
	double kosztCzesci() const;
	double kosztRobocizny() const;
	double kosztCalkowity() const;
	void wyswietlKosztorys() const;
  void dodajGodziny(double godziny);
  double getLiczbaGodzin() const { return liczbaGodzin; }

};


class DokumentSprzedazy {
protected:
	int dataWystawienia;
	double kwota;
public: 
	DokumentSprzedazy(const int data, double kwota);
    virtual void drukuj() const = 0; 
    virtual ~DokumentSprzedazy() {}
};


class Paragon : public DokumentSprzedazy {
public:
    Paragon(const int data, const Kosztorys& kosztorys);
    void drukuj() const override;
};


class Faktura : public DokumentSprzedazy {
    int nip;
public:
    Faktura(const int data, const Kosztorys& kosztorys, int nip);
    void drukuj() const override;
};


class Pracownik {
protected:
	string imie;
	string nazwisko;
	int wiek;
public:
	Pracownik(const string& imie, const string& nazwisko, int wiek);
	virtual ~Pracownik() = default;

};


class Mechanik : public Pracownik {
public:
    Mechanik(const string& imie, const string& nazwisko, int wiek);
	Kosztorys sporzadzKosztorys(const string& opis);
	void naprawaPojazdu(vector<Rezerwacja*> wszystkieRezerwacje);
};


class Ksiegowy : public Pracownik {
public:
	Ksiegowy(const string& imie, const string& nazwisko, int wiek);
	Faktura wystawFakture(const Kosztorys& kosztorys, int nip, int obecnyCzas) const;
    Paragon wystawParagon(const Kosztorys& kosztorys, int obecnyCzas) const;

};


#endif
