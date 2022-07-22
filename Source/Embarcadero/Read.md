Projects in folder Embarcadero are created with the C++Builder 10.4 and following.
Current state is C++Builder 11.1.5

We originally started with a dependent implementation, which is unfortunately what many C++Builder users use, and which is ultimately conveyed at least subliminally.

The source code looked like this

```cpp
class TBankingAccount{
    private:
    String strBankName;
    String strIBANNumber;
    String strBIC;
    String strAccountHolder;
    public:
    TBankingAccount(void);
    TBankingAccount(TBankingAccount const&);
    ~TBankingAccount(void);

    String const& BankName(void) const{return strBankName;}
    String const& IBANNumber(void) const{return strIBANNumber;}
    String const& BIC(void) const{return strBIC;}
    String const& AccountHolder(void) const{return strAccountHolder;}

    String const& BankName(String const& newVal){ return strBankName = newVal; }
    String const& IBANNumber(String const& newVal){ return  strIBANNumber = newVal; }
    String const& BIC(String const& newVal){ return strBIC = newVal; }
    String const& AccountHolder(String const& newVal){ return strAccountHolder = newVal; }

    __property String _BankName      = {read = BankName, write = BankName};
    __property String _IBANNumber    = {read = IBANNumber, write = IBANNumber};
    __property String _BIC           = {read = BIC, write = BIC};
    __property String _AccountHolder = {read = AccountHolder, write = AccountHolder};
};

class TEmployee : public TPerson {
    private:
       String             strJobDesciption;
       double             flSalary;
       String             strTaxNumber;
       String             strSocialSecurityNumber;
       bool               boActive;
       TDepartment const* ptrDepartment;
       TBankingAccount    theBankingAccount;
    public:
       TEmployee(void);
       TEmployee(TEmployee const&);
       ~TEmployee(void);

       // Selektoren
       String const&          JobDesciption(void) const { return strJobDesciption; }
       double const&          Salary(void) const { return flSalary; }
       String const&          TaxNumber(void) const { return strTaxNumber; }
       String const&          SocialSecurityNumber(void) const { return strSocialSecurityNumber; }
       bool                   Active(void) const { return boActive; }
       TDepartment const*     Department(void) const { return ptrDepartment; } 
       TBankingAccount const& BankingAccount(void) const { return theBankingAccount; }
```

