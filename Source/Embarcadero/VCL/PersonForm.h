//---------------------------------------------------------------------------

#ifndef PersonFormH
#define PersonFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------
#include "Prozesse.h"


class TfrmPerson : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TGroupBox *grpPerson;
	TLabel *lblSalutation;
	TLabel *lblFirstName;
	TLabel *lblName;
	TComboBox *cbxSalutation;
	TEdit *edtFirstName;
	TEdit *edtName;
	TPanel *pnlBottom;
	TButton *btnCancel;
	TButton *btnOk;
	TGroupBox *grpAddress;
	TLabel *lblZipCodeCity;
	TEdit *edtZipCode;
	TEdit *edtCity;
	TLabel *lblStreetExtension;
	TEdit *edtStreet;
	TEdit *edtStreetNumber;
	TGroupBox *grpBankingAccount;
	TLabel *lblBankName;
	TEdit *edtBankName;
	TLabel *lblIBANNumber;
	TEdit *edtIBANNumber;
	TLabel *lblBIC;
	TEdit *edtBIC;
	TLabel *lblAccountHolder;
	TEdit *edtAccountHolder;
	TGroupBox *grpEmployee;
	TLabel *lblDepartment;
	TLabel *lblJobDescription;
	TLabel *lblSalary;
	TLabel *lblTaxNumber;
	TLabel *lblSocialSecurityNumber;
	TComboBox *cbxDepartment;
	TEdit *edtJobDescription;
	TEdit *edtSalary;
	TEdit *edtTaxNumber;
	TEdit *edtSocialSecurityNumber;
	TCheckBox *chkActive;
    void __fastcall edtSocialSecurityNumberExit(TObject *Sender);
    void __fastcall edtSalaryEnter(TObject *Sender);
    void __fastcall edtSalaryExit(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
private:	// Benutzer-Deklarationen
   TProcess& process;
   TMyForm   frm;
public:		// Benutzer-Deklarationen
	__fastcall TfrmPerson(TComponent* Owner, TProcess& proc);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPerson *frmPerson;
//---------------------------------------------------------------------------
#endif
