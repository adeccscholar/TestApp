//---------------------------------------------------------------------------

#pragma hdrstop

#include "PersonForm.h"
#include "PersonList.h"
#include "DirectoryForm.h"
#include "FileDlgFormVCL.h"

#include "ProzesseVCL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TProcessVCL::TProcessVCL(void) : TProcess() {
   }


TProcessVCL::~TProcessVCL(void) {
   }

TMyForm TProcessVCL::CreatePersonForm(void) {
   TMyForm frm(new TfrmPerson (nullptr, *this), true);
   return frm;
   }

TMyForm TProcessVCL::CreateEmployeeForm(void) {
   TMyForm frm(new TfrmPerson (nullptr, *this), true);
   return frm;
   }

TMyForm TProcessVCL::CreatePersonListForm(void) {
   TMyForm frm(new TfrmPersonList (nullptr), true);
   return frm;
   }

TMyForm TProcessVCL::CreateDirectoryForm(void) {
   TMyForm frm(new TfrmWorker (*this, nullptr), true);
   return frm;
   }

TMyForm TProcessVCL::CreateFileDialog(void) {
   TMyForm frm(new TfrmFileDlg(FileDlgProcess(), nullptr), true);
   return frm;
   }
