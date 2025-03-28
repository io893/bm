//---------------------------------------------------------------------------

#ifndef TFmLogWinH
#define TFmLogWinH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include "RzSplit.hpp"
#include <ExtCtrls.hpp>
#include "RzLstBox.hpp"
#include "RzForms.hpp"
#include <ImgList.hpp>

#include <TUpsDriver.h>
#include <AppEvnts.hpp>

//---------------------------------------------------------------------------
class TFmLogWin : public TForm
{
__published:	// IDE-managed Components
    TImageList *ImageList1;
    TTimer *Timer1;
    TRzToolbar *RzToolbar1;
    TRzToolButton *RzToolButton1;
    TRzSpacer *RzSpacer1;
    TRzListBox *ListBox;
    TApplicationEvents *ApplicationEvents1;
    void __fastcall RzCheckBox1Click(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall RzToolButton1Click(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ApplicationEvents1Message(tagMSG &Msg, bool &Handled);

private:	// User declarations



    UINT            PrintCount;
    void __fastcall OnModifyEvent(TObject* Sender);

public:		// User declarations
    TGetPacketEvent OldOnGetPacket;
    TNotifyEvent    OldOnModifyEvent;
    void __fastcall OnGetPacket(TObject* Sender,UPSPACKET *packet);

    bool    EnabledNk[32];
    bool    EnabledDst[32][32];

    void    __fastcall EnablePrint(int nk,int dst);
    void    __fastcall DisablePrint(int nk,int dst);



    __fastcall TFmLogWin(TComponent* Owner);
    __fastcall ~TFmLogWin();

    void __fastcall AddString(TObject* Sender,char* str);
};
//---------------------------------------------------------------------------
extern PACKAGE TFmLogWin *FmLogWin;
//---------------------------------------------------------------------------
#endif
