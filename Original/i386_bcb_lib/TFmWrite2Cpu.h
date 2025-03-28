//---------------------------------------------------------------------------

#ifndef TFmWrite2CpuH
#define TFmWrite2CpuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TFrWritePrgCpu0.h"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFmWrite2Cpu : public TForm
{
__published:	// IDE-managed Components
    TRzGroupBox *RzGroupBox1;
    TFrWritePrgCpu0 *FrWritePrgCpu01;
    TFrWritePrgCpu0 *FrWritePrgCpu02;
    TRzCheckBox *Cpu0CheckBox;
    TRzCheckBox *Cpu1CheckBox;
    TRzBitBtn *BtnWrite;
    TRzBitBtn *BtnVerify;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall BtnWriteClick(TObject *Sender);
    void __fastcall BtnVerifyClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFmWrite2Cpu(TComponent* Owner);
    int Nk;

    void __fastcall FastWrite(void)
    {
        BtnWriteClick(this);
    }
};
//---------------------------------------------------------------------------
extern PACKAGE TFmWrite2Cpu *FmWrite2Cpu;
//---------------------------------------------------------------------------
#endif
