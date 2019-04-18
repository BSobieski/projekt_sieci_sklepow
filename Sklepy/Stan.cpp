#include "pch.h"
#include "Stan.h"
#include "Produkt.h"
//W tej klasie wszystkie metody s¹ metodami-szablonami, poniewa¿ bêd¹ one zale¿a³y od wartoœci wskaŸnik

//konstruktor klasy
template <class Klasa>
Stan<Klasa>::Stan(int a, MYSQL *c)
{
	this->connect = c;
	this->wskaznik = new Klasa(0, connect);
	this->produkt = new Produkt(0, connect);
	this->id_stan = a;
	this->id_cel = 3;
	this->id_produkt = 0;
	this->nazwa = "";
	this->typ = "";
	this->ilosc = 0;
	this->dostepnosc = false;
}
//funkcja wyœwietla produkty
template <class Klasa>
void Stan<Klasa>::wyswietl_produkt()
{
	this->produkt->wyswietl();
}
//funkcja wyswietlaj¹ca stany konkretnej klasy
template <class Klasa>
void Stan<Klasa>::wyswietl()
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;

	string insert = "SELECT id_produkt,nazwa,typ,dostepnosc,ilosc FROM stan WHERE " + this->wskaznik->flaga + " = '" + to_string(this->id_cel) + "';";
	const char * c_char = insert.c_str();

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
}
//funkcja tworz¹ca stan
template <class Klasa>
void Stan<Klasa>::stworz()
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	this->wyswietl_produkt();
	cout << "Podaj id produktu: ";
	cin >> this->id_produkt;
	string insert = "SELECT nazwa,typ,dostepnosc FROM produkt WHERE id_produkt = " + to_string(this->id_produkt) + ";";
	const char * c_char = insert.c_str();

	mysql_query(connect, c_char);

	idzapytania = mysql_store_result(connect);
	int num_wierszy = mysql_num_rows(idzapytania);
	int num_kolumn = mysql_num_fields(idzapytania);
	int i = 0;
	while (((wiersz = mysql_fetch_row(idzapytania)) != NULL))
	{
		this->nazwa = wiersz[0];
		this->typ = wiersz[1];
		this->dostepnosc = stoi(wiersz[2]);
	}
	cout << "Podaj ilosc produktu: ";
	cin >> this->ilosc;
}
//funkcja dodaj¹ca stan do bazy danych
template <class Klasa>
void Stan<Klasa>::dodaj()
{
	string insert = "INSERT INTO stan ("+this->wskaznik->flaga+",id_produkt,nazwa,typ,dostepnosc,ilosc) VALUES('" + to_string(this->id_cel) + "','" + to_string(this->id_produkt) + "','" + this->nazwa + "','" + this->typ + "','" + to_string(this->dostepnosc) + "','" + to_string(this->ilosc) + "');";
	const char * c_char = insert.c_str();
	bool query_check = mysql_query(connect, c_char);
	if (query_check == 0)
		cout << "Stan zostal zaktualizowany." << endl;
	else
		cout << "Aktualizacja stanu nie powiodla sie" << endl;
}
//funkcja usuwaj¹ca stan z bazy danych
template <class Klasa>
void Stan<Klasa>::usun()
{
	cout << "Podaj ID produktu, ktory chcesz usunac: ";
	cin >> this->id_produkt;
	if (sprawdz_id(this->id_produkt))
	{
		ostringstream i_to_str;
		i_to_str << this->id_produkt;
		string i_string = i_to_str.str();
		string str_delete = "DELETE FROM stan WHERE id_produkt ='" + i_string + "' AND " + this->wskaznik->flaga + " = '" + to_string(this->id_cel) + "';";
		const char * c_char = str_delete.c_str();
		bool query_check = mysql_query(connect, c_char);
		if (query_check == 0)
			cout << "Usuniecie produktu ze stanu powiodlo sie." << endl;
		else
			cout << "Usuniecie produktu ze stanu nie powiodlo sie" << endl;
	}
	else
		cout << "Nie ma produktu o podanym id" << endl;

}
//funkcja edytuj¹ca iloœæ produktów w stanie
template <class Klasa>
void Stan<Klasa>::edytuj_ilosc()
{
	cout << "Podaj ID produktu, do edycji ilosci: ";
	cin >> this->id_produkt;
	if (sprawdz_id(this->id_produkt))
	{
		cout << "Podaj nowa ilosc: ";
		cin >> this->ilosc;
		string str_update = "UPDATE stan SET ilosc ='" + to_string(this->ilosc) + "'WHERE id_produkt=" + to_string(this->id_produkt) + " AND " + this->wskaznik->flaga + " = '" + to_string(this->id_cel) + "';";
		const char * c_char = str_update.c_str();
		bool query_check = mysql_query(connect, c_char);
		if (query_check == 0)
			cout << "Edycja ilosci powiodla sie." << endl;
		else
			cout << "Edycja ilosci nie powiodla sie" << endl;
	}
	else
		cout << "Nie ma produktu o podanym id" << endl;
}
//funkcja sprawdzaj¹ca czy stan z podanym produktem istnieje w bazie danych
template <class Klasa>
bool Stan<Klasa>::sprawdz()
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	string str_check = "SELECT * FROM stan WHERE id_produkt='" + to_string(this->id_produkt) + "' AND " + this->wskaznik->flaga + " = '" + to_string(this->id_cel) + "';";
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
//funkcja ustawiaj¹ca zmienn¹ id_cel bêd¹c¹ id sklepu/magazynu
template <class Klasa>
void Stan<Klasa>::ustaw_cel(int a)
{
	this->id_cel = a;
}
//funkcja sprawdzaj¹ca czy produkt o podanym id istnieje w tabeli produktów
template <class Klasa>
bool Stan<Klasa>::sprawdz_id(int id_produkt)
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	string str_check = "SELECT * FROM produkt WHERE id_produkt ='" + to_string(id_produkt) + "';";
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