//---------------------------------------------------------------------------


#ifndef TFrTimEditH
#define TFrTimEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class TFrTimEdit : public TFrame
{
__published:	// IDE-managed Components
    TRzBitBtn *BtnDEF;
    TRzBitBtn *BtnM;
    TRzBitBtn *BtnP;
    TRzMaskEdit *MaskEdit;
    TRzMaskEdit *RzMaskEdit5;
    TRzMaskEdit *RzMaskEdit6;
    TRzMaskEdit *RzMaskEdit7;
    TRzBitBtn *BtnMAX;
    TRzBitBtn *BtnMIN;
    TMaskEdit *MaskEdit1;
    void __fastcall BtnDEFClick(TObject *Sender);
    void __fastcall BtnPClick(TObject *Sender);
    void __fastcall BtnMClick(TObject *Sender);
    void __fastcall MaskEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall BtnMINClick(TObject *Sender);
    void __fastcall BtnMAXClick(TObject *Sender);
    void __fastcall MaskEditEnter(TObject *Sender);

private:	// User declarations
//    U32             FValue;
    TNotifyEvent    FOnChangeValue;
    int             DefValue;
    int             MinValue;
    int             MaxValue;

    int  __fastcall readValue(void);
    void __fastcall writeValue(int val);
    int  __fastcall GetValueMask(void);

public:		// User declarations

    __fastcall TFrTimEdit(TComponent* Owner);

    __property int          Value           = { read  = readValue,
                                                write = writeValue };

    __property TNotifyEvent OnChangeValue   = { read  = FOnChangeValue,
                                                write = FOnChangeValue };
};
//---------------------------------------------------------------------------
extern PACKAGE TFrTimEdit *FrTimEdit;
//---------------------------------------------------------------------------
#endif
