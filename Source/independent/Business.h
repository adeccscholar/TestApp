/** \file
\brief   Schnittstelle der Geschäftsregeln (Businessrules)
\details Umsetzung einer einfachen Geschäftsregeln in einer eigenen Klasse.
         Die Implementierung der Klasse TBusinessRules erfolgt dabei erst
         einmal in einer Tool- Class mit statischen Funktionen.
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

#ifndef BusinessH
#define BusinessH
//---------------------------------------------------------------------------

#include <string>

/** \class
\brief Klasse mit Geschäftsregeln für die Anwendung
\author Volker Hillmann
\date    19.03.2022
\version 1.0
\since   Version 1.0
*/
class TBusinessRules {
   public:
      static std::string   BuildIBAN(std::string const& strBLZ, std::string const& strKonto);
      static std::string&& CheckIBANNumber(std::string && strNumber);
      static std::string&& CheckTaxNumber(std::string && strNumber);
      static std::string&& CheckSocialSecurityNumber(std::string && strNumber);

      static void roll_the_dice(std::ostream& out, unsigned int iCount, int iValues);

      static void random_test(std::ostream& out);
   };
#endif
