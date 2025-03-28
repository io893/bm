//-----------------------------------------------------------------------------

#ifndef TConverterH
#define TConverterH
//-----------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <extdefs.h>
#include <upspackage.h>

//-----------------------------------------------------------------------------
// 
typedef bool __fastcall (__closure *TOnConverted)(  TObject* Sender,
                                                    UCHAR* buf,
                                                    U32 len
                                                  );
typedef bool __fastcall (__closure *TOnBeforeSend)(TObject* Sender);
typedef bool __fastcall (__closure *TOnSendBuf)   (TObject* Sender,UCHAR* buf,U32 len,U32 percent);
typedef bool __fastcall (__closure *TOnAfterSend) (System::TObject* Sender);

#define ERR_HEX6X_NOT_FOUND     1
#define ERR_CVTFILE_NOT_FOUND   2
#define ERR_DEL_TMP_FILE        3
#define ERR_OUT_FILE_FMT        4
#define ERR_HEX3X_NOT_FOUND     5




#define VC33F8  0
#define VC33F16 1
#define VC33SL  2

class PACKAGE TConverter : public TComponent
{
private:
    TOnConverted    FOnConverted;
    TOnBeforeSend   FOnBeforeSend;
    TOnSendBuf      FOnSendBuf;
    TOnAfterSend    FOnAfterSend;
    TUpsErrorEvent  FOnError;


    U32             FMaxLenSendBuf;
    U32             FBeginReserve;
    U32             FEndReserve;

protected:
    bool ConvertOutVC33File(char *fname,int mode);

public:
    __fastcall TConverter(TComponent* Owner);

    bool ConvertOut6xFile(char *fname);
    bool ConvertMcsFile  (char *fname);
    inline bool ConvertOutVC33SLFile(char *fname)
    {
        return ConvertOutVC33File(fname,VC33SL);
    }
    inline bool ConvertOutVC33F8File(char *fname)
    {
        return ConvertOutVC33File(fname,VC33F8);
    }
    inline bool ConvertOutVC33F16File(char *fname)
    {
        return ConvertOutVC33File(fname,VC33F16);
    }

__published:
    //-------------------------------------------------------------------------
    // Вызов после конвертации(успешной)
    // Если вернёт false дальнейшие дествия будут прекращены
    //-------------------------------------------------------------------------
    __property TOnConverted OnConverted  =  {
                                                read  = FOnConverted,
                                                write = FOnConverted
                                            };

    //-------------------------------------------------------------------------
    // Вызов перед процессом передачи
    // Если вернёт false дальнейшие дествия будут прекращены
    //-------------------------------------------------------------------------
    __property TOnBeforeSend OnBeforeSend = {
                                                read  = FOnBeforeSend,
                                                write = FOnBeforeSend
                                            };

    //-------------------------------------------------------------------------
    // Вызов для передачи буфера
    // Если вернёт false дальнейшие дествия будут прекращены
    //-------------------------------------------------------------------------
    __property TOnSendBuf OnSendBuf =       {
                                                read  = FOnSendBuf,
                                                write = FOnSendBuf
                                            };

    //-------------------------------------------------------------------------
    // Вызов после процесса передачи буфера
    // Если вернёт false дальнейшие дествия будут прекращены
    //-------------------------------------------------------------------------
    __property TOnAfterSend OnAfterSend =   {
                                                read  = FOnAfterSend,
                                                write = FOnAfterSend
                                            };

    //-------------------------------------------------------------------------
    // Максимальная длинна буфера при вызове OnSendBuf
    //-------------------------------------------------------------------------
    __property U32 MaxLenSendBuf        =  {
                                                read  = FMaxLenSendBuf,
                                                write = FMaxLenSendBuf,
                                                default = 256
                                            };

    //-------------------------------------------------------------------------
    // Количество байт зарезервированных в начале буфера
    //-------------------------------------------------------------------------
    __property U32 BeginReserve         =  {
                                                read  = FBeginReserve,
                                                write = FBeginReserve,
                                                default = 0
                                            };
    //-------------------------------------------------------------------------
    // Количество байт зарезервированных в конце буфера
    //-------------------------------------------------------------------------
    __property U32 EndReserve         =  {
                                                read  = FEndReserve,
                                                write = FEndReserve,
                                                default = 0
                                            };

    __property TUpsErrorEvent OnError      = { read  = FOnError,
                                               write = FOnError      };


};
//---------------------------------------------------------------------------
#endif
