//---------------------------------------------------------------------------
#include "PersonData.h"

#include <iomanip>
#include <typeinfo>
//---------------------------------------------------------------------------

TAddress::TAddress(void) {
   _Init();
   }

TAddress::TAddress(TAddress const& ref) {
   strZipCode      = ref.strZipCode;
   strCity         = ref.strCity;
   strStreet       = ref.strStreet;
   strStreetNumber = ref.strStreetNumber;
   }

void TAddress::Init(void) {
   _Init();
   }

void TAddress::Copy(TAddress const& address) {
   _Copy(address);
   }

void TAddress::_Init(void) {
   strZipCode      = "";
   strCity         = "";
   strStreet       = "";
   strStreetNumber = "";
   }

void TAddress::_Copy(TAddress const& address) {
   strZipCode      = address.strZipCode;
   strCity         = address.strCity;
   strStreet       = address.strStreet;
   strStreetNumber = address.strStreetNumber;
   }

int  TAddress::_Compare(TAddress const& address) const {
   if(strCity != address.strCity)
      return strCity < address.strCity ? -1 : 1;
   if(strZipCode != address.strZipCode)
      return strZipCode < address.strZipCode ? -1 : 1;
   if(strStreet != address.strStreet)
      return strStreet < address.strStreet ? -1 : 1;
   if(strStreetNumber != address.strStreetNumber)
      return strStreetNumber < address.strStreetNumber ? -1 : 1;
   return 0;
   }


std::ostream& operator << (std::ostream& out, TAddress const& address) {
   out << address.ZipCode() << " " << address.City() << std::endl
       << address.Street() << " " <<  address.StreetNumber();
   return out;
}

//-----------------------------------------------------------------------------

TBankingAccount::TBankingAccount(void) {
   _Init();
   }

TBankingAccount::TBankingAccount(TBankingAccount const& ref) {
   _Copy(ref);
   }

void TBankingAccount::Init(void) {
   _Init();
   }

void TBankingAccount::Copy(TBankingAccount const& banking) {
   _Copy(banking);
   }

void TBankingAccount::_Init(void) {
   strBankName      = "";
   strIBANNumber    = "";
   strBIC           = "";
   strAccountHolder = "";
   }

void TBankingAccount::_Copy(TBankingAccount const& banking) {
   strBankName      = banking.strBankName;
   strIBANNumber    = banking.strIBANNumber;
   strBIC           = banking.strBIC;
   strAccountHolder = banking.strAccountHolder;
   }

int  TBankingAccount::_Compare(TBankingAccount const& banking) const {
   if(strIBANNumber != banking.strIBANNumber)
      return strIBANNumber < banking.strIBANNumber ? -1 : 1;
   if(strBIC != banking.strBIC)
      return strBIC < banking.strBIC ? -1 : 1;
   if(strBankName != banking.strBankName)
      return strBankName < banking.strBankName ? -1 : 1;
   if(strAccountHolder != banking.strAccountHolder)
      return strAccountHolder < banking.strAccountHolder ? -1 : 1;
   return 0;
   }

std::ostream& operator << (std::ostream& out, TBankingAccount const& banking) {
   out << "IBAN:    " << banking.IBANNumber() << std::endl
       << "BIC:     " << banking.BIC() << std::endl
       << "Bank:    " << banking.BankName() << std::endl
       << "Inhaber: " << banking.AccountHolder();
   return out;
   }

//-----------------------------------------------------------------------------

TDepartment::TDepartment(void) {
   _Init();
   }

TDepartment::TDepartment(TDepartment const& ref) {
   _Copy(ref);
   }


void TDepartment::Init(void) {
   _Init();
   }

void TDepartment::Copy(TDepartment const& department) {
   _Copy(department);
   }

void TDepartment::_Init(void) {
   strDescription = "";
   }

void TDepartment::_Copy(TDepartment const& department) {
   strDescription = department.strDescription;
   }

int  TDepartment::_Compare(TDepartment const& department) const {
   if(strDescription != department.strDescription)
      return strDescription < department.strDescription ? -1 : 1;
   return 0;
   }

std::ostream& operator << (std::ostream& out, TDepartment const& department) {
   out << department.strDescription;
   return out;
   }

//-----------------------------------------------------------------------------

TPerson::TPerson(void) {
   _Init();
   }

TPerson::TPerson(TPerson const& ref) : theAddress(ref.theAddress) {
   _Copy(ref);
   }

void TPerson::Init(void) {
   _Init();
   }

void TPerson::Copy(TPerson const& person) {
   _Copy(person);
   }

void TPerson::_Init(void) {
   strSalutation   = "";
   strFirstName    = "";
   strName         = "";
   }

void TPerson::_Copy(TPerson const& person) {
   strSalutation   = person.strSalutation;
   strFirstName    = person.strFirstName;
   strName         = person.strName;
   }

int TPerson::_Compare(TPerson const& person) const {
   if(strSalutation != person.strSalutation)
      return strSalutation < person.strSalutation ? -1 : 1;
   if(strName != person.strName)
      return strName < person.strName ? -1 : 1;

   if(strFirstName != person.strFirstName)
      return strFirstName < person.strFirstName ? -1 : 1;
   return 0;
   }

std::ostream& operator << (std::ostream& out, TPerson const& person) {
   out << person.Salutation() << " " <<  person.FirstName()  << " " << person.Name() << std::endl
       << person.Address();
   return out;
}

//-----------------------------------------------------------------------------

TEmployee::TEmployee(void) : TPerson() {
   _Init();
   }

TEmployee::TEmployee(TEmployee const& ref) : TPerson(ref) {
   _Copy(ref);
   }

TEmployee::~TEmployee(void) {
   ptrDepartment           = nullptr;
   }

void TEmployee::Init(void) {
   TPerson::Init();
   _Init();
   }

void TEmployee::Copy(TPerson const& person) {
   TPerson::Copy(person);
   try {
      TEmployee employee = dynamic_cast<TEmployee const&>(person);
      _Copy(employee);
      }
   catch(std::bad_cast & exept) {
      _Init();
      }
   }

void TEmployee::_Init(void) {
   ptrDepartment           = nullptr;
   strJobDescription       = "";
   flSalary                = 0.0 ;
   strTaxNumber            = "";
   strSocialSecurityNumber = "";
   boActive                = false;
   }

void TEmployee::_Copy(TEmployee const& employee) {
   ptrDepartment           = employee.ptrDepartment;
   strJobDescription       = employee.strJobDescription;
   flSalary                = employee.flSalary;
   strTaxNumber            = employee.strTaxNumber;
   strSocialSecurityNumber = employee.strSocialSecurityNumber;
   boActive                = employee.boActive;
   }

std::ostream& operator << (std::ostream& out, TEmployee const& employee) {
    out << employee.Department()->Description() << std::endl
        << employee.JobDescription() << std::endl
        << static_cast<TPerson const&>(employee) << std::endl;
    if(employee.Salary())
        out << std::setprecision(2) << *employee.Salary();
    else
        out << "<empty>";
    return out;
   }

