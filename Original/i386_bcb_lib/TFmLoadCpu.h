//---------------------------------------------------------------------------

#ifndef TFmLoadCpuH
#define TFmLoadCpuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TFrHpiLoadPrgCpu0.h"
//---------------------------------------------------------------------------
class TFmLoadCpu : public TForm
{
__published:	// IDE-managed Components
    TFrHpiLoadPrgCpu0 *FrHpiLoadPrgCpu01;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FrHpiLoadPrgCpu01BtnLoadClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    int Nk;
    __fastcall TFmLoadCpu(TComponent* Owner);

    void __fastcall FastLoad(void)
    {
        FrHpiLoadPrgCpu01->Nk = Nk;
        FrHpiLoadPrgCpu01->BtnLoadClick(this);
    }

};
//---------------------------------------------------------------------------
extern PACKAGE TFmLoadCpu *FmLoadCpu;
//---------------------------------------------------------------------------
#endif
