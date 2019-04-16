#pragma once
using namespace std;
class Produkt
{
	MYSQL *connect;
	int id_produkt;
	string nazwa;
	double cena_brutto;
	double cena_netto;
	string typ;
	bool dostepnosc;
	friend class Paragon;
public:
	Produkt(int a, MYSQL *c);
	void stworz();
	bool sprawdz();
	void dodaj();
	void wyswietl();
	void usun();
	void edytuj();
	bool sprawdz_id(int id_produkt);
};

