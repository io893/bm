//---------------------------------------------------------------------------

#ifndef TFmWriteCpuH
#define TFmWriteCpuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TFrWritePrgCpu0.h"
//---------------------------------------------------------------------------
class TFmWriteCpu : public TForm
{
__published:	// IDE-managed Components
    TFrWritePrgCpu0 *FrWritePrgCpu01;
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    int Nk;
    __fastcall TFmWriteCpu(TComponent* Owner);

    void __fastcall FastWrite(void)
    {
        FrWritePrgCpu01->Nk = Nk;
        FrWritePrgCpu01->BtnWriteClick(this);
    }

};
//---------------------------------------------------------------------------
extern PACKAGE TFmWriteCpu *FmWriteCpu;
//---------------------------------------------------------------------------
#endif
