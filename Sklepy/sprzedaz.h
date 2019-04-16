#pragma once

void sprzedaz(MYSQL *connect);
bool sprawdz_sklep(MYSQL *connect, int id_sklep);
double podaj_cene(MYSQL *connect, int id_produkt);
void aktualizuj_sklep(MYSQL *connect, int id_sklep, int koszt);
void aktualizuj_stan(MYSQL *connect, int id_sklep, int id_produkt, int ilosc_kupiona, int ilosc);
double podaj_obrot(MYSQL *connect, int id_sklep);
bool sprawdz_id_sklep(MYSQL *connect, int id_sklep, int id_produkt);
double pod_ilosc();