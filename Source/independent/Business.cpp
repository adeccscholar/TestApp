/** \file
\brief   Implementierung der Geschäftsregeln (Businessrules)
\details Umsetzung einer einfachen Geschäftsregeln in einer eigenen Klasse.
         Die Implementierung erfolgt dabei erst einmal in einer Tool- Class mit
         statischen Funktionen.
<hr>
$LastChangedDate: $
$Revision: $
$HeadURL: $
<hr>
\author Volker Hillmann
\date    19.03.2022
\version 1.0
\since   Version 1.0
\copyright Copyright ©2022 adecc Systemhaus GmbH, Alle Rechte vorbehalten.
*/

#pragma hdrstop

#include "Business.h"
#include "MyTools.h"
//---------------------------------------------------------------------------
#include <iomanip>
#include <string_view>
#include <sstream>
#include <stdexcept>
#include <regex>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <chrono>
#include <stdexcept>
#include <functional>


/*
Function IBANGermany(blz As String, Konto As String) As String
Dim Nummer As Variant, tmpKonto As String
Dim iKtoLength As Integer, iIBANLength As Long

Dim vTempIBAN As Variant, k As Integer, i As Integer, iRest As Integer
Dim iRestLength As Integer, iAllLength As Integer, vResult As Variant

iKtoLength = Len(Konto)
If (iKtoLength < 10) Then
   tmpKonto = Format(0, String$(10 - iKtoLength, "0")) & Konto
Else
   tmpKonto = Konto
End If

Nummer = blz & tmpKonto & "131400"

iIBANLength = Len(Nummer)
k = Int(iIBANLength / 9) + 2

'Durchlaufen der temp. IBAN in 9er Schritten und berechnen der jeweiligen Prüfziffer
For i = 1 To k
   If i = 1 Then
       '1. Durchlauf immer 9 Stellen
        iRest = Left(Nummer, 9) Mod 97
        iRestLength = Len(iRest)
        iAllLength = 9
    ElseIf i = 2 Then
       '2. Durchlauf Anzahl der Stellen der 1. Prüfziffer und weiteren Stellen der
       'temp IBAN auffüllen bis 9 Stellen
       iRest = (iRest & Mid(Nummer, 10, 9 - iRestLength)) Mod 97
       iRestLength = Len(iRest)
       iAllLength = iAllLength + (9 - iRestLength)
    Else
       iRest = (iRest & Mid(Nummer, iAllLength + 1, 9 - iRestLength)) Mod 97
       iRestLength = Len(iRest)
       iAllLength = iAllLength + (9 - iRestLength)
       'Ist die Länge der temp. IBAN ereicht dann raus hier
       If iAllLength >= iIBANLength Then
          vResult = iRest
          Exit For
       Else
          vResult = iRest
       End If
    End If
Next i

'Rerrechnen der Prüfziffer
vResult = 98 - vResult
Nummer = "DE" & Format(vResult, "00") & blz & tmpKonto
IBANGermany = Nummer
End Function
*/
std::string TBusinessRules::BuildIBAN(std::string const& strBLZ, std::string const& strKonto) {
   std::ostringstream ret;
   return ret.str();
   }

// ISO 13616-konformen nationalen IBAN-Formate   www.iban.com
std::string&& TBusinessRules::CheckIBANNumber(std::string && strNumber) {
   return std::move(strNumber);
   }

std::string&& TBusinessRules::CheckTaxNumber(std::string && strNumber) {
   return std::move(strNumber);
   }

