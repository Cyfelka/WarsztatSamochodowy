#include "headers.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;


int main() {
	srand(static_cast<unsigned int>(time(0)));
	Termin TablicaTerminowStyczen[31];
	for (int i = 0; i < 31; i++) {
		TablicaTerminowStyczen[i] = Termin(i + 1, rand() % 2);
	}
	Termin::wyswietlTerminy(TablicaTerminowStyczen, 31);
	
	//Samochod samochod1;
	//samochod1.wyswietlDaneSamochodu();



	return 0;
}