//---------------------------------------------------------------------------
#ifndef TKioLibH
#define TKioLibH
//---------------------------------------------------------------------------
#include <vcl.h>

#include "TUpsLib.h"
class TKioLib : public TObject
{
    private:
        TUpsLib*        UpsLib;
        TUpsErrorEvent  FOnError;
        DWORD           TimeLabel;
        U32             EraseDst;
        U32             EraseAddr;

        char* TKioLib::AtErrStr(int err);

        bool __fastcall _DbGetBufKt(int nk,int dst,int nkt,int ind8,u32* buf,u32* len8);
        bool __fastcall  _DbSetDelKt(int nk,int dst,int nkt,int set,int siz8,bool *ok);
//        int __fastcall  _DbGetBufKt(int nk,int dst,int nkt,int ind8,u32* buf,u32* len8);

    public:
        __fastcall TKioLib(TUpsLib* upsLib);

        char* __fastcall GetPrint(int nk,int dst);
        char* __fastcall GetPrint(int nk,int dst, bool *is_err);
        
        bool  __fastcall EraseFlashSector(int nk,int dst,U32 addr);
        // возвращает  указатель на массив U32 buf[32];
        U32* __fastcall ReadFlash(int nk,int dst,U32 addr);
        bool __fastcall WriteFlash(int nk,int dst,U32 addr,U32 *buf,U32 siz16,U8 *err);
        bool __fastcall IsErasedFlashSector(int nk,bool *compl, bool *ok);

        bool __fastcall WriteMemBuf32(int nk,int dst,U32 *abuf,U32 *dbuf,U32 len);
        bool __fastcall ReadMemBuf32(int nk,int dst,U32 *abuf,U32 *dbuf,U32 len);

        bool __fastcall WriteMemBuf64(int nk,int dst,U32 *abuf,U64 *dbuf,U32 len);
        bool __fastcall ReadMemBuf64(int nk,int dst,U32 *abuf,U64 *dbuf,U32 len);

        bool __fastcall  AtReadId(int nk,int dst,int chip,u32* id,int *err,char** err_str);
        bool __fastcall  AtRead(int nk,int dst,int chip,u32 adr16,u32 *buf16,u32 len16,int *err,char **err_str);
        bool __fastcall  AtStartErase(int nk,int dst,int chip,int *err,char **err_str);
        bool __fastcall  AtWrite(int nk,int dst,int chip,u32 adr16,u32 *buf16,u32 len16,int *err,char **err_str);
        bool __fastcall  AtCheckErase(int nk,int dst,int chip,int *err,char **err_str);

        u32* __fastcall  RcvKioPack(int nk,u32 time);
        bool __fastcall  SndKioPack(int nk,int nkio,int dst,u32 *buf32);

        bool __fastcall  DbSetKt(int nk,int dst,int nkt,int siz8);
        bool __fastcall  DbDelKt(int nk,int dst,int nkt,int siz8);
        bool __fastcall  DbGetBufKt(int nk,int dst,int nkt,int siz8);

        bool __fastcall  DbSetKt(int nk,int dst,int nkt,int siz8,bool *ok);
        bool __fastcall  DbDelKt(int nk,int dst,int nkt, bool *ok);

        bool __fastcall  DbReadKt(int nk,int dst,int nkt,u32* buf,u32 *len8);


    __published:
        __property TUpsErrorEvent OnError   = { read  = FOnError, write = FOnError };
};






























#endif
