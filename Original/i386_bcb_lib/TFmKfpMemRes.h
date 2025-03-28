//---------------------------------------------------------------------------

#ifndef TFmKfpMemResH
#define TFmKfpMemResH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzTabs.hpp"
#include "TFrKzvEdit.h"
#include "RzButton.hpp"
#include "RzRadChk.hpp"
#include "RzStatus.hpp"
#include <AppEvnts.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzBorder.hpp"
//---------------------------------------------------------------------------
class TFmKfpMemRes : public TForm
{
__published:	// IDE-managed Components
    TRzPageControl *RzPageControl1;
    TRzTabSheet *TabSheet1;
    TRzTabSheet *TabSheet2;
    TFrKzvEdit *FrKzvEdit1;
    TFrKzvEdit *FrKzvEdit2;
    TApplicationEvents *ApplicationEvents1;
    TRzPanel *RzPanel1;
    TRzToolButton *RzToolButton1;
    TImageList *ImageList1;
    TRzToolButton *RzToolButton2;
    TRzToolButton *RzToolButton3;
    TRzToolButton *RzToolButton4;
    TRzMarqueeStatus *P1;
    TRzMarqueeStatus *P0;
    TRzMarqueeStatus *LD;
    TRzMarqueeStatus *TVal;
    TRzPanel *RzPanel2;
    TRzBitBtn *RzBitBtn1;
    TRzBitBtn *BSbusTest;
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ApplicationEvents1Message(tagMSG &Msg, bool &Handled);
    void __fastcall RzToolButton1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall RzBitBtn1Click(TObject *Sender);
    void __fastcall BSbusTestClick(TObject *Sender);
    void __fastcall FrKzvEdit1KzvWSbadrChange(TObject *Sender);
private:	// User declarations
    void __fastcall OnAutoUpdate(TObject *Sender);
    bool __fastcall UpdateAll(void);
    bool __fastcall SendSbusData(int adr,U32 *buf,int len16,int num16);
    void __fastcall TestSbusFunc(TObject *Sender);

    bool IsErr;
public:		// User declarations
    int Nk;
    int DstAdr;
    __fastcall TFmKfpMemRes(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFmKfpMemRes *FmKfpMemRes;
//---------------------------------------------------------------------------
#endif
