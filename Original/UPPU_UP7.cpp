//---------------------------------------------------------------------------


#pragma hdrstop

#include "ARM.h"
#include <math.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool TForm1::PaketUP7_1(Byte ADR_UP7,Byte DATA_UP7[],U32 data_wr)
{

 int nk=1;
Byte dan;
U32 addr_wr,addr_rd,data_rd;
int ret;
Byte LEN=8;
Byte IPK=0xff;//��������� �����
Byte DST=0x7;
Byte SRC=0;
Byte IPS=0x21;
Byte IPK_UP7=0x1;
Byte IPS_Answ=0x22;
int j;
int i;
bool resl=false,res;
union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   : 8,
                 byte5   : 8,
                 byte6   : 8,
                 byte7   : 8;
            } p;
      U32 buf[256/4];
     }  packet;

packet.p.len=LEN;
packet.p.byte1=IPK;
packet.p.byte2=(SRC&0x1F)|(DST<<5);
packet.p.byte3=IPS<<2;
packet.p.byte4=ADR_UP7;
packet.p.byte5=IPK_UP7;
packet.p.byte6=DATA_UP7[0];
packet.p.byte7=DATA_UP7[1];

     for(i=0;i<10;i++)
        {
        if(UPS_SEND_KIO_PACKET (nk,packet.buf) == true)
         {
         resl=true;
         break;
         }
        }//for i

      if(resl==false)
         {
          Application->MessageBox("������ �������� ������ 1 � ��7!","����", MB_ICONERROR| MB_OK);
          return false; //  ������ �� ������
         }

  /* ����� ��������� ������ */

else
  res=PaketAnsw(IPS_Answ);

  if(res){
addr_wr=0x10002f;
addr_rd=0x100030;

if(!PaketP_WRA(addr_wr, data_wr )){
 Application->MessageBox("������ ��� ������ ������ � ����!","��������� ��������������� ����������", MB_ICONERROR| MB_OK);
return false;}
MyTimer(300);

if(!PaketP_RDA(addr_rd, data_rd )){
Application->MessageBox("������ ��� ������ ������ �� ����!","��������� ��������������� ����������", MB_ICONERROR| MB_OK);
return false;}

//if(data_wr!=(data_rd&0x1)){
//Application->MessageBox("������ � ������� ��������������� ���������� �� ���������","��������� ��������������� ����������", MB_ICONERROR| MB_OK);
//return false;}
} //res

return res;
}

bool TForm1::PaketUP7_2(Byte ADR_UP7,Byte DATA_UP7[])
{
  int nk=1;
Byte dan;
Byte LEN=9;
Byte IPK=0xff;//��������� �����
Byte SRC=0;
Byte DST=0x7;
Byte IPS=0x21;
Byte IPK_UP7=0x2;
Byte  IPS_Answ=0x22;
int ret,j,i;
bool res;
union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   : 8,
                 byte5   : 8,
                 byte6   : 8,
                 byte7   : 8,
                 byte8   : 8;
            } p;
      U32 buf[256/4];
     }  packet;

packet.p.len=LEN;
packet.p.byte1=IPK;
packet.p.byte2=(SRC&0x1F)|(DST<<5);
packet.p.byte3=(IPS<<2);
packet.p.byte4=ADR_UP7;
packet.p.byte5=IPK_UP7;
packet.p.byte6=DATA_UP7[0];
packet.p.byte7=DATA_UP7[1];
packet.p.byte8=DATA_UP7[2];

for(i=0;i<9;i++)
{
if(UPS_SEND_KIO_PACKET (nk,packet.buf)==false) //nk=1
 {
 Application->MessageBox("������ �������� ������ 2 ��7!","����", MB_ICONERROR| MB_OK);
  return false;
 }
 else
  {
  res=PaketAnsw(IPS_Answ);
  if(res==true)
   break;
  }
}//for
 return res;
}

