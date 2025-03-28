//---------------------------------------------------------------------------


#pragma hdrstop

#include "ARM.h"
#include <stdio.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

char MsgBuffer[300];

unsigned char bufw1[32]; /* для записи  */
unsigned char bufr1[32]; /* для чтения */

//---------------------------------------------------------------------------
int TForm1::USBCleanup(char* ErrorMsg)
{
    sprintf(MsgBuffer, ErrorMsg);
      if(Application->MessageBox(MsgBuffer,
            "Error",MB_OKCANCEL+MB_ICONSTOP)==IDCANCEL)
              {
             //  ShowMessage("Выполнение прервано");
               return 1; /* прервать */
               }
     return 0;  /* продолжить */
}

//================== коммутация входов PLATA_1=====1--ошибка; 0-- нет ошибок==================
int TForm1::comm_vhod(int n_vhod)
{
//
extern unsigned char bufw1[32]; /* для записи  */
 extern unsigned char bufr1[32]; /* для чтения */
 extern bool circle;
 char MsgB1[180];

 int a,k,k1,i1;
 int ret1,nret1;

 unsigned Dan_1,Dan_2,Dan_3,Dan_4;
 unsigned N1,N2,N3,N4;
 unsigned NE1,NE2,NE3,NE4;
 unsigned bf;
 char buf[20];
 int k0;
 int i;

unsigned bf_my[1000];
unsigned kl_bt[1000];

  DWORD RxBytes_my;

   if(PL_1->ResetP()!=0)
   ShowMessage("Сброс Устройства PLATA1 не произошел");
     k0=0;
m0:;

   NE1=0x1; /* 1-й коммутатор включен */
   NE2=0x1; /* 2-й коммутатор включен */
   NE3=0x1; /* 3-й коммутатор включен */
   NE4=0x0;
   N1=0x0;
   N2=n_vhod&0x7;       /* к нужному входу */
   N3=0x1;   /* соединение с измерителем мощности усилителя */
   N4=0x0;

 Dan_1=N1|(NE1<<3);

 Dan_2=N2|(NE2<<3);

 Dan_3=N3|(NE3<<3);

 Dan_4=N4|(NE4<<3);

 Dan_4=0x0;  /* пока так !!! */
 bufw1[0]=Dan_1&(0xF)|(0x10); /* выделить первую тетраду */
 bufw1[1]=Dan_2&(0xF)|(0x20);
 bufw1[2]=Dan_3&(0xF)|(0x30);
 bufw1[3]=Dan_4&(0xF)|(0x40);
 bufw1[4]=0x8F;  /* 1000 1111 всегда*/

  if((ret1=PL_1->Write(bufw1,5))!=0)
  {
   if(ret1!=0) // 0 - нормальное завершение записи
    {
//       ret1 =-2;
       sprintf(MsgB1, "%s\ ret1 = %d  bufw1[0] = 0x%x\n",
       "Ошибка USB при записи ",ret1, bufw1[0]);

      if(USBCleanup(MsgB1)) return(1);//goto end;
    }
 }
     /* чтение байта состояния */
   //============ чтение =============================
//   RxBytes_my=PL_1->Get_FtStatus();
//        if(RxBytes_my!=0) goto m1;
//              else
//               //Wait_read();
//                Sleep(5);
//               RxBytes_my=PL_1->Get_FtStatus();
//              //RxBytes_my=PL_1.GetStatus(rx_bytes_my, tx_bytes_my);
//               if(RxBytes_my!=0) goto m1;
//                 else {
//                    Sleep(5000);
//                  RxBytes_my=PL_1->Get_FtStatus();
//                // RxBytes_my=PL_1.GetStatus(rx_bytes_my, tx_bytes_my);

//               if(RxBytes_my!=0) goto m1;
//                 ShowMessage("Время ожидания окончено");
//                     goto end;
//                    // return(1);
//                     }
//    m1:;


// if(RxBytes_my ==1)
//     {
//     /* один байт */
//   // ret1=WtRead(bufr1,1,&nret1);
//    ret1=PL_1->Read(bufr1,1,&nret1);
//    bf=(unsigned)bufr1[0];
//   }

//  if(RxBytes_my ==32)
//     {
//    //  ret1=WtRead(bufr1,32,&nret1);
//      ret1=PL_1->Read(bufr1,32,&nret1);
//      bf=(unsigned)bufr1[0];
//     }
//   //   if((ret1!=0)||(nret1!=1))
//     if(ret1!=0)
//        {
//         sprintf(MsgB1, "%s\ ret1 = %d  bufr1[0] = 0x%x nret1 = %d \n",
//         "Ошибка USB при чтении ",ret1, bf,nret1);
//          if(USBCleanup(MsgB1)) return(1);//goto end;
//        }

//     if((bf&0x1)==0)
//         {
//          ShowMessage("Неисправна магистраль обмена");
//          // goto end;
//          return(1);
//         }

//       for(k=0;k<32;k++)
//          bufr1[k]=bufr1[k]&0xFF;


//  if((RxBytes_my!=1)&&(RxBytes_my!=32)&&(RxBytes_my!=0))
//        {
//      // FtReset();
//       PL_1->ResetP();
//       /* RxBytes_my=Get_FtStatus();*/
//       if(k0==0) {k0=k0+1; goto m0;}
//       else
//        {
//        ShowMessage("Неисправна магистраль обмена");
//       //goto end;
//        return(1);
//        }
//     }
   end:;
 return(0);
}
//================== коммутация выходов PLATA_2=====1--ошибка 0;-- нет ошибок==================
int TForm1::comm_vyhod(int n_vyhod)
{
extern unsigned char bufw1[32]; /* для записи  */
 extern unsigned char bufr1[32]; /* для чтения */
 extern bool circle;
 char MsgB1[180];

 int a,k,k1,i1;
 int ret1,nret1;
 //extern unsigned Addr;
 unsigned Dan_1,Dan_2,Dan_3,Dan_4;
 unsigned N1,N2,N3,N4;
 unsigned NE1,NE2,NE3,NE4;
 unsigned bf;
 char buf[20];
 int k0;
 int i;

unsigned bf_my[1000];
unsigned kl_bt[1000];

  DWORD RxBytes_my;

   if(PL_2->ResetP()!=0)
   ShowMessage("Сброс Устройства PLATA2 не произошел");
     k0=0;
m0:;

 if(n_vyhod<8)  /** усилители с 1-ого по 8-й **/
 {
   NE1=0x1; /* 1-й коммутатор включен */
   NE2=0x0;
   NE3=0x1; /* 3-й коммутатор включен */
   NE4=0x0;
   N1=n_vyhod&0x7;
   N2=0x0;
   N3=0x0;
   N4=0x0;
 }
if(n_vyhod>=8)  /** усилители с 9-ого по 13-й **/
 {
   NE1=0x0;
   NE2=0x1; /* 2-й коммутатор включен */
   NE3=0x1; /* 3-й коммутатор включен */
   NE4=0x0;
   N1=0x0;
   N2=(n_vyhod-8)&0x7;
   N3=0x1;
   N4=0x0;
 }

 Dan_1=N1|(NE1<<3);

 Dan_2=N2|(NE2<<3);

 Dan_3=N3|(NE3<<3);

 Dan_4=N4|(NE4<<3);

 Dan_4=0x0;  /* пока так !!! */
 bufw1[0]=Dan_1&(0xF)|(0x10); /* выделить первую тетраду */
 bufw1[1]=Dan_2&(0xF)|(0x20);
 bufw1[2]=Dan_3&(0xF)|(0x30);
 bufw1[3]=Dan_4&(0xF)|(0x40);
 bufw1[4]=0x8F;  /* 1000 1111 всегда*/


  if((ret1=PL_2->Write(bufw1,5))!=0)
  {
   if(ret1!=0) // 0 - нормальное завершение записи
    {
//       ret1 =-2;
       sprintf(MsgB1, "%s\ ret1 = %d  bufw1[0] = 0x%x\n",
       "Ошибка USB при записи ",ret1, bufw1[0]);

      if(USBCleanup(MsgB1)) return(1); //goto end;
    }
 }

   //============ чтение =============================
//   RxBytes_my=PL_2->Get_FtStatus();
//       if(RxBytes_my!=0) goto m1;
//              else
//               //Wait_read();
//                Sleep(5);
//               RxBytes_my=PL_2->Get_FtStatus();
//              //RxBytes_my=PL_2.GetStatus(rx_bytes_my, tx_bytes_my);
//               if(RxBytes_my!=0) goto m1;
//                 else {
//                    Sleep(5000);
//                  RxBytes_my=PL_2->Get_FtStatus();
//                // RxBytes_my=PL_2.GetStatus(rx_bytes_my, tx_bytes_my);

//               if(RxBytes_my!=0) goto m1;
//                 ShowMessage("Время ожидания окончено");
//                     goto end;}
//    m1:;


// if(RxBytes_my ==1)
//     {
//     /* один байт */
//   // ret1=WtRead(bufr1,1,&nret1);
//    ret1=PL_2->Read(bufr1,1,&nret1);
//    bf=(unsigned)bufr1[0];
//   }

//  if(RxBytes_my ==32)
//     {
//    //  ret1=WtRead(bufr1,32,&nret1);
//      ret1=PL_2->Read(bufr1,32,&nret1);
//      bf=(unsigned)bufr1[0];
//     }
//   //   if((ret1!=0)||(nret1!=1))
//     if(ret1!=0)
//        {
//         sprintf(MsgB1, "%s\ ret1 = %d  bufr1[0] = 0x%x nret1 = %d \n",
//         "Ошибка USB при чтении ",ret1, bf,nret1);
//          if(USBCleanup(MsgB1)) //goto end;
//          return(1);
//        }

//     if((bf&0x1)==0)
//         {
//          ShowMessage("Неисправна магистраль обмена");
//          // goto end;
//          return(1);
//         }
//       for(k=0;k<32;k++)
//          bufr1[k]=bufr1[k]&0xFF;

//  if((RxBytes_my!=1)&&(RxBytes_my!=32)&&(RxBytes_my!=0))
//       {
//      // FtReset();
//       PL_2->ResetP();
//       /* RxBytes_my=Get_FtStatus();*/
//       if(k0==0) {k0=k0+1; goto m0;}
//       else
//        {
//        ShowMessage("Неисправна магистраль обмена");
//        //goto end;
//        return(1);
//       }
//     }
   end:;
  return(0);
}

