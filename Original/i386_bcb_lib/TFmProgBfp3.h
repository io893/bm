//---------------------------------------------------------------------------

#ifndef TFmProgBfp3H
#define TFmProgBfp3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzTreeVw.hpp"
#include <ComCtrls.hpp>
#include "RzLstBox.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzShellDialogs.hpp"
#include <Dialogs.hpp>
#include <extdefs.h>
//---------------------------------------------------------------------------
class TFmProgBfp3 : public TForm
{
__published:	// IDE-managed Components
    TRzCheckTree *CheckTree;
    TRzPanel *RzPanel1;
    TRzBitBtn *BtnWrite;
    TRzBitBtn *BtnCompare;
    TOpenDialog *OpenDialog;
    TRzBitBtn *BtnLoad;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormClick(TObject *Sender);
    void __fastcall CheckTreeDblClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall BtnCompareClick(TObject *Sender);
    void __fastcall BtnWriteClick(TObject *Sender);
    void __fastcall BtnLoadClick(TObject *Sender);
private:	// User declarations
    int         GpValueA2;          // Адресный разряд AT17F16
    TTreeNode*  GpNode;
    int         GpNk;
    U32         GpAdr;
    int         GpDst;

    AnsiString NodeCaption(TTreeNode *Node);
    AnsiString NodeParam(TTreeNode *Node);
    AnsiString NodePath(TTreeNode *Node);
    void SaveCheckTree(void);
    void LoadCheckTree(void);

    void __fastcall CompareFunc(TObject *Sender);
    bool __fastcall OnSendBufC(TObject *Sender,UCHAR *buf, U32 len, U32 percent);
    bool __fastcall OnBeforeSendC(TObject *Sender);

    void __fastcall WriteFunc(TObject *Sender);
    bool __fastcall OnBeforeSendW(TObject *Sender);
    bool __fastcall OnSendBufW(TObject *Sender,UCHAR *buf, U32 len, U32 percent);
    bool __fastcall OnCpuConvertedW(TObject *Sender,UCHAR *buf, U32 len);
    bool __fastcall OnCpuSendBufW(TObject *Sender,UCHAR *buf, U32 len, U32 percent);
    bool __fastcall OnCpuAfterSendW(TObject *Sender);

    void __fastcall LoadFunc(TObject *Sender);
    bool __fastcall OnBeforeSendL3(TObject *Sender);
    bool __fastcall OnSendBufL3(TObject *Sender,UCHAR *buf, U32 len, U32 percent);
    bool __fastcall OnConvertedL3(TObject *Sender,UCHAR *buf, U32 len);
    bool __fastcall OnAfterSendL3(TObject *Sender);


    void __fastcall OnCvtError(TObject *Sender,DWORD ErrCode);

public:		// User declarations
    __fastcall TFmProgBfp3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFmProgBfp3 *FmProgBfp3;
//---------------------------------------------------------------------------
#endif
