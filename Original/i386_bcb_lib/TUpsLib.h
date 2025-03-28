//---------------------------------------------------------------------------

#ifndef UpsExchangeH
#define UpsExchangeH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <TUpsDriver.h>
#include <extdefs.h>

typedef void __fastcall (__closure *TOnRcvKioPack) (u32 nk,u32 *buf);
typedef void __fastcall (__closure *TOnSendKioPack)(u32 nk,u32 *buf);

//---------------------------------------------------------------------------
class /*PACKAGE*/ TUpsLib: public TObject
{
private:
    TUpsErrorEvent          FOnError;
    TUpsQuery               FOnSchLock;
    TUpsEvent               FOnSchUnlock;
    TUpsEvent               FOnLoadC64;
    TOnRcvKioPack           FOnRcvKioPack;
    TOnSendKioPack          FOnSendKioPack;

    TUpsDriver     *FUpsDriver;

    UCHAR  TBuf[sizeof(UPSPACKET)];
    U32    TInd;

    UCHAR  RBuf[sizeof(UPSPACKET)];
    U32    RInd,RLen;

    inline U32 Get8(void)
    {
        return RBuf[RInd++];
    }

    inline U32 Get16(void)
    {
        U32 val;
        val =  RBuf[RInd++];
        val |= (RBuf[RInd++] & 0xFF) << 8;
        return val;
    }

    inline U32 Get32(void)
    {
        U32 val;
        val =  RBuf[RInd++];
        val |= (RBuf[RInd++] & 0xFF) << 8;
        val |= (RBuf[RInd++] & 0xFF) << 16;
        val |= (RBuf[RInd++] & 0xFF) << 24;
        return val;
    }

    inline void GetBuf8(void* buf,U32 siz)
    {
        memcpy(buf,&RBuf[RInd],siz);
        RInd += siz;
    }

    inline void GetBuf16(void* buf,U32 siz)
    {
        GetBuf8(buf,siz*2);
    }

    inline void GetBuf32(void* buf,U32 siz)
    {
        GetBuf8(buf,siz*4);
    }

    inline void Put8(U32 val)
    {
        TBuf[TInd++] = val & 0xFF;
    }

    inline void Put16(U32 val)
    {
        TBuf[TInd++] = val & 0xFF;
        TBuf[TInd++] = (val >> 8) & 0xFF;
    }

    inline void Put32(U32 val)
    {
        TBuf[TInd++] = val & 0xFF;
        TBuf[TInd++] = (val >> 8) & 0xFF;
        TBuf[TInd++] = (val >> 16) & 0xFF;
        TBuf[TInd++] = (val >> 24) & 0xFF;
    }

    inline void PutBuf8(void* buf,U32 siz)
    {
        memcpy(&TBuf[TInd],buf,siz);
        TInd += siz;
    }

    inline void PutBuf16(void* buf,U32 siz)
    {
        PutBuf8(buf,siz*2);
    }

    inline void PutBuf32(void* buf,U32 siz)
    {
        PutBuf8(buf,siz*4);
    }

protected:

public:
    void __fastcall ProcessRcvKioPack(void);

    bool __fastcall FlStartEraseSector(U32 addr8,I8 *is_start);
    bool __fastcall FlIsCompleteEraseSector(I8* is_compl,I8 *is_err);
    bool __fastcall FlReadBuffer8(U32 addr8,U32* buf8, U32 siz8, U32 *readen8);
    bool __fastcall FlWriteBuffer8(U32 addr8,U32* buf8, U32 siz8, U32 *written8);

    bool __fastcall AtpReadDeviceID(I8 a2,U32 *did,I8 *is_ok);
    bool __fastcall AtpStartEraseChip(I8 a2,I8 *is_ok);
    bool __fastcall AtpIsCompleteEraseChip(I8 *iscompl, I8 *is_err);
    bool __fastcall AtpWriteBuffer16(I8 a2,U32 addr16,U32* buf16, U32 siz16, U32 *written16);
    bool __fastcall AtpReadBuffer16(I8 a2,U32 addr16,U32* buf16, U32 siz16, U32 *readen16);

    bool __fastcall KioLoadBuf(U8 numsch,U8 *buf8,U32 siz8,I8 *is_ok);
    bool __fastcall KioBeginLoad(U8 numsch,I8 *is_ok);
    bool __fastcall KioEndLoad(U8 numsch,I8 *is_ok);

    bool __fastcall GsSetState(U32 st,U32 *retst);
    bool __fastcall GsSetAndWaitState(U32 state);
    bool __fastcall GsGetState(U32 *retst);

    virtual bool __fastcall SendKioPack(U32 nk,U32 *buf,BOOL* err);

    bool __fastcall SendKioCommand(U32 nk,U32 cmd,BOOL* err);
    virtual bool __fastcall RcvKioPack(U32* nk,U32 *buf);
    virtual bool __fastcall RcvKioSysPack(U32 nk,U32 *buf,U32* len8,U32 ips,U32 tim);


    bool __fastcall  ReadMemBuf32(U32 *addr_buf,U32 *data_buf,U32 len);
    bool __fastcall  WriteMemBuf32(U32 *addr_buf,U32 *data_buf,U32 len);

    bool __fastcall  ResetDevice(void);


    __fastcall TUpsLib(TComponent* Owner);

__published:
    __property TUpsErrorEvent OnError   = { read  = FOnError,
                                            write = FOnError      };

    __property TUpsDriver* UpsDriver    = {  read  = FUpsDriver,
                                             write = FUpsDriver  };

    __property TOnRcvKioPack OnRcvKioPack   = { read  = FOnRcvKioPack,
                                                write = FOnRcvKioPack  };

    __property TOnSendKioPack OnSendKioPack  = { read  = FOnSendKioPack,
                                                 write = FOnSendKioPack  };



};
//---------------------------------------------------------------------------

#endif
