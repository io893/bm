//---------------------------------------------------------------------------


#ifndef Fr1H
#define Fr1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
#include "RzButton.hpp"
//---------------------------------------------------------------------------
class TFrame1 : public TFrame
{
__published:	// IDE-managed Components
    TRzBitBtn *RzBitBtn3;
    TRzBitBtn *RzBitBtn4;
    TRzBitBtn *RzBitBtn8;
    TRzMaskEdit *RzMaskEdit3;
    TRzMaskEdit *RzMaskEdit5;
    TRzMaskEdit *RzMaskEdit6;
    TRzMaskEdit *RzMaskEdit7;
    TRzBitBtn *RzBitBtn10;
    TRzBitBtn *RzBitBtn1;
    TRzBitBtn *RzBitBtn2;
    void __fastcall RzBitBtn3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFrame1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame1 *Frame1;
//---------------------------------------------------------------------------
#endif
