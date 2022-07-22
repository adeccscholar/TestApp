//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DirectoryForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmWorker *frmWorker;
//---------------------------------------------------------------------------
__fastcall TfrmWorker::TfrmWorker(TProcess& proc, TComponent* Owner)
    : process(proc), TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmWorker::FormCreate(TObject *Sender) {
   frm.Set(this, false);
   }

//---------------------------------------------------------------------------
void __fastcall TfrmWorker::btnSelectClick(TObject *Sender) {
   process.SelectWithFileDlg(frm);
   }
//---------------------------------------------------------------------------
void __fastcall TfrmWorker::btnStartClick(TObject *Sender)
{
  // lvData->Items->BeginUpdate();
   process.WorkingWith(frm);
  // lvData->Items->EndUpdate();
}
//---------------------------------------------------------------------------
