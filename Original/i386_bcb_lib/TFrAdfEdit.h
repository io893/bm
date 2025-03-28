//---------------------------------------------------------------------------


#ifndef TFrAdfEditH
#define TFrAdfEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
#include "extdefs.h"
#include "RzButton.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzStatus.hpp"
#include <TFmLib.h>
//---------------------------------------------------------------------------

typedef struct
{
    U32 c       : 2,
        pc      : 2,         // 1
        cr      : 1,         // 0
        m       : 3,         // 1
        pdp     : 1,         // 1
        cp      : 1,         //
        cpg     : 1,
        mtld    : 1,
        pl      : 2,          // 3
        cpi1    : 3,          // 7
        cpi2    : 3,          // 7
        pd      : 2,
        rsv     : 2;
}CLATCH;

typedef struct
{
    U32 c       : 2,
        rsv     : 6,
        b       : 13,           // 100
        cpg     : 1,
        rsv1    : 2;
}NLATCH;

typedef struct
{
    U32 c       : 2,
        r       : 14,           // 5
        abp     : 2,
        ldp     : 1,
        tmb     : 1,
        bsc     : 2,
        rsv1    : 2;
}RLATCH;


class TFrAdfEdit : public TFrame
{
__published:	// IDE-managed Components
    TRzGroupBox *RzGroupBox1;
    TRzSpinEdit *REdit;
    TRzBitBtn *RzBitBtn1;
    TRzLabel *RzLabel4;
    TRzMarqueeStatus *Ld;
    TRzSpinEdit *REdit1;
    void __fastcall RzBitBtn1Click(TObject *Sender);
private:	// User declarations

    U32  _val32_,_adr32_;             // Временные переменная для работы define
    int Nk;
    int DstAdr;

    TOnKioWriteMem32 FOnKioWriteMem32;
    TOnKioReadMem32  FOnKioReadMem32;

public:		// User declarations
    __fastcall TFrAdfEdit(TComponent* Owner);

    bool __fastcall UpdateAll(void);


    __property TOnKioWriteMem32 OnKioWriteMem32 = {
                                                    read  = FOnKioWriteMem32,
                                                    write = FOnKioWriteMem32
                                                  };

    __property TOnKioWriteMem32 OnKioReadMem32 = {
                                                    read  = FOnKioReadMem32,
                                                    write = FOnKioReadMem32
                                                  };

};
//---------------------------------------------------------------------------
extern PACKAGE TFrAdfEdit *FrAdfEdit;
//---------------------------------------------------------------------------
#endif
