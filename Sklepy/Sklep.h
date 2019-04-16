#pragma once
using namespace std;
class Sklep
{
private:
	int id_sklep;
	double obrot;
	friend void sprzedaz(MYSQL *connect);
	friend void zamowienie(MYSQL *connect);
protected:
	MYSQL *connect;
	string numer;
	string miasto;
	string adres;
	string kod_pocztowy;
	bool dostepnosc;
public:
	string flaga = "id_sklep";
	Sklep(int a, MYSQL *c);
	virtual bool sprawdz();
	virtual void stworz();
	virtual void dodaj();
	virtual void wyswietl();
	virtual void usun();
	virtual void edytuj();
	virtual bool sprawdz_id(int id_sklep);
};

