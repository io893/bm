#include "smsd_com.h"
//#include "ARM.h"
/*class SmsdCom{
private:
   HANDLE hCom;
public:
   SmsdCom(){hCom = NULL;}
   ~SmsdCom(){if (hCom != NULL) CloseCom();}
   bool OpenCom(char *com_num);
   bool CloseCom();
   DWORD WriteCom(char* buf, int len);
   DWORD WriteComChar(char b);
   int ReadCom(char *buf, int len);
   char ReadComChar();
};*/

//---------------------------------------------------------------------------
bool SmsdCom::OpenCom(char *com_num)
{
DCB dcb;
COMMTIMEOUTS ct;
if (!com_num)
      return false;
hCom = CreateFile(com_num, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
if (hCom == INVALID_HANDLE_VALUE)
      return false;
if (!SetupComm(hCom, 4096, 4096))
      return false;
if (!GetCommState(hCom, &dcb))
      return false;

dcb.BaudRate = 9600;
((DWORD*)(&dcb))[2] = 0x1001;  // set port properties for TXDI + no flow-control
dcb.ByteSize = 8;
dcb.Parity = EVENPARITY;
dcb.StopBits = 0;
if (!SetCommState(hCom, &dcb))
      return false;

// set the timeouts to 0
ct.ReadIntervalTimeout = MAXDWORD;
ct.ReadTotalTimeoutMultiplier = 0;
ct.ReadTotalTimeoutConstant = 0;
ct.WriteTotalTimeoutMultiplier = 0;
ct.WriteTotalTimeoutConstant = 0;
if (!SetCommTimeouts(hCom, &ct))
      return false;

   return true;
}
//---------------------------------------------------------------------------
bool SmsdCom::CloseCom()
{
bool b = CloseHandle(hCom);
   if (b)
      hCom = NULL;
   return b;
}
//---------------------------------------------------------------------------
DWORD SmsdCom::WriteCom(char* buf, int len)
{
DWORD nSend = 0;
if (!WriteFile(hCom, buf, len, &nSend, NULL))
      return 0;

return nSend;
}
//---------------------------------------------------------------------------
DWORD SmsdCom::WriteComChar(char b)
{
return WriteCom(&b, 1);
}
//---------------------------------------------------------------------------
int SmsdCom::ReadCom(char *buf, int len)
{
DWORD nRec = 0;
if (!ReadFile(hCom, buf, len, &nRec, NULL))
      return 0;

return (int)nRec;
}
//---------------------------------------------------------------------------
char SmsdCom::ReadComChar()
{
DWORD nRec;
char c;
if (!ReadFile(hCom, &c, 1, &nRec, NULL))
      return 0;

return nRec ? c : 0;
}
//---------------------------------------------------------------------------