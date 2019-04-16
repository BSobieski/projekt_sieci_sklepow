#include "pch.h"
#include "Sklep.h"
#include "Magazyn.h"
#include "Produkt.h"
#include "Stan.h"
#include "Stan.cpp"
#include "sprzedaz.h"
#include "zamowienie.h"
#include "Paragon.h"

using namespace std;

void obsluga_sklep(Sklep *s1, MYSQL *connect);
void obsluga_magazyn(Sklep *s1, MYSQL *connect);
void obsluga_produkt(Produkt *p1);
void obsluga_stan_sklep(Stan<Sklep> *stan_sklep, int id_cel);
void obsluga_stan_magazyn(Stan<Magazyn> *stan_magazyn, int id_cel);
void raporty_magazynow(MYSQL *connect);
void raporty_sklepow(MYSQL *connect);
void aktualizuj_produkty(MYSQL *connect);
void logowanie(MYSQL *connect);
void menu_admin(MYSQL *connect);
void menu_klient(MYSQL *connect);
void menu_kierownik(MYSQL *connect);

int main()
{
	MYSQL *connect;
	connect = mysql_init(NULL);
	connect = mysql_real_connect(connect, "localhost", "root", "", "sklepy", 0, NULL, 0);
	if (!connect)
	{
		cout << "Polaczenie nie udane" << endl;
		exit(EXIT_FAILURE);
	}
	cout << "Polaczenie udane" << endl;
	system("PAUSE");
	system("cls");
	logowanie(connect);
	return 0;
}

void menu_kierownik(MYSQL *connect)
{
	Sklep *wskaznik;
	Sklep obiekt_sklep(0, connect);
	Magazyn obiekt_magazyn(0, connect);
	Produkt *p1 = new Produkt(0, connect);
	int opcja = -1;
	while (opcja != 0)
	{
		system("cls");
		cout << "1. Sklepy" << endl;
		cout << "2. Magazyny" << endl;
		cout << "3. Produkty" << endl;
		cout << "4. Raporty" << endl;
		cout << "5. Zamowienie z magazynu" << endl;
		cout << "0. Wyjscie z programu" << endl;
		cin >> opcja;
		switch (opcja)
		{
		case 1:
			aktualizuj_produkty(connect);
			wskaznik = &obiekt_sklep;
			obsluga_sklep(wskaznik, connect);
			break;
		case 2:
			aktualizuj_produkty(connect);
			wskaznik = &obiekt_magazyn;
			obsluga_magazyn(wskaznik, connect);
			break;
		case 3:
			obsluga_produkt(p1);
			break;
		case 4:
			system("cls");
			raporty_sklepow(connect);
			raporty_magazynow(connect);
			system("PAUSE");
			break;
		case 5:
			zamowienie(connect);
			system("PAUSE");
			break;
		case 0:
			return;
			break;
		default:
			cout << "Brak takiej opcji" << endl;
			break;
		}
	}
}

void menu_klient(MYSQL *connect)
{
	Sklep obiekt_sklep(0, connect);
	Magazyn obiekt_magazyn(0, connect);
	Produkt obiekt_produkt(0, connect);
	Paragon *paragon1 = new Paragon(connect);
	int opcja = -1;
	while (opcja != 0)
	{
		system("cls");
		cout << "1. Sklepy" << endl;
		cout << "2. Magazyny" << endl;
		cout << "3. Produkty" << endl;
		cout << "4. Paragony" << endl;
		cout << "6. Sprzedaz" << endl;
		cout << "0. Wyjscie z programu" << endl;
		cin >> opcja;
		switch (opcja)
		{
		case 1:
			system("cls");
			obiekt_sklep.wyswietl();
			system("PAUSE");
			break;
		case 2:
			system("cls");
			obiekt_magazyn.wyswietl();
			system("PAUSE");
			break;
		case 3:
			system("cls");
			obiekt_produkt.wyswietl();
			system("PAUSE");
			break;
		case 4:
			system("cls");
			paragon1->wyswietl_dane();
			system("PAUSE");
			break;
		case 6:
			sprzedaz(connect);
			system("PAUSE");
			break;
		case 0:
			return;
			break;
		default:
			cout << "Brak takiej opcji" << endl;
			break;
		}
	}
}

