//---------------------------------------------------------------------------

#ifndef TFmBurnAtH
#define TFmBurnAtH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TFrBurnAt.h"
//---------------------------------------------------------------------------
class TFmBurnAt : public TForm
{
__published:	// IDE-managed Components
    TFrBurnAt *FrBurnAt1;
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFmBurnAt(TComponent* Owner);

    void __fastcall FastBurn(void)
    {
        FrBurnAt1->BtnWriteClick(this);
    }

};
//---------------------------------------------------------------------------
extern PACKAGE TFmBurnAt *FmBurnAt;
//---------------------------------------------------------------------------
#endif