bool TForm1::PaketUP7_3(Byte ADR_UP7,Byte DATA_UP7[])
{
 int nk=1,i;
//Byte dan;
Byte LEN=13;
Byte IPK=0xff;//��������� �����
Byte DST=0x7;
Byte SRC=0 ;
Byte IPS=0x21;
Byte IPK_UP7=0x3;
Byte IPS_Answ=0x22;
int ret,j;
bool resl=false,res;

union{
       struct{
                  U32 	len     : 8,
			byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8,
                        byte5   : 8,
                        byte6   : 8,
                        byte7   : 8,
                        byte8   : 8,
                        byte9   : 8,
                        byte10  : 8,
                        byte11  : 8,
                        byte12  : 8;

              } p_my;
             U32 buf[256/4];
             }  packet;
packet.p_my.len=LEN;
packet.p_my.byte1=IPK;
packet.p_my.byte2=(SRC&0x1F)|(DST<<5);
packet.p_my.byte3=(IPS<<2);
packet.p_my.byte4=ADR_UP7;
packet.p_my.byte5=IPK_UP7;
packet.p_my.byte6=DATA_UP7[0];
packet.p_my.byte7=DATA_UP7[1];
packet.p_my.byte8=DATA_UP7[2];
packet.p_my.byte9=DATA_UP7[3];
packet.p_my.byte10=DATA_UP7[4];
packet.p_my.byte11=DATA_UP7[5];
packet.p_my.byte12=DATA_UP7[6];


     for(i=0;i<10;i++)
        {
        if(UPS_SEND_KIO_PACKET (nk,packet.buf) == true)
         {
         resl=true;
         break;
         }
        }//for i

      if(resl==false)
         {
          Application->MessageBox("������ �������� ������ 3 ��7!","����", MB_ICONERROR| MB_OK);
          return false; //  ������ �� ������
         }

   /* ����� ��������� ������ */
  /* ret=otvet_paket();
   if(ret==0)   break ;
  else
     {
      if((ret==1)&&(j==9))
      {
      Application->MessageBox("������ ��� �������� ������ 3 ERR=1","����", MB_ICONERROR| MB_OK);
      return false;
      }
      if((ret==2)&&(j==9))
      {
       Application->MessageBox("��� �������� ������� �� ����� 3!","����", MB_ICONERROR| MB_OK);
       return false;
      }
     }//else
  } //for j
  return true;  */
 else
  res=PaketAnsw(IPS_Answ);

 return res;

}
bool TForm1::PaketUP7_4(Byte ADR_UP7,Byte DATA_UP7[])
{

int nk=1;
//Byte dan;
Byte LEN=7;
Byte IPK=0xff;//��������� �����
Byte SRC=0;
Byte DST=0x7;
Byte IPS=0x21;
Byte IPK_UP7=0x4;
Byte  IPS_Answ=0x22;
int ret,j,i;
bool res;
union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   : 8,
                 byte5   : 8,
                 byte6   : 8;

            } p;
      U32 buf[256/4];
     }  packet;

packet.p.len=LEN;
packet.p.byte1=IPK;
packet.p.byte2=(SRC&0x1F)|(DST<<5);
packet.p.byte3=(IPS<<2);
packet.p.byte4=ADR_UP7;
packet.p.byte5=IPK_UP7;
packet.p.byte6=DATA_UP7[0];

for(i=0;i<9;i++)
{
if(UPS_SEND_KIO_PACKET (nk,packet.buf)==false) //nk=1
 {
 Application->MessageBox("������ �������� ������!","����", MB_ICONERROR| MB_OK);
  return false;
 }
 else
  {
  res=PaketAnsw(IPS_Answ);
  if(res==true)
   break;
  }
}//for
 return res;

}

Byte TForm1::GetAdrUp7Post(int indLit,int indPSph)
{
Byte ADR_UP7;
//����� ��7
if(indLit==0)     //������2
 {
   if(indPSph==0) //���
   ADR_UP7=0x2;
   else         //���
   ADR_UP7=0x3;
 }
else             //������ 53
{
    if(indPSph==0) //���
   ADR_UP7=0x0;
   else         //���
   ADR_UP7=0x1;
}
return  ADR_UP7;
}

bool TForm1::SetOUT_EUS_ex(int indLit,int indPSph, int indOut)
{
//�����1 ��7_______________________________
Byte EUS1,EUS2;
Byte EPRM_EPRD;  //���������� ������
Byte DATA_UP7_1[2];
Byte ONVIP=0x1;  /* ��������� ��������� ������� */
Byte ADR_UP7;
 if(Mode==1)
// ����� ��7�
EPRM_EPRD=0x20; // EPRM_EPRD=0x40;  /* ��������� */

else if(Mode==0)   //�����
EPRM_EPRD=0x80;

 if(indOut<8)
 {
  EUS1=0x1<<indOut;
  EUS2=0x0;
 }
 else if(indOut<13)
 {
  EUS1=0x0;
  EUS2=0x1<<(indOut-8);
 }
else{   //��� ����
 EUS1=0xff;
  EUS2=0x1f; }

DATA_UP7_1[0]=EUS1;
DATA_UP7_1[1]=EPRM_EPRD|(ONVIP<<5)|EUS2;
ADR_UP7=GetAdrUp7Post(indLit,indPSph);

Sleep(1);
if(PaketUP7_1(ADR_UP7, DATA_UP7_1,0x1)==false) return false;
return true;
}


