//---------------------------------------------------------------------------

#ifndef MainFormFMXH
#define MainFormFMXH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.Rtti.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
//---------------------------------------------------------------------------
#include "ProzesseFMX.h"

class TfrmMainFMX : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
    TPanel *Panel1;
    TPanel *Panel2;
    TStatusBar *StatusBar1;
    TMemo *memOutput;
    TMemo *memError;
    TSplitter *Splitter1;
    TButton *btnRollDice;
    TLabel *sbMain;
    TButton *btnPersonList;
    TButton *btnPersonNew;
    TButton *btnPersonEdit;
    TButton *btnEmployeeNew;
    TButton *btnEmployeeEdit;
    TEdit *edtValues;
    TButton *btnWork;
    TButton *btnClose;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnRollDiceClick(TObject *Sender);
    void __fastcall btnPersonListClick(TObject *Sender);
    void __fastcall btnPersonNewClick(TObject *Sender);
    void __fastcall btnPersonEditClick(TObject *Sender);
    void __fastcall btnEmployeeNewClick(TObject *Sender);
    void __fastcall btnEmployeeEditClick(TObject *Sender);
    void __fastcall btnWorkClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall btnCloseClick(TObject *Sender);
private:	// Benutzer-Deklarationen
    TProcessFMX process;
    TMyForm frm;
public:		// Benutzer-Deklarationen
    __fastcall TfrmMainFMX(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMainFMX *frmMainFMX;
//---------------------------------------------------------------------------
#endif
