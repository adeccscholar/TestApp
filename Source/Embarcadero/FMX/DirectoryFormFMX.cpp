//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "DirectoryFormFMX.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmWorkerFMX *frmWorkerFMX;
//---------------------------------------------------------------------------
__fastcall TfrmWorkerFMX::TfrmWorkerFMX(TProcess& proc, TComponent* Owner)
    : process(proc), TForm(Owner) {
   }

//---------------------------------------------------------------------------
void __fastcall TfrmWorkerFMX::FormCreate(TObject *Sender) {
   frm.Set(this, false);
   }

//---------------------------------------------------------------------------
void __fastcall TfrmWorkerFMX::btnSelectClick(TObject *Sender) {
   process.SelectWithFileDlg(frm);
   }
//---------------------------------------------------------------------------
void __fastcall TfrmWorkerFMX::btnStartClick(TObject *Sender) {
  // lvData->BeginUpdate();
   process.WorkingWith(frm);
  // lvData->EndUpdate();
   }

//---------------------------------------------------------------------------

