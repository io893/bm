//---------------------------------------------------------------------------


#ifndef TFrIsoipH
#define TFrIsoipH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <TFmLib.h>
#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include <ExtCtrls.hpp>
#include "RzLabel.hpp"
#include "extdefs.h"
#include "RzRadGrp.hpp"
//---------------------------------------------------------------------------
class TFrIisoip : public TFrame
{
__published:	// IDE-managed Components
    TRzGroupBox *RzGroupBox1;
    TRzComboBox *BPeriod;
    TRzBitBtn *BMinus;
    TRzBitBtn *BPlus;
    TRzCheckBox *BEnable;
    TRzLabel *RzLabel3;
    TRzLabel *RzLabel1;
    TRzComboBox *BDiskret;
    TRzRadioGroup *BPeriodMul;
    TRzRadioGroup *BDiskretMul;
    void __fastcall BPeriodSelect(TObject *Sender);
    void __fastcall BPeriodKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall BEnableClick(TObject *Sender);
    void __fastcall BPlusClick(TObject *Sender);
    void __fastcall BMinusClick(TObject *Sender);
private:	// User declarations
    bool IsErr;

    TOnUpsWriteMem32 FOnUpsWriteMem32;
    TOnUpsReadMem32  FOnUpsReadMem32;

    bool __fastcall GetDiskretNs(U64 *val);

public:		// User declarations
    __fastcall TFrIisoip(TComponent* Owner);
    int NumGen;

    bool __fastcall SetPeriodNs(U64 val);

    bool __fastcall GetPeriodNs(U64 *val);

    bool __fastcall TFrIisoip::ApplyData(void);


    __property TOnUpsWriteMem32 OnUpsWriteMem32 = {
                                                    read  = FOnUpsWriteMem32,
                                                    write = FOnUpsWriteMem32
                                                  };

    __property TOnUpsWriteMem32 OnUpsReadMem32 = {
                                                    read  = FOnUpsReadMem32,
                                                    write = FOnUpsReadMem32
                                                  };

};
//---------------------------------------------------------------------------
extern PACKAGE TFrIisoip *FrIisoip;
//---------------------------------------------------------------------------
#endif
