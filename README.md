# README
### projekt_sieci_sklepow jest projektem z przedmiotu Programowanie Obiektowe. Celem projektu była implementacja systemu do zarządania siecią sklepów spożywczych.

## Założenia
System musi umożliwiać:
1. Zarządzanie poszczególnymi sklepami(wstaw, usuń, edytuj)
1. Zarządzanie produktami
1. Wprowadzenie stanów magazynowych produktów  w magazynie
1. Wprowadzanie stanów magazynowych w poszczególnych sklepach
1. Informacja o kończeniu się zapasów magazynowych
1. Sprzedaż produktów
1. Realizacja list zakupowych (zamówień)
1. Zapisywanie historii zrealizowanych zakupów
1. Wystawianie paragonu (w konsoli/pliku) za zakupione produkty
1. Zapis i odczyt stanu aplikacji (plik/baza danych)
1. Walidację wprowadzanych danych

Ponadto, w implementacji należy wykorzystać:
1. Wykorzystać dziedziczenie
1. Wykorzystać kompozycję
1. Wykorzystać funkcje wirtualne
1. Wykorzystać szablon klas
1. Wykorzystać szablon funkcji

## Opis uruchomienia
Aby poprawnie uruchomić program należy:
1. Pobrać wszystkie pliki z repozytorium
1. Bazę danych załączoną do projektu importujemy za pomocą programu [XAMPP](https://www.apachefriends.org/pl/index.html). System jest skonfigurowany by łączyć się z bazą danych na localhost. Aby zmienić konfiguracę należy zmienić parametry funkcji **mysql_real_connect** w pliku **Siec.cpp**.
1. Pobrać MySQL Connector/C++ najlepiej z [oficjalnej strony MySQL](https://dev.mysql.com/downloads/connector/cpp/8.0.html). Następnie w środowisku Visual Studio we właściwościach projektu należy wprowadzić lokalizację folderów:
    * *include* w zakładce C/C++ w polu Dodatkowe katalogii plików nagłówkowych
    * *lib* w zakładce Konsolidator w polu Dodatkowe katalogii biblioteki

## Opis implementacji
Program został napisany w języki C++. Program na początku swojego działania próbuje nawiązać połączenie z bazą danych. Jeśli uzyska on połączenie, następuje próba zalogowania. Program został podzielony na 3 funkcjonalne menu, osobno dla każdego rodzaju użytkownika.
Dane do logowania dla poszczególnych poziomów:
1. Poziom administratora:
   * Login: admin
   * Hasło: admin
1. Poziom kierownika sklepu:
   * Login: wl123
   * Hasło: wl123
1. Poziom klienta:
   * Login: kl123
   * Hasło: kl123
   
Po zalogowaniu się do konkretnego poziomu pojawia się menu z opcjami wyboru działania. Zależnie od poziomu, menu różni się dostępnością opcji, na przykład edycja sklepów oraz stanu produktów w sklepie nie jest dostępna dla użytkownika z poziomu klienta.

Program jest napisany obiektowo. Każda klasa zawiera się w oddzielnym pliku. Klasy odpowiedzlane są za obsługę konkretnych tabel. Poprzez wywoływanie odpowiednich metod zostają wygenerowane polecenia w język SQL które są przesyłane do bazy danych. Za ich pomocą w tabelach są dodawane,usuwane lub edytowane wiersze. Dodatkowo dołączone zostały pliki zamowienie.cpp oraz sprzedaz.cpp zawierające zestawy funkcji odpowiedzialne odpowiedznio za zamawianie towarów do sklepu oraz kupno towarów ze sklepu.

Program został zabespieczony przed błędami. Jeśli użytkownik wykona czynność, która jest niedozwolona w założeniach programu i/lub logice bazy danych, zostanie on o tym poinformowany stosownym komunikatem.
