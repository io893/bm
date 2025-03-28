//---------------------------------------------------------------------------


#pragma hdrstop


#include "TFmLib.h"
#include "Arm.h"


#pragma package(smart_init)

void TForm1::ResetDev(void)
{
        RESET_UPS_GUI("����� ���",NULL);
        RESET_DEVICE_GUI("����� ����",NULL);
// ��� ??????
        UPS_RESET_DEVICE();
}


bool TForm1::PowOn(void)
{
Byte* AskDan;
Byte ERV_All;
Byte EK_All;
Byte TM3_0,TM3_1,TM2_0,TM2_1;
int trm;
Byte* DAN_US; //������ ��� ����������
bool err=false;
ResetDev();

if(PowOnOff==false)        //  ������� �� ��������
 {
  Packet_P_CO();   //????? ��������(�����) �������� � ������� �����  ????
  Vkl_IP(1,1,1,1);      // �������� �� ���� � ��� ��7 ONV2_0, ONV2_1 , ONV3_0, ONV3_1
  PaketFZD(2,AskDan) ; //����� FTS

//�������� ��� � �� ���� � ��7
EK_All=AskDan[1];
if(EK_All&0x1==1)
{
Application->MessageBox("������ ��� ��7 ���. 53 ���","��7", MB_ICONERROR| MB_OK);
err=true;
}
if((EK_All>>1)&0x1==1)
{
Application->MessageBox("������ ��� ��7 ���. 53 ���","��7", MB_ICONERROR| MB_OK);
err=true;
}
if((EK_All>>2)&0x1==1)
{
Application->MessageBox("������ ��� ��7 ���. 2 ���","��7", MB_ICONERROR| MB_OK);
err=true;
}
if((EK_All>>3)&0x1==1)
{
Application->MessageBox("������ ��� ��7 ���. 2 ���","��7", MB_ICONERROR| MB_OK);
err=true;
}

 ERV_All=AskDan[0];
if(ERV_All&0x1==1)
{
  Application->MessageBox("������������� ��� ��7 ���. 53 ���","��7", MB_ICONERROR| MB_OK);
  err=true;
}
if((ERV_All>>1)&0x1==1)
{
 Application->MessageBox("������������� ��� ��7 ���. 53 ���","��7", MB_ICONERROR| MB_OK);
 err=true;
}
if((ERV_All>>2)&0x1==1)
{
 Application->MessageBox("������������� ��� ��7 ���. 2 ���","��7", MB_ICONERROR| MB_OK);
err=true;
}
if((ERV_All>>3)&0x1==1)
{
 Application->MessageBox("������������� ��� ��7 ���. 2 ���","��7", MB_ICONERROR| MB_OK);
err=true;
}
if((ERV_All>>4)&0x1==1)
{
  Application->MessageBox("������������� ��� ����","����", MB_ICONERROR| MB_OK);
err=true;
}
  if(err==false)
   {
   // �������� ���������
   DAN_US[0]=0xff;// ��������� 1-8
   DAN_US[1]=0xff;// ��������� 9-13, ONVIP, EPRD-6, EPRM-7  ?
   PaketUP7_1(0, DAN_US);  //53 ���
   PaketUP7_1(1, DAN_US);  //53 ���
   PaketUP7_1(2, DAN_US);  //2 ���
   PaketUP7_1(3, DAN_US);  //2 ���
   OutAttOnOff(0xff) ;    // ? ������� ��� �������� �����������
 PaketFZD(2,AskDan) ; //����� FTS
 ERV_All=AskDan[0];
if(ERV_All&0x1==1)
{
  Application->MessageBox("������������� ��� ��7 ���. 53 ���","��7 �������� ��������� ��������", MB_ICONERROR| MB_OK);
  err=true;
}
if((ERV_All>>1)&0x1==1)
{
 Application->MessageBox("������������� ��� ��7 ���. 53 ���","��7 �������� ��������� ��������", MB_ICONERROR| MB_OK);
 err=true;
}
if((ERV_All>>2)&0x1==1)
{
 Application->MessageBox("������������� ��� ��7 ���. 2 ���","��7 �������� ��������� ��������", MB_ICONERROR| MB_OK);
err=true;
}
if((ERV_All>>3)&0x1==1)
{
 Application->MessageBox("������������� ��� ��7 ���. 2 ���","��7 �������� ��������� ��������", MB_ICONERROR| MB_OK);
err=true;
}
if((ERV_All>>4)&0x1==1)
{
  Application->MessageBox("������������� ��� ����","���� �������� ��������� ��������", MB_ICONERROR| MB_OK);
err=true;
}
//��������� ����������� ����������
TM3_0=AskDan[2];
if(TM3_0==0x80)
Application->MessageBox("��� ������ � ����������� ��� ������ 53", "����", MB_ICONINFORMATION|MB_OK);
else
if(TM3_0>>7==0x1)
   trm=-(~(TM2_1-0x1));
else
  trm=TM3_0;
if((trm<-60)||(trm>60))
{
DAN_US[0]=0x0;// ��������� 1-8
DAN_US[1]=0x0;// ��������� 9-13, ONVIP, EPRD-6, EPRM-7  ?
PaketUP7_1(0, DAN_US);  //53 ���
Application->MessageBox("����������� ���������� ��� ������ 53\n �� ����������� ���������",
                          "�������� ��������� ���������", MB_ICONERROR| MB_OK);
err=true;
}

TM3_1=AskDan[3];
if(TM3_1==0x80)
Application->MessageBox("��� ������ � ����������� ��� ������ 53", "����", MB_ICONINFORMATION|MB_OK);
else
if(TM3_1>>7==0x1)
   trm=-(~(TM2_1-0x1));
else
  trm=TM3_1;
if((trm<-60)||(trm>60))
{
DAN_US[0]=0x0;// ��������� 1-8
DAN_US[1]=0x0;// ��������� 9-13, ONVIP, EPRD-6, EPRM-7  ?
PaketUP7_1(1, DAN_US);  //53 ���
Application->MessageBox("����������� ���������� ��� ������ 53\n �� ����������� ���������",
                          "�������� ��������� ���������", MB_ICONERROR| MB_OK);
err=true;
}

TM2_0=AskDan[4];
if(TM2_0==0x80)
Application->MessageBox("��� ������ � ����������� ��� ������ 53", "����", MB_ICONINFORMATION|MB_OK);
else
if(TM2_0>>7==0x1)
   trm=-(~(TM2_1-0x1));
else
  trm=TM2_0;
if((trm<-60)||(trm>60))
{
DAN_US[0]=0x0;// ��������� 1-8
DAN_US[1]=0x0;// ��������� 9-13, ONVIP, EPRD-6, EPRM-7  ?
PaketUP7_1(2, DAN_US);  //2 ���
Application->MessageBox("����������� ���������� ��� ������ 2\n �� ����������� ���������",
                          "�������� ��������� ���������", MB_ICONERROR| MB_OK);
err=true;
}

TM2_1=AskDan[4];
if(TM2_1==0x80)
Application->MessageBox("��� ������ � ����������� ��� ������ 2", "����", MB_ICONINFORMATION|MB_OK);
else
if(TM2_1>>7==0x1)
   trm=-(~(TM2_1-0x1));
else
  trm=TM2_1;
if((trm<-60)||(trm>60))
{
DAN_US[0]=0x0;// ��������� 1-8
DAN_US[1]=0x0;// ��������� 9-13, ONVIP, EPRD-6, EPRM-7  ?
PaketUP7_1(3, DAN_US);  //2 ���
Application->MessageBox("����������� ���������� ��� ������ 2\n �� ����������� ���������",
                          "�������� ��������� ���������", MB_ICONERROR| MB_OK);
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
  Vkl_IP(0,0,0,0);      // ��������� �� ���� � ��� ��7 ONV2_0, ONV2_1 , ONV3_0, ONV3_1
  return false;
}
 } // if(PowOnOff==false)
return true; //��������� ���� ��������  �����
}


