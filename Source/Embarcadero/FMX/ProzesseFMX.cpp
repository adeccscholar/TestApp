//---------------------------------------------------------------------------

#pragma hdrstop

#include "PersonFormFMX.h"
#include "FileDlgFormFMX.h"
#include "DirectoryFormFMX.h"

#include "ProzesseFMX.h"
#include "PersonListFMX.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TProcessFMX::TProcessFMX(void) : TProcess() {
   }


TProcessFMX::~TProcessFMX(void) {
   }

TMyForm TProcessFMX::CreatePersonForm(void) {
   TMyForm frm(new TfrmPersonFMX (nullptr, *this), true);
   return frm;
   }

TMyForm TProcessFMX::CreateEmployeeForm(void) {
   TMyForm frm(new TfrmPersonFMX (nullptr, *this), true);
   return frm;
   }

TMyForm TProcessFMX::CreatePersonListForm(void) {
   TMyForm frm(new TfrmPersonListFMX (nullptr), true);
   return frm;
   }

TMyForm TProcessFMX::CreateDirectoryForm(void) {
   //TMyForm frm(new TfrmWorkerFMX (*this, nullptr), true);
   return { new TfrmWorkerFMX (*this, nullptr), true };
   }

TMyForm TProcessFMX::CreateFileDialog(void) {
   //TMyForm frm(new TfrmFileDlgFMX(FileDlgProcess(), nullptr), true);
   return { new TfrmFileDlgFMX(FileDlgProcess(), nullptr), true };
   }

