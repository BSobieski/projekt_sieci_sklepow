#pragma once
#include "Produkt.h"

using namespace std;
class Paragon
{
	MYSQL *connect;
	int id_paragon;
	string numer;
	int id_sklep;
	double koszt;
	vector<Produkt> pozycje;
public:
	Paragon(MYSQL *connect);
	void stworz(int id_skl, double koszt);
	void dodaj_pozycje(int licznik_pozycji, int id_prod, string nazwa, string t, double il,double cena);
	void dodaj();
	void aktualiuzj_pozycje();
	int wez_id(string numer);
	bool sprawdz(int id_paragon);
	void wyswietl();
	void wyswietl_dane();
};

