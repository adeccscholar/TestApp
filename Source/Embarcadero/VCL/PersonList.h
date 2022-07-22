//---------------------------------------------------------------------------

#ifndef PersonListH
#define PersonListH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmPersonList : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
    TPanel *Panel1;
    TButton *btnOk;
    TListView *lvPersons;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
    __fastcall TfrmPersonList(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPersonList *frmPersonList;
//---------------------------------------------------------------------------
#endif
