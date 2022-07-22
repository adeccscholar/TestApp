//---------------------------------------------------------------------------

#ifndef DirectoryFormH
#define DirectoryFormH
//---------------------------------------------------------------------------
#include "Prozesse.h"

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmWorker : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
    TPanel *Panel1;
    TPanel *Panel2;
    TPanel *Panel3;
    TLabel *lblFile;
    TEdit *edtFile;
    TPanel *Panel4;
    TButton *btnSelect;
    TButton *btnClose;
    TButton *btnStart;
    TListView *lvData;
    TMemo *memError;
    void __fastcall btnSelectClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnStartClick(TObject *Sender);
private:	// Benutzer-Deklarationen
    TProcess& process;
    TMyForm   frm;
public:		// Benutzer-Deklarationen
    __fastcall TfrmWorker(TProcess& proc, TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWorker *frmWorker;
//---------------------------------------------------------------------------
#endif
