//---------------------------------------------------------------------------

#ifndef TFmPressSb1H
#define TFmPressSb1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFmPressSb1 : public TForm
{
__published:	// IDE-managed Components
    TButton *Button1;
    TButton *Button2;
    TLabel *Label1;
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFmPressSb1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFmPressSb1 *FmPressSb1;
//---------------------------------------------------------------------------
#endif