void logowanie(MYSQL *connect)
{
	int flag = 1;
	string login,haslo;
	while (flag)
	{
	cout << "Podaj login: ";
	cin >> login;
	if (login == "admin" || login == "kl123" || login == "wl123")
	{
		cout << "Podaj haslo: ";
		cin >> haslo;
		if (haslo == "admin")
			menu_admin(connect);
		else if (haslo == "kl123")
			menu_klient(connect);
		else if (haslo == "wl123")
			menu_kierownik(connect);
		else
			cout << "Bledne haslo" << endl;
		flag = 0;
	}
	else
		cout << "Brak podanego loginu w bazie. Podaj jeszcze raz" << endl;
	}

}

void menu_admin(MYSQL *connect)
{
	Sklep *wskaznik;
	Sklep obiekt_sklep(0, connect);
	Magazyn obiekt_magazyn(0, connect);
	Produkt *p1 = new Produkt(0, connect);
	Paragon *paragon1 = new Paragon(connect);
	int opcja = -1;
	while (opcja != 0)
	{
		system("cls");
		cout << "1. Sklepy" << endl;
		cout << "2. Magazyny" << endl;
		cout << "3. Produkty" << endl;
		cout << "4. Paragony" << endl;
		cout << "5. Raporty" << endl;
		cout << "6. Sprzedaz" << endl;
		cout << "7. Zamowienie z magazynu" << endl;
		cout << "0. Wyjscie z programu" << endl;
		cin >> opcja;
		switch (opcja)
		{
		case 1:
			aktualizuj_produkty(connect);
			wskaznik = &obiekt_sklep;
			obsluga_sklep(wskaznik, connect);
			break;
		case 2:
			aktualizuj_produkty(connect);
			wskaznik = &obiekt_magazyn;
			obsluga_magazyn(wskaznik, connect);
			break;
		case 3:
			obsluga_produkt(p1);
			break;
		case 4:
			system("cls");
			paragon1->wyswietl_dane();
			system("PAUSE");
			break;
		case 5:
			system("cls");
			raporty_sklepow(connect);
			raporty_magazynow(connect);
			system("PAUSE");
			break;
		case 6:
			sprzedaz(connect);
			system("PAUSE");
			break;
		case 7:
			zamowienie(connect);
			system("PAUSE");
			break;
		case 0:
			return;
			break;
		default:
			cout << "Brak takiej opcji" << endl;
			break;
		}
	}
}

void obsluga_sklep(Sklep *s1,MYSQL *connect)
{
	Stan<Sklep> *stan_sklep = new Stan<Sklep>(0, connect);
	int id_celu;
	int opcjain = -1;
	while (opcjain != 0)
	{
		system("cls");
		cout << "SKLEPY" << endl;
		cout << "#####################" << endl;
		cout << "| id | numer | miasto |adres|kod pocztowy|obrot|dostepnosc|" << endl;
		cout << "=====================" << endl;
		s1->wyswietl();
		cout << "#####################" << endl;
		cout << "1. Dodaj" << endl;
		cout << "2. Edytuj" << endl;
		cout << "3. Usun" << endl;
		cout << "4. Stan sklepu" << endl;
		cout << "0. Wstecz" << endl;
		cout << "#####################" << endl;
		cin >> opcjain;
		switch (opcjain)
		{
		case 1:
			cin.ignore();
			s1->stworz();
			if (s1->sprawdz())
				s1->dodaj();
			else
				cout << "Podany sklep istnieje w bazie danych" << endl;
			system("PAUSE");
			break;
		case 2:
			s1->edytuj();
			system("PAUSE");
			break;
		case 3:
			s1->usun();
			system("PAUSE");
			break;
		case 4:
			cout << "Podaj id sklepu: ";
			cin >> id_celu;
			if(s1->sprawdz_id(id_celu))
				obsluga_stan_sklep(stan_sklep, id_celu);
			else
			{
				cout << "Nie ma sklpu o podanym id" << endl;
				system("PAUSE");
			}
			break;
		case 0:
			break;
		default:
			cout << "Brak takiej opcji" << endl;
			system("PAUSE");
			break;
		}
	}
}

