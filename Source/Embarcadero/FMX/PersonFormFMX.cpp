//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "PersonFormFMX.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmPersonFMX *frmPersonFMX;
//---------------------------------------------------------------------------
__fastcall TfrmPersonFMX::TfrmPersonFMX(TComponent* Owner,  TProcess& proc)
    : TForm(Owner), process(proc) {
}
//---------------------------------------------------------------------------
void __fastcall TfrmPersonFMX::FormCreate(TObject *Sender) {
   frm.Set(this, false);
   }
//---------------------------------------------------------------------------

void __fastcall TfrmPersonFMX::edtSalaryEnter(TObject *Sender)
{
    process.EmployeeForm().EnterSalary(frm);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPersonFMX::edtSalaryExit(TObject *Sender)
{
   process.EmployeeForm().ExitSalary(frm);
}
//---------------------------------------------------------------------------

