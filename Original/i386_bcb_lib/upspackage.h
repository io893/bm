#ifndef UPSPACKAGE_H
#define UPSPACKAGE_H
#include <vcl.h>
#include <extdefs.h>

typedef void __fastcall (__closure *TUpsErrorEvent)(System::TObject* Sender,DWORD ErrCode);
typedef bool __fastcall (__closure *TUpsQuery)(System::TObject* Sender,U32 param);
typedef void __fastcall (__closure *TUpsEvent)(System::TObject* Sender,U32 param);

//typedef void __fastcall (__closure *TErrorEvent)(System::TObject* Sender,DWORD ErrCode);


enum
{
    UPS_ERR_RLEN,                   // Размер принятого пакета не равен ожидаемому размеру
    UPS_ERR_NOT_UPS_DRIVER,         // Property UpsDriver   == NULL
    UPS_ERR_NOT_UPS_EXCHANGE,       // Property UpsExchange == NULL
};
#endif
