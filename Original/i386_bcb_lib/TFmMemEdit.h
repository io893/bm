//---------------------------------------------------------------------------

#ifndef TFmMemEditH
#define TFmMemEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TFrMemEdit.h"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
class TFmMemEdit : public TForm
{
__published:	// IDE-managed Components
    TFrMemEdit *FrMemEdit1;
    TRzPanel *RzPanel1;
    TRzCheckBox *RzCheckBox1;
    TApplicationEvents *ApplicationEvents1;
    void __fastcall RzCheckBox1Click(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ApplicationEvents1Message(tagMSG &Msg, bool &Handled);
private:	// User declarations
    void __fastcall OnAutoUpdate(TObject *Sender);
public:		// User declarations
    __fastcall TFmMemEdit(TComponent* Owner);
    __fastcall ~TFmMemEdit();
};
//---------------------------------------------------------------------------
extern PACKAGE TFmMemEdit *FmMemEdit;
//---------------------------------------------------------------------------
#endif