void obsluga_magazyn(Sklep *s1, MYSQL *connect)
{
	Stan<Magazyn> *stan_magazyn = new Stan<Magazyn>(0, connect);
	int id_celu;
	int opcjain = -1;
	while (opcjain != 0)
	{
		system("cls");
		cout << "MAGAZYNY" << endl;
		cout << "#####################" << endl;
		cout << "| id | numer |miasto |adres|kod pocztowy|dostepnosc|" << endl;
		cout << "=====================" << endl;
		s1->wyswietl();
		cout << "#####################" << endl;
		cout << "1. Dodaj" << endl;
		cout << "2. Edytuj" << endl;
		cout << "3. Usun" << endl;
		cout << "4. Stan magazynu" << endl;
		cout << "0. Wstecz" << endl;
		cout << "#####################" << endl;
		cin >> opcjain;
		switch (opcjain)
		{
		case 1:
			cin.ignore();
			s1->stworz();
			if (s1->sprawdz())
				s1->dodaj();
			else
				cout << "Podany magazyn istnieje w bazie danych" << endl;
			system("PAUSE");
			break;
		case 2:
			s1->edytuj();
			system("PAUSE");
			break;
		case 3:
			s1->usun();
			system("PAUSE");
			break;
		case 4:
			cout << "Podaj id magazynu: ";
			cin >> id_celu;
			if(s1->sprawdz_id(id_celu))
				obsluga_stan_magazyn(stan_magazyn, id_celu);
			else
			{
				cout << "Nie ma magazynu o wybranym id" << endl;
				system("PAUSE");
			}
			break;
		case 0:
			break;
		default:
			cout << "Brak takiej opcji" << endl;
			system("PAUSE");
			break;
		}
	}
}

void obsluga_produkt(Produkt *p1)
{
	int opcjain = -1;
	while (opcjain != 0)
	{
		system("cls");
		cout << "PRODUKTY" << endl;
		cout << "#####################" << endl;
		cout << "| id |nazwa|cena brutto|cena netto|typ|dostepnosc|" << endl;
		cout << "=====================" << endl;
		p1->wyswietl();
		cout << "#####################" << endl;
		cout << "1. Dodaj" << endl;
		cout << "2. Edytuj" << endl;
		cout << "3. Usun" << endl;
		cout << "0. Wstecz" << endl;
		cout << "#####################" << endl;
		cin >> opcjain;
		switch (opcjain)
		{
		case 1:
			cin.ignore();
			p1->stworz();
			if (p1->sprawdz())
				p1->dodaj();
			else
				cout << "Podany produkt istnieje w bazie danych" << endl;
			system("PAUSE");
			break;
		case 2:
			p1->edytuj();
			system("PAUSE");
			break;
		case 3:
			p1->usun();
			system("PAUSE");
			break;
		case 0:
			break;
		default:
			cout << "Brak takiej opcji" << endl;
			system("PAUSE");
			break;
		}
	}
}

void obsluga_stan_sklep(Stan<Sklep> *stan_sklep, int id_cel)
{	
	stan_sklep->ustaw_cel(id_cel);
	int opcjain = -1;
	while (opcjain != 0)
	{
		system("cls");
		cout << "STAN sklepu o id " << id_cel << endl;
		cout << "#####################" << endl;
		cout << "| id_produktu | nazwa | typ |dostepnosc|ilosc|" << endl;
		cout << "=====================" << endl;
		stan_sklep->wyswietl();
		cout << "#####################" << endl;
		cout << "1. Dodaj" << endl;
		cout << "2. Edytuj ilosc" << endl;
		cout << "3. Usun" << endl;
		cout << "0. Wstecz" << endl;
		cout << "#####################" << endl;
		cin >> opcjain;
		switch (opcjain)
		{
		case 1:
			cin.ignore();
			stan_sklep->stworz();
			if (stan_sklep->sprawdz())
				stan_sklep->dodaj();
			else
				cout << "Podany produkt istnieje juz na stanie sklepu" << endl;
			system("PAUSE");
			break;
		case 2:
			stan_sklep->edytuj_ilosc();
			system("PAUSE");
			break;
		case 3:
			stan_sklep->usun();
			system("PAUSE");
			break;
		case 0:
			break;
		default:
			cout << "Brak takiej opcji" << endl;
			system("PAUSE");
			break;
		}
	}
}

