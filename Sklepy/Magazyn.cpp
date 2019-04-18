#include "pch.h"
#include "Magazyn.h"

//konstruktor klasy
Magazyn::Magazyn(int a, MYSQL *c) : Sklep(0,c)
{
	this->id_magazyn = a;
	this->connect = c;
	this->numer = "";
	this->miasto = "";
	this->adres = "";
	this->kod_pocztowy = "";
	this->dostepnosc=false;
}
//sprawdzenie czy w bazie danych istnieje magazyn o podanym numerze
bool Magazyn::sprawdz()
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	string str_check = "SELECT * FROM magazyn WHERE numer='" + this->numer + "';";
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
//stworzenie magazynu
void Magazyn::stworz()
{
	int flag = 1;
	while (flag)
	{
		cout << "Podaj numer magazynu (6 znakow): ";
		getline(cin, this->numer);
		if (numer.length() == 6)
			flag = 0;
		else
			cout << "Niepoprawny numer magazynu. Podaj jeszcze raz" << endl;
	}
	cout << "Podaj miasto: ";
	getline(cin, this->miasto);
	cout << "Podaj adres: ";
	getline(cin, this->adres);
	flag = 1;
	while (flag)
	{
		cout << "Podaj kod pocztowy: ";
		cin >> this->kod_pocztowy;
		if (kod_pocztowy.length() == 6 && kod_pocztowy[2] == '-')
			flag = 0;
		else
			cout << "Niepoprawny kod pocztowy. Podaj jeszcze raz" << endl;
	}
	flag = 1;
	int war;
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
//dodanie magazynu do bazy danych
void Magazyn::dodaj()
{
	string insert = "INSERT INTO magazyn (numer,miasto,adres,kod_pocztowy,dostepnosc) VALUES('"+this->numer+"','" + this->miasto + "','" + this->adres + "','" + this->kod_pocztowy + "','" + to_string(this->dostepnosc) + "');";
	const char * c_char = insert.c_str();
	bool query_check = mysql_query(connect, c_char);
	if (query_check == 0)
		cout << "Magazyn zostal dodany." << endl;
	else
		cout << "Dodanie magazynu nie powiodlo sie" << endl;
}
//wyswietlenie tabeli magazyn
void Magazyn::wyswietl()
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;

	mysql_query(connect, "SELECT * FROM magazyn;");

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
//usuniecie magazynu o wybranym id z bazy danych
void Magazyn::usun()
{
	cout << "Podaj ID magazynu, ktory chcesz usunac: ";
	cin >> this->id_magazyn;
	if (sprawdz_id(this->id_magazyn))
	{
		ostringstream i_to_str;
		i_to_str << this->id_magazyn;
		string i_string = i_to_str.str();
		string str_delete = "DELETE FROM magazyn WHERE id_magazyn ='" + i_string + "';";
		const char * c_char = str_delete.c_str();
		bool query_check = mysql_query(connect, c_char);
		if (query_check == 0)
			cout << "Usuniecie magazynu powiodlo sie." << endl;
		else
			cout << "Usuniecie magazynu nie powiodlo sie" << endl;
	}
	else
		cout << "Nie ma magazynu o wybranym id" << endl;
}
//edycja danych o wybranym magazynie w bazie danych
void Magazyn::edytuj()
{
	Magazyn *edytor = new Magazyn(0, connect);
	cout << "Wybierz ID magazynu do edycji: ";
	cin >> edytor->id_magazyn;
	if (sprawdz_id(edytor->id_magazyn))
	{
		int war = -1;
		ostringstream i_to_str;
		string str_update;
		i_to_str << edytor->id_magazyn;
		string id_string = i_to_str.str();
		cout << "1. Numer" << endl;
		cout << "2. Miasto" << endl;
		cout << "3. Adres" << endl;
		cout << "4. Kod pocztowy" << endl;
		cout << "5. Dostepnosc" << endl;
		cout << "0. Wstecz" << endl;
		cin >> war;
		bool warunek;
		switch (war)
		{
		case 1:
			cin.ignore();
			warunek = true;
			while (warunek)
			{
				cout << "Podaj numer magazynu (6 znakow): ";
				getline(cin, edytor->numer);
				if (edytor->numer.length() == 6)
					warunek = false;
				else
					cout << "Niepoprawny numer magazynu. Podaj jeszcze raz" << endl;
			}
			str_update = "UPDATE magazyn SET numer ='" + edytor->numer + "'WHERE id_magazyn=" + id_string + ";";
			break;
		case 2:
			cin.ignore();
			cout << "Podaj miasto: ";
			getline(cin, edytor->miasto);
			str_update = "UPDATE magazyn SET miasto ='" + edytor->miasto + "'WHERE id_magazyn=" + id_string + ";";
			break;
		case 3:
			cin.ignore();
			cout << "Podaj adres: ";
			getline(cin, edytor->adres);
			str_update = "UPDATE magazyn SET adres ='" + edytor->adres + "'WHERE id_magazyn=" + id_string + ";";
			break;
		case 4:
			warunek = true;
			while (warunek)
			{
				cin.ignore();
				cout << "Podaj kod pocztowy: ";
				getline(cin, edytor->kod_pocztowy);
				if (edytor->kod_pocztowy.length() == 6 && edytor->kod_pocztowy[2] == '-')
					warunek = false;
				else
					cout << "Niepoprawny kod pocztowy. Podaj jeszcze raz" << endl;
			}
			str_update = "UPDATE magazyn SET kod_pocztowy ='" + edytor->kod_pocztowy + "'WHERE id_magazyn=" + id_string + ";";
			break;
		case 5:
			warunek = true;
			int war;
			while (warunek)
			{
				cout << "Ustal dostepnosc (1 - dostepny, 0 - niedostepny): ";
				cin >> war;
				switch (war)
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
			str_update = "UPDATE magazyn SET dostepnosc ='" + to_string(edytor->dostepnosc) + "'WHERE id_magazyn=" + id_string + ";";
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
				cout << "Edycja magazynu powiodla sie." << endl;
			else
				cout << "Edycja magazynu nie powiodla sie" << endl;
		}
		else
			cout << "Podany magazyn juz istnieje w bazie danych" << endl;
	}
	else
		cout << "Nie ma magazynu o wybranym id" << endl;
}
//sprawdzenie czy magazyn o podanym id znajduje sie w bazie danych
bool Magazyn::sprawdz_id(int id_magazyn)
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	string str_check = "SELECT * FROM magazyn WHERE id_magazyn ='" + to_string(id_magazyn) + "';";
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