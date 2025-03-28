//---------------------------------------------------------------------------


#ifndef TFrWritePrgCpu0H
#define TFrWritePrgCpu0H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include "TFrChangeFile.h"
#include "extdefs.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFrWritePrgCpu0 : public TFrame
{
__published:	// IDE-managed Components
    TRzGroupBox *RzGroupBox2;
    TRzLabel *RzLabel3;
    TRzBitBtn *BtnWrite;
    TFrChangeFile *FrChangeFile1;
    TRzBitBtn *BtnCompare;
    void __fastcall BtnWriteClick(TObject *Sender);
    void __fastcall BtnCompareClick(TObject *Sender);
private:	// User declarations
    U32 Address;
    void __fastcall WriteFunc(TObject *Sender);
    void __fastcall CompareFunc(TObject *Sender);

    bool __fastcall OnConverted(TObject *Sender,UCHAR *buf, U32 len);
    bool __fastcall OnSendBuf(TObject *Sender,UCHAR *buf, U32 len, U32 percent);
    bool __fastcall OnAfterSend(TObject *Sender);
    void __fastcall OnCvtError(TObject *Sender,DWORD ErrCode);



public:		// User declarations
    U32 Nk;
    U32 DstAdr;
    BOOL Cpu1Mode;
    __fastcall TFrWritePrgCpu0(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrWritePrgCpu0 *FrWritePrgCpu0;
//---------------------------------------------------------------------------
#endif
