#include "pch.h"
#include "Paragon.h"
#include "Produkt.h"

using namespace std;
//konstruktor klasy
Paragon::Paragon(MYSQL *connect)
{
	this->connect = connect;
}
//stworzenie paragonu i wylosowanie mu numeru
void Paragon::stworz(int id_skl, double koszt)
{
	srand(time(NULL));
	this->numer = "";
	for (int i = 0; i < 6; i++)
		this->numer += to_string(rand() % 10);
	this->id_sklep = id_skl;
	this->koszt = koszt;
}
//funkcja tworzy pozycjê na paragonie i dodaje j¹ do wektora pozycji na paragonie
void Paragon::dodaj_pozycje(int licznik_pozycji, int id_prod, string nazwa, string t, double il,double cena)
{
	Produkt p1(0,connect);
	p1.id_produkt = id_prod;
	p1.nazwa = nazwa;
	p1.typ = t;
	p1.cena_netto = il;
	p1.cena_brutto = cena;
	pozycje.push_back(p1);
}
//dodaje paragon do bazy danych
void Paragon::dodaj()
{
	string insert = "INSERT INTO paragon (numer,id_sklep,data,koszt) VALUES('" + this->numer + "','" + to_string(this->id_sklep) + "',NOW(),'" + to_string(this->koszt)+"');";
	const char * c_char = insert.c_str();
	bool query_check = mysql_query(connect, c_char);
	if (query_check == 0)
		cout << "Paragon zostal dodany" << endl;
	else
		cout << "Dodanie paragonu nie powiodlo sie" << endl;
}
//funkcja pobiera id paragonu o podanym numerze
int Paragon::wez_id(string numer)
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	int id;

	string tekst = "SELECT id_paragon FROM paragon where numer = '" + numer + "';";
	const char * c_char = tekst.c_str();
	mysql_query(connect, c_char);

	idzapytania = mysql_store_result(connect);
	int num_wierszy = mysql_num_rows(idzapytania);
	int num_kolumn = mysql_num_fields(idzapytania);
	while (((wiersz = mysql_fetch_row(idzapytania)) != NULL))
	{
		id = stoi(wiersz[0]);
	}
	return id;
}
//funkcja wpisuje do bazy danych pozycje tworzonego paragonu
void Paragon::aktualiuzj_pozycje()
{
	for (int i = 0; i < this->pozycje.size(); i++)
	{
		string insert = "INSERT INTO paragon_pozycja (id_paragon,id_produkt,nazwa,typ,ilosc,cena,koszt) VALUES('" + to_string(this->wez_id(this->numer)) + "','"+to_string(pozycje[i].id_produkt)+"','" + pozycje[i].nazwa + "','"+pozycje[i].typ+"','"+to_string(pozycje[i].cena_netto)+"','"+to_string(pozycje[i].cena_brutto)+"','"+to_string(pozycje[i].cena_netto * pozycje[i].cena_brutto)+"');";
		const char * c_char = insert.c_str();
		bool query_check = mysql_query(connect, c_char);
		if (query_check == 0)
			cout << "Pozycja " << i+1 << " paragonu zostala dodana" << endl;
		else
			cout << "Dodanie pozycji "<< i+1 << " nie powiodlo sie" << endl;
	}
}
//funkcja wyœwietla tablice paragon
void Paragon::wyswietl()
{
	cout << "PARAGONY" << endl;
	cout << "#####################" << endl;
	cout << "| id_paragon | numer | id_sklep |data|koszt|" << endl;
	cout << "=====================" << endl;
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;

	mysql_query(connect, "SELECT * FROM paragon;");

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
}
//funkcja sprawdza czy paragon o podanym id istnieje w bazie danych
bool Paragon::sprawdz(int id_paragon)
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	string str_check = "SELECT * FROM sklep WHERE numer='" + this->numer + "';";
	const char * c_char = str_check.c_str();
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
//funkcja wyœwietla pozycje wybranego paragonu
void Paragon::wyswietl_dane()
{
	int id;
	double suma=0;
	this->wyswietl();
	cout << "=====================" << endl;
	cout << "Podaj id paragonu do wyswietlenia: ";
	cin >> id;
	if (this->sprawdz(id))
	{
		system("cls");
		cout << "Paragon o id " << id << endl;
		cout << "|id_produkt| nazwa | typ | cena | koszt |" << endl;
		cout << "=====================" << endl;
		MYSQL_RES *idzapytania;
		MYSQL_ROW wiersz;

		string linia = "SELECT id_produkt,nazwa,typ,cena,koszt FROM paragon_pozycja WHERE id_paragon = '" + to_string(id) + "';";
		const char *c_char = linia.c_str();
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
			suma += stod(wiersz[4]);
		}
		cout << endl << "Koszt calkowity: " << suma << endl;
		
	}
	else
		cout << "Nie ma paragonu o podanym id" << endl;
}
