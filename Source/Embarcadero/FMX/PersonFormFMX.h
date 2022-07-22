//---------------------------------------------------------------------------

#ifndef PersonFormFMXH
#define PersonFormFMXH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
#include "Prozesse.h"
class TfrmPersonFMX : public TForm
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
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall edtSalaryEnter(TObject *Sender);
    void __fastcall edtSalaryExit(TObject *Sender);
private:	// Benutzer-Deklarationen
   TProcess& process;
   TMyForm   frm;
public:		// Benutzer-Deklarationen
    __fastcall TfrmPersonFMX(TComponent* Owner, TProcess& proc);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPersonFMX *frmPersonFMX;
//---------------------------------------------------------------------------
#endif
