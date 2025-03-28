//---------------------------------------------------------------------------


#pragma hdrstop

#include "ARM.h"
#include "TFmLib.h"
#include "TFmLoadUps.h"
#include "TFmWriteUps.h"
#include "TUpsLib.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
 bool TForm1::ShowErr(AnsiString St)
 {
  Application->MessageBox(St.c_str(),"УППУ", MB_ICONERROR| MB_OK);
  return false;
 }
bool TForm1::PaketP_RDF(U32 addr_rd,U32 data_rd[])
{
  int nk, nf=1;
Byte IPS=0x4, DST=0x7;
Byte SRC=0x0;

bool res;
union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   :8,
                 byte5   :8,
                 byte6   :8,
                 byte7   :8;

            } p;
      U32 buf[256/4];
     }  packet;

 union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   :8,
                 byte5   :8,
                 byte6   :8,
                 byte7   :8;
            } p;
      U32 buf[256/4];
     } anspacket;

//anspacket.p.len=18;


packet.p.len=8;
packet.p.byte1=0xff;
packet.p.byte2=(DST<<5)|SRC;
packet.p.byte3=(IPS<<2);
packet.buf[1]=addr_rd;
unsigned int t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = UPS_SEND_KIO_PACKET(nf, packet.buf);
   }while (!res && (GetTickCount() <= t));
if(!res ){
  Application->MessageBox("Ошибка передачи пакета P_RDF","УППУ", MB_ICONERROR| MB_OK);
  return false;}


  t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = UPS_RECIV_KIO_PACKET(&nk, anspacket.buf)&&((anspacket.p.byte3>>2)==0x5)  ;
   }while (!res && (GetTickCount() <= t));
if(!res ) {
  Application->MessageBox("Ошибка отклика на пакет P_RDA","УППУ", MB_ICONERROR| MB_OK);
  return false;
  }

for(int i=0;i<7;i++)
data_rd[i]=anspacket.buf[i+1];

      return res;  

}

bool TForm1::PaketP_RDA(U32 addr_rd,U32 &data_rd )
{
int nk,nf=1;
Byte IPS=0x8, DST=0x7;
Byte SRC=0x0;
bool res;
union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   :8,
                 byte5   :8,
                 byte6   :8,
                 byte7   :8;

            } p;
      U32 buf[256/4];
     }  packet;

packet.p.len=8;
packet.p.byte1=0xff;
packet.p.byte2=(DST<<5)|SRC;
packet.p.byte3=IPS<<2;
packet.buf[1]=addr_rd;

int t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = UPS_SEND_KIO_PACKET(nf, packet.buf);
   }while (!res && (GetTickCount() <= t));
if(!res ){
  Application->MessageBox("Ошибка передачи пакета P_WRA","УППУ", MB_ICONERROR| MB_OK);
  return false;}

union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   :8,
                 byte5   :8,
                 byte6   :8,
                 byte7   :8;
            } p;
      U32 buf[256/4];
     } anspacket;

anspacket.p.len=8;

  t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = UPS_RECIV_KIO_PACKET(&nk, anspacket.buf) && (anspacket.p.len & 0xff) && ((anspacket.p.byte3>>2)==0x9) ;
   }while (!res && (GetTickCount() <= t));
if(!res )
  Application->MessageBox("Ошибка отклика на пакет P_RDA","УППУ", MB_ICONERROR| MB_OK);
else
data_rd=anspacket.buf[1];
      return res;
}





bool TForm1::PaketP_WRA(U32 addr_wr,U32 data_wr )
{
int nf=1,t,nk;
bool res;
Byte DST=0x7,SRC=0;
Byte IPS=0x0a;
Byte IPS_Answ=0x0b;
union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   :8,
                 byte5   :8,
                 byte6   :8,
                 byte7   :8,
                 byte8   :8,
                 byte9   :8,
                 byte10   :8,
                 byte11   :8;
            } p;
      U32 buf[256/4];
     }  packet;

packet.p.len=12;
packet.p.byte1=0xff;
packet.p.byte2= (SRC&0x1F)|(DST<<5);
packet.p.byte3=IPS<<2;
packet.buf[1]=addr_wr;
packet.buf[2]=data_wr;

 t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = UPS_SEND_KIO_PACKET(nf, packet.buf);
   }while (!res && (GetTickCount() <= t));
if(!res ){
  Application->MessageBox("Ошибка передачи пакета P_WRA","УППУ", MB_ICONERROR| MB_OK);
  return false;}

res=PaketAnsw(IPS_Answ);
return res;
}

