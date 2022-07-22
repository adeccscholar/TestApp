//---------------------------------------------------------------------------

#ifndef PersonListFMXH
#define PersonListFMXH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Rtti.hpp>
//---------------------------------------------------------------------------
class TfrmPersonListFMX : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
    TStringGrid *lvPersons;
    TPanel *Panel1;
    TButton *btnOk;
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
    __fastcall TfrmPersonListFMX(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPersonListFMX *frmPersonListFMX;
//---------------------------------------------------------------------------
#endif
