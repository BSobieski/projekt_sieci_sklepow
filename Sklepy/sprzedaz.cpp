#include "sprzedaz.h"
#include "pch.h"
#include "Stan.h"
#include "Sklep.h"
#include "Paragon.h"

using namespace std;

//funlcja zwraca obród wybranego sklepu
double podaj_obrot(MYSQL *connect, int id_sklep)
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	double obrot;

	string tekst = "SELECT obrot FROM sklep WHERE id_sklep = '" + to_string(id_sklep) + "';";
	const char * c_char = tekst.c_str();
	mysql_query(connect, c_char);
	idzapytania = mysql_store_result(connect);
	if (idzapytania != NULL)
	{
		int num_wierszy = mysql_num_rows(idzapytania);
		int num_kolumn = mysql_num_fields(idzapytania);
		while (((wiersz = mysql_fetch_row(idzapytania)) != NULL))
		{
			obrot = stod(wiersz[0]);
		}
		return obrot;
	}
	return 0;
}
//funkcja aktualizuje iloœæ pozycji stanu sklepu
void aktualizuj_stan(MYSQL *connect, int id_sklep, int id_produkt, double ilosc_kupiona, double ilosc)
{
	string str_update = "UPDATE stan SET ilosc ='" + to_string(ilosc - ilosc_kupiona) + "'WHERE id_sklep=" + to_string(id_sklep) + " AND id_produkt = '" + to_string(id_produkt) + "';";
	const char *c_char = str_update.c_str();
	bool query_check = mysql_query(connect, c_char);
	if (query_check == 0)
		cout << "Edycja stanu sklepu powiodla sie." << endl;
	else
		cout << "Edycja stanu sklepu nie powiodla sie" << endl;
}
//funkcja aktualizuje obrót sklepu
void aktualizuj_sklep(MYSQL *connect, int id_sklep, double koszt)
{
	string str_update = "UPDATE sklep SET obrot ='" + to_string(koszt + podaj_obrot(connect, id_sklep)) + "'WHERE id_sklep=" + to_string(id_sklep) + ";";
	const char *c_char = str_update.c_str();
	bool query_check = mysql_query(connect, c_char);
	if (query_check == 0)
		cout << "Edycja obrotu sklepu powiodla sie." << endl;
	else
		cout << "Edycja obrotu sklepu nie powiodla sie" << endl;
}
//funkcja zwraca cenê wybranego produktu
double podaj_cene(MYSQL *connect, int id_produkt)
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	double cena;

	string tekst = "SELECT cena_brutto FROM produkt WHERE id_produkt = '" + to_string(id_produkt) + "';";
	const char * c_char = tekst.c_str();
	mysql_query(connect, c_char);
	idzapytania = mysql_store_result(connect);
	int num_wierszy = mysql_num_rows(idzapytania);
	int num_kolumn = mysql_num_fields(idzapytania);
	while (((wiersz = mysql_fetch_row(idzapytania)) != NULL))
	{
		cena = stod(wiersz[0]);
	}
	return cena;
}
//funkcja sprawdzaj¹ca czy sklep o podanym id istnieje
bool sprawdz_sklep(MYSQL *connect, int id_sklep)
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	bool warunek;

	string tekst = "SELECT dostepnosc FROM sklep where id_sklep = '" + to_string(id_sklep) + "';";
	const char * c_char = tekst.c_str();
	mysql_query(connect, c_char);

	idzapytania = mysql_store_result(connect);
	int num_wierszy = mysql_num_rows(idzapytania);
	int num_kolumn = mysql_num_fields(idzapytania);
	while (((wiersz = mysql_fetch_row(idzapytania)) != NULL))
	{
		warunek = stoi(wiersz[0]);
	}
	return warunek;
}
//funkcja sprawdza czy stan sklepu z konkretnym produktem istnieje
bool sprawdz_id_sklep(MYSQL *connect, int id_sklep, int id_produkt)
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	string str_check = "SELECT * FROM stan WHERE id_sklep ='" + to_string(id_sklep) + "' AND id_produkt= '" + to_string(id_produkt) + "';";
	const char * c_char = str_check.c_str();
	mysql_query(connect, c_char);
	idzapytania = mysql_store_result(connect);
	int num_wierszy = mysql_num_rows(idzapytania);
	if (num_wierszy == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
//funkcja szablonowa do podawania iloœci produktu
template <typename typ>
double pod_ilosc()
{
	int flag = 1;
	double ilosc;
	while (flag)
	{
		cin >> ilosc;
		if ((double)((typ)ilosc) == ilosc)
			flag = 0;
		else
			cout << "Niepoprawnie podana liczba. Podaj jeszcze raz" << endl;
	}
	return ilosc;
}
//funkcja realizuj¹ca sprzeda¿
void sprzedaz(MYSQL *connect)
{
	system("cls");
	string typ,nazwa;
	bool dostepnosc, zakupy, f;
	double ilosc, cena, koszt = 0.0, ilosc_p;
	int warunek_stop, licznik_pozycji=0;
	Paragon *paragon1 = new Paragon(connect);
	Sklep *s1 = new Sklep(0, connect);
	Stan<Sklep> *stan1 = new Stan<Sklep>(0, connect);
	s1->wyswietl();
	cout << "Podaj id sklepu: ";
	cin >> s1->id_sklep;
	if (s1->sprawdz_id(s1->id_sklep))
	{
		if (sprawdz_sklep(connect, s1->id_sklep))
		{
			zakupy = true;
			while (zakupy)
			{
				stan1->ustaw_cel(s1->id_sklep);
				stan1->wyswietl();
				cout << "Podaj id produktu: ";
				cin >> stan1->id_produkt;
				if (sprawdz_id_sklep(connect, s1->id_sklep, stan1->id_produkt))
				{
					MYSQL_RES *idzapytania;
					MYSQL_ROW wiersz;

					string tekst = "SELECT nazwa,typ,dostepnosc,ilosc FROM stan where id_sklep = '" + to_string(s1->id_sklep) + "' AND id_produkt = '" + to_string(stan1->id_produkt) + "';";
					const char * c_char = tekst.c_str();
					mysql_query(connect, c_char);
					idzapytania = mysql_store_result(connect);
					int num_wierszy = mysql_num_rows(idzapytania);
					int num_kolumn = mysql_num_fields(idzapytania);
					while (((wiersz = mysql_fetch_row(idzapytania)) != NULL))
					{
						nazwa = wiersz[0];
						typ = wiersz[1];
						dostepnosc = stoi(wiersz[2]);
						ilosc = stod(wiersz[3]);
					}
					if (dostepnosc)
					{
						if (typ == "kg")
						{
							cout << "Produkt sprzedawany w kg" << endl;
							cout << "Podaj ilosc: ";
							ilosc_p = pod_ilosc<double>();
						}
						else
						{
							int flag = 1;
							cout << "Produkt sprzedawany w sztukach" << endl;
							cout << "Podaj ilosc CALKOWITA: ";
							ilosc_p = pod_ilosc<int>();
						}
						if (ilosc_p <= ilosc)
						{
							cena = podaj_cene(connect, stan1->id_produkt);
							koszt += cena * ilosc_p;
							cout << "Koszt produktu wynosi " << cena * ilosc_p << endl;
							paragon1->dodaj_pozycje(licznik_pozycji, stan1->id_produkt, nazwa, typ, ilosc_p, cena);
							f = true;
							while (f)
							{
								cout << "Czy chcesz kontynuowac zakupy?" << endl;
								cout << "1. Tak" << endl;
								cout << "2. Nie" << endl;
								cin >> warunek_stop;
								switch (warunek_stop)
								{
								case 1:
									f = false;
									licznik_pozycji++;
									system("cls");
									break;
								case 2:
									paragon1->stworz(s1->id_sklep, koszt);
									f = false;
									zakupy = false;
									system("cls");
									cout << "Koszt calkowity wynosi " << koszt << endl;
									aktualizuj_sklep(connect, s1->id_sklep, koszt);
									paragon1->dodaj();
									paragon1->aktualiuzj_pozycje();
									aktualizuj_stan(connect, s1->id_sklep, stan1->id_produkt, ilosc_p, ilosc);
									break;
								default:
									cout << "Nie ma takiej opcji. Wpisz jeszcze raz" << endl;
									break;
								}
							}
						}
						else
						{
							cout << "Wybrany sklep nie spelnia wymagan co do ilosci produktu. Wybierz ilosc ponownie" << endl;
						}
					}
					else
						cout << "Wybrany produkt jest niedostepny " << endl;
				}
				else
					cout << "Nie ma produktu o podanym id" << endl;
			}

		}
		else
			cout << "Wybrany sklep nie jest dostepny" << endl;
	}
	else
		cout << "Nie ma sklpu o podanym id" << endl;
}
