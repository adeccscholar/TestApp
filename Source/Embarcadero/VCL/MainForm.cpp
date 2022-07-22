//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "PersonData.h"
#include "FileDlgFormVCL.h"

#include "Business.h"

#include "MyForm.h"
#include "MyTools.h"
#include "MyStream.h"
#include "MyDS_Iterator.h"

#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;

//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner) : TForm(Owner) {
   }

//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender) {
   frm.Set(this, false);
   std::ifstream ins("..\\..\\..\\..\\..\\Data\\LocalizeFirstApp.xml");
   if(ins) process.Read(ins);

   process.InitMainForm(frm);


   my_dslist lb (ListBox1->Items);
   vector<string> values;
   copy(lb.begin(), lb.end(), back_inserter(values));
   copy(values.begin(), values.end(), ostream_iterator<string>( cout, "\n"));

   }

//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormDestroy(TObject *Sender) {
   process.CloseMainForm(frm);
   }

//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnPersonNewClick(TObject *Sender) {
   process.PersonNew();
   }


//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnPersonEditClick(TObject *Sender) {
   TPerson person;
   process.CreatePerson(person);
   process.PersonEdit(person);
   }


//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnEmployeeNewClick(TObject *Sender) {
   process.EmployeeNew();
   }
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnEmployeeEditClick(TObject *Sender) {
   TDepartment department;
   TEmployee   employee;
   process.CreateEmployee(department, employee);
   process.EmployeeEdit(employee);
   }
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnPersonListClick(TObject *Sender) {
   try {
      process.ShowPersonList();
      }
   catch(std::exception& ex) {
       std::cerr << "Fehler:" << std::endl
                 << ex.what() << std::endl;
      }
   }

//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRollDiceClick(TObject *Sender) {
   try {
      process.Roll_Dices(frm);
      }
   catch(std::exception& ex) {
       std::cerr << "Fehler:" << std::endl
                 << ex.what() << std::endl;
      }
   }
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnWorkClick(TObject *Sender) {
   process.WorkingWithFileDlg();
   }
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnCloseClick(TObject *Sender) {
   Close();
   }
//---------------------------------------------------------------------------

