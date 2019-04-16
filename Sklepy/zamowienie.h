#pragma once

double podaj_ilosc(MYSQL *connect, int id_sklep, int id_produkt);
void zamowienie(MYSQL *connect);
int wyswietl_zawierajace(MYSQL *connect, int id_produkt);
bool sprawdz_stan(MYSQL *connect, int id_produkt, int id_sklep);
void dodaj_stan(MYSQL *connect, int id_sklep, int id_produkt, string typ, string nazwa, bool dostepnosc);
void aktualizuj_stan_magazyn(MYSQL *connect, double ilosc, double ilosc_pobrana, int id_magazyn, int id_produkt);
void aktualizuj_stan_sklep(MYSQL *connect, double ilosc, int id_sklep, int id_produkt);
bool sprawdz_id(MYSQL *connect, int id_magazyn, int id_produkt);
double pod_ilosc();