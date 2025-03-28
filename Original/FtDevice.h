#include <windows.h>
#include <string.h>
#include "Ftd2xx.h"
//#include "ARM.h"
//---------------------------------------------------------------------------
#define TIME_READ     1    // FT_SetTimeouts
#define TIME_WRITE    30   // FT_SetTimeouts
#define TIME_WAIT     1    // FT_SetLatencyTimer (1-255)
#define MAX_DEV_COUNT 2
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CFtDevice{
private:
   FT_STATUS ftStatus;
   FT_HANDLE fthnd;
public:
   CFtDevice(){fthnd = NULL;}
   //~CFtDevice(){ if (fthnd) Stop();}
    ~CFtDevice(){ if (fthnd) FT_Close(fthnd); fthnd = NULL;}
   int Start(char *descr);
   //void Stop();
   int ResetP(void);
   int Write(char *buf, int size);
   int Read(char *buf, int size, int *sz_readed);
   int GetStatus(int *rx_bytes, int *tx_bytes);
   DWORD Get_FtStatus(void);
   int WtProgr(void);
   };
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma package(smart_init)