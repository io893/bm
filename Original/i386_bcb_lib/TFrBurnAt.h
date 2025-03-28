//---------------------------------------------------------------------------


#ifndef TFrBurnAtH
#define TFrBurnAtH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "extdefs.h"
#include "RzButton.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include "TFrChangeFile.h"
#include <ExtCtrls.hpp>
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TFrBurnAt : public TFrame
{
__published:	// IDE-managed Components
    TRzGroupBox *RzGroupBox3;
    TRzLabel *RzLabel2;
    TRzLabel *RzLabel4;
    TRzBitBtn *BtnWrite;
    TFrChangeFile *FrChangeFile1;
    TRzBitBtn *BtnCompare;
    TFrChangeFile *FrChangeFile2;
    TRzCheckBox *RzCheckBox1;
    TRzSpinEdit *RzSpinEdit1;
    TRzLabel *RzLabel1;
    void __fastcall BtnWriteClick(TObject *Sender);
    void __fastcall BtnCompareClick(TObject *Sender);
private:	// User declarations
//    bool NeedBurnAt2;               // true если необходимо записать AT2

    int ValueA2;                    // Адресный разряд AT17F16
    U32 Addr16;                     // Параметр при прожиге
    u32 CrNumWrite;                 // Текущий проход записи



    bool __fastcall OnBeforeSendW(TObject *Sender);
    bool __fastcall OnSendBufW(TObject *Sender,UCHAR *buf, U32 len, U32 percent);
    bool __fastcall OnBeforeSendC(TObject *Sender);
    bool __fastcall OnSendBufC(TObject *Sender,UCHAR *buf, U32 len, U32 percent);
    void __fastcall OnCvtError(TObject *Sender,DWORD ErrCode);

    void __fastcall WriteFunc  (TObject *Sender);
    void __fastcall CompareFunc(TObject *Sender);

public:		// User declarations
    __fastcall TFrBurnAt(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrBurnAt *FrBurnAt;
//---------------------------------------------------------------------------
#endif
