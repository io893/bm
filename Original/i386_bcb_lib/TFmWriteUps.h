//---------------------------------------------------------------------------

#ifndef TFmWriteUpsH
#define TFmWriteUpsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TFrWriteCfgUps.h"
//---------------------------------------------------------------------------
class TFmWriteUps : public TForm
{
__published:	// IDE-managed Components
    TFrWriteCfgUps *FrWriteCfgUps1;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FrWriteCfgUps1BtnWriteClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFmWriteUps(TComponent* Owner);

    void __fastcall FastWrite(void)
    {
        FrWriteCfgUps1->BtnWriteClick(this);
    }

};
//---------------------------------------------------------------------------
extern PACKAGE TFmWriteUps *FmWriteUps;
//---------------------------------------------------------------------------
#endif
