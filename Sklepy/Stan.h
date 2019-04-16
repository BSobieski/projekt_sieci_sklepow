#pragma once
#include "Produkt.h"

using namespace std;

template <class Klasa>
class Stan
{
	MYSQL *connect;
	Klasa *wskaznik;
	Produkt *produkt;
	int id_stan;
	int id_cel;
	int id_produkt;
	string nazwa;
	string typ;
	double ilosc;
	bool dostepnosc;
	friend void sprzedaz(MYSQL *connect);
public:
	Stan(int a, MYSQL *c);
	void wyswietl_produkt();
	void wyswietl();
	void stworz();
	void dodaj();
	void usun();
	void edytuj_ilosc();
	bool sprawdz();
	void ustaw_cel(int a);
	bool sprawdz_id(int produkt_id);
};