void obsluga_stan_magazyn(Stan<Magazyn> *stan_magazyn, int id_cel)
{
	stan_magazyn->ustaw_cel(id_cel);
	int opcjain = -1;
	while (opcjain != 0)
	{
		system("cls");
		cout << "STAN magazynu o id " << id_cel << endl;
		cout << "#####################" << endl;
		cout << "| id_produktu | nazwa | typ |ilosc|" << endl;
		cout << "=====================" << endl;
		stan_magazyn->wyswietl();
		cout << "#####################" << endl;
		cout << "1. Dodaj" << endl;
		cout << "2. Edytuj ilosc" << endl;
		cout << "3. Usun" << endl;
		cout << "0. Wstecz" << endl;
		cout << "#####################" << endl;
		cin >> opcjain;
		switch (opcjain)
		{
		case 1:
			cin.ignore();
			stan_magazyn->stworz();
			if (stan_magazyn->sprawdz())
				stan_magazyn->dodaj();
			else
				cout << "Podany produkt istnieje juz na stanie sklepu" << endl;
			system("PAUSE");
			break;
		case 2:
			stan_magazyn->edytuj_ilosc();
			system("PAUSE");
			break;
		case 3:
			stan_magazyn->usun();
			system("PAUSE");
			break;
		case 0:
			break;
		default:
			cout << "Brak takiej opcji" << endl;
			system("PAUSE");
			break;
		}
	}
}

void raporty_magazynow(MYSQL *connect)
{
	int id_magazyn, id_produkt, ilosc;
	string nazwa;
	cout << "Raporty Magazynow" << endl;
	cout << "#####################" << endl;
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;

	mysql_query(connect, "SELECT id_magazyn,id_produkt,nazwa,ilosc FROM stan WHERE id_magazyn IS NOT NULL;");

	idzapytania = mysql_store_result(connect);
	int num_wierszy = mysql_num_rows(idzapytania);
	int num_kolumn = mysql_num_fields(idzapytania);
	int i = 0;
	while (((wiersz = mysql_fetch_row(idzapytania)) != NULL))
	{
		id_magazyn = stoi(wiersz[0]);
		id_produkt = stoi(wiersz[1]);
		nazwa = wiersz[2];
		ilosc = stoi(wiersz[3]);
		if (ilosc > 0 && ilosc < 50)
		{
			cout << "Magazyn id " << id_magazyn << ": Produkt " << id_produkt << " o nazwie " << nazwa << " - zapaz w magazynie na wykonczeniu." << endl;
			i++;
		}
		else if (ilosc == 0)
		{
			cout << "Magazyn id " << id_magazyn << ": Produkt " << id_produkt << " o nazwie " << nazwa << " - brak produktu w magazynie." << endl;
			i++;
		}
	}
}

void raporty_sklepow(MYSQL *connect)
{
	int id_sklep, id_produkt, ilosc;
	string nazwa;
	cout << "Raporty Sklepow" << endl;
	cout << "#####################" << endl;
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;

	mysql_query(connect, "SELECT id_sklep,id_produkt,nazwa,ilosc FROM stan WHERE id_sklep IS NOT NULL;");

	idzapytania = mysql_store_result(connect);
	int num_wierszy = mysql_num_rows(idzapytania);
	int num_kolumn = mysql_num_fields(idzapytania);
	int i = 0;
	while (((wiersz = mysql_fetch_row(idzapytania)) != NULL))
	{
		id_sklep = stoi(wiersz[0]);
		id_produkt = stoi(wiersz[1]);
		nazwa = wiersz[2];
		ilosc = stoi(wiersz[3]);
		if (ilosc == 0)
		{
			cout << "Sklep id " << id_sklep << ": Produkt " << id_produkt << " o nazwie " << nazwa << " - brak produktu w sklepie." << endl;
			i++;
		}
	}
}

void aktualizuj_produkty(MYSQL *connect)
{
	MYSQL_RES *idzapytania;
	MYSQL_ROW wiersz;
	int id_produkt;
	string nazwa;
	string typ;
	bool dostepnosc;

	string update;
	const char *upd;
	string tekst = "SELECT id_produkt,nazwa,typ,dostepnosc FROM produkt;";
	const char * c_char = tekst.c_str();
	mysql_query(connect, c_char);
	idzapytania = mysql_store_result(connect);
	if (idzapytania != NULL)
	{
		int num_wierszy = mysql_num_rows(idzapytania);
		int num_kolumn = mysql_num_fields(idzapytania);
		while (((wiersz = mysql_fetch_row(idzapytania)) != NULL))
		{
			id_produkt = stoi(wiersz[0]);
			nazwa = wiersz[1];
			typ = wiersz[2];
			dostepnosc = stoi(wiersz[3]);
			update = "UPDATE stan SET nazwa='" + nazwa + "',typ='" + typ + "',dostepnosc='" + to_string(dostepnosc) + "' WHERE id_produkt='" + to_string(id_produkt) + "'";
			upd = update.c_str();
			mysql_query(connect, upd);
		}
	}
}