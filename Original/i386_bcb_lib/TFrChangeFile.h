//---------------------------------------------------------------------------


#ifndef TFrChangeFileH
#define TFrChangeFileH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include "RzCommon.hpp"
#include "RzShellDialogs.hpp"
#include "RzLabel.hpp"
#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include "RzRadChk.hpp"

//---------------------------------------------------------------------------
class TFrChangeFile : public TFrame
{
__published:	// IDE-managed Components
    TRzOpenDialog *OpenDialog;
    TRzComboBox *ComboBox;
    TRzBitBtn *RzBitBtn1;
    void __fastcall ButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFrChangeFile(TComponent* Owner);

    void __fastcall SaveStateToIni  (TRzRegIniFile *Ini, AnsiString Section);
    void __fastcall LoadStateFromIni(TRzRegIniFile *Ini, AnsiString Section);

};
//---------------------------------------------------------------------------
extern PACKAGE TFrChangeFile *FrChangeFile;
//---------------------------------------------------------------------------
#endif
