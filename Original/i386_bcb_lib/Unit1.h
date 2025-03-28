//---------------------------------------------------------------------------


#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TFrame1 : public TFrame
{
__published:	// IDE-managed Components
    TRzSpinButtons *RzSpinButtons1;
    TRzNumericEdit *RzNumericEdit2;
    TRzSpinButtons *RzSpinButtons2;
    TRzNumericEdit *RzNumericEdit1;
    TRzSpinButtons *RzSpinButtons3;
    TRzNumericEdit *RzNumericEdit3;
    TRzLabel *RzLabel1;
    TRzLabel *RzLabel2;
    TRzLabel *RzLabel3;
    TRzSpinButtons *RzSpinButtons4;
    TRzNumericEdit *RzNumericEdit4;
    TRzLabel *RzLabel4;
private:	// User declarations
public:		// User declarations
    __fastcall TFrame1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame1 *Frame1;
//---------------------------------------------------------------------------
#endif
