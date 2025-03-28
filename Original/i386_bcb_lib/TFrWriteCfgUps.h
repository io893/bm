//---------------------------------------------------------------------------


#ifndef TFrWriteCfgUpsH
#define TFrWriteCfgUpsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include "TFrChangeFile.h"
#include <ExtCtrls.hpp>
#include "extdefs.h"
//---------------------------------------------------------------------------
class TFrWriteCfgUps : public TFrame
{
__published:	// IDE-managed Components
    TRzGroupBox *RzGroupBox1;
    TFrChangeFile *FrChangeFile1;
    TFrChangeFile *FrChangeFile2;
    TRzLabel *RzLabel1;
    TRzLabel *RzLabel2;
    TRzBitBtn *BtnWrite;
    TRzBitBtn *BtnVerify;
    TRzCheckBox *RzCheckBox1;
    TRzCheckBox *RzCheckBox2;
    void __fastcall BtnWriteClick(TObject *Sender);
    void __fastcall BtnVerifyClick(TObject *Sender);
private:	// User declarations
    U32 Address;

    bool __fastcall WriteArea(U32 addr8,UCHAR* buf8,U32 siz8);
    bool __fastcall EraseArea(int first_sec,int num_sec);
    bool __fastcall VerifyArea(U32 addr8,UCHAR* buf8,U32 len8);

    void __fastcall OnCvtError(TObject *Sender,DWORD ErrCode);
    bool __fastcall OnSendBufCpu(TObject *Sender,UCHAR *buf, U32 len, U32 percent);
    bool __fastcall OnBeforeSendCpu(TObject *Sender);
    bool __fastcall OnConvertedFpga(TObject*  Sender,UCHAR* buf, U32 len );
    bool __fastcall OnSendBufFpga(TObject *Sender,UCHAR *buf, U32 len, U32 percent);
    bool __fastcall OnBeforeSendFpga(TObject *Sender);

    bool __fastcall OnSendBufVCpu(TObject *Sender,UCHAR *buf, U32 len, U32 percent);
    bool __fastcall OnBeforeSendVCpu(TObject *Sender);
    bool __fastcall OnConvertedVFpga(TObject*  Sender,UCHAR* buf, U32 len );
    bool __fastcall OnSendBufVFpga(TObject *Sender,UCHAR *buf, U32 len, U32 percent);
    bool __fastcall OnBeforeSendVFpga(TObject *Sender);


    void __fastcall WriteFunc(TObject *Sender);
    void __fastcall VerifyFunc(TObject *Sender);


public:		// User declarations
    __fastcall TFrWriteCfgUps(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrWriteCfgUps *FrWriteCfgUps;
//---------------------------------------------------------------------------
#endif