bool TForm1::PaketP_WRD(Byte data,Byte DST)     //ЦАП ПКУ
{
int nf=1,t,nk;
bool res;
union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   :8;
            } p;
      U32 buf[256/4];
     }  packet;

packet.p.len=5;
packet.p.byte1=0xff;  //пультовый
packet.p.byte2=(DST<<5);
packet.p.byte3=(0x25<<2);
packet.p.byte4=data;

 t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = UPS_SEND_KIO_PACKET(nf, packet.buf);
   }while (!res && (GetTickCount() <= t));
if(!res ){
  Application->MessageBox("Ошибка передачи пакета P_WRD","УППУ", MB_ICONERROR| MB_OK);
  return false;}

union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8;

            } p;
      U32 buf[256/4];
     } anspacket;

  t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = UPS_RECIV_KIO_PACKET(&nk, anspacket.buf) && (anspacket.p.len & 0xff) && ((anspacket.p.byte3>>2)==0x26) ;
   }while (!res && (GetTickCount() <= t));
if(!res )
  Application->MessageBox("Ошибка отклика на пакет P_WRD","УППУ", MB_ICONERROR| MB_OK);

      return res;
}

bool TForm1::PaketP_WRP(u8* buf_dan,Byte DST,Byte sz)
{
int nf=1,nk,t;
bool res;

union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8;

            } p;
      U32 buf[256/4];
     }  packet;

union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   :8;
            } p;
      U32 buf[256/4];
     }  packet_ans;

packet.p.len=sz+4;
packet.p.byte1=0xff;  //пультовый
packet.p.byte2=DST<<5;
packet.p.byte3=0x1e<<2;//IPS=0x1e

for(int i=0;i<16;i++)
packet.buf[i+1]= buf_dan[i];

 t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = UPS_SEND_KIO_PACKET(nf, packet.buf);
   }while (!res && (GetTickCount() <= t));
   if (!res)
if(!res ){
  Application->MessageBox("Ошибка передачи пакета P_WRP","УППУ", MB_ICONERROR| MB_OK);
  return false;}


   t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = UPS_RECIV_KIO_PACKET(&nk, packet_ans.buf) && ((packet_ans.p.byte3>>2)==0x1f )
                                && (packet_ans.p.byte4==0) ;
   }while (!res && (GetTickCount() <= t));

if(!res )
  Application->MessageBox("Ошибка при приеме  пакета P_WRP","УППУ", MB_ICONERROR| MB_OK);

 return  res ;

}

//Формуляр обслуживания цели
bool TForm1::PaketFOC(int indIn,int NP,unsigned get,unsigned sint,unsigned NL )
{
Byte NIT;
Byte ZOC=0x0;
Byte NKS=0 ;
Byte NAP=0;
int nk=1,i;
Byte LEN=7;
Byte IPK=0x16;  //для FOC
Byte BYTE2;
Byte KF;
Byte dan;
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

 NIT=indIn;

BYTE2=NIT|(ZOC<<3)|(NKS<<6)|(NAP<<7);
KF=(Byte(get)<<3)|Byte(sint);

packet.p.len=LEN;
packet.p.byte1=IPK;
packet.p.byte2=BYTE2;
packet.p.byte3=KF;
packet.p.byte4=NL|(NP<<3);
packet.p.byte5=0;
packet.p.byte6=0;
union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   :8;
            } p;
      U32 buf[256/4];
     } anspacket;

int t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = UPS_SEND_KIO_PACKET(nk, packet.buf);
   }while (!res && (GetTickCount() <= t));
if(!res ){
  Application->MessageBox("Ошибка передачи пакета FOC","УППУ", MB_ICONERROR| MB_OK);
  return false;}

 /* t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
    //  res = UPS_RECIV_KIO_PACKET(&nk, anspacket.buf);
    //  Byte a=(anspacket.p.len & 0xff);
    //  a= anspacket.p.byte32;
    //  a= anspacket.p.byte4;
   //   res = UPS_RECIV_KIO_PACKET(&nk, anspacket.buf);// && (anspacket.p.len & 0xff)
    //   && ((anspacket.p.byte3)==0x16);//&&(anspacket.p.byte4==0) ;
   }while (!res && (GetTickCount() <= t));

if(!res )
  Application->MessageBox("Ошибка при приеме отклика на пакет FOC","УППУ", MB_ICONERROR| MB_OK);*/

 return true;

}