/**
\brief Methode zum Überprüfen einer Sozialversicherungsnummer
\details Kontrolle und Formatierung einer Sozialversicherungsummer, Berechnung
         der Prüfziffer, Formatierung der eingegenen Nummer
\details Aufbau der Prüfummer
         - Stellen 1-2: Bereichsnummer der Vergabeanstalt
         - Stellen 3-8: Dein Geburtsdatum
         - Stelle 9: Anfangsbuchstabe deines Geburtsnamens
         - Stellen 10-11: Seriennummer
         - Stelle 12: Prüfziffer
\details Prüfzifferberechnung
         - numerische Folge bilden, Buchstabe als Zahl (A = 1, ...)
         - Werte mit Faktoren multiplizieren und Quersumme bilden
         - Faktoren für die Positionen 2, 1, 2, 5, 7, 1, 2, 1, 2, 1, 2, 1
         - Divisionsreset mit 10 ist die Prüfziffer
\param   strNumber RValue Referenz auf einen std::string mit der zu prüfenden Nummer
\returns RValue von einem std::string mit der geprüften und formatierten Nummer
\throws  std::runtime_error im Fehlerfall
\Test Beispielnummer: 04 130863 M 33 8
      - 2, 1, 2,  5, 7, 1,  2, 1, 2, 1, 2, 1 Faktoren
      - 0, 4, 1,  3, 0, 8,  6, 3, 1, 3, 3, 3 als Zahl (M = 13)
      - 0  4  2  15  0  8  12  3  2  3  6  3 = 58 % 10 =  8
\author Volker Hillmann
\date    01.12.2021
*/
std::string&& TBusinessRules::CheckSocialSecurityNumber(std::string && strNumber) {
   auto check = [](std::string const& number) {
      static const std::regex parser("([0-9]{2})([0-9]{2})([0-9]{2})([0-9]{2})([A-Z]{1})([0-9]{2})([0-9]{1})");
      return std::regex_match(number, parser);
      };
   auto calc = [](std::string const& number) {
      static std::vector<int> factors = { 2, 1, 2, 5, 7, 1, 2, 1, 2, 1, 2, 1 };
      std::vector<int> values         = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
      for(auto i : { 0, 1, 2, 3, 4, 5, 6, 7 } ) {
         values[i] = number[i] - '0';
         }
      for(auto i : { 9, 10 } ) {
         values[i + 1] = number[i] - '0';
         }
      auto x = number[8] - 'A' + 1;
      if(x < 10)      { values[8] = 0; values[9] = x;      }
      else if(x < 20) { values[8] = 1; values[9] = x - 10; }
      else            { values[8] = 2; values[9] = x - 20; }
      for(auto i = 0; i < 12; ++i) values[i] *= factors[i];
      return std::accumulate(values.begin(), values.end(), 0) % 10;
      };

   strNumber = TMyTools::clean(strNumber);
   if(strNumber.length() < 12) {
      std::ostringstream os;
      os << "Ungültige Sozialversicherungnummer [" << strNumber << "]." << std::endl
         << "Die Nummer ist zu kurz!" << std::endl
         << "Datei: " << __FILE__ << ", Zeile: " << __LINE__ << std::endl;
      throw std::runtime_error(os.str());
      }

   if(strNumber.length() > 12) {
      std::ostringstream os;
      os << "Ungültige Sozialversicherungnummer [" << strNumber << "]." << std::endl
         << "Die Nummer ist zu lang!" << std::endl
         << "Datei: " << __FILE__ << ", Zeile: " << __LINE__ << std::endl;
      throw std::runtime_error(os.str());
      }

   if(!check(strNumber)) {
      std::ostringstream os;
      os << "Ungültige Sozialversicherungnummer [" << strNumber << "]." << std::endl
         << "Datei: " << __FILE__ << ", Zeile: " << __LINE__ << std::endl;
      throw std::runtime_error(os.str());
      }
   if(auto p = calc(strNumber); p != strNumber[11] - '0') {
      std::ostringstream os;
      os << "Ungültige Sozialversicherungnummer [" << strNumber << "]." << std::endl
         << "Prüfziffer ist ungültig!" << std::endl
         << "Datei: " << __FILE__ << ", Zeile: " << __LINE__ << std::endl;
      throw std::runtime_error(os.str());
      }
   //std::cerr << "Check: " << strNumber << std::endl;
   std::string_view view(strNumber);
   std::ostringstream os;
   os << view.substr(0, 2) << " " << view.substr(2, 6) << " " << view.substr(8, 1)
      << " " << view.substr(9, 2) << " " << view.substr(11, 1);
   strNumber = os.str();
   return std::move(strNumber);
   }


/**
\brief Methode zum Würfeln mit Hilfe des Zufallszahlengenerators
\details Nutzung der C++11 random- Bibliothek zur Bestimmung von
         gleichverteilten Zufallszahlen um eine Serie von Würfeln zu bestimmen
         und die Häufigkeiten auszuwerten.
\param   out Referenz auf einen std::ostream für Ausgabe
\param   iCount Anzahl der Tests
\param   iValues Anzahl der möglichen Werte im Test
\returns kein Rückgabewert
\author Volker Hillmann
\date    01.12.2015
*/
void TBusinessRules::roll_the_dice(std::ostream& out, unsigned int iCount, int iValues) {
   std::mt19937                        rand_value;
   std::uniform_int_distribution<int>  distri_value;

   // Build a uniform distribution
   rand_value.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
   distri_value.param(std::uniform_int_distribution<int>( 0, iValues - 1).param());
   auto func_value = std::bind(distri_value, rand_value);

   out << "roll the dice ..." << std::endl
       << "Values: " << iValues << std::endl
       << "Count:  " << iCount  << std::endl << std::endl;

   try {
      std::vector<int>  vecDiced;
      vecDiced.assign(iValues, 0);
      unsigned int i;

      // roll the dice
      for(i = 0; i < iCount; ++i) vecDiced[func_value()]++;

      // print results
      for(i = 0; i < iValues; ++i) {
         out << std::setw( 3) << std::right << i + 1 << std::setw(10) << std::right << vecDiced[i]
             << std::setw(10) << std::setprecision(4) << std::right << (vecDiced[i] * 100.0) / iCount
             << "%" << std::endl;
         }

         // determine and print minimum und maximum
         std::vector<int>::iterator it;
         it = std::min_element(vecDiced.begin(), vecDiced.end());
         out << std::endl
              << "Minimum = " << std::setw(5) << std::right << it - vecDiced.begin() + 1 << std::endl;
         it = std::max_element(vecDiced.begin(), vecDiced.end());
         out << "Maximum = " << std::setw(5) << std::right << it - vecDiced.begin() + 1 << std::endl;
      }
   catch(std::exception &ex) {
      std::ostringstream os;
      os << "c++ error in the function roll_the dice" << std::endl << ex.what() << std::endl;
      throw std::runtime_error(os.str());
      }
   return;
   }


void TBusinessRules::random_test(std::ostream& out) {
    std::random_device rdevice;
    std::mt19937                        rand_value;
    rand_value.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::default_random_engine engine(rand_value);
    std::uniform_int_distribution<int> uniform_dist(1, 6);
    for(int i = 0; i < 20; ++i) out << uniform_dist(engine) << std::endl;

   }
