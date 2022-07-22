//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <iostream>
//---------------------------------------------------------------------------
#include "PersonData.h"
#include "ProzesseVCL.h"

class TfrmMain : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TPanel *pnlControl;
	TButton *btnPersonNew;
	TMemo *memOutput;
	TStatusBar *sbMain;
	TButton *btnPersonEdit;
	TButton *btnEmployeeNew;
	TButton *btnEmployeeEdit;
	TPanel *pnlMain;
	TMemo *memError;
	TSplitter *Splitter1;
    TListBox *ListBox1;
    TButton *btnPersonList;
    TButton *btnRollDice;
    TEdit *edtValues;
    TButton *btnWork;
    TButton *btnClose;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnPersonNewClick(TObject *Sender);
	void __fastcall btnPersonEditClick(TObject *Sender);
	void __fastcall btnEmployeeNewClick(TObject *Sender);
	void __fastcall btnEmployeeEditClick(TObject *Sender);
    void __fastcall btnPersonListClick(TObject *Sender);
    void __fastcall btnRollDiceClick(TObject *Sender);
    void __fastcall btnWorkClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall btnCloseClick(TObject *Sender);
private:	// Benutzer-Deklarationen
    TProcessVCL process;
    TMyForm  frm;
public:		// Benutzer-Deklarationen
	__fastcall TfrmMain(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
