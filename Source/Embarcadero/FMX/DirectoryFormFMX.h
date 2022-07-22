//---------------------------------------------------------------------------

#ifndef DirectoryFormFMXH
#define DirectoryFormFMXH

#include "Prozesse.h"
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Rtti.hpp>
//---------------------------------------------------------------------------
class TfrmWorkerFMX : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
    TPanel *Panel1;
    TPanel *Panel2;
    TPanel *Panel3;
    TPanel *Panel4;
    TLabel *lblFile;
    TEdit *edtFile;
    TButton *btnSelect;
    TMemo *memError;
    TSplitter *Splitter1;
    TStringGrid *lvData;
    TButton *btnClose;
    TButton *btnStart;
    void __fastcall btnStartClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnSelectClick(TObject *Sender);
private:	// Benutzer-Deklarationen
    TProcess& process;
    TMyForm   frm;
public:		// Benutzer-Deklarationen
    __fastcall TfrmWorkerFMX(TProcess& proc, TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmWorkerFMX *frmWorkerFMX;
//---------------------------------------------------------------------------
#endif
