//---------------------------------------------------------------------------


#pragma hdrstop

#include "ARM.h"
#include "visa.h"
#include "TFmLib.h"
#include "TFmLoadUps.h"
#include "TFmWriteUps.h"
#include "TUpsLib.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <process.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

extern bool circle;

void __fastcall TForm1::CalbOutChan53(TObject *Sender)
{
//
 extern double F_rtu[224];
  double freq;
  char buf1[256]={0};
ShowPanel(Panel_53);
Panel_53->Visible=true;

   P_1->Visible=false;
Panel1->Visible=false;
Panel2->Visible=false;
PanelPotent->Visible=false;
Mode=1;

//freq=F_rtu[UD2_f->Position];
// sprintf(buf1,"%.2f",freq);
//          E2_f->Text=buf1;
//          E2_f->Repaint();


 freq=F_rtu[UD53_f->Position+64];
  sprintf(buf1,"%.2f",freq);
          E53_f->Text=buf1;
          E53_f->Repaint();
          FileCalbGnPm();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::B26_closeClick(TObject *Sender)
{
 Panel_53->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::B53_stopClick(TObject *Sender)
{
  extern bool circle;
  extern bool vyh;
  vyh=false;
  circle=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::UD53_fClick(TObject *Sender, TUDBtnType Button)
{
 extern double F_rtu[224];
 double freq;
 char buf1[256]={0};

 freq=F_rtu[UD53_f->Position+64];
 sprintf(buf1,"%.2f",freq);
          E53_f->Text=buf1;
          E53_f->Repaint();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::B53_puskClick(TObject *Sender)
{
if(ChkDevs==true)       /** убрать комментарии для работы ***/
 Calib53OutChn();
 else
 {
if(FindDevises()==true)
 {
 if(ChekDev()==true)
  Calib53OutChn();

 }    //FindDevises()
 }//else
}
//---------------------------------------------------------------------------
//-----    Ручной ружим  --------------------------------
void TForm1::Calib53OutChn(void)
{
  extern bool vyh;
  ViStatus stat=0; // объявление переменной типа ViStatus
  extern double F_rtu[224];

   double powerDBM=0.0;
   double m_freqq;
   double power;

  unsigned ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8,ADC9,ADC10,ADC11,ADC12,ADC13=0x0;
  int ADC=0;

  unsigned NVIP=0x0,TM1=0x0,TM2=0x0,TM3=0x0;
  int T;
  int nf=0x8;/* номер запроса 8 либо 9*/

 //char buf1[256]={0};
// char buf2[256]={0};

 char buf[256]={0};

// double m_freqq_n;
 //double m_freqq_v;

  double P[25];
  double P_1=0;
  double dP;
 int j,k,n_jj;
 //int num=0;
 //char rdbuffer[256]={0};

 int ind; //индекс доступа к массивам калибровки
 long longdown=0; /* ожидание операции завершения*/

 double m_p,m_p_1;  /* мощность, задаваемая на генераторе*/
 double pn;
 double pv;
 double pstep;

 double m_Pow;
 char buf1[256]={0};
 int n_post;
  unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
   int nk,nu;  /* номер КИО*/
  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/
  //unsigned Q_vh[5]={0x0,0x1,0x2,0x4,0x8}; /* 0000, 0001,0010,0100,1000*/
  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* 0000,0001,...,1111 */
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  //unsigned kod_att[13];
  unsigned kod_att[12];
  unsigned IPK_UP7;
	unsigned indLit=1, indPSph=0,  indOut=0;
  AnsiString str2[25]={"ППС1","ППС2","ППС3","ППС4",
                       "ППС5","ППС6","ППС7","ППС8",
                       "ППС9","ППС10","ППС11","ППС12",
                       "ЗПС1","ЗПС2","ЗПС3","ЗПС4",
                       "ЗПС5","ЗПС6","ЗПС7","ЗПС8",
                       "ЗПС9","ЗПС10","ЗПС11","ЗПС12"};
  AnsiString str1[4]={"1ВЧ-53","2ВЧ-53","3ВЧ-53","4ВЧ-53"};

  u32 buf_my[256/4]; // Буфер для принятого пакета

  union{
       struct{
						U32   len     : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8,
                        byte5   : 8;
              } p_my_v;
             U32 buf_my[256/4];
             } packet_my;

 union{
       struct{
                  U32   len   : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8,
                        byte5   : 8,
                        byte6   : 8,
                        byte7   : 8,
                        byte8   : 8,
                        byte9   : 8,
                        byte10  : 8;
              } p_my_v;
             U32 buf_my[256/4];
             } packet_my_t;
  union{
       struct{
                  U32   len     : 8, /*LEN*/
                        byte1   : 8, /*IPK*/
                        byte2   : 8, /*DST SRC*/
                        byte3   : 8, /*IPS DST*/
                        byte4   : 8, /*ERR*/
                        /*byte5   : 8,*/  /*ADR_UP7*/
                        byte5   : 8, /*IPK_UP7*/
                        byte6   : 8, /*ADC1 */
                        byte7   : 8, /*ADC2 */
                        byte8   : 8, /*ADC3 */
                        byte9   : 8, /*ADC4 */
                        byte10  : 8, /*ADC5 */
                        byte11  : 8, /*ADC6 */
                        byte12  : 8, /*ADC7 */
                        byte13  : 8, /*ADC8 */
                        byte14  : 8, /*ADC9 */
                        byte15  : 8, /*ADC10 */
                        byte16  : 8, /*ADC11 */
                        byte17  : 8; /*ADC12 */
                      //  byte18  : 8; /*ADC13 */

                        } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;

         E_53_um->Text=" ";
         E_53_um->Repaint();

         E_t53_0->Text=" ";
         E_t53_0->Repaint();

         E_t53_1->Text=" ";
         E_t53_1->Repaint();

             /* пакет 8*/

              E_53_izm_m->Text=" ";
              E_53_izm_m->Repaint();

        ShowMessage("Подать сигнал с ВЧ генератора на вход "+str1[CB_53_vh->ItemIndex]);
        ShowMessage("Подключить измеритель мощности через аттенюатор 30дБ к выходу "+str2[CB_53_vyh->ItemIndex]);
  /*  if(comm_vhod(CB_53_vh->ItemIndex+4))  //1 -- ошибка, 0 -- без ошибок
           {
             ShowMessage("Не сработал коммутатор 1");
             goto end;
             }
     if(comm_vyhod(CB_53_vyh->ItemIndex))//1 -- ошибка, 0 -- без ошибок
            {
             ShowMessage("Не сработал коммутатор 2");
             goto end;
             }
  */
           /* пакет 2*/
    /*  сначала выключаем неиспользываемые номера выходов матрицы ПМ */
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение матрицы для  1-го и 2-го канала СВЧ */=========================
          n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/

  if(CB_53_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
      if(CB_53_vyh->ItemIndex>11) /* если выбран ППС, то выключаем ЗПС*/
           n_post=1; /*ЗПС*/   /* если выбран ППС, то выключаем ЗПС*/
           else  n_post=0;  nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           if(CB_53_vyh->ItemIndex<=11) /* если выбран ППС, то выключаем ЗПС*/
                 n_post=1;
           else  n_post=0; nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
         if(CB_53_vyh->ItemIndex<=11) /* если выбран ЗПС, то выключаем ППС*/
                 n_post=0;
           else  n_post=1;  nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
          if(CB_53_vyh->ItemIndex<=11) /* если выбран ЗПС, то выключаем ППС*/
              n_post=0;
           else  n_post=1; nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7!\n");
     //goto end;
    }

  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
   Sleep(1);
                       /* пакет 2*/
 
      // US[i]=0x0;
//============/* включение номера выхода матрицы ПМ для 1-ого и 2-ого канала */========================================
//============/* задание кода входных атт для 1-ого и 2-ого канала */==========================
  //if(((UD_2->Position)>=1)&&((UD_2->Position)<=4))
  // {
  //  n_post=2;   /* 1--0: 2(ППС), 3(ЗПС)*/
  // }
  // else  n_post=3;   /* 1--0: 2(ППС), 3(ЗПС)*/

 // if(n_post==2){n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;} /* n_vh1 -- номер выхода матрицы для 1-ого канала СВЧ 0--0xF (4 разряда)*/
 // if(n_post==3){n_vh2= 3+UD_2->Position; n_vh1=3+UD_2->Position;} /* n_vh2 -- номер выхода матрицы для 2-ого канала СВЧ 0--0xF (4 разряда)*/
        n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/
  if(CB_53_vh->ItemIndex==0){in1_at=Qv_vh[CB_53_att_vh->ItemIndex];in2_at=0x1F;
                                 n_post=0; nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[CB_53_att_vh->ItemIndex];
                        n_post=0; nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=Qv_vh[CB_53_att_vh->ItemIndex];in2_at=0x1F;
                      n_post=1;   nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[CB_53_att_vh->ItemIndex];
             n_post=1; nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  //  if((CB_53_vyh->ItemIndex<=12)&&(n_vh1>=4))
   //    {
   //     ShowMessage("Номер выбранного луча не соответствует выбранному выходу ППС!\n");
   //     goto end;
   //    }
   //  if((CB_53_vyh->ItemIndex>=13)&&(n_vh1<=4))
   //    {
    //    ShowMessage("Номер выбранного луча не соответствует выбранному выходу ЗПС!\n");
    //    goto end;
    //    }


 if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче пакета 2 в УП7 ERR=1!\n");
   //  goto end1;
    }

   /* Прием ответного пакета */
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
       Sleep(1);

       /* пакет 3*/
//    for(i=0;i<=12;i++)
    for(i=0;i<=11;i++)
      {
       kod_att[i]=0xF;
      }
  //============/* формуляр задание кода выходных атт */====
   if(CB_53_vyh->ItemIndex<=11)
   {
	 n_post=0;    /*ППС*/
	 indPSph=0;
	 indOut= CB_53_vyh->ItemIndex;
    kod_att[CB_53_vyh->ItemIndex]= Q_vh[CB_53_att_vyh->ItemIndex];
      /* доделать */
  /*  kod_att[0]= Q_vh[CB2_a1->ItemIndex];
    kod_att[1]= Q_vh[CB2_a2->ItemIndex];
    kod_att[2]= Q_vh[CB2_a3->ItemIndex];
    kod_att[3]= Q_vh[CB2_a4->ItemIndex];
    kod_att[4]= Q_vh[CB2_a5->ItemIndex];
    kod_att[5]= Q_vh[CB2_a6->ItemIndex];
    kod_att[6]= Q_vh[CB2_a7->ItemIndex];
    kod_att[7]= Q_vh[CB2_a8->ItemIndex];
    kod_att[8]= Q_vh[CB2_a9->ItemIndex];
    kod_att[9]= Q_vh[CB2_a10->ItemIndex];
    kod_att[10]= Q_vh[CB2_a11->ItemIndex];
    kod_att[11]= Q_vh[CB2_a12->ItemIndex];
	 kod_att[12]= Q_vh[CB2_a13->ItemIndex];
 */
   }
//  if(CB_53_vyh->ItemIndex>12)
   if(CB_53_vyh->ItemIndex>11)
   {
	 n_post=1; /*ЗПС*/
	 indOut= CB_53_vyh->ItemIndex-12;
	 kod_att[CB_53_vyh->ItemIndex-12]= Q_vh[CB_53_att_vyh->ItemIndex];


   /* kod_att[0]= Q_vh[CBzps_a1->ItemIndex];
    kod_att[1]= Q_vh[CBzps_a2->ItemIndex];
    kod_att[2]= Q_vh[CBzps_a3->ItemIndex];
    kod_att[3]= Q_vh[CBzps_a4->ItemIndex];
    kod_att[4]= Q_vh[CBzps_a5->ItemIndex];
    kod_att[5]= Q_vh[CBzps_a6->ItemIndex];
    kod_att[6]= Q_vh[CBzps_a7->ItemIndex];
    kod_att[7]= Q_vh[CBzps_a8->ItemIndex];
    kod_att[8]= Q_vh[CBzps_a9->ItemIndex];
    kod_att[9]= Q_vh[CBzps_a10->ItemIndex];
	 kod_att[10]= Q_vh[CBzps_a11->ItemIndex];
    kod_att[11]= Q_vh[CBzps_a12->ItemIndex];
    kod_att[12]= Q_vh[CBzps_a13->ItemIndex];
   */
   }
 if((res=Vkl_att_t(n_post,kod_att))==1)   /*0-- нет ошибок, 1-- есть ошибки */
     {
      ShowMessage("Ошибка при передаче пакета 3 ERR=1");
     // goto end;
     }
 if(res==2) {ShowMessage("Нет ответных пакетов на пакет 3!");}

         Sleep(1);

	 if(SetOUT_EUS( indLit, indPSph,  indOut)==false) goto end;
              /* пакет 1*/
//-----------------формуляр передачи данных в УП7 -------------------------------------------------------
 //============/* включение канала усилителя, включение источника питания УП7 */========================================            /* пакет 1*/
  //n_post=2+(CB_2_ps->ItemIndex);
  if(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
	{
    n_post=0;    /*ППС*/
    nu=(CB_53_vyh->ItemIndex);    /*индекс от 0 до 12*/  /* nu-- номер усилителя*/
    }
   if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
    nu=(CB_53_vyh->ItemIndex)-12;    /*индекс от 13 до 25*/  /* nu-- номер усилителя*/
    }
  // nu=0;  /* ???? nu-- nu=(номер усилителя*/
   if((res=Vkl_us_vip_t(n_post,nu))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче пакета 1 в УП7 ERR=1!\n");
 //  goto end;
    }
   if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");}

   Sleep(1);

//*************************************************************************

       //Открываем сеанс на GPIB

    m_freqq=F_rtu[UD53_f->Position+64];
   //m_freqq = strtod(E2_f->Text.c_str(),NULL);

   powerDBM = strtod(E53_p->Text.c_str(),NULL);

 /*15.12.10*/ //    power = -70.0;  //отладка
 // Установка на генератор частоты и мощности
 // powerDBM = power;
 stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // частота
 stat = viPrintf(viG,":POW %f dBm\n",powerDBM); // мощность
   if (stat != VI_SUCCESS)
  {
     ShowMessage("Ошибка при установке значений на генератор");
     goto end;
  }
 // viPrintf(vigen,"PULM:STAT OFF\n");   // ВКЛючить имп модуляцию
   viPrintf(viG,"OUTPut:STATe ON\n"); //подкл.  сигнала на выход ген-ра

    longdown=0;

    viPrintf(viG,"*OPC?\n");

        while(!longdown)
    viScanf(viG,"%d", &longdown);

    viPrintf(viP,"ABORT\n");
   viPrintf(viP,"INIT:CONT ON\n");
   viPrintf(viP,"FETC?\n");
   viScanf(viP,"%t",buf);

    Sleep(1);

   /*15.12.10*/ //  pn=-70.0;
   /*15.12.10*/ // pv=3.0;
   /*15.12.10*/ // pstep=3.0;

  for(k=64; k<=223;k++) /* определение ind*/
     {
      if(F_rtu[k]==m_freqq){ind=k;break;}
     }

  // ind=(f-Fl)/StepCalb;
   m_p=powerDBM;
   m_p_1=m_p-dPg[ind];     /*с учетом калибровки кабеля*/
   // m_p_1=m_p;

   stat = viPrintf(viG,":POW %f dBm\n",m_p_1); // мощность на генераторе

 for(i=0;i<=9;i++)  /* чтение датчика температуры без индикации */
    {
  //  if((CB_53_vh->ItemIndex==0)||(CB_53_vh->ItemIndex==1))
  //   {
  //   n_post=2; /**/
  //   }
  //  if((CB_53_vh->ItemIndex==2)||(CB_53_vh->ItemIndex==3))
  //   {
  //   n_post=3; /**/
  //   }
   if(CB_53_vyh->ItemIndex<=11)   /*  в зависимости от выхода*/
     {
     n_post=0; /**/
     }
    if(CB_53_vyh->ItemIndex>11)
     {
     n_post=1; /**/
     }
        nf=0x8;/* запрос состояния */
//17.07 n_jj=0;

//17.07 m_jj_1:
 if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра запроса данных в УП7!\n");
     goto end;
    }

  // ShowMessage("Формуляр передачи запроса данных в УП7 прошел!\n");


   Sleep(10);
//17.07   if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07        // Нет принятых пакетов//     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07   }

   if(!UPS_RECIV_KIO_PACKET(&nk,packet_my.buf_my))
   {
        // Нет принятых пакетов
//       ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07     if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj_1;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("Сбой по магистрале!");
//17.07       goto m2_end_2;
//17.07      }
   }
  else
    {
        // Принят пакет
        LEN=packet_my_t.p_my_v.len;
        IPK=packet_my_t.p_my_v.byte1;
        SRC=packet_my.p_my_v.byte2&0x1F;
        DST=((packet_my_t.p_my_v.byte2>>5)&0x7)|((packet_my_t.p_my_v.byte3&0x3)<<3);  /* левое крыло DST=0x6, правое крыло DST=0x7*/
        IPS=(packet_my_t.p_my_v.byte3>>2)&0x3F;
        ERR=packet_my_t.p_my_v.byte4&0x1;
        /*ADR_UP7=packet_my_t.p_my_v.byte5;*/
        IPK_UP7=packet_my_t.p_my_v.byte5;
        NVIP=packet_my_t.p_my_v.byte6&0x1;
        TM1=packet_my_t.p_my_v.byte7&0xFF|((packet_my_t.p_my_v.byte8&0xF)<<8);
        TM2=(packet_my_t.p_my_v.byte8>>4)&0xF|(packet_my_t.p_my_v.byte9&0xFF)<<4;

//10.01.11    if(ERR==1)
//      {
//         //ShowMessage("Ошибка при передаче пакета 1 УП7! ERR=1");
//           n_jj=n_jj+1;
//         if(n_jj<=9)
//            {
//             goto m_jj_1;
//            }
//          else
//            {
//             ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении температуры! ERR=1");
//             goto m21;
//            }
//        }
       // if(NVIP==0x1) ShowMessage("Неисправность источника питания!");
    } /* end else from recive*/
  m21:;
    // Sleep(1000);
}/*end for */
m2_end_2:;

      vyh=true;

 while(vyh==true)
  {
   Application->ProcessMessages();
   if(vyh==false) goto end1;


    viPrintf(viP,"ABORT\n");
    viPrintf(viP,"INIT:CONT ON\n");
    viPrintf(viP,"FETC?\n");
    viScanf(viP,"%t",buf);

    m_Pow = atof(buf);
  //  m_Pow=m_Pow-dPm[ind]+30.0;   /*с учетом калибровки кабеля*/
      m_Pow=m_Pow-dPm[ind];   /*с учетом калибровки кабеля*/

        //  Pw=pow(10,Pdbm/10); //мВт       Pw=pow(10,-3)*pow(10,Pdbm/10);  //Вт

          m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

           memset(&buf1,0,20);
           sprintf(buf1,"%.3f",m_Pow);

           E_53_izm_m->Text=buf1;  /* мощность*/
           E_53_izm_m->Repaint();

    Sleep(1);

        /* пакет 8 запрос температуры*/
        nf=0x8;
   if(CB_53_vyh->ItemIndex<=11) /*  в зависимости от выхода*/
     {
     n_post=0; /**/
     }
    if(CB_53_vyh->ItemIndex>11)
     {
     n_post=1; /**/
     }
     nf=0x8;/* запрос состояния */
     n_jj=0;

m_jj_2:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- нет ошибок, 1-- есть ошибки */
      {
       ShowMessage("Ошибка при передаче формуляра запроса данных в УП7!\n");
       vyh=false; goto end;
      }

  // ShowMessage("Формуляр передачи запроса данных в УП7 прошел!\n");

   Sleep(10);
//17.07  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
//17.07     {
//17.07        // Нет принятых пакетов
//17.07 //       ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07     if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj_2;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("Сбой по магистрале!");
//17.07      vyh=false; goto end;// goto m2_end_3;
//17.07      }
//17.07    }

   if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
    {
        // Нет принятых пакетов
//23.12       ShowMessage("Нет принятых пакетов после запроса состояния!");
    }
   else
      {
        // Принят пакет
          LEN=packet_my_t.p_my_v.len;
          IPK=packet_my_t.p_my_v.byte1;
          SRC=packet_my_t.p_my_v.byte2&0x1F;
          DST=((packet_my_t.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* левое крыло DST=0x6, правое крыло DST=0x7*/
          IPS=(packet_my_t.p_my_v.byte3>>2)&0x3F;
          ERR=packet_my_t.p_my_v.byte4&0x1;
        /*ADR_UP7=packet_my.p_my_v.byte5;*/
          IPK_UP7=packet_my_t.p_my_v.byte5;
          NVIP=packet_my_t.p_my_v.byte6&0x1;
          TM1=packet_my_t.p_my_v.byte7&0xFF|((packet_my_t.p_my_v.byte8&0xF)<<8);
          TM2=(packet_my_t.p_my_v.byte8>>4)&0xF|(packet_my_t.p_my_v.byte9&0xFF)<<4;

       /*  NVIP=packet_my.buf_my[6];
         TM1=packet_my.buf_my[7];
         TM2=packet_my.buf_my[8];
         TM3=packet_my.buf_my[9];
       */

        if(ERR==1)
         {
          //ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении Т! ERR=1");
             n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj_2;
            }
          else
            {
             ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении T! ERR=1");
             vyh=false; goto end; // goto m22;
            }
        }
      //22.12.10  if(NVIP==0x1) ShowMessage("Неисправность источника питания!");
//        T=235-(400*(int)TM1)/(int)TM2;
       if((TM1==0)||(TM2==0)){;}
          else
           {
             T=235-(400*TM1)/TM2;

             memset(&buf1,0,20); /* ???????? ?????? */;
             sprintf(buf1,"%d",T);
/* 22.12.10 */
 if(n_post==0)
           {
           E_t53_0->Text=buf1;
           E_t53_0->Repaint();
           }
          else
           {
           E_t53_1->Text=buf1;
           E_t53_1->Repaint();
           }

        }

    } /*else from recive*/

    Sleep(1);
                   /* запрос кода мощности */
                         /* пакет 9*/
//-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//----------------Чтение уровня мощности для каналов усилителей------------------------------
 // if((CB_53_vh->ItemIndex==0)||(CB_53_vh->ItemIndex==1))
//   {
//  n_post=2; /*ППС*/
//   }
//  if((CB_53_vh->ItemIndex==2)||(CB_53_vh->ItemIndex==3))
//    {
//      n_post=3; /*ЗПС*/
//    }
 if(CB_53_vyh->ItemIndex<=11)  /* в зависимости от выхода */     {
     n_post=0; /**/
     }
  if(CB_53_vyh->ItemIndex>11)
     {
     n_post=1; /**/
     }

     nf=0x9;
 n_jj=0;

m_jj:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- нет ошибок, 1-- есть ошибки */
   {
     ShowMessage("Ошибка при передаче формуляра запроса данных (9) в УП7!\n");
    // 10.01.11 vyh=false; goto end;
   }

  Sleep(10);
//17.07 if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07        // Нет принятых пакетов
//17.07//     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07   }

  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
//17.07        // Нет принятых пакетов
//17.07 //     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07      if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("Сбой по магистрале!");
//17.07       vyh=false; goto end; //goto m2_end_5;
//17.07      }
   }
   else
   {
        // Принят пакет

      LEN=packet_my_km.p_my_v.len;
      IPK=packet_my_km.p_my_v.byte1;
      SRC=packet_my_km.p_my_v.byte2&0x1F;
      DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* левое крыло DST=0x6, правое крыло DST=0x7*/
      IPS=(packet_my_km.p_my_v.byte3>>2)&0x3F;
      ERR=packet_my_km.p_my_v.byte4&0x1;
       /* ADR_UP7=packet_my_km.p_my_v.byte5;*/
      IPK_UP7=packet_my_km.p_my_v.byte5;
      ADC1=packet_my_km.p_my_v.byte6;
      ADC2=packet_my_km.p_my_v.byte7;
      ADC3=packet_my_km.p_my_v.byte8;
      ADC4=packet_my_km.p_my_v.byte9;
      ADC5=packet_my_km.p_my_v.byte10;
      ADC6=packet_my_km.p_my_v.byte11;
      ADC7=packet_my_km.p_my_v.byte12;
      ADC8=packet_my_km.p_my_v.byte13;
      ADC9=packet_my_km.p_my_v.byte14;
      ADC10=packet_my_km.p_my_v.byte15;
      ADC11=packet_my_km.p_my_v.byte16;
      ADC12=packet_my_km.p_my_v.byte17;
     // ADC13=packet_my_km.p_my_v.byte18;

// 22.12.10
    if(CB_53_vyh->ItemIndex<=11)  /* в зависимости от выхода */
      {
        if(CB_53_vyh->ItemIndex==0) ADC=ADC1&0xFF;
        if(CB_53_vyh->ItemIndex==1) ADC=ADC2&0xFF;
        if(CB_53_vyh->ItemIndex==2) ADC=ADC3&0xFF;
        if(CB_53_vyh->ItemIndex==3) ADC=ADC4&0xFF;
        if(CB_53_vyh->ItemIndex==4) ADC=ADC5&0xFF;
        if(CB_53_vyh->ItemIndex==5) ADC=ADC6&0xFF;
        if(CB_53_vyh->ItemIndex==6) ADC=ADC7&0xFF;
        if(CB_53_vyh->ItemIndex==7) ADC=ADC8&0xFF;
        if(CB_53_vyh->ItemIndex==8) ADC=ADC9&0xFF;
        if(CB_53_vyh->ItemIndex==9) ADC=ADC10&0xFF;
        if(CB_53_vyh->ItemIndex==10) ADC=ADC11&0xFF;
        if(CB_53_vyh->ItemIndex==11) ADC=ADC12&0xFF;
       // if(CB_53_vyh->ItemIndex==12) ADC=ADC13&0xFF;
      }
      if(CB_53_vyh->ItemIndex>11)  /* в зависимости от выхода */
      {
        if(CB_53_vyh->ItemIndex==12) ADC=ADC1&0xFF;
        if(CB_53_vyh->ItemIndex==13) ADC=ADC2&0xFF;
        if(CB_53_vyh->ItemIndex==14) ADC=ADC3&0xFF;
        if(CB_53_vyh->ItemIndex==15) ADC=ADC4&0xFF;
        if(CB_53_vyh->ItemIndex==16) ADC=ADC5&0xFF;
        if(CB_53_vyh->ItemIndex==17) ADC=ADC6&0xFF;
        if(CB_53_vyh->ItemIndex==18) ADC=ADC7&0xFF;
        if(CB_53_vyh->ItemIndex==19) ADC=ADC8&0xFF;
        if(CB_53_vyh->ItemIndex==20) ADC=ADC9&0xFF;
        if(CB_53_vyh->ItemIndex==21) ADC=ADC10&0xFF;
        if(CB_53_vyh->ItemIndex==22) ADC=ADC11&0xFF;
        if(CB_53_vyh->ItemIndex==23) ADC=ADC12&0xFF;
      //  if(CB_10_vyh->ItemIndex==24) ADC=ADC12&0xFF;
     //   if(CB_10_vyh->ItemIndex==25) ADC=ADC13&0xFF;
      }

       if(ERR==1)
         {
          //ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении кода мощности! ERR=1");
          //goto m1;
           n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj;
            }
          else
            {
             ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении кода мощности! ERR=1");
             goto m1;
            }
          }
           memset(&buf1,0,20);
           sprintf(buf1,"%d",ADC);

           E_53_um->Text=buf1;
           E_53_um->Repaint();

       m1:;
     }
    m2_end_5:;
    m2_end_3:;

   }  /* while*/
   end1:;                         /* пакет 2 */
 //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение матрицы для  1-го и 2-го канала СВЧ */=========================
          n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/

  if(CB_53_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
                           n_post=0;  nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           // if(CB_10_vyh->ItemIndex<=12)
                 n_post=0;    /*ППС*/
         //  else  n_post=3;
         nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
            n_post=1; nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
            n_post=1; nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7!\n");
     //goto end;
    }

  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
   Sleep(1);
                          /* пакет 1*/
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение канала усилителя, выключение источника питания УП7 */=========================
 if(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
   {
    n_post=0;    /*ППС*/
   // nu=(CB_53_vyh->ItemIndex);    /*индекс от 0 до 12*/  /* nu-- номер усилителя*/
    }
   if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
   // nu=12-(CB_53_vyh->ItemIndex);    /*индекс от 13 до 25*/  /* nu-- номер усилителя*/
    }
  // nu=0;  /* ???? nu-- nu=(номер усилителя*/

   if((res=Vykl_us_vip_t(n_post))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных (1) в УП7!\n");
     //goto end;
    }
   if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");}

     Sleep(1);
 end:;
  viPrintf(viG,"OUTPut:STATe OFF\n"); //выкл. сигнала на выход ген-ра
	  EUSOff(); //выключить все усилители и запретить излучение,  пакет1
    ShowMessage("Измерение закончено\n");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::B53_avtClick(TObject *Sender)
{
if(ChkDevs==true)
 {
   Avt53OutChn();
  }
  else
  {
 if(FindDevises()==true)
  {
  if(ChekDev()==true)
  {
    Avt53OutChn();
   }
  }    //FindDevises()
 }//else

}
//-----------------------Автоматический режим -----------------------------
void TForm1::Avt53OutChn(void)
{
extern bool vyh;
  ViStatus stat=0; // объявление переменной типа ViStatus
  extern double F_rtu[224];

   double powerDBM=0.0;
   double m_freqq;
   double power;

   double K_nu=0.0;

 //char buf1[256]={0};
// char buf2[256]={0};

 char buf[256]={0};

// double m_freqq_n;
 //double m_freqq_v;

  double P[35];       /*измеренное значение в Вт*/
  double P_dB[35];    /*измеренное значение в дБ*/

  double P_1=0;
  double dP;
  double p_vt_izm;
  double P_max;
  int j,k,k1;
 //int num=0;
 //char rdbuffer[256]={0};

 int ind; //индекс доступа к массивам калибровки
 long longdown=0; /* ожидание операции завершения*/

 int m_p;
 float x_m_p;
 double m_p_1;  /* мощность, задаваемая на генераторе*/
 int pn;
 int pv;
 int pstep;
 int k_att=0;
 int k_max=0;

 double m_Pow;
 char buf1[256]={0};
  int n_post;
  unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
   int nk,nu;  /* номер КИО*/
                                  /* входной атт */
  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/
/* float Qvh_osl[32]={0.0,-0.75,-1.5,-2.25,-3.0,-3.75,-4.5,-5.25,-6.0,
                     -6.75,-7.5,-8.25,-9.0,-9.75,-10.5,-11.25,-12.0,
                     -12.75,-13.5,-14.25,-15.0,-15.75,-16.5,-17.25,-18.0,
                     -18.75,-19.5,-20.25,-21.0,-21.75,-22.5,-23.25};
*/
                  /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/
 float Qvh_osl[32]={-23.25,-22.5,-21.75,-21.0,-20.25,-19.5,-18.75,-18.0,
                     -17.25,-16.5,-15.75,-15.0,-14.25,-13.5,-12.75,-12.0,
                     -11.25,-10.5,-9.75,-9.0,-8.25,-7.5,-6.75,-6.0,-5.25,
                     -4.5,-3.75,-3.0,-2.25,-1.5,-0.75,0.0};

                     /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/


  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* выходной атт */
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned kod_att[12];

  AnsiString str2[24]={"ППС1","ППС2","ППС3","ППС4",
                       "ППС5","ППС6","ППС7","ППС8",
                       "ППС9","ППС10","ППС11","ППС12",
                       "ЗПС1","ЗПС2","ЗПС3","ЗПС4",
                       "ЗПС5","ЗПС6","ЗПС7","ЗПС8",
                       "ЗПС9","ЗПС10","ЗПС11","ЗПС12"};
  AnsiString str1[4]={"1ВЧ-53","2ВЧ-53","3ВЧ-53","4ВЧ-53"};

  TChartSeries *Series[4]={LineSeries1,LineSeries2,LineSeries7,LineSeries8};

  u32 buf_my[256/4]; // Буфер для принятого пакета

  union{
       struct{
                  U32   len     : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8,
                        byte5   : 8;
              } p_my_v;
             U32 buf_my[256/4];
            } packet_my;
    union{
       struct{
                  U32   len     : 8, /*LEN*/
                        byte1   : 8, /*IPK*/
                        byte2   : 8, /*DST SRC*/
                        byte3   : 8, /*IPS DST*/
                        byte4   : 8, /*ERR*/
                        /*byte5   : 8,*/  /*ADR_UP7*/
                        byte5   : 8, /*IPK_UP7*/
                        byte6   : 8, /*ADC1 */
                        byte7   : 8, /*ADC2 */
                        byte8   : 8, /*ADC3 */
                        byte9   : 8, /*ADC4 */
                        byte10  : 8, /*ADC5 */
                        byte11  : 8, /*ADC6 */
                        byte12  : 8, /*ADC7 */
                        byte13  : 8, /*ADC8 */
                        byte14  : 8, /*ADC9 */
                        byte15  : 8, /*ADC10 */
                        byte16  : 8, /*ADC11 */
                        byte17  : 8; /*ADC12 */
                    //    byte18  : 8; /*ADC13 */

                        } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;
       unsigned ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8,ADC9,ADC10,ADC11,ADC12,ADC13=0x0;
       int ADC=0;
       unsigned IPK_UP7;
       float Kod_M[35]={0};
       int Kod_DM_izm[35]={0};
       int Kod_DM_max=0;
       int nf,n_jj;
       int mk;

              E_53_izm_m->Text=" ";
              E_53_izm_m->Repaint();

        Series[0]->Clear();
        Series[1]->Clear();
        Series[2]->Clear();
        Series[3]->Clear();

        Chart3->BottomAxis->SetMinMax(-24,0);
        Chart3->Title->Text->Clear();
        Chart3->Title->Text->Add("P=P(km)");

       // Series[3]->Repaint();
         Ep53_max->Text="";
         L53_pmax_no->Caption="";

          E53_km_s->Text="";
          E53_km_mx->Text="";

          E53_dm_2->Text="";

      for(k=0; k<=34; k++)
        {
         P[k]=0;
        }

        ShowMessage("Подать сигнал с ВЧ генератора на вход "+str1[CB_53_vh->ItemIndex]);
        ShowMessage("Подключить измеритель мощности через аттенюатор 30дБ к выходу "+str2[CB_53_vyh->ItemIndex]);

  /*  if(comm_vhod(CB_53_vh->ItemIndex+4))  //1 -- ошибка, 0 -- без ошибок
           {
             ShowMessage("Не сработал коммутатор 1");
             goto end;
             }
     if(comm_vyhod(CB_53_vyh->ItemIndex))//1 -- ошибка, 0 -- без ошибок
            {
             ShowMessage("Не сработал коммутатор 2");
             goto end;
             }
  */           

        Chart3->Repaint();

        /* пакет 3*/
    for(i=0;i<=11;i++)
      {
      // US[i]=0x0;
       kod_att[i]=0xF;
      }
  //============/* формуляр задание кода выходных атт */====
   if(CB_53_vyh->ItemIndex<=11)
   {
    n_post=0;    /*ППС*/
    kod_att[CB_53_vyh->ItemIndex]= Q_vh[CB_53_att_vyh->ItemIndex];
   }
  if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
    kod_att[CB_53_vyh->ItemIndex-12]= Q_vh[CB_53_att_vyh->ItemIndex];/****?????****/
    }

   if((res=Vkl_att_t(n_post,kod_att))==1)   /*0-- нет ошибок, 1-- есть ошибки */
     {
      ShowMessage("Ошибка при передаче формуляра 3 данных в УП7 ERR=1!\n");
      //goto end;
     }
 if(res==2) {ShowMessage("Нет ответных пакетов на пакет 3!");}
           Sleep(1);


              /* пакет 1*/
//-----------------формуляр передачи данных в УП7 -------------------------------------------------------
 //============/* включение канала усилителя, включение источника питания УП7 */========================================            /* пакет 1*/
  //n_post=2+(CB_2_ps->ItemIndex);
  if(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
   {
    n_post=0;    /*ППС*/
    nu=(CB_53_vyh->ItemIndex);    /*индекс от 0 до 12*/  /* nu-- номер усилителя*/
    }
   if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
    nu=(CB_53_vyh->ItemIndex)-12;    /*индекс от 13 до 25*/  /* nu-- номер усилителя*/
    }
  // nu=0;  /* ???? nu-- nu=(номер усилителя*/

   if((res=Vkl_us_vip_t(n_post,nu))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных (1) в УП7!\n");
    // goto end;
    }
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");}
    Sleep(1);
 //*************************************************************************

     //  m_freqq = (double)CSE2->Value;
     //  Открываем сеанс на GPIB
     //  m_freqq = (double)CSE2->Value;

    m_freqq=F_rtu[UD53_f->Position+64];
   //m_freqq = strtod(E2_f->Text.c_str(),NULL);

   powerDBM = strtod(E53_p->Text.c_str(),NULL);

   K_nu = strtod(E_ks_53->Text.c_str(),NULL);
   if((K_nu>3.0)||(K_nu<0.0))
   {
    ShowMessage("Неверное значение константы насыщения");
    goto end;
   }

    K_nu=(3.0-K_nu)/4.0;

  for(k=64; k<=223;k++) /* определение ind*/
     {
      if(F_rtu[k]==m_freqq){ind=k;break;}
     }
  m_p_1=powerDBM-dPg[ind];   /* с учетом калибровки кабеля */

 /*15.12.10*/ //    power = -70.0;  //отладка

 // Установка на генератор частоты и мощности
 stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // частота
 stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // мощность
  if (stat != VI_SUCCESS)
  {
     ShowMessage("Ошибка при установке значений на генератор");
     goto end;
  }
 // viPrintf(vigen,"PULM:STAT OFF\n");   // ВКЛючить имп модуляцию
   viPrintf(viG,"OUTPut:STATe ON\n"); //подкл.  сигнала на выход ген-ра

    longdown=0;

    viPrintf(viG,"*OPC?\n");

        while(!longdown)
    viScanf(viG,"%d", &longdown);

    viPrintf(viP,"ABORT\n");
   viPrintf(viP,"INIT:CONT ON\n");
   viPrintf(viP,"FETC?\n");
   viScanf(viP,"%t",buf);

    Sleep(1);

    //  pn=-23.25;
   //  pv=0.0;
   //  pstep=0.75;
            /* пакет 2*/
    /*  сначала выключаем неиспользываемые номера выходов матрицы ПМ */
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение матрицы для  1-го и 2-го канала СВЧ */=========================
          n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/

  if(CB_53_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
      if(CB_53_vyh->ItemIndex>11) /* если выбран ППС, то выключаем ЗПС*/
           n_post=1; /*ЗПС*/   /* если выбран ППС, то выключаем ЗПС*/
           else  n_post=0;  nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           if(CB_53_vyh->ItemIndex<=11) /* если выбран ППС, то выключаем ЗПС*/
                 n_post=1;
           else  n_post=0; nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
         if(CB_53_vyh->ItemIndex<=11) /* если выбран ЗПС, то выключаем ППС*/
                 n_post=0;
           else  n_post=1;  nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
          if(CB_53_vyh->ItemIndex<=11) /* если выбран ЗПС, то выключаем ППС*/
              n_post=0;
           else  n_post=1; nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7!\n");
     //goto end;
    }

  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
   Sleep(1);

    pn=0x1F;
    pv=0x0;
    pstep=-0x1;  /* коды входного аттенюатора */

      vyh=true;

 for(m_p=pn,j=0; m_p>=pv; m_p+=pstep,j++) /* по мощности*/
  {
   // Application->ProcessMessages();
 //  if(vyh==false) goto end1;
                   /* пакет 2*/
 //============/* включение номера выхода матрицы ПМ для 1-ого и 2-ого канала */========================================
//============/* задание кода входных атт для 1-ого и 2-ого канала */==========================
   /* n_vh1 -- номер выхода матрицы для 1-ого канала СВЧ 0--0xF (4 разряда)*/
   /* n_vh2 -- номер выхода матрицы для 2-ого канала СВЧ 0--0xF (4 разряда)*/

       n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/
  if(CB_53_vh->ItemIndex==0){in1_at=Qv_vh[m_p];in2_at=0x1F;n_post=0;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[m_p];n_post=0;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=Qv_vh[m_p];in2_at=0x1F;n_post=1;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[m_p];n_post=1;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

   if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7 ERR=1!\n");
     goto end1;
    }

    /* Прием ответного пакета */
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
       Sleep(5);


    viPrintf(viP,"ABORT\n");
    viPrintf(viP,"INIT:CONT ON\n");
    viPrintf(viP,"FETC?\n");
    viScanf(viP,"%t",buf);

    m_Pow = atof(buf);
  //  m_Pow=m_Pow-dPm[ind]+30.0;   /*с учетом калибровки кабеля*/
   m_Pow=m_Pow-dPm[ind];   /*с учетом калибровки кабеля*/
    P_dB[j]=m_Pow;

        //  Pw=pow(10,Pdbm/10); //мВт       Pw=pow(10,-3)*pow(10,Pdbm/10);  //Вт

          m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

       /*    memset(&buf1,0,20);
           sprintf(buf1,"%.3f",m_Pow);

           E2_izm_m->Text=buf1;
           E2_izm_m->Repaint();
       */
           P[j]=m_Pow;  /* значение в Вт */
           x_m_p=Qvh_osl[j];

        /* чтение датчика мощности */
                   /* запрос кода мощности */
                         /* пакет 9*/
//-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//----------------Чтение уровня мощности для каналов усилителей------------------------------
 // if((CB_53_vh->ItemIndex==0)||(CB_53_vh->ItemIndex==1))
//   {
//  n_post=2; /*ППС*/
//   }
//  if((CB_53_vh->ItemIndex==2)||(CB_53_vh->ItemIndex==3))
//    {
//      n_post=3; /*ЗПС*/
//    }
 if(CB_53_vyh->ItemIndex<=11)  /* в зависимости от выхода */     {
     n_post=0; /**/
     }
  if(CB_53_vyh->ItemIndex>11)
     {
     n_post=1; /**/
     }
    nf=0x9;
 n_jj=0;

m_jj:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- нет ошибок, 1-- есть ошибки */
   {
     ShowMessage("Ошибка при передаче формуляра запроса данных (9) в УП7!\n");
    // 10.01.11 vyh=false; goto end;
   }

  Sleep(10);
//17.07 if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07        // Нет принятых пакетов
//17.07 //     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07   }

  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
//17.07        // Нет принятых пакетов
//17.07 //     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07      if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("Сбой по магистрале!");
//17.07       vyh=false; goto end; //goto m2_end_5;
//17.07      }
   }
   else
   {
        // Принят пакет

      LEN=packet_my_km.p_my_v.len;
      IPK=packet_my_km.p_my_v.byte1;
      SRC=packet_my_km.p_my_v.byte2&0x1F;
      DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* левое крыло DST=0x6, правое крыло DST=0x7*/
      IPS=(packet_my_km.p_my_v.byte3>>2)&0x3F;
      ERR=packet_my_km.p_my_v.byte4&0x1;
       /* ADR_UP7=packet_my_km.p_my_v.byte5;*/
      IPK_UP7=packet_my_km.p_my_v.byte5;
      ADC1=packet_my_km.p_my_v.byte6;
      ADC2=packet_my_km.p_my_v.byte7;
      ADC3=packet_my_km.p_my_v.byte8;
      ADC4=packet_my_km.p_my_v.byte9;
      ADC5=packet_my_km.p_my_v.byte10;
      ADC6=packet_my_km.p_my_v.byte11;
      ADC7=packet_my_km.p_my_v.byte12;
      ADC8=packet_my_km.p_my_v.byte13;
      ADC9=packet_my_km.p_my_v.byte14;
      ADC10=packet_my_km.p_my_v.byte15;
      ADC11=packet_my_km.p_my_v.byte16;
      ADC12=packet_my_km.p_my_v.byte17;
     // ADC13=packet_my_km.p_my_v.byte18;

// 22.12.10
     if(CB_53_vyh->ItemIndex<=11)  /* в зависимости от выхода */
       {
        if(CB_53_vyh->ItemIndex==0) ADC=ADC1&0xFF;
        if(CB_53_vyh->ItemIndex==1) ADC=ADC2&0xFF;
        if(CB_53_vyh->ItemIndex==2) ADC=ADC3&0xFF;
        if(CB_53_vyh->ItemIndex==3) ADC=ADC4&0xFF;
        if(CB_53_vyh->ItemIndex==4) ADC=ADC5&0xFF;
        if(CB_53_vyh->ItemIndex==5) ADC=ADC6&0xFF;
        if(CB_53_vyh->ItemIndex==6) ADC=ADC7&0xFF;
        if(CB_53_vyh->ItemIndex==7) ADC=ADC8&0xFF;
        if(CB_53_vyh->ItemIndex==8) ADC=ADC9&0xFF;
        if(CB_53_vyh->ItemIndex==9) ADC=ADC10&0xFF;
        if(CB_53_vyh->ItemIndex==10) ADC=ADC11&0xFF;
        if(CB_53_vyh->ItemIndex==11) ADC=ADC12&0xFF;
//        if(CB_10_vyh->ItemIndex==12) ADC=ADC13&0xFF;
      }
    if(CB_53_vyh->ItemIndex>11)  /* в зависимости от выхода */
      {
        if(CB_53_vyh->ItemIndex==12) ADC=ADC1&0xFF;
        if(CB_53_vyh->ItemIndex==13) ADC=ADC2&0xFF;
        if(CB_53_vyh->ItemIndex==14) ADC=ADC3&0xFF;
        if(CB_53_vyh->ItemIndex==15) ADC=ADC4&0xFF;
        if(CB_53_vyh->ItemIndex==16) ADC=ADC5&0xFF;
        if(CB_53_vyh->ItemIndex==17) ADC=ADC6&0xFF;
        if(CB_53_vyh->ItemIndex==18) ADC=ADC7&0xFF;
        if(CB_53_vyh->ItemIndex==19) ADC=ADC8&0xFF;
        if(CB_53_vyh->ItemIndex==20) ADC=ADC9&0xFF;
        if(CB_53_vyh->ItemIndex==21) ADC=ADC10&0xFF;
        if(CB_53_vyh->ItemIndex==22) ADC=ADC11&0xFF;
        if(CB_53_vyh->ItemIndex==23) ADC=ADC12&0xFF;
       // if(CB_10_vyh->ItemIndex==24) ADC=ADC13&0xFF;
       // if(CB_10_vyh->ItemIndex==25) ADC=ADC13&0xFF;
      }

        if(ERR==1)
         {
          //ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении кода мощности! ERR=1");
          //goto m1;
           n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj;
            }
          else
            {
             ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении кода мощности! ERR=1");
             goto m1_1;
            }
          }

         Kod_DM_izm[j]=ADC;
         Kod_M[j]=0.017*ADC;


         /*  memset(&buf1,0,20);
           sprintf(buf1,"%d",ADC);

           E_2_um->Text=buf1;
           E_2_um->Repaint();
         */
       m1_1:;
     }
//    m2_end_5:;
 //   m2_end_3:;
 //====================================
          //Sleep(10);
        Series[3]->AddXY(x_m_p,P[j]);
        Series[3]->Repaint();

        Series[0]->AddXY(x_m_p,Kod_M[j]);
        Series[0]->Repaint();

          Chart3->Repaint();
       // LineSeries6->Repaint();

   }    /* end for */

/*     for(k=0;k<=31;k++)
       {
         x_m_p=Qvh_osl[k];
         Series[3]->AddXY(x_m_p,P[k]);
       }
     for(k=0;k<=31;k++)
       {
         x_m_p=Qvh_osl[k];
        Series[0]->AddXY(x_m_p,Kod_M[k]);

       }
  */
   for(k1=0,P_max=P[0]; k1<=31; k1+=1)  /* вычисление max на кривой */
       {
        if(P[k1]>P_max) {P_max=P[k1];k_max=k1;}
       }
      memset(&buf1,0,20);
        sprintf(buf1,"%.2f",P_max);
           E53_pmx_1->Text=buf1;
           E53_pmx_1->Repaint();

      memset(&buf1,0,20);
     sprintf(buf1,"%.2f",Qvh_osl[k_max]);
           E53_kd_1->Text=buf1;
           E53_kd_1->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%d",Kod_DM_izm[k_max]);

           E53_dm_2->Text=buf1;
           E53_dm_2->Repaint();

        mk=0;
    for(k=1; k<=31; k+=1)
//     for(k=31; k>=1; k-=1)
//      for(k=k_max; k>=1; k-=1)  /* поиск от максимума вниз */
       {
      //  dP=fabs(P_dB[k]-P_dB[k-5]);

         dP=fabs(P_dB[k]-P_dB[k-1]);
       // if(dP<0.25)
          if(dP<K_nu)
        //  if(dP>K_nu)
            {
             P_1=P_dB[k];
             p_vt_izm=P[k];
             k_att=k;
             mk=mk+1;
            /* P_1=P_dB[k-1];
             p_vt_izm=P[k-1];
             k_att=k-1;
            */
            // if((P_1<-20.0)&&(k<31)) goto m1;     /* дБм */
            if((p_vt_izm<0.2)&&(k<31)) goto m1;  /* Вт*/
             if(mk==3)goto end2;
           }
        m1:;
       }

     end2:;
         if(P_1>-20.0)
           {
        //   sprintf(buf1,"%.2f",P_1);

            memset(&buf1,0,20);
           sprintf(buf1,"%.2f",p_vt_izm);
           Ep53_max->Text=buf1;
           Ep53_max->Repaint();

            memset(&buf1,0,20);
           sprintf(buf1,"%.2f",Qvh_osl[k_att]);
           E53_max_ka->Text=buf1;
           E53_max_ka->Repaint();

           memset(&buf1,0,20);
           sprintf(buf1,"%d",Kod_DM_izm[k_att]);

           E53_km_s->Text=buf1;
           E53_km_s->Repaint();
          }
   else  L53_pmax_no->Caption="Усилитель не калибруется";
    // for(k1=0,P_max=P[0]; k1<=31; k1+=1)
    //   {
    //    if(P[k1]>P_max) {P_max=P[k1];k_max=k1;}
    //   }
    //      memset(&buf1,0,20);
    //    sprintf(buf1,"%.2f",P_max);
    //       E_pmx_1->Text=buf1;
    //       E_pmx_1->Repaint();

    //  memset(&buf1,0,20);
    // sprintf(buf1,"%.2f",Qvh_osl[k_max]);
    //       E_kd_1->Text=buf1;
    //       E_kd_1->Repaint();

    //    memset(&buf1,0,20);
    //    sprintf(buf1,"%d",Kod_DM_izm[k_max]);

    //       E_dm_2->Text=buf1;
    //       E_dm_2->Repaint();


    for(k1=0,Kod_DM_max=Kod_DM_izm[0]; k1<=31; k1+=1)
       {
//         dP=fabs(P[k]-P[k-1]);
         if(Kod_DM_izm[k1]>Kod_DM_max) {Kod_DM_max=Kod_DM_izm[k1];k_max=k1;}
       }

           memset(&buf1,0,20);
           sprintf(buf1,"%d",Kod_DM_max);

           E53_km_mx->Text=buf1;
           E53_km_mx->Repaint();

           memset(&buf1,0,20);
           sprintf(buf1,"%.2f",Qvh_osl[k_max]);
           E53_kdm_1->Text=buf1;
           E53_kdm_1->Repaint();
  //=============0.25 =======
   /* for(k=1; k<=31; k+=1)
       {
        dP=fabs(P_dB[k]-P_dB[k-1]);
        if(dP<0.25)
            {
             P_1=P_dB[k];
             p_vt_izm=P[k];
             k_att=k;
             if((P_1<-20.0)&&(k<31)) goto m1_2;
             goto end2_2;
           }
        m1_2:;
       }

     end2_2:;
         if(P_1>-20.0)
           {
           sprintf(buf1,"%.2f",p_vt_izm);
           E_1r->Text=buf1;
           E_1r->Repaint();

           sprintf(buf1,"%.2f",Qvh_osl[k_att]);
           E_2r->Text=buf1;
           E_2r->Repaint();
          }
   else  L_pmax_no->Caption="Усилитель не калибруется";
 */
  //========================

   end1:;                         /* пакет 2 */
 //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение м атрицы для  1-го и 2-го канала СВЧ */=========================
          n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/

  if(CB_53_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;n_post=0;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;n_post=0;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;n_post=1;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;n_post=1;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7 ERR=1!\n");
     //goto end;
    }
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
     Sleep(1);
                         /* пакет 1*/
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение канала усилителя, выключение источника питания УП7 */=========================
 if(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
   {
    n_post=0;    /*ППС*/
   // nu=(CB_10_vyh->ItemIndex);    /*индекс от 0 до 12*/  /* nu-- номер усилителя*/
    }
   if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
   // nu=12-(CB_53_vyh->ItemIndex);    /*индекс от 13 до 25*/  /* nu-- номер усилителя*/
    }
  // nu=0;  /* ???? nu-- nu=(номер усилителя*/

   if((res=Vykl_us_vip_t(n_post))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных (1) в УП7 ERR=1!\n");
    // goto end;
    }
    if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");}
    Sleep(1);
   end:;
  viPrintf(viG,"OUTPut:STATe OFF\n"); //выкл. сигнала на выход ген-ра

  /*15.12.10*/ //   for(k=1; k<=24; k++)
  /*15.12.10*/ //     {
  /*15.12.10*/ //       dP=fabs(P[k]-P[k-1]);
  /*15.12.10*/ //       if(dP<1.0)
  /*15.12.10*/ //          {
  /*15.12.10*/ //           P_1=P[k];
  /*15.12.10*/ //           if((P_1<-30.0)&&(k<24)) goto m1;
  /*15.12.10*/ //           goto end1;
   /*15.12.10*/ //         }
   /*15.12.10*/ //      m1:;
   /*15.12.10*/ //    }

   /*15.12.10*/ // end1:;
   /*15.12.10*/ //        if(P_1>-30.0)
   /*15.12.10*/ //        {
   /*15.12.10*/ //        sprintf(buf1,"%.2f",P_1);
   /*15.12.10*/ //        E_pmax->Text=buf1;
   /*15.12.10*/ //        E_pmax->Repaint();
   /*15.12.10*/ //        }
   /*15.12.10*/ //        else  L_pmax_no->Caption="Усилитель не калибруется";

    ShowMessage("Измерение закончено\n");

}
//---------------------------------------------------------------------------
void __fastcall TForm1::B53_tablClick(TObject *Sender)
{if(ChkDevs==true)
 {
//  P_6->Visible=true;
  Tabl53OutChn();
  }
  else
  {
 if(FindDevises()==true)
  {
  if(ChekDev()==true)
  {
 // P_6->Visible=true;
  Tabl53OutChn();
    }
  }    //FindDevises()
 }//else
}
//---------------------------------------------------------------------------
//-----   Заполнение таблицы --------------------------------
void TForm1::Tabl53OutChn(void)
{
 P_7->Visible=true;
 tabl53_visble_chten();
}
//-----  вызов таблицы, чтение из файла  --------------------------------
void TForm1::tabl53_visble_chten(void)
{
 extern double F_rtu[224];
 FILE *tr;
 String str;
 AnsiString str1[4]={"Вход 1ВЧ-53","Вход 2ВЧ-53","Вход 3ВЧ-53","Вход 4ВЧ-53"};
 AnsiString str2[24]={"Выход ППС-1","Выход ППС-2","Выход ППС-3","Выход ППС-4",
                       "Выход ППС-5","Выход ППС-6","Выход ППС-7","Выход ППС-8",
                       "Выход ППС-9","Выход ППС-10","Выход ППС-11","Выход ППС-12",
                       "Выход ЗПС-1","Выход ЗПС-2","Выход ЗПС-3","Выход ЗПС-4",
                       "Выход ЗПС-5","Выход ЗПС-6","Выход ЗПС-7","Выход ЗПС-8",
                       "Выход ЗПС-9","Выход ЗПС-10","Выход ЗПС-11","Выход ЗПС-12"};

 int k,j,n_us;
// int kod_fpch;
 float P_izm[12][8][160]={0.0},osl[12][8][160]={0.0};
 int kad_acp[12][8][160]={0},k_f[160]={0};

 str=E53_fd->Text;

if((tr = fopen(str.c_str(),"r+")) == NULL)
  {
  ShowMessage("Нет файла");
  goto m1;
 }
 /* сначала чтение из файла */
   for(n_us=0;n_us<=11;n_us++)
    {
     for(k=0;k<=159;k++)
       {
        fscanf(tr,"%d",&k_f[k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][0][k],&osl[n_us][0][k], &kad_acp[n_us][0][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][1][k],&osl[n_us][1][k], &kad_acp[n_us][1][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][2][k],&osl[n_us][2][k], &kad_acp[n_us][2][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][3][k],&osl[n_us][3][k], &kad_acp[n_us][3][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][4][k],&osl[n_us][4][k], &kad_acp[n_us][4][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][5][k],&osl[n_us][5][k], &kad_acp[n_us][5][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][6][k],&osl[n_us][6][k], &kad_acp[n_us][6][k]);
        fscanf(tr,"%f%f%d\n",&P_izm[n_us][7][k],&osl[n_us][7][k],&kad_acp[n_us][7][k]);
      } /* end k*/
    } /* end n_us */
  fclose(tr);

  Label49->Caption="Таблица выходных мощностей и кодов входных аттенюторов "+str1[CB_53_vh->ItemIndex]+"  "
  +str2[CB_53_vyh->ItemIndex];

   PostMessage(SG_53->Handle, WM_MBUTTONDOWN, MK_LBUTTON,0);
   PostMessage(SG_53->Handle, WM_MBUTTONUP, MK_LBUTTON,0);

        /* очистить таблицу*/
  for(k=1;k<=160;k++)    /* строка  */
   for(j=1;j<=24;j++)   /* столбец  */
     {
     SG_53->Cells[j][k]=" ";
     }

   for(k=64;k<=223;k++)    /* строка  */   /*?????*/
   SG_53->Cells[0][k-64]=FloatToStr(F_rtu[k]);

        /* вывести в таблицу */
    n_us=CB_53_vyh->ItemIndex;

     for(k=0;k<=159;k++)
      {
                         /* Луч 1 */
        SG_53->Cells[1][k]=FloatToStrF(P_izm[n_us][0][k],ffGeneral,3,2);
        SG_53->Cells[2][k]=FloatToStrF(osl[n_us][0][k],ffGeneral,4,2);
      //  SG_53->Cells[3][k]=FloatToStrF(kad_acp[n_us][0][k],ffGeneral,3,2);
        SG_53->Cells[3][k]=IntToStr(kad_acp[n_us][0][k]);
                         /* Луч 2 */
        SG_53->Cells[4][k]=FloatToStrF(P_izm[n_us][1][k],ffGeneral,3,2);
        SG_53->Cells[5][k]=FloatToStrF(osl[n_us][1][k],ffGeneral,4,2);
       // SG_53->Cells[6][k]=FloatToStrF(kad_acp[n_us][1][k],ffGeneral,3,2);
        SG_53->Cells[6][k]=IntToStr(kad_acp[n_us][1][k]);
                           /* Луч 3*/
        SG_53->Cells[7][k]=FloatToStrF(P_izm[n_us][2][k],ffGeneral,3,2);
        SG_53->Cells[8][k]=FloatToStrF(osl[n_us][2][k],ffGeneral,4,2);
      //  SG_53->Cells[9][k]=FloatToStrF(kad_acp[n_us][2][k],ffGeneral,3,2);
        SG_53->Cells[9][k]=IntToStr(kad_acp[n_us][2][k]);
                           /* Луч 4 */
        SG_53->Cells[10][k]=FloatToStrF(P_izm[n_us][3][k],ffGeneral,3,2);
        SG_53->Cells[11][k]=FloatToStrF(osl[n_us][3][k],ffGeneral,4,2);
      //  SG_53->Cells[12][k]=FloatToStrF(kad_acp[n_us][3][k],ffGeneral,3,2);
        SG_53->Cells[12][k]=IntToStr(kad_acp[n_us][3][k]);
                           /* Луч 5 */
        SG_53->Cells[13][k]=FloatToStrF(P_izm[n_us][4][k],ffGeneral,3,2);
        SG_53->Cells[14][k]=FloatToStrF(osl[n_us][4][k],ffGeneral,4,2);
      //  SG_53->Cells[15][k]=FloatToStrF(kad_acp[n_us][4][k],ffGeneral,3,2);
         SG_53->Cells[15][k]=IntToStr(kad_acp[n_us][4][k]);
                             /* Луч 6 */
        SG_53->Cells[16][k]=FloatToStrF(P_izm[n_us][5][k],ffGeneral,3,2);
        SG_53->Cells[17][k]=FloatToStrF(osl[n_us][5][k],ffGeneral,4,2);
      //  SG_53->Cells[18][k]=FloatToStrF(kad_acp[n_us][5][k],ffGeneral,3,2);
         SG_53->Cells[18][k]=IntToStr(kad_acp[n_us][5][k]);
                               /* Луч 7 */
        SG_53->Cells[19][k]=FloatToStrF(P_izm[n_us][6][k],ffGeneral,3,2);
        SG_53->Cells[20][k]=FloatToStrF(osl[n_us][6][k],ffGeneral,4,2);
    //   SG_53->Cells[21][k]=FloatToStrF(kad_acp[n_us][6][k],ffGeneral,3,2);
        SG_53->Cells[21][k]=IntToStr(kad_acp[n_us][6][k]);
                               /* Луч 8 */
        SG_53->Cells[22][k]=FloatToStrF(P_izm[n_us][7][k],ffGeneral,3,2);
        SG_53->Cells[23][k]=FloatToStrF(osl[n_us][7][k],ffGeneral,4,2);
       // SG_53->Cells[24][k]=FloatToStrF(kad_acp[n_us][7][k],ffGeneral,3,2);
        SG_53->Cells[24][k]=IntToStr(kad_acp[n_us][7][k]);

     } /* end k*/
 m1:;
}
//------------------Пуск---------------------------------------------------------
void __fastcall TForm1::Button29Click(TObject *Sender)
{
 tabl53_visble();
}
//-----  измерение таблицы --------------------------------
void TForm1::tabl53_visble(void)
{
 int j,k;

  AnsiString str1[4]={"Вход 1ВЧ-53","Вход 2ВЧ-53","Вход 3ВЧ-53","Вход 4ВЧ-53"};
  AnsiString str2[24]={"Выход ППС-1","Выход ППС-2","Выход ППС-3","Выход ППС-4",
                       "Выход ППС-5","Выход ППС-6","Выход ППС-7","Выход ППС-8",
                       "Выход ППС-9","Выход ППС-10","Выход ППС-11","Выход ППС-12",
                       "Выход ЗПС-1","Выход ЗПС-2","Выход ЗПС-3","Выход ЗПС-4",
                       "Выход ЗПС-5","Выход ЗПС-6","Выход ЗПС-7","Выход ЗПС-8",
                       "Выход ЗПС-9","Выход ЗПС-10","Выход ЗПС-11","Выход ЗПС-12"};


   extern bool vyh;
  ViStatus stat=0; // объявление переменной типа ViStatus
  extern double F_rtu[224];
  //extern int Q[4][64]; /* массив измеренных значений кодов входных атт. */

  //extern unsigned AT_1[4][64],AT_2[4][64],AT_3[4][64],AT_4[4][64],AT_5[4][64],AT_6[4][64],
  //       AT_7[4][64],AT_8[4][64],AT_9[4][64],AT_10[4][64],AT_11[4][64],
  //       AT_12[4][64],AT_13[4][64];  /* аттенюаторы выходных усилит. передатчика */
  //extern unsigned IN_AT[4][64];  /* аттенюатор выбранного входа */

//  extern unsigned AT_1_53[8][160],AT_2_53[8][160],AT_3_53[8][160],AT_4_53[8][160],
//         AT_5_53[8][160],AT_6_53[8][160],AT_7_53[8][160],AT_8_53[8][160],
//         AT_9_53[8][160],AT_10_53[8][160],AT_11_53[8][160],AT_12_53[8][160],
//         AT_13_53[8][160];  /* аттенюаторы выходных усилит. передатчика литера 53*/
// extern unsigned IN_AT_53[8][160];  /* аттенюатор выбранного входа литера 53*/

   double powerDBM=0.0;
   double m_freqq;
   double power;

   double K_nu=0.0;

 //char buf1[256]={0};
// char buf2[256]={0};

 char buf[256]={0};

// double m_freqq_n;
 //double m_freqq_v;

 // double P[35]={0.0};       /*измеренное значение в Вт*/
 // double P_dB[35]={0.0};    /*измеренное значение в дБ*/

//  double P_1=0.0;
//  double dP;
//  double p_vt_izm=0.0;

  float P[35]={0.0};       /*измеренное значение в Вт*/
  float P_dB[35]={0.0};    /*измеренное значение в дБ*/

  float P_1=0.0;
  float dP;
  float p_vt_izm=0.0;

  //int num=0;
 //char rdbuffer[256]={0};

 int ind; //индекс доступа к массивам калибровки
 long longdown=0; /* ожидание операции завершения*/

 int m_p;
 float x_m_p;
 double m_p_1;  /* мощность, задаваемая на генераторе*/
 int pn;
 int pv;
 int pstep;
 int k_att=0;

 unsigned ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8,ADC9,ADC10,ADC11,ADC12,ADC13=0x0;
  int ADC=0;
  int nf;

 double m_Pow;
 //double P_max;

  float P_max;
// char buf1[256]={0};
  int n_post;
  unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
  int nk,nu,n_us;//,n_us_n,n_us_v;  /* номер КИО*/
                                  /* входной атт */
  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/
/* float Qvh_osl[32]={0.0,-0.75,-1.5,-2.25,-3.0,-3.75,-4.5,-5.25,-6.0,
                     -6.75,-7.5,-8.25,-9.0,-9.75,-10.5,-11.25,-12.0,
                     -12.75,-13.5,-14.25,-15.0,-15.75,-16.5,-17.25,-18.0,
                     -18.75,-19.5,-20.25,-21.0,-21.75,-22.5,-23.25};
*/
                  /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/
 float Qvh_osl[32]={-23.25,-22.5,-21.75,-21.0,-20.25,-19.5,-18.75,-18.0,
                     -17.25,-16.5,-15.75,-15.0,-14.25,-13.5,-12.75,-12.0,
                     -11.25,-10.5,-9.75,-9.0,-8.25,-7.5,-6.75,-6.0,-5.25,
                     -4.5,-3.75,-3.0,-2.25,-1.5,-0.75,0.0};

                     /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/


  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* выходной атт 4 разряда*/
  float Q_vh_zn[16]={0.0,-0.75,-1.5,-2.25,-3.0,-3.75,-4.5,-5.25,-6.0,
                     -6.75,-7.5,-8.25,-9.0,-9.75,-10.5,-11.25};     /* выходной атт 4 разряда*/
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned kod_att[12];
  int k_f,nl,jk,n_jj,k2,nl_n,nl_v;
  //int ret=0;
  int k1,k_max=0;
  int kod_att_izm=0;
  int mk=0;


  unsigned IPK_UP7;
  u32 buf_my[256/4]; // Буфер для принятого пакета

  union{
       struct{
                  U32   len     : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8,
                        byte5   : 8;
              } p_my_v;
             U32 buf_my[256/4];
             } packet_my;

 union{
       struct{
                  U32   len     : 8, /*LEN*/
                        byte1   : 8, /*IPK*/
                        byte2   : 8, /*DST SRC*/
                        byte3   : 8, /*IPS DST*/
                        byte4   : 8, /*ERR*/
                        /*byte5   : 8,*/  /*ADR_UP7*/
                        byte5   : 8, /*IPK_UP7*/
                        byte6   : 8, /*ADC1 */
                        byte7   : 8, /*ADC2 */
                        byte8   : 8, /*ADC3 */
                        byte9   : 8, /*ADC4 */
                        byte10  : 8, /*ADC5 */
                        byte11  : 8, /*ADC6 */
                        byte12  : 8, /*ADC7 */
                        byte13  : 8, /*ADC8 */
                        byte14  : 8, /*ADC9 */
                        byte15  : 8, /*ADC10 */
                        byte16  : 8, /*ADC11 */
                        byte17  : 8; /*ADC12 */
                      //  byte18  : 8; /*ADC13 */

                        } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;

  K_nu = strtod(E_ks_53->Text.c_str(),NULL);
   if((K_nu>3.0)||(K_nu<0.0))
   {
    ShowMessage("Неверное значение константы насыщения");
    goto end;
   }

    K_nu=(3.0-K_nu)/4.0;

 PostMessage(SG_53->Handle, WM_MBUTTONDOWN, MK_LBUTTON,0);
 PostMessage(SG_53->Handle, WM_MBUTTONUP, MK_LBUTTON,0);

 Label54->Caption="                        "; /* усилитель не калибруется */

/********************/
  if(CB_53_vyh->ItemIndex<=11)
    {
   //  n_us_n=CB_10_vyh->ItemIndex;
   //  n_us_v=CB_10_vyh->ItemIndex;
     n_us=CB_53_vyh->ItemIndex;
    }
  if(CB_53_vyh->ItemIndex>11)
    {
   //  n_us_n=13-CB_10_vyh->ItemIndex;
   //  n_us_v=13-CB_10_vyh->ItemIndex;
     n_us=CB_53_vyh->ItemIndex-12;
    }
 //   Label49->Caption="Таблица выходных мощностей и кодов входных аттенюторов "+str1[CB_53_vh->ItemIndex]+"  "
//   +str2[CB_53_vyh->ItemIndex];
      for(k=0; k<=34; k++)
        {
         P[k]=0;
        }

        ShowMessage("Подать сигнал с ВЧ генератора на вход "+str1[CB_53_vh->ItemIndex]);
        ShowMessage("Подключить измеритель мощности через аттенюатор 30дБ к выходу "+str2[CB_53_vyh->ItemIndex]);

 /*  if(comm_vhod(CB_53_vh->ItemIndex+4))  //1 -- ошибка, 0 -- без ошибок
           {
             ShowMessage("Не сработал коммутатор 1");
             goto end;
             }
     if(comm_vyhod(CB_53_vyh->ItemIndex))//1 -- ошибка, 0 -- без ошибок
            {
             ShowMessage("Не сработал коммутатор 2");
             goto end;
             }
  */           
     //  vyh=true;
 if(CB_53_vyh->ItemIndex<=11)
   {
    n_post=0;    /*ППС*/
   // L2_1->Caption="|           Луч 1";
   // L2_2->Caption="|           Луч 2";
   // L2_3->Caption="|           Луч 3";
   // L2_4->Caption="|           Луч 4                             |";
    nl_n=0;nl_v=7;
   }
  if(CB_10_vyh->ItemIndex>11)
   {
    n_post=1;    /*ЗПС*/
    //L2_1->Caption="|           Луч 5";
    //L2_2->Caption="|           Луч 6";
    //L2_3->Caption="|           Луч 7";
    //L2_4->Caption="|           Луч 8                             |";
    nl_n=0; nl_v=7;
  }

 for(nl=nl_n;nl<=nl_v;nl++)   /* цикл по номеру луча*/
  {
   if((nl==0)&&(CheckBox1->Checked==false)) goto end_luch;
   if((nl==1)&&(CheckBox2->Checked==false)) goto end_luch;
   if((nl==2)&&(CheckBox3->Checked==false)) goto end_luch;
   if((nl==3)&&(CheckBox4->Checked==false)) goto end_luch;
   if((nl==4)&&(CheckBox5->Checked==false)) goto end_luch;
   if((nl==5)&&(CheckBox6->Checked==false)) goto end_luch;
   if((nl==6)&&(CheckBox7->Checked==false)) goto end_luch;
   if((nl==7)&&(CheckBox8->Checked==false)) goto end_luch;


      /* пакет 3*/
    for(i=0;i<=11;i++)
      {
      // US[i]=0x0;
       kod_att[i]=0xF;
      }
        /*  сначала выключаем неиспользываемые номера выходов матрицы ПМ */
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение матрицы для  1-го и 2-го канала СВЧ */=========================
          n_vh1=nl; n_vh2=nl;  /* от 0 до 7*/

  if(CB_53_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
      if(CB_53_vyh->ItemIndex>11) /* если выбран ППС, то выключаем ЗПС*/
           n_post=1; /*ЗПС*/   /* если выбран ППС, то выключаем ЗПС*/
           else  n_post=0;  nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           if(CB_53_vyh->ItemIndex<=11) /* если выбран ППС, то выключаем ЗПС*/
                 n_post=1;
           else  n_post=0; nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
         if(CB_53_vyh->ItemIndex<=11) /* если выбран ЗПС, то выключаем ППС*/
                 n_post=0;
           else  n_post=1;  nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
          if(CB_53_vyh->ItemIndex<=11) /* если выбран ЗПС, то выключаем ППС*/
              n_post=0;
           else  n_post=1; nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7!\n");
     goto m_otl;
    // goto end;
    }

  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");goto m_otl;}
   Sleep(1);

  //============/* формуляр задание кода выходных атт */====

  if(CB_53_vyh->ItemIndex<=11)
   {
    n_post=0;    /*ППС*/
   /* один усилитель */
    kod_att[CB_53_vyh->ItemIndex]= Q_vh[CB_53_att_vyh->ItemIndex];
    }
  if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
    kod_att[CB_53_vyh->ItemIndex-12]= Q_vh[CB_53_att_vyh->ItemIndex];
  }

if((res=Vkl_att_t(n_post,kod_att))==1)   /*0-- нет ошибок, 1-- есть ошибки */
     {
      ShowMessage("Ошибка при передаче пакета 3 ERR=1");
     // goto end;
     goto m_otl;
     }
 if(res==2) {ShowMessage("Нет ответных пакетов на пакет 3!");goto m_otl;}
                 /* пакет 1*/
//-----------------формуляр передачи данных в УП7 -------------------------------------------------------
 //============/* включение канала усилителя, включение источника питания УП7 */========================================            /* пакет 1*/
 if(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
   {
    n_post=0;    /*ППС*/
  //  nu=(CB_10_vyh->ItemIndex);    /*индекс от 0 до 12*/  /* nu-- номер усилителя*/
  }
   if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
 //   nu=13-(CB_10_vyh->ItemIndex);    /*индекс от 13 до 25*/  /* nu-- номер усилителя*/
    }
   nu=n_us;  /* n_us= nu=(номер усилителя*/

  if((res=Vkl_us_vip_t(n_post,nu))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче пакета 1 в УП7 ERR=1!\n");
 //  goto end;
    goto m_otl;
    }
   if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");goto m_otl;}

     Sleep(1);
//*************************************************************************

     //  Открываем сеанс на GPIB
  powerDBM = strtod(E53_p->Text.c_str(),NULL);

  vyh=true;

 for(k_f=64; k_f<=223; k_f++) /* по частоте*/
  {
    Application->ProcessMessages();
      // if(vyh==false) goto m_otl;
    if(vyh==false) goto end; /* конец измерений */
     m_freqq=F_rtu[k_f];
   //m_freqq = strtod(E2_f->Text.c_str(),NULL);

  for(k=64; k<=223;k++) /* определение ind*/
   {
   if(F_rtu[k]==m_freqq){ind=k;break;}
    }
    m_p_1=powerDBM-dPg[ind];   /* с учетом калибровки кабеля */

 /*15.12.10*/ //    power = -70.0;  //отладка

 // Установка на генератор частоты и мощности
 stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // частота
 stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // мощность
  if (stat != VI_SUCCESS)
  {
     ShowMessage("Ошибка при установке значений на генератор");
     goto end;
  }
 // viPrintf(vigen,"PULM:STAT OFF\n");   // ВКЛючить имп модуляцию
   viPrintf(viG,"OUTPut:STATe ON\n"); //подкл.  сигнала на выход ген-ра

    longdown=0;

    viPrintf(viG,"*OPC?\n");

        while(!longdown)
    viScanf(viG,"%d", &longdown);

    viPrintf(viP,"ABORT\n");
   viPrintf(viP,"INIT:CONT ON\n");
   viPrintf(viP,"FETC?\n");
   viScanf(viP,"%t",buf);

    Sleep(1);

    //  pn=-23.25;
   //  pv=0.0;
   //  pstep=0.75;

    pn=0x1F;
    pv=0x0;
    pstep=-0x1;  /* коды входного аттенюатора */

//      vyh=true;

 for(m_p=pn,j=0; m_p>=pv; m_p+=pstep,j++) /* по мощности*/
  {
  // Application->ProcessMessages();
 //  if(vyh==false) goto end1;

                   /* пакет 2*/
//============/* включение номера выхода матрицы ПМ для 1-ого и 2-ого канала */========================================
//============/* задание кода входных атт для 1-ого и 2-ого канала */==========================
   /* n_vh1 -- номер выхода матрицы для 1-ого канала СВЧ 0--0xF (4 разряда)*/
   /* n_vh2 -- номер выхода матрицы для 2-ого канала СВЧ 0--0xF (4 разряда)*/

       n_vh1= nl; n_vh2=nl;  /* от 0 до 7 -- здесь от 0 до 3*/
  if(CB_53_vh->ItemIndex==0){in1_at=Qv_vh[m_p];in2_at=0x1F;n_post=0;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[m_p];n_post=0;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=Qv_vh[m_p];in2_at=0x1F;n_post=1;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[m_p];n_post=1;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче пакета 2 в УП7 ERR=1!\n");
//     goto end1_v;
     goto m_otl;
    }

   /* Прием ответного пакета */
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");goto m_otl;}

     Sleep(1);

    viPrintf(viP,"ABORT\n");
    viPrintf(viP,"INIT:CONT ON\n");
    viPrintf(viP,"FETC?\n");
    viScanf(viP,"%t",buf);

    m_Pow = atof(buf);
//    m_Pow=m_Pow-dPm[ind]+30.0;   /*с учетом калибровки кабеля*/
    m_Pow=m_Pow-dPm[ind];   /* 10.02.2011 с учетом калибровки кабеля*/
    P_dB[j]=m_Pow;

        //  Pw=pow(10,Pdbm/10); //мВт       Pw=pow(10,-3)*pow(10,Pdbm/10);  //Вт

          m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

       /*    memset(&buf1,0,20);
           sprintf(buf1,"%.3f",m_Pow);

           E2_izm_m->Text=buf1;
           E2_izm_m->Repaint();
       */
           P[j]=m_Pow;  /* значение в Вт */
           x_m_p=Qvh_osl[j];

   }    /* end for */

/***** 10.01.2011 */
if(RG_53_11->ItemIndex==0) /* P 2 дБ сжат. */
  {
    mk=0;  /*15.03.11*/
    for(k=1; k<=31; k+=1)
       {
        dP=fabs(P_dB[k]-P_dB[k-1]);
  //      if(dP<0.25)
         if(dP<K_nu)
            {
             P_1=P_dB[k];
             p_vt_izm=P[k];
             k_att=k;
             mk=mk+1;/*15.03.11*/

           //  if((p_vt_izm<0.5)&&(k<31)) goto m11;
             if((p_vt_izm<0.1)&&(k<31)) goto m11;
             if(mk==3) goto end2; /*15.03.11*/
           }
        m11:;
       }

     end2:;
    //  if(p_vt_izm>0.5)
     if(p_vt_izm>0.1)
       {
         if(CB_53_vyh->ItemIndex<=11)
          {
          //sprintf(buf1,"%.2f",p_vt_izm);
          //SG_9->Cells[3*nl+1][k_f]=FloatToStrF(p_vt_izm,ffGeneral,3,2);
           SG_53->Cells[3*nl+1][k_f-64]=CurrToStrF(p_vt_izm,ffFixed,2);
           SG_53->Repaint();

         // sprintf(buf1,"%.2f",Qvh_osl[k_att]);
        //  SG_9->Cells[3*nl+2][k_f]=FloatToStrF(Qvh_osl[k_att],ffGeneral,3,2);
         SG_53->Cells[3*nl+2][k_f-64]=CurrToStrF(Qvh_osl[k_att],ffFixed,2);
         SG_53->Repaint();
         }
        if(CB_53_vyh->ItemIndex>11)
          {
         // sprintf(buf1,"%.2f",p_vt_izm);
         // SG_9->Cells[3*(nl-4)+1][k_f]=FloatToStrF(p_vt_izm,ffGeneral,3,2);
          SG_53->Cells[3*(nl-4)+1][k_f-64]=CurrToStrF(p_vt_izm,ffFixed,2);
          SG_53->Repaint();

         // sprintf(buf1,"%.2f",Qvh_osl[k_att]);
         // SG_9->Cells[3*(nl-4)+2][k_f]=FloatToStrF(Qvh_osl[k_att],ffGeneral,3,2);
          SG_53->Cells[3*(nl-4)+2][k_f-64]=CurrToStrF(Qvh_osl[k_att],ffFixed,2);
          SG_53->Repaint();
         }

         // Q[nl][k_f]=Qv_vh[31-k_att];  /* для массива рабочих точек */
          kod_att_izm=k_att;
      }
    else
      {
        Label54->Caption="Усилитель не калибруется";

       if(CB_53_vyh->ItemIndex<=11)
          {
          SG_53->Cells[3*nl+3][k_f-64]=IntToStr(0);/* изменить!!!*/
          SG_53->Repaint();
          SG_53->Cells[3*nl+1][k_f-64]=IntToStr(0);
          SG_53->Repaint();
          SG_53->Cells[3*nl+2][k_f-64]=IntToStr(0);
          SG_53->Repaint();
          }
       if(CB_53_vyh->ItemIndex>11)
          {
          SG_53->Cells[3*(nl-4)+3][k_f-64]=IntToStr(0);/* изменить!!!*/
          SG_53->Repaint();
          SG_53->Cells[3*(nl-4)+1][k_f-64]=IntToStr(0);
          SG_53->Repaint();
          SG_53->Cells[3*(nl-4)+2][k_f-64]=IntToStr(0);
          SG_53->Repaint();
          }

        goto  m2_end_5_v;
      }
}/*if 0*/

  if(RG_53_11->ItemIndex==1) /* по Р мах */
  {
    for(k1=0,P_max=P[0]; k1<=31; k1+=1)
       {

         if(P[k1]>P_max) {P_max=P[k1];k_max=k1;}
       }
      if(CB_53_vyh->ItemIndex<=11)
       {
         // sprintf(buf1,"%.2f",P_max);
         // SG_9->Cells[3*nl+1][k_f]=FloatToStrF(P_max,ffGeneral,3,2);
          SG_53->Cells[3*nl+1][k_f-64]=CurrToStrF(P_max,ffFixed,2);
          SG_53->Repaint();

         // sprintf(buf1,"%.2f",Qvh_osl[k_max]);
         // SG_9->Cells[3*nl+2][k_f]=FloatToStrF(Qvh_osl[k_max],ffGeneral,3,2);
         SG_53->Cells[3*nl+2][k_f-64]=CurrToStrF(Qvh_osl[k_max],ffFixed,2);
          SG_53->Repaint();
      }
    if(CB_53_vyh->ItemIndex>11)
       {
         //  sprintf(buf1,"%.2f",P_max);
         //  SG_9->Cells[3*(nl-4)+1][k_f]=FloatToStrF(P_max,ffGeneral,3,2);
          SG_53->Cells[3*(nl-4)+1][k_f-64]=CurrToStrF(P_max,ffFixed,2);
           SG_53->Repaint();

         //  sprintf(buf1,"%.2f",Qvh_osl[k_max]);
         //  SG_9->Cells[3*(nl-4)+2][k_f]=FloatToStrF(Qvh_osl[k_max],ffGeneral,3,2);
          SG_53->Cells[3*(nl-4)+2][k_f-64]=CurrToStrF(Qvh_osl[k_max],ffFixed,2);
           SG_53->Repaint();
      }

  //   Q[nl][k_f]=Qv_vh[31-k_max];  /* для массива рабочих точек */
     kod_att_izm=k_max;

  }  /*if 1 */
  Sleep(10);
      /* измерение Кода АЦП*/
/*сначала выставить соответствующий код входного атт  и включить матрицу ПМ пакет 2*/
    n_vh1= nl; n_vh2=nl;  /* от 0 до 7 -- здесь от 0 до 3*/
   // kod_att_izm=31-kod_att_izm;   /*заменить!!! */

if(CB_53_vh->ItemIndex==0){in1_at=Qv_vh[31-kod_att_izm];in2_at=0x1F;n_post=0;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[31-kod_att_izm];n_post=0;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

if(CB_53_vh->ItemIndex==2){in1_at=Qv_vh[31-kod_att_izm];in2_at=0x1F;n_post=1;nk_svch=1;
       }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[31-kod_att_izm];n_post=1;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче пакета 2 в УП7 ERR=1!\n");
    // goto end1;
    goto m_otl;
    }
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");goto m_otl;}

 Sleep(10);
                   /* запрос кода мощности */
                          /* пакет 9*/
//-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//----------------Чтение уровня мощности для каналов усилителей------------------------------
 if(CB_53_vyh->ItemIndex<=11)   /*  в зависимости от выхода*/
     {
     n_post=0; /**/
     }
  if(CB_53_vyh->ItemIndex>11)
     {
     n_post=1; /**/
   }
    nf=0x9;

  n_jj=0;

m_jj_v:
 //if((res=zapr_dan_up7_t(n_post,nf))==1)   /*0-- нет ошибок, 1-- есть ошибки */
 if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра запроса данных (9) в УП7!\n");
   //6.12.2011  vyh=false;
     // goto end;
     goto m_otl;
   }
   Sleep(10);
//17.07 if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07        // Нет принятых пакетов//     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07   }

  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
//17.07        // Нет принятых пакетов
//17.07 //     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07      if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj_v;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("Сбой по магистрале!");
//17.07       goto m2_end_5_v;
//17.07      }
   }
  else
  {
   /* Прием ответного пакета */

       // Принят пакет
      LEN=packet_my_km.p_my_v.len;
      IPK=packet_my_km.p_my_v.byte1;
      SRC=packet_my_km.p_my_v.byte2&0x1F;
      DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* левое крыло DST=0x6, правое крыло DST=0x7*/
      IPS=(packet_my_km.p_my_v.byte3>>2)&0x3F;
      ERR=packet_my_km.p_my_v.byte4&0x1;
       /* ADR_UP7=packet_my_km.p_my_v.byte5;*/
      IPK_UP7=packet_my_km.p_my_v.byte5;
      ADC1=packet_my_km.p_my_v.byte6;
      ADC2=packet_my_km.p_my_v.byte7;
      ADC3=packet_my_km.p_my_v.byte8;
      ADC4=packet_my_km.p_my_v.byte9;
      ADC5=packet_my_km.p_my_v.byte10;
      ADC6=packet_my_km.p_my_v.byte11;
      ADC7=packet_my_km.p_my_v.byte12;
      ADC8=packet_my_km.p_my_v.byte13;
      ADC9=packet_my_km.p_my_v.byte14;
      ADC10=packet_my_km.p_my_v.byte15;
      ADC11=packet_my_km.p_my_v.byte16;
      ADC12=packet_my_km.p_my_v.byte17;
//      ADC13=packet_my_km.p_my_v.byte18;

// 22.12.10
      if(CB_53_vyh->ItemIndex<=11)  /* в зависимости от выхода */
       {
        if(CB_53_vyh->ItemIndex==0) ADC=ADC1&0xFF;
        if(CB_53_vyh->ItemIndex==1) ADC=ADC2&0xFF;
        if(CB_53_vyh->ItemIndex==2) ADC=ADC3&0xFF;
        if(CB_53_vyh->ItemIndex==3) ADC=ADC4&0xFF;
        if(CB_53_vyh->ItemIndex==4) ADC=ADC5&0xFF;
        if(CB_53_vyh->ItemIndex==5) ADC=ADC6&0xFF;
        if(CB_53_vyh->ItemIndex==6) ADC=ADC7&0xFF;
        if(CB_53_vyh->ItemIndex==7) ADC=ADC8&0xFF;
        if(CB_53_vyh->ItemIndex==8) ADC=ADC9&0xFF;
        if(CB_53_vyh->ItemIndex==9) ADC=ADC10&0xFF;
        if(CB_53_vyh->ItemIndex==10) ADC=ADC11&0xFF;
        if(CB_53_vyh->ItemIndex==11) ADC=ADC12&0xFF;
       // if(CB_53_vyh->ItemIndex==12) ADC=ADC13&0xFF;
       }
    if(CB_53_vyh->ItemIndex>11)  /* в зависимости от выхода */
      {
        if(CB_53_vyh->ItemIndex==12) ADC=ADC1&0xFF;
        if(CB_53_vyh->ItemIndex==13) ADC=ADC2&0xFF;
        if(CB_53_vyh->ItemIndex==14) ADC=ADC3&0xFF;
        if(CB_53_vyh->ItemIndex==15) ADC=ADC4&0xFF;
        if(CB_53_vyh->ItemIndex==16) ADC=ADC5&0xFF;
        if(CB_53_vyh->ItemIndex==17) ADC=ADC6&0xFF;
        if(CB_53_vyh->ItemIndex==18) ADC=ADC7&0xFF;
        if(CB_53_vyh->ItemIndex==19) ADC=ADC8&0xFF;
        if(CB_53_vyh->ItemIndex==20) ADC=ADC9&0xFF;
        if(CB_53_vyh->ItemIndex==21) ADC=ADC10&0xFF;
        if(CB_53_vyh->ItemIndex==22) ADC=ADC11&0xFF;
        if(CB_53_vyh->ItemIndex==23) ADC=ADC12&0xFF;
//        if(CB_10_vyh->ItemIndex==24) ADC=ADC13&0xFF;
//        if(CB_10_vyh->ItemIndex==25) ADC=ADC14&0xFF;
      }

    if(ERR==1)
     {
          //ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении кода мощности! ERR=1");
         // goto m22;
           n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj_v;
            }
          else
            {
             ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении кода мощности! ERR=1");
             goto m22_v;
            }
     }

         // memset(&buf1,0,20);
         // sprintf(buf1,"%d",ADC);

        if(CB_53_vyh->ItemIndex<=11)
          {
          SG_53->Cells[3*nl+3][k_f-64]=IntToStr(ADC);/* изменить!!!*/
          SG_53->Repaint();
          }
        if(CB_53_vyh->ItemIndex>11)
          {
          SG_53->Cells[3*(nl-4)+3][k_f-64]=IntToStr(ADC);/* изменить!!!*/
          SG_53->Repaint();
          }

       m22_v:;
   }
  m2_end_5_v:;


   }/* end   по частое k_f*/

   end1_v:;                         /* пакет 2 */
 //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение матрицы для  1-го и 2-го канала СВЧ */=========================
       //   n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* от 0 до 7*/
       n_vh1= nl; n_vh2=nl;  /* от 0 до 7*/

  if(CB_53_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;n_post=0;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;n_post=0;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;n_post=1;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;n_post=1;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

 if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче пакета 2 в УП7 ERR=1!\n");
    // goto end;
    goto m_otl;
    }

  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");goto m_otl;}

     Sleep(1);
                      /* пакет 1*/
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение канала усилителя, выключение источника питания УП7 */=========================

 if(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
   {
    n_post=0;    /*ППС*/

    }
 if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
   }

  if((res=Vykl_us_vip_t(n_post))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче пакета 1 в УП7 ERR=1!\n");
    // goto end;
    goto m_otl;
    }

  if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");goto m_otl;}
         Sleep(1);

  end_luch:;
  } /* end  nl*/

