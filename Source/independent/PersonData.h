/** \file
\brief   Schnittstellen der Systemschicht für die  Anwendung
\details In dieser Datei sind die Klassen der Systemschicht for das Semester-
         Pausen- Projekt definiert. Nach einer anfänglichen VCL- Implementierung
         wurden alle Nicht- C++ Typen und Sprachkonstruktionen entfernt und eine
         C++- Standardschnittstelle und Implementierung umgesetzt.
<hr>
$LastChangedDate: $
$Revision: $
$HeadURL: $
<hr>
\author Volker Hillmann
\date    15.02.2022
\version 1.0
\since   Version 1.0
\copyright Copyright ©2022 adecc Systemhaus GmbH, Alle Rechte vorbehalten.
*/

#ifndef PersonDataH
#define PersonDataH
//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <optional>
#include <stdexcept>

/** \class
\brief   Klasse zur Verwaltung von Adressdaten innerhalb der Anwendung
\note    Die Adress- Informationen beziehen sich auf Adressen innerhalb von
         Deutschland und können international abweichen.
\author  Volker Hillmann
\date    19.03.2022
\version 1.0
\since   Version 1.0
*/
class TAddress {
   friend std::ostream& operator << (std::ostream& out, TAddress const& address);
   private:
	  std::string strZipCode;        ///< Postleitzahl zur Adresse
	  std::string strCity;           ///< Name der Stadt zur Adresse
	  std::string strStreet;         ///< Straßenname zur Adresse
	  std::string strStreetNumber;   ///< Hausnummer mit Ergänzung zur Adresse
   public:
	  TAddress(void);
	  TAddress(TAddress const&);
	  virtual ~TAddress(void) { };

      bool operator == (TAddress const& ref) const { return _Compare(ref) == 0; }
      bool operator != (TAddress const& ref) const { return _Compare(ref) == 0; }
      bool operator <  (TAddress const& ref) const { return _Compare(ref) == 0; }
      bool operator <= (TAddress const& ref) const { return _Compare(ref) == 0; }
      bool operator >  (TAddress const& ref) const { return _Compare(ref) == 0; }
      bool operator >= (TAddress const& ref) const { return _Compare(ref) == 0; }

      virtual void Init(void);
      virtual void Copy(TAddress const&);

      /** \name Selektoren der Klasse TAddress
         \{  */
	  std::string const& ZipCode(void) const { return strZipCode; }
	  std::string const& City(void) const { return strCity; }
	  std::string const& Street(void) const { return strStreet; }
	  std::string const& StreetNumber(void) const { return strStreetNumber; }
      /// \}
      /** \name Manipulatoren der Klasse TAddress
         \{  */
	  std::string const& ZipCode(std::string const& newVal) { return strZipCode = newVal; }
	  std::string const& City(std::string const& newVal) { return strCity = newVal; }
	  std::string const& Street(std::string const& newVal) { return strStreet = newVal; }
	  std::string const& StreetNumber(std::string const& newVal) { return strStreetNumber = newVal; }
      /// \}
   private:
       void _Init(void);
       void _Copy(TAddress const&);
       int  _Compare(TAddress const&) const;
 	  };




class TBankingAccount {
   friend std::ostream& operator << (std::ostream&, TBankingAccount const&);
   private:
	  std::string strBankName;
	  std::string strIBANNumber;
	  std::string strBIC;
	  std::string strAccountHolder;
   public:
	  TBankingAccount(void);
	  TBankingAccount(TBankingAccount const&);
	  ~TBankingAccount(void) { }

      bool operator == (TBankingAccount const& ref) const { return _Compare(ref) == 0; }
      bool operator != (TBankingAccount const& ref) const { return _Compare(ref) == 0; }
      bool operator <  (TBankingAccount const& ref) const { return _Compare(ref) == 0; }
      bool operator <= (TBankingAccount const& ref) const { return _Compare(ref) == 0; }
      bool operator >  (TBankingAccount const& ref) const { return _Compare(ref) == 0; }
      bool operator >= (TBankingAccount const& ref) const { return _Compare(ref) == 0; }

      virtual void Init(void);
      virtual void Copy(TBankingAccount const&);

	  std::string const& BankName(void) const { return strBankName; }
	  std::string const& IBANNumber(void) const { return strIBANNumber; }
	  std::string const& BIC(void) const { return strBIC; }
	  std::string const& AccountHolder(void) const { return strAccountHolder; }

	  std::string const& BankName(std::string const& newVal) { return strBankName = newVal; }
	  std::string const& IBANNumber(std::string const& newVal) { return strIBANNumber = newVal; }
	  std::string const& BIC(std::string const& newVal) { return strBIC = newVal; }
	  std::string const& AccountHolder(std::string const& newVal) { return strAccountHolder = newVal; }

   private:
       void _Init(void);
       void _Copy(TBankingAccount const&);
       int  _Compare(TBankingAccount const&) const;

   };




class TDepartment {
   friend std::ostream& operator << (std::ostream&, TDepartment const&);
   private:
	  std::string strDescription;
   public:
	  TDepartment(void);
	  TDepartment(TDepartment const&);
	  ~TDepartment(void) { }

