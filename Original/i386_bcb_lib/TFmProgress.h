//---------------------------------------------------------------------------

#ifndef TFmProgressH
#define TFmProgressH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include "RzPrgres.hpp"
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
class TFmProgress : public TForm
{
__published:	// IDE-managed Components
    TRzPanel *RzPanel1;
    TRzProgressBar *ProgressBar;
    TRzBitBtn *BtnCancel;
    TRzLabel *Label;
    TApplicationEvents *ApplicationEvents1;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall ApplicationEvents1Message(tagMSG &Msg, bool &Handled);
    void __fastcall BtnCancelClick(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
    TNotifyEvent    ExecuteFunc;
public:		// User declarations
    bool    IsClickBreak;
    void   *Param;

    void    StartExecute(TNotifyEvent func,void *param);

    __fastcall TFmProgress(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFmProgress *FmProgress;
//---------------------------------------------------------------------------
#endif