m_otl:;
        viPrintf(viG,"OUTPut:STATe OFF\n"); //выкл. сигнала на выход ген-ра
        zapis_tabl53_my(n_us);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   /*  обработка результатов для записи */
   end:;
                 //  для выхода по Стоп
      /* пакет 2 */
 //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение матрицы для  1-го и 2-го канала СВЧ */=========================
       //   n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* от 0 до 7*/
      if(nl>3) nl=3;
        n_vh1= nl; n_vh2=nl;  /* от 0 до 7*/

  if(CB_53_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;n_post=0;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;n_post=0;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;n_post=1;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;n_post=1;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

 if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче пакета 2 в УП7 ERR=1!\n");
    // goto end;
    goto m_otl_end;
    }

  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");goto m_otl_end;}

     Sleep(1);
                      /* пакет 1*/
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение канала усилителя, выключение источника питания УП7 */=========================

 if(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
  {
    n_post=0;    /*ППС*/

   }
  if(CB_10_vyh->ItemIndex>11)
  {
    n_post=1; /*ЗПС*/
   }

  if((res=Vykl_us_vip_t(n_post))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче пакета 1 в УП7 ERR=1!\n");
    // goto end;
    goto m_otl_end;
    }

  if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");goto m_otl_end;}
         Sleep(1);
 m_otl_end:;
  viPrintf(viG,"OUTPut:STATe OFF\n"); //выкл. сигнала на выход ген-ра

  ShowMessage("Измерение закончено\n");

}
//---------------------------------------------------------------------------
void __fastcall TForm1::B53_stClick(TObject *Sender)
{
 extern bool vyh;
  vyh=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::B53_vyhClick(TObject *Sender)
{
 P_7->Visible=false;
}
//---------------------------------------------------------------------------
//============== запись файла таблицы =========================
void  TForm1::zapis_tabl53_my(int nus)
{
 FILE *tr;
 String str;
 int k,j,n_us;
// int kod_fpch;
 float P_izm[12][8][160]={0.0},osl[12][8][160]={0.0};
 int kad_acp[12][8][160]={0},k_f[160]={0};

 str=E53_fd->Text;

if((tr = fopen(str.c_str(),"r+")) == NULL)
  {
  ShowMessage("Нет файла");
  goto m1;
 }

  /* сначала чтение из файла */

   for(n_us=0;n_us<=11;n_us++)
    {
     for(k=0;k<=159;k++)
       {
        fscanf(tr,"%d",&k_f[k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][0][k],&osl[n_us][0][k], &kad_acp[n_us][0][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][1][k],&osl[n_us][1][k], &kad_acp[n_us][1][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][2][k],&osl[n_us][2][k], &kad_acp[n_us][2][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][3][k],&osl[n_us][3][k], &kad_acp[n_us][3][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][4][k],&osl[n_us][4][k], &kad_acp[n_us][4][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][5][k],&osl[n_us][5][k], &kad_acp[n_us][5][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][6][k],&osl[n_us][6][k], &kad_acp[n_us][6][k]);
        fscanf(tr,"%f%f%d\n",&P_izm[n_us][7][k],&osl[n_us][7][k],&kad_acp[n_us][7][k]);
      } /* end k*/
    } /* end n_us */

   fclose(tr);

 if(MessageDlg("Перезаписать файл?",
     mtConfirmation,TMsgDlgButtons() << mbYes<< mbNo,0) == mrYes)
    {
      ShowMessage("Файл будет перезаписан");
    }
   else goto m1;

 if((tr = fopen(str.c_str(),"w+")) == NULL)
  {
  ShowMessage("Нет файла");
  goto m1;
  }

 for(n_us=0;n_us<=11;n_us++)
  {
    if(n_us==nus)
     {
      /* запись в файл */
     for(k=0;k<=159;k++)    /* строка  */
       {
        fprintf(tr,"%d ",k);
         // for(j=1;j<=10;j=j+3)   /* столбец  */
          for(j=1;j<=22;j=j+3)   /* столбец  */
           {
            // if((j+2)==12)
             if((j+2)==24)
              {
              fprintf(tr,"%.2f %.2f %d\n",atof((SG_53->Cells[j][k]).c_str()),
               atof((SG_53->Cells[j+1][k]).c_str()),atoi((SG_53->Cells[j+2][k]).c_str()));
              }
            else
              fprintf(tr,"%.2f %.2f %d ",atof((SG_53->Cells[j][k]).c_str()),
               atof((SG_53->Cells[j+1][k]).c_str()),atoi((SG_53->Cells[j+2][k]).c_str()));
          }
       }   /*  end for*/
   }  /* if n_us==nus */
    else
     {
      for(k=0;k<=159;k++) /* запись в файл остальных усилителей*/
       {
        fprintf(tr,"%d ",k);
         fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][0][k],osl[n_us][0][k],kad_acp[n_us][0][k]);
         fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][1][k],osl[n_us][1][k],kad_acp[n_us][1][k]);
         fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][2][k],osl[n_us][2][k],kad_acp[n_us][2][k]);
         fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][3][k],osl[n_us][3][k],kad_acp[n_us][3][k]);
         fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][4][k],osl[n_us][4][k],kad_acp[n_us][4][k]);
         fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][5][k],osl[n_us][5][k],kad_acp[n_us][5][k]);
         fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][6][k],osl[n_us][6][k],kad_acp[n_us][6][k]);
         fprintf(tr,"%.2f %.2f %d\n",P_izm[n_us][7][k],osl[n_us][7][k],kad_acp[n_us][7][k]);
        }  /* end k*/
     } /*  else*/

    if(n_us==11)   fclose(tr);
  } /* end n_us*/

 m1:;
}
//-----------------Чтение и редактирование файла измерений в таблицу ----------------------------------------------------------
void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
 extern double F_rtu[224];
 AnsiString StNIn;
