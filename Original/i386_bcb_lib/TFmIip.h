//---------------------------------------------------------------------------

#ifndef TFmIipH
#define TFmIipH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TFrIsoip.h"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <AppEvnts.hpp>
#include "RzCmboBx.hpp"
#include "RzLabel.hpp"
#include "RzRadGrp.hpp"
#include "RzRadChk.hpp"
//---------------------------------------------------------------------------
class TFmIip : public TForm
{
__published:	// IDE-managed Components
    TFrIisoip *FrIisoip1;
    TFrIisoip *FrIisoip2;
    TRzPanel *RzPanel1;
    TRzToolButton *RzToolButton1;
    TImageList *ImageList1;
    TApplicationEvents *ApplicationEvents1;
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ApplicationEvents1Message(tagMSG &Msg, bool &Handled);
    void __fastcall RzToolButton1Click(TObject *Sender);
private:	// User declarations
    bool IsErr;

public:		// User declarations
    __fastcall TFmIip(TComponent* Owner);
    int Nk;
    int DstAdr;

    bool __fastcall SendSbusData(int adr,U32 *buf,int len16,int cnt16);
};
//---------------------------------------------------------------------------
extern PACKAGE TFmIip *FmIip;
//---------------------------------------------------------------------------
#endif
