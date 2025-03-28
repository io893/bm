//---------------------------------------------------------------------------


#ifndef TFrLoadCfgUpsH
#define TFrLoadCfgUpsH
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
#include "extdefs.h"
//---------------------------------------------------------------------------
class TFrLoadCfgUps : public TFrame
{
__published:	// IDE-managed Components
    TRzGroupBox *RzGroupBox1;
    TRzLabel *RzLabel1;
    TRzLabel *RzLabel2;
    TFrChangeFile *FrChangeFile1;
    TFrChangeFile *FrChangeFile2;
    TRzBitBtn *BtnLoad;
    void __fastcall BtnLoadClick(TObject *Sender);
private:	// User declarations
    bool __fastcall OnBeforeSendCpu(TObject *Sender);
    bool __fastcall OnSendBufCpu(TObject *Sender,UCHAR *buf, U32 len, U32 percent);
    bool __fastcall OnBeforeSendFpga(TObject *Sender);
    bool __fastcall OnSendBufFpga(TObject *Sender,UCHAR *buf, U32 len, U32 percent);
    void __fastcall OnCvtError(TObject *Sender,DWORD ErrCode);

    void __fastcall LoadFunc(TObject *Sender);

public:		// User declarations
    __fastcall TFrLoadCfgUps(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrLoadCfgUps *FrLoadCfgUps;
//---------------------------------------------------------------------------
#endif
