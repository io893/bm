#include "ARM.h"
//#include "FtDevice.h"
  /* 27/06.2011 */
  DWORD RxBytes;
  DWORD EventDWord;
  DWORD TxBytes;
  DWORD BytesReceived;

  FT_PROGRAM_DATA ftData = {
  0x00000000, // Header - must be 0x00000000
  0xFFFFFFFF, // Header - must be 0xffffffff
  0x00000000, // Header - FT_PROGRAM_DATA version - set by dll
  0x0403, // VID
  0x6001, // PID
  "FTDI", // Manufacturer
  "FT", // Manufacturer ID
  //"USB HS Serial Converter", // Description
  "USB - PLATA1", // Description
   "FT000001", // Serial Number
   44, // MaxPower
   1, // PnP
   0, // SelfPowered
   1, // RemoteWakeup
   1, // non-zero if Rev4 chip, zero otherwise
   0, // non-zero if in endpoint is isochronous
   0, // non-zero if out endpoint is isochronous
   0, // non-zero if pull down enabled
   1, // non-zero if serial number to be used
   0, // non-zero if chip uses USBVersion
   0x0110 // BCD (0x0200 => USB2)
   };
//---------------------------------------------------------------------------
int CFtDevice::Start(char *descr)
{
 //  Stop();
   if (fthnd){ FT_Close(fthnd);  fthnd = NULL;}
     if (strcmp(descr, "") == 0)
      for (int i = 0; i < MAX_DEV_COUNT; i++){
         ftStatus = FT_Open(i, &fthnd);
         if (ftStatus == FT_OK)
            break;
      }
   else
      ftStatus = FT_OpenEx(descr, FT_OPEN_BY_DESCRIPTION, &fthnd);
   if (ftStatus != FT_OK)
      return ftStatus;
   FT_SetTimeouts(fthnd, TIME_READ, TIME_WRITE); //30(read),15(write)-работает
   ftStatus = FT_SetLatencyTimer(fthnd, TIME_WAIT); //1mls-read
   if (ftStatus != FT_OK)
      return ftStatus;
   FT_ResetDevice(fthnd);
   ftStatus = FT_Purge(fthnd, FT_PURGE_RX | FT_PURGE_TX);
   if (ftStatus != FT_OK)
      return ftStatus;
   return FT_OK;
}
//---------------------------------------------------------------------------
//void CFtDevice::Stop()
//{
//   if (fthnd){
//      FT_Close(fthnd);
//      fthnd = NULL;
//     }
//}
//---------------------------------------------------------------------------
int CFtDevice::ResetP(void)
{
   if (fthnd)
      FT_ResetDevice(fthnd);
   ftStatus = FT_Purge(fthnd, FT_PURGE_RX | FT_PURGE_TX);
   if (ftStatus != FT_OK)
      return ftStatus;
   return FT_OK;
}
//---------------------------------------------------------------------------
int CFtDevice::Write(char *buf, int size)
{
   DWORD sz = 0;
   ftStatus = FT_Write(fthnd, buf, (DWORD)size, &sz);
   if (ftStatus != FT_OK)
      return ftStatus;
   if (sz != (DWORD)size)
      return FT_OTHER_ERROR;
   return FT_OK;
}
//---------------------------------------------------------------------------
int CFtDevice::Read(char *buf, int size, int *sz_readed)
{
   DWORD i, sizi = 0;
   for (i = 0; i < 2; i++){
      ftStatus = FT_Read(fthnd, &buf[sizi], (DWORD)size-sizi, (DWORD*)sz_readed);
      if (ftStatus != FT_OK)
         return ftStatus;
      sizi += *sz_readed;
      if (sizi == (DWORD)size)
         break;
   }
   *sz_readed = sizi;
   return FT_OK;
}
//---------------------------------------------------------------------------
int CFtDevice::GetStatus(int *rx_bytes, int *tx_bytes)
{
   DWORD event_dword, rxb, txb;
   if (!rx_bytes && !tx_bytes)
      return FT_OTHER_ERROR;
   if (!rx_bytes)
     rx_bytes = (int*)&rxb;
   if (!tx_bytes)
     tx_bytes = (int*)&txb;
   ftStatus = FT_GetStatus(fthnd, (DWORD*)rx_bytes, (DWORD*)tx_bytes, &event_dword);
   if (ftStatus != FT_OK)
      return ftStatus;
   return FT_OK;
}
//---------------------------------------------------------------------------
DWORD CFtDevice::Get_FtStatus()
{
   FT_GetStatus(fthnd,&RxBytes,&TxBytes,&EventDWord);
   return(RxBytes);
 }

//----------------------------------------------------------------------------
int  CFtDevice::WtProgr(void)
{
 //FtStop();
  ftStatus = FT_Open(0,&fthnd);
  if (ftStatus == FT_OK)
   {
    ftStatus = FT_EE_Program(fthnd, &ftData);
  if (ftStatus == FT_OK)
   {
 // FT_EE_Program OK!
    return(0);
    }
   else
   {
// FT_EE_Program FAILED!
   return(ftStatus);
   }
 }
 return(ftStatus);
}
