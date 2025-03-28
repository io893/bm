//---------------------------------------------------------------------------


#ifndef TFrResetH
#define TFrResetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TFrReset : public TFrame
{
__published:	// IDE-managed Components
    TRzBitBtn *BtnReset;
    TRzToolButton *RzToolButton1;
    TImageList *ImageList1;
    void __fastcall BtnResetClick(TObject *Sender);
private:	// User declarations
    void __fastcall ResetFunc(TObject *Sender);
public:		// User declarations
    __fastcall TFrReset(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrReset *FrReset;
//---------------------------------------------------------------------------
#endif
