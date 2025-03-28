//---------------------------------------------------------------------------

#ifndef TFmLoadUpsH
#define TFmLoadUpsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TFrLoadCfgUps.h"
//---------------------------------------------------------------------------
class TFmLoadUps : public TForm
{
__published:	// IDE-managed Components
    TFrLoadCfgUps *FrLoadCfgUps1;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FrLoadCfgUps1BtnLoadClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFmLoadUps(TComponent* Owner);

    void __fastcall FastLoad(void)
    {
        FrLoadCfgUps1->BtnLoadClick(this);
    }

};
//---------------------------------------------------------------------------
extern PACKAGE TFmLoadUps *FmLoadUps;
//---------------------------------------------------------------------------
#endif
