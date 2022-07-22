//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PersonData.h"

#include "PersonForm.h"
#include "MyForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPerson *frmPerson;
//---------------------------------------------------------------------------
__fastcall TfrmPerson::TfrmPerson(TComponent* Owner,  TProcess& proc) : TForm(Owner), process(proc) {
	}

//---------------------------------------------------------------------------
void __fastcall TfrmPerson::FormCreate(TObject *Sender) {
   frm.Set(this, false);
   }

//---------------------------------------------------------------------------
void __fastcall TfrmPerson::edtSocialSecurityNumberExit(TObject *Sender) {
   auto [ret, msg] = process.EmployeeForm().CheckSocialSecurityNumber(frm);
   if(!ret) ShowMessage(msg.c_str());
   }

//---------------------------------------------------------------------------
void __fastcall TfrmPerson::edtSalaryEnter(TObject *Sender) {
   auto [ret, msg] = process.EmployeeForm().EnterSalary(frm);
   if(!ret) ShowMessage(msg.c_str());
   //edtSalary->Alignment = taLeftJustify;
   }

//---------------------------------------------------------------------------
void __fastcall TfrmPerson::edtSalaryExit(TObject *Sender) {
   auto [ret, msg] = process.EmployeeForm().ExitSalary(frm);
   if(!ret) ShowMessage(msg.c_str());
   //edtSalary->Alignment = taRightJustify;
   }

//---------------------------------------------------------------------------

