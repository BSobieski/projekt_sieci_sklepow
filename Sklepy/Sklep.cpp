#include "pch.h"
#include "Sklep.h"
#include "Magazyn.h"

//konstruktor klasy
Sklep::Sklep(int a, MYSQL *c)
{
	this->connect = c;
	this->id_sklep = a;
	this->numer = "";
	this->miasto = "";
	this->adres = "";
	this->dostepnosc = false;
}
//funkcja sprawdzaj¹ca czy sklep o podanym numerze istnieje w bazie danych
bool Sklep::sprawdz()
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
//funkcja wtorz¹ca sklep
void Sklep::stworz()
{
	int flag = 1;
	while (flag)
	{
		cout << "Podaj numer sklepu (6 znakow): ";
		getline(cin, this->numer);
		if (numer.length() == 6)
			flag = 0;
		else
			cout << "Niepoprawny numer sklepu. Podaj jeszcze raz" << endl;
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
//funkcja dodaj¹ca sklep do bazy danych
void Sklep::dodaj()
{
	string insert = "INSERT INTO sklep (numer,miasto,adres,kod_pocztowy,dostepnosc) VALUES('" + this->numer + "','" + this->miasto + "','" + this->adres + "','" + this->kod_pocztowy + "','" + to_string(this->dostepnosc) + "');";
	const char * c_char = insert.c_str();
	bool query_check = mysql_query(connect, c_char);
	if (query_check == 0)
		cout << "Sklep zostal dodany." << endl;
	else
		cout << "Dodanie sklepu nie powiodlo sie" << endl;
}
//funkcja wyœwietlaj¹ca tabelê sklep
void Sklep::wyswietl()
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;

	mysql_query(connect, "SELECT * FROM sklep;");

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
//funkcja usuwaj¹ca sklep po id
void Sklep::usun()
{
	cout << "Podaj ID sklepu, ktory chcesz usunac: ";
	cin >> this->id_sklep;
	if (sprawdz_id(this->id_sklep))
	{
		ostringstream i_to_str;
		i_to_str << this->id_sklep;
		string i_string = i_to_str.str();
		string str_delete = "DELETE FROM sklep WHERE id_sklep ='" + i_string + "';";
		const char * c_char = str_delete.c_str();
		bool query_check = mysql_query(connect, c_char);
		if (query_check == 0)
			cout << "Usuniecie sklepu powiodlo sie." << endl;
		else
			cout << "Usuniecie sklepu nie powiodlo sie" << endl;
	}
	else
		cout << "Nie ma sklepu o wybranym id" << endl;
}
//funkcja edytuj¹ca dane o wybranym sklepie
void Sklep::edytuj()
{
	Sklep *edytor = new Sklep(0, connect);
	cout << "Wybierz ID sklepu do edycji: ";
	cin >> edytor->id_sklep;
	if (sprawdz_id(edytor->id_sklep))
	{
		int war = -1;
		ostringstream i_to_str;
		string str_update;
		i_to_str << edytor->id_sklep;
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
			warunek = true;
			while (warunek)
			{
				cin.ignore();
				cout << "Podaj numer sklepu (6 znakow): ";
				getline(cin, edytor->numer);
				if (edytor->numer.length() == 6)
					warunek = false;
				else
					cout << "Niepoprawny numer sklepu. Podaj jeszcze raz" << endl;
			}
			str_update = "UPDATE sklep SET numer ='" + edytor->numer + "'WHERE id_sklep=" + id_string + ";";
			break;
		case 2:
			cin.ignore();
			cout << "Podaj miasto: ";
			getline(cin, edytor->miasto);
			str_update = "UPDATE sklep SET miasto ='" + edytor->miasto + "'WHERE id_sklep=" + id_string + ";";
			break;
		case 3:
			cin.ignore();
			cout << "Podaj adres: ";
			getline(cin, edytor->adres);
			str_update = "UPDATE sklep SET adres ='" + edytor->adres + "'WHERE id_sklep=" + id_string + ";";
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
			str_update = "UPDATE sklep SET kod_pocztowy ='" + edytor->kod_pocztowy + "'WHERE id_sklep=" + id_string + ";";
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
			str_update = "UPDATE sklep SET dostepnosc ='" + to_string(edytor->dostepnosc) + "'WHERE id_sklep=" + id_string + ";";
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
				cout << "Edycja sklepu powiodla sie." << endl;
			else
				cout << "Edycja sklepu nie powiodla sie" << endl;
		}
		else
			cout << "Podany sklep juz istnieje w bazie danych" << endl;
	}
	else
		cout << "Nie ma sklpu o podanym id" << endl;
}
//funkcja sprawdzaj¹ca czy sklep o podanym id istnieje w bazie danych
bool Sklep::sprawdz_id(int id_sklep)
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	string str_check = "SELECT * FROM sklep WHERE id_sklep ='" + to_string(id_sklep) + "';";
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