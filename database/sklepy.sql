-- phpMyAdmin SQL Dump
-- version 4.8.3
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Czas generowania: 17 Kwi 2019, 12:17
-- Wersja serwera: 10.1.37-MariaDB
-- Wersja PHP: 7.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Baza danych: `sklepy`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `magazyn`
--

CREATE TABLE `magazyn` (
  `id_magazyn` int(11) NOT NULL,
  `numer` varchar(6) NOT NULL,
  `miasto` varchar(50) NOT NULL,
  `adres` varchar(70) NOT NULL,
  `kod_pocztowy` varchar(6) NOT NULL,
  `dostepnosc` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Zrzut danych tabeli `magazyn`
--

INSERT INTO `magazyn` (`id_magazyn`, `numer`, `miasto`, `adres`, `kod_pocztowy`, `dostepnosc`) VALUES
(1, 'asd123', 'Warszawa', 'Gorczewska 12', '01-239', 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `paragon`
--

CREATE TABLE `paragon` (
  `id_paragon` int(11) NOT NULL,
  `numer` varchar(6) NOT NULL,
  `id_sklep` int(11) NOT NULL,
  `data` datetime NOT NULL,
  `koszt` float(12,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Zrzut danych tabeli `paragon`
--

INSERT INTO `paragon` (`id_paragon`, `numer`, `id_sklep`, `data`, `koszt`) VALUES
(1, '331219', 1, '2019-04-16 17:14:49', 50.00);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `paragon_pozycja`
--

CREATE TABLE `paragon_pozycja` (
  `id_pozycja` int(11) NOT NULL,
  `id_paragon` int(11) NOT NULL,
  `id_produkt` int(11) NOT NULL,
  `nazwa` varchar(50) NOT NULL,
  `typ` set('kg','sztuka') NOT NULL,
  `ilosc` float(8,2) NOT NULL,
  `cena` float(8,2) NOT NULL,
  `koszt` float(12,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Zrzut danych tabeli `paragon_pozycja`
--

INSERT INTO `paragon_pozycja` (`id_pozycja`, `id_paragon`, `id_produkt`, `nazwa`, `typ`, `ilosc`, `cena`, `koszt`) VALUES
(1, 1, 1, 'kukurydza', 'sztuka', 20.00, 2.50, 50.00);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `produkt`
--

CREATE TABLE `produkt` (
  `id_produkt` int(11) NOT NULL,
  `nazwa` varchar(50) NOT NULL,
  `cena_brutto` float(8,2) NOT NULL,
  `cena_netto` float(8,2) NOT NULL,
  `typ` set('kg','sztuka') NOT NULL,
  `dostepnosc` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Zrzut danych tabeli `produkt`
--

INSERT INTO `produkt` (`id_produkt`, `nazwa`, `cena_brutto`, `cena_netto`, `typ`, `dostepnosc`) VALUES
(1, 'kukurydza', 2.50, 2.38, 'sztuka', 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `sklep`
--

CREATE TABLE `sklep` (
  `id_sklep` int(11) NOT NULL,
  `numer` varchar(6) NOT NULL,
  `miasto` varchar(50) NOT NULL,
  `adres` varchar(70) NOT NULL,
  `kod_pocztowy` varchar(6) NOT NULL,
  `dostepnosc` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Zrzut danych tabeli `sklep`
--

INSERT INTO `sklep` (`id_sklep`, `numer`, `miasto`, `adres`, `kod_pocztowy`, `dostepnosc`) VALUES
(1, 'abc123', 'warszawa', 'czorsztyäska 2/11', '01-410', 1),
(2, 'asksjd', 'Krak¢w', 'Ziekona 3', '12-120', 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `stan`
--

CREATE TABLE `stan` (
  `id_stan` int(11) NOT NULL,
  `id_sklep` int(11) DEFAULT NULL,
  `id_magazyn` int(11) DEFAULT NULL,
  `id_produkt` int(11) NOT NULL,
  `nazwa` varchar(50) NOT NULL,
  `typ` set('kg','sztuka') NOT NULL,
  `dostepnosc` tinyint(1) NOT NULL,
  `ilosc` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Zrzut danych tabeli `stan`
--

INSERT INTO `stan` (`id_stan`, `id_sklep`, `id_magazyn`, `id_produkt`, `nazwa`, `typ`, `dostepnosc`, `ilosc`) VALUES
(1, 1, NULL, 1, 'kukurydza', 'sztuka', 1, 103),
(2, NULL, 1, 1, 'kukurydza', 'sztuka', 1, 0),
(3, 2, NULL, 1, 'kukurydza', 'sztuka', 1, 30);

--
-- Indeksy dla zrzutów tabel
--

--
-- Indeksy dla tabeli `magazyn`
--
ALTER TABLE `magazyn`
  ADD PRIMARY KEY (`id_magazyn`);

--
-- Indeksy dla tabeli `paragon`
--
ALTER TABLE `paragon`
  ADD PRIMARY KEY (`id_paragon`),
  ADD KEY `paragon_sklep_fk` (`id_sklep`);

--
-- Indeksy dla tabeli `paragon_pozycja`
--
ALTER TABLE `paragon_pozycja`
  ADD PRIMARY KEY (`id_pozycja`),
  ADD KEY `paragon_pozycja_fk` (`id_paragon`),
  ADD KEY `paragon_pozycja_produkt_fk` (`id_produkt`);

--
-- Indeksy dla tabeli `produkt`
--
ALTER TABLE `produkt`
  ADD PRIMARY KEY (`id_produkt`);

--
-- Indeksy dla tabeli `sklep`
--
ALTER TABLE `sklep`
  ADD PRIMARY KEY (`id_sklep`);

--
-- Indeksy dla tabeli `stan`
--
ALTER TABLE `stan`
  ADD PRIMARY KEY (`id_stan`),
  ADD KEY `stan_sklep_fk` (`id_sklep`),
  ADD KEY `stan_magazyn_fk` (`id_magazyn`),
  ADD KEY `stan_produkt_fk` (`id_produkt`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT dla tabeli `magazyn`
--
ALTER TABLE `magazyn`
  MODIFY `id_magazyn` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT dla tabeli `paragon`
--
ALTER TABLE `paragon`
  MODIFY `id_paragon` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT dla tabeli `paragon_pozycja`
--
ALTER TABLE `paragon_pozycja`
  MODIFY `id_pozycja` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT dla tabeli `produkt`
--
ALTER TABLE `produkt`
  MODIFY `id_produkt` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT dla tabeli `sklep`
--
ALTER TABLE `sklep`
  MODIFY `id_sklep` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT dla tabeli `stan`
--
ALTER TABLE `stan`
  MODIFY `id_stan` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- Ograniczenia dla zrzutów tabel
--

--
-- Ograniczenia dla tabeli `paragon`
--
ALTER TABLE `paragon`
  ADD CONSTRAINT `paragon_sklep_fk` FOREIGN KEY (`id_sklep`) REFERENCES `sklep` (`id_sklep`) ON DELETE NO ACTION;

--
-- Ograniczenia dla tabeli `paragon_pozycja`
--
ALTER TABLE `paragon_pozycja`
  ADD CONSTRAINT `paragon_pozycja_fk` FOREIGN KEY (`id_paragon`) REFERENCES `paragon` (`id_paragon`) ON DELETE CASCADE,
  ADD CONSTRAINT `paragon_pozycja_produkt_fk` FOREIGN KEY (`id_produkt`) REFERENCES `produkt` (`id_produkt`) ON DELETE NO ACTION;

--
-- Ograniczenia dla tabeli `stan`
--
ALTER TABLE `stan`
  ADD CONSTRAINT `stan_magazyn_fk` FOREIGN KEY (`id_magazyn`) REFERENCES `magazyn` (`id_magazyn`) ON DELETE CASCADE,
  ADD CONSTRAINT `stan_produkt_fk` FOREIGN KEY (`id_produkt`) REFERENCES `produkt` (`id_produkt`) ON DELETE CASCADE,
  ADD CONSTRAINT `stan_sklep_fk` FOREIGN KEY (`id_sklep`) REFERENCES `sklep` (`id_sklep`) ON DELETE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
