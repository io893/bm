//---------------------------------------------------------------------------
#ifndef TUpsDriverH
#define TUpsDriverH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include <UpsPackage.h>

//-------------------------------------------------------
// Структура пакета для обмена с платой УПС
//-------------------------------------------------------
typedef struct
{
    // заголовок
    UINT    len8 : 12,        // размер пакета в байтах(включая заголовок)
            id   : 12,        // идетификатор пакета
            num  : 8;         // номер пакета
    // буфер
    UINT    buf[(2048-4)/4];
}UPSPACKET;

#define UPSPACKET_SIZE_BUF8 ((2048-4))

typedef void __fastcall (__closure *TGetPacketEvent)(System::TObject* Sender,UPSPACKET *packet);

enum TFtdiState{ftsUnconnect,ftsBitBang,ftsNormal};
//---------------------------------------------------------------------------
class PACKAGE TUpsDriver : public TComponent
{
private:
    TNotifyEvent    FOnResetUps;
    TNotifyEvent    FOnConnectFtdi;
    TNotifyEvent    FOnUnconnectFtdi;
    TUpsErrorEvent  FOnError;
    TGetPacketEvent FOnGetPacket;

    TFtdiState   FFtdiState;

    UINT            TimeOutSpiMode;

    void*  FtHandle;
    unsigned char FtOutBuf[1024];
    int           FtOutInd;

    UINT    SendPackNum;        

    void __fastcall TimerEvent(TObject *Sender);
    void __fastcall SetFtdiState(TFtdiState state);
    TFtdiState __fastcall GetFtdiState(void);

    void __fastcall CloseFtdi(void);
    bool __fastcall ClearFtdi(void);
    bool __fastcall OpenFtdiNormalMode(void);
    bool __fastcall OpenFtdiBitBangMode(void);
    bool __fastcall SetSplMode(void);
    bool __fastcall FlushFtdi(void);

    bool __fastcall _WaitPacket(UPSPACKET *packet,UINT time,UINT id,UINT num,bool RetOnAny);


    bool __fastcall Put(unsigned char byte)
    {
        FtOutBuf[FtOutInd++] = byte;
        if(FtOutInd >= sizeof(FtOutBuf))
        {
                return FlushFtdi();
        }
            return true;
    }


    virtual void __fastcall Loaded(void);

protected:
public:
    TTimer       *Timer;


    __property TFtdiState FtdiState = { read  = GetFtdiState,
                                        write = SetFtdiState  };

    bool __fastcall Reset(bool spl_mode);
    bool __fastcall SendSpiBuf(unsigned long *buf, int siz);

    bool __fastcall SendPacket(UPSPACKET *packet);
    bool __fastcall WaitPacket(UPSPACKET *packet,UINT time);


    bool __fastcall Exchange(UINT tid,UCHAR *tbuf,UINT tlen,UINT rid,UCHAR *rbuf,UINT rsiz,UINT *rlen,UINT timeo);

    __fastcall TUpsDriver(TComponent* Owner);
    __fastcall ~TUpsDriver();

__published:
    __property TNotifyEvent OnResetUps     = { read  = FOnResetUps,
                                               write = FOnResetUps      };

    __property TNotifyEvent OnConnectFtdi  = { read  = FOnConnectFtdi,
                                               write = FOnConnectFtdi   };
    __property TNotifyEvent OnUnconnectFtdi  = { read  = FOnUnconnectFtdi,
                                               write = FOnUnconnectFtdi   };

    __property TUpsErrorEvent OnError      = { read  = FOnError,
                                               write = FOnError      };

    __property TGetPacketEvent OnGetPacket = { read  = FOnGetPacket,
                                               write = FOnGetPacket  };

};
//---------------------------------------------------------------------------
#endif
