#include "zamowienie.h"
#include "pch.h"
#include "Sklep.h"
#include "Magazyn.h"
#include "Stan.h"

//plik zawiera funkcje pomocnicze przy realizacji zamówienia

using namespace std;
//funkcja zwraca iloœæ konkretnego produktu na stanie konkretnego magazynu
double podaj_ilosc(MYSQL *connect, int id_magazyn, int id_produkt)
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	double iilosc=0;

	string tekst = "SELECT ilosc FROM stan WHERE id_magazyn = '" + to_string(id_magazyn) + "' AND id_produkt = '" + to_string(id_produkt) + "';";
	const char * c_char = tekst.c_str();
	mysql_query(connect, c_char);
	idzapytania = mysql_store_result(connect);
	int num_wierszy = mysql_num_rows(idzapytania);
	int num_kolumn = mysql_num_fields(idzapytania);
	while (((wiersz = mysql_fetch_row(idzapytania)) != NULL))
	{
		iilosc = stod(wiersz[0]);
	}
	return iilosc;
}
//funkcja sprawdza dostêpnoœæ magazynu
bool sprawdz_magazyn(MYSQL *connect, int id_magazyn)
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	bool warunek;

	string tekst = "SELECT dostepnosc FROM magazyn WHERE id_magazyn = '" + to_string(id_magazyn) + "';";
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
//funkcja wyœwietla magazyny które zawieraj¹ dany produkt
int wyswietl_zawierajace(MYSQL *connect, int id_produkt)
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;

	string tekst = "SELECT * FROM magazyn WHERE id_magazyn IN (SELECT id_magazyn FROM stan WHERE id_sklep IS NULL AND id_produkt = '" + to_string(id_produkt) + "');";
	const char * c_char = tekst.c_str();

	mysql_query(connect, c_char);

	idzapytania = mysql_store_result(connect);
	int num_wierszy = mysql_num_rows(idzapytania);
	int num_kolumn = mysql_num_fields(idzapytania);
	int i = 0;
	while (((wiersz = mysql_fetch_row(idzapytania)) != NULL))
	{
		for (int i = 0; i < num_kolumn; i++) {
			cout << wiersz[i] << " | ";
		}
		cout << endl;
	}
	return num_wierszy;
}
//funkcja sprawdza istnienie stanu sklepu z konkretnym produktem
bool sprawdz_stan(MYSQL *connect, int id_produkt, int id_sklep)
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;

	string tekst = "SELECT * FROM stan WHERE id_sklep = '" + to_string(id_sklep) + "' AND id_produkt = '" + to_string(id_produkt) + "';";
	const char * c_char = tekst.c_str();

	mysql_query(connect, c_char);

	idzapytania = mysql_store_result(connect);
	int num_wierszy = mysql_num_rows(idzapytania);
	if (num_wierszy == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//funkcja dodaje stan sklepu do bazy danych
void dodaj_stan(MYSQL *connect, int id_sklep, int id_produkt, string typ, string nazwa, bool dostepnosc)
{
	string insert = "INSERT INTO stan (id_sklep,id_produkt,nazwa,typ,dostepnosc,ilosc) VALUES('" + to_string(id_sklep) + "','" + to_string(id_produkt) + "','" + nazwa + "','" + typ + "','" + to_string(dostepnosc) + "','0');";
	const char * c_char = insert.c_str();
	bool query_check = mysql_query(connect, c_char);
	if (query_check == 0)
		cout << "Wybrany produkt zostal dodany do stanu sklepu." << endl;
	else
		cout << "Dodanie wybranego produktu do stanu sklepu nie powiodlo sie." << endl;
}
//funkcja aktualizuje stan magazynu
void aktualizuj_stan_magazyn(MYSQL *connect, double ilosc, double ilosc_pobrana, int id_magazyn, int id_produkt)
{
	string str_update = "UPDATE stan SET ilosc ='" + to_string(ilosc_pobrana - ilosc) + "'WHERE id_magazyn=" + to_string(id_magazyn) + " AND id_produkt = '" + to_string(id_produkt) + "';";
	const char *c_char = str_update.c_str();
	bool query_check = mysql_query(connect, c_char);
	if (query_check == 0)
		cout << "Edycja stanu magazynuu powiodla sie." << endl;
	else
		cout << "Edycja stanu magazynu nie powiodla sie" << endl;
}
//funkcja aktualizuje stan sklepu
void aktualizuj_stan_sklep(MYSQL *connect, double ilosc, int id_sklep, int id_produkt)
{
	string str_update = "UPDATE stan SET ilosc ='" + to_string(ilosc + podaj_ilosc(connect, id_sklep, id_produkt)) + "'WHERE id_sklep=" + to_string(id_sklep) + " AND id_produkt='" + to_string(id_produkt) + "';";
	const char *c_char = str_update.c_str();
	bool query_check = mysql_query(connect, c_char);
	if (query_check == 0)
		cout << "Edycja stanu sklepu powiodla sie." << endl;
	else
		cout << "Edycja stanu sklepu nie powiodla sie" << endl;
}
//funkcja sprawdza czy stan magazynu z konkretnym produktem istnieje
bool sprawdz_id(MYSQL *connect, int id_magazyn, int id_produkt)
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	string str_check = "SELECT * FROM stan WHERE id_magazyn ='" + to_string(id_magazyn) + "' AND id_produkt = '" + to_string(id_produkt) + "';";
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
//funkcja realizuj¹ca zamówienie
void zamowienie(MYSQL *connect)
{
	system("cls");
	Sklep *s1 = new Sklep(0, connect);
	Magazyn *m1 = new Magazyn(0, connect);
	Stan<Magazyn> *stan1 = new Stan<Magazyn>(0, connect);
	int id_produkt, id_magazyn, flag=1;
	double ilosc, ilosc_pobrana;
	string typ, nazwa;
	bool dostepnosc;

	s1->wyswietl();
	cout << "Podaj id sklepu: ";
	cin >> s1->id_sklep;
	if (s1->sprawdz_id(s1->id_sklep))
	{
		stan1->wyswietl_produkt();
		cout << "Podaj id produktu: ";
		cin >> id_produkt;
		if (stan1->sprawdz_id(id_produkt))
		{
			cout << "Magazyny zawierajace wybrany produkt:" << endl;
			if (wyswietl_zawierajace(connect, id_produkt) == 0)
			{
				cout << "Produkt nie wystepuje w zadnym magazynie" << endl;
				return;
			}
			else
			{
				cout << "Podaj id magazynu: ";
				cin >> id_magazyn;
				if (sprawdz_id(connect, id_magazyn, id_produkt))
				{
					if (sprawdz_magazyn(connect, id_magazyn))
					{
						MYSQL_RES *idzapytania;
						MYSQL_ROW wiersz;

						string tekst = "SELECT nazwa,typ,dostepnosc,ilosc FROM stan WHERE id_magazyn = '" + to_string(id_magazyn) + "'AND id_produkt = '" + to_string(id_produkt) + "';";
						const char * c_char = tekst.c_str();

						mysql_query(connect, c_char);

						idzapytania = mysql_store_result(connect);
						int num_wierszy = mysql_num_rows(idzapytania);
						int num_kolumn = mysql_num_fields(idzapytania);
						while (((wiersz = mysql_fetch_row(idzapytania)) != NULL))
						{
							nazwa = wiersz[0];
							typ = wiersz[1];
							dostepnosc = atoi(wiersz[2]);
							ilosc_pobrana = stod(wiersz[3]);
						}

						while (flag)
						{
							if (typ == "kg")
							{
								cout << "Produkt sprzedawany w kg" << endl;
								cout << "Podaj ilosc: ";
								ilosc = pod_ilosc<double>();
							}
							else
							{
								int flag = 1;
								cout << "Produkt sprzedawany w sztukach" << endl;
								cout << "Podaj ilosc CALKOWITA: ";
								ilosc = pod_ilosc<int>();
							}
							if (ilosc > podaj_ilosc(connect, id_magazyn, id_produkt))
							{
								cout << "Ilosc produktu przekracza ilosc w magazynie. Podaj jeszcze raz" << endl;
							}
							else
								flag = 0;
						}
						
						if (sprawdz_stan(connect, id_produkt, s1->id_sklep))
							dodaj_stan(connect, s1->id_sklep, id_produkt, typ, nazwa, dostepnosc);

						aktualizuj_stan_magazyn(connect, ilosc, ilosc_pobrana, id_magazyn, id_produkt);
						aktualizuj_stan_sklep(connect, ilosc, s1->id_sklep, id_produkt);
						cout << endl << "Transakcja zrealizowana" << endl;
					}
					else
						cout << "Wybrany magazyn nie jest dostepny" << endl;
				}
				else
					cout << "Nie ma magazynu o podanym id" << endl;
			}
		}
		else
			cout << "Nie ma produktu o podanym id" << endl;
	}
	else
		cout << "Nie ma sklpu o podanym id" << endl;
}