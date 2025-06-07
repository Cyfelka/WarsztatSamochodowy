#include "headers.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>

using namespace std;

int obecnyCzas = 1;
vector<Rezerwacja*> wszystkieRezerwacje;
void skip24h();


int main() {
	srand(static_cast<unsigned int>(time(0)));
	Termin TablicaTerminowStyczen[31];
	for (int i = 0; i < 31; i++) {
		TablicaTerminowStyczen[i] = Termin(i + 1, rand() % 2);
	}
	
	int wybor = 0;
	while (wybor != 9) {

		system("cls");
		cout << "=== Co dzis robimy ===		Dzisiejsza data: "<<obecnyCzas<<".01.2025\n";
		cout << "Wybierz, opcje:\n";
		cout << "  1. Rezerwacja terminu\n";
		cout << "  2. Status Naprawy pojazdu\n";
		cout << "  3. Odbierz pojazd\n";
		cout << "=======================\n";
		cout << "  4. Napraw pojazd lub wykonanie kosztorysu\n";
		cout << "  5. Oplac naprawe\n";
		cout << "=======================\n";
		cout << "  7. Skip 1 dzien\n";
		cout << "  8. Skip 7 dni\n";
		cout << "  9. Zamknij program\n";
		cout << "Podaj wybor (od 1 do ...): ";

		while (!(cin >> wybor) || wybor<1 || wybor>9) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Nieprawidlowy wybor. Wpisz 1 lub 2: ";
		}

		switch (wybor)
		{
		case 1: {
			system("cls");
			Rezerwacja* rezerwacja1 = new Rezerwacja();
			Termin::wyswietlTerminy(TablicaTerminowStyczen, 31);
			cout << "Podaj numer terminu (1-31): ";
			int numerTerminu = 0;
			while (
				!(cin >> numerTerminu) || numerTerminu < 1 || numerTerminu > 31 || !TablicaTerminowStyczen[numerTerminu - 1].czyDostepny()
				) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Nieprawidlowy numer terminu lub termin niedostepny.\n";
				cout << "Wpisz ponownie liczbe od 1 do 31: ";
			}
			rezerwacja1->setTermin(&TablicaTerminowStyczen[numerTerminu - 1]);

			TablicaTerminowStyczen[numerTerminu - 1].zarezerwuj();

			rezerwacja1->wypiszRezerwacje();

			wszystkieRezerwacje.push_back(rezerwacja1);
			cout << "Nacisnij Enter, aby kontynuowac...";
			cin.get();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		case 2: {
			system("cls");

			cout << "=== Wyszukiwanie Rezerwacji ===\n";

			cout << "Wybierz typ klienta:\n";
			cout << "  1. Podaj ID\n";
			cout << "  2. Podaj Imie i Nazwisko\n";
			cout << "Podaj wybor (1 lub 2): ";
			int wybor = 0;
			while (!(cin >> wybor) || (wybor != 1 && wybor != 2)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Nieprawidlowy wybor. Wpisz 1 lub 2: ";
			}

			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (wybor == 1) {
				int idRezerwacji;
				cout << "Podaj ID rezerwacji: ";
				while (!(cin >> idRezerwacji) || idRezerwacji < 1) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Nieprawidlowe ID. Podaj ID rezerwacji (liczba calkowita >= 1): ";
				}
				bool found = false;
				for (const Rezerwacja* r : wszystkieRezerwacje) {
					if (r->getIdRezerwacji() == idRezerwacji) {
						r->wypiszRezerwacje();
						found = true;
						break;
					}
				}
				if (!found) {
					cout << "Nie znaleziono rezerwacji o ID: " << idRezerwacji << endl;
				}
			}
			else if (wybor == 2) {
				string imie, nazwisko;
				cout << "Podaj imie: ";
				getline(cin, imie);
				cout << "Podaj nazwisko: ";
				getline(cin, nazwisko);
				bool found = false;
				for (const Rezerwacja* r : wszystkieRezerwacje) {
					if (r->getDaneKlienta()->getImie() == imie && r->getDaneKlienta()->getNazwisko() == nazwisko) {
						r->wypiszRezerwacje();
						found = true;
						break;
					}
				}
				if (!found) {
					cout << "Nie znaleziono rezerwacji dla klienta: " << imie << " " << nazwisko << endl;
				}
			}
			else {
				cout << "Podales liczbe z poza zakresu ";
			}

			cout << "Nacisnij Enter, aby kontynuowac...";
			cin.get();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
			break;
		}
		case 3: {
			system("cls");

			cout << "=== Wyszukiwanie Rezerwacji ===\n";

			cout << "Wybierz typ klienta:\n";
			cout << "  1. Podaj ID\n";
			cout << "  2. Podaj Imie i Nazwisko\n";
			cout << "Podaj wybor (1 lub 2): ";
			int wybor = 0;
			while (!(cin >> wybor) || (wybor != 1 && wybor != 2)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Nieprawidlowy wybor. Wpisz 1 lub 2: ";
			}

			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (wybor == 1) {
				int idRezerwacji;
				cout << "Podaj ID rezerwacji: ";
				while (!(cin >> idRezerwacji) || idRezerwacji < 1) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Nieprawidlowe ID. Podaj ID rezerwacji (liczba calkowita >= 1): ";
				}
				bool found = false;
				for (const Rezerwacja* r : wszystkieRezerwacje) {
					if (r->getIdRezerwacji() == idRezerwacji && r->getStatus()==1) {
						found = true;
						cout << "Dziekujemy za skorzystanie z naszych uslug oto twoj pojazd" << endl;
						delete r;
						break;
					}
				}
				if (!found) {
					cout << "Nie znaleziono rezerwacji o ID: " << idRezerwacji << endl;
				}
			}
			else if (wybor == 2) {
				string imie, nazwisko;
				cout << "Podaj imie: ";
				getline(cin, imie);
				cout << "Podaj nazwisko: ";
				getline(cin, nazwisko);
				bool found = false;
				for (const Rezerwacja* r : wszystkieRezerwacje) {
					if (r->getDaneKlienta()->getImie() == imie && r->getDaneKlienta()->getNazwisko() == nazwisko&& r->getStatus() == 1) {
						found = true;
						cout << "Dziekujemy za skorzystanie z naszych uslug oto twoj pojazd" << endl;
						delete r;
						break;
					}
				}
				if (!found) {
					cout << "Nie znaleziono rezerwacji dla klienta: " << imie << " " << nazwisko << endl;
				}
			}
			else {
				cout << "Podales liczbe z poza zakresu ";
			}
			cout << "Nacisnij Enter, aby kontynuowac...";
			cin.get();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
			break;
		}
		case 4: {
			system("cls");

			cout << "=== Wyszukiwanie Rezerwacji ===\n";

			cout << "Wybierz typ klienta:\n";
			cout << "  1. Podaj ID\n";
			cout << "  2. Podaj Imie i Nazwisko\n";
			cout << "Podaj wybor (1 lub 2): ";
			int wybor = 0;
			while (!(cin >> wybor) || (wybor != 1 && wybor != 2)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Nieprawidlowy wybor. Wpisz 1 lub 2: ";
			}

			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (wybor == 1) {
				int idRezerwacji;
				cout << "Podaj ID rezerwacji: ";
				while (!(cin >> idRezerwacji) || idRezerwacji < 1) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Nieprawidlowe ID. Podaj ID rezerwacji (liczba calkowita >= 1): ";
				}
				bool found = false;
				for (const Rezerwacja* r : wszystkieRezerwacje) {
					if (r->getIdRezerwacji() == idRezerwacji) {
						found = true;
              r->naprawSamochod();
						break;
					}
				}
				if (!found) {
					cout << "Nie znaleziono rezerwacji o ID: " << idRezerwacji << endl;
				}
			}
			else if (wybor == 2) {
				string imie, nazwisko;
				cout << "Podaj imie: ";
				getline(cin, imie);
				cout << "Podaj nazwisko: ";
				getline(cin, nazwisko);
				bool found = false;
				for (const Rezerwacja* r : wszystkieRezerwacje) {
					if (r->getDaneKlienta()->getImie() == imie && r->getDaneKlienta()->getNazwisko() == nazwisko) {
						found = true;
          r->naprawSamochod();
						break;
					}
				}
				if (!found) {
					cout << "Nie znaleziono rezerwacji dla klienta: " << imie << " " << nazwisko << endl;
				}
			}
			else {
				cout << "Podales liczbe z poza zakresu ";
			}
			cout << "Nacisnij Enter, aby kontynuowac...";
			cin.get();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
			break;
		}
      
		case 5: {
			system("cls");

			cout << "=== Oplacanie Rezerwacji ===\n";

			cout << "Wybierz typ klienta:\n";
			cout << "  1. Podaj ID\n";
			cout << "  2. Podaj Imie i Nazwisko\n";
			cout << "Podaj wybor (1 lub 2): ";
			int wybor = 0;
			while (!(cin >> wybor) || (wybor != 1 && wybor != 2)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Nieprawidlowy wybor. Wpisz 1 lub 2: ";
			}

			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (wybor == 1) {
				int idRezerwacji;
				cout << "Podaj ID rezerwacji: ";
				while (!(cin >> idRezerwacji) || idRezerwacji < 1) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Nieprawidlowe ID. Podaj ID rezerwacji (liczba calkowita >= 1): ";
				}
				bool found = false;
				for (const Rezerwacja* r : wszystkieRezerwacje) {
					if (r->getIdRezerwacji() == idRezerwacji) {
						r->oplac();
						found = true;
						break;
					}
				}
				if (!found) {
					cout << "Nie znaleziono rezerwacji o ID: " << idRezerwacji << endl;
				}
			}
			else if (wybor == 2) {
				string imie, nazwisko;
				cout << "Podaj imie: ";
				getline(cin, imie);
				cout << "Podaj nazwisko: ";
				getline(cin, nazwisko);
				bool found = false;
				for (const Rezerwacja* r : wszystkieRezerwacje) {
					if (r->getDaneKlienta()->getImie() == imie && r->getDaneKlienta()->getNazwisko() == nazwisko) {
						r->oplac();
						found = true;
						break;
					}
				}
				if (!found) {
					cout << "Nie znaleziono rezerwacji dla klienta: " << imie << " " << nazwisko << endl;
				}
			}
			else {
				cout << "Podales liczbe z poza zakresu ";
			}

			cout << "Nacisnij Enter, aby kontynuowac...";
			cin.get();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
			break;
		}
		case 7: {
			obecnyCzas++;
			cout << "Przesunieto czas o 1 dzien. Obecny czas: " << obecnyCzas << ".01.2025\n";
			cout << "Nacisnij Enter, aby kontynuowac...";
			cin.get();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		case 8: {
			obecnyCzas++;
			cout << "Przesunieto czas o 1 dzien. Obecny czas: " << obecnyCzas << ".01.2025\n";
			cout << "Nacisnij Enter, aby kontynuowac...";
			cin.get();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		default:
			break;
		}
	}
	for (Rezerwacja* r : wszystkieRezerwacje) {
		delete r;
	}
	wszystkieRezerwacje.clear();

	return 0;
}

void skip24h() {
	obecnyCzas++;

}
