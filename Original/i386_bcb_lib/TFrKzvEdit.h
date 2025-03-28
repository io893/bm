//---------------------------------------------------------------------------
#ifndef TFrKzvEditH
#define TFrKzvEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include "RzStatus.hpp"
#include "TFrTimEdit.h"
#include <ExtCtrls.hpp>
#include "RzTreeVw.hpp"
#include <ComCtrls.hpp>
#include "RzCmboBx.hpp"
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "RzLabel.hpp"
#include "RzListVw.hpp"
#include "RzSpnEdt.hpp"

#include <TFmLib.h>
#include "..\c64_lib\kfp_reg.h"
//---------------------------------------------------------------------------
class TFrKzvEdit : public TFrame
{
__published:	// IDE-managed Components
    TRzGroupBox *RzGroupBox1;
    TRzLabel *RzLabel1;
    TRzLabel *RzLabel2;
    TRzCheckBox *KzvWEnso;
    TRzCheckBox *KzvWStso;
    TRzGroupBox *RzGroupBox2;
    TRzListView *ListView;
    TRzComboBox *LcRv;
    TRzGroupBox *RzGroupBox3;
    TRzGroupBox *RzGroupBox4;
    TRzLabel *RzLabel3;
    TRzCheckBox *KzvWTest;
    TRzCheckBox *KzvWEnmod;
    TRzCheckBox *KzvWCpsb;
    TRzLabel *RzLabel4;
    TRzCheckBox *KzvWEnsb;
    TRzComboBox *KzvWAtt;
    TRzComboBox *KzvWSbadr;
    TRzLabel *RzLabel5;
    TRzComboBox *KzvWVpage;
    TRzLabel *RzLabel6;
    TRzComboBox *KzvWSbpage;
    TRzLabel *RzLabel8;
    TRzLabel *RzLabel9;
    TRzLabel *RzLabel10;
    TRzEdit *KzvRTzso;
    TRzLabel *RzLabel11;
    TRzEdit *KzvRNumso;
    TRzEdit *KzvRLadr;
    TRzEdit *KzvWLadr;
    TRzEdit *LcTz;
    TRzEdit *LcFd;
    TRzEdit *LcFsh;
    TRzEdit *LcAc;
    TRzEdit *KzvWPpso;
    TRzEdit *KzvWTzso;
    TRzGroupBox *RzGroupBox5;
    TRzMarqueeStatus *BSo;
    TRzMarqueeStatus *BK1;
    TRzMarqueeStatus *BK2;
    TRzMarqueeStatus *BK16;
    TRzMarqueeStatus *Pout;
    TRzEdit *KzvRppeso;
    TRzLabel *RzLabel7;
    TRzCheckBox *BlPrd;
    TRzMarqueeStatus *Prd;
    TRzCheckBox *BEnI;
    TRzCheckBox *BEnQ;
    TRzCheckBox *RzCheckBox1;
    void __fastcall KzvWSbadrChange(TObject *Sender);
    void __fastcall KzvWAttChange(TObject *Sender);
    void __fastcall KzvWTzsoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall KzvWEnsoClick(TObject *Sender);
    void __fastcall KzvWPpsoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall KzvWCpsbClick(TObject *Sender);
    void __fastcall KzvWEnsbClick(TObject *Sender);
    void __fastcall KzvWSbpageChange(TObject *Sender);
    void __fastcall KzvWVpageChange(TObject *Sender);
    void __fastcall KzvWLadrKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall BtnReplaceClick(TObject *Sender);
    void __fastcall ListViewDblClick(TObject *Sender);
    void __fastcall ListViewCheckStateChange(TObject *Sender,
          TListItem *Item);
    void __fastcall LcRvChange(TObject *Sender);
    void __fastcall LcTzKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall ListViewChange(TObject *Sender, TListItem *Item,
          TItemChange Change);
    void __fastcall BlPrdClick(TObject *Sender);
    void __fastcall BEnIClick(TObject *Sender);
    void __fastcall RzCheckBox1Click(TObject *Sender);
private:	// User declarations

    TOnKioWriteMem32 FOnKioWriteMem32;
    TOnKioReadMem32  FOnKioReadMem32;

    U32  _val32_,_adr32_;             // Временные переменная для работы define
    int  Nk;
    int  DstAdr;
    bool IsErr;



    void __fastcall WriteLc(int nlc);
    void __fastcall WriteLcMask(void);


public:		// User declarations

    int             NumKzv;             // номер КЗВ
    TFrKzvEdit      *FriendKzv;
    LCKZV           LcKzv[32];
    KZVW            KzvW;


    bool __fastcall ApplyAll(void);

    __fastcall TFrKzvEdit(TComponent* Owner);

    __fastcall bool UpdateAll(void);

    bool __fastcall ReceiveSbusData(int adr,U32 *buf,int len16);


    __fastcall void AfterSaveState(TRzRegIniFile *IniFile);
    __fastcall void AfterLoadState(TRzRegIniFile *IniFile);


    __property TOnKioWriteMem32 OnKioWriteMem32 = {
                                                    read  = FOnKioWriteMem32,
                                                    write = FOnKioWriteMem32
                                                  };

    __property TOnKioWriteMem32 OnKioReadMem32  = {
                                                    read  = FOnKioReadMem32,
                                                    write = FOnKioReadMem32
                                                  };
};
//---------------------------------------------------------------------------
extern PACKAGE TFrKzvEdit *FrKzvEdit;
//---------------------------------------------------------------------------
#endif
