//---------------------------------------------------------------------------


#pragma hdrstop

#include "ARM.h"
#include <math.h>
#include "visa.h"
#include <vcl.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)
 bool TForm1::Init1911A(AnsiString UnP)
{
  AnsiString S,SPow;
  ViUInt32   retCnt;
  ViChar buffer[200];
         S="*CLS\n";
       status = viPrintf(viP, S.c_str());

          S="UNIT:POW "+UnP;     //DBM\n" ;
         status= viWrite(viP, (ViBuf)S.c_str(),S.Length(), &retCnt);
         dl=true;

         if (status < VI_SUCCESS)
          {
           viClose(viP);

           ShowMessage("Ошибка обращения к измерителю мощности");
           return false;
          }
          return true;
}

float TForm1::StepRdPow(void)
{
AnsiString S,SPow,St;
Word CFr,CGn;
float Pw;
 int a;
ViUInt32   retCnt;
ViChar buffer[200];
 long longdown=0;


S="ABORT\n";
status = viWrite(viP, (ViBuf)S.c_str(),S.Length(), &retCnt);
S="INIT:CONT ON\n";      //S="TRIG:SOUR:IMM\n";
status = viWrite(viP, (ViBuf)S.c_str(),S.Length(), &retCnt);

if(dl==true)
{
Sleep(1000);  //3000
dl=false;
}
S="FETC:POW:AC?\n" ;
status = viWrite(viP, (ViBuf)S.c_str(),S.Length(), &retCnt);
status = viRead(viP, (ViBuf)buffer, sizeof(buffer), &retCnt);

  if (status < VI_SUCCESS)
          {
           viClose(viP);
           ShowMessage("Ошибка обращения к измерителю мощности");
           return 0;
          }
S=AnsiString(buffer, retCnt-1);
Pw=ConvStr(S);//StrToFloat(S);

S="*OPC?\n";
          status = viWrite(viP, (ViBuf)S.c_str(),S.Length(), &retCnt);

        while(!longdown)
   viScanf(viP,"%d", &longdown);



return Pw;
}


void TForm1::CalPm(void)
{
 AnsiString S ;
 ViUInt32   retCnt;
 long longdown=0;
 Panel6->Visible=true;
 Label8->Caption="Калибровка измерителя мощности";
 Label8->Repaint();


  OfGenE825();

  S="CAL:ZERO:AUTO ONCE\n";
  status= viWrite(viP, (ViBuf)S.c_str(),S.Length(), &retCnt);

    S="*OPC?\n";
          status = viWrite(viP, (ViBuf)S.c_str(),S.Length(), &retCnt);

while(!longdown)
viScanf(viP,"%d", &longdown);


 Panel6->Visible=false;
   ClbPwm=true;
}
//---------------------------------------------------------------------------



float TForm1::ConvStr(AnsiString S)
{
int pos;
 AnsiString Bas, Mant;
 float Pdbm;
 float Pt;
 int m;
pos=S.Pos("E");
if(pos!=0)
{
Bas=S.SubString(1,pos-1);
Mant=S.SubString(pos+1,S.Length()-pos);
}
//pos=Bas.Pos(".");
//Bas.Delete(pos,1);
//Bas.Insert(",",pos);

Pt=StrToFloat(Bas);
m=StrToInt(Mant);
Pdbm=Pt*pow(10,m);
return Pdbm;
}


