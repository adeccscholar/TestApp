//---------------------------------------------------------------------------

#pragma hdrstop

#include "MyStream.h"
#include "MyForm.h"

#include <fmx.h>
#include "MainFormFMX.h"
#include "PersonListFMX.h"

#include <locale>
#include <memory>
#include <fstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmMainFMX *frmMainFMX;
//---------------------------------------------------------------------------
__fastcall TfrmMainFMX::TfrmMainFMX(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMainFMX::FormCreate(TObject *Sender) {
   frm.Set(this, false);
   try {
      std::ifstream ins("..\\..\\..\\..\\..\\Data\\LocalizeFirstApp.xml");
      if(ins) process.Read(ins);
      process.InitMainForm(frm);
      }
   catch(std::exception& ex) {
      ShowMessage(ex.what());
      }
   }
//---------------------------------------------------------------------------

void __fastcall TfrmMainFMX::FormDestroy(TObject *Sender) {
   process.CloseMainForm(frm);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainFMX::btnPersonNewClick(TObject *Sender) {
   process.PersonNew();
   }
//---------------------------------------------------------------------------

void __fastcall TfrmMainFMX::btnPersonEditClick(TObject *Sender) {
   TPerson person;
   process.CreatePerson(person);
   process.PersonEdit(person);
   }
//---------------------------------------------------------------------------

void __fastcall TfrmMainFMX::btnEmployeeNewClick(TObject *Sender) {
   process.EmployeeNew();
   }
//---------------------------------------------------------------------------

void __fastcall TfrmMainFMX::btnEmployeeEditClick(TObject *Sender) {
   TDepartment department;
   TEmployee   employee;
   process.CreateEmployee(department, employee);
   process.EmployeeEdit(employee);
   }

//---------------------------------------------------------------------------

void __fastcall TfrmMainFMX::btnRollDiceClick(TObject *Sender) {
   process.Roll_Dices(frm);
   }

//---------------------------------------------------------------------------
void __fastcall TfrmMainFMX::btnPersonListClick(TObject *Sender) {
   process.ShowPersonList();
   }
//---------------------------------------------------------------------------

void __fastcall TfrmMainFMX::btnWorkClick(TObject *Sender) {
   process.WorkingWithFileDlg();
   }
//---------------------------------------------------------------------------

void __fastcall TfrmMainFMX::btnCloseClick(TObject *Sender) {
   Close();
   }
//---------------------------------------------------------------------------

