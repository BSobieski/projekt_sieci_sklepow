#pragma once
#include "Sklep.h"
class Magazyn :
	public Sklep
{
private:
	int id_magazyn;
public:
	string flaga = "id_magazyn";
	Magazyn(int a, MYSQL *connect);
	bool sprawdz() override;
	void stworz() override;
	void dodaj() override;
	void wyswietl() override;
	void usun() override;
	void edytuj() override;
	bool sprawdz_id(int id_magazyn) override;
};