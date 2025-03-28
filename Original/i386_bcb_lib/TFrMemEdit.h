//---------------------------------------------------------------------------


#ifndef TFrMemEditH
#define TFrMemEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include "RzEdit.hpp"
#include <Mask.hpp>
#include <extdefs.h>
#include <TFmLib.h>
//---------------------------------------------------------------------------
class TFrMemEdit : public TFrame
{
__published:	// IDE-managed Components
    TStringGrid *StringGrid;
    void __fastcall StringGridSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
    void __fastcall StringGridKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
    U32 CalkCurrentAdr(int ACol,int ARow);
    int CurRow,CurCol;

    bool FIsUpsMode;

    TOnKioWriteMem32 FOnKioWriteMem32;
    TOnKioReadMem32  FOnKioReadMem32;

    TOnUpsWriteMem32 FOnUpsWriteMem32;
    TOnUpsReadMem32  FOnUpsReadMem32;

    void writeIsUpsMode(bool mode)
    {
        if(mode == true)
        {
            StringGrid->Cells[0][0] = "Адрес";
            StringGrid->Cells[1][0] = "0";
            StringGrid->Cells[2][0] = "1";
            StringGrid->Cells[3][0] = "2";
            StringGrid->Cells[4][0] = "3";
        }else{
            StringGrid->Cells[0][0] = "Адрес";
            StringGrid->Cells[1][0] = "0";
            StringGrid->Cells[2][0] = "4";
            StringGrid->Cells[3][0] = "8";
            StringGrid->Cells[4][0] = "C";
        }
        FIsUpsMode = mode;
    }

public:		// User declarations

    int  NkKio,DstAdrKio;

    bool __fastcall UpdateData(void);

    __fastcall TFrMemEdit(TComponent* Owner);

    __property bool IsUpsMode = {   read  = FIsUpsMode,
                                    write = writeIsUpsMode,
                                };


    __property TOnKioWriteMem32 OnKioWriteMem32 = {
                                                    read  = FOnKioWriteMem32,
                                                    write = FOnKioWriteMem32
                                                  };

    __property TOnKioWriteMem32 OnKioReadMem32 = {
                                                    read  = FOnKioReadMem32,
                                                    write = FOnKioReadMem32
                                                  };

    __property TOnUpsWriteMem32 OnUpsWriteMem32 = {
                                                    read  = FOnUpsWriteMem32,
                                                    write = FOnUpsWriteMem32
                                                  };

    __property TOnUpsWriteMem32 OnUpsReadMem32 = {
                                                    read  = FOnUpsReadMem32,
                                                    write = FOnUpsReadMem32
                                                  };

};
//---------------------------------------------------------------------------
extern PACKAGE TFrMemEdit *FrMemEdit;
//---------------------------------------------------------------------------
#endif