int indIn,colLuch,colOut,colF;
int Flb,Lit,i,j;
AnsiString SbS,SbL,StrDir,StIn,SbS_t;
AnsiString MyFileName;
int n_vh,nl,k,n_us;

 float P_izm[12][8][160]={0.0},osl[12][8][160]={0.0};
 int kad_acp[12][8][160]={0},k_f[160]={0};
 // unsigned NIT;

 //float P_izm_mod[13]={0.0}; /* массив для записи в файл */

 FILE *tr;

StNIn= InputBox("Введите номер входа", "один из четырех (1,2,3,4). Полусфера должна быть выбрана на панели","1");

if(RG53_10->ItemIndex==0)
 {
  SbS_t="ППС";
  SbS="pps";
  }
else
  {
  SbS_t="ЗПС";
  SbS="zps";
  }
//SbL="ВЧ_2";
  SbL="_53";
Flb=Fl;
colLuch=8;
colOut=12;
Lit=1;

//colF=((Fb-Fl)/500)*8;

// StrDir=GetCurrentDir();  для новой директории

 StIn=SbS+"_"+StNIn+SbL+".dan";
// MyFileName=StrDir+"\\PowMesh\\"+StIn;
 MyFileName=StIn;
 if(FileExists(MyFileName))
 {
   n_vh=StrToInt(StNIn);
 //    chten_mrt(n_vh);
 //   if(n_vhod==1) str="pps_1_2.mrt";
if((tr = fopen(MyFileName.c_str(),"r+")) == NULL)
  {
  ShowMessage("Невозможно открыть файл");
   goto m1;
  }
 /* сначала чтение из файла */

 for(n_us=0;n_us<=11;n_us++) /* по 12 усилителям */
   {
   for(k=0;k<=159;k++)
       {
        fscanf(tr,"%d",&k_f[k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][0][k],&osl[n_us][0][k], &kad_acp[n_us][0][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][1][k],&osl[n_us][1][k], &kad_acp[n_us][1][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][2][k],&osl[n_us][2][k], &kad_acp[n_us][2][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][3][k],&osl[n_us][3][k], &kad_acp[n_us][3][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][4][k],&osl[n_us][4][k], &kad_acp[n_us][4][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][5][k],&osl[n_us][5][k], &kad_acp[n_us][5][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][6][k],&osl[n_us][6][k], &kad_acp[n_us][6][k]);
        fscanf(tr,"%f%f%d\n",&P_izm[n_us][7][k],&osl[n_us][7][k],&kad_acp[n_us][7][k]);
      } /* end k*/
    } /* end n_us */

   fclose(tr);

   P53_fi->Visible=true;

   Label55->Caption="Таблица  выходных мощностей и кодов входных аттенюторов. Вход "+StNIn+". "+"Литера"+SbL+". "+SbS_t;

   PostMessage(SG53_fi->Handle, WM_MBUTTONDOWN, MK_LBUTTON,0);
   PostMessage(SG53_fi->Handle, WM_MBUTTONUP, MK_LBUTTON,0);

        /* очистить таблицу*/
for(n_us=0;n_us<=11;n_us++)     /* по 8-ми лучам */
    {
  for(k=1;k<=160;k++)    /* строка  */
   for(j=1;j<=24;j++)   /* столбец  */
     {
     SG53_fi->Cells[j][k+n_us*160]=" ";
     }
  }
  for(n_us=0;n_us<=11;n_us++)     /* по 12 усилителям */
    {
   for(k=64;k<=223;k++)    /* строка  */   /*?????*/
   SG53_fi->Cells[0][k+1-64+n_us*160+n_us]=FloatToStr(F_rtu[k]);
   }
                /* вывести в таблицу */
    for(n_us=0;n_us<=11;n_us++)     /* по 12 усилителям */
    {
         SG53_fi->Cells[0][n_us*160+n_us]=" ";
         SG53_fi->Cells[4][n_us*160+n_us]="Выход";
         SG53_fi->Cells[5][n_us*160+n_us]=SbS_t+"-"+IntToStr(n_us+1);
     for(k=0;k<=159;k++)
      {
                         /* Луч 1 */
        SG53_fi->Cells[1][n_us*160+k+(n_us+1)]=FloatToStrF(P_izm[n_us][0][k],ffGeneral,3,2);
        SG53_fi->Cells[2][n_us*160+k+(n_us+1)]=FloatToStrF(osl[n_us][0][k],ffGeneral,4,2);
//        SG53_fi->Cells[3][n_us*160+k+(n_us+1)]=FloatToStrF(kad_acp[n_us][0][k],ffGeneral,3,2);
        SG53_fi->Cells[3][n_us*160+k+(n_us+1)]=IntToStr(kad_acp[n_us][0][k]);
                         /* Луч 2 */
        SG53_fi->Cells[4][n_us*160+k+(n_us+1)]=FloatToStrF(P_izm[n_us][1][k],ffGeneral,3,2);
        SG53_fi->Cells[5][n_us*160+k+(n_us+1)]=FloatToStrF(osl[n_us][1][k],ffGeneral,4,2);
    //    SG53_fi->Cells[6][n_us*160+k+(n_us+1)]=FloatToStrF(kad_acp[n_us][1][k],ffGeneral,3,2);
         SG53_fi->Cells[6][n_us*160+k+(n_us+1)]=IntToStr(kad_acp[n_us][1][k]);
                           /* Луч 3*/
        SG53_fi->Cells[7][n_us*160+k+(n_us+1)]=FloatToStrF(P_izm[n_us][2][k],ffGeneral,3,2);
        SG53_fi->Cells[8][n_us*160+k+(n_us+1)]=FloatToStrF(osl[n_us][2][k],ffGeneral,4,2);
      //  SG53_fi->Cells[9][n_us*160+k+(n_us+1)]=FloatToStrF(kad_acp[n_us][2][k],ffGeneral,3,2);
        SG53_fi->Cells[9][n_us*160+k+(n_us+1)]=IntToStr(kad_acp[n_us][2][k]);

                           /* Луч 4 */
        SG53_fi->Cells[10][n_us*160+k+(n_us+1)]=FloatToStrF(P_izm[n_us][3][k],ffGeneral,3,2);
        SG53_fi->Cells[11][n_us*160+k+(n_us+1)]=FloatToStrF(osl[n_us][3][k],ffGeneral,4,2);
     //   SG53_fi->Cells[12][n_us*160+k+(n_us+1)]=FloatToStrF(kad_acp[n_us][3][k],ffGeneral,3,2);
        SG53_fi->Cells[12][n_us*160+k+(n_us+1)]=IntToStr(kad_acp[n_us][3][k]);
                           /* Луч 5 */
        SG53_fi->Cells[13][n_us*160+k+(n_us+1)]=FloatToStrF(P_izm[n_us][4][k],ffGeneral,3,2);
        SG53_fi->Cells[14][n_us*160+k+(n_us+1)]=FloatToStrF(osl[n_us][4][k],ffGeneral,4,2);
      //  SG53_fi->Cells[15][n_us*160+k+(n_us+1)]=FloatToStrF(kad_acp[n_us][4][k],ffGeneral,3,2);
        SG53_fi->Cells[15][n_us*160+k+(n_us+1)]=IntToStr(kad_acp[n_us][4][k]);
                             /* Луч 6 */
        SG53_fi->Cells[16][n_us*160+k+(n_us+1)]=FloatToStrF(P_izm[n_us][5][k],ffGeneral,3,2);
        SG53_fi->Cells[17][n_us*160+k+(n_us+1)]=FloatToStrF(osl[n_us][5][k],ffGeneral,4,2);
       // SG53_fi->Cells[18][n_us*160+k+(n_us+1)]=FloatToStrF(kad_acp[n_us][5][k],ffGeneral,3,2);
        SG53_fi->Cells[18][n_us*160+k+(n_us+1)]=IntToStr(kad_acp[n_us][5][k]);
                               /* Луч 7 */
        SG53_fi->Cells[19][n_us*160+k+(n_us+1)]=FloatToStrF(P_izm[n_us][6][k],ffGeneral,3,2);
        SG53_fi->Cells[20][n_us*160+k+(n_us+1)]=FloatToStrF(osl[n_us][6][k],ffGeneral,4,2);
       // SG53_fi->Cells[21][n_us*160+k+(n_us+1)]=FloatToStrF(kad_acp[n_us][6][k],ffGeneral,3,2);
        SG53_fi->Cells[21][n_us*160+k+(n_us+1)]=IntToStr(kad_acp[n_us][6][k]);
                               /* Луч 8 */
        SG53_fi->Cells[22][n_us*160+k+(n_us+1)]=FloatToStrF(P_izm[n_us][7][k],ffGeneral,3,2);
        SG53_fi->Cells[23][n_us*160+k+(n_us+1)]=FloatToStrF(osl[n_us][7][k],ffGeneral,4,2);
       // SG53_fi->Cells[24][n_us*160+k+(n_us+1)]=FloatToStrF(kad_acp[n_us][7][k],ffGeneral,3,2);
        SG53_fi->Cells[24][n_us*160+k+(n_us+1)]=IntToStr(kad_acp[n_us][7][k]);
     } /* end k*/
  } /* end n_us */

 }  //if
 else ShowMessage("Нет файла");