bool TForm1::CheckKRDY(Byte KRDY)
{
if(KRDY!=0)
{
            if((KRDY&0x1)!=0)
           Application->MessageBox("Ошибка УП7-1!","УППУ", MB_ICONERROR| MB_OK);
            if((KRDY&0x2)!=0)
           Application->MessageBox("Ошибка УП7-2!","УППУ", MB_ICONERROR| MB_OK);
            if((KRDY&0x4)!=0)
           Application->MessageBox("Ошибка УП7-3!","УППУ", MB_ICONERROR| MB_OK);
            if((KRDY&0x8)!=0)
           Application->MessageBox("Ошибка УП7-4!","УППУ", MB_ICONERROR| MB_OK);

           return false;
}
else
 return true;
}

//Квитанция управления
bool TForm1::PaketFKU(Byte* DanFKU,Byte initIPK )
{
unsigned int t;
int nk;
 char* buff;
 bool res;
 Byte KRDY,a;
//memset(DanFKU,0,3);
 union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   : 8;
            } p;
      U32 buf[256/4];
     }  packet;

 t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = (UPS_RECIV_KIO_PACKET (&nk,packet.buf)==true)&&(packet.p.len&0xff)&&
                                  (packet.p.byte1==0x10)&&(packet.p.byte3==initIPK);//&&(packet.p.byte4==0);

     }while (!res && (GetTickCount() <= t));



/*a=packet.p.len;
a=  packet.p.byte1;
a=   packet.p.byte2;
a=   packet.p.byte3;
a=   packet.p.byte4; */

if(res==true)
  {
  KRDY=packet.p.byte4;
  if(CheckKRDY(KRDY))
    {
     DanFKU[0]= packet.p.byte2;
     DanFKU[1]= packet.p.byte3;
     DanFKU[2]= packet.p.byte4;
     return true;
    }
   else return false;
  }
else{
  Application->MessageBox("Нет FKU","", MB_ICONERROR| MB_OK);
 return false;  }
}

bool TForm1::PaketFTS(Byte DanFTS[14])
{
 int nk=1;
 bool res;
 //Byte LEN=16;
 //Byte Dn[15];
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
                 byte8   : 8,
                 byte9   : 8,
                 byte10   : 8,
                 byte11   : 8,
                 byte12   : 8,
                 byte13   : 8,
                 byte14   : 8,
                 byte15   : 8;
            } p;
      U32 buf[256/4];
     }  packet;

Sleep(100);
//UPS_RECIV_KIO_PACKET (&nk,packet.buf);

int t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = (UPS_RECIV_KIO_PACKET (&nk,packet.buf)==true)&&(packet.p.len&0xff)&& (packet.p.byte1==0x12);

     }while (!res && (GetTickCount() <= t));

if(!res)
   return ShowErr("Нет пакета FTS");
 else
   {
      DanFTS[0]=packet.p.byte2;
      DanFTS[1]=packet.p.byte3;
      DanFTS[2]=packet.p.byte4;
      DanFTS[3]=packet.p.byte5;
      DanFTS[4]=packet.p.byte6;
      DanFTS[5]=packet.p.byte7;
      DanFTS[6]=packet.p.byte8;
      DanFTS[7]=packet.p.byte9;
      DanFTS[8]=packet.p.byte10;
      DanFTS[9]=packet.p.byte11;
      DanFTS[10]=packet.p.byte12;
      DanFTS[11]=packet.p.byte13;
      DanFTS[12]=packet.p.byte14;
      DanFTS[13]=packet.p.byte15;
      return true;
    }

}


bool TForm1::PaketFUK(Byte* DATA)
{
  int i,nk=1;
  unsigned LEN=5;
  Byte dan;
  unsigned IPK=0x14;
  bool res;

union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   : 8;
            } p;
      U32 buf[256/4];
     }  packet;

packet.p.len=LEN;
packet.p.byte1=IPK;
packet.p.byte2=DATA[0];
packet.p.byte3=DATA[1];
packet.p.byte4=DATA[2];

union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   :8;
            } p;
      U32 buf[256/4];
     } anspacket;

int t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = UPS_SEND_KIO_PACKET(nk, packet.buf);
   }while (!res && (GetTickCount() <= t));
if(!res ){
  Application->MessageBox("Ошибка передачи пакета FUK","УППУ", MB_ICONERROR| MB_OK);
  return false;}

  t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = UPS_RECIV_KIO_PACKET(&nk, anspacket.buf) && (anspacket.p.len & 0xff) && ((anspacket.p.byte3)==0x14);
                               //  &&(anspacket.p.byte4==0) ;
   }while (!res && (GetTickCount() <= t));
if(!res )
   Application->MessageBox("Ошибка при приеме отклика на пакет FUK","УППУ", MB_ICONERROR| MB_OK);

   return res;
}

