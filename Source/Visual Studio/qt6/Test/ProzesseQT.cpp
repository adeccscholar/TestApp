#include "ProzesseQT.h"
#include "PersonDlgClass.h"
#include "PersonListClass.h"
#include "FileDlgClass.h"
#include "WorkingDlgClass.h"



TProcessQT::TProcessQT(void) : TProcess() {
}


TProcessQT::~TProcessQT(void) {
}

TMyForm TProcessQT::CreatePersonForm(void) {
   //TMyForm frm(new PersonDlgClass(/* *this */), true);
   //return frm;
   return { new PersonDlgClass(/* *this */), true };
}

TMyForm TProcessQT::CreateEmployeeForm(void) {
   TMyForm frm(new PersonDlgClass(/* *this */), true); 
   return frm;
}

TMyForm TProcessQT::CreatePersonListForm(void) {
   TMyForm frm(new PersonListClass(), true);
   return frm;
}

TMyForm TProcessQT::CreateDirectoryForm(void) {
   TMyForm frm(new WorkingDlgClass(*this, nullptr), true);
   return frm;
}

TMyForm TProcessQT::CreateFileDialog(void) {
   TMyForm frm(new FileDlgClass(FileDlgProcess(), nullptr), true);
   return frm;
}