m1:;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::B53_fiClick(TObject *Sender)
{
  P53_fi->Visible=false;
}
//---------------Запись отредактированного файла измерений *.dan ------------------
void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
 extern double F_rtu[224];
 AnsiString StNIn,Str;
int indIn,colLuch,colOut,colF;
int Flb,Lit,i,j;
AnsiString SbS,SbL,StrDir,StIn,SbS_t;
AnsiString MyFileName;
int n_vh,nl,k,k_f,n_us;

 float P_izm[12][8][160]={0.0},osl[12][8][160]={0.0};
 int kad_acp[12][8][160]={0};//k_f[64]={0};

 FILE *tr;
 bool res;

//StNIn= InputBox("Введите номер входа", "один из четырех (1,2,3,4). Полусфера должна быть выбрана на панели","1");
 Str=Label55->Caption;//"Таблица  выходных мощностей и кодов входных аттенюторов. Вход "+StNIn+". "+"Литера"+SbL+". "+SbS_t ";

 int p=Str.Pos(".");
 //StNIn=Str.SubString(p+7,1);  /* имя файла ????*/
 StNIn=Str.SubString(p+7,1);  /* имя файла ????*/

 if(RG53_10->ItemIndex==0)
 {
  SbS_t="ППС";
  SbS="pps";
  }
else
  {
  SbS_t="ЗПС";
  SbS="zps";
  }
//SbL="ВЧ_2";
  SbL="_53"; /* сделать и для _53 !!!!*/
Flb=Fl;
colLuch=8;
colOut=12;
Lit=1;
//colF=((Fb-Fl)/500)*8;