//================формуляр FOU ================================================
bool TForm1::Vkl_IP(Byte ONV,Byte ONV2_0,Byte ONV2_1 ,Byte ONV3_0,Byte ONV3_1)
{
 Byte LEN=5;
 Byte IPK=0x15;
 Byte NAP=0x0;/* выяснить */
 Byte MROC=0x0; /* выяснить */
 Byte RKDO=0x0,RKD1=0x0,RSCH=0x0; /* выяснить */
 Byte RETS=0x0;  /* выяснить */
 Byte RAD=0x0;   /* выяснить */
 Byte dan;
 int nk=1,i;
 bool res;
 union{
       struct{
                  U32   len     : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8;
              } p_my;
             U32 buf[256/4];
             }  packet;

union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   :8;
            } p;
      U32 buf[256/4];
     } anspacket;

        // ONV=0x1; /* включить источник питания УППУ */
         LEN=0x5; /*5*/
         IPK=0x15;  /* формуляр общего управления FOU*/

        packet.p_my.len = LEN;
        packet.p_my.byte1 = IPK;  /* IPK=0x15*/
        packet.p_my.byte2 = ONV3_0|(ONV3_1<<1)|(ONV2_0<<2)|(ONV2_1<<3)|(ONV<<4)|(NAP<<7);
        packet.p_my.byte3 = MROC&0xFF;
        packet.p_my.byte4 = RKDO|(RKD1<<1)|(RSCH<<2)|(RETS<<3)|(RAD<<4);

 for(int j=0;j<9;j++){
if((res=UPS_SEND_KIO_PACKET (nk,packet.buf))==true)
break;}


if(res==false){
 Application->MessageBox("Ошибка передачи пакета FOU!","УППУ", MB_ICONERROR| MB_OK);
 return false;}

/*int t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = (UPS_RECIV_KIO_PACKET (&nk,anspacket.buf)==true)&&(anspacket.p.len&0xff)&&
                                  (anspacket.p.byte1==0x10)&&(anspacket.p.byte3==0x15);
                                //  &&(anspacket.p.byte4==0) ;

     }while (!res && (GetTickCount() <= t));
 if(!res)
 Application->MessageBox("Ошибка при приеме отклика на пакет FOC","УППУ", MB_ICONERROR| MB_OK);*/
return true;

}

//пакет запроса данных

bool TForm1::PaketFZD(Byte ZFTS_ZFKU,Byte* AskDan)  //1-ZFKU,2-ZFTS
{
 Byte LEN=3,IPK=0x11;
 Byte NAP=0x0;/* выяснить */
 int nk=1;
 Byte dan;


if((ZFTS_ZFKU<1)||(ZFTS_ZFKU>2))
goto M1;
 union{
       struct{
                  U32   len     : 8,
                        byte1   : 8,
                        byte2  : 8;
              } p;
             U32 buf[256/4];
             }  packet;

        packet.p.len = LEN;
        packet.p.byte1 = IPK;
        packet.p.byte2 = NAP|ZFTS_ZFKU;

 if(UPS_SEND_KIO_PACKET (nk,packet.buf)==false) //nk=1 не известно
 {
 Application->MessageBox("Ошибка передачи пакета!","УППУ", MB_ICONERROR| MB_OK);
  return false;
 }
else if(ZFTS_ZFKU==1)
     {
      if(PaketFKU(AskDan,0x11)==true)
      {
        return true;
      }
     else
      return false;

     } //if FKU

else if (ZFTS_ZFKU==2)
 {
  if(PaketFTS(AskDan)==true)
  return true;
  else
  {
    Application->MessageBox("Ошибка приема пакета технического состояния FTS!","УППУ", MB_ICONERROR| MB_OK);
   return false;
  }


 } //else if (ZFTS_ZFKU==2)
M1:;
  return false;
}

bool TForm1::PaketFUP(Byte bytes[4],Byte& dan )
{
int i,t;
int nk=1,nf;
Byte LEN=0x6;
Byte IPK=0x13;
bool res;
union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   : 8,
                 byte5   : 8;
            } p;
      U32 buf[256/4];
     }  packet;

packet.p.len=LEN;
packet.p.byte1=IPK;
packet.p.byte2=bytes[0];
packet.p.byte3=bytes[1];
packet.p.byte4=bytes[2];
packet.p.byte5=bytes[3];


union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   :8;
            } p;
      U32 buf[256/4];
     } anspacket;



