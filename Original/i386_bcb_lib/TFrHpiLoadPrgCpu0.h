//---------------------------------------------------------------------------


#ifndef TFrHpiLoadPrgCpu0H
#define TFrHpiLoadPrgCpu0H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include "TFrChangeFile.h"
#include <ExtCtrls.hpp>
#include <extdefs.h>
//---------------------------------------------------------------------------
class TFrHpiLoadPrgCpu0 : public TFrame
{
__published:	// IDE-managed Components
    TRzGroupBox *RzGroupBox2;
    TRzLabel *RzLabel3;
    TRzBitBtn *BtnLoad;
    TFrChangeFile *ChangeFile;
    void __fastcall BtnLoadClick(TObject *Sender);
private:	// User declarations
    void __fastcall LoadFunc(TObject *Sender);
    bool __fastcall OnSendBuf(TObject *Sender,UCHAR *buf, U32 len, U32 percent);
    bool __fastcall OnBeforeSend(TObject *Sender);
    bool __fastcall OnAfterSend(TObject *Sender);
    void __fastcall OnCvtError(TObject *Sender,DWORD ErrCode);
    bool __fastcall OnConverted(TObject *Sender,UCHAR *buf, U32 len);


public:		// User declarations
    int Nk;
    __fastcall TFrHpiLoadPrgCpu0(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TFrHpiLoadPrgCpu0 *FrHpiLoadPrgCpu0;
//---------------------------------------------------------------------------
#endif
