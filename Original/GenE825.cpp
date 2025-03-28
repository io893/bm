//---------------------------------------------------------------------------


#pragma hdrstop

#include "ARM.h"

#include <vcl.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)


bool TForm1::WrGenE825(AnsiString St)
{
AnsiString CGen;
ViUInt32	retCnt;


CGen=":FREQ "+St+"MHz\n";
status = viWrite(viG, (ViBuf)CGen.c_str(),CGen.Length(), &retCnt);
       if (status < VI_SUCCESS)
        {
        viClose(viG);

        ShowMessage("Ошибка обращения к генератору E8257D");
        return false;
        }

          CGen="OUTP:STAT ON\n";
    status = viWrite(viG, (ViBuf)CGen.c_str(),CGen.Length(), &retCnt);
 
     return true;
}


bool TForm1::WrGenE825(AnsiString St,AnsiString SPg)
{
AnsiString CGen;
ViUInt32	retCnt;

CGen=":FREQ "+St+"MHz\n";
  status = viWrite(viG, (ViBuf)CGen.c_str(),CGen.Length(), &retCnt);
       if (status < VI_SUCCESS)
        {
        viClose(viG);
        ShowMessage("Ошибка обращения к генератору E8257D");
        return false;
        }
         //
         Sleep(10);
          CGen="POW:AMPL "+SPg+"dBm\n";   //установить  мощность
          status = viWrite(viG, (ViBuf)CGen.c_str(),CGen.Length(), &retCnt);

          CGen="OUTP:STAT ON\n";
          status = viWrite(viG, (ViBuf)CGen.c_str(),CGen.Length(), &retCnt);



     return true;
}


bool TForm1::InitE825(AnsiString SPg)
{
AnsiString S;
ViUInt32   retCnt;

         //  S="*RST\n";
         //  status = viPrintf(viG, S.c_str());
           S="*CLS";
           status = viWrite(viG, (ViBuf)S.c_str(),S.Length(), &retCnt);
           S="OUTP:STAT OFF\n";
          status = viWrite(viG, (ViBuf)S.c_str(),S.Length(), &retCnt);

          S="OUTP:MOD:STATE OFF\n"; // отключить модуляцию
          status = viWrite(viG, (ViBuf)S.c_str(),S.Length(), &retCnt);

          S="POW:AMPL "+SPg+"dBm\n";   //установить постоянную мощность
          status = viWrite(viG, (ViBuf)S.c_str(),S.Length(), &retCnt);


        return true;
}

bool TForm1::OfGenE825(void)
{
AnsiString S;
ViUInt32   retCnt;
S="OUTP:STAT OFF\n";
          status = viWrite(viG, (ViBuf)S.c_str(),S.Length(), &retCnt);
          if (status < VI_SUCCESS)
        {
        viClose(viG);
        ShowMessage("Ошибка обращения к генератору E8257D");
        return false;
        }
if(!ModGenE825off())
return false;

 return true;
}

void TForm1:: CorrStrGen(AnsiString &SPg)
{
int pos;
 pos=SPg.Pos(",");
if(pos!=0)
{
SPg.Delete(pos,1);
SPg.Insert(".",pos);
}
}

bool TForm1::ModGenE825(float per, float rang )
{
//AnsiString CGen;
//ViUInt32   retCnt;


if(viPrintf(viG, "POW:ALC OFF\n")<VI_SUCCESS){
        viClose(viG);
        ShowMessage("Ошибка обращения к генератору E8257D");
        return false;
        }
if(viPrintf(viG, "PULM:INT:PER %f uS\n", per)<VI_SUCCESS){
        viClose(viG);
        ShowMessage("Ошибка обращения к генератору E8257D");
        return false; }

if(viPrintf(viG, "PULM:INT:PWID %f uS\n", rang)< VI_SUCCESS){
        viClose(viG);
        ShowMessage("Ошибка обращения к генератору E8257D");
        return false;}
if(viPrintf(viG, "PULM:STAT ON\n")<VI_SUCCESS){
        viClose(viG);
        ShowMessage("Ошибка обращения к генератору E8257D");
        return false;}

return true;

/*  if (AglErr(viPrintf(gnr_sig, "POW:ALC OFF\n"), gnr_sig, "Ошибка при отключении автоматической коррекции уровня (ALC)"))
         return false;   if (AglErr(viPrintf(gnr_sig, "PULM:INT:PER %f uS\n", T), gnr_sig, "Ошибка при установке периода модуляции генератора Сигнала"))      return false;
   if (AglErr(viPrintf(gnr_sig, "PULM:INT:PWID %f uS\n", tau), gnr_sig, "Ошибка при установке длительности импульса модуляции генератора Сигнала"))      return false;
   if (AglErr(viPrintf(gnr_sig, "PULM:STAT ON\n"), gnr_sig, "Ошибка при включении модулятора генератора Сигнала"))
      return false;

   return true;  */
}

bool TForm1::ModGenE825off(void )
{
if(viPrintf(viG, "PULM:STAT OFF\n")<VI_SUCCESS){
        viClose(viG);
        ShowMessage("Ошибка обращения к генератору E8257D");
        return false;}
else return true;
}
