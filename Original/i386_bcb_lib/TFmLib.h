//---------------------------------------------------------------------------

#ifndef TFmLibH
#define TFmLibH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>

#include <Forms.hpp>

#include <extdefs.h>
//#include "..\vc33_ups_kfp\vc33_ups_kfp.h"
#include "..\c64_lib\stdkio.h"
#include "savfm.h"

#include "RzCommon.hpp"

#include <TUpsDriver.h>

#include "TUpsLib.h"
#include "TKioLib.h"

#include <AppEvnts.hpp>
#include <ExtCtrls.hpp>


//---------------------------------------------------------------------------
typedef bool __fastcall (__closure *TOnKioWriteMem32)(int nk, int dst, U32 *abuf, U32* dbuf, U32 len);
typedef bool __fastcall (__closure *TOnKioReadMem32) (int nk, int dst, U32 *abuf, U32* dbuf, U32 len);
typedef bool __fastcall (__closure *TOnUpsWriteMem32)(U32 *abuf, U32* dbuf, U32 len);
typedef bool __fastcall (__closure *TOnUpsReadMem32) (U32 *abuf, U32* dbuf, U32 len);



//---------------------------------------------------------------------------
class TFmLib : public TForm
{
__published:	// IDE-managed Components
    TRzRegIniFile *ConfigIni;
    TApplicationEvents *ApplicationEvents1;
    TTimer *Timer1;
    void __fastcall UpsDriverError(TObject *Sender, DWORD ErrCode);
    void __fastcall UpsError(TObject *Sender, DWORD ErrCode);
    void __fastcall KioError(TObject *Sender, DWORD ErrCode);
    void __fastcall ApplicationEvents1Message(tagMSG &Msg, bool &Handled);
    void __fastcall UpsDriverConnectFtdi(TObject *Sender);
    void __fastcall UpsDriverUnconnectFtdi(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
/*
    __property TNotifyEvent OnConnectUsb = {   read  = FOnConnectUsb,
                                               write = FOnConnectUsb   };

    __property TNotifyEvent OnConnectUsb = {   read  = FOnConnectUsb,
                                               write = FOnConnectUsb   };
*/
private:	// User declarations
//    TNotifyEvent    FOnModifyEvent;
//    TNotifyEvent    FOnAvtoUpdate;
    bool            FLock;
    TList           *UpdateList;

    DWORD           TimeForCheckHard;

    void __fastcall FuncResetDevice(TObject *Sender);
    void __fastcall FuncResetUps(TObject *Sender);


    void __fastcall StartProgram(void);
    void __fastcall CheckHard(void);


public:		// User declarations

    bool            IsUsbConnected;
    bool            IsUpsConnected;
    bool            IsFormClose;

    TUpsDriver      *UpsDriver;
    TUpsLib         *UpsLib;
    TKioLib         *KioLib;

    __fastcall TFmLib(TComponent* Owner);
    __fastcall TFmLib::~TFmLib();


    void ResetDeviceGui(char *caption,char* label);
    void ResetUpsGui(char *caption,char* label);


    bool __fastcall Lock(void)
    {
        bool old = FLock;
        FLock    = true;
//        if(FOnModifyEvent){  FOnModifyEvent(this);  }
        return old;
    };

    void __fastcall RestoreLock(bool st)
    {
        FLock    = st;
//        if(FOnModifyEvent){  FOnModifyEvent(this);  }
        return;
    };

    bool __fastcall IsLocked(void){ return FLock; }

    void __fastcall AddAutoUpdateCall(TNotifyEvent call)
    {
        TNotifyEvent *item  = new TNotifyEvent;
        *item = call;
        UpdateList->Add((void*)item);
    }

    void __fastcall DelAutoUpdateCall(TNotifyEvent call)
    {
        for(int i = 0; i < UpdateList->Count; i++)
        {
            TNotifyEvent *item;
            item = (TNotifyEvent*)UpdateList->Items[i];
            if(*item == call){UpdateList->Delete(i);}
        }
    }

    // Событие - Изменение Чего либо (появился отказ, наоборот и т.д)
/*    __property TNotifyEvent OnModifyEvent = {   read  = FOnModifyEvent,
                                                write = FOnModifyEvent
                                            };*/

    //--------------------------------------------------------------------------
    __inline bool UpsReset(bool is_spl)
    {

        bool ret;
        IsUpsConnected = false;
        ret = UpsLib->UpsDriver->Reset(is_spl);
        CheckHard();
//        if(FOnModifyEvent){  FOnModifyEvent(this);  }
        return ret;
    }
    //--------------------------------------------------------------------------
    __inline bool UpsSendSpiBuf(U32 *buf,int siz)
    {
        return UpsDriver->SendSpiBuf((ULONG*)buf,siz);
    }
    //--------------------------------------------------------------------------
    __inline bool UpsFlStartEraseSector(U32 addr8,I8 *is_start)
    {
        return UpsLib->FlStartEraseSector(addr8,is_start);
    }
    //--------------------------------------------------------------------------
    __inline bool UpsFlIsCompleteEraseSector(I8* is_compl,I8 *is_err)
    {
        return UpsLib->FlIsCompleteEraseSector(is_compl,is_err);
    }
    //--------------------------------------------------------------------------
    __inline bool UpsFlReadBuffer8(U32 addr8,U32* buf8, U32 siz8, U32 *readen8)
    {
        return UpsLib->FlReadBuffer8(addr8,buf8,siz8,readen8);
    }
    //--------------------------------------------------------------------------
    __inline bool UpsFlWriteBuffer8(U32 addr8,U32* buf8, U32 siz8, U32 *written8)
    {
        return UpsLib->FlWriteBuffer8(addr8,buf8,siz8,written8);
    }
    //--------------------------------------------------------------------------
    __inline bool UpsSendKioPacket(int nk,U32 *buf)
    {
        BOOL ret = FALSE;
        UpsLib->SendKioPack(nk,buf,&ret);
        return ret;
    }
    //--------------------------------------------------------------------------
    __inline bool UpsSendKioCommand(int nk,U32 cmd)
    {
        BOOL ret = FALSE;
        UpsLib->SendKioCommand(nk,cmd,&ret);
        return ret;
    }
    //--------------------------------------------------------------------------
    __inline bool UpsRecivKioPacket(int* nk,U32 *buf)
    {
        return UpsLib->RcvKioPack((U32 *)nk,buf);
    }
    //--------------------------------------------------------------------------
    __inline bool UpsSetState(U32 st,U32 *retst)
    {
        return UpsLib->GsSetState(st,retst);
    }
    //--------------------------------------------------------------------------
    __inline bool UpsSetAndWaitState(U32 state)
    {
        return UpsLib->GsSetAndWaitState(state);
    }
    //--------------------------------------------------------------------------
    __inline bool UpsAtpReadDeviceID(int a2,U32 *p_did,I8 *p_is_ok)
    {
        return UpsLib->AtpReadDeviceID(a2,p_did,p_is_ok);
    }
    //--------------------------------------------------------------------------
    __inline bool UpsAtpStartEraseChip(int a2,I8 *is_ok_pi8)
    {
        return UpsLib->AtpStartEraseChip(a2,is_ok_pi8);
    }
    //--------------------------------------------------------------------------
    __inline bool UpsAtpIsCompleteEraseChip(I8* is_compl_pi8,I8* is_err_pi8)
    {
        return UpsLib->AtpIsCompleteEraseChip(is_compl_pi8,is_err_pi8);
    }
    //--------------------------------------------------------------------------
    __inline bool UpsAtpWriteBuffer16(I8 a2,U32 addr16,U32* buf16, U32 siz16, U32 *written16)
    {
        return UpsLib->AtpWriteBuffer16(a2,addr16,buf16,siz16,written16);
    }
    //--------------------------------------------------------------------------
    __inline bool UpsAtpReadBuffer16(I8 a2,U32 addr16,U32* buf16, U32 siz16, U32 *readen16)
    {
        return UpsLib->AtpReadBuffer16(a2,addr16,buf16,siz16,readen16);
    }
    //--------------------------------------------------------------------------
    __fastcall bool UpsReadMemBuf32(U32 *addr_buf,U32 *data_buf,U32 len)
    {
        return UpsLib->ReadMemBuf32(addr_buf,data_buf,len);
    }
    //--------------------------------------------------------------------------
    __fastcall bool UpsWriteMemBuf32(U32 *addr_buf,U32 *data_buf,U32 len)
    {
        return UpsLib->WriteMemBuf32(addr_buf,data_buf,len);
    }
    //--------------------------------------------------------------------------
    __inline bool UpsResetDevice(void)
    {
        return UpsLib->ResetDevice();
    }
    //--------------------------------------------------------------------------
    __inline bool UpsSetResetDevice(bool val)
    {
        U32 addr_buf[] = {0x900010};
        U32 data_buf[] = {0};

        data_buf[0] = (val == true) ? 0 : 1;
        return UpsWriteMemBuf32(addr_buf,data_buf,1);
        
    }
    //--------------------------------------------------------------------------

    __inline char* KioGetPrint(int nk,int dst)
    {
        return KioLib->GetPrint(nk,dst);
    }
    //--------------------------------------------------------------------------
    __inline bool  KioEraseFlashSector(int nk,int dst,U32 addr)
    {
        return KioLib->EraseFlashSector(nk,dst,addr);
    }
    //--------------------------------------------------------------------------
    // возвращает  указатель на массив U32 buf[32];
    __inline U32* KioReadFlash(int nk,int dst,U32 addr)
    {
        return KioLib->ReadFlash(nk,dst,addr);
    }
    //--------------------------------------------------------------------------
    __inline bool KioWriteFlash(int nk,int dst,U32 addr,U32 *buf,U32 siz16,U8 *err)
    {
        return KioLib->WriteFlash(nk,dst,addr,buf,siz16,err);
    }
    //--------------------------------------------------------------------------
    __inline bool KioIsErasedFlashSector(int nk,bool *compl,bool *ok)
    {
        return KioLib->IsErasedFlashSector(nk,compl,ok);
    }
    //--------------------------------------------------------------------------
    __fastcall bool KioReadMemBuf32(int nk,int dst,U32 *abuf,U32 *dbuf,U32 len)
    {
        return KioLib->ReadMemBuf32(nk,dst,abuf,dbuf,len);
    }
    //--------------------------------------------------------------------------
    __fastcall bool KioWriteMemBuf32(int nk,int dst,U32 *abuf,U32 *dbuf,U32 len)
    {
        return KioLib->WriteMemBuf32(nk,dst,abuf,dbuf,len);
    }
    //--------------------------------------------------------------------------
    __fastcall bool KioReadMemBuf64(int nk,int dst,U32 *abuf,U64 *dbuf,U32 len)
    {
        return KioLib->ReadMemBuf64(nk,dst,abuf,dbuf,len);
    }
    //--------------------------------------------------------------------------
    __fastcall bool KioWriteMemBuf64(int nk,int dst,U32 *abuf,U64 *dbuf,U32 len)
    {
        return KioLib->WriteMemBuf64(nk,dst,abuf,dbuf,len);
    }
    //--------------------------------------------------------------------------
    __fastcall bool AtReadId(int nk,int dst,int chip,u32* id,int *err,char **err_str)
    {
        return KioLib->AtReadId(nk,dst,chip,id,err,err_str);
    }
    //--------------------------------------------------------------------------
    __fastcall  bool AtRead(int nk,int dst,int chip,u32 adr16, u32 *buf16,u32 len16,int *err,char **err_str)
    {
        return KioLib->AtRead(nk,dst,chip,adr16,buf16,len16,err,err_str);
    }
    //--------------------------------------------------------------------------
    bool __fastcall  AtWrite(int nk,int dst,int chip,u32 adr16,u32 *buf16,u32 len16,int *err,char **err_str)
    {
        return KioLib->AtWrite(nk,dst,chip,adr16,buf16,len16,err,err_str);
    }
    //--------------------------------------------------------------------------
    bool __fastcall  AtCheckErase(int nk,int dst,int chip,int *err,char **err_str)
    {
        return KioLib->AtCheckErase(nk,dst,chip,err,err_str);
    }
    //--------------------------------------------------------------------------
    bool __fastcall  AtStartErase(int nk,int dst,int chip,int *err,char **err_str)
    {
        return  KioLib->AtStartErase(nk,dst,chip,err,err_str);
    }
    //--------------------------------------------------------------------------
    u32* __fastcall  RcvKioPack(int nk,u32 time)
    {
        return KioLib->RcvKioPack(nk,time);
    }
    //--------------------------------------------------------------------------
    bool __fastcall  SndKioPack(int nk,int nkio,int dst,u32 *buf32)
    {
        return KioLib->SndKioPack(nk,nkio,dst, buf32);
    }
    //--------------------------------------------------------------------------
    __fastcall u32  GetKioVal32Try(int nk,u32 adr)
    {
        u32 a32[1];
        u32 d32[1];

        a32[0] = adr;

        if(KioReadMemBuf32(nk,DA_ANY,a32,d32,SIZE(a32)) == false){
            throw "Ошибка обмена по КИО.";
        }
        return d32[0];
    }
    //--------------------------------------------------------------------------
    __fastcall void PutKioVal32Try(int nk,u32 adr,u32 dat)
    {
        u32 a32[1];
        u32 d32[1];

        a32[0] = adr;
        d32[0] = dat;

        if(KioWriteMemBuf32(nk,DA_ANY,a32,d32,SIZE(a32)) == false){
            throw "Ошибка обмена по КИО.";
        }
        return;
    }
    //--------------------------------------------------------------------------
    __fastcall u64  GetKioVal64Try(int nk,u32 adr)
    {
        u32 a32[1];
        u64 d64[1];

        a32[0] = adr;

        if(KioReadMemBuf64(nk,DA_ANY,a32,d64,SIZE(a32)) == false){
            throw "Ошибка обмена по КИО.";
        }
        return d64[0];
    }
    //---------------------------------------------------------------------------
    __fastcall void PutKioVal64Try(int nk,u32 adr,u64 dat)
    {
        u32 a32[1];
        u64 d64[1];

        a32[0] = adr;
        d64[0] = dat;

        if(KioWriteMemBuf64(nk,DA_ANY,a32,d64,SIZE(a32)) == false){
            throw "Ошибка обмена по КИО.";
        }
        return;
    }
    //---------------------------------------------------------------------------
    __fastcall u32  GetUpsVal32Try(u32 adr)
    {
        u32 a32[1];
        u32 d32[1];

        a32[0] = adr;

        if(UpsReadMemBuf32(a32,d32,SIZE(a32)) == false)
        {
            throw "Ошибка обмена c UPS.";
        }
        return d32[0];
    }
    //---------------------------------------------------------------------------
    __fastcall void PutUpsVal32Try(u32 adr,u32 dat)
    {
        u32 a32[1];
        u32 d32[1];

        a32[0] = adr;
        d32[0] = dat;

        if(UpsWriteMemBuf32(a32,d32,SIZE(a32)) == false)
        {
            throw "Ошибка обмена c UPS.";
        }
        return;
    }
    //---------------------------------------------------------------------------
    __fastcall  void  ResetDeviceTry(void)
    {
        if(UpsResetDevice() == false)
        {
            throw "Ошибка обмена c UPS.";
        }
    }
};


#define RESET_DEVICE_GUI(caption,label) \
        FmLib->ResetDeviceGui(caption,label)

#define RESET_UPS_GUI(caption,label) \
        FmLib->ResetUpsGui(caption,label)

#define UPS_RESET_DEVICE() \
        FmLib->UpsResetDevice()

#define UPS_RESET(is_spl) \
        FmLib->UpsReset(is_spl)

#define UPS_SEND_SPI_BUF(buf,siz32) \
        FmLib->UpsSendSpiBuf(buf,siz32)

//    __inline bool UpsFlStartEraseSector(U32 addr8,I8 *is_start)
#define UPS_FL_START_ERASE_SECTOR(addr8,is_start) \
        FmLib->UpsFlStartEraseSector(addr8,is_start)

//    __inline bool FlIsCompleteEraseSector(I8* is_compl,I8 *is_err)
#define UPS_FL_IS_COMPLETE_ERASE_SECTOR(is_compl,is_err) \
        FmLib->UpsFlIsCompleteEraseSector(is_compl,is_err)

//    __inline bool FlReadBuffer8(U32 addr8,U32* buf8, U32 siz8, U32 *readen8)
#define UPS_FL_READ_BUFFER8(addr8,buf8,siz8,readen8) \
        FmLib->UpsFlReadBuffer8(addr8,buf8,siz8,readen8)

//    __inline bool FlWriteBuffer8(U32 addr8,U32* buf8, U32 siz8, U32 *written8)
#define UPS_FL_WRITE_BUFFER8(addr8,buf8,siz8,readen8) \
        FmLib->UpsFlWriteBuffer8(addr8,buf8,siz8,readen8)

#define UPS_SEND_KIO_PACKET(nk,buf) \
        FmLib->UpsSendKioPacket(nk,buf)

#define UPS_RECIV_KIO_PACKET(nk,buf) \
        FmLib->UpsRecivKioPacket(nk,buf)

#define UPS_SET_AND_WAIT_STATE(st) \
        FmLib->UpsSetAndWaitState(st)

#define UPS_SET_STATE(st,retst_pu32) \
        FmLib->UpsSetState(st,retst_pu32)

#define UPS_ATP_READ_DEVICE_ID(a2,did_pu32,is_ok_pi8) \
        FmLib->UpsAtpReadDeviceID(a2,did_pu32,is_ok_pi8)

#define UPS_ATP_START_ERASE_CHIP(a2,is_ok_pi8) \
        FmLib->UpsAtpStartEraseChip(a2,is_ok_pi8)

#define UPS_ATP_IS_COMPLETE_ERASE_CHIP(is_compl_pi8,is_err_pi8) \
        FmLib->UpsAtpIsCompleteEraseChip(is_compl_pi8,is_err_pi8)

#define UPS_ATP_WRITE_BUFFER16(a2,addr16,buf16_pu32,siz16,written16_pu32) \
        FmLib->UpsAtpWriteBuffer16(a2,addr16,buf16_pu32,siz16,written16_pu32)

#define UPS_ATP_READ_BUFFER16(a2,addr16,buf16_pu32,siz16,readen16_pu32) \
        FmLib->UpsAtpReadBuffer16(a2,addr16,buf16_pu32,siz16,readen16_pu32)

#define UPS_READ_MEMBUF32(abuf,dbuf,len) \
        FmLib->UpsReadMemBuf32(abuf,dbuf,len)

#define UPS_WRITE_MEMBUF32(abuf,dbuf,len) \
        FmLib->UpsWriteMemBuf32(abuf,dbuf,len)

#define KIO_GET_PRINT(nk,dst) \
        FmLib->KioGetPrint(nk,dst)

#define KIO_ERASE_FLASH_SECTOR(nk,dst,addr) \
        FmLib->KioEraseFlashSector(nk,dst,addr)

#define KIO_READ_FLASH(nk,dst,addr) \
        FmLib->KioReadFlash(nk,dst,addr)

#define KIO_WRITE_FLASH(nk,dst,addr,buf,siz16,err) \
        FmLib->KioWriteFlash(nk,dst,addr,buf,siz16,err)

#define KIO_IS_ERASED_FLASH_SECTOR(nk,compl,ok) \
        FmLib->KioIsErasedFlashSector(nk,compl,ok)

#define KIO_READ_MEMBUF32(nk,dst,abuf,dbuf,len) \
        FmLib->KioReadMemBuf32(nk,dst,abuf,dbuf,len)

#define KIO_WRITE_MEMBUF32(nk,dst,abuf,dbuf,len) \
        FmLib->KioWriteMemBuf32(nk,dst,abuf,dbuf,len)

#define KIO_READ_MEMBUF64(nk,dst,abuf,dbuf,len) \
        FmLib->KioReadMemBuf64(nk,dst,abuf,dbuf,len)

#define KIO_WRITE_MEMBUF64(nk,dst,abuf,dbuf,len) \
        FmLib->KioWriteMemBuf64(nk,dst,abuf,dbuf,len)

#define GET_KIO_VAL32_TRY(nk,a)     FmLib->GetKioVal32Try(nk,a)
#define PUT_KIO_VAL32_TRY(nk,a,d)   FmLib->PutKioVal32Try(nk,a,d)
#define GET_KIO_VAL64_TRY(nk,a)     FmLib->GetKioVal64Try(nk,a)
#define PUT_KIO_VAL64_TRY(nk,a,d)   FmLib->PutKioVal64Try(nk,a,d)
#define GET_UPS_VAL32_TRY(a)        FmLib->GetUpsVal32Try(a)
#define PUT_UPS_VAL32_TRY(a,d)      FmLib->PutUpsVal32Try(a,d)
#define RESET_DEVICE_TRY            FmLib->ResetDeviceTry
//---------------------------------------------------------------------------
extern PACKAGE TFmLib *FmLib;
/*
// Ставвится в конструкторе формы
#define RESTORE_FORM_VISIBLE \
        PostMessage(Handle,WMU_FORM_CREATE,0,0);\
        if(FmLib->ConfigIni->ReadBool(Name,Name+"_Visible",false)){\
            PostMessage(Handle,WMU_FORM_SHOW,0,0);\
        }
// Ставится внутри событий OnHide и OnShow
#define SAVE_FORM_VISIBLE \
        if(FmLib->IsFormClose == false){\
            FmLib->ConfigIni->WriteBool(Name,Name+"_Visible",Visible);\
        }


#define SAVE_FORM_STATE  SaveFormState(FmLib->ConfigIni,this)
#define LOAD_FORM_STATE  LoadFormState(FmLib->ConfigIni,this)
*/
#endif