for(i=0;i<9;i++)
{
if((res=UPS_SEND_KIO_PACKET (nk,packet.buf))) //nk=1
break;
}
if(!res)
 Application->MessageBox("Ошибка передачи пакета FUP!","УППУ", MB_ICONERROR| MB_OK);

 t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
//      res = UPS_RECIV_KIO_PACKET(&nf, anspacket.buf);
		res = UPS_RECIV_KIO_PACKET(&nf, anspacket.buf) && (anspacket.p.len & 0xff) && (anspacket.p.byte1==0x10)
                                                     &&(anspacket.p.byte3==0x13);//&&(anspacket.p.byte4==0) ;
Byte a=anspacket.p.len ;
a= anspacket.p.byte1;
a=anspacket.p.byte3;
a=anspacket.p.byte4;
   }while (!res && (GetTickCount() <= t));
if(!res)

 Application->MessageBox("Ошибка при риеме отклика на пакет FUP!","УППУ", MB_ICONERROR| MB_OK);

   dan=anspacket.p.byte2;
      return res;
}

//Формуляр(пакет) перехода в штатный режим
bool TForm1::Packet_P_CO(void)
{
 int nk=1;
 Byte LEN =4;
 Byte IPK=0xff;   //пультовый режим
 Byte IPS=0x1a;
 Byte DST=0x7;///!!!!!!
 Byte IPS_Answ=0x1b;
 union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
					  byte3   : 8;
            } p;
      U32 buf[256/4];
     }  packet;

     packet.p.len=LEN;
     packet.p.byte1=IPK;
     packet.p.byte2=DST<<5;
     packet.p.byte3=IPS<<2;


 if(UPS_SEND_KIO_PACKET (nk,packet.buf)==false)
 {
 Application->MessageBox("Ошибка передачи пакета P_GO!","УППУ", MB_ICONERROR| MB_OK);
  return false;
 }
else
{

  if(PaketAnsw(IPS_Answ)==true)
  return true;
  else
    return   false;


} //else

}
// формат ответного пакета , написан только заголовок

bool TForm1::PaketAnsw(Byte IPS_Answ)
{
int nk;
//Byte IPS;
Byte err,a;
unsigned t;

bool res;
 char* buff;
 union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8,
                 byte4   :8;
            } p;
      U32 buf[256/4];
     }  packet;

 t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
	  res = UPS_RECIV_KIO_PACKET (&nk,packet.buf)&&((packet.p.byte3>>2)==IPS_Answ);

     }while (!res && (GetTickCount() <= t));
a= packet.p.byte3>>2;

if(res==false)
{
Application->MessageBox("Время ожидания отклика на пакеты пультового режима истекло","Квитанции управления не получена!", MB_ICONERROR| MB_OK);
return false;
}
else {
if((IPS_Answ!=0x1b)&&(IPS_Answ!=0x0b)){
if((packet.p.byte4&0x1)!=0)
return false;}
else  return true;
}
}


void __fastcall TForm1::ResetUPPU(TObject *Sender)
{

if(Application->MessageBox("Питание 1ППА-52 включено?", "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
{
if(Res_UPPU())
ShowMessage("Сброс УППУ прошел");

}
}

bool TForm1::Res_UPPU(void)
{
 unsigned sbros_pk;

  U32 abuf[]={0x900011};
  U32 dbuf[]={0};
  U32 len_my=1; // len_my=10;
          sbros_pk = 0x0;
  dbuf[0]= sbros_pk&0x1;

 if(FmLib-> UpsWriteMemBuf32(abuf,dbuf,len_my)==true){;}
      else
         {
          ShowMessage("Ошибка сброса УППУ");
          return false  ;
          }

       MyTimer(1000);

       sbros_pk = 0x1;

  dbuf[0]= sbros_pk&0x1;

    if(FmLib-> UpsWriteMemBuf32(abuf,dbuf,len_my)==true){return true;}

      else
        {
          ShowMessage("Ошибка при записи сброса УППУ!");
          return false ;
        }

}

//закрыть аттенюаторы СБ-53
void TForm1::AttCB_53Off(void)
{
 Byte DATA[3];
 Byte AT12_1=0x1f;
 DATA[0]=AT12_1;
 DATA[1]=0x0;
 DATA[2]=0x0;
 PaketFUK(DATA);

}




void TForm1::MyTimer(int tm)
{
 Timer1->Interval=tm;
 Timer1->Enabled=true;
 while(!TimeOff)
  Application->ProcessMessages();
 TimeOff=false;
}


void __fastcall TForm1::TimerOff(TObject *Sender)
{
TimeOff=true;
Timer1->Enabled=false;
}
//---------------------------------------------------------------------------