//--------------проверка правильности заполнения таблицы------------------------
 for(n_us=0;n_us<=11;n_us++)
  {
       /* запись в файл */
     for(k=0;k<=159;k++)    /* строка  */
       {
         /* Луч 1 */
    res=TryStrToFloat(SG53_fi->Cells[1][n_us*160+k+(n_us+1)],P_izm[n_us][0][k]);
     if(res==false)
         {
         ShowMessage("Неправильно введено значение Ризм: Луч 1. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
         }
     res=TryStrToFloat(SG53_fi->Cells[2][n_us*160+k+(n_us+1)],osl[n_us][0][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт.: Луч 1. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
         }

     res=TryStrToInt(SG53_fi->Cells[3][n_us*160+k+(n_us+1)],kad_acp[n_us][0][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код ДМ: Луч 1. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
         }

        /* Луч 2*/
     res=TryStrToFloat(SG53_fi->Cells[4][n_us*160+k+(n_us+1)],P_izm[n_us][1][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Ризм: Луч 2. Выход "+SbS_t+"-"+IntToStr(n_us+1)+" строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
         }
       res=TryStrToFloat(SG53_fi->Cells[5][n_us*160+k+(n_us+1)],osl[n_us][1][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт.: Луч 2. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
         }
       res=TryStrToInt(SG53_fi->Cells[6][n_us*160+k+(n_us+1)],kad_acp[n_us][1][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код ДМ: Луч 2. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
         }

           /* Луч 3 */
      res=TryStrToFloat(SG53_fi->Cells[7][n_us*160+k+(n_us+1)],P_izm[n_us][2][k]);
      if(res==false)
         {
         ShowMessage("Неправильно введено значение Ризм: Луч 3. Выход "+SbS_t+"-"+IntToStr(n_us+1)+" строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
         }
        res=TryStrToFloat(SG53_fi->Cells[8][n_us*160+k+(n_us+1)],osl[n_us][2][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт.: Луч 3. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
         }
      res=TryStrToInt(SG53_fi->Cells[9][n_us*160+k+(n_us+1)],kad_acp[n_us][2][k]);
      if(res==false)
         {
         ShowMessage("Неправильно введено значение Код ДМ: Луч 3. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
         }

          /* Луч 4*/
       res=TryStrToFloat(SG53_fi->Cells[10][n_us*160+k+(n_us+1)],P_izm[n_us][3][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Ризм: Луч 4. Выход "+SbS_t+"-"+IntToStr(n_us+1)+" строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
         }
       res=TryStrToFloat(SG53_fi->Cells[11][n_us*160+k+(n_us+1)],osl[n_us][3][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт.: Луч 4. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
        }
      res=TryStrToInt(SG53_fi->Cells[12][n_us*160+k+(n_us+1)],kad_acp[n_us][3][k]);
       if(res==false)
        {
         ShowMessage("Неправильно введено значение Код ДМ: Луч 4. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
        }
         /* Луч 5*/
       res=TryStrToFloat(SG53_fi->Cells[13][n_us*160+k+(n_us+1)],P_izm[n_us][4][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Ризм: Луч 5. Выход "+SbS_t+"-"+IntToStr(n_us+1)+" строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
         }
       res=TryStrToFloat(SG53_fi->Cells[14][n_us*160+k+(n_us+1)],osl[n_us][4][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт.: Луч 5. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
        }
      res=TryStrToInt(SG53_fi->Cells[15][n_us*160+k+(n_us+1)],kad_acp[n_us][4][k]);
       if(res==false)
        {
         ShowMessage("Неправильно введено значение Код ДМ: Луч 5. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
       }
         /* Луч 6*/
       res=TryStrToFloat(SG53_fi->Cells[16][n_us*160+k+(n_us+1)],P_izm[n_us][5][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Ризм: Луч 6. Выход "+SbS_t+"-"+IntToStr(n_us+1)+" строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
         }
       res=TryStrToFloat(SG53_fi->Cells[17][n_us*160+k+(n_us+1)],osl[n_us][5][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт.: Луч 6. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
        }
      res=TryStrToInt(SG53_fi->Cells[18][n_us*160+k+(n_us+1)],kad_acp[n_us][5][k]);
       if(res==false)
        {
         ShowMessage("Неправильно введено значение Код ДМ: Луч 6. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
        }
           /* Луч 7*/
       res=TryStrToFloat(SG53_fi->Cells[19][n_us*160+k+(n_us+1)],P_izm[n_us][6][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Ризм: Луч 7. Выход "+SbS_t+"-"+IntToStr(n_us+1)+" строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
         }
       res=TryStrToFloat(SG53_fi->Cells[20][n_us*160+k+(n_us+1)],osl[n_us][6][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт.: Луч 7. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
        }
      res=TryStrToInt(SG53_fi->Cells[21][n_us*160+k+(n_us+1)],kad_acp[n_us][6][k]);
       if(res==false)
        {
         ShowMessage("Неправильно введено значение Код ДМ: Луч 7. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
        }
          /* Луч 8*/
       res=TryStrToFloat(SG53_fi->Cells[22][n_us*160+k+(n_us+1)],P_izm[n_us][7][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Ризм: Луч 7. Выход "+SbS_t+"-"+IntToStr(n_us+1)+" строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
         }
       res=TryStrToFloat(SG53_fi->Cells[23][n_us*160+k+(n_us+1)],osl[n_us][7][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт.: Луч 7. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
         goto m1;
        }
      res=TryStrToInt(SG53_fi->Cells[24][n_us*160+k+(n_us+1)],kad_acp[n_us][7][k]);
       if(res==false)
        {
         ShowMessage("Неправильно введено значение Код ДМ: Луч 7. Выход "+SbS_t+"-"+IntToStr(n_us+1)+"строка "+FloatToStr(F_rtu[k+64]));
          goto m1;
        }

     }  /* end k по частоте*/

 }   /* end n_us */

// StrDir=GetCurrentDir();  для новой директории

 StIn=SbS+"_"+StNIn+SbL+".dan";
// MyFileName=StrDir+"\\PowMesh\\"+StIn;
 MyFileName=StIn;
 if(FileExists(MyFileName))
 {
   n_vh=StrToInt(StNIn);
 if(MessageDlg("Перезаписать файл измерений для Входа "+StNIn+"Литеры"+SbL+SbS_t+"?",
     mtConfirmation,TMsgDlgButtons() << mbYes<< mbNo,0) == mrYes)
    {
      ShowMessage("Файл будет перезаписан");
    }
   else goto m1;

//=====================================================
 if((tr = fopen(MyFileName.c_str(),"w+")) == NULL)
  {
  ShowMessage("Нет файла");
  goto m1;
  }

 for(n_us=0;n_us<=11;n_us++)
  {
       /* запись в файл */
     for(k=0;k<=159;k++)    /* строка  */
       {
        fprintf(tr,"%d ",k);
        fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][0][k],osl[n_us][0][k],kad_acp[n_us][0][k]);
        fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][1][k],osl[n_us][1][k],kad_acp[n_us][1][k]);
        fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][2][k],osl[n_us][2][k],kad_acp[n_us][2][k]);
        fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][3][k],osl[n_us][3][k],kad_acp[n_us][3][k]);
        fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][4][k],osl[n_us][4][k],kad_acp[n_us][4][k]);
        fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][5][k],osl[n_us][5][k],kad_acp[n_us][5][k]);
        fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][6][k],osl[n_us][6][k],kad_acp[n_us][6][k]);
        fprintf(tr,"%.2f %.2f %d \n",P_izm[n_us][7][k],osl[n_us][7][k],kad_acp[n_us][7][k]);
       }   /*  end for */
  } /* end n_us*/

}/* if*/
   fclose(tr);

m1:;
}
//------------------формирование файла  *.mrt текстового ---------------------------------------------------------
void __fastcall TForm1::B53_mrtClick(TObject *Sender)
{
 FILE *tr;
 String str;
 int k,j,n_us,k1,k2,k_max_mod,nl;
// int kod_fpch;
 float P_izm[12][8][160]={0.0},osl[12][8][160]={0.0};
 int kad_acp[12][8][160]={0},k_f[160]={0};
 // unsigned NIT;

 float P_izm_mod[12]={0.0}; /* массив для записи в файл */
  float P_in_att=0.0;
  float P_max_mod=0.0;

  float dP_osl_0[8][160]={0.0},dP_osl_1[8][160]={0.0},dP_osl_2[8][160]={0.0},
        dP_osl_3[8][160]={0.0},dP_osl_4[8][160]={0.0},dP_osl_5[8][160]={0.0},
        dP_osl_6[8][160]={0.0},dP_osl_7[8][160]={0.0},dP_osl_8[8][160]={0.0},
        dP_osl_9[8][160]={0.0},dP_osl_10[8][160]={0.0},dP_osl_11[8][160]={0.0};
       // dP_osl_12[8][160]={0.0};

//  if(CB_3_vh->ItemIndex==0){NIT=4;}  /* Вход 1-2 */
//  if(CB_3_vh->ItemIndex==1){NIT=5;}  /* Вход 2-2 */
//  if(CB_3_vh->ItemIndex==2){NIT=6;}  /* Вход 3-2 */
//  if(CB_3_vh->ItemIndex==3){NIT=7;}  /* Вход 4-2 */

   str=E53_fd->Text;     /* имя обрабатываемого файла */

// 17.06.2011  убрать для реальных значений
//if((tr = fopen(str.c_str(),"r+")) == NULL)
//  {
//  ShowMessage("Нет файла");
//  goto m1;
// }

  /* сначала чтение из файла */

//   for(n_us=0;n_us<=11;n_us++)
//    {
//     for(k=0;k<=159;k++)
//       {
//        fscanf(tr,"%d",&k_f[k]);
//        fscanf(tr,"%f%f%d",&P_izm[n_us][0][k],&osl[n_us][0][k], &kad_acp[n_us][0][k]);
//      fscanf(tr,"%f%f%d",&P_izm[n_us][1][k],&osl[n_us][1][k], &kad_acp[n_us][1][k]);
//        fscanf(tr,"%f%f%d",&P_izm[n_us][2][k],&osl[n_us][2][k], &kad_acp[n_us][2][k]);
//        fscanf(tr,"%f%f%d",&P_izm[n_us][3][k],&osl[n_us][3][k], &kad_acp[n_us][3][k]);
//        fscanf(tr,"%f%f%d",&P_izm[n_us][4][k],&osl[n_us][4][k], &kad_acp[n_us][4][k]);
//        fscanf(tr,"%f%f%d",&P_izm[n_us][5][k],&osl[n_us][5][k], &kad_acp[n_us][5][k]);
//        fscanf(tr,"%f%f%d",&P_izm[n_us][6][k],&osl[n_us][6][k], &kad_acp[n_us][6][k]);
//        fscanf(tr,"%f%f%d\n",&P_izm[n_us][7][k],&osl[n_us][7][k],&kad_acp[n_us][7][k]);
//      } /* end k*/
//    } /* end n_us */
//   fclose(tr);

   if(MessageDlg("Перезаписать файл МРТ?",
     mtConfirmation,TMsgDlgButtons() << mbYes<< mbNo,0) == mrYes)
    {
      ShowMessage("Файл будет перезаписан");
    }
   else goto m1;

//   str="pps_1_53.mrt";
   str=E53_mrt->Text;    /* имя текстового файла МРТ */
 if((tr = fopen(str.c_str(),"w+")) == NULL)
  {
  ShowMessage("Нет файла");
  goto m1;
 }

 for(nl=0;nl<=7;nl++)   /* цикл по номеру луча*/
  {
  for(k=0; k<=159; k++) /* по частоте*/
   {

    P_izm_mod[0]=0.0;//osl[0][nl][k];
    P_izm_mod[1]=0.0;//osl[1][nl][k];
    P_izm_mod[2]=0.0;//osl[2][nl][k];
    P_izm_mod[3]=0.0;//osl[3][nl][k];
    P_izm_mod[4]=0.0;//osl[4][nl][k];
    P_izm_mod[5]=0.0;//osl[5][nl][k];
    P_izm_mod[6]=0.0;//osl[6][nl][k];
    P_izm_mod[7]=0.0;//osl[7][nl][k];
    P_izm_mod[8]=0.0;//osl[8][nl][k];
    P_izm_mod[9]=0.0;//osl[9][nl][k];
    P_izm_mod[10]=0.0;//osl[10][nl][k];
    P_izm_mod[11]=0.0;//osl[11][nl][k];
   // P_izm_mod[12]=osl[12][nl][k];

//   for(k1=0,P_max_mod=P_izm_mod[0]; k1<=11; k1+=1)
//       {
//       if(P_izm_mod[k1]>P_max_mod) {P_max_mod=P_izm_mod[k1];k_max_mod=k1;}  /* max значение и номер этого усилителя */
//       }

     P_in_att=0.0;//P_max_mod;

     dP_osl_0[nl][k]=0.0;//P_izm_mod[0]-P_max_mod;
     dP_osl_1[nl][k]=0.0;//P_izm_mod[1]-P_max_mod;
     dP_osl_2[nl][k]=0.0;//P_izm_mod[2]-P_max_mod;
     dP_osl_3[nl][k]=0.0;//P_izm_mod[3]-P_max_mod;
     dP_osl_4[nl][k]=0.0;//P_izm_mod[4]-P_max_mod;
     dP_osl_5[nl][k]=0.0;//P_izm_mod[5]-P_max_mod;
     dP_osl_6[nl][k]=0.0;//P_izm_mod[6]-P_max_mod;
     dP_osl_7[nl][k]=0.0;//P_izm_mod[7]-P_max_mod;
     dP_osl_8[nl][k]=0.0;//P_izm_mod[8]-P_max_mod;
     dP_osl_9[nl][k]=0.0;//P_izm_mod[9]-P_max_mod;
     dP_osl_10[nl][k]=0.0;//P_izm_mod[10]-P_max_mod;
     dP_osl_11[nl][k]=0.0;//P_izm_mod[11]-P_max_mod;
//     dP_osl_12[nl][k]=P_izm_mod[12]-P_max_mod;


        fprintf(tr,"%d ",k);
         fprintf(tr,"%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",P_in_att,dP_osl_0[nl][k],
                 dP_osl_1[nl][k],dP_osl_2[nl][k],dP_osl_3[nl][k],dP_osl_4[nl][k],dP_osl_5[nl][k],dP_osl_6[nl][k],
                 dP_osl_7[nl][k],dP_osl_8[nl][k],dP_osl_9[nl][k],dP_osl_10[nl][k],dP_osl_11[nl][k]);//dP_osl_12[nl][k]);

       }  /* end k по частоте*/

}   /* end nl по лучам*/

   fclose(tr);

m1:;
}
//---------------Чтение и редактирование файла *mrt (тестового) ---------------
void __fastcall TForm1::SpeedButton6Click(TObject *Sender)
{
 extern double F_rtu[224];
 AnsiString StNIn;
//int indIn,colLuch,colOut,colF;
//int Flb,Lit;
int i,j;
AnsiString SbS,SbL,StrDir,StIn,SbS_t;
AnsiString MyFileName;
int n_vh,nl,k,k_f;

   float P_in_att[8][160]={0.0};
 // float P_max_mod=0.0;

  float dP_osl_0[8][160]={0.0},dP_osl_1[8][160]={0.0},dP_osl_2[8][160]={0.0},
        dP_osl_3[8][160]={0.0},dP_osl_4[8][160]={0.0},dP_osl_5[8][160]={0.0},
        dP_osl_6[8][160]={0.0},dP_osl_7[8][160]={0.0},dP_osl_8[8][160]={0.0},
        dP_osl_9[8][160]={0.0},dP_osl_10[8][160]={0.0},dP_osl_11[8][160]={0.0},
        dP_osl_12[8][160]={0.0};

 FILE *tr;
// String str;
// int k,j,n_us,k1,k2,k_max_mod,nl,k_f;


StNIn= InputBox("Введите номер входа", "один из четырех (1,2,3,4). Полусфера должна быть выбрана на панели","1");

if(RG53_10->ItemIndex==0)
 {
  SbS_t="ППС";
  SbS="pps";
  }
else
  {
  SbS_t="ЗПС";
  SbS="zps";
  }
//SbL="ВЧ_2";
  SbL="_53";

//Flb=Fl;
//colLuch=4;
//colOut=13;
//Lit=0;
//colF=((Fb-Fl)/500)*8;

// StrDir=GetCurrentDir();  для новой директории

 StIn=SbS+"_"+StNIn+SbL+".mrt";
// MyFileName=StrDir+"\\PowMesh\\"+StIn;
 MyFileName=StIn;
 if(FileExists(MyFileName))
 {
   n_vh=StrToInt(StNIn);
 //    chten_mrt(n_vh);
 //   if(n_vhod==1) str="pps_1_53.mrt";
if((tr = fopen(MyFileName.c_str(),"r+")) == NULL)
  {
  ShowMessage("Нет файла");
   goto m1;
  }
 /* сначала чтение из файла */
  for(nl=0;nl<=7;nl++)     /* по 7-м лучам */
    {
     for(k=0;k<=159;k++)
       {
         fscanf(tr,"%d",&k_f);
         fscanf(tr,"%f%f%f%f%f%f%f%f%f%f%f%f%f\n",&P_in_att[nl][k],&dP_osl_0[nl][k],
         &dP_osl_1[nl][k],&dP_osl_2[nl][k],&dP_osl_3[nl][k],&dP_osl_4[nl][k],&dP_osl_5[nl][k],&dP_osl_6[nl][k],
         &dP_osl_7[nl][k],&dP_osl_8[nl][k],&dP_osl_9[nl][k],&dP_osl_10[nl][k],&dP_osl_11[nl][k]);//,&dP_osl_12[nl][k]);
       } /* end k*/
    } /* end nl */
   fclose(tr);

   Panel7->Visible=true;
   Label60->Caption="Значения файла  массива  рабочих точек (MRT). Вход "+StNIn+". "+"Литера"+SbL+". "+SbS_t;

   PostMessage(SG53_mrt->Handle, WM_MBUTTONDOWN, MK_LBUTTON,0);
   PostMessage(SG53_mrt->Handle, WM_MBUTTONUP, MK_LBUTTON,0);

        /* очистить таблицу*/
for(nl=0;nl<=7;nl++)     /* по 8-ми лучам */
    {
  for(k=1;k<=160;k++)    /* строка  */
   for(j=1;j<=12;j++)   /* столбец  */
     {
     SG53_mrt->Cells[j][k+nl*160]=" ";
     }
  }
   SG53_mrt->Cells[0][0]="Частота";
   SG53_mrt->Cells[1][0]="Код вх.атт";
   SG53_mrt->Cells[2][0]="Код атт 1";
   SG53_mrt->Cells[3][0]="Код атт 2";
   SG53_mrt->Cells[4][0]="Код атт 3";
   SG53_mrt->Cells[5][0]="Код атт 4";
   SG53_mrt->Cells[6][0]="Код атт 5";
   SG53_mrt->Cells[7][0]="Код атт 6";
   SG53_mrt->Cells[8][0]="Код атт 7";
   SG53_mrt->Cells[9][0]="Код атт 8";
   SG53_mrt->Cells[10][0]="Код атт 9";
   SG53_mrt->Cells[11][0]="Код атт10";
   SG53_mrt->Cells[12][0]="Код атт11";
   SG53_mrt->Cells[13][0]="Код атт12";
 //  SG2->Cells[14][0]="Код атт13";

  for(nl=0;nl<=7;nl++)     /* по 8-м лучам */
    {
   for(k=1;k<=160;k++)    /* строка  */   /*?????*/
   SG53_mrt->Cells[0][k+nl*160+(nl+1)]=FloatToStr(F_rtu[k+64-1]);
   }

    for(nl=0;nl<=7;nl++)     /* по 4-м лучам */
    {
         SG53_mrt->Cells[5][nl*160+(nl+1)]="Луч "+IntToStr(nl+1);
     for(k=0;k<=159;k++)
      {
        SG53_mrt->Cells[1][nl*160+k+(nl+2)]=FloatToStrF(P_in_att[nl][k],ffGeneral,3,2);
        SG53_mrt->Cells[2][nl*160+k+(nl+2)]=FloatToStrF(dP_osl_0[nl][k],ffGeneral,3,2);
        SG53_mrt->Cells[3][nl*160+k+(nl+2)]=FloatToStrF(dP_osl_1[nl][k],ffGeneral,3,2);
        SG53_mrt->Cells[4][nl*160+k+(nl+2)]=FloatToStrF(dP_osl_2[nl][k],ffGeneral,3,2);
        SG53_mrt->Cells[5][nl*160+k+(nl+2)]=FloatToStrF(dP_osl_3[nl][k],ffGeneral,3,2);
        SG53_mrt->Cells[6][nl*160+k+(nl+2)]=FloatToStrF(dP_osl_4[nl][k],ffGeneral,3,2);
        SG53_mrt->Cells[7][nl*160+k+(nl+2)]=FloatToStrF(dP_osl_5[nl][k],ffGeneral,3,2);
        SG53_mrt->Cells[8][nl*160+k+(nl+2)]=FloatToStrF(dP_osl_6[nl][k],ffGeneral,3,2);
        SG53_mrt->Cells[9][nl*160+k+(nl+2)]=FloatToStrF(dP_osl_7[nl][k],ffGeneral,3,2);
        SG53_mrt->Cells[10][nl*160+k+(nl+2)]=FloatToStrF(dP_osl_8[nl][k],ffGeneral,3,2);
        SG53_mrt->Cells[11][nl*160+k+(nl+2)]=FloatToStrF(dP_osl_9[nl][k],ffGeneral,3,2);
        SG53_mrt->Cells[12][nl*160+k+(nl+2)]=FloatToStrF(dP_osl_10[nl][k],ffGeneral,3,2);
        SG53_mrt->Cells[13][nl*160+k+(nl+2)]=FloatToStrF(dP_osl_11[nl][k],ffGeneral,3,2);
       // SG2->Cells[14][nl*64+k+(nl+2)]=FloatToStrF(dP_osl_12[nl][k],ffGeneral,3,2);
      } /* end k*/
    } /* end nl */

 }  //if
m1:;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button26Click(TObject *Sender)
{
  Panel7->Visible=false;
}
//------------------редактирование массива рабочих точек *.mrt для 53 литеры---------------------------------------------------------
void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
extern double F_rtu[224];
AnsiString StNIn,Str;
int indIn;
//int colLuch,colOut,colF;
//int Flb,Lit;
int i,j;
AnsiString SbS,SbL,StrDir,StIn,SbS_t;
AnsiString MyFileName;
int n_vh,nl,k,k_f;

   float P_in_att[8][160]={0.0};
 // float P_max_mod=0.0;

  float dP_osl_0[8][160]={0.0},dP_osl_1[8][160]={0.0},dP_osl_2[8][160]={0.0},
        dP_osl_3[8][160]={0.0},dP_osl_4[8][160]={0.0},dP_osl_5[8][160]={0.0},
        dP_osl_6[8][160]={0.0},dP_osl_7[8][160]={0.0},dP_osl_8[8][160]={0.0},
        dP_osl_9[8][160]={0.0},dP_osl_10[8][160]={0.0},dP_osl_11[8][160]={0.0},
        dP_osl_12[8][160]={0.0};

 FILE *tr;
 bool res;

//StNIn= InputBox("Введите номер входа", "один из четырех (1,2,3,4). Полусфера должна быть выбрана на панели","1");
 Str=Label60->Caption;//"Значения файла  массива  рабочих точек (MRT). Вход "+StNIn+". "+"Литера"+SbL+". "+SbS_t;

 int p=Str.Pos("д");
 StNIn=Str.SubString(p+2,1);

 if(RG9->ItemIndex==0)
 {
  SbS_t="ППС";
  SbS="pps";
  }
else
  {
  SbS_t="ЗПС";
  SbS="zps";
  }
//SbL="ВЧ_2";
  SbL="_53"; /* сделать и для _53 !!!!*/
//Flb=Fl;
//colLuch=4;
//colOut=13;
//Lit=0;
//colF=((Fb-Fl)/500)*8;
//--------------проверка правильности заполнения таблицы------------------------
// for(nl=0;nl<=3;nl++)   /* цикл по номеру луча*/
 for(nl=0;nl<=7;nl++)   /* цикл по номеру луча*/
  {
//  for(k=0; k<=63; k++) /* по частоте*/
  for(k=0; k<=159; k++) /* по частоте*/
   {
    res=TryStrToFloat(SG53_mrt->Cells[1][nl*160+k+(nl+2)],P_in_att[nl][k]);
      if(res==false)
         {
         ShowMessage("Неправильно введено значение Код вх.атт: луч "+IntToStr(nl+1)+"в столбце 1 и строке "+FloatToStr(F_rtu[k]));
         goto m1;
         }
   //  P_in_att[nl][k]=StrToFloat(SG2->Cells[1][nl*64+k+(nl+2)]);

     res=TryStrToFloat(SG53_mrt->Cells[2][nl*160+k+(nl+2)],dP_osl_0[nl][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт1: луч "+IntToStr(nl+1)+" строка "+FloatToStr(F_rtu[k]));
         goto m1;
         }

     res=TryStrToFloat(SG53_mrt->Cells[3][nl*160+k+(nl+2)],dP_osl_1[nl][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт2: луч "+IntToStr(nl+1)+" строка "+FloatToStr(F_rtu[k]));
         goto m1;
         }

     res=TryStrToFloat(SG53_mrt->Cells[4][nl*160+k+(nl+2)],dP_osl_2[nl][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт3: луч "+IntToStr(nl+1)+" строка "+FloatToStr(F_rtu[k]));
         goto m1;
         }
      res=TryStrToFloat(SG53_mrt->Cells[5][nl*160+k+(nl+2)],dP_osl_3[nl][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт4: луч "+IntToStr(nl+1)+" строка "+FloatToStr(F_rtu[k]));
         goto m1;
         }
      res=TryStrToFloat(SG53_mrt->Cells[6][nl*160+k+(nl+2)],dP_osl_4[nl][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт5: луч "+IntToStr(nl+1)+" строка "+FloatToStr(F_rtu[k]));
         goto m1;
         }

      res=TryStrToFloat(SG53_mrt->Cells[7][nl*160+k+(nl+2)],dP_osl_5[nl][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт6: луч "+IntToStr(nl+1)+" строка "+FloatToStr(F_rtu[k]));
         goto m1;
         }
      res=TryStrToFloat(SG53_mrt->Cells[8][nl*160+k+(nl+2)],dP_osl_6[nl][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт7: луч "+IntToStr(nl+1)+" строка "+FloatToStr(F_rtu[k]));
         goto m1;
         }
      res=TryStrToFloat(SG53_mrt->Cells[9][nl*160+k+(nl+2)],dP_osl_7[nl][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт8: луч "+IntToStr(nl+1)+" строка "+FloatToStr(F_rtu[k]));
         goto m1;
         }
      res=TryStrToFloat(SG53_mrt->Cells[10][nl*160+k+(nl+2)],dP_osl_8[nl][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт9: луч "+IntToStr(nl+1)+" строка "+FloatToStr(F_rtu[k]));
         goto m1;
         }
       res=TryStrToFloat(SG53_mrt->Cells[11][nl*160+k+(nl+2)],dP_osl_9[nl][k]);
       if(res==false)
         {
         ShowMessage("Неправильно введено значение Код атт10: луч "+IntToStr(nl+1)+" строка "+FloatToStr(F_rtu[k]));
         goto m1;
        }
     res=TryStrToFloat(SG53_mrt->Cells[12][nl*160+k+(nl+2)],dP_osl_10[nl][k]);
       if(res==false)
        {
         ShowMessage("Неправильно введено значение Код атт11: луч "+IntToStr(nl+1)+" строка "+FloatToStr(F_rtu[k]));
         goto m1;
        }
      res=TryStrToFloat(SG53_mrt->Cells[13][nl*160+k+(nl+2)],dP_osl_11[nl][k]);
       if(res==false)
        {
         ShowMessage("Неправильно введено значение Код атт12: луч "+IntToStr(nl+1)+" строка "+FloatToStr(F_rtu[k]));
         goto m1;
        }
  //    res=TryStrToFloat(SG2->Cells[14][nl*160+k+(nl+2)],dP_osl_12[nl][k]);
  //     if(res==false)
  //      {
  //       ShowMessage("Неправильно введено значение Код атт13: луч "+IntToStr(nl+1)+" строка "+FloatToStr(F_rtu[k]));
  //       goto m1;
  //      }

     }  /* end k по частоте*/
 }   /* end nl по лучам*/

// StrDir=GetCurrentDir();  для новой директории

 StIn=SbS+"_"+StNIn+SbL+".mrt";
// MyFileName=StrDir+"\\PowMesh\\"+StIn;
 MyFileName=StIn;
 if(FileExists(MyFileName))
 {
   n_vh=StrToInt(StNIn);
 if(MessageDlg("Перезаписать файл МРТ для Входа "+StNIn+" Литеры "+SbL+SbS_t+"?",
     mtConfirmation,TMsgDlgButtons() << mbYes<< mbNo,0) == mrYes)
    {
      ShowMessage("Файл будет перезаписан");
    }
   else goto m1;

//=====================================================
 if((tr = fopen(MyFileName.c_str(),"w+")) == NULL)
  {
  ShowMessage("Нет файла");
  goto m1;
 }

// for(nl=0;nl<=3;nl++)   /* цикл по номеру луча*/
 for(nl=0;nl<=7;nl++)   /* цикл по номеру луча*/
  {
  for(k=0; k<=159; k++) /* по частоте*/
   {
 //    bool res=TryStrToFloat(SG2->Cells[1][nl*64+k+(nl+2)],P_in_att[nl][k]);
 //     if(res==false)
 //      {
 //        ShowMessage("Неправильно введено значение Код вх.атт в столбце 1 и строке "+IntToStr(nl*64+k+(nl+2)));
 //       goto m1;
 //       }

  /* dP_osl_0[nl][k]=StrToFloat(SG2->Cells[2][nl*64+k+(nl+2)]);
     dP_osl_1[nl][k]=StrToFloat(SG2->Cells[3][nl*64+k+(nl+2)]);
     dP_osl_2[nl][k]=StrToFloat(SG2->Cells[4][nl*64+k+(nl+2)]);
     dP_osl_3[nl][k]=StrToFloat(SG2->Cells[5][nl*64+k+(nl+2)]);
     dP_osl_4[nl][k]=StrToFloat(SG2->Cells[6][nl*64+k+(nl+2)]);
     dP_osl_5[nl][k]=StrToFloat(SG2->Cells[7][nl*64+k+(nl+2)]);
     dP_osl_6[nl][k]=StrToFloat(SG2->Cells[8][nl*64+k+(nl+2)]);
     dP_osl_7[nl][k]=StrToFloat(SG2->Cells[9][nl*64+k+(nl+2)]);
     dP_osl_8[nl][k]=StrToFloat(SG2->Cells[10][nl*64+k+(nl+2)]);
     dP_osl_9[nl][k]=StrToFloat(SG2->Cells[11][nl*64+k+(nl+2)]);
     dP_osl_10[nl][k]=StrToFloat(SG2->Cells[12][nl*64+k+(nl+2)]);
     dP_osl_11[nl][k]=StrToFloat(SG2->Cells[13][nl*64+k+(nl+2)]);
     dP_osl_12[nl][k]=StrToFloat(SG2->Cells[14][nl*64+k+(nl+2)]);
  */
        fprintf(tr,"%d ",k);
         fprintf(tr,"%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",P_in_att[nl][k],dP_osl_0[nl][k],
                 dP_osl_1[nl][k],dP_osl_2[nl][k],dP_osl_3[nl][k],dP_osl_4[nl][k],dP_osl_5[nl][k],dP_osl_6[nl][k],
                 dP_osl_7[nl][k],dP_osl_8[nl][k],dP_osl_9[nl][k],dP_osl_10[nl][k],dP_osl_11[nl][k]);//,dP_osl_12[nl][k]);

       }  /* end k по частоте*/
 }   /* end nl по лучам*/

}/* if*/
   fclose(tr);
   
m1:;

}
//-----------------------Выход----------------------------------------------------
void __fastcall TForm1::Button27Click(TObject *Sender)
{
  Panel7->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button28Click(TObject *Sender)
{
  Panel8->Visible=false;
}
//---------------------АЧХ------------------------------------------------------
void __fastcall TForm1::Button34Click(TObject *Sender)
{
 if(ChkDevs==true)       /** убрать комментарии для работы ***/
 Calib53_ACHX();
 else
 {
 if(FindDevises()==true)
  {
  if(ChekDev()==true)
  Calib53_ACHX();
 }    //FindDevises()
 }//else
}
//---------------------АЧХ------------------------------------------------------
void TForm1::Calib53_ACHX(void)
{
extern bool vyh;
  ViStatus stat=0; // объявление переменной типа ViStatus
  extern double F_rtu[224];

   double powerDBM=0.0;
   double m_freqq;
   double power;

   double K_nu=0.0;

 //char buf1[256]={0};
// char buf2[256]={0};

 char buf[256]={0};

// double m_freqq_n;
 //double m_freqq_v;

  double P[160]={0.0};       /*измеренное значение в Вт*/
  double P_dB[160]={0.0};    /*измеренное значение в дБ*/

  double P_1=0;
  //double dP;
  double p_vt_izm;
  double P_max,P_min;
  float Pmin_v,Pmax_v,dP;
  int j,k,k1;
 //int num=0;
 //char rdbuffer[256]={0};

 int ind; //индекс доступа к массивам калибровки
 long longdown=0; /* ожидание операции завершения*/

 int m_p;
 float x_m_p;
 double m_p_1;  /* мощность, задаваемая на генераторе*/

 int k_att=0;
// int k_max=0,k_min=0;

 double m_Pow;
 char buf1[256]={0};
  int n_post;
  unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
   int nk,nu;  /* номер КИО*/
                                  /* входной атт */
  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/
/* float Qvh_osl[32]={0.0,-0.75,-1.5,-2.25,-3.0,-3.75,-4.5,-5.25,-6.0,
                     -6.75,-7.5,-8.25,-9.0,-9.75,-10.5,-11.25,-12.0,
                     -12.75,-13.5,-14.25,-15.0,-15.75,-16.5,-17.25,-18.0,
                     -18.75,-19.5,-20.25,-21.0,-21.75,-22.5,-23.25};
*/
                  /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/
 float Qvh_osl[32]={-23.25,-22.5,-21.75,-21.0,-20.25,-19.5,-18.75,-18.0,
                     -17.25,-16.5,-15.75,-15.0,-14.25,-13.5,-12.75,-12.0,
                     -11.25,-10.5,-9.75,-9.0,-8.25,-7.5,-6.75,-6.0,-5.25,
                     -4.5,-3.75,-3.0,-2.25,-1.5,-0.75,0.0};

                     /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/


  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* выходной атт */
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned kod_att[12];

  AnsiString str2[24]={"ППС1","ППС2","ППС3","ППС4",
                       "ППС5","ППС6","ППС7","ППС8",
                       "ППС9","ППС10","ППС11","ППС12",
                       "ЗПС1","ЗПС2","ЗПС3","ЗПС4",
                       "ЗПС5","ЗПС6","ЗПС7","ЗПС8",
                       "ЗПС9","ЗПС10","ЗПС11","ЗПС12"};
  AnsiString str1[4]={"1ВЧ-53","2ВЧ-53","3ВЧ-53","4ВЧ-53"};

  TChartSeries *Series[4]={LineSeries1,LineSeries2,LineSeries7,LineSeries8};

  u32 buf_my[256/4]; // Буфер для принятого пакета

  union{
       struct{
                  U32   len     : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8,
                        byte5   : 8;
              } p_my_v;
             U32 buf_my[256/4];
            } packet_my;
    union{
       struct{
                  U32   len     : 8, /*LEN*/
                        byte1   : 8, /*IPK*/
                        byte2   : 8, /*DST SRC*/
                        byte3   : 8, /*IPS DST*/
                        byte4   : 8, /*ERR*/
                        /*byte5   : 8,*/  /*ADR_UP7*/
                        byte5   : 8, /*IPK_UP7*/
                        byte6   : 8, /*ADC1 */
                        byte7   : 8, /*ADC2 */
                        byte8   : 8, /*ADC3 */
                        byte9   : 8, /*ADC4 */
                        byte10  : 8, /*ADC5 */
                        byte11  : 8, /*ADC6 */
                        byte12  : 8, /*ADC7 */
                        byte13  : 8, /*ADC8 */
                        byte14  : 8, /*ADC9 */
                        byte15  : 8, /*ADC10 */
                        byte16  : 8, /*ADC11 */
                        byte17  : 8; /*ADC12 */
                    //    byte18  : 8; /*ADC13 */

                        } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;
       unsigned ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8,ADC9,ADC10,ADC11,ADC12,ADC13=0x0;
       int ADC=0;
       unsigned IPK_UP7;
       float Kod_M[160]={0.0};

       int Kod_DM_izm[160]={0};
       int Kod_DM_max=0;
       int Kod_min_km=0,Kod_max_km=0;
       int nf,n_jj;
       int mk;

              E_53_izm_m->Text=" ";
              E_53_izm_m->Repaint();

        Series[0]->Clear();
        Series[1]->Clear();
        Series[2]->Clear();
        Series[3]->Clear();

        Chart3->BottomAxis->SetMinMax(0,159);
        Chart3->Title->Text->Clear();
        Chart3->Title->Text->Add("P=P(f)");

       // Series[3]->Repaint();
         Ep53_max->Text="";
         L53_pmax_no->Caption="";

          E53_km_s->Text="";
          E53_km_mx->Text="";

          E53_dm_2->Text="";

          Edit1->Text=" ";
          Edit2->Text="";
          Edit3->Text="";

   /*   for(k=0; k<=34; k++)
        {
         P[k]=0.0;
        }
     */

        ShowMessage("Подать сигнал с ВЧ генератора на вход "+str1[CB_53_vh->ItemIndex]);

        ShowMessage("Подключить измеритель мощности через аттенюатор 30дБ к выходу "+str2[CB_53_vyh->ItemIndex]);


  /*  if(comm_vhod(CB_53_vh->ItemIndex+4))  //1 -- ошибка, 0 -- без ошибок
           {
             ShowMessage("Не сработал коммутатор 1");
             goto end;
             }
     if(comm_vyhod(CB_53_vyh->ItemIndex))//1 -- ошибка, 0 -- без ошибок
            {
             ShowMessage("Не сработал коммутатор 2");
             goto end;
             }
   */
      Chart3->Repaint();

        /* пакет 3*/
    for(i=0;i<=11;i++)
      {
      // US[i]=0x0;
       kod_att[i]=0xF;
      }
  //============/* формуляр задание кода выходных атт */====
   if(CB_53_vyh->ItemIndex<=11)
   {
    n_post=0;    /*ППС*/
    kod_att[CB_53_vyh->ItemIndex]= Q_vh[CB_53_att_vyh->ItemIndex];
   }
  if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
    kod_att[CB_53_vyh->ItemIndex-12]= Q_vh[CB_53_att_vyh->ItemIndex];/****?????****/
    }

   if((res=Vkl_att_t(n_post,kod_att))==1)   /*0-- нет ошибок, 1-- есть ошибки */
     {
      ShowMessage("Ошибка при передаче формуляра 3 данных в УП7 ERR=1!\n");
      //goto end;
     }
 if(res==2) {ShowMessage("Нет ответных пакетов на пакет 3!");}
           Sleep(1);


              /* пакет 1*/
//-----------------формуляр передачи данных в УП7 -------------------------------------------------------
 //============/* включение канала усилителя, включение источника питания УП7 */========================================            /* пакет 1*/
  //n_post=2+(CB_2_ps->ItemIndex);
  if(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
   {
    n_post=0;    /*ППС*/
    nu=(CB_53_vyh->ItemIndex);    /*индекс от 0 до 12*/  /* nu-- номер усилителя*/
    }
   if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
    nu=(CB_53_vyh->ItemIndex)-12;    /*индекс от 13 до 25*/  /* nu-- номер усилителя*/
    }
  // nu=0;  /* ???? nu-- nu=(номер усилителя*/

   if((res=Vkl_us_vip_t(n_post,nu))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных (1) в УП7!\n");
    // goto end;
    }
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");}
    Sleep(1);
 //*************************************************************************
   m_freqq=F_rtu[64];
   //m_freqq = strtod(E2_f->Text.c_str(),NULL);

   powerDBM = strtod(E53_p->Text.c_str(),NULL);

   K_nu = strtod(E_ks_53->Text.c_str(),NULL);
   if((K_nu>3.0)||(K_nu<0.0))
   {
    ShowMessage("Неверное значение константы насыщения");
    goto end;
   }

    K_nu=(3.0-K_nu)/4.0;

//  for(k=64; k<=223;k++) /* определение ind*/
//     {
//      if(F_rtu[k]==m_freqq){ind=k;break;}
//     }
   m_p_1=powerDBM-dPg[64];   /* с учетом калибровки кабеля */

 /*15.12.10*/ //    power = -70.0;  //отладка

 // Установка на генератор частоты и мощности
 stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // частота
 stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // мощность
  if (stat != VI_SUCCESS)
  {
     ShowMessage("Ошибка при установке значений на генератор");
     goto end;
  }
 // viPrintf(vigen,"PULM:STAT OFF\n");   // ВКЛючить имп модуляцию
   viPrintf(viG,"OUTPut:STATe ON\n"); //подкл.  сигнала на выход ген-ра

    longdown=0;

    viPrintf(viG,"*OPC?\n");

        while(!longdown)
    viScanf(viG,"%d", &longdown);

    viPrintf(viP,"ABORT\n");
   viPrintf(viP,"INIT:CONT ON\n");
   viPrintf(viP,"FETC?\n");
   viScanf(viP,"%t",buf);

    Sleep(1);

    //  pn=-23.25;
   //  pv=0.0;
   //  pstep=0.75;
            /* пакет 2*/
    /*  сначала выключаем неиспользываемые номера выходов матрицы ПМ */
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение матрицы для  1-го и 2-го канала СВЧ */=========================
          n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/

  if(CB_53_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
      if(CB_53_vyh->ItemIndex>11) /* если выбран ППС, то выключаем ЗПС*/
           n_post=1; /*ЗПС*/   /* если выбран ППС, то выключаем ЗПС*/
           else  n_post=0;  nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           if(CB_53_vyh->ItemIndex<=11) /* если выбран ППС, то выключаем ЗПС*/
                 n_post=1;
           else  n_post=0; nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
         if(CB_53_vyh->ItemIndex<=11) /* если выбран ЗПС, то выключаем ППС*/
                 n_post=0;
           else  n_post=1;  nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
          if(CB_53_vyh->ItemIndex<=11) /* если выбран ЗПС, то выключаем ППС*/
              n_post=0;
           else  n_post=1; nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7!\n");
     //goto end;
    }

  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
   Sleep(1);
      /* пакет 2*/
 //============/* включение номера выхода матрицы ПМ для 1-ого и 2-ого канала */========================================
//============/* задание кода входных атт для 1-ого и 2-ого канала */==========================
   /* n_vh1 -- номер выхода матрицы для 1-ого канала СВЧ 0--0xF (4 разряда)*/
   /* n_vh2 -- номер выхода матрицы для 2-ого канала СВЧ 0--0xF (4 разряда)*/

       n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/
  if(CB_53_vh->ItemIndex==0){in1_at=Qv_vh[CB_53_att_vh->ItemIndex];in2_at=0x1F;n_post=0;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[CB_53_att_vh->ItemIndex];n_post=0;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=Qv_vh[CB_53_att_vh->ItemIndex];in2_at=0x1F;n_post=1;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[CB_53_att_vh->ItemIndex];n_post=1;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

   if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7 ERR=1!\n");
     goto end1;
    }

    /* Прием ответного пакета */
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
       Sleep(5);

      vyh=true;

 // for(j=0; j<=63;j++)  /* литера 2*/
 for(j=64; j<=223;j++)  /* литера 53*/
  {
  // Application->ProcessMessages();
 //  if(vyh==false) goto end1;

    m_freqq=F_rtu[j];
    m_p_1=powerDBM-dPg[j];   /* с учетом калибровки кабеля */
    stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // частота
     stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // мощность
  if (stat != VI_SUCCESS)
  {
     ShowMessage("Ошибка при установке значений на генератор");
     goto end;
  }

    viPrintf(viP,"ABORT\n");
    viPrintf(viP,"INIT:CONT ON\n");
    viPrintf(viP,"FETC?\n");
    viScanf(viP,"%t",buf);

    m_Pow = atof(buf);
//  for(k=64; k<=223;k++) /* определение ind*/
//     {
//      if(F_rtu[k]==m_freqq){ind=k;break;}
//     }

      ind=j;
   m_Pow=m_Pow-dPm[ind];   /*с учетом калибровки кабеля*/
    P_dB[j-64]=m_Pow;

        //  Pw=pow(10,Pdbm/10); //мВт       Pw=pow(10,-3)*pow(10,Pdbm/10);  //Вт

          m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

          P[j-64]=m_Pow;  /* значение в Вт */
         //  x_m_p=Qvh_osl[j];

        /* чтение датчика мощности */
                   /* запрос кода мощности */
                         /* пакет 9*/
//-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//----------------Чтение уровня мощности для каналов усилителей------------------------------
 // if((CB_53_vh->ItemIndex==0)||(CB_53_vh->ItemIndex==1))
//   {
//  n_post=2; /*ППС*/
//   }
//  if((CB_53_vh->ItemIndex==2)||(CB_53_vh->ItemIndex==3))
//    {
//      n_post=3; /*ЗПС*/
//    }
 if(CB_53_vyh->ItemIndex<=11)  /* в зависимости от выхода */     {
     n_post=0; /**/
     }
  if(CB_53_vyh->ItemIndex>11)
     {
     n_post=1; /**/
     }
    nf=0x9;
 n_jj=0;

m_jj:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- нет ошибок, 1-- есть ошибки */
   {
     ShowMessage("Ошибка при передаче формуляра запроса данных (9) в УП7!\n");
    // 10.01.11 vyh=false; goto end;
   }

  Sleep(10);
//17.07 if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07        // Нет принятых пакетов
//17.07 //     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07   }

  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
//17.07        // Нет принятых пакетов
//17.07 //     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07      if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("Сбой по магистрале!");
//17.07       vyh=false; goto end; //goto m2_end_5;
//17.07      }
   }
   else
   {
        // Принят пакет

      LEN=packet_my_km.p_my_v.len;
      IPK=packet_my_km.p_my_v.byte1;
      SRC=packet_my_km.p_my_v.byte2&0x1F;
      DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* левое крыло DST=0x6, правое крыло DST=0x7*/
      IPS=(packet_my_km.p_my_v.byte3>>2)&0x3F;
      ERR=packet_my_km.p_my_v.byte4&0x1;
       /* ADR_UP7=packet_my_km.p_my_v.byte5;*/
      IPK_UP7=packet_my_km.p_my_v.byte5;
      ADC1=packet_my_km.p_my_v.byte6;
      ADC2=packet_my_km.p_my_v.byte7;
      ADC3=packet_my_km.p_my_v.byte8;
      ADC4=packet_my_km.p_my_v.byte9;
      ADC5=packet_my_km.p_my_v.byte10;
      ADC6=packet_my_km.p_my_v.byte11;
      ADC7=packet_my_km.p_my_v.byte12;
      ADC8=packet_my_km.p_my_v.byte13;
      ADC9=packet_my_km.p_my_v.byte14;
      ADC10=packet_my_km.p_my_v.byte15;
      ADC11=packet_my_km.p_my_v.byte16;
      ADC12=packet_my_km.p_my_v.byte17;
     // ADC13=packet_my_km.p_my_v.byte18;

// 22.12.10
     if(CB_53_vyh->ItemIndex<=11)  /* в зависимости от выхода */
       {
        if(CB_53_vyh->ItemIndex==0) ADC=ADC1&0xFF;
        if(CB_53_vyh->ItemIndex==1) ADC=ADC2&0xFF;
        if(CB_53_vyh->ItemIndex==2) ADC=ADC3&0xFF;
        if(CB_53_vyh->ItemIndex==3) ADC=ADC4&0xFF;
        if(CB_53_vyh->ItemIndex==4) ADC=ADC5&0xFF;
        if(CB_53_vyh->ItemIndex==5) ADC=ADC6&0xFF;
        if(CB_53_vyh->ItemIndex==6) ADC=ADC7&0xFF;
        if(CB_53_vyh->ItemIndex==7) ADC=ADC8&0xFF;
        if(CB_53_vyh->ItemIndex==8) ADC=ADC9&0xFF;
        if(CB_53_vyh->ItemIndex==9) ADC=ADC10&0xFF;
        if(CB_53_vyh->ItemIndex==10) ADC=ADC11&0xFF;
        if(CB_53_vyh->ItemIndex==11) ADC=ADC12&0xFF;
//        if(CB_10_vyh->ItemIndex==12) ADC=ADC13&0xFF;
      }
    if(CB_53_vyh->ItemIndex>11)  /* в зависимости от выхода */
      {
        if(CB_53_vyh->ItemIndex==12) ADC=ADC1&0xFF;
        if(CB_53_vyh->ItemIndex==13) ADC=ADC2&0xFF;
        if(CB_53_vyh->ItemIndex==14) ADC=ADC3&0xFF;
        if(CB_53_vyh->ItemIndex==15) ADC=ADC4&0xFF;
        if(CB_53_vyh->ItemIndex==16) ADC=ADC5&0xFF;
        if(CB_53_vyh->ItemIndex==17) ADC=ADC6&0xFF;
        if(CB_53_vyh->ItemIndex==18) ADC=ADC7&0xFF;
        if(CB_53_vyh->ItemIndex==19) ADC=ADC8&0xFF;
        if(CB_53_vyh->ItemIndex==20) ADC=ADC9&0xFF;
        if(CB_53_vyh->ItemIndex==21) ADC=ADC10&0xFF;
        if(CB_53_vyh->ItemIndex==22) ADC=ADC11&0xFF;
        if(CB_53_vyh->ItemIndex==23) ADC=ADC12&0xFF;
       // if(CB_10_vyh->ItemIndex==24) ADC=ADC13&0xFF;
       // if(CB_10_vyh->ItemIndex==25) ADC=ADC13&0xFF;
      }

        if(ERR==1)
         {
          //ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении кода мощности! ERR=1");
          //goto m1;
           n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj;
            }
          else
            {
             ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении кода мощности! ERR=1");
             goto m1_1;
            }
          }

         Kod_DM_izm[j-64]=ADC;
         Kod_M[j-64]=0.017*ADC;


         /*  memset(&buf1,0,20);
           sprintf(buf1,"%d",ADC);

           E_2_um->Text=buf1;
           E_2_um->Repaint();
         */
       m1_1:;
     }
//    m2_end_5:;
 //   m2_end_3:;
 //====================================
          Sleep(10);
        x_m_p=j-64;
        Series[3]->AddXY(x_m_p,P[j-64]);
        Series[3]->Repaint();

        Series[0]->AddXY(x_m_p,Kod_M[j-64]);
        Series[0]->Repaint();

        Chart3->Repaint();

   }    /* end for по частоте */


 /*    for(k=0;k<=159;k++)
       {
         x_m_p=k;
         Series[3]->AddXY(x_m_p,P[k]);
       }
     for(k=0;k<=159;k++)
       {
         x_m_p=k;
         Series[0]->AddXY(x_m_p,Kod_M[k]);
       }
  */

   for(k1=0,P_max=P_min=P[0]; k1<=159; k1+=1)  /* вычисление max на кривой */
       {
        if(P[k1]>P_max) {P_max=P[k1];}//k_max=k1;}
        if(P[k1]<P_min) {P_min=P[k1];}//k_min=k1;}
       }

      Pmin_v=(float)P_min;
      Pmax_v=(float)P_max;
      dP=(float)fabs(P_max-P_min);

        memset(&buf1,0,20);
        sprintf(buf1,"%.2f",Pmin_v);
           Edit1->Text=buf1;
           Edit1->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%.2f",Pmax_v);

           Edit2->Text=buf1;
           Edit2->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%.2f",dP);

           Edit3->Text=buf1;
           Edit3->Repaint();

    for(k1=0,Kod_max_km=Kod_min_km=Kod_DM_izm[0]; k1<=159; k1+=1)  /* вычисление max на кривой */
       {
        if(Kod_DM_izm[k1]>Kod_max_km) {Kod_max_km=Kod_DM_izm[k1];}//k_max=k1;}
        if(Kod_DM_izm[k1]<Kod_min_km) {Kod_min_km=Kod_DM_izm[k1];}//k_min=k1;}
       }

     //  dP=(float)fabs(P_max-P_min);

        memset(&buf1,0,20);
        sprintf(buf1,"%d",Kod_min_km);
           Edit4->Text=buf1;
           Edit4->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%d",Kod_max_km);

           Edit5->Text=buf1;
           Edit5->Repaint();

   end1:;                         /* пакет 2 */
 //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение м атрицы для  1-го и 2-го канала СВЧ */=========================
          n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/

  if(CB_53_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;n_post=0;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;n_post=0;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;n_post=1;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;n_post=1;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7 ERR=1!\n");
     //goto end;
    }
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
     Sleep(1);
                         /* пакет 1*/
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение канала усилителя, выключение источника питания УП7 */=========================
 if(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
   {
    n_post=0;    /*ППС*/
   // nu=(CB_10_vyh->ItemIndex);    /*индекс от 0 до 12*/  /* nu-- номер усилителя*/
    }
   if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
   // nu=12-(CB_53_vyh->ItemIndex);    /*индекс от 13 до 25*/  /* nu-- номер усилителя*/
    }
  // nu=0;  /* ???? nu-- nu=(номер усилителя*/

   if((res=Vykl_us_vip_t(n_post))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных (1) в УП7 ERR=1!\n");
    // goto end;
    }
    if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");}
    Sleep(1);
   end:;
  viPrintf(viG,"OUTPut:STATe OFF\n"); //выкл. сигнала на выход ген-ра

    ShowMessage("Измерение закончено\n");
}
//--------------------------АЧХ ручное ------------------------------------------------
void __fastcall TForm1::Button35Click(TObject *Sender)
{
  if(ChkDevs==true)       /** убрать комментарии для работы ***/
 ACHX53_rucn();
 else
 {
 if(FindDevises()==true)
  {
  if(ChekDev()==true)
  ACHX53_rucn();
 }    //FindDevises()
 }//else
}
//---------------------------------------------------------------------------
//---------------------АЧХ  ручное ------------------------------------------------------
void TForm1::ACHX53_rucn(void)
{
 extern bool vyh;
 extern bool circle;
  ViStatus stat=0; // объявление переменной типа ViStatus
  extern double F_rtu[224];

   double powerDBM=0.0;
   double m_freqq;
   double power;

   double K_nu=0.0;

 //char buf1[256]={0};
// char buf2[256]={0};

 char buf[256]={0};

 // double P[160]={0.0};       /*измеренное значение в Вт*/
 // double P_dB[160]={0.0};    /*измеренное значение в дБ*/

  double P_1=0;
  //double dP;
  double p_vt_izm;
    int j,k,k1;
 //int num=0;
 //char rdbuffer[256]={0};

 int ind; //индекс доступа к массивам калибровки
 long longdown=0; /* ожидание операции завершения*/

 int m_p;
 float x_m_p;
 double m_p_1;  /* мощность, задаваемая на генераторе*/
 int k_att=0;
 int k_max=0,k_min=0;

 double m_Pow;
 float P_izm;
 char buf1[256]={0};
  int n_post;
  unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
   int nk,nu;  /* номер КИО*/
                                  /* входной атт */
  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/
/* float Qvh_osl[32]={0.0,-0.75,-1.5,-2.25,-3.0,-3.75,-4.5,-5.25,-6.0,
                     -6.75,-7.5,-8.25,-9.0,-9.75,-10.5,-11.25,-12.0,
                     -12.75,-13.5,-14.25,-15.0,-15.75,-16.5,-17.25,-18.0,
                     -18.75,-19.5,-20.25,-21.0,-21.75,-22.5,-23.25};
*/
                  /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/
 float Qvh_osl[32]={-23.25,-22.5,-21.75,-21.0,-20.25,-19.5,-18.75,-18.0,
                     -17.25,-16.5,-15.75,-15.0,-14.25,-13.5,-12.75,-12.0,
                     -11.25,-10.5,-9.75,-9.0,-8.25,-7.5,-6.75,-6.0,-5.25,
                     -4.5,-3.75,-3.0,-2.25,-1.5,-0.75,0.0};

                     /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/


  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* выходной атт */
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned kod_att[12];

  AnsiString str2[24]={"ППС1","ППС2","ППС3","ППС4",
                       "ППС5","ППС6","ППС7","ППС8",
                       "ППС9","ППС10","ППС11","ППС12",
                       "ЗПС1","ЗПС2","ЗПС3","ЗПС4",
                       "ЗПС5","ЗПС6","ЗПС7","ЗПС8",
                       "ЗПС9","ЗПС10","ЗПС11","ЗПС12"};
  AnsiString str1[4]={"1ВЧ-53","2ВЧ-53","3ВЧ-53","4ВЧ-53"};

  TChartSeries *Series[4]={LineSeries1,LineSeries2,LineSeries7,LineSeries8};

  u32 buf_my[256/4]; // Буфер для принятого пакета

  union{
       struct{
                  U32   len     : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8,
                        byte5   : 8;
              } p_my_v;
             U32 buf_my[256/4];
            } packet_my;
    union{
       struct{
                  U32   len     : 8, /*LEN*/
                        byte1   : 8, /*IPK*/
                        byte2   : 8, /*DST SRC*/
                        byte3   : 8, /*IPS DST*/
                        byte4   : 8, /*ERR*/
                        /*byte5   : 8,*/  /*ADR_UP7*/
                        byte5   : 8, /*IPK_UP7*/
                        byte6   : 8, /*ADC1 */
                        byte7   : 8, /*ADC2 */
                        byte8   : 8, /*ADC3 */
                        byte9   : 8, /*ADC4 */
                        byte10  : 8, /*ADC5 */
                        byte11  : 8, /*ADC6 */
                        byte12  : 8, /*ADC7 */
                        byte13  : 8, /*ADC8 */
                        byte14  : 8, /*ADC9 */
                        byte15  : 8, /*ADC10 */
                        byte16  : 8, /*ADC11 */
                        byte17  : 8; /*ADC12 */
                    //    byte18  : 8; /*ADC13 */

                        } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;
       unsigned ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8,ADC9,ADC10,ADC11,ADC12,ADC13=0x0;
       int ADC=0;
       unsigned IPK_UP7;
       float Kod_M={0.0};
       int Kod_DM_izm={0};

       int nf,n_jj;
       int mk;

              E_53_izm_m->Text=" ";
              E_53_izm_m->Repaint();

        Series[0]->Clear();
        Series[1]->Clear();
        Series[2]->Clear();
        Series[3]->Clear();

        Chart3->BottomAxis->SetMinMax(0,159);
        Chart3->Title->Text->Clear();
        Chart3->Title->Text->Add("P=P(f)");

       // Series[3]->Repaint();
         Ep53_max->Text="";
         L53_pmax_no->Caption="";

          E53_km_s->Text="";
          E53_km_mx->Text="";

          E53_dm_2->Text="";

          Edit1->Text=" ";
          Edit2->Text="";
          Edit3->Text="";
          Edit6->Text=" ";

          Edit7->Text="";

        ShowMessage("Подать сигнал с ВЧ генератора на вход "+str1[CB_53_vh->ItemIndex]);

        ShowMessage("Подключить измеритель мощности через аттенюатор 30дБ к выходу "+str2[CB_53_vyh->ItemIndex]);

  /*    if(comm_vhod(CB_53_vh->ItemIndex+4))  //1 -- ошибка, 0 -- без ошибок
           {
             ShowMessage("Не сработал коммутатор 1");
             goto end;
             }
     if(comm_vyhod(CB_53_vyh->ItemIndex))//1 -- ошибка, 0 -- без ошибок
            {
             ShowMessage("Не сработал коммутатор 2");
             goto end;
             }
  */
         Chart3->Repaint();

        /* пакет 3*/
    for(i=0;i<=11;i++)
      {
      // US[i]=0x0;
       kod_att[i]=0xF;
      }
  //============/* формуляр задание кода выходных атт */====
   if(CB_53_vyh->ItemIndex<=11)
   {
    n_post=0;    /*ППС*/
    kod_att[CB_53_vyh->ItemIndex]= Q_vh[CB_53_att_vyh->ItemIndex];
   }
  if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
    kod_att[CB_53_vyh->ItemIndex-12]= Q_vh[CB_53_att_vyh->ItemIndex];/****?????****/
    }

   if((res=Vkl_att_t(n_post,kod_att))==1)   /*0-- нет ошибок, 1-- есть ошибки */
     {
      ShowMessage("Ошибка при передаче формуляра 3 данных в УП7 ERR=1!\n");
      goto end;
     }
 if(res==2) {ShowMessage("Нет ответных пакетов на пакет 3!");goto end;}
           Sleep(1);


              /* пакет 1*/
//-----------------формуляр передачи данных в УП7 -------------------------------------------------------
 //============/* включение канала усилителя, включение источника питания УП7 */========================================            /* пакет 1*/
  //n_post=2+(CB_2_ps->ItemIndex);
  if(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
   {
    n_post=0;    /*ППС*/
    nu=(CB_53_vyh->ItemIndex);    /*индекс от 0 до 12*/  /* nu-- номер усилителя*/
    }
   if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
    nu=(CB_53_vyh->ItemIndex)-12;    /*индекс от 13 до 25*/  /* nu-- номер усилителя*/
    }
  // nu=0;  /* ???? nu-- nu=(номер усилителя*/

   if((res=Vkl_us_vip_t(n_post,nu))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных (1) в УП7!\n");
     goto end;
    }
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");goto end;}
    Sleep(1);
 //*************************************************************************
   TrackBar3->Position=80;
   m_freqq=F_rtu[TrackBar3->Position+64];

   powerDBM = strtod(E53_p->Text.c_str(),NULL);

   K_nu = strtod(E_ks_53->Text.c_str(),NULL);
   if((K_nu>3.0)||(K_nu<0.0))
   {
    ShowMessage("Неверное значение константы насыщения");
    goto end;
   }

    K_nu=(3.0-K_nu)/4.0;

//  for(k=64; k<=223;k++) /* определение ind*/
//     {
//      if(F_rtu[k]==m_freqq){ind=k;break;}
//     }
   m_p_1=powerDBM-dPg[TrackBar3->Position+64];   /* с учетом калибровки кабеля */

 /*15.12.10*/ //    power = -70.0;  //отладка

 // Установка на генератор частоты и мощности
 stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // частота
 stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // мощность
  if (stat != VI_SUCCESS)
  {
     ShowMessage("Ошибка при установке значений на генератор");
     goto end;
  }
 // viPrintf(vigen,"PULM:STAT OFF\n");   // ВКЛючить имп модуляцию
   viPrintf(viG,"OUTPut:STATe ON\n"); //подкл.  сигнала на выход ген-ра

    longdown=0;

    viPrintf(viG,"*OPC?\n");

        while(!longdown)
    viScanf(viG,"%d", &longdown);

    viPrintf(viP,"ABORT\n");
   viPrintf(viP,"INIT:CONT ON\n");
   viPrintf(viP,"FETC?\n");
   viScanf(viP,"%t",buf);

    Sleep(1);
            /* пакет 2*/
    /*  сначала выключаем неиспользываемые номера выходов матрицы ПМ */
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение матрицы для  1-го и 2-го канала СВЧ */=========================
          n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/

  if(CB_53_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
      if(CB_53_vyh->ItemIndex>11) /* если выбран ППС, то выключаем ЗПС*/
           n_post=1; /*ЗПС*/   /* если выбран ППС, то выключаем ЗПС*/
           else  n_post=0;  nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           if(CB_53_vyh->ItemIndex<=11) /* если выбран ППС, то выключаем ЗПС*/
                 n_post=1;
           else  n_post=0; nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
         if(CB_53_vyh->ItemIndex<=11) /* если выбран ЗПС, то выключаем ППС*/
                 n_post=0;
           else  n_post=1;  nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
          if(CB_53_vyh->ItemIndex<=11) /* если выбран ЗПС, то выключаем ППС*/
              n_post=0;
           else  n_post=1; nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7!\n");
     goto end;
    }

  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
   Sleep(1);
      /* пакет 2*/
 //============/* включение номера выхода матрицы ПМ для 1-ого и 2-ого канала */========================================
//============/* задание кода входных атт для 1-ого и 2-ого канала */==========================
   /* n_vh1 -- номер выхода матрицы для 1-ого канала СВЧ 0--0xF (4 разряда)*/
   /* n_vh2 -- номер выхода матрицы для 2-ого канала СВЧ 0--0xF (4 разряда)*/

       n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/
  if(CB_53_vh->ItemIndex==0){in1_at=Qv_vh[CB_53_att_vh->ItemIndex];in2_at=0x1F;n_post=0;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[CB_53_att_vh->ItemIndex];n_post=0;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=Qv_vh[CB_53_att_vh->ItemIndex];in2_at=0x1F;n_post=1;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[CB_53_att_vh->ItemIndex];n_post=1;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

   if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7 ERR=1!\n");
     goto end;
    }

    /* Прием ответного пакета */
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
       Sleep(5);

   Series[1]->Clear();
   Series[3]->Clear();

  //   TrackBar3->Position=80;

     circle=true;             /*  циклически */
  while(circle==true)
    {
     Application->ProcessMessages();
     m_freqq=F_rtu[TrackBar3->Position+64];
   // m_freqq=F_rtu[j];
  //  m_p_1=powerDBM-dPg[j];   /* с учетом калибровки кабеля */
    m_p_1=powerDBM-dPg[TrackBar3->Position+64];   /* с учетом калибровки кабеля */
    stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // частота
     stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // мощность
  if (stat != VI_SUCCESS)
  {
     ShowMessage("Ошибка при установке значений на генератор");
     goto end;
  }

    viPrintf(viP,"ABORT\n");
    viPrintf(viP,"INIT:CONT ON\n");
    viPrintf(viP,"FETC?\n");
    viScanf(viP,"%t",buf);

    m_Pow = atof(buf);
    ind=TrackBar3->Position+64;
   m_Pow=m_Pow-dPm[TrackBar3->Position+64];   /*с учетом калибровки кабеля*/
    // P_dB[j-64]=m_Pow;

        //  Pw=pow(10,Pdbm/10); //мВт       Pw=pow(10,-3)*pow(10,Pdbm/10);  //Вт

          m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

         P_izm=(float)m_Pow;  /* значение в Вт */

        memset(&buf1,0,20);  /* вывод на экран */
        sprintf(buf1,"%.2f",P_izm);
           Edit6->Text=buf1;
           Edit6->Repaint();

           Sleep(10);
       // x_m_p=j-64;
        x_m_p=TrackBar3->Position;
        Series[1]->AddXY(x_m_p,P_izm);
        Series[1]->Repaint();

        Chart3->Repaint();

        /* чтение датчика мощности */
                   /* запрос кода мощности */
                         /* пакет 9*/
//-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//----------------Чтение уровня мощности для каналов усилителей------------------------------
 // if((CB_53_vh->ItemIndex==0)||(CB_53_vh->ItemIndex==1))
//   {
//  n_post=2; /*ППС*/
//   }
//  if((CB_53_vh->ItemIndex==2)||(CB_53_vh->ItemIndex==3))
//    {
//      n_post=3; /*ЗПС*/
//    }
 if(CB_53_vyh->ItemIndex<=11)  /* в зависимости от выхода */     {
     n_post=0; /**/
     }
  if(CB_53_vyh->ItemIndex>11)
     {
     n_post=1; /**/
     }
    nf=0x9;
 n_jj=0;

m_jj:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- нет ошибок, 1-- есть ошибки */
   {
     ShowMessage("Ошибка при передаче формуляра запроса данных (9) в УП7!\n");
     circle=false; goto end;
   }

  Sleep(10);
//17.07 if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07        // Нет принятых пакетов
//17.07 //     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07   }

  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
//17.07        // Нет принятых пакетов
//17.07//     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07      if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("Сбой по магистрале!");
//17.07       circle=false; goto end; //goto m2_end_5;
//17.07      }
   }
   else
   {
        // Принят пакет

      LEN=packet_my_km.p_my_v.len;
      IPK=packet_my_km.p_my_v.byte1;
      SRC=packet_my_km.p_my_v.byte2&0x1F;
      DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* левое крыло DST=0x6, правое крыло DST=0x7*/
      IPS=(packet_my_km.p_my_v.byte3>>2)&0x3F;
      ERR=packet_my_km.p_my_v.byte4&0x1;
       /* ADR_UP7=packet_my_km.p_my_v.byte5;*/
      IPK_UP7=packet_my_km.p_my_v.byte5;
      ADC1=packet_my_km.p_my_v.byte6;
      ADC2=packet_my_km.p_my_v.byte7;
      ADC3=packet_my_km.p_my_v.byte8;
      ADC4=packet_my_km.p_my_v.byte9;
      ADC5=packet_my_km.p_my_v.byte10;
      ADC6=packet_my_km.p_my_v.byte11;
      ADC7=packet_my_km.p_my_v.byte12;
      ADC8=packet_my_km.p_my_v.byte13;
      ADC9=packet_my_km.p_my_v.byte14;
      ADC10=packet_my_km.p_my_v.byte15;
      ADC11=packet_my_km.p_my_v.byte16;
      ADC12=packet_my_km.p_my_v.byte17;
     // ADC13=packet_my_km.p_my_v.byte18;

// 22.12.10
     if(CB_53_vyh->ItemIndex<=11)  /* в зависимости от выхода */
       {
        if(CB_53_vyh->ItemIndex==0) ADC=ADC1&0xFF;
        if(CB_53_vyh->ItemIndex==1) ADC=ADC2&0xFF;
        if(CB_53_vyh->ItemIndex==2) ADC=ADC3&0xFF;
        if(CB_53_vyh->ItemIndex==3) ADC=ADC4&0xFF;
        if(CB_53_vyh->ItemIndex==4) ADC=ADC5&0xFF;
        if(CB_53_vyh->ItemIndex==5) ADC=ADC6&0xFF;
        if(CB_53_vyh->ItemIndex==6) ADC=ADC7&0xFF;
        if(CB_53_vyh->ItemIndex==7) ADC=ADC8&0xFF;
        if(CB_53_vyh->ItemIndex==8) ADC=ADC9&0xFF;
        if(CB_53_vyh->ItemIndex==9) ADC=ADC10&0xFF;
        if(CB_53_vyh->ItemIndex==10) ADC=ADC11&0xFF;
        if(CB_53_vyh->ItemIndex==11) ADC=ADC12&0xFF;
//        if(CB_10_vyh->ItemIndex==12) ADC=ADC13&0xFF;
      }
    if(CB_53_vyh->ItemIndex>11)  /* в зависимости от выхода */
      {
        if(CB_53_vyh->ItemIndex==12) ADC=ADC1&0xFF;
        if(CB_53_vyh->ItemIndex==13) ADC=ADC2&0xFF;
        if(CB_53_vyh->ItemIndex==14) ADC=ADC3&0xFF;
        if(CB_53_vyh->ItemIndex==15) ADC=ADC4&0xFF;
        if(CB_53_vyh->ItemIndex==16) ADC=ADC5&0xFF;
        if(CB_53_vyh->ItemIndex==17) ADC=ADC6&0xFF;
        if(CB_53_vyh->ItemIndex==18) ADC=ADC7&0xFF;
        if(CB_53_vyh->ItemIndex==19) ADC=ADC8&0xFF;
        if(CB_53_vyh->ItemIndex==20) ADC=ADC9&0xFF;
        if(CB_53_vyh->ItemIndex==21) ADC=ADC10&0xFF;
        if(CB_53_vyh->ItemIndex==22) ADC=ADC11&0xFF;
        if(CB_53_vyh->ItemIndex==23) ADC=ADC12&0xFF;
       // if(CB_10_vyh->ItemIndex==24) ADC=ADC13&0xFF;
       // if(CB_10_vyh->ItemIndex==25) ADC=ADC13&0xFF;
      }

        if(ERR==1)
         {
          //ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении кода мощности! ERR=1");
          //goto m1;
           n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj;
            }
          else
            {
             ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении кода мощности! ERR=1");
             goto m1_1;
            }
          }

         Kod_DM_izm=ADC;
         Kod_M=0.017*ADC;

       m1_1:;
     }
//    m2_end_5:;
 //   m2_end_3:;
 //====================================
        Sleep(10);

        memset(&buf1,0,20);
        sprintf(buf1,"%d",Kod_DM_izm);
           Edit7->Text=buf1;
           Edit7->Repaint();

           Sleep(10);
      //  x_m_p=j-64;
        x_m_p=TrackBar3->Position;
        Series[2]->AddXY(x_m_p,Kod_M);
        Series[2]->Repaint();

        Chart3->Repaint();

   }    /* end for по частоте */

   end1:;                         /* пакет 2 */
 //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение м атрицы для  1-го и 2-го канала СВЧ */=========================
          n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/

  if(CB_53_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;n_post=0;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;n_post=0;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;n_post=1;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;n_post=1;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7 ERR=1!\n");
     //goto end;
    }
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
     Sleep(1);
                         /* пакет 1*/
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение канала усилителя, выключение источника питания УП7 */=========================
 if(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
   {
    n_post=0;    /*ППС*/
   // nu=(CB_10_vyh->ItemIndex);    /*индекс от 0 до 12*/  /* nu-- номер усилителя*/
    }
   if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
   // nu=12-(CB_53_vyh->ItemIndex);    /*индекс от 13 до 25*/  /* nu-- номер усилителя*/
    }
  // nu=0;  /* ???? nu-- nu=(номер усилителя*/

   if((res=Vykl_us_vip_t(n_post))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных (1) в УП7 ERR=1!\n");
    // goto end;
    }
    if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");}
    Sleep(1);
   end:;
  viPrintf(viG,"OUTPut:STATe OFF\n"); //выкл. сигнала на выход ген-ра

 //   ShowMessage("Измерение закончено\n");
}
//---------------------АЧХ из файла измерений ------------------------------------------------------
void __fastcall TForm1::Button36Click(TObject *Sender)
{
 if(ChkDevs==true)       /** убрать комментарии для работы ***/
 ACHX53_izm();
 else
 {
if(FindDevises()==true)
 {
 if(ChekDev()==true)
  ACHX53_izm();

 }    //FindDevises()
 }//else

}
//---------------------АЧХ из файла измерений ------------------------------------------------------
void TForm1::ACHX53_izm(void)
{
  extern bool vyh;
  ViStatus stat=0; // объявление переменной типа ViStatus
  extern double F_rtu[224];

   double powerDBM=0.0;
   double m_freqq;
   double power;

   double K_nu=0.0;

 //char buf1[256]={0};
// char buf2[256]={0};

 char buf[256]={0};

// double m_freqq_n;
 //double m_freqq_v;

  double P[160]={0.0};       /*измеренное значение в Вт*/
  double P_dB[160]={0.0};    /*измеренное значение в дБ*/

 // double P_1=0;
  //double dP;
  double p_vt_izm;
  double P_max,P_min;
  float Pmin_v,Pmax_v,dP;
  int j,k,k1;
 //int num=0;
 //char rdbuffer[256]={0};

 int ind; //индекс доступа к массивам калибровки
 long longdown=0; /* ожидание операции завершения*/

 int m_p;
 float x_m_p;
 double m_p_1;  /* мощность, задаваемая на генераторе*/

 int k_att=0;
 //int k_max=0,k_min=0;

 double m_Pow;
 char buf1[256]={0};
  int n_post;
  unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
   int nk,nu;  /* номер КИО*/
                                  /* входной атт */
  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/
 float Qvh_osl_my[32]={0.0,-0.75,-1.5,-2.25,-3.0,-3.75,-4.5,-5.25,-6.0,
                     -6.75,-7.5,-8.25,-9.0,-9.75,-10.5,-11.25,-12.0,
                     -12.75,-13.5,-14.25,-15.0,-15.75,-16.5,-17.25,-18.0,
                     -18.75,-19.5,-20.25,-21.0,-21.75,-22.5,-23.25};

                  /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/
 //float Qvh_osl[32]={-23.25,-22.5,-21.75,-21.0,-20.25,-19.5,-18.75,-18.0,
 //                    -17.25,-16.5,-15.75,-15.0,-14.25,-13.5,-12.75,-12.0,
 //                    -11.25,-10.5,-9.75,-9.0,-8.25,-7.5,-6.75,-6.0,-5.25,
 //                    -4.5,-3.75,-3.0,-2.25,-1.5,-0.75,0.0};

                     /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/


  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* выходной атт */
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned kod_att[12];

  AnsiString str2[24]={"ППС1","ППС2","ППС3","ППС4",
                       "ППС5","ППС6","ППС7","ППС8",
                       "ППС9","ППС10","ППС11","ППС12",
                       "ЗПС1","ЗПС2","ЗПС3","ЗПС4",
                       "ЗПС5","ЗПС6","ЗПС7","ЗПС8",
                       "ЗПС9","ЗПС10","ЗПС11","ЗПС12"};
  AnsiString str1[4]={"1ВЧ-53","2ВЧ-53","3ВЧ-53","4ВЧ-53"};

  TChartSeries *Series[4]={LineSeries1,LineSeries2,LineSeries7,LineSeries8};

  u32 buf_my[256/4]; // Буфер для принятого пакета

  union{
       struct{
                  U32   len     : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8,
                        byte5   : 8;
              } p_my_v;
             U32 buf_my[256/4];
            } packet_my;
    union{
       struct{
                  U32   len     : 8, /*LEN*/
                        byte1   : 8, /*IPK*/
                        byte2   : 8, /*DST SRC*/
                        byte3   : 8, /*IPS DST*/
                        byte4   : 8, /*ERR*/
                        /*byte5   : 8,*/  /*ADR_UP7*/
                        byte5   : 8, /*IPK_UP7*/
                        byte6   : 8, /*ADC1 */
                        byte7   : 8, /*ADC2 */
                        byte8   : 8, /*ADC3 */
                        byte9   : 8, /*ADC4 */
                        byte10  : 8, /*ADC5 */
                        byte11  : 8, /*ADC6 */
                        byte12  : 8, /*ADC7 */
                        byte13  : 8, /*ADC8 */
                        byte14  : 8, /*ADC9 */
                        byte15  : 8, /*ADC10 */
                        byte16  : 8, /*ADC11 */
                        byte17  : 8; /*ADC12 */
                    //    byte18  : 8; /*ADC13 */

                        } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;
       unsigned ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8,ADC9,ADC10,ADC11,ADC12,ADC13=0x0;
       int ADC=0;
       unsigned IPK_UP7;
       float Kod_M[160]={0.0};

       int Kod_DM_izm[160]={0};
       int Kod_DM_max=0;
       int Kod_min_km=0,Kod_max_km=0;
       int nf,n_jj;
       int mk;
  //================================================
 AnsiString StNIn;
 AnsiString SbS,SbL,StIn;/*SbS_t;*/
 AnsiString MyFileName;
 int n_vh,nl,n_us,N_us;/*k*/

 float PP_izm[12][8][160]={0.0},osl[12][8][160]={0.0};
 int kad_acp[12][8][160]={0},k_f[160]={0};
 float Qsl_my=0.0;
 int kod_att_my=0,km;

 FILE *tr;
 StNIn=IntToStr(CB_53_vh->ItemIndex+1); /* выбран вход*/

if(CB_53_vyh->ItemIndex<=11) /* если выбран ППС*/
 {
  SbS="pps";
  N_us= CB_53_vyh->ItemIndex;
  }
else
  {
  SbS="zps";
  N_us= CB_53_vyh->ItemIndex-12;
  }
//SbL="ВЧ_2";
  SbL="_53";

 StIn=SbS+"_"+StNIn+SbL+".dan";
 MyFileName=StIn; //MyFileName="pps_1_2.dan";

 if(FileExists(MyFileName))
 {

 if((tr = fopen(MyFileName.c_str(),"r+")) == NULL)
  {
  ShowMessage("Невозможно открыть файл");
   goto m1;
  }
 /* сначала чтение из файла */

 for(n_us=0;n_us<=11;n_us++) /* по 12 усилителям */
   {
   for(k=0;k<=159;k++)
       {
        fscanf(tr,"%d",&k_f[k]);
        fscanf(tr,"%f%f%d",&PP_izm[n_us][0][k],&osl[n_us][0][k], &kad_acp[n_us][0][k]);
        fscanf(tr,"%f%f%d",&PP_izm[n_us][1][k],&osl[n_us][1][k], &kad_acp[n_us][1][k]);
        fscanf(tr,"%f%f%d",&PP_izm[n_us][2][k],&osl[n_us][2][k], &kad_acp[n_us][2][k]);
        fscanf(tr,"%f%f%d",&PP_izm[n_us][3][k],&osl[n_us][3][k], &kad_acp[n_us][3][k]);
        fscanf(tr,"%f%f%d",&PP_izm[n_us][4][k],&osl[n_us][4][k], &kad_acp[n_us][4][k]);
        fscanf(tr,"%f%f%d",&PP_izm[n_us][5][k],&osl[n_us][5][k], &kad_acp[n_us][5][k]);
        fscanf(tr,"%f%f%d",&PP_izm[n_us][6][k],&osl[n_us][6][k], &kad_acp[n_us][6][k]);
        fscanf(tr,"%f%f%d\n",&PP_izm[n_us][7][k],&osl[n_us][7][k],&kad_acp[n_us][7][k]);
      } /* end k*/
    } /* end n_us */

   fclose(tr);

  }
      //=================================================
              E_53_izm_m->Text=" ";
              E_53_izm_m->Repaint();

        Series[0]->Clear();
        Series[1]->Clear();
        Series[2]->Clear();
        Series[3]->Clear();

        Chart3->BottomAxis->SetMinMax(0,159);
        Chart3->Title->Text->Clear();
        Chart3->Title->Text->Add("P=P(f)");

       // Series[3]->Repaint();
         Ep53_max->Text="";
         L53_pmax_no->Caption="";

          E53_km_s->Text="";
          E53_km_mx->Text="";

          E53_dm_2->Text="";

          Edit1->Text=" ";
          Edit2->Text="";
          Edit3->Text="";

       ShowMessage("Подать сигнал с ВЧ генератора на вход "+str1[CB_53_vh->ItemIndex]);

        ShowMessage("Подключить измеритель мощности через аттенюатор 30дБ к выходу "+str2[CB_53_vyh->ItemIndex]);

    /*   if(comm_vhod(CB_53_vh->ItemIndex+4))  //1 -- ошибка, 0 -- без ошибок
           {
             ShowMessage("Не сработал коммутатор 1");
             goto end;
             }
        if(comm_vyhod(CB_53_vyh->ItemIndex))//1 -- ошибка, 0 -- без ошибок
            {
             ShowMessage("Не сработал коммутатор 2");
             goto end;
             }
     */        

         Chart3->Repaint();

        /* пакет 3*/
    for(i=0;i<=11;i++)
      {
      // US[i]=0x0;
       kod_att[i]=0xF;
      }
  //============/* формуляр задание кода выходных атт */====
   if(CB_53_vyh->ItemIndex<=11)
   {
    n_post=0;    /*ППС*/
    kod_att[CB_53_vyh->ItemIndex]= Q_vh[CB_53_att_vyh->ItemIndex];
   }
  if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
    kod_att[CB_53_vyh->ItemIndex-12]= Q_vh[CB_53_att_vyh->ItemIndex];/****?????****/
    }

   if((res=Vkl_att_t(n_post,kod_att))==1)   /*0-- нет ошибок, 1-- есть ошибки */
     {
      ShowMessage("Ошибка при передаче формуляра 3 данных в УП7 ERR=1!\n");
      //goto end;
     }
 if(res==2) {ShowMessage("Нет ответных пакетов на пакет 3!");}
           Sleep(1);


              /* пакет 1*/
//-----------------формуляр передачи данных в УП7 -------------------------------------------------------
 //============/* включение канала усилителя, включение источника питания УП7 */========================================            /* пакет 1*/
   if(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
   {
    n_post=0;    /*ППС*/
    nu=(CB_53_vyh->ItemIndex);    /*индекс от 0 до 12*/  /* nu-- номер усилителя*/
    }
   if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
    nu=(CB_53_vyh->ItemIndex)-12;    /*индекс от 13 до 25*/  /* nu-- номер усилителя*/
    }
  // nu=0;  /* ???? nu-- nu=(номер усилителя*/

   if((res=Vkl_us_vip_t(n_post,nu))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных (1) в УП7!\n");
    // goto end;
    }
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");}
    Sleep(1);
 //*************************************************************************
   m_freqq=F_rtu[64];
   //m_freqq = strtod(E2_f->Text.c_str(),NULL);

   powerDBM = strtod(E53_p->Text.c_str(),NULL);

   K_nu = strtod(E_ks_53->Text.c_str(),NULL);
   if((K_nu>3.0)||(K_nu<0.0))
   {
    ShowMessage("Неверное значение константы насыщения");
    goto end;
   }

    K_nu=(3.0-K_nu)/4.0;

//  for(k=64; k<=223;k++) /* определение ind*/
//     {
//      if(F_rtu[k]==m_freqq){ind=k;break;}
//     }
   m_p_1=powerDBM-dPg[64];   /* с учетом калибровки кабеля */

 /*15.12.10*/ //    power = -70.0;  //отладка

 // Установка на генератор частоты и мощности
 stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // частота
 stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // мощность
  if (stat != VI_SUCCESS)
  {
     ShowMessage("Ошибка при установке значений на генератор");
     goto end;
  }
 // viPrintf(vigen,"PULM:STAT OFF\n");   // ВКЛючить имп модуляцию
   viPrintf(viG,"OUTPut:STATe ON\n"); //подкл.  сигнала на выход ген-ра

    longdown=0;

    viPrintf(viG,"*OPC?\n");

        while(!longdown)
    viScanf(viG,"%d", &longdown);

    viPrintf(viP,"ABORT\n");
   viPrintf(viP,"INIT:CONT ON\n");
   viPrintf(viP,"FETC?\n");
   viScanf(viP,"%t",buf);

    Sleep(1);
            /* пакет 2*/
    /*  сначала выключаем неиспользываемые номера выходов матрицы ПМ */
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение матрицы для  1-го и 2-го канала СВЧ */=========================
          n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/

  if(CB_53_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
      if(CB_53_vyh->ItemIndex>11) /* если выбран ППС, то выключаем ЗПС*/
           n_post=1; /*ЗПС*/   /* если выбран ППС, то выключаем ЗПС*/
           else  n_post=0;  nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           if(CB_53_vyh->ItemIndex<=11) /* если выбран ППС, то выключаем ЗПС*/
                 n_post=1;
           else  n_post=0; nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
         if(CB_53_vyh->ItemIndex<=11) /* если выбран ЗПС, то выключаем ППС*/
                 n_post=0;
           else  n_post=1;  nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
          if(CB_53_vyh->ItemIndex<=11) /* если выбран ЗПС, то выключаем ППС*/
              n_post=0;
           else  n_post=1; nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7!\n");
     //goto end;
    }

  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
   Sleep(1);

    vyh=true;

 // for(j=0; j<=63;j++)  /* литера 2*/
 for(j=64; j<=223;j++)  /* литера 53*/
  {
  // Application->ProcessMessages();
 //  if(vyh==false) goto end1;

   /* выбор нужного значения кода входного атт. из файла */
   for(km=0;km<=31;km++)
   {
    Qsl_my=osl[N_us][UD_53->Position-1][j-64];
    if(Qsl_my==Qvh_osl_my[km]) kod_att_my=km;
   }

      /* пакет 2*/
 //============/* включение номера выхода матрицы ПМ для 1-ого и 2-ого канала */========================================
//============/* задание кода входных атт для 1-ого и 2-ого канала */==========================
   /* n_vh1 -- номер выхода матрицы для 1-ого канала СВЧ 0--0xF (4 разряда)*/
   /* n_vh2 -- номер выхода матрицы для 2-ого канала СВЧ 0--0xF (4 разряда)*/

       n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/
//  if(CB_53_vh->ItemIndex==0){in1_at=Qv_vh[CB_53_att_vh->ItemIndex];in2_at=0x1F;n_post=0;nk_svch=1;
//        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

//  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[CB_53_att_vh->ItemIndex];n_post=0;nk_svch=2;
//      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

//  if(CB_53_vh->ItemIndex==2){in1_at=Qv_vh[CB_53_att_vh->ItemIndex];in2_at=0x1F;n_post=1;nk_svch=1;
//        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

//  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[CB_53_att_vh->ItemIndex];n_post=1;nk_svch=2;
//      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==0){in1_at=Qv_vh[kod_att_my];in2_at=0x1F;n_post=0;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[kod_att_my];n_post=0;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=Qv_vh[kod_att_my];in2_at=0x1F;n_post=1;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[kod_att_my];n_post=1;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/


   if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7 ERR=1!\n");
     goto end1;
    }

    /* Прием ответного пакета */
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
       Sleep(5);

    m_freqq=F_rtu[j];
    m_p_1=powerDBM-dPg[j];   /* с учетом калибровки кабеля */
    stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // частота
     stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // мощность
  if (stat != VI_SUCCESS)
  {
     ShowMessage("Ошибка при установке значений на генератор");
     goto end;
  }

    viPrintf(viP,"ABORT\n");
    viPrintf(viP,"INIT:CONT ON\n");
    viPrintf(viP,"FETC?\n");
    viScanf(viP,"%t",buf);

    m_Pow = atof(buf);
//  for(k=64; k<=223;k++) /* определение ind*/
//     {
//      if(F_rtu[k]==m_freqq){ind=k;break;}
//     }

      ind=j;
   m_Pow=m_Pow-dPm[ind];   /*с учетом калибровки кабеля*/
    P_dB[j-64]=m_Pow;

        //  Pw=pow(10,Pdbm/10); //мВт       Pw=pow(10,-3)*pow(10,Pdbm/10);  //Вт

          m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

          P[j-64]=m_Pow;  /* значение в Вт */
         //  x_m_p=Qvh_osl[j];

        /* чтение датчика мощности */
                   /* запрос кода мощности */
                         /* пакет 9*/
//-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//----------------Чтение уровня мощности для каналов усилителей------------------------------
 // if((CB_53_vh->ItemIndex==0)||(CB_53_vh->ItemIndex==1))
//   {
//  n_post=2; /*ППС*/
//   }
//  if((CB_53_vh->ItemIndex==2)||(CB_53_vh->ItemIndex==3))
//    {
//      n_post=3; /*ЗПС*/
//    }
 if(CB_53_vyh->ItemIndex<=11)  /* в зависимости от выхода */     {
     n_post=0; /**/
     }
  if(CB_53_vyh->ItemIndex>11)
     {
     n_post=1; /**/
     }
    nf=0x9;
 n_jj=0;

m_jj:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- нет ошибок, 1-- есть ошибки */
   {
     ShowMessage("Ошибка при передаче формуляра запроса данных (9) в УП7!\n");
    // 10.01.11 vyh=false; goto end;
   }

  Sleep(10);
//17.07 if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07        // Нет принятых пакетов
//17.07 //     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07   }

  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
//17.07        // Нет принятых пакетов
//17.07 //     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07      if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("Сбой по магистрале!");
//17.07       vyh=false; goto end; //goto m2_end_5;
//17.07      }
   }
   else
   {
        // Принят пакет

      LEN=packet_my_km.p_my_v.len;
      IPK=packet_my_km.p_my_v.byte1;
      SRC=packet_my_km.p_my_v.byte2&0x1F;
      DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* левое крыло DST=0x6, правое крыло DST=0x7*/
      IPS=(packet_my_km.p_my_v.byte3>>2)&0x3F;
      ERR=packet_my_km.p_my_v.byte4&0x1;
       /* ADR_UP7=packet_my_km.p_my_v.byte5;*/
      IPK_UP7=packet_my_km.p_my_v.byte5;
      ADC1=packet_my_km.p_my_v.byte6;
      ADC2=packet_my_km.p_my_v.byte7;
      ADC3=packet_my_km.p_my_v.byte8;
      ADC4=packet_my_km.p_my_v.byte9;
      ADC5=packet_my_km.p_my_v.byte10;
      ADC6=packet_my_km.p_my_v.byte11;
      ADC7=packet_my_km.p_my_v.byte12;
      ADC8=packet_my_km.p_my_v.byte13;
      ADC9=packet_my_km.p_my_v.byte14;
      ADC10=packet_my_km.p_my_v.byte15;
      ADC11=packet_my_km.p_my_v.byte16;
      ADC12=packet_my_km.p_my_v.byte17;
     // ADC13=packet_my_km.p_my_v.byte18;

// 22.12.10
     if(CB_53_vyh->ItemIndex<=11)  /* в зависимости от выхода */
       {
        if(CB_53_vyh->ItemIndex==0) ADC=ADC1&0xFF;
        if(CB_53_vyh->ItemIndex==1) ADC=ADC2&0xFF;
        if(CB_53_vyh->ItemIndex==2) ADC=ADC3&0xFF;
        if(CB_53_vyh->ItemIndex==3) ADC=ADC4&0xFF;
        if(CB_53_vyh->ItemIndex==4) ADC=ADC5&0xFF;
        if(CB_53_vyh->ItemIndex==5) ADC=ADC6&0xFF;
        if(CB_53_vyh->ItemIndex==6) ADC=ADC7&0xFF;
        if(CB_53_vyh->ItemIndex==7) ADC=ADC8&0xFF;
        if(CB_53_vyh->ItemIndex==8) ADC=ADC9&0xFF;
        if(CB_53_vyh->ItemIndex==9) ADC=ADC10&0xFF;
        if(CB_53_vyh->ItemIndex==10) ADC=ADC11&0xFF;
        if(CB_53_vyh->ItemIndex==11) ADC=ADC12&0xFF;
//        if(CB_10_vyh->ItemIndex==12) ADC=ADC13&0xFF;
      }
    if(CB_53_vyh->ItemIndex>11)  /* в зависимости от выхода */
      {
        if(CB_53_vyh->ItemIndex==12) ADC=ADC13&0xFF;
        if(CB_53_vyh->ItemIndex==13) ADC=ADC2&0xFF;
        if(CB_53_vyh->ItemIndex==14) ADC=ADC3&0xFF;
        if(CB_53_vyh->ItemIndex==15) ADC=ADC4&0xFF;
        if(CB_53_vyh->ItemIndex==16) ADC=ADC5&0xFF;
        if(CB_53_vyh->ItemIndex==17) ADC=ADC6&0xFF;
        if(CB_53_vyh->ItemIndex==18) ADC=ADC7&0xFF;
        if(CB_53_vyh->ItemIndex==19) ADC=ADC8&0xFF;
        if(CB_53_vyh->ItemIndex==20) ADC=ADC9&0xFF;
        if(CB_53_vyh->ItemIndex==21) ADC=ADC10&0xFF;
        if(CB_53_vyh->ItemIndex==22) ADC=ADC11&0xFF;
        if(CB_53_vyh->ItemIndex==23) ADC=ADC12&0xFF;
       // if(CB_10_vyh->ItemIndex==24) ADC=ADC13&0xFF;
       // if(CB_10_vyh->ItemIndex==25) ADC=ADC13&0xFF;
      }

        if(ERR==1)
         {
          //ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении кода мощности! ERR=1");
          //goto m1;
           n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj;
            }
          else
            {
             ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении кода мощности! ERR=1");
             goto m1_1;
            }
          }

         Kod_DM_izm[j-64]=ADC;
         Kod_M[j-64]=0.017*ADC;


         /*  memset(&buf1,0,20);
           sprintf(buf1,"%d",ADC);

           E_2_um->Text=buf1;
           E_2_um->Repaint();
         */
       m1_1:;
     }
//    m2_end_5:;
 //   m2_end_3:;
 //====================================
          Sleep(10);
        x_m_p=j-64;
        Series[3]->AddXY(x_m_p,P[j-64]);
        Series[3]->Repaint();

        Series[0]->AddXY(x_m_p,Kod_M[j-64]);
        Series[0]->Repaint();

        Chart3->Repaint();

   }    /* end for по частоте */


 /*    for(k=0;k<=159;k++)
       {
         x_m_p=k;
         Series[3]->AddXY(x_m_p,P[k]);
       }
     for(k=0;k<=159;k++)
       {
         x_m_p=k;
         Series[0]->AddXY(x_m_p,Kod_M[k]);
       }
  */

   for(k1=0,P_max=P_min=P[0]; k1<=159; k1+=1)  /* вычисление max на кривой */
       {
        if(P[k1]>P_max) {P_max=P[k1];}//k_max=k1;}
        if(P[k1]<P_min) {P_min=P[k1];}//k_min=k1;}
       }

      Pmin_v=(float)P_min;
      Pmax_v=(float)P_max;
      dP=(float)fabs(P_max-P_min);

        memset(&buf1,0,20);
        sprintf(buf1,"%.2f",Pmin_v);
           Edit1->Text=buf1;
           Edit1->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%.2f",Pmax_v);

           Edit2->Text=buf1;
           Edit2->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%.2f",dP);

           Edit3->Text=buf1;
           Edit3->Repaint();

    for(k1=0,Kod_max_km=Kod_min_km=Kod_DM_izm[0]; k1<=159; k1+=1)  /* вычисление max на кривой */
       {
        if(Kod_DM_izm[k1]>Kod_max_km) {Kod_max_km=Kod_DM_izm[k1];}//k_max=k1;}
        if(Kod_DM_izm[k1]<Kod_min_km) {Kod_min_km=Kod_DM_izm[k1];}//k_min=k1;}
       }

           memset(&buf1,0,20);
        sprintf(buf1,"%d",Kod_min_km);
           Edit4->Text=buf1;
           Edit4->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%d",Kod_max_km);

           Edit5->Text=buf1;
           Edit5->Repaint();

   end1:;                         /* пакет 2 */
 //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение м атрицы для  1-го и 2-го канала СВЧ */=========================
          n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/

  if(CB_53_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;n_post=0;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;n_post=0;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;n_post=1;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;n_post=1;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7 ERR=1!\n");
     //goto end;
    }
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
     Sleep(1);
                         /* пакет 1*/
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение канала усилителя, выключение источника питания УП7 */=========================
 if(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
   {
    n_post=0;    /*ППС*/
   // nu=(CB_10_vyh->ItemIndex);    /*индекс от 0 до 12*/  /* nu-- номер усилителя*/
    }
   if(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
   // nu=12-(CB_53_vyh->ItemIndex);    /*индекс от 13 до 25*/  /* nu-- номер усилителя*/
    }
  // nu=0;  /* ???? nu-- nu=(номер усилителя*/

   if((res=Vykl_us_vip_t(n_post))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных (1) в УП7 ERR=1!\n");
    // goto end;
    }
    if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");}
    Sleep(1);
   end:;
  viPrintf(viG,"OUTPut:STATe OFF\n"); //выкл. сигнала на выход ген-ра

    ShowMessage("Измерение закончено\n");

 m1:;
}
//----------------------- Измерение Рмин в канале ----------------------------
void __fastcall TForm1::Button37Click(TObject *Sender)
{
 if(ChkDevs==true)       /** убрать комментарии для работы ***/
 ACHX53_tabl();
 else
 {
if(FindDevises()==true)
 {
 if(ChekDev()==true)
  ACHX53_tabl();

 }    //FindDevises()
 }//else
}
//----------------------- Измерение Рмин в канале ----------------------------
void TForm1::ACHX53_tabl(void)
{
 extern double F_rtu[224];
  double freq;
  char buf1[256]={0};
  AnsiString str2[24]={"ППС1","ППС2","ППС3","ППС4",
                       "ППС5","ППС6","ППС7","ППС8",
                       "ППС9","ППС10","ППС11","ППС12",
                       "ЗПС1","ЗПС2","ЗПС3","ЗПС4",
                       "ЗПС5","ЗПС6","ЗПС7","ЗПС8",
                       "ЗПС9","ЗПС10","ЗПС11","ЗПС12"};
 int j,k;

Panel9->Visible=true;
Panel10->Visible=false;
Panel1->Visible=false;
Panel2->Visible=false;
PanelPotent->Visible=false;
Mode=1;
 if(RG53_10->ItemIndex==0){
                   Label73->Caption="Выход "+str2[0];
                   Label74->Caption="Выход "+str2[1];
                   Label75->Caption="Выход "+str2[2];
                   Label76->Caption="Выход "+str2[3];
                   Label77->Caption="Выход "+str2[4];
                   Label78->Caption="Выход "+str2[5];
                   Label79->Caption="Выход "+str2[6];
                   Label80->Caption="Выход "+str2[7];
                   Label81->Caption="Выход "+str2[8];
                   Label82->Caption="Выход "+str2[9];
                   Label83->Caption="Выход "+str2[10];
                   Label84->Caption="Выход "+str2[11];
                   }

            else
               {
                   Label73->Caption="Выход "+str2[12];
                   Label74->Caption="Выход "+str2[13];
                   Label75->Caption="Выход "+str2[14];
                   Label76->Caption="Выход "+str2[15];
                   Label77->Caption="Выход "+str2[16];
                   Label78->Caption="Выход "+str2[17];
                   Label79->Caption="Выход "+str2[18];
                   Label80->Caption="Выход "+str2[19];
                   Label81->Caption="Выход "+str2[20];
                   Label82->Caption="Выход "+str2[21];
                   Label83->Caption="Выход "+str2[22];
                   Label84->Caption="Выход "+str2[23];
                }
        /* очистить таблицу*/
  for(k=1;k<=24;k++)    /* строка  */
   for(j=0;j<=15;j++)   /* столбец  */
     {
     StringGrid2->Cells[j][k]=" ";
     }

   }
//--------------------------------------------------------------------------
void __fastcall TForm1::Button40Click(TObject *Sender)
{
 Panel9->Visible=false;
//
}
//---------------------Измерение Рвых табл------------------------------------------------------
void __fastcall TForm1::Button38Click(TObject *Sender)
{
extern bool vyh;
  ViStatus stat=0; // объявление переменной типа ViStatus
  extern double F_rtu[224];

   double powerDBM=0.0;
   double m_freqq;
   double power;

   double K_nu=0.0;

 char buf[256]={0};

  double P[160]={0.0};       /*измеренное значение в Вт*/
  double P_dB[160]={0.0};    /*измеренное значение в дБ*/

  double p_vt_izm;
  double P_max,P_min;
  float Pmin_v;/*,Pmax_v,dP;*/
  int j,k,k1;

 int ind; //индекс доступа к массивам калибровки
 long longdown=0; /* ожидание операции завершения*/

 int m_p;
 float x_m_p;
 double m_p_1;  /* мощность, задаваемая на генераторе*/

 //int k_max=0,k_min=0;

 double m_Pow;
 //char buf1[256]={0};
  int n_post;
  unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
  int nk,nu;  /* номер КИО*/
                                  /* входной атт */
  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 разрядов 00000, 00001,00010,00100,01000,10000*/

  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* выходной атт */
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned kod_att[12];

  AnsiString str2[24]={"ППС1","ППС2","ППС3","ППС4",
                       "ППС5","ППС6","ППС7","ППС8",
                       "ППС9","ППС10","ППС11","ППС12",
                       "ЗПС1","ЗПС2","ЗПС3","ЗПС4",
                       "ЗПС5","ЗПС6","ЗПС7","ЗПС8",
                       "ЗПС9","ЗПС10","ЗПС11","ЗПС12"};
  AnsiString str1[4]={"1ВЧ-53","2ВЧ-53","3ВЧ-53","4ВЧ-53"};


  u32 buf_my[256/4]; // Буфер для принятого пакета

  union{
       struct{
                  U32   len     : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8,
                        byte5   : 8;
              } p_my_v;
             U32 buf_my[256/4];
            } packet_my;
    union{
       struct{
                  U32   len     : 8, /*LEN*/
                        byte1   : 8, /*IPK*/
                        byte2   : 8, /*DST SRC*/
                        byte3   : 8, /*IPS DST*/
                        byte4   : 8, /*ERR*/
                        /*byte5   : 8,*/  /*ADR_UP7*/
                        byte5   : 8, /*IPK_UP7*/
                        byte6   : 8, /*ADC1 */
                        byte7   : 8, /*ADC2 */
                        byte8   : 8, /*ADC3 */
                        byte9   : 8, /*ADC4 */
                        byte10  : 8, /*ADC5 */
                        byte11  : 8, /*ADC6 */
                        byte12  : 8, /*ADC7 */
                        byte13  : 8, /*ADC8 */
                        byte14  : 8, /*ADC9 */
                        byte15  : 8, /*ADC10 */
                        byte16  : 8, /*ADC11 */
                        byte17  : 8; /*ADC12 */
                    //    byte18  : 8; /*ADC13 */

                        } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;
       unsigned ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8,ADC9,ADC10,ADC11,ADC12,ADC13=0x0;
       int ADC=0;
       unsigned IPK_UP7;
       float Kod_M[160]={0.0};

       int Kod_DM_izm[160]={0};
      // int Kod_DM_max=0;
       int Kod_min_km=0,Kod_max_km=0;
       int nf,n_jj;
       int mk,n_us_t=0,n_l_t=0;

  Label72->Caption="Таблица  Pмин  (Вт) и кодов мощности в канале "+str1[CB_53_vh->ItemIndex];

   PostMessage(StringGrid2->Handle, WM_MBUTTONDOWN, MK_LBUTTON,0);
   PostMessage(StringGrid2->Handle, WM_MBUTTONUP, MK_LBUTTON,0);

        /* вывести в таблицу */
    for(j=0;j<=14;j=j+2)   /* столбец  */
     {
      StringGrid2->Cells[j][0]="Pmin";
      StringGrid2->Cells[j+1][0]="Код мощ";
     }


    ShowMessage("Подать сигнал с ВЧ генератора на вход "+str1[CB_53_vh->ItemIndex]);
 /*
  if(comm_vhod(CB_53_vh->ItemIndex+4))  //1 -- ошибка, 0 -- без ошибок
           {
             ShowMessage("Не сработал коммутатор 1");
             goto end;
             }
 */
  //*************************************************************************
   m_freqq=F_rtu[64];
   powerDBM = strtod(E53_p->Text.c_str(),NULL);

   K_nu = strtod(E_ks_53->Text.c_str(),NULL);
   if((K_nu>3.0)||(K_nu<0.0))
   {
    ShowMessage("Неверное значение константы насыщения");
    goto end;
   }

    K_nu=(3.0-K_nu)/4.0;
   m_p_1=powerDBM-dPg[64];   /* с учетом калибровки кабеля */

 /*15.12.10*/ //    power = -70.0;  //отладка

 // Установка на генератор частоты и мощности
 stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // частота
 stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // мощность
  if (stat != VI_SUCCESS)
  {
     ShowMessage("Ошибка при установке значений на генератор");
     goto end;
  }
 // viPrintf(vigen,"PULM:STAT OFF\n");   // ВКЛючить имп модуляцию
   viPrintf(viG,"OUTPut:STATe ON\n"); //подкл.  сигнала на выход ген-ра

    longdown=0;

    viPrintf(viG,"*OPC?\n");

        while(!longdown)
    viScanf(viG,"%d", &longdown);

    viPrintf(viP,"ABORT\n");
   viPrintf(viP,"INIT:CONT ON\n");
   viPrintf(viP,"FETC?\n");
   viScanf(viP,"%t",buf);

    Sleep(1);

 for(n_us_t=0;n_us_t<=11;n_us_t++)/* цикл по выходам */
  {
   if((n_us_t==0)&&(CheckBox9->Checked==false)) goto end_vhod;
   if((n_us_t==1)&&(CheckBox10->Checked==false)) goto end_vhod;
   if((n_us_t==2)&&(CheckBox11->Checked==false)) goto end_vhod;
   if((n_us_t==3)&&(CheckBox12->Checked==false)) goto end_vhod;
   if((n_us_t==4)&&(CheckBox13->Checked==false)) goto end_vhod;
   if((n_us_t==5)&&(CheckBox14->Checked==false)) goto end_vhod;
   if((n_us_t==6)&&(CheckBox15->Checked==false)) goto end_vhod;
   if((n_us_t==7)&&(CheckBox16->Checked==false)) goto end_vhod;
   if((n_us_t==8)&&(CheckBox17->Checked==false)) goto end_vhod;
   if((n_us_t==9)&&(CheckBox18->Checked==false)) goto end_vhod;
   if((n_us_t==10)&&(CheckBox19->Checked==false)) goto end_vhod;
   if((n_us_t==11)&&(CheckBox20->Checked==false)) goto end_vhod;


   /* очистить строку */
  for(j=0;j<=15;j++)   /* столбец  */
    {
     StringGrid2->Cells[j][2*n_us_t+1]=" ";
    }
 /* Убрать сообщение? это для разных полусфер */
  if(RG53_10->ItemIndex==0) ShowMessage("Подключить измеритель мощности через аттенюатор 30дБ к выходу "+str2[n_us_t]);
   else  ShowMessage("Подключить измеритель мощности через аттенюатор 30дБ к выходу "+str2[n_us_t+12]);

  //  if(comm_vyhod(n_us_t))//1 -- ошибка, 0 -- без ошибок
  //          {
  //           ShowMessage("Не сработал коммутатор 2");
  //           goto end;
  //           }

    viPrintf(viG,"OUTPut:STATe ON\n"); //подкл.  сигнала на выход ген-ра

  for(n_l_t=0;n_l_t<=7;n_l_t++)/* цикл по лучам одного усилетеля */
    {


           /* пакет 3*/
    for(i=0;i<=11;i++)
      {
      // US[i]=0x0;
       kod_att[i]=0xF;
      }
  //============/* формуляр задание кода выходных атт */====
   if(RG53_10->ItemIndex==0)// (CB_53_vyh->ItemIndex<=11)
   {
    n_post=0;    /*ППС*/
//    kod_att[CB_53_vyh->ItemIndex]= Q_vh[CB_53_att_vyh->ItemIndex];
      kod_att[n_us_t]=Q_vh[CB_53_att_vyh->ItemIndex];
   }
  if(RG53_10->ItemIndex==1)//(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/
//    kod_att[CB_53_vyh->ItemIndex-12]= Q_vh[CB_53_att_vyh->ItemIndex];/****?????****/
      kod_att[n_us_t]=Q_vh[CB_53_att_vyh->ItemIndex];
    }

   if((res=Vkl_att_t(n_post,kod_att))==1)   /*0-- нет ошибок, 1-- есть ошибки */
     {
      ShowMessage("Ошибка при передаче формуляра 3 данных в УП7 ERR=1!\n");
      goto end;
     }
 if(res==2) {ShowMessage("Нет ответных пакетов на пакет 3!");}
           Sleep(1);


              /* пакет 1*/
//-----------------формуляр передачи данных в УП7 -------------------------------------------------------
 //============/* включение канала усилителя, включение источника питания УП7 */========================================            /* пакет 1*/
  if(RG53_10->ItemIndex==0) //(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
   {
    n_post=0;    /*ППС*/
      /*индекс от 0 до 12*/  /* nu-- номер усилителя*/
     nu=n_us_t;
    }
   if(RG53_10->ItemIndex==1) //(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/  /*индекс от 13 до 25*/  /* nu-- номер усилителя*/
      nu=n_us_t;
    }
  // nu=0;  /* ???? nu-- nu=(номер усилителя*/

   if((res=Vkl_us_vip_t(n_post,nu))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных (1) в УП7!\n");
     goto end;
    }
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");}
    Sleep(1);
               /* пакет 2*/
    /*  сначала выключаем неиспользываемые номера выходов матрицы ПМ */
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение матрицы для  1-го и 2-го канала СВЧ */=========================
        //  n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/
          n_vh1= n_l_t; n_vh2=n_l_t;  /* от 0 до 7*/
  if(CB_53_vh->ItemIndex==0)
    {
    in1_at=0x1F;in2_at=0x1F;
      if(RG53_10->ItemIndex==1)//(CB_53_vyh->ItemIndex>11) /* если выбран ППС, то выключаем ЗПС*/
           n_post=1; /*ЗПС*/   /* если выбран ППС, то выключаем ЗПС*/
           else  n_post=0;  nk_svch=1;
    }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1)
   {
    in1_at=0x1F;in2_at=0x1F;
           if(RG53_10->ItemIndex==0)//(CB_53_vyh->ItemIndex<=11) /* если выбран ППС, то выключаем ЗПС*/
                 n_post=1;
           else  n_post=0; nk_svch=2;
    } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2)
    {
     in1_at=0x1F;in2_at=0x1F;
       if(RG53_10->ItemIndex==0)  //(CB_53_vyh->ItemIndex<=11) /* если выбран ЗПС, то выключаем ППС*/
                 n_post=0;
           else  n_post=1;  nk_svch=1;
    }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3)
   {
     in1_at=0x1F;in2_at=0x1F;
        if(RG53_10->ItemIndex==0)//(CB_53_vyh->ItemIndex<=11) /* если выбран ЗПС, то выключаем ППС*/
             n_post=0;
          else  n_post=1; nk_svch=2;
   } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7!\n");
     goto end;
    }

  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
   Sleep(1);
      /* пакет 2*/
 //============/* включение номера выхода матрицы ПМ для 1-ого и 2-ого канала */========================================
//============/* задание кода входных атт для 1-ого и 2-ого канала */==========================
   /* n_vh1 -- номер выхода матрицы для 1-ого канала СВЧ 0--0xF (4 разряда)*/
   /* n_vh2 -- номер выхода матрицы для 2-ого канала СВЧ 0--0xF (4 разряда)*/

   //    n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/
           n_vh1= n_l_t; n_vh2=n_l_t;  /* от 0 до 7*/
  if(CB_53_vh->ItemIndex==0)
  {in1_at=Qv_vh[CB_53_att_vh->ItemIndex];in2_at=0x1F;n_post=0;nk_svch=1;
  }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1)
  {in1_at=0x1F;in2_at=Qv_vh[CB_53_att_vh->ItemIndex];n_post=0;nk_svch=2;
  } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2)
  {in1_at=Qv_vh[CB_53_att_vh->ItemIndex];in2_at=0x1F;n_post=1;nk_svch=1;
   }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3)
  {in1_at=0x1F;in2_at=Qv_vh[CB_53_att_vh->ItemIndex];n_post=1;nk_svch=2;
  } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

   if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7 ERR=1!\n");
     goto end1;
    }

    /* Прием ответного пакета */
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
       Sleep(5);

      vyh=true;

 // for(j=0; j<=63;j++)  /* литера 2*/
 for(j=64; j<=223;j++)  /* литера 53*/
  {
   Application->ProcessMessages();
   if(vyh==false) goto end;

    m_freqq=F_rtu[j];
    m_p_1=powerDBM-dPg[j];   /* с учетом калибровки кабеля */
    stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // частота
     stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // мощность
  if (stat != VI_SUCCESS)
  {
     ShowMessage("Ошибка при установке значений на генератор");
     goto end;
  }

    viPrintf(viP,"ABORT\n");
    viPrintf(viP,"INIT:CONT ON\n");
    viPrintf(viP,"FETC?\n");
    viScanf(viP,"%t",buf);

    m_Pow = atof(buf);
      ind=j;
   m_Pow=m_Pow-dPm[ind];   /*с учетом калибровки кабеля*/
    P_dB[j-64]=m_Pow;

        //  Pw=pow(10,Pdbm/10); //мВт       Pw=pow(10,-3)*pow(10,Pdbm/10);  //Вт

          m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

          P[j-64]=m_Pow;  /* значение в Вт */

        /* чтение датчика мощности */
                   /* запрос кода мощности */
                         /* пакет 9*/
//-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//----------------Чтение уровня мощности для каналов усилителей------------------------------
 if(RG53_10->ItemIndex==0)//(CB_53_vyh->ItemIndex<=11)  /* в зависимости от выхода */
    {
     n_post=0; /**/
     }
  if(RG53_10->ItemIndex==1)//(CB_53_vyh->ItemIndex>11)
     {
     n_post=1; /**/
     }
    nf=0x9;
 n_jj=0;

m_jj:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- нет ошибок, 1-- есть ошибки */
   {
     ShowMessage("Ошибка при передаче формуляра запроса данных (9) в УП7!\n");
    // 10.01.11 vyh=false; goto end;
   }

  Sleep(10);
//17.07 if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07        // Нет принятых пакетов
//17.07 //     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07   }

  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
//17.07        // Нет принятых пакетов
//17.07 //     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07      if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("Сбой по магистрале!");
//17.07       vyh=false; goto end; //goto m2_end_5;
//17.07      }
   }
   else
   {
        // Принят пакет

      LEN=packet_my_km.p_my_v.len;
      IPK=packet_my_km.p_my_v.byte1;
      SRC=packet_my_km.p_my_v.byte2&0x1F;
      DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* левое крыло DST=0x6, правое крыло DST=0x7*/
      IPS=(packet_my_km.p_my_v.byte3>>2)&0x3F;
      ERR=packet_my_km.p_my_v.byte4&0x1;
       /* ADR_UP7=packet_my_km.p_my_v.byte5;*/
      IPK_UP7=packet_my_km.p_my_v.byte5;
      ADC1=packet_my_km.p_my_v.byte6;
      ADC2=packet_my_km.p_my_v.byte7;
      ADC3=packet_my_km.p_my_v.byte8;
      ADC4=packet_my_km.p_my_v.byte9;
      ADC5=packet_my_km.p_my_v.byte10;
      ADC6=packet_my_km.p_my_v.byte11;
      ADC7=packet_my_km.p_my_v.byte12;
      ADC8=packet_my_km.p_my_v.byte13;
      ADC9=packet_my_km.p_my_v.byte14;
      ADC10=packet_my_km.p_my_v.byte15;
      ADC11=packet_my_km.p_my_v.byte16;
      ADC12=packet_my_km.p_my_v.byte17;
     // ADC13=packet_my_km.p_my_v.byte18;

// 22.12.10
     if(RG53_10->ItemIndex==0)//(CB_53_vyh->ItemIndex<=11)  /* в зависимости от выхода */
       {
        if(n_us_t==0) ADC=ADC1&0xFF;
        if(n_us_t==1) ADC=ADC2&0xFF;
        if(n_us_t==2) ADC=ADC3&0xFF;
        if(n_us_t==3) ADC=ADC4&0xFF;
        if(n_us_t==4) ADC=ADC5&0xFF;
        if(n_us_t==5) ADC=ADC6&0xFF;
        if(n_us_t==6) ADC=ADC7&0xFF;
        if(n_us_t==7) ADC=ADC8&0xFF;
        if(n_us_t==8) ADC=ADC9&0xFF;
        if(n_us_t==9) ADC=ADC10&0xFF;
        if(n_us_t==10) ADC=ADC11&0xFF;
        if(n_us_t==11) ADC=ADC12&0xFF;
      }
    if(RG53_10->ItemIndex==1)//(CB_53_vyh->ItemIndex>11)  /* в зависимости от выхода */
      {
        if(n_us_t==0) ADC=ADC1&0xFF;
        if(n_us_t==1) ADC=ADC2&0xFF;
        if(n_us_t==2) ADC=ADC3&0xFF;
        if(n_us_t==3) ADC=ADC4&0xFF;
        if(n_us_t==4) ADC=ADC5&0xFF;
        if(n_us_t==5) ADC=ADC6&0xFF;
        if(n_us_t==6) ADC=ADC7&0xFF;
        if(n_us_t==7) ADC=ADC8&0xFF;
        if(n_us_t==8) ADC=ADC9&0xFF;
        if(n_us_t==9) ADC=ADC10&0xFF;
        if(n_us_t==10) ADC=ADC11&0xFF;
        if(n_us_t==11) ADC=ADC12&0xFF;
      }

        if(ERR==1)
         {
          //ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении кода мощности! ERR=1");
          //goto m1;
           n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj;
            }
          else
            {
             ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении кода мощности! ERR=1");
             goto m1_1;
            }
          }

         Kod_DM_izm[j-64]=ADC;
         Kod_M[j-64]=0.017*ADC;

       m1_1:;
     }
//    m2_end_5:;
 //   m2_end_3:;
 //====================================
         Sleep(10);

  }    /* end for по частоте */

   for(k1=0,P_max=P_min=P[0]; k1<=159; k1+=1)  /* вычисление max на кривой */
       {
        if(P[k1]>P_max) {P_max=P[k1];}//k_max=k1;}
        if(P[k1]<P_min) {P_min=P[k1];}//k_min=k1;}
       }

      Pmin_v=(float)P_min;
     // Pmax_v=(float)P_max;
     // dP=(float)fabs(P_max-P_min);

      StringGrid2->Cells[2*n_l_t][2*n_us_t+1]=CurrToStrF(Pmin_v,ffFixed,2);
      StringGrid2->Repaint();

   for(k1=0,Kod_max_km=Kod_min_km=Kod_DM_izm[0]; k1<=159; k1+=1)  /* вычисление max на кривой */
       {
        if(Kod_DM_izm[k1]>Kod_max_km) {Kod_max_km=Kod_DM_izm[k1];}//k_max=k1;}
        if(Kod_DM_izm[k1]<Kod_min_km) {Kod_min_km=Kod_DM_izm[k1];}//k_min=k1;}
       }

       StringGrid2->Cells[2*n_l_t+1][2*n_us_t+1]=IntToStr(Kod_min_km);
       StringGrid2->Repaint();

   end1:;                         /* пакет 2 */
 //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение матрицы для  1-го и 2-го канала СВЧ */=========================
     //     n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* от 0 до 7*/
         n_vh1= n_l_t; n_vh2=n_l_t;  /* от 0 до 7*/

  if(CB_53_vh->ItemIndex==0)
        {in1_at=0x1F;in2_at=0x1F;n_post=0;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==1)
       {in1_at=0x1F;in2_at=0x1F;n_post=0;nk_svch=2;
       } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==2)
        {in1_at=0x1F;in2_at=0x1F;n_post=1;nk_svch=1;
        }   /* код входного атт. 1-ого,2-ого канала -- 0x1F(5 разрядов)*/

  if(CB_53_vh->ItemIndex==3)
      {in1_at=0x1F;in2_at=0x1F;n_post=1;nk_svch=2;
      } /* код входного атт. 1-ого,2-ого канала-- 0x1F(5 разрядов)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных 2 в УП7 ERR=1!\n");
     //goto end;
    }
  if(res==2){ShowMessage("Нет ответных пакетов на пакет 2!");}
     Sleep(1);
                         /* пакет 1*/
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение канала усилителя, выключение источника питания УП7 */=========================
 if(RG53_10->ItemIndex==0)//(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
   {
    n_post=0;    /*ППС*/  /*индекс от 0 до 12*/  /* nu-- номер усилителя*/
    }
   if(RG53_10->ItemIndex==1)//(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/ /*индекс от 13 до 25*/  /* nu-- номер усилителя*/
    }
  // nu=0;  /* ???? nu-- nu=(номер усилителя*/

   if((res=Vykl_us_vip_t(n_post))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных (1) в УП7 ERR=1!\n");
    // goto end;
    }
    if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");}
    Sleep(1);
     } /*  цикл по лучам одного усилителя */
    end_vhod:;
   viPrintf(viG,"OUTPut:STATe OFF\n"); //подкл.  сигнала на выход ген-ра

  }  /*  цикл по выходам (усилителям) */

   end:;
     viPrintf(viG,"OUTPut:STATe OFF\n"); //выкл. сигнала на выход ген-ра
     /*для выхода по стоп */
                             /* пакет 1*/
  //-----------------формуляр передачи данных в УП7 -------------------------------------------------------
