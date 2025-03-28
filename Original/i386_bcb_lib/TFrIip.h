//---------------------------------------------------------------------------


#ifndef TFrIipH
#define TFrIipH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include <ExtCtrls.hpp>
#include "RzLabel.hpp"
//---------------------------------------------------------------------------
class TFrame1 : public TFrame
{
__published:	// IDE-managed Components
    TRzGroupBox *RzGroupBox1;
    TRzComboBox *KzvWSbadr;
    TRzBitBtn *RzBitBtn1;
    TRzBitBtn *RzBitBtn2;
    TRzCheckBox *RzCheckBox1;
    TRzLabel *RzLabel3;
    TRzLabel *RzLabel1;
    TRzComboBox *RzComboBox1;
private:	// User declarations
public:		// User declarations
    __fastcall TFrame1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame1 *Frame1;
//---------------------------------------------------------------------------
#endif