      bool operator == (TDepartment const& ref) const { return _Compare(ref) == 0; }
      bool operator != (TDepartment const& ref) const { return _Compare(ref) == 0; }
      bool operator <  (TDepartment const& ref) const { return _Compare(ref) == 0; }
      bool operator <= (TDepartment const& ref) const { return _Compare(ref) == 0; }
      bool operator >  (TDepartment const& ref) const { return _Compare(ref) == 0; }
      bool operator >= (TDepartment const& ref) const { return _Compare(ref) == 0; }

      virtual void Init(void);
      virtual void Copy(TDepartment const&);

	  // Selektoren
	  std::string const& Description(void) const { return strDescription; }

	  // Manipulatoren
	  std::string const& Description(std::string const& newVal) { return strDescription = newVal; }

   private:
       void _Init(void);
       void _Copy(TDepartment const&);
       int  _Compare(TDepartment const&) const;

   };




class TPerson {
   friend std::ostream& operator << (std::ostream& out, TPerson const&);
   private:
	  std::string strSalutation;
	  std::string strFirstName;
	  std::string strName;

	  TAddress theAddress;
   public:
	  TPerson(void);
	  TPerson(TPerson const&);
	  virtual ~TPerson(void) { }

      virtual void Init(void);
      virtual void Copy(TPerson const&);

      bool operator == (TPerson const& ref) const { return _Compare(ref) == 0; }
      bool operator != (TPerson const& ref) const { return _Compare(ref) == 0; }
      bool operator <  (TPerson const& ref) const { return _Compare(ref) == 0; }
      bool operator <= (TPerson const& ref) const { return _Compare(ref) == 0; }
      bool operator >  (TPerson const& ref) const { return _Compare(ref) == 0; }
      bool operator >= (TPerson const& ref) const { return _Compare(ref) == 0; }


	  // Selektoren
	  std::string const& Salutation(void) const { return strSalutation; }
	  std::string const& FirstName(void) const { return strFirstName; }
	  std::string const& Name(void) const { return strName; }
	  TAddress const& Address(void) const { return theAddress; }

	  // Manipulatoren
	  std::string Salutation(std::string const& newVal) { return strSalutation = newVal; }
	  std::string FirstName(std::string const& newVal) { return strFirstName = newVal; }
	  std::string Name(std::string const& newVal) { return strName = newVal; }

	  TAddress& Address(void) { return theAddress; }

   private:
       void _Init(void);
       void _Copy(TPerson const&);
       int  _Compare(TPerson const&) const;
   };




class TEmployee : public TPerson {
    friend std::ostream& operator << (std::ostream&, TEmployee const&);
	private:
	   std::string        strJobDescription;
	   std::optional<double>             flSalary;
	   std::string        strTaxNumber;
	   std::string        strSocialSecurityNumber;
	   bool               boActive;
	   TDepartment const* ptrDepartment;
	   TBankingAccount    theBankingAccount;
	public:
	   TEmployee(void);
	   TEmployee(TEmployee const&);
	   ~TEmployee(void);

       virtual void Init(void);
       virtual void Copy(TPerson const&);

      bool operator == (TEmployee const& ref) const { return _Compare(ref) == 0; }
      bool operator != (TEmployee const& ref) const { return _Compare(ref) == 0; }
      bool operator <  (TEmployee const& ref) const { return _Compare(ref) == 0; }
      bool operator <= (TEmployee const& ref) const { return _Compare(ref) == 0; }
      bool operator >  (TEmployee const& ref) const { return _Compare(ref) == 0; }
      bool operator >= (TEmployee const& ref) const { return _Compare(ref) == 0; }


	   // Selektoren
	   std::string const&     JobDescription(void) const { return strJobDescription; }
	   std::optional<double> const&               Salary(void) const { return flSalary; }
	   std::string const&     TaxNumber(void) const { return strTaxNumber; }
	   std::string const&     SocialSecurityNumber(void) const { return strSocialSecurityNumber; }
	   bool                        Active(void) const { return boActive; }
	   TDepartment const*          Department(void) const {
          if(!ptrDepartment) throw std::runtime_error("department pointer is null");
          return ptrDepartment;
          }

	   TBankingAccount const&      BankingAccount(void) const { return theBankingAccount; }

	   // Manipuatoren
	   std::string const&     JobDescription(std::string const& newVal) { return strJobDescription = newVal; }
	   std::optional<double> const&               Salary(std::optional<double> const& newVal) { return flSalary = newVal; }
	   std::string const&     TaxNumber(std::string const& newVal) { return strTaxNumber = newVal; }
	   std::string const&     SocialSecurityNumber(std::string const& newVal) { return strSocialSecurityNumber = newVal; }
	   bool                   Active(bool newVal) { return boActive = newVal; }
	   TDepartment const*     Department(TDepartment const* newVal) { return ptrDepartment = newVal; }
	   TBankingAccount&       BankingAccount(void) { return theBankingAccount; }

   private:
       void _Init(void);
       void _Copy(TEmployee const&);
       int  _Compare(TEmployee const&) const;

};


#endif