bool TForm1::SetOUT_EUS(int indLit,int indPSph, int indOut)
{
//�����1 ��7_______________________________
Byte EUS1,EUS2;
Byte EPRM_EPRD;  //���������� ������
Byte DATA_UP7_1[2];
Byte ONVIP=0x1;  /* ��������� ��������� ������� */
Byte ADR_UP7;
 if(Mode==1)
 EPRM_EPRD=0x40;  /* ��������� */

else if(Mode==0)   //�����
EPRM_EPRD=0x80;

 if(indOut<8)
 {
  EUS1=0x1<<indOut;
  EUS2=0x0;
 }
 else if(indOut<13)
 {
  EUS1=0x0;
  EUS2=0x1<<(indOut-8);
 }
else{   //��� ����
 EUS1=0xff;
  EUS2=0x1f; }

DATA_UP7_1[0]=EUS1;
DATA_UP7_1[1]=EPRM_EPRD|(ONVIP<<5)|EUS2;
ADR_UP7=GetAdrUp7Post(indLit,indPSph);

Sleep(1);
if(PaketUP7_1(ADR_UP7, DATA_UP7_1,0x1)==false) return false;
return true;
}

//������� ��� �� �����������
void TForm1::InAttOff(void)
{
int i;
Byte DATA_UP7[3];
Byte ON1,ON2;
Byte N1O,N2O;
Byte lN1Att;
Byte lN2Att;

ON1=0;
ON2=0;
lN1Att=0x1f;
lN2Att=0x1f;
DATA_UP7[0]=0x0;
DATA_UP7[1]=lN1Att||(ON1<<5);
DATA_UP7[2]=lN2Att||(ON2<<5);
for(i=0;i<3;i++)
PaketUP7_2( i,DATA_UP7);  //��� 4 ��7  ����� 2
}

//��������� ��� ��������� � ��������� ���������
void TForm1::EUSOff(void)
{
 int i;
Byte DATA_UP7[2];
 for(i=0;i<2;i++)
  DATA_UP7[i]=0x0;

for(i=0;i<4;i++)
PaketUP7_1( i,DATA_UP7,0);     //��� 4 ��7 ����� 1
}

//�������/������� ��� �������� �����������

void TForm1::OutAttOnOff(Byte On_Off)
{
 int i;
Byte DATA_UP7[7];
for(i=0;i<7;i++)
DATA_UP7[i]=On_Off;
for(i=0;i<4;i++)
PaketUP7_3( i,DATA_UP7); //��� 4 ��7 ����� 3

}

bool TForm1::SetOutAtt(int lit,int post, int nl,int freq_index)
{
Byte DATA_UP7[7];
Byte ADR_UP7;
int i,j;
for(j=0,i=0;j<7;j++)
{
	DATA_UP7[j]= Att_OUTi[nl][i][freq_index]|(Att_OUTi[nl][i+1][freq_index]<<4);
 	i=i+2;
}
ADR_UP7=GetAdrUp7Post(lit,post);
return PaketUP7_3(ADR_UP7,DATA_UP7); //��� 4 ��7 ����� 3

}



//-------------------------------------------------
/*
m1:     for(i=0;i<10;i++)
        {
        if(UPS_SEND_KIO_PACKET (nk,packet.buf) == true)
         {
         resl=true;
         break;
         }
        }//for
      if(resl==false)
         {
          Application->MessageBox("������ �������� ������ 1!","����", MB_ICONERROR| MB_OK);
          return false; //  ������ �� ������
         }

   // ����� ��������� ������
   ret=otvet_paket();

   if(ret!=0)
   {
    k++;
     if(k<=9) goto m1;
     else
     {
      if(ret==1)
      {
       ShowMessage("������ ��� �������� ������ 1 ERR=1");
       return false;
      }
      if(ret==2)
      {
       ShowMessage("��� �������� ������� �� ����� 1!");
             return false;
      }
     }//else
  } //(ret!=0)
 else return true;
  return false; */
