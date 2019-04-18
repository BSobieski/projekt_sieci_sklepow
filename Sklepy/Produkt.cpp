#include "pch.h"
#include "Produkt.h"

//konstruktor klasy
Produkt::Produkt(int a, MYSQL *c)
{
	this->connect = c;
	this->id_produkt = a;
	this->nazwa = "";
	this->cena_brutto = 0.0;
	this->cena_netto = 0.0;
	this->typ = "";
	this->dostepnosc = false;
}
//sprawdzenie czy produkt o podanej nazwie znajduje siê w bazie danych
bool Produkt::sprawdz()
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	string str_check = "SELECT * FROM produkt WHERE nazwa='" + this->nazwa + "';";
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
//stworzenie produktu
void Produkt::stworz()
{
	cout << "Podaj nazwe: ";
	getline(cin, this->nazwa);
	cout << "Podaj cene brutto: ";
	cin >> this->cena_brutto;
	this->cena_netto = this->cena_brutto - (this->cena_brutto*0.05);
	int flag = 1;
	int war;
	while (flag)
	{
		cout << "Ustal typ produktu (1 - kg, 2 - sztuka): ";
		cin >> war;
		switch (war)
		{
		case 1:
			this->typ = "kg";
			flag = 0;
			break;
		case 2:
			this->typ = "sztuka";
			flag = 0;
			break;
		default:
			cout << "Niepoprawny ustalony typ protuktu. Ustal jeszcze raz" << endl;
			break;
		}
	}
	flag = 1;
	while (flag)
	{
		cout << "Ustal dostepnosc (1 - dostepny, 0 - niedostepny): ";
		cin >> war;
		switch (war)
		{
		case 1:
			this->dostepnosc = true;
			flag = 0;
			break;
		case 0:
			this->dostepnosc = false;
			flag = 0;
			break;
		default:
			cout << "Niepoprawny ustalona dostepnosc. Ustal jeszcze raz" << endl;
			break;
		}
	}
}
//dodanie produktu do bazy danych
void Produkt::dodaj()
{
	string insert = "INSERT INTO produkt (nazwa,cena_brutto,cena_netto,typ,dostepnosc) VALUES('" + this->nazwa + "','" + to_string(this->cena_brutto) + "','" + to_string(this->cena_netto) + "','"+ this->typ+"','"+ to_string(this->dostepnosc) + "');";
	const char * c_char = insert.c_str();
	bool query_check = mysql_query(connect, c_char);
	if (query_check == 0)
		cout << "Produkt zostal dodany." << endl;
	else
		cout << "Dodanie produktu nie powiodlo sie" << endl;
}
//wyœwietlenie tabeli produkt
void Produkt::wyswietl()
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;

	mysql_query(connect, "SELECT * FROM produkt;");

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
//usuniecie produktu o wybranym id
void Produkt::usun()
{
	cout << "Podaj ID produktu, ktory chcesz usunac: ";
	cin >> this->id_produkt;
	if (sprawdz_id(this->id_produkt))
	{
		ostringstream i_to_str;
		i_to_str << this->id_produkt;
		string i_string = i_to_str.str();
		string str_delete = "DELETE FROM produkt WHERE id_produkt ='" + i_string + "';";
		const char * c_char = str_delete.c_str();
		bool query_check = mysql_query(connect, c_char);
		if (query_check == 0)
			cout << "Usuniecie produktu powiodlo sie." << endl;
		else
			cout << "Usuniecie produktu nie powiodlo sie" << endl;
	}
	else
		cout << "Nie ma produktu o podanym id" << endl;

}
//edycja danych o wybranym produkcie w bazie danych
void Produkt::edytuj()
{
	Produkt *edytor = new Produkt(0, connect);
	cout << "Wybierz ID produktu do edycji: ";
	cin >> edytor->id_produkt;
	if (sprawdz_id(edytor->id_produkt))
	{
		int war = -1;
		ostringstream i_to_str;
		string str_update;
		i_to_str << edytor->id_produkt;
		string id_string = i_to_str.str();
		cout << "1. Nazwa" << endl;
		cout << "2. Cena brutto" << endl;
		cout << "3. Dotepnosc" << endl;
		cout << "4. Typ produktu" << endl;
		cout << "0. Wstecz" << endl;
		cin >> war;
		bool warunek;
		switch (war)
		{
		case 1:
			cin.ignore();
			cout << "Podaj nazwe: ";
			getline(cin, edytor->nazwa);
			str_update = "UPDATE produkt SET nazwa ='" + edytor->nazwa + "'WHERE id_produkt=" + id_string + ";";
			break;
		case 2:
			cin.ignore();
			cout << "Podaj cene brutto: ";
			cin >> edytor->cena_brutto;
			edytor->cena_netto = edytor->cena_brutto - (edytor->cena_brutto*0.05);
			str_update = "UPDATE produkt SET cena_brutto ='" + to_string(edytor->cena_brutto) + "', cena_netto='" + to_string(edytor->cena_netto) + "'WHERE id_produkt=" + id_string + ";";
			break;
		case 3:
			warunek = true;
			int war1;
			while (warunek)
			{
				cout << "Ustal dostepnosc (1 - dostepny, 0 - niedostepny): ";
				cin >> war1;
				switch (war1)
				{
				case 1:
					edytor->dostepnosc = true;
					warunek = false;
					break;
				case 0:
					edytor->dostepnosc = false;
					warunek = false;
					break;
				default:
					cout << "Niepoprawny ustalona dostepnosc. Ustal jeszcze raz" << endl;
					break;
				}
			}
			str_update = "UPDATE produkt SET dostepnosc ='" + to_string(edytor->dostepnosc) + "'WHERE id_produkt=" + id_string + ";";
			break;
		case 4:
			warunek = true;
			int war2;
			while (warunek)
			{
				cout << "Ustal typ produktu (1 - kg, 2 - sztuka): ";
				cin >> war2;
				switch (war2)
				{
				case 1:
					edytor->typ = "kg";
					warunek = 0;
					break;
				case 2:
					edytor->typ = "sztuka";
					warunek = 0;
					break;
				default:
					cout << "Niepoprawny ustalony typ protuktu. Ustal jeszcze raz" << endl;
					break;
				}
			}
			str_update = "UPDATE produkt SET typ ='" + edytor->typ + "'WHERE id_produkt=" + id_string + ";";
			break;
		case 0:
			break;
		default:
			cout << "Brak takiej opcji" << endl;
			break;
		}
		if (edytor->sprawdz())
		{
			const char * c_char = str_update.c_str();
			bool query_check = mysql_query(connect, c_char);
			if (query_check == 0)
				cout << "Edycja produktu powiodla sie." << endl;
			else
				cout << "Edycja produktu nie powiodla sie" << endl;
		}
		else
			cout << "Podany produkt juz istnieje w bazie danych" << endl;
	}
	else
		cout << "Nie ma produktu o podanym id" << endl;
}
//sprawdzenie czy produkt o podanym id znajduje siê w bazie danych
bool Produkt::sprawdz_id(int id_produkt)
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