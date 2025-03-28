//---------------------------------------------------------------------------


#pragma hdrstop


#include "TFmLib.h"
#include "Arm.h"


#pragma package(smart_init)

void TForm1::ResetDev(void)
{
        RESET_UPS_GUI("Сброс УПС",NULL);
        RESET_DEVICE_GUI("Сброс УППУ",NULL);
// или ??????
        UPS_RESET_DEVICE();
}


bool TForm1::PowOn(void)
{
Byte* AskDan;
Byte ERV_All;
Byte EK_All;
Byte TM3_0,TM3_1,TM2_0,TM2_1;
int trm;
Byte* DAN_US; //данные для усилителей
bool err=false;
ResetDev();

if(PowOnOff==false)        //  питание не включено
 {
  Packet_P_CO();   //????? Формуляр(пакет) перехода в штатный режим  ????
  Vkl_IP(1,1,1,1);      // включить ИП УППУ и все УП7 ONV2_0, ONV2_1 , ONV3_0, ONV3_1
  PaketFZD(2,AskDan) ; //запрс FTS

//Проверка КИО и ИП УППУ и УП7
EK_All=AskDan[1];
if(EK_All&0x1==1)
{
Application->MessageBox("Ошибка КИО УП7 лит. 53 ППС","УП7", MB_ICONERROR| MB_OK);
err=true;
}
if((EK_All>>1)&0x1==1)
{
Application->MessageBox("Ошибка КИО УП7 лит. 53 ЗПС","УП7", MB_ICONERROR| MB_OK);
err=true;
}
if((EK_All>>2)&0x1==1)
{
Application->MessageBox("Ошибка КИО УП7 лит. 2 ППС","УП7", MB_ICONERROR| MB_OK);
err=true;
}
if((EK_All>>3)&0x1==1)
{
Application->MessageBox("Ошибка КИО УП7 лит. 2 ЗПС","УП7", MB_ICONERROR| MB_OK);
err=true;
}

 ERV_All=AskDan[0];
if(ERV_All&0x1==1)
{
  Application->MessageBox("Неисправность ВИП УП7 лит. 53 ППС","УП7", MB_ICONERROR| MB_OK);
  err=true;
}
if((ERV_All>>1)&0x1==1)
{
 Application->MessageBox("Неисправность ВИП УП7 лит. 53 ЗПС","УП7", MB_ICONERROR| MB_OK);
 err=true;
}
if((ERV_All>>2)&0x1==1)
{
 Application->MessageBox("Неисправность ВИП УП7 лит. 2 ППС","УП7", MB_ICONERROR| MB_OK);
err=true;
}
if((ERV_All>>3)&0x1==1)
{
 Application->MessageBox("Неисправность ВИП УП7 лит. 2 ЗПС","УП7", MB_ICONERROR| MB_OK);
err=true;
}
if((ERV_All>>4)&0x1==1)
{
  Application->MessageBox("Неисправность ВИП УППУ","УППУ", MB_ICONERROR| MB_OK);
err=true;
}
  if(err==false)
   {
   // Включаем усилители
   DAN_US[0]=0xff;// усилитель 1-8
   DAN_US[1]=0xff;// усилитель 9-13, ONVIP, EPRD-6, EPRM-7  ?
   PaketUP7_1(0, DAN_US);  //53 ППС
   PaketUP7_1(1, DAN_US);  //53 ЗПС
   PaketUP7_1(2, DAN_US);  //2 ППС
   PaketUP7_1(3, DAN_US);  //2 ЗПС
   OutAttOnOff(0xff) ;    // ? закрыть все выходные аттенюаторы
 PaketFZD(2,AskDan) ; //запрс FTS
 ERV_All=AskDan[0];
if(ERV_All&0x1==1)
{
  Application->MessageBox("Неисправность ВИП УП7 лит. 53 ППС","УП7 Выходные усилители включены", MB_ICONERROR| MB_OK);
  err=true;
}
if((ERV_All>>1)&0x1==1)
{
 Application->MessageBox("Неисправность ВИП УП7 лит. 53 ЗПС","УП7 Выходные усилители включены", MB_ICONERROR| MB_OK);
 err=true;
}
if((ERV_All>>2)&0x1==1)
{
 Application->MessageBox("Неисправность ВИП УП7 лит. 2 ППС","УП7 Выходные усилители включены", MB_ICONERROR| MB_OK);
err=true;
}
if((ERV_All>>3)&0x1==1)
{
 Application->MessageBox("Неисправность ВИП УП7 лит. 2 ЗПС","УП7 Выходные усилители включены", MB_ICONERROR| MB_OK);
err=true;
}
if((ERV_All>>4)&0x1==1)
{
  Application->MessageBox("Неисправность ВИП УППУ","УППУ Выходные усилители включены", MB_ICONERROR| MB_OK);
err=true;
}
//Проверяем температуру усилителей
TM3_0=AskDan[2];
if(TM3_0==0x80)
Application->MessageBox("Нет данных о температуре ППС литеры 53", "УППУ", MB_ICONINFORMATION|MB_OK);
else
if(TM3_0>>7==0x1)
   trm=-(~(TM2_1-0x1));
else
  trm=TM3_0;
if((trm<-60)||(trm>60))
{
DAN_US[0]=0x0;// усилитель 1-8
DAN_US[1]=0x0;// усилитель 9-13, ONVIP, EPRD-6, EPRM-7  ?
PaketUP7_1(0, DAN_US);  //53 ППС
Application->MessageBox("Температура усилителей ППС литеры 53\n за допустимыми границами",
                          "Выходные усилители выключены", MB_ICONERROR| MB_OK);
err=true;
}

TM3_1=AskDan[3];
if(TM3_1==0x80)
Application->MessageBox("Нет данных о температуре ЗПС литеры 53", "УППУ", MB_ICONINFORMATION|MB_OK);
else
if(TM3_1>>7==0x1)
   trm=-(~(TM2_1-0x1));
else
  trm=TM3_1;
if((trm<-60)||(trm>60))
{
DAN_US[0]=0x0;// усилитель 1-8
DAN_US[1]=0x0;// усилитель 9-13, ONVIP, EPRD-6, EPRM-7  ?
PaketUP7_1(1, DAN_US);  //53 ЗПС
Application->MessageBox("Температура усилителей ЗПС литеры 53\n за допустимыми границами",
                          "Выходные усилители выключены", MB_ICONERROR| MB_OK);
err=true;
}

TM2_0=AskDan[4];
if(TM2_0==0x80)
Application->MessageBox("Нет данных о температуре ЗПС литеры 53", "УППУ", MB_ICONINFORMATION|MB_OK);
else
if(TM2_0>>7==0x1)
   trm=-(~(TM2_1-0x1));
else
  trm=TM2_0;
if((trm<-60)||(trm>60))
{
DAN_US[0]=0x0;// усилитель 1-8
DAN_US[1]=0x0;// усилитель 9-13, ONVIP, EPRD-6, EPRM-7  ?
PaketUP7_1(2, DAN_US);  //2 ППС
Application->MessageBox("Температура усилителей ППС литеры 2\n за допустимыми границами",
                          "Выходные усилители выключены", MB_ICONERROR| MB_OK);
err=true;
}

TM2_1=AskDan[4];
if(TM2_1==0x80)
Application->MessageBox("Нет данных о температуре ЗПС литеры 2", "УППУ", MB_ICONINFORMATION|MB_OK);
else
if(TM2_1>>7==0x1)
   trm=-(~(TM2_1-0x1));
else
  trm=TM2_1;
if((trm<-60)||(trm>60))
{
DAN_US[0]=0x0;// усилитель 1-8
DAN_US[1]=0x0;// усилитель 9-13, ONVIP, EPRD-6, EPRM-7  ?
PaketUP7_1(3, DAN_US);  //2 ППС
Application->MessageBox("Температура усилителей ППС литеры 2\n за допустимыми границами",
                          "Выходные усилители выключены", MB_ICONERROR| MB_OK);
err=true;
}

   } //err=false
if(err==false)
{
 PowOnOff==true ;
 return true;
}
else
{
  Vkl_IP(0,0,0,0);      // выключить ИП УППУ и все УП7 ONV2_0, ONV2_1 , ONV3_0, ONV3_1
  return false;
}
 } // if(PowOnOff==false)
return true; //источники были включены  ранее
}