//============/* выключение канала усилителя, выключение источника питания УП7 */=========================
 if(RG53_10->ItemIndex==0)//(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(ППС), 3(ЗПС)*/
   {
    n_post=0;    /*ППС*/  /*индекс от 0 до 12*/  /* nu-- номер усилителя*/
    }
   if(RG53_10->ItemIndex==1)//(CB_53_vyh->ItemIndex>11)
   {
    n_post=1; /*ЗПС*/ /*индекс от 13 до 25*/  /* nu-- номер усилителя*/
    }

   if((res=Vykl_us_vip_t(n_post))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра данных (1) в УП7 ERR=1!\n");
    // goto end;
    }
    if(res==2){ShowMessage("Нет ответных пакетов на пакет 1!");}
    Sleep(1);

    ShowMessage("Измерение закончено\n");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button39Click(TObject *Sender)
{
extern bool vyh;
 vyh=false;
}
//---------------Измерение температуры ------------------------------------------------------------
void __fastcall TForm1::Button48Click(TObject *Sender)
{
 extern bool vyh;

  unsigned NVIP=0x0,TM1=0x0,TM2=0x0,TM3=0x0;
  int T;
  int nf=0x8;/* номер запроса 8 либо 9*/

 //char buf1[256]={0};
// char buf2[256]={0};

 char buf[256]={0};
 int j,k,n_jj;

 char buf1[256]={0};
 int n_post;
  unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
   int nk,nu;  /* номер КИО*/

  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned IPK_UP7;

  u32 buf_my[256/4]; // Буфер для принятого пакета

  union{
       struct{
                  U32   len   : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8,
                        byte5   : 8,
                        byte6   : 8,
                        byte7   : 8,
                        byte8   : 8,
                        byte9   : 8,
                        byte10  : 8;
              } p_my_v;
             U32 buf_my[256/4];
             } packet_my_t;

         E_53_um->Text=" ";
         E_53_um->Repaint();

         E_t53_0->Text=" ";
         E_t53_0->Repaint();

         E_t53_1->Text=" ";
         E_t53_1->Repaint();

             /* пакет 8*/

              E_53_izm_m->Text=" ";
              E_53_izm_m->Repaint();

for(i=0;i<=9;i++)  /* чтение датчика температуры без индикации */
    {
    if(RG53_10->ItemIndex==0) //if(CB_53_vyh->ItemIndex<=11)   /*  в зависимости от выхода*/
     {
     n_post=0; /*ППС*/
     }
    if(RG53_10->ItemIndex==1) //if(CB_53_vyh->ItemIndex>11)
     {
     n_post=1; /*ЗПС*/
     }
        nf=0x8;/* запрос состояния */
//17.07 n_jj=0;

//17.07m_jj_1:
if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра запроса данных в УП7!\n");
     goto end;
    }

  // ShowMessage("Формуляр передачи запроса данных в УП7 прошел!\n");


   Sleep(10);
//17.07   if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
//17.07   {
//17.07        // Нет принятых пакетов//     ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07   }

   if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
   {
//17.07        // Нет принятых пакетов
//17.07 //       ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07     if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj_1;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("Сбой по магистрале!");
//17.07       goto m2_end_2;
//17.07      }
   }
  else
    {
        // Принят пакет
        LEN=packet_my_t.p_my_v.len;
        IPK=packet_my_t.p_my_v.byte1;
        SRC=packet_my_t.p_my_v.byte2&0x1F;
        DST=((packet_my_t.p_my_v.byte2>>5)&0x7)|((packet_my_t.p_my_v.byte3&0x3)<<3);  /* левое крыло DST=0x6, правое крыло DST=0x7*/
        IPS=(packet_my_t.p_my_v.byte3>>2)&0x3F;
        ERR=packet_my_t.p_my_v.byte4&0x1;
        /*ADR_UP7=packet_my_t.p_my_v.byte5;*/
        IPK_UP7=packet_my_t.p_my_v.byte5;
        NVIP=packet_my_t.p_my_v.byte6&0x1;
        TM1=packet_my_t.p_my_v.byte7&0xFF|((packet_my_t.p_my_v.byte8&0xF)<<8);
        TM2=(packet_my_t.p_my_v.byte8>>4)&0xF|(packet_my_t.p_my_v.byte9&0xFF)<<4;

//10.01.11    if(ERR==1)
//      {
//         //ShowMessage("Ошибка при передаче пакета 1 УП7! ERR=1");
//           n_jj=n_jj+1;
//         if(n_jj<=9)
//            {
//             goto m_jj_1;
//            }
//          else
//            {
//             ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении температуры! ERR=1");
//             goto m21;
//            }
//        }
       // if(NVIP==0x1) ShowMessage("Неисправность источника питания!");
    } /* end else from recive*/
  m21:;
    // Sleep(1000);
}/*end for */
m2_end_2:;

      vyh=true;

 while(vyh==true)
  {
   Application->ProcessMessages();
   if(vyh==false) goto end;
        /* пакет 8 запрос температуры*/
        nf=0x8;
   if(RG53_10->ItemIndex==0) //if(CB_53_vyh->ItemIndex<=11) /*  в зависимости от выхода*/
     {
     n_post=0; /*ППС*/
     }
   if(RG53_10->ItemIndex==1) // if(CB_53_vyh->ItemIndex>11)
     {
     n_post=1; /*ЗПС*/
     }
     nf=0x8;/* запрос состояния */
     n_jj=0;

m_jj_2:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- нет ошибок, 1-- есть ошибки */
      {
       ShowMessage("Ошибка при передаче формуляра запроса данных в УП7!\n");
       vyh=false; goto end;
      }

  // ShowMessage("Формуляр передачи запроса данных в УП7 прошел!\n");

   Sleep(10);
//17.07  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
//17.07     {
//17.07        // Нет принятых пакетов
//17.07 //       ShowMessage("Нет принятых пакетов после запроса состояния!");
//17.07     if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj_2;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("Сбой по магистрале!");
//17.07      vyh=false; goto end;// goto m2_end_3;
//17.07      }
//17.07    }

   if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
    {
        // Нет принятых пакетов
//23.12       ShowMessage("Нет принятых пакетов после запроса состояния!");
    }
   else
      {
        // Принят пакет
          LEN=packet_my_t.p_my_v.len;
          IPK=packet_my_t.p_my_v.byte1;
          SRC=packet_my_t.p_my_v.byte2&0x1F;
          DST=((packet_my_t.p_my_v.byte2>>5)&0x7)|((packet_my_t.p_my_v.byte3&0x3)<<3);  /* левое крыло DST=0x6, правое крыло DST=0x7*/
          IPS=(packet_my_t.p_my_v.byte3>>2)&0x3F;
          ERR=packet_my_t.p_my_v.byte4&0x1;
        /*ADR_UP7=packet_my.p_my_v.byte5;*/
          IPK_UP7=packet_my_t.p_my_v.byte5;
          NVIP=packet_my_t.p_my_v.byte6&0x1;
          TM1=packet_my_t.p_my_v.byte7&0xFF|((packet_my_t.p_my_v.byte8&0xF)<<8);
          TM2=(packet_my_t.p_my_v.byte8>>4)&0xF|(packet_my_t.p_my_v.byte9&0xFF)<<4;

     if(ERR==1)
         {
          //ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении Т! ERR=1");
             n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj_2;
            }
          else
            {
             ShowMessage("Ошибка при передаче ответного пакета УП7 при чтении T! ERR=1");
             vyh=false; goto end; // goto m22;
            }
        }
      //22.12.10  if(NVIP==0x1) ShowMessage("Неисправность источника питания!");
//        T=235-(400*(int)TM1)/(int)TM2;
       if((TM1==0)||(TM2==0)){;}
          else
           {
             T=235-(400*TM1)/TM2;

             memset(&buf1,0,20); /* ???????? ?????? */;
             sprintf(buf1,"%d",T);
/* 22.12.10 */
 if(n_post==0)
           {
           E_t53_0->Text=buf1;
           E_t53_0->Repaint();
           }
          else
           {
           E_t53_1->Text=buf1;
           E_t53_1->Repaint();
           }

      }

    } /*else from recive*/

    Sleep(1);
   }  /* while*/
  end:;

   ShowMessage("Измерение закончено\n");
}
//---------------------------------------------------------------------------
