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
#include <math.hpp>
#include <string.h>
#include <process.h>

#pragma package(smart_init)


  bool circle;
  bool vyh;
  double F_rtu[224]={4026.0,4090.0,4154.0,4218.0,4282.0,4346.0,4410.0,4474.0,//1-� ����� ���
                   4526.0,4590.0,4654.0,4718.0,4782.0,4846.0,4910.0,4974.0,//2-� ����� ���

                   5026.0,5090.0,5154.0,5218.0,5282.0,5346.0,5410.0,5474.0,//3-� ����� ���
                   5526.0,5590.0,5654.0,5718.0,5782.0,5846.0,5910.0,5974.0,//4-� ����� ���

                   6026.0,6090.0,6154.0,6218.0,6282.0,6346.0,6410.0,6474.0,//5-� ����� ���
                   6526.0,6590.0,6654.0,6718.0,6782.0,6846.0,6910.0,6974.0,//6-� ����� ���

                   7026.0,7090.0,7154.0,7218.0,7282.0,7346.0,7410.0,7474.0,//7-� ����� ���
                   7526.0,7590.0,7654.0,7718.0,7782.0,7846.0,7910.0,7974.0,//8-� ����� ���

                   8026.0,8090.0,8154.0,8218.0,8282.0,8346.0,8410.0,8474.0,//9-� ����� ���
                   8526.0,8590.0,8654.0,8718.0,8782.0,8846.0,8910.0,8974.0,//10-� ����� ���

                   9026.0,9090.0,9154.0,9218.0,9282.0,9346.0,9410.0,9474.0,//11-� ����� ���
                   9526.0,9590.0,9654.0,9718.0,9782.0,9846.0,9910.0,9974.0,//12-� ����� ���

                   10026.0,10090.0,10154.0,10218.0,10282.0,10346.0,10410.0,10474.0,//13-� ����� ���
                   10526.0,10590.0,10654.0,10718.0,10782.0,10846.0,10910.0,10974.0,//14-� ����� ���

                   11026.0,11090.0,11154.0,11218.0,11282.0,11346.0,11410.0,11474.0,//15-� ����� ���
                   11526.0,11590.0,11654.0,11718.0,11782.0,11846.0,11910.0,11974.0,//16-� ����� ���

                   12026.0,12090.0,12154.0,12218.0,12282.0,12346.0,12410.0,12474.0,//17-� ����� ���
                   12526.0,12590.0,12654.0,12718.0,12782.0,12846.0,12910.0,12974.0,//18-� ����� ���

                   13026.0,13090.0,13154.0,13218.0,13282.0,13346.0,13410.0,13474.0,//19-� ����� ���
                   13526.0,13590.0,13654.0,13718.0,13782.0,13846.0,13910.0,13974.0,//20-� ����� ���

                   14026.0,14090.0,14154.0,14218.0,14282.0,14346.0,14410.0,14474.0,//21-� ����� ���
                   14526.0,14590.0,14654.0,14718.0,14782.0,14846.0,14910.0,14974.0,//22-� ����� ���

                   15026.0,15090.0,15154.0,15218.0,15282.0,15346.0,15410.0,15474.0,//23-� ����� ���
                   15526.0,15590.0,15654.0,15718.0,15782.0,15846.0,15910.0,15974.0,//24-� ����� ���

                   16026.0,16090.0,16154.0,16218.0,16282.0,16346.0,16410.0,16474.0,//25-� ����� ���
                   16526.0,16590.0,16654.0,16718.0,16782.0,16846.0,16910.0,16974.0,//26-� ����� ���

                   17026.0,17090.0,17154.0,17218.0,17282.0,17346.0,17410.0,17474.0,//27-� ����� ���
                   17526.0,17590.0,17654.0,17718.0,17782.0,17846.0,17910.0,17974.0//28-� ����� ���
                   };

//---------------------------------------------------------------------------
unsigned AT_1[4][64],AT_2[4][64],AT_3[4][64],AT_4[4][64],AT_5[4][64],AT_6[4][64],
         AT_7[4][64],AT_8[4][64],AT_9[4][64],AT_10[4][64],AT_11[4][64],
         AT_12[4][64],AT_13[4][64];  /* ����������� �������� ������. ����������� ������ 2*/
unsigned IN_AT[4][64];  /* ���������� ���������� ����� ������ 2 */
int Q[4][64]; /* ������ ���������� �������� ����� ������� ���. */
//float P_mod[4][13][64]; /* ������ ��� ������ � ���� 13 �������� (��� ������� ���������) ����� ��� ���. �� 4 ����� � �� ������ ��������� �����*/
unsigned AT_1_53[8][160],AT_2_53[8][160],AT_3_53[8][160],AT_4_53[8][160],
         AT_5_53[8][160],AT_6_53[8][160],AT_7_53[8][160],AT_8_53[8][160],
         AT_9_53[8][160],AT_10_53[8][160],AT_11_53[8][160],AT_12_53[8][160],
         AT_13_53[8][160];  /* ����������� �������� ������. ����������� ������ 53*/
unsigned IN_AT_53[8][160];  /* ���������� ���������� ����� ������ 53*/

unsigned long FileSize(FILE *file);
unsigned long FileSize(const char *file_name);
//u16 __fastcall GetCRC(FILE *file,u32 fsize);
u16 GetCRC(FILE *file,u32 fsize);

//---------------------------------------------------------------------------
void __fastcall TForm1::CalbOutChan(TObject *Sender)
{
extern double F_rtu[224];
  double freq;
  char buf1[256]={0};
ShowPanel(P_1);
P_1->Visible=true;
Panel1->Visible=false;
Panel2->Visible=false;
PanelPotent->Visible=false;
Mode=1;

freq=F_rtu[UD2_f->Position];
 sprintf(buf1,"%.2f",freq);
          E2_f->Text=buf1;
          E2_f->Repaint();


 freq=F_rtu[UD53_f->Position+64];
  sprintf(buf1,"%.2f",freq);
          E53_f->Text=buf1;
          E53_f->Repaint();
          FileCalbGnPm();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::B2_puskClick(TObject *Sender)
{
 if(ChkDevs==true)
 {
  Calib2OutChn();
  }
  else
  {
 if(FindDevises()==true)
  {
  if(ChekDev()==true)
  {
  Calib2OutChn();
    }
  }    //FindDevises()
 }//else
}
//-----    ������ �����  --------------------------------
void TForm1::Calib2OutChn(void)
{
  extern bool vyh;
  ViStatus stat=0; // ���������� ���������� ���� ViStatus
  extern double F_rtu[224];

   double powerDBM=0.0;
   double m_freqq;
   double power;

  unsigned ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8,ADC9,ADC10,ADC11,ADC12,ADC13;
  int ADC=0;

  unsigned NVIP=0x0,TM1=0x0,TM2=0x0;
  int T;
  int nf=0x8;/* ����� ������� 8 ���� 9*/

 //char buf1[256]={0};
// char buf2[256]={0};

 char buf[256]={0};

 double P[25];
 double dP;
 int j,k,n_jj;
 //int num=0;
 //char rdbuffer[256]={0};

 int ind; //������ ������� � �������� ����������
 long longdown=0; /* �������� �������� ����������*/

 double m_p,m_p_1;  /* ��������, ���������� �� ����������*/
 double pn;
 double pv;
 double pstep;

 double m_Pow;
 char buf1[256]={0};
 int n_post;
  unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
   int nk,nu;  /* ����� ���*/
  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 �������� 00000, 00001,00010,00100,01000,10000*/
  //unsigned Q_vh[5]={0x0,0x1,0x2,0x4,0x8}; /* 0000, 0001,0010,0100,1000*/
  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* 0000,0001,...,1111 */
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned kod_att[13];
  unsigned IPK_UP7;
	unsigned indLit=0, indPSph=0,  indOut=CB_10_vyh->ItemIndex;
  AnsiString str2[26]={"���1","���2","���3","���4",
                       "���5","���6","���7","���8",
                       "���9","���10","���11","���12","���13",
                       "���1","���2","���3","���4",
                       "���5","���6","���7","���8",
                       "���9","���10","���11","���12","���13"};
  AnsiString str1[4]={"1��-2","2��-2","3��-2","4��-2"};

  u32 buf_my[256/4]; // ����� ��� ��������� ������

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
                        byte17  : 8, /*ADC12 */
                        byte18  : 8; /*ADC13 */

                        } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;

         E_2_um->Text=" ";
         E_2_um->Repaint();

         E_t2_0->Text=" ";
         E_t2_0->Repaint();

         E_t2_1->Text=" ";
         E_t2_1->Repaint();

             /* ����� 8*/

              E2_izm_m->Text=" ";
              E2_izm_m->Repaint();

       ShowMessage("������ ������ � �� ���������� �� ���� "+str1[CB_3_vh->ItemIndex]);
       ShowMessage("���������� ���������� �������� ����� ���������� 30�� � ������ "+str2[CB_10_vyh->ItemIndex]);

   /*  if(comm_vhod(CB_3_vh->ItemIndex))  //1 -- ������, 0 -- ��� ������
           {
             ShowMessage("�� �������� ���������� 1");
             goto end;
             }
     if(comm_vyhod(CB_10_vyh->ItemIndex))//1 -- ������, 0 -- ��� ������
            {
             ShowMessage("�� �������� ���������� 2");
             goto end;
             }
     */

                    /* ����� 2*/
    /*  ������� ��������� ���������������� ������ ������� ������� �� */
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������� ���  1-�� � 2-�� ������ ��� */=========================
          n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* �� 0 �� 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
      if(CB_10_vyh->ItemIndex>12) /* ���� ������ ���, �� ��������� ���*/
           n_post=3; /*���*/   /* ���� ������ ���, �� ��������� ���*/
           else  n_post=2;  nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
                 n_post=3;
           else  n_post=2; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
         if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
                 n_post=2;
           else  n_post=3;  nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
          if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
              n_post=2;
           else  n_post=3; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7!\n");
     //goto end;
    }

  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
   Sleep(1);
                       /* ����� 2*/
 //============/* ��������� ������ ������ ������� �� ��� 1-��� � 2-��� ������ */========================================
//============/* ������� ���� ������� ��� ��� 1-��� � 2-��� ������ */==========================
  //if(((UD_2->Position)>=1)&&((UD_2->Position)<=4))
  // {
  //  n_post=2;   /* 1--0: 2(���), 3(���)*/
  // }
  // else  n_post=3;   /* 1--0: 2(���), 3(���)*/

 // if(n_post==2){n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;} /* n_vh1 -- ����� ������ ������� ��� 1-��� ������ ��� 0--0xF (4 �������)*/
 // if(n_post==3){n_vh2= 3+UD_2->Position; n_vh1=3+UD_2->Position;} /* n_vh2 -- ����� ������ ������� ��� 2-��� ������ ��� 0--0xF (4 �������)*/
        n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* �� 0 �� 7*/
  if(CB_3_vh->ItemIndex==0){in1_at=Qv_vh[CB10_att_vh->ItemIndex];in2_at=0x1F;
                                 n_post=2; nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[CB10_att_vh->ItemIndex];
                        n_post=2; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=Qv_vh[CB10_att_vh->ItemIndex];in2_at=0x1F;
                      n_post=3;   nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[CB10_att_vh->ItemIndex];
             n_post=3; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  //  if((CB_10_vyh->ItemIndex<=12)&&(n_vh1>=4))
   //    {
   //     ShowMessage("����� ���������� ���� �� ������������� ���������� ������ ���!\n");
   //     goto end;
   //    }
   //  if((CB_10_vyh->ItemIndex>=13)&&(n_vh1<=4))
   //    {
    //    ShowMessage("����� ���������� ���� �� ������������� ���������� ������ ���!\n");
    //    goto end;
    //    }


 if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ������ 2 � ��7 ERR=1!\n");
   //  goto end1;
    }

   /* ����� ��������� ������ */
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
       Sleep(1);

       /* ����� 3*/
    for(i=0;i<=12;i++)
      {
      // US[i]=0x0;
       kod_att[i]=0xF;
      }
  //============/* �������� ������� ���� �������� ��� */====
   if(CB_10_vyh->ItemIndex<=12)
   {
    n_post=2;    /*���*/
    kod_att[CB_10_vyh->ItemIndex]= Q_vh[CB10_att_vyh->ItemIndex];
      /* �������� */
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
  if(CB_10_vyh->ItemIndex>12)
   {
	 n_post=3; /*���*/
	 indPSph=1;
	 indOut= CB_10_vyh->ItemIndex-13;
	 kod_att[CB_10_vyh->ItemIndex-13]= Q_vh[CB10_att_vyh->ItemIndex];

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
 if((res=Vkl_att_t(n_post,kod_att))==1)   /*0-- ��� ������, 1-- ���� ������ */
     {
      ShowMessage("������ ��� �������� ������ 3 ERR=1");
     // goto end;
     }
 if(res==2) {ShowMessage("��� �������� ������� �� ����� 3!");}

			Sleep(1);

	 if(SetOUT_EUS( indLit, indPSph,  indOut)==false) goto end;
				  /* ����� 1*/
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
 //============/* ��������� ������ ���������, ��������� ��������� ������� ��7 */========================================            /* ����� 1*/
  //n_post=2+(CB_2_ps->ItemIndex);
  if(CB_10_vyh->ItemIndex<=12)  /* 1--0: 2(���), 3(���)*/
   {
    n_post=2;    /*���*/
    nu=(CB_10_vyh->ItemIndex);    /*������ �� 0 �� 12*/  /* nu-- ����� ���������*/
    }
   if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
    nu=(CB_10_vyh->ItemIndex)-13;    /*������ �� 13 �� 25*/  /* nu-- ����� ���������*/
    }
  // nu=0;  /* ???? nu-- nu=(����� ���������*/
   if((res=Vkl_us_vip_t(n_post,nu))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ������ 1 � ��7 ERR=1!\n");
 //  goto end;
    }
   if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");}

   Sleep(1);

//*************************************************************************

       //��������� ����� �� GPIB

    m_freqq=F_rtu[UD2_f->Position];
   //m_freqq = strtod(E2_f->Text.c_str(),NULL);

   powerDBM = strtod(E2_p->Text.c_str(),NULL);

 /*15.12.10*/ //    power = -70.0;  //�������
 // ��������� �� ��������� ������� � ��������
 // powerDBM = power;
 stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // �������
 stat = viPrintf(viG,":POW %f dBm\n",powerDBM); // ��������
   if (stat != VI_SUCCESS)
  {
     ShowMessage("������ ��� ��������� �������� �� ���������");
     goto end;
  }
 // viPrintf(vigen,"PULM:STAT OFF\n");   // �������� ��� ���������
   viPrintf(viG,"OUTPut:STATe ON\n"); //�����.  ������� �� ����� ���-��

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

  for(k=0; k<=63;k++) /* ����������� ind*/
   {
   if(F_rtu[k]==m_freqq){ind=k;break;}
    }

  // ind=(f-Fl)/StepCalb;
   m_p=powerDBM;
   m_p_1=m_p-dPg[ind];     /*� ������ ���������� ������*/
   // m_p_1=m_p;

   stat = viPrintf(viG,":POW %f dBm\n",m_p_1); // �������� �� ����������

 for(i=0;i<=9;i++)  /* ������ ������� ����������� ��� ��������� */
    {
  //  if((CB_3_vh->ItemIndex==0)||(CB_3_vh->ItemIndex==1))
  //   {
  //   n_post=2; /**/
  //   }
  //  if((CB_3_vh->ItemIndex==2)||(CB_3_vh->ItemIndex==3))
  //   {
  //   n_post=3; /**/
  //   }
   if(CB_10_vyh->ItemIndex<=12)   /*  � ����������� �� ������*/
     {
     n_post=2; /**/
     }
    if(CB_10_vyh->ItemIndex>12)
     {
     n_post=3; /**/
     }
        nf=0x8;/* ������ ��������� */
//17.07 n_jj=0;

//17.07 m_jj_1:
if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������� ������ � ��7!\n");
     goto end;
    }

  // ShowMessage("�������� �������� ������� ������ � ��7 ������!\n");


   Sleep(10);
//17.07   if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07        // ��� �������� �������//     ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07   }

   if(!UPS_RECIV_KIO_PACKET(&nk,packet_my.buf_my))
   {
        // ��� �������� �������
//       ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07     if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj_1;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("���� �� ����������!");
//17.07       goto m2_end_2;
//17.07      }
   }
  else
    {
        // ������ �����
        LEN=packet_my_t.p_my_v.len;
        IPK=packet_my_t.p_my_v.byte1;
        SRC=packet_my.p_my_v.byte2&0x1F;
        DST=((packet_my_t.p_my_v.byte2>>5)&0x7)|((packet_my_t.p_my_v.byte3&0x3)<<3);  /* ����� ����� DST=0x6, ������ ����� DST=0x7*/
        IPS=(packet_my_t.p_my_v.byte3>>2)&0x3F;
        ERR=packet_my_t.p_my_v.byte4&0x1;
        /*ADR_UP7=packet_my_t.p_my_v.byte5;*/
        IPK_UP7=packet_my_t.p_my_v.byte5;
        NVIP=packet_my_t.p_my_v.byte6&0x1;
        TM1=packet_my_t.p_my_v.byte7&0xFF|((packet_my_t.p_my_v.byte8&0xF)<<8);
        TM2=(packet_my_t.p_my_v.byte8>>4)&0xF|(packet_my_t.p_my_v.byte9&0xFF)<<4;

//10.01.11    if(ERR==1)
//      {
//         //ShowMessage("������ ��� �������� ������ 1 ��7! ERR=1");
//           n_jj=n_jj+1;
//         if(n_jj<=9)
//            {
//             goto m_jj_1;
//            }
//          else
//            {
//             ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ �����������! ERR=1");
//            goto m21;
//            }
//        }
       // if(NVIP==0x1) ShowMessage("������������� ��������� �������!");
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
  //  m_Pow=m_Pow-dPm[ind]+30.0;   /*� ������ ���������� ������*/
      m_Pow=m_Pow-dPm[ind];   /*� ������ ���������� ������*/

        //  Pw=pow(10,Pdbm/10); //���       Pw=pow(10,-3)*pow(10,Pdbm/10);  //��

          m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

           memset(&buf1,0,20);
           sprintf(buf1,"%.3f",m_Pow);

           E2_izm_m->Text=buf1;  /* ��������*/
           E2_izm_m->Repaint();

    Sleep(1);

        /* ����� 8 ������ �����������*/
        nf=0x8;
   if(CB_10_vyh->ItemIndex<=12) /*  � ����������� �� ������*/
     {
     n_post=2; /**/
     }
    if(CB_10_vyh->ItemIndex>12)
     {
     n_post=3; /**/
     }
     nf=0x8;/* ������ ��������� */
     n_jj=0;

m_jj_2:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- ��� ������, 1-- ���� ������ */
      {
       ShowMessage("������ ��� �������� ��������� ������� ������ � ��7!\n");
       vyh=false; goto end;
      }

  // ShowMessage("�������� �������� ������� ������ � ��7 ������!\n");

   Sleep(10);
//17.07  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
//17.07     {
//17.07        // ��� �������� �������
//17.07//       ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07     if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj_2;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("���� �� ����������!");
//17.07      vyh=false; goto end;// goto m2_end_3;
//17.07      }
//17.07    }

   if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
    {
        // ��� �������� �������
//23.12       ShowMessage("��� �������� ������� ����� ������� ���������!");
    }
   else
      {
        // ������ �����
          LEN=packet_my_t.p_my_v.len;
          IPK=packet_my_t.p_my_v.byte1;
          SRC=packet_my_t.p_my_v.byte2&0x1F;
          DST=((packet_my_t.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* ����� ����� DST=0x6, ������ ����� DST=0x7*/
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
          //ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ �! ERR=1");
             n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj_2;
            }
          else
            {
             ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ T! ERR=1");
             vyh=false; goto end; // goto m22;
            }
        }
      //22.12.10  if(NVIP==0x1) ShowMessage("������������� ��������� �������!");
//        T=235-(400*(int)TM1)/(int)TM2;
       if((TM1==0)||(TM2==0)){;}
          else
           {
             T=235-(400*TM1)/TM2;

             memset(&buf1,0,20); /* ???????? ?????? */;
             sprintf(buf1,"%d",T);
/* 22.12.10 */
 if(n_post==2)
           {
           E_t2_0->Text=buf1;
           E_t2_0->Repaint();
           }
          else
           {
           E_t2_1->Text=buf1;
           E_t2_1->Repaint();
           }

        }

    } /*else from recive*/

    Sleep(1);
                   /* ������ ���� �������� */
                         /* ����� 9*/
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//----------------������ ������ �������� ��� ������� ����������------------------------------
 // if((CB_3_vh->ItemIndex==0)||(CB_3_vh->ItemIndex==1))
//   {
//  n_post=2; /*���*/
//   }
//  if((CB_3_vh->ItemIndex==2)||(CB_3_vh->ItemIndex==3))
//    {
//      n_post=3; /*���*/
//    }
 if(CB_10_vyh->ItemIndex<=12)  /* � ����������� �� ������ */     {
     n_post=2; /**/
     }
  if(CB_10_vyh->ItemIndex>12)
     {
     n_post=3; /**/
     }

     nf=0x9;
 n_jj=0;

m_jj:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- ��� ������, 1-- ���� ������ */
   {
     ShowMessage("������ ��� �������� ��������� ������� ������ (9) � ��7!\n");
    // 10.01.11 vyh=false; goto end;
   }

  Sleep(10);
//17.07 if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07        // ��� �������� �������
//17.07//     ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07   }

  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
//17.07        // ��� �������� �������
//17.07//     ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07      if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("���� �� ����������!");
//17.07       vyh=false; goto end; //goto m2_end_5;
//17.07      }
   }
   else
   {
        // ������ �����

      LEN=packet_my_km.p_my_v.len;
      IPK=packet_my_km.p_my_v.byte1;
      SRC=packet_my_km.p_my_v.byte2&0x1F;
      DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* ����� ����� DST=0x6, ������ ����� DST=0x7*/
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
      ADC13=packet_my_km.p_my_v.byte18;

// 22.12.10
    if(CB_10_vyh->ItemIndex<=12)  /* � ����������� �� ������ */
      {
        if(CB_10_vyh->ItemIndex==0) ADC=ADC1&0xFF;
        if(CB_10_vyh->ItemIndex==1) ADC=ADC2&0xFF;
        if(CB_10_vyh->ItemIndex==2) ADC=ADC3&0xFF;
        if(CB_10_vyh->ItemIndex==3) ADC=ADC4&0xFF;
        if(CB_10_vyh->ItemIndex==4) ADC=ADC5&0xFF;
        if(CB_10_vyh->ItemIndex==5) ADC=ADC6&0xFF;
        if(CB_10_vyh->ItemIndex==6) ADC=ADC7&0xFF;
        if(CB_10_vyh->ItemIndex==7) ADC=ADC8&0xFF;
        if(CB_10_vyh->ItemIndex==8) ADC=ADC9&0xFF;
        if(CB_10_vyh->ItemIndex==9) ADC=ADC10&0xFF;
        if(CB_10_vyh->ItemIndex==10) ADC=ADC11&0xFF;
        if(CB_10_vyh->ItemIndex==11) ADC=ADC12&0xFF;
        if(CB_10_vyh->ItemIndex==12) ADC=ADC13&0xFF;
      }
      if(CB_10_vyh->ItemIndex>12)  /* � ����������� �� ������ */
      {
        if(CB_10_vyh->ItemIndex==13) ADC=ADC1&0xFF;
        if(CB_10_vyh->ItemIndex==14) ADC=ADC2&0xFF;
        if(CB_10_vyh->ItemIndex==15) ADC=ADC3&0xFF;
        if(CB_10_vyh->ItemIndex==16) ADC=ADC4&0xFF;
        if(CB_10_vyh->ItemIndex==17) ADC=ADC5&0xFF;
        if(CB_10_vyh->ItemIndex==18) ADC=ADC6&0xFF;
        if(CB_10_vyh->ItemIndex==19) ADC=ADC7&0xFF;
        if(CB_10_vyh->ItemIndex==20) ADC=ADC8&0xFF;
        if(CB_10_vyh->ItemIndex==21) ADC=ADC9&0xFF;
        if(CB_10_vyh->ItemIndex==22) ADC=ADC10&0xFF;
        if(CB_10_vyh->ItemIndex==23) ADC=ADC11&0xFF;
        if(CB_10_vyh->ItemIndex==24) ADC=ADC12&0xFF;
        if(CB_10_vyh->ItemIndex==25) ADC=ADC13&0xFF;
      }

       if(ERR==1)
         {
          //ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ ���� ��������! ERR=1");
          //goto m1;
           n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj;
            }
          else
            {
             ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ ���� ��������! ERR=1");
             goto m1;
            }
          }
           memset(&buf1,0,20);
           sprintf(buf1,"%d",ADC);

           E_2_um->Text=buf1;
           E_2_um->Repaint();

       m1:;
     }
    m2_end_5:;
    m2_end_3:;

   }  /* while*/
   end1:;                         /* ����� 2 */
 //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������� ���  1-�� � 2-�� ������ ��� */=========================
          n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* �� 0 �� 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
                           n_post=2;  nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           // if(CB_10_vyh->ItemIndex<=12)
                 n_post=2;    /*���*/
         //  else  n_post=3;
         nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
            n_post=3; nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
            n_post=3; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7!\n");
     //goto end;
    }

  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
   Sleep(1);
                          /* ����� 1*/
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������ ���������, ���������� ��������� ������� ��7 */=========================
 if(CB_10_vyh->ItemIndex<=12)  /* 1--0: 2(���), 3(���)*/
   {
    n_post=2;    /*���*/
   // nu=(CB_10_vyh->ItemIndex);    /*������ �� 0 �� 12*/  /* nu-- ����� ���������*/
    }
   if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
   // nu=13-(CB_10_vyh->ItemIndex);    /*������ �� 13 �� 25*/  /* nu-- ����� ���������*/
    }
  // nu=0;  /* ???? nu-- nu=(����� ���������*/

   if((res=Vykl_us_vip_t(n_post))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ (1) � ��7!\n");
     //goto end;
    }
   if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");}

     Sleep(1);
 end:;
  viPrintf(viG,"OUTPut:STATe OFF\n"); //����. ������� �� ����� ���-��
      EUSOff(); //��������� ��� ��������� � ��������� ���������,  �����1
    ShowMessage("��������� ���������\n");
}

//---------------------------------------------------------------------------

void __fastcall TForm1::B2_stopClick(TObject *Sender)
{

  extern bool vyh;
  extern bool circle;
  vyh=false;
  circle=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Bt_ZClick(TObject *Sender)
{
 P_1->Visible=false;
}
 //-----------------------------------------------------------------
void __fastcall TForm1::UD2_fClick(TObject *Sender, TUDBtnType Button)
{
 extern double F_rtu[224];
 double freq;
 char buf1[256]={0};

 freq=F_rtu[UD2_f->Position];
 sprintf(buf1,"%.2f",freq);
          E2_f->Text=buf1;
          E2_f->Repaint();
}
//----------------------------------------------------------------------
//============/* ���������� ������� �� ��� 1-��� � 2-��� ������ */========================================
//============/*  ��� ������� ��� ��� 1-��� � 2-��� ������ =0x1F*/==========================
int TForm1::Vykl_nk_att(int n_post,unsigned n_vh1,unsigned n_vh2,unsigned in1_at,unsigned in2_at,unsigned nk_svch)   /*0-- ��� ������, 1-- ���� ������ */
{
  int i,jk,ret;

 unsigned LEN,IPK=0xFF;
 unsigned DST=0x7,SRC=0x0,IPS=0x21; //IPS=100001 (0x21)
 unsigned ADR_UP7; /*����� ��7  2-���2 (���), 3 -- ���2 (���) */
 unsigned IPK_UP7=0x2; /* ������������� ������ ��7=2: ���������� ������� ������ �� ���� ������� ��� */

 unsigned N1_O[4]={0};/* ����� ������ ������� �� ��� 1-��� ������ */
 unsigned N2_O[4]={0};/* ����� ������ ������� �� ��� 2-��� ������ */
 unsigned ON_1,ON_2;  /* ��������� max(ON1=ON2=0) ��������� �� ������ IN1_AT, IN2_AT */
 unsigned IN_1_AT[5]={0};  /* ��������� 1-��� �������� ��� */
 unsigned IN_2_AT[5]={0};  /* ��������� 2-��� �������� ��� */
  // char buf1[256]={0};

 // u32 buf_my[256/4]; // ����� ��� ��������� ������
  // int nplis;      // ����� ����
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
                        byte8   : 8;

              } p_my;
             U32 buf[256/4];
             }  packet;
         LEN=0x9; /*9*/
         IPK=0xFF;
//         ADR_UP7=CB2_ps->3-ItemIndex;   /* 1--0: 2(���), 3(���)*/
          ADR_UP7=n_post; /* ����� ����� */

//       for(i=0;i<=12;i++)
//         {
//          US[i]=0x0;
//         }
//        US[nu]=0x1; /* nu-- ����� ���������*/

      // �������� �������� ������ � ��7

        N1_O[0]=n_vh1&0x1;
        N1_O[1]=(n_vh1>>1)&0x1;
        N1_O[2]=(n_vh1>>2)&0x1;
        N1_O[3]=(n_vh1>>3)&0x1;

        N2_O[0]=n_vh2&0x1;
        N2_O[1]=(n_vh2>>1)&0x1;
        N2_O[2]=(n_vh2>>2)&0x1;
        N2_O[3]=(n_vh2>>3)&0x1;

        IN_1_AT[0]=in1_at&0x1;
        IN_1_AT[1]=(in1_at>>1)&0x1;
        IN_1_AT[2]=(in1_at>>2)&0x1;
        IN_1_AT[3]=(in1_at>>3)&0x1;
        IN_1_AT[4]=(in1_at>>4)&0x1;

        IN_2_AT[0]=in2_at&0x1;
        IN_2_AT[1]=(in2_at>>1)&0x1;
        IN_2_AT[2]=(in2_at>>2)&0x1;
        IN_2_AT[3]=(in2_at>>3)&0x1;
        IN_2_AT[4]=(in2_at>>4)&0x1;

      //  if(nk_svch==1) ON_1=0x0;
      //  if(nk_svch==2) ON_2=0x0; /* �� ������������ ��������� */

         ON_1=0x1; ON_2=0x1;

        packet.p_my.len = LEN;
        packet.p_my.byte1 = IPK;  /* IPK=1 ???*/
        packet.p_my.byte2 = (SRC&0x1F)|((DST&0x7)<<5);
        packet.p_my.byte3 = ((DST>>3)&0x3)|(IPS<<2);
        packet.p_my.byte4 = ADR_UP7;
        packet.p_my.byte5 = IPK_UP7;
      //  packet.p_my.byte6 = 0x5; /* ���������� ���� � ������*/
      //  packet.p_my.byte7 = 0x2;
       packet.p_my.byte6 = N1_O[0]|N1_O[1]<<1|N1_O[2]<<2|N1_O[3]<<3|N2_O[0]<<4|N2_O[1]<<5|N2_O[2]<<6|N2_O[3]<<7;
       packet.p_my.byte7 = IN_1_AT[0]|IN_1_AT[1]<<1|IN_1_AT[2]<<2|IN_1_AT[3]<<3|IN_1_AT[4]<<4|ON_1<<5;
       packet.p_my.byte8 = IN_2_AT[0]|IN_2_AT[1]<<1|IN_2_AT[2]<<2|IN_2_AT[3]<<3|IN_2_AT[4]<<4|ON_2<<5;

     if( UPS_SEND_KIO_PACKET (1,packet.buf)  ==  true){return(0);}
         else{//ShowMessage("������ �������� ������ 2!");
             return(1);}

}
//============/* ��������� ������ ������ ������� �� ��� 1-��� � 2-��� ������ */========================================
//============/* ������� ���� ������� ��� ��� 1-��� � 2-��� ������ */==========================
int TForm1::Vkl_nk_att(int n_post,unsigned n_vh1,unsigned n_vh2,unsigned in1_at,unsigned in2_at,unsigned nk_svch)   /*0-- ��� ������, 1-- ���� ������ */
{
 int i,jk,ret;

 unsigned LEN,IPK=0xFF;
 unsigned DST=0x7,SRC=0x0,IPS=0x21; //IPS=100001 (0x21)
 unsigned ADR_UP7; /*����� ��7  2-���2 (���), 3 -- ���2 (���) */
 unsigned IPK_UP7=0x2; /* ������������� ������ ��7=2: ���������� ������� ������ �� ���� ������� ��� */

 unsigned N1_O[4]={0};/* ����� ������ ������� �� ��� 1-��� ������ */
 unsigned N2_O[4]={0};/* ����� ������ ������� �� ��� 2-��� ������ */
 unsigned ON_1,ON_2;  /* ��������� max(ON1=ON2=0) ��������� �� ������ IN1_AT, IN2_AT */
 unsigned IN_1_AT[5]={0};  /* ��������� 1-��� �������� ��� */
 unsigned IN_2_AT[5]={0};  /* ��������� 2-��� �������� ��� */
  // char buf1[256]={0};

 // u32 buf_my[256/4]; // ����� ��� ��������� ������
  // int nplis;      // ����� ����
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
                        byte8   : 8;

              } p_my;
             U32 buf[256/4];
             }  packet;
         LEN=0x9; /*9*/
         IPK=0xFF;
//         ADR_UP7=CB2_ps->3-ItemIndex;   /* 1--0: 2(���), 3(���)*/
          ADR_UP7=n_post; /* ����� ����� */

//       for(i=0;i<=12;i++)
//         {
//          US[i]=0x0;
//         }
//        US[nu]=0x1; /* nu-- ����� ���������*/

      // �������� �������� ������ � ��7

        N1_O[0]=n_vh1&0x1;
        N1_O[1]=(n_vh1>>1)&0x1;
        N1_O[2]=(n_vh1>>2)&0x1;
        N1_O[3]=(n_vh1>>3)&0x1;

        N2_O[0]=n_vh2&0x1;
        N2_O[1]=(n_vh2>>1)&0x1;
        N2_O[2]=(n_vh2>>2)&0x1;
        N2_O[3]=(n_vh2>>3)&0x1;

        IN_1_AT[0]=in1_at&0x1;
        IN_1_AT[1]=(in1_at>>1)&0x1;
        IN_1_AT[2]=(in1_at>>2)&0x1;
        IN_1_AT[3]=(in1_at>>3)&0x1;
        IN_1_AT[4]=(in1_at>>4)&0x1;

        IN_2_AT[0]=in2_at&0x1;
        IN_2_AT[1]=(in2_at>>1)&0x1;
        IN_2_AT[2]=(in2_at>>2)&0x1;
        IN_2_AT[3]=(in2_at>>3)&0x1;
        IN_2_AT[4]=(in2_at>>4)&0x1;

      //  if(nk_svch==1) ON_1=0x0;
      //  if(nk_svch==2) ON_2=0x0; /* �� ������������ ��������� */

         ON_1=0x1; ON_2=0x1;

        packet.p_my.len = LEN;
        packet.p_my.byte1 = IPK;  /* IPK=1 ???*/
        packet.p_my.byte2 = (SRC&0x1F)|((DST&0x7)<<5);
        packet.p_my.byte3 = ((DST>>3)&0x3)|(IPS<<2);
        packet.p_my.byte4 = ADR_UP7;
        packet.p_my.byte5 = IPK_UP7;
      //  packet.p_my.byte6 = 0x5; /* ���������� ���� � ������*/
      //  packet.p_my.byte7 = 0x2;
       packet.p_my.byte6 = N1_O[0]|N1_O[1]<<1|N1_O[2]<<2|N1_O[3]<<3|N2_O[0]<<4|N2_O[1]<<5|N2_O[2]<<6|N2_O[3]<<7;
       packet.p_my.byte7 = IN_1_AT[0]|IN_1_AT[1]<<1|IN_1_AT[2]<<2|IN_1_AT[3]<<3|IN_1_AT[4]<<4|ON_1<<5;
       packet.p_my.byte8 = IN_2_AT[0]|IN_2_AT[1]<<1|IN_2_AT[2]<<2|IN_2_AT[3]<<3|IN_2_AT[4]<<4|ON_2<<5;

       if( UPS_SEND_KIO_PACKET (1,packet.buf)  ==  true){return(0);}
         else{//ShowMessage("������ �������� ������ 2!");
          return(1);}
}
//============/* ��������� ������ ������ ������� �� ��� 1-��� � 2-��� ������  � ������� */========================================
//============/* ������� ���� ������� ��� ��� 1-��� � 2-��� ������ */==========================
int TForm1::Vkl_nk_att_t(int n_post,unsigned n_vh1,unsigned n_vh2,unsigned in1_at,unsigned in2_at,unsigned nk_svch)   /*0-- ��� ������, 1-- ���� ������ */
{
 int i,jk,ret;

 unsigned LEN,IPK=0xFF;
 unsigned DST=0x7,SRC=0x0,IPS=0x21; //IPS=100001 (0x21)
 unsigned ADR_UP7; /*����� ��7  2-���2 (���), 3 -- ���2 (���) */
 unsigned IPK_UP7=0x2; /* ������������� ������ ��7=2: ���������� ������� ������ �� ���� ������� ��� */

 unsigned N1_O[4]={0};/* ����� ������ ������� �� ��� 1-��� ������ */
 unsigned N2_O[4]={0};/* ����� ������ ������� �� ��� 2-��� ������ */
 unsigned ON_1,ON_2;  /* ��������� max(ON1=ON2=0) ��������� �� ������ IN1_AT, IN2_AT */
 unsigned IN_1_AT[5]={0};  /* ��������� 1-��� �������� ��� */
 unsigned IN_2_AT[5]={0};  /* ��������� 2-��� �������� ��� */
  // char buf1[256]={0};
//static int iii = 0;
 // u32 buf_my[256/4]; // ����� ��� ��������� ������
  // int nplis;      // ����� ����
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
                        byte8   : 8;

              } p_my;
             U32 buf[256/4];
             }  packet_at;

         LEN=0x9; /*9*/
         IPK=0xFF;

         ADR_UP7=n_post; /* ����� ����� */

      // �������� �������� ������ � ��7

        N1_O[0]=n_vh1&0x1;
        N1_O[1]=(n_vh1>>1)&0x1;
        N1_O[2]=(n_vh1>>2)&0x1;
        N1_O[3]=(n_vh1>>3)&0x1;

        N2_O[0]=n_vh2&0x1;
        N2_O[1]=(n_vh2>>1)&0x1;
        N2_O[2]=(n_vh2>>2)&0x1;
        N2_O[3]=(n_vh2>>3)&0x1;

        IN_1_AT[0]=in1_at&0x1;
        IN_1_AT[1]=(in1_at>>1)&0x1;
        IN_1_AT[2]=(in1_at>>2)&0x1;
        IN_1_AT[3]=(in1_at>>3)&0x1;
        IN_1_AT[4]=(in1_at>>4)&0x1;

        IN_2_AT[0]=in2_at&0x1;
        IN_2_AT[1]=(in2_at>>1)&0x1;
        IN_2_AT[2]=(in2_at>>2)&0x1;
        IN_2_AT[3]=(in2_at>>3)&0x1;
        IN_2_AT[4]=(in2_at>>4)&0x1;

        if(nk_svch==1) {ON_1=0x1; ON_2=0x0;}
        if(nk_svch==2) {ON_1=0x0; ON_2=0x1;}

       //  ON_1=0x1; ON_2=0x1;

        packet_at.p_my.len = LEN;
        packet_at.p_my.byte1 = IPK;  /* IPK=1 ???*/
        packet_at.p_my.byte2 = (SRC&0x1F)|((DST&0x7)<<5);
        packet_at.p_my.byte3 = ((DST>>3)&0x3)|(IPS<<2);
        packet_at.p_my.byte4 = ADR_UP7;
        packet_at.p_my.byte5 = IPK_UP7;
      //  packet.p_my.byte6 = 0x5; /* ���������� ���� � ������*/
      //  packet.p_my.byte7 = 0x2;
       packet_at.p_my.byte6 = N1_O[0]|N1_O[1]<<1|N1_O[2]<<2|N1_O[3]<<3|N2_O[0]<<4|N2_O[1]<<5|N2_O[2]<<6|N2_O[3]<<7;
       packet_at.p_my.byte7 = IN_1_AT[0]|IN_1_AT[1]<<1|IN_1_AT[2]<<2|IN_1_AT[3]<<3|IN_1_AT[4]<<4|ON_1<<5;
       packet_at.p_my.byte8 = IN_2_AT[0]|IN_2_AT[1]<<1|IN_2_AT[2]<<2|IN_2_AT[3]<<3|IN_2_AT[4]<<4|ON_2<<5;

      // if( UPS_SEND_KIO_PACKET (1,packet.buf)  ==  true){return(0);}
      //   else{//ShowMessage("������ �������� ������ 2!");
      //       return(1);}
          jk=0;
m1:
//try{
 Sleep(10);
    if(UPS_SEND_KIO_PACKET (1,packet_at.buf) == true){;}
         else{
             //ShowMessage("������ �������� ������ 3!");
            //return(1);   ������ �� ������
            }
//}
//  catch(...){
//    iii++;
//  }
   /* ����� ��������� ������ */
    ret=otvet_paket();

   if(ret==1)
   {
    jk=jk+1; if(jk<=9) goto m1; else
     {
    // ShowMessage("������ ��� �������� ������ 2 ERR=1");
       return 1;
     }
   }
  if(ret==2){
             //ShowMessage("��� �������� ������� �� ����� 2!");
             return 2;
             }
  if(ret==0) return 0;
   return 0;
 }
//============/* ���������� ������� �� ��� 1-��� � 2-��� ������ � ������� */========================================
//============/*  ��� ������� ��� ��� 1-��� � 2-��� ������ =0x1F*/==========================
int TForm1::Vykl_nk_att_t(int n_post,unsigned n_vh1,unsigned n_vh2,unsigned in1_at,unsigned in2_at,unsigned nk_svch)   /*0-- ��� ������, 1-- ���� ������ */
{
 int i,jk,ret;

 unsigned LEN,IPK=0xFF;
 unsigned DST=0x7,SRC=0x0,IPS=0x21; //IPS=100001 (0x21)
 unsigned ADR_UP7; /*����� ��7  2-���2 (���), 3 -- ���2 (���) */
 unsigned IPK_UP7=0x2; /* ������������� ������ ��7=2: ���������� ������� ������ �� ���� ������� ��� */

 unsigned N1_O[4]={0};/* ����� ������ ������� �� ��� 1-��� ������ */
 unsigned N2_O[4]={0};/* ����� ������ ������� �� ��� 2-��� ������ */
 unsigned ON_1,ON_2;  /* ��������� max(ON1=ON2=0) ��������� �� ������ IN1_AT, IN2_AT */
 unsigned IN_1_AT[5]={0};  /* ��������� 1-��� �������� ��� */
 unsigned IN_2_AT[5]={0};  /* ��������� 2-��� �������� ��� */
  // char buf1[256]={0};

 // u32 buf_my[256/4]; // ����� ��� ��������� ������
  // int nplis;      // ����� ����
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
                        byte8   : 8;

              } p_my;
             U32 buf[256/4];
             }  packet;
         LEN=0x9; /*9*/
         IPK=0xFF;
         ADR_UP7=n_post; /* ����� ����� */

      // �������� �������� ������ � ��7

        N1_O[0]=n_vh1&0x1;
        N1_O[1]=(n_vh1>>1)&0x1;
        N1_O[2]=(n_vh1>>2)&0x1;
        N1_O[3]=(n_vh1>>3)&0x1;

        N2_O[0]=n_vh2&0x1;
        N2_O[1]=(n_vh2>>1)&0x1;
        N2_O[2]=(n_vh2>>2)&0x1;
        N2_O[3]=(n_vh2>>3)&0x1;

        IN_1_AT[0]=in1_at&0x1;
        IN_1_AT[1]=(in1_at>>1)&0x1;
        IN_1_AT[2]=(in1_at>>2)&0x1;
        IN_1_AT[3]=(in1_at>>3)&0x1;
        IN_1_AT[4]=(in1_at>>4)&0x1;

        IN_2_AT[0]=in2_at&0x1;
        IN_2_AT[1]=(in2_at>>1)&0x1;
        IN_2_AT[2]=(in2_at>>2)&0x1;
        IN_2_AT[3]=(in2_at>>3)&0x1;
        IN_2_AT[4]=(in2_at>>4)&0x1;

      //  if(nk_svch==1) ON_1=0x0;
      //  if(nk_svch==2) ON_2=0x0; /* �� ������������ ��������� */

         ON_1=0x0; ON_2=0x0;

        packet.p_my.len = LEN;
        packet.p_my.byte1 = IPK;  /* IPK=1 ???*/
        packet.p_my.byte2 = (SRC&0x1F)|((DST&0x7)<<5);
        packet.p_my.byte3 = ((DST>>3)&0x3)|(IPS<<2);
        packet.p_my.byte4 = ADR_UP7;
        packet.p_my.byte5 = IPK_UP7;
      //  packet.p_my.byte6 = 0x5; /* ���������� ���� � ������*/
      //  packet.p_my.byte7 = 0x2;
       packet.p_my.byte6 = N1_O[0]|N1_O[1]<<1|N1_O[2]<<2|N1_O[3]<<3|N2_O[0]<<4|N2_O[1]<<5|N2_O[2]<<6|N2_O[3]<<7;
       packet.p_my.byte7 = IN_1_AT[0]|IN_1_AT[1]<<1|IN_1_AT[2]<<2|IN_1_AT[3]<<3|IN_1_AT[4]<<4|ON_1<<5;
       packet.p_my.byte8 = IN_2_AT[0]|IN_2_AT[1]<<1|IN_2_AT[2]<<2|IN_2_AT[3]<<3|IN_2_AT[4]<<4|ON_2<<5;

//       if( UPS_SEND_KIO_PACKET (1,packet.buf)  ==  true){return(0);}
//         else{//ShowMessage("������ �������� ������ 2!");
//             return(1);}
      jk=0;
m1:  if(UPS_SEND_KIO_PACKET (1,packet.buf) == true){;}
         else{
             //ShowMessage("������ �������� ������ 3!");
            //return(1);   ������ �� ������
            }
   /* ����� ��������� ������ */
    ret=otvet_paket();

   if(ret==1)
   {
    jk=jk+1; if(jk<=9) goto m1; else
     {
    // ShowMessage("������ ��� �������� ������ 3 ERR=1");
       return 1;
     }
   }
  if(ret==2){
             //ShowMessage("��� �������� ������� �� ����� 3!");
             return 2;
             }
  if(ret==0) return 0;
    return 0;

}
//============/* ������� ���� �������� ��� */==== ���� �� ����� ������� ======================
int TForm1::Vkl_att(int n_post,unsigned *kod_att)   /*0-- ��� ������, 1-- ���� ������ */
{int i,jk,ret;

 unsigned LEN,IPK=0xFF;
 unsigned DST=0x7,SRC=0x0,IPS=0x21; //IPS=100001 (0x21)
 unsigned ADR_UP7; /*����� ��7  2-���2 (���), 3 -- ���2 (���) */
 unsigned IPK_UP7=0x3; /* ������������� ������ ��7=1: ���������� ������� ������ �� ���� ������� ��� */

 unsigned AT1[4]={0};
 unsigned AT2[4]={0};
 unsigned AT3[4]={0};
 unsigned AT4[4]={0};
 unsigned AT5[4]={0};
 unsigned AT6[4]={0};
 unsigned AT7[4]={0};
 unsigned AT8[4]={0};
 unsigned AT9[4]={0};
 unsigned AT10[4]={0};
 unsigned AT11[4]={0};
 unsigned AT12[4]={0};

 unsigned AT13[4]={0};
  // char buf1[256]={0};

 // u32 buf_my[256/4]; // ����� ��� ��������� ������
  // int nplis;      // ����� ����
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
         LEN=0xD; /*13 ���� � ������ (6+7)*/
         IPK=0xFF;
//         ADR_UP7=CB2_ps->3-ItemIndex;   /* 1--0: 2(���), 3(���)*/
          ADR_UP7=n_post; /* ����� ����� */

//       for(i=0;i<=12;i++)
//         {
//          US[i]=0x0;
//         }
//        US[nu]=0x1; /* nu-- ����� ���������*/

      // �������� �������� ������ � ��7

        AT1[0]=kod_att[0]&0x1;
        AT1[1]=(kod_att[0]>>1)&0x1;
        AT1[2]=(kod_att[0]>>2)&0x1;
        AT1[3]=(kod_att[0]>>3)&0x1;

        AT2[0]=kod_att[1]&0x1;
        AT2[1]=(kod_att[1]>>1)&0x1;
        AT2[2]=(kod_att[1]>>2)&0x1;
        AT2[3]=(kod_att[1]>>3)&0x1;

        AT3[0]=kod_att[2]&0x1;
        AT3[1]=(kod_att[2]>>1)&0x1;
        AT3[2]=(kod_att[2]>>2)&0x1;
        AT3[3]=(kod_att[2]>>3)&0x1;

        AT4[0]=kod_att[3]&0x1;
        AT4[1]=(kod_att[3]>>1)&0x1;
        AT4[2]=(kod_att[3]>>2)&0x1;
        AT4[3]=(kod_att[3]>>3)&0x1;

        AT5[0]=kod_att[4]&0x1;
        AT5[1]=(kod_att[4]>>1)&0x1;
        AT5[2]=(kod_att[4]>>2)&0x1;
        AT5[3]=(kod_att[4]>>3)&0x1;

        AT6[0]=kod_att[5]&0x1;
        AT6[1]=(kod_att[5]>>1)&0x1;
        AT6[2]=(kod_att[5]>>2)&0x1;
        AT6[3]=(kod_att[5]>>3)&0x1;

        AT7[0]=kod_att[6]&0x1;
        AT7[1]=(kod_att[6]>>1)&0x1;
        AT7[2]=(kod_att[6]>>2)&0x1;
        AT7[3]=(kod_att[6]>>3)&0x1;

        AT8[0]=kod_att[7]&0x1;
        AT8[1]=(kod_att[7]>>1)&0x1;
        AT8[2]=(kod_att[7]>>2)&0x1;
        AT8[3]=(kod_att[7]>>3)&0x1;

        AT9[0]=kod_att[8]&0x1;
        AT9[1]=(kod_att[8]>>1)&0x1;
        AT9[2]=(kod_att[8]>>2)&0x1;
        AT9[3]=(kod_att[8]>>3)&0x1;

        AT10[0]=kod_att[9]&0x1;
        AT10[1]=(kod_att[9]>>1)&0x1;
        AT10[2]=(kod_att[9]>>2)&0x1;
        AT10[3]=(kod_att[9]>>3)&0x1;

        AT11[0]=kod_att[10]&0x1;
        AT11[1]=(kod_att[10]>>1)&0x1;
        AT11[2]=(kod_att[10]>>2)&0x1;
        AT11[3]=(kod_att[10]>>3)&0x1;

        AT12[0]=kod_att[11]&0x1;
        AT12[1]=(kod_att[11]>>1)&0x1;
        AT12[2]=(kod_att[11]>>2)&0x1;
        AT12[3]=(kod_att[11]>>3)&0x1;

        if((ADR_UP7==2)||(ADR_UP7==3))
         {
          AT13[0]=kod_att[12]&0x1;
          AT13[1]=(kod_att[12]>>1)&0x1;
          AT13[2]=(kod_att[12]>>2)&0x1;
          AT13[3]=(kod_att[12]>>3)&0x1;
         }

        packet.p_my.len = LEN;
        packet.p_my.byte1 = IPK;  /* IPK=0xFF*/
        packet.p_my.byte2 = (SRC&0x1F)|((DST&0x7)<<5);
        packet.p_my.byte3 = ((DST>>3)&0x3)|(IPS<<2);
        packet.p_my.byte4 = ADR_UP7;
        packet.p_my.byte5 = IPK_UP7;
       // packet.p_my.byte6 = 0x9; /* ���������� ���� � ������*/
       // packet.p_my.byte7 = 0x3;
    packet.p_my.byte6 = AT1[0]|AT1[1]<<1|AT1[2]<<2|AT1[3]<<3|AT2[0]<<4|AT2[1]<<5|AT2[2]<<6|AT2[3]<<7;
    packet.p_my.byte7 = AT3[0]|AT3[1]<<1|AT3[2]<<2|AT3[3]<<3|AT4[0]<<4|AT4[1]<<5|AT4[2]<<6|AT4[3]<<7;
    packet.p_my.byte8 = AT5[0]|AT5[1]<<1|AT5[2]<<2|AT5[3]<<3|AT6[0]<<4|AT6[1]<<5|AT6[2]<<6|AT6[3]<<7;
    packet.p_my.byte9 = AT7[0]|AT7[1]<<1|AT7[2]<<2|AT7[3]<<3|AT8[0]<<4|AT8[1]<<5|AT8[2]<<6|AT8[3]<<7;
    packet.p_my.byte10 = AT9[0]|AT9[1]<<1|AT9[2]<<2|AT9[3]<<3|AT10[0]<<4|AT10[1]<<5|AT10[2]<<6|AT10[3]<<7;
    packet.p_my.byte11 = AT11[0]|AT11[1]<<1|AT11[2]<<2|AT11[3]<<3|AT12[0]<<4|AT12[1]<<5|AT12[2]<<6|AT12[3]<<7;
    packet.p_my.byte12 = AT13[0]|AT13[1]<<1|AT13[2]<<2|AT13[3]<<3;

       if( UPS_SEND_KIO_PACKET (1,packet.buf)  ==  true){return(0);}
         else{
             //ShowMessage("������ �������� ������ 3!");
             return(1);}
//  return 0;           
}
//============/* ������� ���� �������� ��� � ������� */==== ���� �� ����� ������� ======================
int TForm1::Vkl_att_t(int n_post,unsigned *kod_att)   /*0-- ��� ������, 1-- ���� ������ */
{
 int i,jk,ret;

 unsigned LEN,IPK=0xFF;
 unsigned DST=0x7,SRC=0x0,IPS=0x21; //IPS=100001 (0x21)
 unsigned ADR_UP7; /*����� ��7  2-���2 (���), 3 -- ���2 (���) */
 unsigned IPK_UP7=0x3; /* ������������� ������ ��7=1: ���������� ������� ������ �� ���� ������� ��� */

 unsigned AT1[4]={0};
 unsigned AT2[4]={0};
 unsigned AT3[4]={0};
 unsigned AT4[4]={0};
 unsigned AT5[4]={0};
 unsigned AT6[4]={0};
 unsigned AT7[4]={0};
 unsigned AT8[4]={0};
 unsigned AT9[4]={0};
 unsigned AT10[4]={0};
 unsigned AT11[4]={0};
 unsigned AT12[4]={0};

 unsigned AT13[4]={0};
  // char buf1[256]={0};

 // u32 buf_my[256/4]; // ����� ��� ��������� ������
  // int nplis;      // ����� ����
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
         LEN=0xD; /*13 ���� � ������ (6+7)*/
         IPK=0xFF;
//         ADR_UP7=CB2_ps->3-ItemIndex;   /* 1--0: 2(���), 3(���)*/
          ADR_UP7=n_post; /* ����� ����� */

//       for(i=0;i<=12;i++)
//         {
//          US[i]=0x0;
//         }
//        US[nu]=0x1; /* nu-- ����� ���������*/

      // �������� �������� ������ � ��7

        AT1[0]=kod_att[0]&0x1;
        AT1[1]=(kod_att[0]>>1)&0x1;
        AT1[2]=(kod_att[0]>>2)&0x1;
        AT1[3]=(kod_att[0]>>3)&0x1;

        AT2[0]=kod_att[1]&0x1;
        AT2[1]=(kod_att[1]>>1)&0x1;
        AT2[2]=(kod_att[1]>>2)&0x1;
        AT2[3]=(kod_att[1]>>3)&0x1;

        AT3[0]=kod_att[2]&0x1;
        AT3[1]=(kod_att[2]>>1)&0x1;
        AT3[2]=(kod_att[2]>>2)&0x1;
        AT3[3]=(kod_att[2]>>3)&0x1;

        AT4[0]=kod_att[3]&0x1;
        AT4[1]=(kod_att[3]>>1)&0x1;
        AT4[2]=(kod_att[3]>>2)&0x1;
        AT4[3]=(kod_att[3]>>3)&0x1;

        AT5[0]=kod_att[4]&0x1;
        AT5[1]=(kod_att[4]>>1)&0x1;
        AT5[2]=(kod_att[4]>>2)&0x1;
        AT5[3]=(kod_att[4]>>3)&0x1;

        AT6[0]=kod_att[5]&0x1;
        AT6[1]=(kod_att[5]>>1)&0x1;
        AT6[2]=(kod_att[5]>>2)&0x1;
        AT6[3]=(kod_att[5]>>3)&0x1;

        AT7[0]=kod_att[6]&0x1;
        AT7[1]=(kod_att[6]>>1)&0x1;
        AT7[2]=(kod_att[6]>>2)&0x1;
        AT7[3]=(kod_att[6]>>3)&0x1;

        AT8[0]=kod_att[7]&0x1;
        AT8[1]=(kod_att[7]>>1)&0x1;
        AT8[2]=(kod_att[7]>>2)&0x1;
        AT8[3]=(kod_att[7]>>3)&0x1;

        AT9[0]=kod_att[8]&0x1;
        AT9[1]=(kod_att[8]>>1)&0x1;
        AT9[2]=(kod_att[8]>>2)&0x1;
        AT9[3]=(kod_att[8]>>3)&0x1;

        AT10[0]=kod_att[9]&0x1;
        AT10[1]=(kod_att[9]>>1)&0x1;
        AT10[2]=(kod_att[9]>>2)&0x1;
        AT10[3]=(kod_att[9]>>3)&0x1;

        AT11[0]=kod_att[10]&0x1;
        AT11[1]=(kod_att[10]>>1)&0x1;
        AT11[2]=(kod_att[10]>>2)&0x1;
        AT11[3]=(kod_att[10]>>3)&0x1;

        AT12[0]=kod_att[11]&0x1;
        AT12[1]=(kod_att[11]>>1)&0x1;
        AT12[2]=(kod_att[11]>>2)&0x1;
        AT12[3]=(kod_att[11]>>3)&0x1;

        if((ADR_UP7==2)||(ADR_UP7==3))
         {
          AT13[0]=kod_att[12]&0x1;
          AT13[1]=(kod_att[12]>>1)&0x1;
          AT13[2]=(kod_att[12]>>2)&0x1;
          AT13[3]=(kod_att[12]>>3)&0x1;
         }

        packet.p_my.len = LEN;
        packet.p_my.byte1 = IPK;  /* IPK=0xFF*/
        packet.p_my.byte2 = (SRC&0x1F)|((DST&0x7)<<5);
        packet.p_my.byte3 = ((DST>>3)&0x3)|(IPS<<2);
        packet.p_my.byte4 = ADR_UP7;
        packet.p_my.byte5 = IPK_UP7;
       // packet.p_my.byte6 = 0x9; /* ���������� ���� � ������*/
       // packet.p_my.byte7 = 0x3;
    packet.p_my.byte6 = AT1[0]|AT1[1]<<1|AT1[2]<<2|AT1[3]<<3|AT2[0]<<4|AT2[1]<<5|AT2[2]<<6|AT2[3]<<7;
    packet.p_my.byte7 = AT3[0]|AT3[1]<<1|AT3[2]<<2|AT3[3]<<3|AT4[0]<<4|AT4[1]<<5|AT4[2]<<6|AT4[3]<<7;
    packet.p_my.byte8 = AT5[0]|AT5[1]<<1|AT5[2]<<2|AT5[3]<<3|AT6[0]<<4|AT6[1]<<5|AT6[2]<<6|AT6[3]<<7;
    packet.p_my.byte9 = AT7[0]|AT7[1]<<1|AT7[2]<<2|AT7[3]<<3|AT8[0]<<4|AT8[1]<<5|AT8[2]<<6|AT8[3]<<7;
    packet.p_my.byte10 = AT9[0]|AT9[1]<<1|AT9[2]<<2|AT9[3]<<3|AT10[0]<<4|AT10[1]<<5|AT10[2]<<6|AT10[3]<<7;
    packet.p_my.byte11 = AT11[0]|AT11[1]<<1|AT11[2]<<2|AT11[3]<<3|AT12[0]<<4|AT12[1]<<5|AT12[2]<<6|AT12[3]<<7;
    packet.p_my.byte12 = AT13[0]|AT13[1]<<1|AT13[2]<<2|AT13[3]<<3;

    jk=0;
m1:  if(UPS_SEND_KIO_PACKET (1,packet.buf) == true){;}
         else{
             //ShowMessage("������ �������� ������ 3!");
            //return(1);   ������ �� ������
            }
   /* ����� ��������� ������ */
    ret=otvet_paket();

   if(ret==1)
   {
    jk=jk+1; if(jk<=9) goto m1; else
     {
    // ShowMessage("������ ��� �������� ������ 3 ERR=1");
       return 1;
     }
   }
  if(ret==2){
             //ShowMessage("��� �������� ������� �� ����� 3!");
             return 2;
             }
  if(ret==0) return 0;
  return 0;
}
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
 //============/* ��������� ������ ���������, ��������� ��������� ������� ��7 � ������� */========================================
int TForm1::Vkl_us_vip_t(int n_post,int nu)   /*0-- ��� ������, 1-- ���� ������ */
{
 int nk,i,jk,ret;  /* ����� ���*/
// AnsiString vip3_0,vip3_1,vip2_0,vip2_1,vip_uppu;
// AnsiString kio3_0,kio3_1,kio2_0,kio2_1;
 unsigned LEN,IPK=0xFF;
 unsigned DST=0x7,SRC=0x0,IPS=0x21; //IPS=100001 (0x21)
 unsigned ADR_UP7; /*����� ��7  2-���2 (���), 3 -- ���2 (���) */
 unsigned IPK_UP7=0x1; /* ������������� ������ ��7=1: ��������� ������ � ���. ���.*/
 //unsigned EUS_1,EUS2,EUS3,EUS4,EUS5,EUS6,EUS7,EUS8,EUS9,EUS10,
 //EUS11,EUS12,EUS13;    /* ��������� ������ ���������*/
 unsigned US[13];
 unsigned ON_VIP=0x1;  /* ��������� ��������� ������� */
 unsigned EPRD=0x1;  /* ���������� ��������� */
 unsigned EPRM=0x0;  /*  ���������� ������ */
  // char buf1[256]={0};

  u32 buf_my[256/4]; // ����� ��� ��������� ������
  // int nplis;      // ����� ����
 union{
       struct{
                  U32 	len     : 8,
			byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8,
                        byte5   : 8,
                        byte6   : 8,
                        byte7   : 8;

              } p_my;
             U32 buf[256/4];
             }  packet;
         LEN=0x8; /*8*/
         IPK=0xFF;  /* �������� ���������� ������*/
//         ADR_UP7=CB2_ps->3-ItemIndex;   /* 1--0: 2(���), 3(���)*/
          ADR_UP7=n_post; /* ����� ����� */
     for(i=0;i<=12;i++)
         {
          US[i]=0x0;
         }

       if(nu==0xD)
         {
           for(i=0;i<=12;i++)  /* ��� 13 ���������� */
           {
            US[i]=0x1;
           }
           US[12]=0x0;
          }
       else
         US[nu]=0x1; /* nu-- ����� ���������: ����� ��������� ��������� */
      // �������� �������� ������ � ��7

        packet.p_my.len = LEN;
        packet.p_my.byte1 = IPK;  /* IPK=0xFF*/
        packet.p_my.byte2 = (SRC&0x1F)|((DST<<5))&0x7;
        packet.p_my.byte3 = (DST&0x3)|(IPS<<2);
        packet.p_my.byte4 = ADR_UP7;
        packet.p_my.byte5 = IPK_UP7;
       // packet.p_my.byte6 = 0x4; /* ���������� ���� � ������*/
       // packet.p_my.byte6 = 0x1;
       packet.p_my.byte6 = US[0]|US[1]<<1|US[2]<<2|US[3]<<3|US[4]<<4|US[5]<<5|US[6]<<6|US[7]<<7;
       packet.p_my.byte7 = US[8]|US[9]<<1|US[10]<<2|US[11]<<3|US[12]<<4|ON_VIP<<5|EPRD<<6|EPRM<<7;

//       if( UPS_SEND_KIO_PACKET (1,packet.buf)  ==  true){return(0);}
//         else{
//         //ShowMessage("������ �������� ������!");
//         return(1);}
        jk=0;
m1:  if(UPS_SEND_KIO_PACKET (1,packet.buf) == true){;}
         else{
             //ShowMessage("������ �������� ������ 3!");
            //return(1);   ������ �� ������
            }
   /* ����� ��������� ������ */
    ret=otvet_paket();

   if(ret==1)
   {
    jk=jk+1; if(jk<=9) goto m1; else
     {
    // ShowMessage("������ ��� �������� ������ 3 ERR=1");
       return 1;
     }
   }
  if(ret==2){
             //ShowMessage("��� �������� ������� �� ����� 3!");
             return 2;
             }
  if(ret==0) return 0;

  return 0;
}
 //============/* ��������� ������ ���������, ��������� ��������� ������� ��7 */========================================
int TForm1::Vkl_us_vip(int n_post,int nu)   /*0-- ��� ������, 1-- ���� ������ */
{
 int nk,i,jk,ret;  /* ����� ���*/
// AnsiString vip3_0,vip3_1,vip2_0,vip2_1,vip_uppu;
// AnsiString kio3_0,kio3_1,kio2_0,kio2_1;
 unsigned LEN,IPK=0xFF;
 unsigned DST=0x7,SRC=0x0,IPS=0x21; //IPS=100001 (0x21)
 unsigned ADR_UP7; /*����� ��7  2-���2 (���), 3 -- ���2 (���) */
 unsigned IPK_UP7=0x1; /* ������������� ������ ��7=1: ��������� ������ � ���. ���.*/
 //unsigned EUS_1,EUS2,EUS3,EUS4,EUS5,EUS6,EUS7,EUS8,EUS9,EUS10,
 //EUS11,EUS12,EUS13;    /* ��������� ������ ���������*/
 unsigned US[13];
 unsigned ON_VIP=0x1;  /* ��������� ��������� ������� */
 unsigned EPRD=0x1;  /* ���������� ��������� */
 unsigned EPRM=0x0;  /*  ���������� ������ */
  // char buf1[256]={0};

  u32 buf_my[256/4]; // ����� ��� ��������� ������
  // int nplis;      // ����� ����
 union{
       struct{
                  U32 	len     : 8,
			byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8,
                        byte5   : 8,
                        byte6   : 8,
                        byte7   : 8;

              } p_my;
             U32 buf[256/4];
             }  packet;
         LEN=0x8; /*8*/
         IPK=0xFF;  /* �������� ���������� ������*/
//         ADR_UP7=CB2_ps->3-ItemIndex;   /* 1--0: 2(���), 3(���)*/
          ADR_UP7=n_post; /* ����� ����� */

        for(i=0;i<=12;i++)
         {
          US[i]=0x0;
         }
        US[nu]=0x1; /* nu-- ����� ���������: ����� ��������� ��������� */
      // �������� �������� ������ � ��7

        packet.p_my.len = LEN;
        packet.p_my.byte1 = IPK;  /* IPK=0xFF*/
        packet.p_my.byte2 = (SRC&0x1F)|((DST<<5))&0x7;
        packet.p_my.byte3 = (DST&0x3)|(IPS<<2);
        packet.p_my.byte4 = ADR_UP7;
        packet.p_my.byte5 = IPK_UP7;
       // packet.p_my.byte6 = 0x4; /* ���������� ���� � ������*/
       // packet.p_my.byte6 = 0x1;
       packet.p_my.byte6 = US[0]|US[1]<<1|US[2]<<2|US[3]<<3|US[4]<<4|US[5]<<5|US[6]<<6|US[7]<<7;
       packet.p_my.byte7 = US[8]|US[9]<<1|US[10]<<2|US[11]<<3|US[12]<<4|ON_VIP<<5|EPRD<<6|EPRM<<7;

       if( UPS_SEND_KIO_PACKET (1,packet.buf)  ==  true){return(0);}
         else{
         //ShowMessage("������ �������� ������!");
         return(1);}
//         return 0;

}
//============/* ���������� ������ ���������, ���������� ��������� ������� ��7 */========================================
int TForm1::Vykl_us_vip(int n_post)   /*0-- ��� ������, 1-- ���� ������ */
{
 int nk,i,jk,ret;  /* ����� ���*/
// AnsiString vip3_0,vip3_1,vip2_0,vip2_1,vip_uppu;
// AnsiString kio3_0,kio3_1,kio2_0,kio2_1;
 unsigned LEN,IPK=0xFF;
 unsigned DST=0x7,SRC=0x0,IPS=0x21; //IPS=100001 (0x21)
 unsigned ADR_UP7; /*����� ��7  2-���2 (���), 3 -- ���2 (���) */
 unsigned IPK_UP7=0x1; /* ������������� ������ ��7=1: ��������� ������ � ���. ���.*/
 //unsigned EUS_1,EUS2,EUS3,EUS4,EUS5,EUS6,EUS7,EUS8,EUS9,EUS10,
 //EUS11,EUS12,EUS13;    /* ���������� ������ ���������*/
 unsigned US[13];
 unsigned ON_VIP=0x0;  /* ���������� ��������� ������� */
 unsigned EPRD=0x1;  /* ���������� ��������� */
 unsigned EPRM=0x0;  /*  ���������� ������ */
  // char buf1[256]={0};

  u32 buf_my[256/4]; // ����� ��� ��������� ������
  // int nplis;      // ����� ����
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

              } p_my;
             U32 buf[256/4];
             }  packet;
         LEN=0x8; /*8*/
         IPK=0xFF;  /* �������� ���������� ������*/
//         ADR_UP7=CB2_ps->3-ItemIndex;   /* 1--0: 2(���), 3(���)*/
          ADR_UP7=n_post; /* ����� ����� */

        for(i=0;i<=12;i++)
         {
          US[i]=0x0;
         }
//     US[nu]=0x1; /* nu-- ����� ���������: ����� ��������� ��������� */
      // �������� �������� ������ � ��7

        packet.p_my.len = LEN;
        packet.p_my.byte1 = IPK;  /* IPK=0xFF*/
        packet.p_my.byte2 = (SRC&0x1F)|((DST<<5))&0x7;
        packet.p_my.byte3 = (DST&0x3)|(IPS<<2);
        packet.p_my.byte4 = ADR_UP7;
        packet.p_my.byte5 = IPK_UP7;
       // packet.p_my.byte6 = 0x4; /* ���������� ���� � ������*/
       // packet.p_my.byte6 = 0x1;
       packet.p_my.byte6 = US[0]|US[1]<<1|US[2]<<2|US[3]<<3|US[4]<<4|US[5]<<5|US[6]<<6|US[7]<<7;
       packet.p_my.byte7 = US[8]|US[9]<<1|US[10]<<2|US[11]<<3|US[12]<<4|ON_VIP<<5|EPRD<<6|EPRM<<7;

       if( UPS_SEND_KIO_PACKET (1,packet.buf)  ==  true){return(0);}
        else{
         //ShowMessage("������ �������� ������!");
         return(1);}
    //  return 0;
}
//============/* ���������� ������ ���������, ���������� ��������� ������� ��7 � ������� */========================================
int TForm1::Vykl_us_vip_t(int n_post)   /*0-- ��� ������, 1-- ���� ������ */
{
 int nk,i,jk,ret;  /* ����� ���*/
// AnsiString vip3_0,vip3_1,vip2_0,vip2_1,vip_uppu;
// AnsiString kio3_0,kio3_1,kio2_0,kio2_1;
 unsigned LEN,IPK=0xFF;
 unsigned DST=0x7,SRC=0x0,IPS=0x21; //IPS=100001 (0x21)
 unsigned ADR_UP7; /*����� ��7  2-���2 (���), 3 -- ���2 (���) */
 unsigned IPK_UP7=0x1; /* ������������� ������ ��7=1: ��������� ������ � ���. ���.*/
 //unsigned EUS_1,EUS2,EUS3,EUS4,EUS5,EUS6,EUS7,EUS8,EUS9,EUS10,
 //EUS11,EUS12,EUS13;    /* ���������� ������ ���������*/
 unsigned US[13];
 unsigned ON_VIP=0x0;  /* ���������� ��������� ������� */
 unsigned EPRD=0x1;  /* ���������� ��������� */
 unsigned EPRM=0x0;  /*  ���������� ������ */
  // char buf1[256]={0};

  u32 buf_my[256/4]; // ����� ��� ��������� ������
  // int nplis;      // ����� ����
 union{
       struct{
                  U32 	len     : 8,
			byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8,
                        byte5   : 8,
                        byte6   : 8,
                        byte7   : 8;

              } p_my;
             U32 buf[256/4];
             }  packet;
         LEN=0x8; /*8*/
         IPK=0xFF;  /* �������� ���������� ������*/
//         ADR_UP7=CB2_ps->3-ItemIndex;   /* 1--0: 2(���), 3(���)*/
          ADR_UP7=n_post; /* ����� ����� */

        for(i=0;i<=12;i++)
         {
          US[i]=0x0;
         }
//     US[nu]=0x1; /* nu-- ����� ���������: ����� ��������� ��������� */
      // �������� �������� ������ � ��7

        packet.p_my.len = LEN;
        packet.p_my.byte1 = IPK;  /* IPK=0xFF*/
        packet.p_my.byte2 = (SRC&0x1F)|((DST<<5))&0x7;
        packet.p_my.byte3 = (DST&0x3)|(IPS<<2);
        packet.p_my.byte4 = ADR_UP7;
        packet.p_my.byte5 = IPK_UP7;
       // packet.p_my.byte6 = 0x4; /* ���������� ���� � ������*/
       // packet.p_my.byte6 = 0x1;
       packet.p_my.byte6 = US[0]|US[1]<<1|US[2]<<2|US[3]<<3|US[4]<<4|US[5]<<5|US[6]<<6|US[7]<<7;
       packet.p_my.byte7 = US[8]|US[9]<<1|US[10]<<2|US[11]<<3|US[12]<<4|ON_VIP<<5|EPRD<<6|EPRM<<7;

//       if( UPS_SEND_KIO_PACKET (1,packet.buf)  ==  true){return(0);}
//         else{
//         //ShowMessage("������ �������� ������!");
//         return(1);}
    jk=0;
m1:  if(UPS_SEND_KIO_PACKET (1,packet.buf) == true){;}
         else{
             //ShowMessage("������ �������� ������ 3!");
            //return(1);   ������ �� ������
            }
   /* ����� ��������� ������ */
    ret=otvet_paket();

   if(ret==1)
   {
    jk=jk+1; if(jk<=9) goto m1; else
     {
    // ShowMessage("������ ��� �������� ������ 3 ERR=1");
       return 1;
     }
   }
  if(ret==2){
             //ShowMessage("��� �������� ������� �� ����� 3!");
             return 2;
             }
  if(ret==0) return 0;

  return 0;
}
//=================================================================
/* ������  ������� ����������� ��������� ������� */
void __fastcall TForm1::B_cht_2Click(TObject *Sender)
{

}
 //============/* ������ ��������� (����� 8) ����� =6 */========================================
int TForm1::zapr_dan_up7(int n_post, int nf)   /*0-- ��� ������, 1-- ���� ������ */
{
 int nk;  /* ����� ���*/
 unsigned LEN,IPK=0xFF;
 unsigned DST=0x7,SRC=0x0,IPS=0x23; //IPS=100001 (0x21)
 unsigned ADR_UP7; /*����� ��7  2-���2 (���), 3 -- ���2 (���) */
 unsigned IPK_UP7; /* ������������� ������ ��7:������ ��������� (���� 8, ���� 9)*/

  // char buf1[256]={0};

  u32 buf_my[256/4]; // ����� ��� ��������� ������
  // int nplis;      // ����� ����
 union{
       struct{
                  U32   len     : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8,
                        byte5   : 8;

              } p_my;
             U32 buf[256/4];
             }  packet;
         LEN=0x6;
         IPK=0xFF;  /* �������� ���������� ������*/
         ADR_UP7=n_post; /* ����� ����� */
         IPK_UP7=nf; /* ����� �������*/
     // �������� �������� ������ � ��7

        packet.p_my.len = LEN;
        packet.p_my.byte1 = IPK;  /* IPK=0xFF*/
        packet.p_my.byte2 = (SRC&0x1F)|((DST&0x7)<<5);
        packet.p_my.byte3 = ((DST>>3)&0x3)|(IPS<<2);
        packet.p_my.byte4 = ADR_UP7; /* n_post*/
        packet.p_my.byte5 = IPK_UP7; /*8, ���� 9 */

       if( UPS_SEND_KIO_PACKET (1,packet.buf)  ==  true){return(0);}
         else{
         //ShowMessage("������ �������� ������!");
         return(1);}
  //     return 0;
 }
//============/* ������ ��������� (����� 8) ����� =6 � ������� */========================================
int TForm1::zapr_dan_up7_t(int n_post, int nf)   /*0-- ��� ������, 1-- ���� ������ */
{
 int nk,jk,ret;  /* ����� ���*/
 unsigned LEN,IPK=0xFF;
 unsigned DST=0x7,SRC=0x0,IPS=0x23; //IPS=100001 (0x21)
 unsigned ADR_UP7; /*����� ��7  2-���2 (���), 3 -- ���2 (���) */
 unsigned IPK_UP7; /* ������������� ������ ��7:������ ��������� (���� 8, ���� 9)*/

  // char buf1[256]={0};

  u32 buf_my[256/4]; // ����� ��� ��������� ������
  // int nplis;      // ����� ����
 union{
       struct{
                  U32   len     : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8,
                        byte4   : 8,
                        byte5   : 8;

              } p_my;
             U32 buf[256/4];
             }  packet;
         LEN=0x6;
         IPK=0xFF;  /* �������� ���������� ������*/
         ADR_UP7=n_post; /* ����� ����� */
         IPK_UP7=nf; /* ����� �������*/
     // �������� �������� ������ � ��7

        packet.p_my.len = LEN;
        packet.p_my.byte1 = IPK;  /* IPK=0xFF*/
        packet.p_my.byte2 = (SRC&0x1F)|((DST&0x7)<<5);
        packet.p_my.byte3 = ((DST>>3)&0x3)|(IPS<<2);
        packet.p_my.byte4 = ADR_UP7; /* n_post*/
        packet.p_my.byte5 = IPK_UP7; /*8, ���� 9 */

//       if( UPS_SEND_KIO_PACKET (1,packet.buf)  ==  true){return(0);}
//         else{
//         //ShowMessage("������ �������� ������!");
//         return(1);}

             jk=0;
m1:  if(UPS_SEND_KIO_PACKET (1,packet.buf) == true){;}
         else{
             //ShowMessage("������ �������� ������ 3!");
            //return(1);   ������ �� ������
            }
   /* ����� ��������� ������ */
    ret=otvet_paket();
 if(ret==1)
   {
    jk=jk+1; if(jk<=9) goto m1; else
     {
    // ShowMessage("������ ��� �������� ������ 2 ERR=1");
       return 1;
     }
   }
 if(ret==2){
             //ShowMessage("��� �������� ������� �� ����� 2!");
             return 2;
             }
 if(ret==0) return 0;
  return 0;
}
//----------------������ ������ �������� ��� ������� ����������------------------------------
void __fastcall TForm1::Button22Click(TObject *Sender)
{

}
//-----------------------�������������� ����� -----------------------------
void __fastcall TForm1::B2_avtClick(TObject *Sender)
{
 if(ChkDevs==true)
 {
   Avt2OutChn();
  }
  else
  {
 if(FindDevises()==true)
  {
  if(ChekDev()==true)
  {
    Avt2OutChn();
   }
  }    //FindDevises()
 }//else
}
//-----------------------�������������� ����� -----------------------------
void TForm1::Avt2OutChn(void)
{
 extern bool vyh;
  ViStatus stat=0; // ���������� ���������� ���� ViStatus
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

  double P[35];       /*���������� �������� � ��*/
  double P_dB[35];    /*���������� �������� � ��*/

  double P_1=0;
  double dP;
  double p_vt_izm;
  double P_max;
  int j,k,k1;
 //int num=0;
 //char rdbuffer[256]={0};

 int ind; //������ ������� � �������� ����������
 long longdown=0; /* �������� �������� ����������*/

 int m_p;
 float x_m_p;
 double m_p_1;  /* ��������, ���������� �� ����������*/
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
   int nk,nu;  /* ����� ���*/
                                  /* ������� ��� */
  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 �������� 00000, 00001,00010,00100,01000,10000*/
/* float Qvh_osl[32]={0.0,-0.75,-1.5,-2.25,-3.0,-3.75,-4.5,-5.25,-6.0,
                     -6.75,-7.5,-8.25,-9.0,-9.75,-10.5,-11.25,-12.0,
                     -12.75,-13.5,-14.25,-15.0,-15.75,-16.5,-17.25,-18.0,
                     -18.75,-19.5,-20.25,-21.0,-21.75,-22.5,-23.25};
*/
                  /* 5 �������� 00000, 00001,00010,00100,01000,10000*/
 float Qvh_osl[32]={-23.25,-22.5,-21.75,-21.0,-20.25,-19.5,-18.75,-18.0,
                     -17.25,-16.5,-15.75,-15.0,-14.25,-13.5,-12.75,-12.0,
                     -11.25,-10.5,-9.75,-9.0,-8.25,-7.5,-6.75,-6.0,-5.25,
                     -4.5,-3.75,-3.0,-2.25,-1.5,-0.75,0.0};

                     /* 5 �������� 00000, 00001,00010,00100,01000,10000*/


  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* �������� ��� */
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned kod_att[13];

  AnsiString str2[26]={"���1","���2","���3","���4",
                       "���5","���6","���7","���8",
                       "���9","���10","���11","���12","���13",
                       "���1","���2","���3","���4",
                       "���5","���6","���7","���8",
                       "���9","���10","���11","���12","���13"};
  AnsiString str1[4]={"1��-2","2��-2","3��-2","4��-2"};

  TChartSeries *Series[4]={LineSeries3,LineSeries4,LineSeries5,LineSeries6};

  u32 buf_my[256/4]; // ����� ��� ��������� ������

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
                        byte17  : 8, /*ADC12 */
                        byte18  : 8; /*ADC13 */

                        } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;
       unsigned ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8,ADC9,ADC10,ADC11,ADC12,ADC13;
       int ADC=0;
       unsigned IPK_UP7;
       float Kod_M[35]={0};
       int Kod_DM_izm[35]={0};
       int Kod_DM_max=0;
       int nf,n_jj;
       int mk;

              E2_izm_m->Text=" ";
              E2_izm_m->Repaint();
        Chart_kvk->BottomAxis->SetMinMax(-24,0);
        Chart_kvk->LeftAxis->SetMinMax(0,3.2);
        Chart_kvk->Title->Text->Clear();
        Chart_kvk->Title->Text->Add("������ ����������� �������� �������� ���� �� ���� �������� �����������");

        Series[0]->Clear();
        Series[1]->Clear();
        Series[2]->Clear();
        Series[3]->Clear();

       // Series[3]->Repaint();
         E_pmax->Text="";
         L_pmax_no->Caption="";

          E_km_s->Text="";
          E_km_mx->Text="";

          E_dm_2->Text="";

      for(k=0; k<=34; k++)
        {
         P[k]=0;
        }

       ShowMessage("������ ������ � �� ���������� �� ���� "+str1[CB_3_vh->ItemIndex]);
        ShowMessage("���������� ���������� �������� ����� ���������� 30�� � ������ "+str2[CB_10_vyh->ItemIndex]);

   /*  if(comm_vhod(CB_3_vh->ItemIndex))  //1 -- ������, 0 -- ��� ������
           {
             ShowMessage("�� �������� ���������� 1");
             goto end;
             }
     if(comm_vyhod(CB_10_vyh->ItemIndex))//1 -- ������, 0 -- ��� ������
            {
             ShowMessage("�� �������� ���������� 2");
             goto end;
             }
   */
        Chart_kvk->Repaint();

        /* ����� 3*/
    for(i=0;i<=12;i++)
      {
      // US[i]=0x0;
       kod_att[i]=0xF;
      }
  //============/* �������� ������� ���� �������� ��� */====
   if(CB_10_vyh->ItemIndex<=12)
   {
    n_post=2;    /*���*/
    kod_att[CB_10_vyh->ItemIndex]= Q_vh[CB10_att_vyh->ItemIndex];
   }
  if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
    kod_att[CB_10_vyh->ItemIndex-13]= Q_vh[CB10_att_vyh->ItemIndex];/****?????****/
    }

   if((res=Vkl_att_t(n_post,kod_att))==1)   /*0-- ��� ������, 1-- ���� ������ */
     {
      ShowMessage("������ ��� �������� ��������� 3 ������ � ��7 ERR=1!\n");
      //goto end;
     }
 if(res==2) {ShowMessage("��� �������� ������� �� ����� 3!");}
           Sleep(1);


              /* ����� 1*/
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
 //============/* ��������� ������ ���������, ��������� ��������� ������� ��7 */========================================            /* ����� 1*/
  //n_post=2+(CB_2_ps->ItemIndex);
  if(CB_10_vyh->ItemIndex<=12)  /* 1--0: 2(���), 3(���)*/
   {
    n_post=2;    /*���*/
    nu=(CB_10_vyh->ItemIndex);    /*������ �� 0 �� 12*/  /* nu-- ����� ���������*/
    }
   if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
    nu=(CB_10_vyh->ItemIndex)-13;    /*������ �� 13 �� 25*/  /* nu-- ����� ���������*/
    }
  // nu=0;  /* ???? nu-- nu=(����� ���������*/

   if((res=Vkl_us_vip_t(n_post,nu))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ (1) � ��7!\n");
    // goto end;
    }
  if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");}
    Sleep(1);
 //*************************************************************************

     //  m_freqq = (double)CSE2->Value;
     //  ��������� ����� �� GPIB
     //  m_freqq = (double)CSE2->Value;

    m_freqq=F_rtu[UD2_f->Position];
   //m_freqq = strtod(E2_f->Text.c_str(),NULL);

   powerDBM = strtod(E2_p->Text.c_str(),NULL);

   K_nu = strtod(E_ks_1->Text.c_str(),NULL);
   if((K_nu>3.0)||(K_nu<0.0))
   {
    ShowMessage("�������� �������� ��������� ���������");
    goto end;
   }

    K_nu=(3.0-K_nu)/4.0;

  for(k=0; k<=63;k++) /* ����������� ind*/
   {
   if(F_rtu[k]==m_freqq){ind=k;break;}
    }
    m_p_1=powerDBM-dPg[ind];   /* � ������ ���������� ������ */

 /*15.12.10*/ //    power = -70.0;  //�������

 // ��������� �� ��������� ������� � ��������
 stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // �������
 stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // ��������
  if (stat != VI_SUCCESS)
  {
     ShowMessage("������ ��� ��������� �������� �� ���������");
     goto end;
  }
 // viPrintf(vigen,"PULM:STAT OFF\n");   // �������� ��� ���������
   viPrintf(viG,"OUTPut:STATe ON\n"); //�����.  ������� �� ����� ���-��

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
            /* ����� 2*/
    /*  ������� ��������� ���������������� ������ ������� ������� �� */
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������� ���  1-�� � 2-�� ������ ��� */=========================
          n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* �� 0 �� 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
      if(CB_10_vyh->ItemIndex>12) /* ���� ������ ���, �� ��������� ���*/
           n_post=3; /*���*/   /* ���� ������ ���, �� ��������� ���*/
           else  n_post=2;  nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
                 n_post=3;
           else  n_post=2; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
         if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
                 n_post=2;
           else  n_post=3;  nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
          if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
              n_post=2;
           else  n_post=3; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7!\n");
     //goto end;
    }

  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
   Sleep(1);

    pn=0x1F;
    pv=0x0;
    pstep=-0x1;  /* ���� �������� ����������� */

      vyh=true;

 for(m_p=pn,j=0; m_p>=pv; m_p+=pstep,j++) /* �� ��������*/
  {
   // Application->ProcessMessages();
 //  if(vyh==false) goto end1;
                   /* ����� 2*/
 //============/* ��������� ������ ������ ������� �� ��� 1-��� � 2-��� ������ */========================================
//============/* ������� ���� ������� ��� ��� 1-��� � 2-��� ������ */==========================
   /* n_vh1 -- ����� ������ ������� ��� 1-��� ������ ��� 0--0xF (4 �������)*/
   /* n_vh2 -- ����� ������ ������� ��� 2-��� ������ ��� 0--0xF (4 �������)*/

       n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* �� 0 �� 7*/
  if(CB_3_vh->ItemIndex==0){in1_at=Qv_vh[m_p];in2_at=0x1F;n_post=2;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[m_p];n_post=2;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=Qv_vh[m_p];in2_at=0x1F;n_post=3;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[m_p];n_post=3;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

   if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7 ERR=1!\n");
     goto end1;
    }

    /* ����� ��������� ������ */
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
       Sleep(5);


    viPrintf(viP,"ABORT\n");
    viPrintf(viP,"INIT:CONT ON\n");
    viPrintf(viP,"FETC?\n");
    viScanf(viP,"%t",buf);

    m_Pow = atof(buf);
  //  m_Pow=m_Pow-dPm[ind]+30.0;   /*� ������ ���������� ������*/
   m_Pow=m_Pow-dPm[ind];   /*� ������ ���������� ������*/
    P_dB[j]=m_Pow;

        //  Pw=pow(10,Pdbm/10); //���       Pw=pow(10,-3)*pow(10,Pdbm/10);  //��

          m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

       /*    memset(&buf1,0,20);
           sprintf(buf1,"%.3f",m_Pow);

           E2_izm_m->Text=buf1;
           E2_izm_m->Repaint();
       */
           P[j]=m_Pow;  /* �������� � �� */
           x_m_p=Qvh_osl[j];

        /* ������ ������� �������� */
                   /* ������ ���� �������� */
                         /* ����� 9*/
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//----------------������ ������ �������� ��� ������� ����������------------------------------
 // if((CB_3_vh->ItemIndex==0)||(CB_3_vh->ItemIndex==1))
//   {
//  n_post=2; /*���*/
//   }
//  if((CB_3_vh->ItemIndex==2)||(CB_3_vh->ItemIndex==3))
//    {
//      n_post=3; /*���*/
//    }
 if(CB_10_vyh->ItemIndex<=12)  /* � ����������� �� ������ */     {
     n_post=2; /**/
     }
  if(CB_10_vyh->ItemIndex>12)
     {
     n_post=3; /**/
     }
    nf=0x9;
 n_jj=0;

m_jj:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- ��� ������, 1-- ���� ������ */
   {
     ShowMessage("������ ��� �������� ��������� ������� ������ (9) � ��7!\n");
    // 10.01.11 vyh=false; goto end;
   }

  Sleep(10);
//17.07 if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07        // ��� �������� �������
//17.07//     ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07   }

  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
//17.07        // ��� �������� �������
//17.07//     ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07      if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("���� �� ����������!");
//17.07       vyh=false; goto end; //goto m2_end_5;
//17.07      }
  }
   else
   {
        // ������ �����

      LEN=packet_my_km.p_my_v.len;
      IPK=packet_my_km.p_my_v.byte1;
      SRC=packet_my_km.p_my_v.byte2&0x1F;
      DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* ����� ����� DST=0x6, ������ ����� DST=0x7*/
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
      ADC13=packet_my_km.p_my_v.byte18;

// 22.12.10
     if(CB_10_vyh->ItemIndex<=12)  /* � ����������� �� ������ */
       {
        if(CB_10_vyh->ItemIndex==0) ADC=ADC1&0xFF;
        if(CB_10_vyh->ItemIndex==1) ADC=ADC2&0xFF;
        if(CB_10_vyh->ItemIndex==2) ADC=ADC3&0xFF;
        if(CB_10_vyh->ItemIndex==3) ADC=ADC4&0xFF;
        if(CB_10_vyh->ItemIndex==4) ADC=ADC5&0xFF;
        if(CB_10_vyh->ItemIndex==5) ADC=ADC6&0xFF;
        if(CB_10_vyh->ItemIndex==6) ADC=ADC7&0xFF;
        if(CB_10_vyh->ItemIndex==7) ADC=ADC8&0xFF;
        if(CB_10_vyh->ItemIndex==8) ADC=ADC9&0xFF;
        if(CB_10_vyh->ItemIndex==9) ADC=ADC10&0xFF;
        if(CB_10_vyh->ItemIndex==10) ADC=ADC11&0xFF;
        if(CB_10_vyh->ItemIndex==11) ADC=ADC12&0xFF;
        if(CB_10_vyh->ItemIndex==12) ADC=ADC13&0xFF;
      }
    if(CB_10_vyh->ItemIndex>12)  /* � ����������� �� ������ */
      {
        if(CB_10_vyh->ItemIndex==13) ADC=ADC1&0xFF;
        if(CB_10_vyh->ItemIndex==14) ADC=ADC2&0xFF;
        if(CB_10_vyh->ItemIndex==15) ADC=ADC3&0xFF;
        if(CB_10_vyh->ItemIndex==16) ADC=ADC4&0xFF;
        if(CB_10_vyh->ItemIndex==17) ADC=ADC5&0xFF;
        if(CB_10_vyh->ItemIndex==18) ADC=ADC6&0xFF;
        if(CB_10_vyh->ItemIndex==19) ADC=ADC7&0xFF;
        if(CB_10_vyh->ItemIndex==20) ADC=ADC8&0xFF;
        if(CB_10_vyh->ItemIndex==21) ADC=ADC9&0xFF;
        if(CB_10_vyh->ItemIndex==22) ADC=ADC10&0xFF;
        if(CB_10_vyh->ItemIndex==23) ADC=ADC11&0xFF;
        if(CB_10_vyh->ItemIndex==24) ADC=ADC12&0xFF;
        if(CB_10_vyh->ItemIndex==25) ADC=ADC13&0xFF;
      }

        if(ERR==1)
         {
          //ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ ���� ��������! ERR=1");
          //goto m1;
           n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj;
            }
          else
            {
             ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ ���� ��������! ERR=1");
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

          Chart_kvk->Repaint();

   }    /* end for */

//     for(k=0;k<=31;k++)
//       {
//         x_m_p=Qvh_osl[k];
//         Series[3]->AddXY(x_m_p,P[k]);
//       }
//     for(k=0;k<=31;k++)
//       {
//         x_m_p=Qvh_osl[k];
//         Series[0]->AddXY(x_m_p,Kod_M[k]);
//       }


   for(k1=0,P_max=P[0]; k1<=31; k1+=1)  /* ���������� max �� ������ */
       {
        if(P[k1]>P_max) {P_max=P[k1];k_max=k1;}
       }
      memset(&buf1,0,20);
        sprintf(buf1,"%.2f",P_max);
           E_pmx_1->Text=buf1;
           E_pmx_1->Repaint();

      memset(&buf1,0,20);
     sprintf(buf1,"%.2f",Qvh_osl[k_max]);
           E_kd_1->Text=buf1;
           E_kd_1->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%d",Kod_DM_izm[k_max]);

           E_dm_2->Text=buf1;
           E_dm_2->Repaint();

        mk=0;
    for(k=1; k<=31; k+=1)
//     for(k=31; k>=1; k-=1)
//      for(k=k_max; k>=1; k-=1)  /* ����� �� ��������� ���� */
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
             if((P_1<-20.0)&&(k<31)) goto m1;
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
           E_pmax->Text=buf1;
           E_pmax->Repaint();

            memset(&buf1,0,20);
           sprintf(buf1,"%.2f",Qvh_osl[k_att]);
           E_max_ka->Text=buf1;
           E_max_ka->Repaint();

           memset(&buf1,0,20);
           sprintf(buf1,"%d",Kod_DM_izm[k_att]);

           E_km_s->Text=buf1;
           E_km_s->Repaint();
          }
   else  L_pmax_no->Caption="��������� �� �����������";
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

           E_km_mx->Text=buf1;
           E_km_mx->Repaint();

           memset(&buf1,0,20);
           sprintf(buf1,"%.2f",Qvh_osl[k_max]);
           E_kdm_1->Text=buf1;
           E_kdm_1->Repaint();
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
   else  L_pmax_no->Caption="��������� �� �����������";
 */
  //========================

   end1:;                         /* ����� 2 */
 //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� � ������ ���  1-�� � 2-�� ������ ��� */=========================
          n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* �� 0 �� 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7 ERR=1!\n");
     //goto end;
    }
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
     Sleep(1);
                         /* ����� 1*/
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������ ���������, ���������� ��������� ������� ��7 */=========================
 if(CB_10_vyh->ItemIndex<=12)  /* 1--0: 2(���), 3(���)*/
   {
    n_post=2;    /*���*/
   // nu=(CB_10_vyh->ItemIndex);    /*������ �� 0 �� 12*/  /* nu-- ����� ���������*/
    }
   if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
   // nu=13-(CB_10_vyh->ItemIndex);    /*������ �� 13 �� 25*/  /* nu-- ����� ���������*/
    }
  // nu=0;  /* ???? nu-- nu=(����� ���������*/

   if((res=Vykl_us_vip_t(n_post))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ (1) � ��7 ERR=1!\n");
    // goto end;
    }
    if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");}
    Sleep(1);
   end:;
  viPrintf(viG,"OUTPut:STATe OFF\n"); //����. ������� �� ����� ���-��

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
   /*15.12.10*/ //        else  L_pmax_no->Caption="��������� �� �����������";

    ShowMessage("��������� ���������\n");

}
//======================== ������� =====================================
void __fastcall TForm1::B2_tablClick(TObject *Sender)
{
if(ChkDevs==true)
 {
//  P_6->Visible=true;
  Tabl2OutChn();
  }
  else
  {
 if(FindDevises()==true)
  {
  if(ChekDev()==true)
  {
 // P_6->Visible=true;
  Tabl2OutChn();
    }
  }    //FindDevises()
 }//else
}
//---------------------------------------------------------------------------
//---------- ���������� ������� --------------------------------
void TForm1::Tabl2OutChn(void)
{
 P_6->Visible=true;
 tabl_visble();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::B2_vyhClick(TObject *Sender)
{
 P_6->Visible=false;
}
//---------------------------------------------------------------------------
//-----  ����� ������� --------------------------------
void TForm1::tabl_visble(void)
{
 int j,k;

  AnsiString str1[4]={"���� 1��-2","���� 2��-2","���� 3��-2","���� 4��-2"};
  AnsiString str2[26]={"����� ���-1","����� ���-2","����� ���-3","����� ���-4",
                       "����� ���-5","����� ���-6","����� ���-7","����� ���-8",
                       "����� ���-9","����� ���-10","����� ���-11","����� ���-12","����� ���-13",
                       "����� ���-1","����� ���-2","����� ���-3","����� ���-4",
                       "����� ���-5","����� ���-6","����� ���-7","����� ���-8",
                       "����� ���-9","����� ���-10","����� ���-11","����� ���-12","����� ���-13"};


   extern bool vyh;
  ViStatus stat=0; // ���������� ���������� ���� ViStatus
  extern double F_rtu[224];
  //extern int Q[4][64]; /* ������ ���������� �������� ����� ������� ���. */
  extern unsigned AT_1[4][64],AT_2[4][64],AT_3[4][64],AT_4[4][64],AT_5[4][64],AT_6[4][64],
         AT_7[4][64],AT_8[4][64],AT_9[4][64],AT_10[4][64],AT_11[4][64],
         AT_12[4][64],AT_13[4][64];  /* ����������� �������� ������. ����������� */
  extern unsigned IN_AT[4][64];  /* ���������� ���������� ����� */

   double powerDBM=0.0;
   double m_freqq;
   double power;

   double K_nu=0.0;

 //char buf1[256]={0};
// char buf2[256]={0};

 char buf[256]={0};

  float P[35]={0.0};       /*���������� �������� � ��*/
  float P_dB[35]={0.0};    /*���������� �������� � ��*/

 // float P_1=0.0;
  float dP;
  float p_vt_izm=0.0;

 int ind; //������ ������� � �������� ����������
 long longdown=0; /* �������� �������� ����������*/

 int m_p;
 float x_m_p;
 double m_p_1;  /* ��������, ���������� �� ����������*/
 int pn;
 int pv;
 int pstep;
 int k_att=0;

 unsigned ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8,ADC9,ADC10,ADC11,ADC12,ADC13;
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
  int nk,nu,n_us;//,n_us_n,n_us_v;  /* ����� ���*/
                                  /* ������� ��� */
  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 �������� 00000, 00001,00010,00100,01000,10000*/
/* float Qvh_osl[32]={0.0,-0.75,-1.5,-2.25,-3.0,-3.75,-4.5,-5.25,-6.0,
                     -6.75,-7.5,-8.25,-9.0,-9.75,-10.5,-11.25,-12.0,
                     -12.75,-13.5,-14.25,-15.0,-15.75,-16.5,-17.25,-18.0,
                     -18.75,-19.5,-20.25,-21.0,-21.75,-22.5,-23.25};
*/
                  /* 5 �������� 00000, 00001,00010,00100,01000,10000*/
 float Qvh_osl[32]={-23.25,-22.5,-21.75,-21.0,-20.25,-19.5,-18.75,-18.0,
                     -17.25,-16.5,-15.75,-15.0,-14.25,-13.5,-12.75,-12.0,
                     -11.25,-10.5,-9.75,-9.0,-8.25,-7.5,-6.75,-6.0,-5.25,
                     -4.5,-3.75,-3.0,-2.25,-1.5,-0.75,0.0};

                     /* 5 �������� 00000, 00001,00010,00100,01000,10000*/


  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* �������� ��� 4 �������*/

  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned kod_att[13];
  int k_f,nl,jk,n_jj,k2,nl_n,nl_v;

  int k1,k_max=0;
  int kod_att_izm=0;
  int mk=0;


  unsigned IPK_UP7;
  u32 buf_my[256/4]; // ����� ��� ��������� ������

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
                        byte17  : 8, /*ADC12 */
                        byte18  : 8; /*ADC13 */

                        } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;

  K_nu = strtod(E_ks_1->Text.c_str(),NULL);
   if((K_nu>3.0)||(K_nu<0.0))
   {
    ShowMessage("�������� �������� ��������� ���������");
    goto end;
   }

    K_nu=(3.0-K_nu)/4.0;

 PostMessage(SG_9->Handle, WM_MBUTTONDOWN, MK_LBUTTON,0);
 PostMessage(SG_9->Handle, WM_MBUTTONUP, MK_LBUTTON,0);

 L_pmax_no1->Caption="                        ";

/********************/
  if(CB_10_vyh->ItemIndex<=12)
    {
   //  n_us_n=CB_10_vyh->ItemIndex;
   //  n_us_v=CB_10_vyh->ItemIndex;
     n_us=CB_10_vyh->ItemIndex;
    }
  if(CB_10_vyh->ItemIndex>12)
    {
   //  n_us_n=13-CB_10_vyh->ItemIndex;
   //  n_us_v=13-CB_10_vyh->ItemIndex;
     n_us=CB_10_vyh->ItemIndex-13;
    }

 //if(RG7_us->ItemIndex==1) /* ��� ��������� */
 //   {
 //   n_us_n=0; n_us_v=12;
 //  }
// for(n_us=n_us_n; n_us<=n_us_v; n_us++) /* �� ����������*/
//  {
    //��� ������� ��� ���������    goto m_otl;
     /* �������� �������*/
    for(k=0;k<=63;k++)    /* ������  */
   for(j=0;j<=12;j++)   /* �������  */
     {
     SG_9->Cells[j][k]=" ";
     }
   for(k=0;k<=63;k++)    /* ������  */   /*?????*/
   SG_9->Cells[0][k]=FloatToStr(F_rtu[k]);

   L_zagol->Caption="������� �������� ��������� � ����� ������� ����������� "+str1[CB_3_vh->ItemIndex]+"  "
   +str2[CB_10_vyh->ItemIndex];
      for(k=0; k<=34; k++)
        {
         P[k]=0;
        }

        ShowMessage("������ ������ � �� ���������� �� ���� "+str1[CB_3_vh->ItemIndex]);
        ShowMessage("���������� ���������� �������� ����� ���������� 30�� � ������ "+str2[CB_10_vyh->ItemIndex]);

  /*   if(comm_vhod(CB_3_vh->ItemIndex))  //1 -- ������, 0 -- ��� ������
           {
             ShowMessage("�� �������� ���������� 1");
             goto end;
             }
     if(comm_vyhod(CB_10_vyh->ItemIndex))//1 -- ������, 0 -- ��� ������
            {
             ShowMessage("�� �������� ���������� 2");
             goto end;
             }
  */
        //  vyh=true;
 if(CB_10_vyh->ItemIndex<=12)
   {
    n_post=2;    /*���*/
    L2_1->Caption="|           ��� 1";
    L2_2->Caption="|           ��� 2";
    L2_3->Caption="|           ��� 3";
    L2_4->Caption="|           ��� 4                             |";
    nl_n=0;nl_v=3;
   }
  if(CB_10_vyh->ItemIndex>=13)
   {
    n_post=3;    /*���*/
    L2_1->Caption="|           ��� 5";
    L2_2->Caption="|           ��� 6";
    L2_3->Caption="|           ��� 7";
    L2_4->Caption="|           ��� 8                             |";
    nl_n=4; nl_v=7;
  }

// for(nl=0;nl<=3;nl++)   /* ���� �� ������ ����*/
 for(nl=nl_n;nl<=nl_v;nl++)   /* ���� �� ������ ����*/
  {
      /* ����� 3*/
    for(i=0;i<=12;i++)
      {
      // US[i]=0x0;
       kod_att[i]=0xF;
      }
        /*  ������� ��������� ���������������� ������ ������� ������� �� */
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������� ���  1-�� � 2-�� ������ ��� */=========================
          n_vh1=nl; n_vh2=nl;  /* �� 0 �� 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
      if(CB_10_vyh->ItemIndex>12) /* ���� ������ ���, �� ��������� ���*/
           n_post=3; /*���*/   /* ���� ������ ���, �� ��������� ���*/
           else  n_post=2;  nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
                 n_post=3;
           else  n_post=2; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
         if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
                 n_post=2;
           else  n_post=3;  nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
          if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
              n_post=2;
           else  n_post=3; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7!\n");
     //goto end;
    }

  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
   Sleep(1);

  //============/* �������� ������� ���� �������� ��� */====

  if(CB_10_vyh->ItemIndex<=12)
   {
    n_post=2;    /*���*/
   /* ���� ��������� */
    kod_att[CB_10_vyh->ItemIndex]= Q_vh[CB10_att_vyh->ItemIndex];
    }
  if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
    kod_att[CB_10_vyh->ItemIndex-13]= Q_vh[CB10_att_vyh->ItemIndex];
  }

if((res=Vkl_att_t(n_post,kod_att))==1)   /*0-- ��� ������, 1-- ���� ������ */
     {
      ShowMessage("������ ��� �������� ������ 3 ERR=1");
     // goto end;
     }
 if(res==2) {ShowMessage("��� �������� ������� �� ����� 3!");}
                 /* ����� 1*/
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
 //============/* ��������� ������ ���������, ��������� ��������� ������� ��7 */========================================            /* ����� 1*/
 if(CB_10_vyh->ItemIndex<=12)  /* 1--0: 2(���), 3(���)*/
   {
    n_post=2;    /*���*/
  //  nu=(CB_10_vyh->ItemIndex);    /*������ �� 0 �� 12*/  /* nu-- ����� ���������*/
  }
   if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
 //   nu=13-(CB_10_vyh->ItemIndex);    /*������ �� 13 �� 25*/  /* nu-- ����� ���������*/
    }
   nu=n_us;  /* n_us= nu=(����� ���������*/

  if((res=Vkl_us_vip_t(n_post,nu))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ������ 1 � ��7 ERR=1!\n");
 //  goto end;
    }
   if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");}

     Sleep(1);
//*************************************************************************

     //  ��������� ����� �� GPIB
  powerDBM = strtod(E2_p->Text.c_str(),NULL);

  vyh=true;

 for(k_f=0; k_f<=63; k_f++) /* �� �������*/
  {
    Application->ProcessMessages();
      // if(vyh==false) goto m_otl;
    if(vyh==false) goto end; /* ����� ��������� */
     m_freqq=F_rtu[k_f];
   //m_freqq = strtod(E2_f->Text.c_str(),NULL);

  for(k=0; k<=63;k++) /* ����������� ind*/
   {
   if(F_rtu[k]==m_freqq){ind=k;break;}
    }
    m_p_1=powerDBM-dPg[ind];   /* � ������ ���������� ������ */

 /*15.12.10*/ //    power = -70.0;  //�������

 // ��������� �� ��������� ������� � ��������
 stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // �������
 stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // ��������
  if (stat != VI_SUCCESS)
  {
     ShowMessage("������ ��� ��������� �������� �� ���������");
     goto end;
  }
 // viPrintf(vigen,"PULM:STAT OFF\n");   // �������� ��� ���������
   viPrintf(viG,"OUTPut:STATe ON\n"); //�����.  ������� �� ����� ���-��

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
    pstep=-0x1;  /* ���� �������� ����������� */

//      vyh=true;

 for(m_p=pn,j=0; m_p>=pv; m_p+=pstep,j++) /* �� ��������*/
  {
  // Application->ProcessMessages();
 //  if(vyh==false) goto end1;

                   /* ����� 2*/
//============/* ��������� ������ ������ ������� �� ��� 1-��� � 2-��� ������ */========================================
//============/* ������� ���� ������� ��� ��� 1-��� � 2-��� ������ */==========================
   /* n_vh1 -- ����� ������ ������� ��� 1-��� ������ ��� 0--0xF (4 �������)*/
   /* n_vh2 -- ����� ������ ������� ��� 2-��� ������ ��� 0--0xF (4 �������)*/

       n_vh1= nl; n_vh2=nl;  /* �� 0 �� 7 -- ����� �� 0 �� 3*/
  if(CB_3_vh->ItemIndex==0){in1_at=Qv_vh[m_p];in2_at=0x1F;n_post=2;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[m_p];n_post=2;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=Qv_vh[m_p];in2_at=0x1F;n_post=3;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[m_p];n_post=3;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ������ 2 � ��7 ERR=1!\n");
     goto end1_v;
    }

   /* ����� ��������� ������ */
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}

     Sleep(1);

    viPrintf(viP,"ABORT\n");
    viPrintf(viP,"INIT:CONT ON\n");
    viPrintf(viP,"FETC?\n");
    viScanf(viP,"%t",buf);

    m_Pow = atof(buf);
//    m_Pow=m_Pow-dPm[ind]+30.0;   /*� ������ ���������� ������*/
    m_Pow=m_Pow-dPm[ind];   /* 10.02.2011 � ������ ���������� ������*/
    P_dB[j]=m_Pow;

        //  Pw=pow(10,Pdbm/10); //���       Pw=pow(10,-3)*pow(10,Pdbm/10);  //��

          m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

       /*    memset(&buf1,0,20);
           sprintf(buf1,"%.3f",m_Pow);

           E2_izm_m->Text=buf1;
           E2_izm_m->Repaint();
       */
           P[j]=m_Pow;  /* �������� � �� */
           x_m_p=Qvh_osl[j];

   }    /* end for */

/***** 10.01.2011 */
if(RG10->ItemIndex==0) /* P 2 �� ����. */
  {
    mk=0;  /*15.03.11*/
    for(k=1; k<=31; k+=1)
       {
        dP=fabs(P_dB[k]-P_dB[k-1]);
  //      if(dP<0.25)
         if(dP<K_nu)
            {
            // P_1=P_dB[k];
             p_vt_izm=P[k];
             k_att=k;
             mk=mk+1;/*15.03.11*/
           //  if((P_1<-20.0)&&(k<31)) goto m11;
            // if((P_1<0.0)&&(k<31)) goto m11;
             if((p_vt_izm<0.5)&&(k<31)) goto m11;
             if(mk==3) goto end2; /*15.03.11*/
           }
        m11:;
       }

     end2:;
      if(p_vt_izm>0.5)
       {
         if(CB_10_vyh->ItemIndex<=12)
          {
          //sprintf(buf1,"%.2f",p_vt_izm);
          //SG_9->Cells[3*nl+1][k_f]=FloatToStrF(p_vt_izm,ffGeneral,3,2);
           SG_9->Cells[3*nl+1][k_f]=CurrToStrF(p_vt_izm,ffFixed,2);
          SG_9->Repaint();

         // sprintf(buf1,"%.2f",Qvh_osl[k_att]);
        //  SG_9->Cells[3*nl+2][k_f]=FloatToStrF(Qvh_osl[k_att],ffGeneral,3,2);
         SG_9->Cells[3*nl+2][k_f]=CurrToStrF(Qvh_osl[k_att],ffFixed,2);
          SG_9->Repaint();
         }
        if(CB_10_vyh->ItemIndex>12)
          {
         // sprintf(buf1,"%.2f",p_vt_izm);
         // SG_9->Cells[3*(nl-4)+1][k_f]=FloatToStrF(p_vt_izm,ffGeneral,3,2);
          SG_9->Cells[3*(nl-4)+1][k_f]=CurrToStrF(p_vt_izm,ffFixed,2);
          SG_9->Repaint();

         // sprintf(buf1,"%.2f",Qvh_osl[k_att]);
         // SG_9->Cells[3*(nl-4)+2][k_f]=FloatToStrF(Qvh_osl[k_att],ffGeneral,3,2);
          SG_9->Cells[3*(nl-4)+2][k_f]=CurrToStrF(Qvh_osl[k_att],ffFixed,2);
          SG_9->Repaint();
         }

         // Q[nl][k_f]=Qv_vh[31-k_att];  /* ��� ������� ������� ����� */
          kod_att_izm=k_att;
      }
    else
      {
        L_pmax_no1->Caption="��������� �� �����������";

       if(CB_10_vyh->ItemIndex<=12)
          {
          SG_9->Cells[3*nl+3][k_f]=IntToStr(0);/* ��������!!!*/
          SG_9->Repaint();
          SG_9->Cells[3*nl+1][k_f]=IntToStr(0);
          SG_9->Repaint();
          SG_9->Cells[3*nl+2][k_f]=IntToStr(0);
          SG_9->Repaint();
          }
       if(CB_10_vyh->ItemIndex>12)
          {
          SG_9->Cells[3*(nl-4)+3][k_f]=IntToStr(0);/* ��������!!!*/
          SG_9->Repaint();
          SG_9->Cells[3*(nl-4)+1][k_f]=IntToStr(0);
          SG_9->Repaint();
          SG_9->Cells[3*(nl-4)+2][k_f]=IntToStr(0);
          SG_9->Repaint();
          }

        goto  m2_end_5_v;
      }
}/*if 0*/

  if(RG10->ItemIndex==1) /* �� � ��� */
  {
    for(k1=0,P_max=P[0]; k1<=31; k1+=1)
       {

         if(P[k1]>P_max) {P_max=P[k1];k_max=k1;}
       }
      if(CB_10_vyh->ItemIndex<=12)
       {
         // sprintf(buf1,"%.2f",P_max);
         // SG_9->Cells[3*nl+1][k_f]=FloatToStrF(P_max,ffGeneral,3,2);
          SG_9->Cells[3*nl+1][k_f]=CurrToStrF(P_max,ffFixed,2);
          SG_9->Repaint();

         // sprintf(buf1,"%.2f",Qvh_osl[k_max]);
         // SG_9->Cells[3*nl+2][k_f]=FloatToStrF(Qvh_osl[k_max],ffGeneral,3,2);
         SG_9->Cells[3*nl+2][k_f]=CurrToStrF(Qvh_osl[k_max],ffFixed,2);
          SG_9->Repaint();
      }
    if(CB_10_vyh->ItemIndex>12)
       {
         //  sprintf(buf1,"%.2f",P_max);
         //  SG_9->Cells[3*(nl-4)+1][k_f]=FloatToStrF(P_max,ffGeneral,3,2);
          SG_9->Cells[3*(nl-4)+1][k_f]=CurrToStrF(P_max,ffFixed,2);
           SG_9->Repaint();

         //  sprintf(buf1,"%.2f",Qvh_osl[k_max]);
         //  SG_9->Cells[3*(nl-4)+2][k_f]=FloatToStrF(Qvh_osl[k_max],ffGeneral,3,2);
          SG_9->Cells[3*(nl-4)+2][k_f]=CurrToStrF(Qvh_osl[k_max],ffFixed,2);
           SG_9->Repaint();
      }

  //   Q[nl][k_f]=Qv_vh[31-k_max];  /* ��� ������� ������� ����� */
     kod_att_izm=k_max;

  }  /*if 1 */
  Sleep(10);
      /* ��������� ���� ���*/
/*������� ��������� ��������������� ��� �������� ���  � �������� ������� �� ����� 2*/
    n_vh1= nl; n_vh2=nl;  /* �� 0 �� 7 -- ����� �� 0 �� 3*/
   // kod_att_izm=31-kod_att_izm;   /*��������!!! */

if(CB_3_vh->ItemIndex==0){in1_at=Qv_vh[31-kod_att_izm];in2_at=0x1F;n_post=2;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[31-kod_att_izm];n_post=2;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

if(CB_3_vh->ItemIndex==2){in1_at=Qv_vh[31-kod_att_izm];in2_at=0x1F;n_post=3;nk_svch=1;
       }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[31-kod_att_izm];n_post=3;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ������ 2 � ��7 ERR=1!\n");
    // goto end1;
    }
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}

 Sleep(10);
                   /* ������ ���� �������� */
                          /* ����� 9*/
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//----------------������ ������ �������� ��� ������� ����������------------------------------
 if(CB_10_vyh->ItemIndex<=12)   /*  � ����������� �� ������*/
     {
     n_post=2; /**/
     }
  if(CB_10_vyh->ItemIndex>12)
     {
     n_post=3; /**/
   }
    nf=0x9;

  n_jj=0;

m_jj_v:
 //if((res=zapr_dan_up7_t(n_post,nf))==1)   /*0-- ��� ������, 1-- ���� ������ */
 if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������� ������ (9) � ��7!\n");
   //6.12.2011  vyh=false;
     // goto end;
   }
   Sleep(10);
//17.07 if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07        // ��� �������� �������//     ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07   }

  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
//17.07        // ��� �������� �������
//17.07//     ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07      if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj_v;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("���� �� ����������!");
//17.07       goto m2_end_5_v;
//17.07      }
   }
  else
  {
   /* ����� ��������� ������ */

       // ������ �����
      LEN=packet_my_km.p_my_v.len;
      IPK=packet_my_km.p_my_v.byte1;
      SRC=packet_my_km.p_my_v.byte2&0x1F;
      DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* ����� ����� DST=0x6, ������ ����� DST=0x7*/
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
      ADC13=packet_my_km.p_my_v.byte18;

// 22.12.10
      if(CB_10_vyh->ItemIndex<=12)  /* � ����������� �� ������ */
       {
        if(CB_10_vyh->ItemIndex==0) ADC=ADC1&0xFF;
        if(CB_10_vyh->ItemIndex==1) ADC=ADC2&0xFF;
        if(CB_10_vyh->ItemIndex==2) ADC=ADC3&0xFF;
        if(CB_10_vyh->ItemIndex==3) ADC=ADC4&0xFF;
        if(CB_10_vyh->ItemIndex==4) ADC=ADC5&0xFF;
        if(CB_10_vyh->ItemIndex==5) ADC=ADC6&0xFF;
        if(CB_10_vyh->ItemIndex==6) ADC=ADC7&0xFF;
        if(CB_10_vyh->ItemIndex==7) ADC=ADC8&0xFF;
        if(CB_10_vyh->ItemIndex==8) ADC=ADC9&0xFF;
        if(CB_10_vyh->ItemIndex==9) ADC=ADC10&0xFF;
        if(CB_10_vyh->ItemIndex==10) ADC=ADC11&0xFF;
        if(CB_10_vyh->ItemIndex==11) ADC=ADC12&0xFF;
        if(CB_10_vyh->ItemIndex==12) ADC=ADC13&0xFF;
       }
    if(CB_10_vyh->ItemIndex>12)  /* � ����������� �� ������ */
      {
        if(CB_10_vyh->ItemIndex==13) ADC=ADC1&0xFF;
        if(CB_10_vyh->ItemIndex==14) ADC=ADC2&0xFF;
        if(CB_10_vyh->ItemIndex==15) ADC=ADC3&0xFF;
        if(CB_10_vyh->ItemIndex==16) ADC=ADC4&0xFF;
        if(CB_10_vyh->ItemIndex==17) ADC=ADC5&0xFF;
        if(CB_10_vyh->ItemIndex==18) ADC=ADC6&0xFF;
        if(CB_10_vyh->ItemIndex==19) ADC=ADC7&0xFF;
        if(CB_10_vyh->ItemIndex==20) ADC=ADC8&0xFF;
        if(CB_10_vyh->ItemIndex==21) ADC=ADC9&0xFF;
        if(CB_10_vyh->ItemIndex==22) ADC=ADC10&0xFF;
        if(CB_10_vyh->ItemIndex==23) ADC=ADC11&0xFF;
        if(CB_10_vyh->ItemIndex==24) ADC=ADC12&0xFF;
        if(CB_10_vyh->ItemIndex==25) ADC=ADC13&0xFF;
      }

    if(ERR==1)
     {
          //ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ ���� ��������! ERR=1");
         // goto m22;
           n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj_v;
            }
          else
            {
             ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ ���� ��������! ERR=1");
             goto m22_v;
            }
     }

         // memset(&buf1,0,20);
         // sprintf(buf1,"%d",ADC);

        if(CB_10_vyh->ItemIndex<=12)
          {
          SG_9->Cells[3*nl+3][k_f]=IntToStr(ADC);/* ��������!!!*/
          SG_9->Repaint();
          }
        if(CB_10_vyh->ItemIndex>12)
          {
          SG_9->Cells[3*(nl-4)+3][k_f]=IntToStr(ADC);/* ��������!!!*/
          SG_9->Repaint();
          }

       m22_v:;
   }
  m2_end_5_v:;


   }/* end   �� ������ k_f*/

   end1_v:;                         /* ����� 2 */
 //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������� ���  1-�� � 2-�� ������ ��� */=========================
       //   n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* �� 0 �� 7*/
       n_vh1= nl; n_vh2=nl;  /* �� 0 �� 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

 if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ������ 2 � ��7 ERR=1!\n");
    // goto end;
    }

  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}

     Sleep(1);
                      /* ����� 1*/
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������ ���������, ���������� ��������� ������� ��7 */=========================

 if(CB_10_vyh->ItemIndex<=12)  /* 1--0: 2(���), 3(���)*/
   {
    n_post=2;    /*���*/

    }
 if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
   }

  if((res=Vykl_us_vip_t(n_post))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ������ 1 � ��7 ERR=1!\n");
    // goto end;
    }

  if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");}
         Sleep(1);
  } /* end  nl*/

m_otl:;
        viPrintf(viG,"OUTPut:STATe OFF\n"); //����. ������� �� ����� ���-��
        zapis_tabl_my(n_us);
   //    }  /* end �� ����������*/
// }  /*��� ��������� */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   /*  ��������� ����������� ��� ������ */
   end:;
                 //  ��� ������ �� ����
      /* ����� 2 */
 //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������� ���  1-�� � 2-�� ������ ��� */=========================
       //   n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* �� 0 �� 7*/
      if(nl>3) nl=3;
        n_vh1= nl; n_vh2=nl;  /* �� 0 �� 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

 if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ������ 2 � ��7 ERR=1!\n");
    // goto end;
    }

  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}

     Sleep(1);
                      /* ����� 1*/
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������ ���������, ���������� ��������� ������� ��7 */=========================

 if(CB_10_vyh->ItemIndex<=12)  /* 1--0: 2(���), 3(���)*/
  {
    n_post=2;    /*���*/

   }
  if(CB_10_vyh->ItemIndex>12)
  {
    n_post=3; /*���*/
   }

  if((res=Vykl_us_vip_t(n_post))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ������ 1 � ��7 ERR=1!\n");
    // goto end;
    }

  if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");}
         Sleep(1);

  viPrintf(viG,"OUTPut:STATe OFF\n"); //����. ������� �� ����� ���-��

  ShowMessage("��������� ���������\n");
}
//---------------------------------------------------------------------------
//void __fastcall TForm1::obrabotka(void)
//{
// //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   /*  ��������� ����������� ��� ������ */
// for(nl=0;nl<=3;nl++)   /* ���� �� ������ ����*/
//  {
//  for(k_f=0; k_f<=63; k_f++) /* �� �������*/
//   {
// /*   P_izm_mod[0][nl][k_f]=P0[nl][k_f];
//    P_izm_mod[1][nl][k_f]=P1[nl][k_f];
//    P_izm_mod[2][nl][k_f]=P2[nl][k_f];
//    P_izm_mod[3][nl][k_f]=P3[nl][k_f];
//    P_izm_mod[4][nl][k_f]=P4[nl][k_f];
//    P_izm_mod[5][nl][k_f]=P5[nl][k_f];
//    P_izm_mod[6][nl][k_f]=P6[nl][k_f];
//    P_izm_mod[7][nl][k_f]=P7[nl][k_f];
//    P_izm_mod[8][nl][k_f]=P8[nl][k_f];
//    P_izm_mod[9][nl][k_f]=P9[nl][k_f];
//    P_izm_mod[10][nl][k_f]=P10[nl][k_f];
//    P_izm_mod[11][nl][k_f]=P11[nl][k_f];
//    P_izm_mod[12][nl][k_f]=P12[nl][k_f];
//    P_izm_mod[13][nl][k_f]=P13[nl][k_f];
//*/
//    P_izm_mod[0]=P0[nl][k_f];
//    P_izm_mod[1]=P1[nl][k_f];
//    P_izm_mod[2]=P2[nl][k_f];
//    P_izm_mod[3]=P3[nl][k_f];
//    P_izm_mod[4]=P4[nl][k_f];
//    P_izm_mod[5]=P5[nl][k_f];
//    P_izm_mod[6]=P6[nl][k_f];
//    P_izm_mod[7]=P7[nl][k_f];
//    P_izm_mod[8]=P8[nl][k_f];
//    P_izm_mod[9]=P9[nl][k_f];
//    P_izm_mod[10]=P10[nl][k_f];
//    P_izm_mod[11]=P11[nl][k_f];
//    P_izm_mod[12]=P12[nl][k_f];
//    P_izm_mod[13]=P13[nl][k_f];

///*   for(k1=0,P_max_mod=P_izm_mod[0][nl][k_f]; k1<=12; k1+=1)
//       {
//       if(P_izm_mod[k1][nl][k_f]>P_max_mod) {P_max_mod=P_izm_mod[k1][nl][k_f];k_max_mod=k1;}
//       }
//*/
//   for(k1=0,P_max_mod=P_izm_mod[0]; k1<=12; k1+=1)
//       {
//       if(P_izm_mod[k1]>P_max_mod) {P_max_mod=P_izm_mod[k1];k_max_mod=k1;}
//       }
//
//    if(k_max_mod==0) P_in_att=P0[nl][k_f];
//    if(k_max_mod==1) P_in_att=P1[nl][k_f];
//    if(k_max_mod==2) P_in_att=P2[nl][k_f];
//    if(k_max_mod==3) P_in_att=P3[nl][k_f];
//    if(k_max_mod==4) P_in_att=P4[nl][k_f];
//    if(k_max_mod==5) P_in_att=P5[nl][k_f];
//    if(k_max_mod==6) P_in_att=P6[nl][k_f];
//    if(k_max_mod==7) P_in_att=P7[nl][k_f];
//    if(k_max_mod==8) P_in_att=P8[nl][k_f];
//    if(k_max_mod==9) P_in_att=P9[nl][k_f];
//    if(k_max_mod==10) P_in_att=P10[nl][k_f];
//    if(k_max_mod==11) P_in_att=P11[nl][k_f];
//    if(k_max_mod==12) P_in_att=P12[nl][k_f];
//
//   for(k1=0; k1<=31; k1+=1)
//       {
//        if(P_in_att==Qvh_osl[31-k1]) {IN_AT[nl][k_f]=Qv_vh[k1];} /* ��� ������� ������� �����  ��� �������� ���*/
//       }
//
//     dP_osl_0[nl][k_f]=P0[nl][k_f]-P_max_mod;
//     dP_osl_1[nl][k_f]=P1[nl][k_f]-P_max_mod;
//     dP_osl_2[nl][k_f]=P2[nl][k_f]-P_max_mod;
//     dP_osl_3[nl][k_f]=P3[nl][k_f]-P_max_mod;
//     dP_osl_4[nl][k_f]=P4[nl][k_f]-P_max_mod;
//     dP_osl_5[nl][k_f]=P5[nl][k_f]-P_max_mod;
//     dP_osl_6[nl][k_f]=P6[nl][k_f]-P_max_mod;
//     dP_osl_7[nl][k_f]=P7[nl][k_f]-P_max_mod;
//     dP_osl_8[nl][k_f]=P8[nl][k_f]-P_max_mod;
//     dP_osl_9[nl][k_f]=P9[nl][k_f]-P_max_mod;
//     dP_osl_10[nl][k_f]=P10[nl][k_f]-P_max_mod;
//     dP_osl_10[nl][k_f]=P11[nl][k_f]-P_max_mod;
//     dP_osl_12[nl][k_f]=P12[nl][k_f]-P_max_mod;
//
//     AT_1[nl][k_f]=0xF; AT_2[nl][k_f]=0xF;AT_3[nl][k_f]=0xF;
//     AT_4[nl][k_f]=0xF; AT_5[nl][k_f]=0xF;AT_6[nl][k_f]=0xF;
//     AT_7[nl][k_f]=0xF; AT_8[nl][k_f]=0xF;AT_9[nl][k_f]=0xF;
//     AT_10[nl][k_f]=0xF;AT_11[nl][k_f]=0xF;AT_12[nl][k_f]=0xF;
//     AT_13[nl][k_f]=0xF;
//
//     for(k2=0;k2<=15;k2++)  /* ���������� ����� �������� ��� �� �� 16 ���������*/
//      {
//        if(dP_osl_0[nl][k_f]==Q_vh_zn[k2]) AT_1[nl][k_f]=k2;
//         if(dP_osl_1[nl][k_f]==Q_vh_zn[k2]) AT_2[nl][k_f]=k2;
//          if(dP_osl_2[nl][k_f]==Q_vh_zn[k2]) AT_3[nl][k_f]=k2;
//           if(dP_osl_3[nl][k_f]==Q_vh_zn[k2]) AT_4[nl][k_f]=k2;
//            if(dP_osl_4[nl][k_f]==Q_vh_zn[k2]) AT_5[nl][k_f]=k2;
//             if(dP_osl_5[nl][k_f]==Q_vh_zn[k2]) AT_6[nl][k_f]=k2;
//              if(dP_osl_6[nl][k_f]==Q_vh_zn[k2]) AT_7[nl][k_f]=k2;
//               if(dP_osl_7[nl][k_f]==Q_vh_zn[k2]) AT_8[nl][k_f]=k2;
//                if(dP_osl_8[nl][k_f]==Q_vh_zn[k2]) AT_9[nl][k_f]=k2;
//                 if(dP_osl_9[nl][k_f]==Q_vh_zn[k2]) AT_10[nl][k_f]=k2;
//                  if(dP_osl_10[nl][k_f]==Q_vh_zn[k2]) AT_11[nl][k_f]=k2;
//                   if(dP_osl_11[nl][k_f]==Q_vh_zn[k2]) AT_12[nl][k_f]=k2;
//                    if(dP_osl_12[nl][k_f]==Q_vh_zn[k2]) AT_13[nl][k_f]=k2;
//       }
//     }/* end k_f */
//  } /* end nl */
//
//}


void __fastcall TForm1::B2_stClick(TObject *Sender)
{
 extern bool vyh;
 vyh=false;
}
//---------------------------------------------------------------------------
int TForm1::otvet_paket(void) /* 0-- ��� ������; 1-- ���� ������ (ERR=1); 2-- ��� �������� �������*/
{
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  int jk;
  int nk;

  unsigned IPK_UP7;


  u32 buf_my[256/4]; // ����� ��� ��������� ������

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

   /* ����� ��������� ������ */
 for(jk=0;jk<=9;jk++)
   {
    if(!UPS_RECIV_KIO_PACKET(&nk,packet_my.buf_my))
      {
       // ��� �������� �������
       Sleep(1);
       if(jk==9)
       {
     //  ShowMessage("��� �������� ������� �� ����� (2)!");
       return 2; //goto m2_end;
       }
     }
     else break;
   } /* end for*/
        // ������ �����
        LEN=packet_my.p_my_v.len;
        IPK=packet_my.p_my_v.byte1;
        SRC=packet_my.p_my_v.byte2&0x1F;
        DST=((packet_my.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* ����� ����� DST=0x6, ������ ����� DST=0x7*/
        IPS=(packet_my.p_my_v.byte3>>2)&0x3F;
        ERR=packet_my.p_my_v.byte4&0x1;
        if(ERR==1) {
                    // ShowMessage("������ ��� �������� ������ 2 ��7! ERR=1");
                     return 1;
                    }
  //  m2_end:;
   return 0;
}
//=================================================================
//struct LUCHi_kvh
//       {
//        int n_f;   /* ����� ��������� ����� ��� ������ 2: 0--63*/
//        unsigned kod_att_vh;  /* ��� �������� �����.*/
//        unsigned kod_att_vyh; /* ��� ��������� �����. */
//        float P_vyh;    /* ���������� �������� �������� �� ������ ���������*/
//       };
//========================================================================

int TForm1::zap_dann(unsigned kod_f,unsigned NL, unsigned NP, unsigned NIT)
{
 //extern
 unsigned AT_1,AT_2,AT_3,AT_4,AT_5,AT_6,
        AT_7,AT_8,AT_9,AT_10,AT_11,AT_12,AT_13;
 //extern unsigned AT_1[4][64],AT_2[4][64],AT_3[4][64],AT_4[4][64],AT_5[4][64],AT_6[4][64],
 //        AT_7[4][64],AT_8[4][64],AT_9[4][64],AT_10[4][64],AT_11[4][64],
 //        AT_12[4][64],AT_13[4][64];  /* ����������� �������� ������. ����������� */
// extern unsigned IN_AT[4][64];  /* ���������� ���������� ����� */

// extern
 unsigned IN_AT;
 unsigned i;
 unsigned NS;

 unsigned LEN,IPK=0xFF;
 unsigned DST=0x0,SRC=0x0,IPS=0x6; /* ������ �� FLASH */
// U32 ADDR_FLASH;

 unsigned AT1[4]={0};
 unsigned AT2[4]={0};
 unsigned AT3[4]={0};
 unsigned AT4[4]={0};
 unsigned AT5[4]={0};
 unsigned AT6[4]={0};
 unsigned AT7[4]={0};
 unsigned AT8[4]={0};
 unsigned AT9[4]={0};
 unsigned AT10[4]={0};
 unsigned AT11[4]={0};
 unsigned AT12[4]={0};

 unsigned AT13[4]={0};
 unsigned INAT[4]={0};

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
                        byte10  : 8;

              } p_my;
             U32 buf[256/4];
             }  packet;
         LEN=0xA; /*10 ���� � ������ (4+6)*/
         IPK=0xFF;

      // �������� ������ ������ �� FLASH

        AT1[0]=AT_1&0x1;
        AT1[1]=(AT_1>>1)&0x1;
        AT1[2]=(AT_1>>2)&0x1;
        AT1[3]=(AT_1>>3)&0x1;

        AT2[0]=AT_2&0x1;
        AT2[1]=(AT_2>>1)&0x1;
        AT2[2]=(AT_2>>2)&0x1;
        AT2[3]=(AT_2>>3)&0x1;

        AT3[0]=AT_3&0x1;
        AT3[1]=(AT_3>>1)&0x1;
        AT3[2]=(AT_3>>2)&0x1;
        AT3[3]=(AT_3>>3)&0x1;

        AT4[0]=AT_4&0x1;
        AT4[1]=(AT_4>>1)&0x1;
        AT4[2]=(AT_4>>2)&0x1;
        AT4[3]=(AT_4>>3)&0x1;

        AT5[0]=AT_5&0x1;
        AT5[1]=(AT_5>>1)&0x1;
        AT5[2]=(AT_5>>2)&0x1;
        AT5[3]=(AT_5>>3)&0x1;

        AT6[0]=AT_6&0x1;
        AT6[1]=(AT_6>>1)&0x1;
        AT6[2]=(AT_6>>2)&0x1;
        AT6[3]=(AT_6>>3)&0x1;

        AT7[0]=AT_7&0x1;
        AT7[1]=(AT_7>>1)&0x1;
        AT7[2]=(AT_7>>2)&0x1;
        AT7[3]=(AT_7>>3)&0x1;

        AT8[0]=AT_8&0x1;
        AT8[1]=(AT_8>>1)&0x1;
        AT8[2]=(AT_8>>2)&0x1;
        AT8[3]=(AT_8>>3)&0x1;

        AT9[0]=AT_9&0x1;
        AT9[1]=(AT_9>>1)&0x1;
        AT9[2]=(AT_9>>2)&0x1;
        AT9[3]=(AT_9>>3)&0x1;

        AT10[0]=AT_10&0x1;
        AT10[1]=(AT_10>>1)&0x1;
        AT10[2]=(AT_10>>2)&0x1;
        AT10[3]=(AT_10>>3)&0x1;

        AT11[0]=AT_11&0x1;
        AT11[1]=(AT_11>>1)&0x1;
        AT11[2]=(AT_11>>2)&0x1;
        AT11[3]=(AT_11>>3)&0x1;

        AT12[0]=AT_12&0x1;
        AT12[1]=(AT_12>>1)&0x1;
        AT12[2]=(AT_12>>2)&0x1;
        AT12[3]=(AT_12>>3)&0x1;

        if(NIT>=4)       /* ����� ������ 2 (NIT=4,5,6,7)*/
         {
          AT13[0]=AT_13&0x1;
          AT13[1]=(AT_13>>1)&0x1;
          AT13[2]=(AT_13>>2)&0x1;
          AT13[3]=(AT_13>>3)&0x1;
         }
        INAT[0]=IN_AT&0x1;  /* ������� ���. ���������������� ����� */
        INAT[1]=(IN_AT>>1)&0x1;
        INAT[2]=(IN_AT>>2)&0x1;
        INAT[3]=(IN_AT>>3)&0x1;

      for(i=0;i<=3;i++)
       {
        NS=i;
        packet.p_my.len = LEN;
        packet.p_my.byte1 = IPK;  /* IPK=0xFF*/
        packet.p_my.byte2 = (SRC&0x1F)|((DST<<5))&0x7;
        packet.p_my.byte3 = (DST&0x3)|(IPS<<2);

    packet.p_my.byte4 = (NS&0x3)|((kod_f&0x3F)<<2);   /* �� kod_f 6 ��������*/     /*?????????!!!!!!!!*/
    packet.p_my.byte5 = ((kod_f>>6)&0x3)|((NL&0x7)<<2)|((NP&0x1)<<5)|((NIT&0x7)<<6);  /*�����*/
    packet.p_my.byte6 = (0x1<<5)&0xFF;
    packet.p_my.byte7 = 0x0;

    if(NS==0)
    {
    packet.p_my.byte8 = AT1[0]|AT1[1]<<1|AT1[2]<<2|AT1[3]<<3|AT2[0]<<4|AT2[1]<<5|AT2[2]<<6|AT2[3]<<7;
    packet.p_my.byte9 = AT3[0]|AT3[1]<<1|AT3[2]<<2|AT3[3]<<3|AT4[0]<<4|AT4[1]<<5|AT4[2]<<6|AT4[3]<<7;
    }
    if(NS==1)
    {
    packet.p_my.byte8 = AT5[0]|AT5[1]<<1|AT5[2]<<2|AT5[3]<<3|AT6[0]<<4|AT6[1]<<5|AT6[2]<<6|AT6[3]<<7;
    packet.p_my.byte9 = AT7[0]|AT7[1]<<1|AT7[2]<<2|AT7[3]<<3|AT8[0]<<4|AT8[1]<<5|AT8[2]<<6|AT8[3]<<7;
    }
    if(NS==2)
    {
    packet.p_my.byte8 = AT9[0]|AT9[1]<<1|AT9[2]<<2|AT9[3]<<3|AT10[0]<<4|AT10[1]<<5|AT10[2]<<6|AT10[3]<<7;
    packet.p_my.byte9 = AT11[0]|AT11[1]<<1|AT11[2]<<2|AT11[3]<<3|AT12[0]<<4|AT12[1]<<5|AT12[2]<<6|AT12[3]<<7;
    }
    if(NS==3)
    {
    packet.p_my.byte8 = AT13[0]|AT13[1]<<1|AT13[2]<<2|AT13[3]<<3;
    packet.p_my.byte9 = INAT[0]|INAT[1]<<1|INAT[2]<<2|INAT[3]<<3;
    }

       if( UPS_SEND_KIO_PACKET (1,packet.buf)  ==  true){return(0);}
         else{ShowMessage("������ �������� ������!");return(1);}
    } /*end for*/
   return(0);
 }
//***************************������  � ���� ����������  mrt.* ***********************
void __fastcall TForm1::B_22_zapClick(TObject *Sender)
{
  FILE *tr;
  FILE *tr_dan;

//extern int Q[4][64]; /* ������ ���������� �������� ����� ������� ���. */
 unsigned Addr[4][64];
 unsigned adress;
 //u16 Addr[4][64];
 //u16 adress;

 extern unsigned AT_1[4][64],AT_2[4][64],AT_3[4][64],AT_4[4][64],AT_5[4][64],AT_6[4][64],
                 AT_7[4][64],AT_8[4][64],AT_9[4][64],AT_10[4][64],AT_11[4][64],
                 AT_12[4][64],AT_13[4][64];  /* ����������� �������� ������. ����������� ��� ������ 2*/
 extern unsigned IN_AT[4][64];  /* ���������� ���������� ����� ��� ������ 2 */
 extern unsigned AT_1_53[8][160],AT_2_53[8][160],AT_3_53[8][160],AT_4_53[8][160],
         AT_5_53[8][160],AT_6_53[8][160],AT_7_53[8][160],AT_8_53[8][160],
         AT_9_53[8][160],AT_10_53[8][160],AT_11_53[8][160],AT_12_53[8][160],
         AT_13_53[8][160];  /* ����������� �������� ������. ����������� ������ 53*/
 extern unsigned IN_AT_53[8][160];  /* ���������� ���������� ����� ������ 53*/

 unsigned i;
 unsigned kod_f;
 unsigned NS,NL,NP,NIT,NVYX,Nn;
 unsigned addr_7,addr_16;
 //u8 addr_7,addr_16;
 //u8 dan_0_ml,dan_0_st,dan_1_ml,dan_1_st,dan_2_ml,dan_2_st,dan_3_ml,dan_3_st;
 unsigned dan_0_ml,dan_0_st,dan_1_ml,dan_1_st,dan_2_ml,dan_2_st,dan_3_ml,dan_3_st;
 unsigned dan_0,dan_1,dan_2,dan_3;
 u16 dan_0_all=0x0;
 unsigned AT1[4]={0};
 unsigned AT2[4]={0};
 unsigned AT3[4]={0};
 unsigned AT4[4]={0};
 unsigned AT5[4]={0};
 unsigned AT6[4]={0};
 unsigned AT7[4]={0};
 unsigned AT8[4]={0};
 unsigned AT9[4]={0};
 unsigned AT10[4]={0};
 unsigned AT11[4]={0};
 unsigned AT12[4]={0};

 unsigned AT13[4]={0};
 unsigned INAT[5]={0};

 float P_in_att[4][64];

 String str,str1;
 int n,k,ns,k_f;
 int kod_fpch;
 int n_p,n_l,n_it,n_n,n_fpch,nl1,nl2,k_v,nl,nl_ind;
 int k1,k2,m_my,n_vhod,lit;

  u32 cnt = 0; //���-�� ������� ������
 //  const u32 sz = 64; //������ �������
   u16 crc = 0; //����������� �����

   str=E_f->Text;
 if((tr = fopen(str.c_str(),"wb+")) == NULL)
  {
  ShowMessage("��� �����");
  goto m1;
 }
 else
 {
  if(MessageDlg("������������ ����?",
     mtConfirmation,TMsgDlgButtons() << mbYes<< mbNo,0) == mrYes)
    {
      ShowMessage("���� ����� �����������");
     }
   else goto m1;
  }

     //  for(n = 0;n<2801;n++)
 //   fwrite(&P[n],sizeof(P[n]),1,tr);
   m_my=1; /*1-�� ������*/

  for(n_it=0;n_it<=7;n_it++) /* ����� ��� 53 ������ 0--3; ��� ������ 2: 4--7 */
   {
   NIT=n_it;
   for(n_p=0;n_p<=1;n_p++) /* ��� - 0, ��� - 1 */
    {
      NP=n_p;

     if(n_it<=3) goto m_ne_read;  /* ���� ������ 53, �� ���� �� ������  (����� 0) */
  //   if((n_it>3)&&(n_it!=4)) goto m_ne_read;  /* ���� ������ 2 (����� 1-��� �����), �� ���� �� ������ (����� 0) */
      if((n_it>3)&&(n_p==1)) goto m_ne_read;  /* ���� ������ 2 � ���,  �� �� ������  (����� 0)*/

//===================������ �� ������ zps_1_53.mrt,..., pps_1_2.mrt, ...pps_4_2.mrt=============================

    if(n_it<=3){n_vhod=n_it;lit=1;}  /*  ��� 53-� ������: ����� 1,2,3,4; */
    if(n_it>3){n_vhod=n_it-3;lit=0;} /* ��� 2-� ������: ����� 1,2,3,4;*/
    if(chten_mrt(n_vhod,n_p,lit)==1) goto m_CRC;

    m_ne_read:;
  //=============================================================================
     for(n_l=0;n_l<=7;n_l++) /* ����� ���� ��� 53 ������ 0--7; ��� ������ 2:  0--3 (���) 4-- 7 (���)*/
      {
       NL=n_l;
       //===============================================
        n=0; /* ����� ��������� ����� � �������� ����� 0--63 (������ 2); 0--159(������ 53) */
       //==============================================
       for(n_n=0;n_n<=31;n_n++)/* ��� ������ ������ �� */
        {
         Nn=n_n;
         for(n_fpch=0;n_fpch<=7;n_fpch++)  /* 8 ����� ������ ������ */
          {
            for(ns=0;ns<=3;ns++)
               {
                NS=ns; /* ����� ����� */
            if((n_it<=3)&&(NP==0)){//fprintf(tr,"%d\n",dan_0_all);   /* ��� 53 ������ ��� ����� ������ */
                                    fwrite(&dan_0_all, 2, 1, tr);
                                    goto end_f;}
            if((n_it<=3)&&(NP==1)){//fprintf(tr,"%d\n",dan_0_all);   /* ��� 53 ������ ��� ����� ������ */
                                    fwrite(&dan_0_all, 2, 1, tr);
                                    goto end_f;}

      //       if(n_it<=3){       /* ��� 53 ������ ���  � ��� */
      //               if((n_n<=7)||(n_n>27)){//fprintf(tr,"%d\n",dan_0_all);  /*��� ��������� ����� */; /*����� 0 !!!!�� �� ������� */
      //                     fwrite(&dan_0_all, 2, 1, tr);  /*��� ��������� ����� */
      //                     goto end_f;
      //                   }
      //  AT1[0]=AT_1_53[n_l][n]&0x1; //n=[8*Nn+n_fpch]
      //  AT1[1]=(AT_1_53[n_l][n]>>1)&0x1;
      //  AT1[2]=(AT_1_53[n_l][n]>>2)&0x1;
      //  AT1[3]=(AT_1_53[n_l][n]>>3)&0x1;

      //  AT2[0]=AT_2_53[n_l][n]&0x1;
       // AT2[1]=(AT_2_53[n_l][n]>>1)&0x1;
       // AT2[2]=(AT_2_53[n_l][n]>>2)&0x1;
       // AT2[3]=(AT_2_53[n_l][n]>>3)&0x1;

        // AT3[0]=AT_3_53[n_l][n]&0x1;
        // AT3[1]=(AT_3_53[n_l][n]>>1)&0x1;
        // AT3[2]=(AT_3_53[n_l][n]>>2)&0x1;
        // AT3[3]=(AT_3_53[n_l][n]>>3)&0x1;

        // AT4[0]=AT_4_53[n_l][n]&0x1;
        // AT4[1]=(AT_4_53[n_l][n]>>1)&0x1;
        // AT4[2]=(AT_4_53[n_l][n]>>2)&0x1;
        // AT4[3]=(AT_4_53[n_l][n]>>3)&0x1;

        //AT5[0]=AT_5_53[n_l][n]&0x1;
        //AT5[1]=(AT_5_53[n_l][n]>>1)&0x1;
        //AT5[2]=(AT_5_53[n_l][n]>>2)&0x1;
        //AT5[3]=(AT_5_53[n_l][n]>>3)&0x1;

        //AT6[0]=AT_6_53[n_l][n]&0x1;
        //AT6[1]=(AT_6_53[n_l][n]>>1)&0x1;
        //AT6[2]=(AT_6_53[n_l][n]>>2)&0x1;
        //AT6[3]=(AT_6_53[n_l][n]>>3)&0x1;

        //AT7[0]=AT_7_53[n_l][n]&0x1;
        //AT7[1]=(AT_7_53[n_l][n]>>1)&0x1;
        //AT7[2]=(AT_7_53[n_l][n]>>2)&0x1;
        //AT7[3]=(AT_7[n_l][n]>>3)&0x1;

        //AT8[0]=AT_8_53[n_l][n]&0x1;
        //AT8[1]=(AT_8_53[n_l][n]>>1)&0x1;
        //AT8[2]=(AT_8_53[n_l][n]>>2)&0x1;
        //AT8[3]=(AT_8_53[n_l][n]>>3)&0x1;

        //AT9[0]=AT_9_53[n_l][n]&0x1;
        //AT9[1]=(AT_9_53[n_l][n]>>1)&0x1;
        //AT9[2]=(AT_9_53[n_l][n]>>2)&0x1;
        //AT9[3]=(AT_9_53[n_l][n]>>3)&0x1;

        //AT10[0]=AT_10_53[n_l][n]&0x1;
        //AT10[1]=(AT_10_53[n_l][n]>>1)&0x1;
        //AT10[2]=(AT_10_53[n_l][n]>>2)&0x1;
        //AT10[3]=(AT_10_53[n_l][n]>>3)&0x1;

        //AT11[0]=AT_11_53[n_l][n]&0x1;
        //AT11[1]=(AT_11_53[n_l][n]>>1)&0x1;
        //AT11[2]=(AT_11_53[n_l][n]>>2)&0x1;
        //AT11[3]=(AT_11_53[n_l][n]>>3)&0x1;

        //AT12[0]=AT_12_53[n_l][n]&0x1;
        //AT12[1]=(AT_12_53[n_l][n]>>1)&0x1;
        //AT12[2]=(AT_12_53[n_l][n]>>2)&0x1;
        //AT12[3]=(AT_12_53[n_l][n]>>3)&0x1;

        //AT13[0]=0x0;
        //AT13[1]=0x0;
        //AT13[2]=0x0;
        //AT13[3]=0x0;

      // /* AT13[0]=AT_13_53[n_l][n]&0x1;
      //  AT13[1]=(AT_13_53[n_l][n]>>1)&0x1;
      //  AT13[2]=(AT_13_53[n_l][n]>>2)&0x1;
      //  AT13[3]=(AT_13_53[n_l][n]>>3)&0x1;
      //  */
       // INAT[0]=IN_AT_53[n_l][n]&0x1;  /* ������� ���. ���������������� ����� */
       // INAT[1]=(IN_AT_53[n_l][n]>>1)&0x1;
       // INAT[2]=(IN_AT_53[n_l][n]>>2)&0x1;
       // INAT[3]=(IN_AT_53[n_l][n]>>3)&0x1;
       // INAT[4]=(IN_AT_53[n_l][n]>>4)&0x1;

    //if(ns==0)
    //   {
    //   dan_0_ml= AT1[0]|AT1[1]<<1|AT1[2]<<2|AT1[3]<<3|AT2[0]<<4|AT2[1]<<5|AT2[2]<<6|AT2[3]<<7;
    //   dan_0_st= AT3[0]|AT3[1]<<1|AT3[2]<<2|AT3[3]<<3|AT4[0]<<4|AT4[1]<<5|AT4[2]<<6|AT4[3]<<7;
    //   dan_0=(dan_0_ml|dan_0_st<<8)&0xffff;

     // // fprintf(tr,"%d\n",dan_0);  /*��� ��������� ����� */
     //  fwrite(&dan_0, 2, 1, tr);
     //   }
    //if(ns==1)
    //  {

    //dan_1_ml = AT5[0]|AT5[1]<<1|AT5[2]<<2|AT5[3]<<3|AT6[0]<<4|AT6[1]<<5|AT6[2]<<6|AT6[3]<<7;
    //dan_1_st = AT7[0]|AT7[1]<<1|AT7[2]<<2|AT7[3]<<3|AT8[0]<<4|AT8[1]<<5|AT8[2]<<6|AT8[3]<<7;
    //    dan_1=(dan_1_ml|dan_1_st<<8)&0xffff;

    //   // fprintf(tr,"%d\n",dan_1);/*��� ��������� ����� */
    //    fwrite(&dan_1, 2, 1, tr);
    // }

    // if(ns==2)
    //  {
    // dan_2_ml = AT9[0]|AT9[1]<<1|AT9[2]<<2|AT9[3]<<3|AT10[0]<<4|AT10[1]<<5|AT10[2]<<6|AT10[3]<<7;
    // dan_2_st = AT11[0]|AT11[1]<<1|AT11[2]<<2|AT11[3]<<3|AT12[0]<<4|AT12[1]<<5|AT12[2]<<6|AT12[3]<<7;

     //   dan_2=(dan_2_ml|dan_2_st<<8)&0xffff;

      // // fprintf(tr,"%d\n",dan_2);    /*��� ��������� ����� */
       // fwrite(&dan_2, 2, 1, tr);
      // }

    // if(ns==3)
    //   {
    //    dan_3_ml = AT13[0]|AT13[1]<<1|AT13[2]<<2|AT13[3]<<3;
    //    dan_3_st = INAT[0]|INAT[1]<<1|INAT[2]<<2|INAT[3]<<3|INAT[4]<<4;

    //    dan_3=(dan_3_ml|dan_3_st<<8)&0xffff;

    //    // fprintf(tr,"%d\n",dan_3);  /* ������ ���� �������� ���*/ /*��� ��������� ����� */
    //    fwrite(&dan_3, 2, 1, tr);
    //   }
    //  n=n+1;
    // } /* end ��� ������ 53 ��� � ���*/

    //31.05.11!!!    if((n_it>3)&&(n_it!=4)&&(NP==0)){//fprintf(tr,"%d\n",dan_0_all);   /* ��� 2 ������ ��� ��� ����� ����� 1-��, ������!!!*/
    //31.05.11!!!                                 fwrite(&dan_0_all, 2, 1, tr);
     //31.05.11!!!                                goto end_f;} /* ��� 2 ������ ��� */

      //31.05.11!!!       if((n_it==4)&&(NP==0)) /* ��� 2 ������ ��� ������ 1-� ���� */
       //31.05.11!!!         {
        //31.05.11!!!          if(n_n>7){//fprintf(tr,"%d\n",dan_0_all);  /*��� ��������� ����� */; /*����� 0 !!!!�� �� ������� */
         //31.05.11!!!                   fwrite(&dan_0_all, 2, 1, tr);  /*��� ��������� ����� */
          //31.05.11!!!                  goto end_f;
           //31.05.11!!!               }
             //31.05.11!!!     if(n_l>3){// fprintf(tr,"%d\n",dan_0_all); /*����� 0 !!!! �� �� ���� */
              //31.05.11!!!                fwrite(&dan_0_all, 2, 1, tr);  /*��� ��������� ����� */
               //31.05.11!!!              goto end_f;
                 //31.05.11!!!         }

         if((n_it>3)&&(NP==0)){   /* ��� 2 ������ ��� ��� ����� */

                         if(n_n>7) {//fprintf(tr,"%d\n",dan_0_all);  /*��� ��������� ����� */; /*����� 0 !!!!�� �� ������� */
                          fwrite(&dan_0_all, 2, 1, tr);  /*��� ��������� ����� */
                          goto end_f;
                                 }
          if(n_l>3){// fprintf(tr,"%d\n",dan_0_all); /*����� 0 !!!! �� �� ���� */
                         fwrite(&dan_0_all, 2, 1, tr);  /*��� ��������� ����� */
                            goto end_f;
                    }
        AT1[0]=AT_1[n_l][n]&0x1; //n=[8*Nn+n_fpch]
        AT1[1]=(AT_1[n_l][n]>>1)&0x1;
        AT1[2]=(AT_1[n_l][n]>>2)&0x1;
        AT1[3]=(AT_1[n_l][n]>>3)&0x1;

        AT2[0]=AT_2[n_l][n]&0x1;
        AT2[1]=(AT_2[n_l][n]>>1)&0x1;
        AT2[2]=(AT_2[n_l][n]>>2)&0x1;
        AT2[3]=(AT_2[n_l][n]>>3)&0x1;

        AT3[0]=AT_3[n_l][n]&0x1;
        AT3[1]=(AT_3[n_l][n]>>1)&0x1;
        AT3[2]=(AT_3[n_l][n]>>2)&0x1;
        AT3[3]=(AT_3[n_l][n]>>3)&0x1;

        AT4[0]=AT_4[n_l][n]&0x1;
        AT4[1]=(AT_4[n_l][n]>>1)&0x1;
        AT4[2]=(AT_4[n_l][n]>>2)&0x1;
        AT4[3]=(AT_4[n_l][n]>>3)&0x1;

        AT5[0]=AT_5[n_l][n]&0x1;
        AT5[1]=(AT_5[n_l][n]>>1)&0x1;
        AT5[2]=(AT_5[n_l][n]>>2)&0x1;
        AT5[3]=(AT_5[n_l][n]>>3)&0x1;

        AT6[0]=AT_6[n_l][n]&0x1;
        AT6[1]=(AT_6[n_l][n]>>1)&0x1;
        AT6[2]=(AT_6[n_l][n]>>2)&0x1;
        AT6[3]=(AT_6[n_l][n]>>3)&0x1;

        AT7[0]=AT_7[n_l][n]&0x1;
        AT7[1]=(AT_7[n_l][n]>>1)&0x1;
        AT7[2]=(AT_7[n_l][n]>>2)&0x1;
        AT7[3]=(AT_7[n_l][n]>>3)&0x1;

        AT8[0]=AT_8[n_l][n]&0x1;
        AT8[1]=(AT_8[n_l][n]>>1)&0x1;
        AT8[2]=(AT_8[n_l][n]>>2)&0x1;
        AT8[3]=(AT_8[n_l][n]>>3)&0x1;

        AT9[0]=AT_9[n_l][n]&0x1;
        AT9[1]=(AT_9[n_l][n]>>1)&0x1;
        AT9[2]=(AT_9[n_l][n]>>2)&0x1;
        AT9[3]=(AT_9[n_l][n]>>3)&0x1;

        AT10[0]=AT_10[n_l][n]&0x1;
        AT10[1]=(AT_10[n_l][n]>>1)&0x1;
        AT10[2]=(AT_10[n_l][n]>>2)&0x1;
        AT10[3]=(AT_10[n_l][n]>>3)&0x1;

        AT11[0]=AT_11[n_l][n]&0x1;
        AT11[1]=(AT_11[n_l][n]>>1)&0x1;
        AT11[2]=(AT_11[n_l][n]>>2)&0x1;
        AT11[3]=(AT_11[n_l][n]>>3)&0x1;

        AT12[0]=AT_12[n_l][n]&0x1;
        AT12[1]=(AT_12[n_l][n]>>1)&0x1;
        AT12[2]=(AT_12[n_l][n]>>2)&0x1;
        AT12[3]=(AT_12[n_l][n]>>3)&0x1;

        AT13[0]=AT_13[n_l][n]&0x1;
        AT13[1]=(AT_13[n_l][n]>>1)&0x1;
        AT13[2]=(AT_13[n_l][n]>>2)&0x1;
        AT13[3]=(AT_13[n_l][n]>>3)&0x1;

        INAT[0]=IN_AT[n_l][n]&0x1;  /* ������� ���. ���������������� ����� */
        INAT[1]=(IN_AT[n_l][n]>>1)&0x1;
        INAT[2]=(IN_AT[n_l][n]>>2)&0x1;
        INAT[3]=(IN_AT[n_l][n]>>3)&0x1;
        INAT[4]=(IN_AT[n_l][n]>>4)&0x1;

    if(ns==0)
       {
       dan_0_ml= AT1[0]|AT1[1]<<1|AT1[2]<<2|AT1[3]<<3|AT2[0]<<4|AT2[1]<<5|AT2[2]<<6|AT2[3]<<7;
       dan_0_st= AT3[0]|AT3[1]<<1|AT3[2]<<2|AT3[3]<<3|AT4[0]<<4|AT4[1]<<5|AT4[2]<<6|AT4[3]<<7;
       dan_0=(dan_0_ml|dan_0_st<<8)&0xffff;

     // fprintf(tr,"%d\n",dan_0);  /*��� ��������� ����� */
       fwrite(&dan_0, 2, 1, tr);
        }
    if(ns==1)
      {

    dan_1_ml = AT5[0]|AT5[1]<<1|AT5[2]<<2|AT5[3]<<3|AT6[0]<<4|AT6[1]<<5|AT6[2]<<6|AT6[3]<<7;
    dan_1_st = AT7[0]|AT7[1]<<1|AT7[2]<<2|AT7[3]<<3|AT8[0]<<4|AT8[1]<<5|AT8[2]<<6|AT8[3]<<7;
        dan_1=(dan_1_ml|dan_1_st<<8)&0xffff;

       // fprintf(tr,"%d\n",dan_1);/*��� ��������� ����� */
        fwrite(&dan_1, 2, 1, tr);
     }

    if(ns==2)
      {
    dan_2_ml = AT9[0]|AT9[1]<<1|AT9[2]<<2|AT9[3]<<3|AT10[0]<<4|AT10[1]<<5|AT10[2]<<6|AT10[3]<<7;
    dan_2_st = AT11[0]|AT11[1]<<1|AT11[2]<<2|AT11[3]<<3|AT12[0]<<4|AT12[1]<<5|AT12[2]<<6|AT12[3]<<7;

        dan_2=(dan_2_ml|dan_2_st<<8)&0xffff;

      // fprintf(tr,"%d\n",dan_2);    /*��� ��������� ����� */
       fwrite(&dan_2, 2, 1, tr);
      }

    if(ns==3)
       {
        dan_3_ml = AT13[0]|AT13[1]<<1|AT13[2]<<2|AT13[3]<<3;
        dan_3_st = INAT[0]|INAT[1]<<1|INAT[2]<<2|INAT[3]<<3|INAT[4]<<4;

        dan_3=(dan_3_ml|dan_3_st<<8)&0xffff;

        // fprintf(tr,"%d\n",dan_3);  /* ������ ���� �������� ���*/ /*��� ��������� ����� */
        fwrite(&dan_3, 2, 1, tr);
       }
    if(ns==3)  n=n+1;
  } /*  end ��� 2 ������*/

       if((n_it>3)&&(NP==1)){//fprintf(tr,"%d\n",dan_0_all);   /* ��� 2 ������ ��� ��� �����: ��� ������ ��� ��� ������ 2, ����� ������!!!*/
                                    fwrite(&dan_0_all, 2, 1, tr);
                                    goto end_f; } /* ��� 2 ������ ��� */

    //   if((n_it>3)&&(NP==1))     /* ��� 2 ������ ��� ��� ����� */
    //           {
    //           if(n_n>7){//fprintf(tr,"%d\n",dan_0_all);  /*��� ��������� ����� */; /*����� 0 !!!!�� �� ������� */
    //                     fwrite(&dan_0_all, 2, 1, tr);  /*��� ��������� ����� */
    //                       goto end_f;
    //                     }
    //             if(n_l<=3){// fprintf(tr,"%d\n",dan_0_all); /*����� 0 !!!! �� �� ���� */
    //                         fwrite(&dan_0_all, 2, 1, tr);  /*��� ��������� ����� */
    //                         goto end_f;
    //                     }
    //           /*  k=n_l-4;  ��� 2 ������ ��� ���� 4,5,6,7 */
    //    AT1[0]=AT_1[n_l-4][n]&0x1; //n=[8*Nn+n_fpch]
    //    AT1[1]=(AT_1[n_l-4][n]>>1)&0x1;
    //    AT1[2]=(AT_1[n_l-4][n]>>2)&0x1;
    //    AT1[3]=(AT_1[n_l-4][n]>>3)&0x1;

     //   AT2[0]=AT_2[n_l-4][n]&0x1;
     //   AT2[1]=(AT_2[n_l-4][n]>>1)&0x1;
     //   AT2[2]=(AT_2[n_l-4][n]>>2)&0x1;
     //   AT2[3]=(AT_2[n_l-4][n]>>3)&0x1;

     //   AT3[0]=AT_3[n_l-4][n]&0x1;
     //   AT3[1]=(AT_3[n_l-4][n]>>1)&0x1;
     //   AT3[2]=(AT_3[n_l-4][n]>>2)&0x1;
     //   AT3[3]=(AT_3[n_l-4][n]>>3)&0x1;

     //   AT4[0]=AT_4[n_l-4][n]&0x1;
     //   AT4[1]=(AT_4[n_l-4][n]>>1)&0x1;
     //   AT4[2]=(AT_4[n_l-4][n]>>2)&0x1;
     //   AT4[3]=(AT_4[n_l-4][n]>>3)&0x1;

     //   AT5[0]=AT_5[n_l-4][n]&0x1;
     //   AT5[1]=(AT_5[n_l-4][n]>>1)&0x1;
     //   AT5[2]=(AT_5[n_l-4][n]>>2)&0x1;
     //   AT5[3]=(AT_5[n_l-4][n]>>3)&0x1;

     //   AT6[0]=AT_6[n_l-4][n]&0x1;
     //   AT6[1]=(AT_6[n_l-4][n]>>1)&0x1;
     //   AT6[2]=(AT_6[n_l-4][n]>>2)&0x1;
     //   AT6[3]=(AT_6[n_l-4][n]>>3)&0x1;

      //  AT7[0]=AT_7[n_l-4][n]&0x1;
      //  AT7[1]=(AT_7[n_l-4][n]>>1)&0x1;
      //  AT7[2]=(AT_7[n_l-4][n]>>2)&0x1;
      //  AT7[3]=(AT_7[n_l-4][n]>>3)&0x1;

      //  AT8[0]=AT_8[n_l-4][n]&0x1;
      //  AT8[1]=(AT_8[n_l-4][n]>>1)&0x1;
      //  AT8[2]=(AT_8[n_l-4][n]>>2)&0x1;
      //  AT8[3]=(AT_8[n_l-4][n]>>3)&0x1;

      //  AT9[0]=AT_9[n_l-4][n]&0x1;
      //  AT9[1]=(AT_9[n_l-4][n]>>1)&0x1;
      //  AT9[2]=(AT_9[n_l-4][n]>>2)&0x1;
      //  AT9[3]=(AT_9[n_l-4][n]>>3)&0x1;

      //  AT10[0]=AT_10[n_l-4][n]&0x1;
      //  AT10[1]=(AT_10[n_l-4][n]>>1)&0x1;
      //  AT10[2]=(AT_10[n_l-4][n]>>2)&0x1;
      //  AT10[3]=(AT_10[n_l-4][n]>>3)&0x1;

      //  AT11[0]=AT_11[n_l-4][n]&0x1;
      //  AT11[1]=(AT_11[n_l-4][n]>>1)&0x1;
      //  AT11[2]=(AT_11[n_l-4][n]>>2)&0x1;
      // AT11[3]=(AT_11[n_l-4][n]>>3)&0x1;

      //  AT12[0]=AT_12[n_l-4][n]&0x1;
      //  AT12[1]=(AT_12[n_l-4][n]>>1)&0x1;
      //  AT12[2]=(AT_12[n_l-4][n]>>2)&0x1;
      //  AT12[3]=(AT_12[n_l-4][n]>>3)&0x1;

      //  AT13[0]=AT_13[n_l-4][n]&0x1;
      //  AT13[1]=(AT_13[n_l-4][n]>>1)&0x1;
      //  AT13[2]=(AT_13[n_l-4][n]>>2)&0x1;
      //  AT13[3]=(AT_13[n_l-4][n]>>3)&0x1;

      //  INAT[0]=IN_AT[n_l-4][n]&0x1;  /* ������� ���. ���������������� ����� */
      //  INAT[1]=(IN_AT[n_l-4][n]>>1)&0x1;
      //  INAT[2]=(IN_AT[n_l-4][n]>>2)&0x1;
      //  INAT[3]=(IN_AT[n_l-4][n]>>3)&0x1;
      //  INAT[4]=(IN_AT[n_l-4][n]>>4)&0x1;

   // if(ns==0)
   //    {
   //    dan_0_ml= AT1[0]|AT1[1]<<1|AT1[2]<<2|AT1[3]<<3|AT2[0]<<4|AT2[1]<<5|AT2[2]<<6|AT2[3]<<7;
   //    dan_0_st= AT3[0]|AT3[1]<<1|AT3[2]<<2|AT3[3]<<3|AT4[0]<<4|AT4[1]<<5|AT4[2]<<6|AT4[3]<<7;
   //    dan_0=(dan_0_ml|dan_0_st<<8)&0xffff;

   //  // fprintf(tr,"%d\n",dan_0);  /*��� ��������� ����� */
   //    fwrite(&dan_0, 2, 1, tr);
   //     }
   // if(ns==1)
   //   {
   // dan_1_ml = AT5[0]|AT5[1]<<1|AT5[2]<<2|AT5[3]<<3|AT6[0]<<4|AT6[1]<<5|AT6[2]<<6|AT6[3]<<7;
   // dan_1_st = AT7[0]|AT7[1]<<1|AT7[2]<<2|AT7[3]<<3|AT8[0]<<4|AT8[1]<<5|AT8[2]<<6|AT8[3]<<7;
   //     dan_1=(dan_1_ml|dan_1_st<<8)&0xffff;

  //     // fprintf(tr,"%d\n",dan_1);/*��� ��������� ����� */
   //     fwrite(&dan_1, 2, 1, tr);
   //  }

   // if(ns==2)
   //   {
   // dan_2_ml = AT9[0]|AT9[1]<<1|AT9[2]<<2|AT9[3]<<3|AT10[0]<<4|AT10[1]<<5|AT10[2]<<6|AT10[3]<<7;
  //  dan_2_st = AT11[0]|AT11[1]<<1|AT11[2]<<2|AT11[3]<<3|AT12[0]<<4|AT12[1]<<5|AT12[2]<<6|AT12[3]<<7;

  //  dan_2=(dan_2_ml|dan_2_st<<8)&0xffff;

  //    // fprintf(tr,"%d\n",dan_2);    /*��� ��������� ����� */
  //     fwrite(&dan_2, 2, 1, tr);
  //    }

  //  if(ns==3)
  //     {
  //      dan_3_ml = AT13[0]|AT13[1]<<1|AT13[2]<<2|AT13[3]<<3;
  //      dan_3_st = INAT[0]|INAT[1]<<1|INAT[2]<<2|INAT[3]<<3|INAT[4]<<4;

  //      dan_3=(dan_3_ml|dan_3_st<<8)&0xffff;

   //     // fprintf(tr,"%d\n",dan_3);  /* ������ ���� �������� ���*/ /*��� ��������� ����� */
   //     fwrite(&dan_3, 2, 1, tr);
   //    }
   //   n=n+1;
   //   }   /*  end ��� 2 ������*/

          end_f:;
          if(m_my==131071) goto m_CRC;
          m_my=m_my+1;
           }/* ns*/
          }  /* n_fpch */
        }   /*n_n*/
      }    /*n_l */
    }    /*n_p */
  }    /* n_it*/

  m_CRC:;
   fclose(tr);

 //  str1="mrt.102"; /* ���� str1=E_f->Text;  �� �������������� ���� */
   str1=E_f->Text;
   tr_dan = fopen(str1.c_str(), "rb");      /* mrt.000 -������� ����,*/
   if (!tr_dan){
      ShowMessage("�� ���� ������� ���� �� ������!");
      return;
   }

  cnt = FileSize(tr_dan);
  crc = GetCRC(tr_dan, cnt); /* ��������� ����������� ����� */
  cnt >>= 1;   //���-�� 16�� ����. ����
  fclose(tr_dan);

 m1:;
}
//==============������ ������ ����� ����������� ��������� =========================
int Results_zap(char* ErrorMsg)
{
   // sprintf(MsgBuffer, ErrorMsg);
   //   if(Application->MessageBox(MsgBuffer,
   //         "������������� ������ ����������� ���������",MB_OKCANCEL+MB_ICONINFORMATION)==IDCANCEL)
   //           {
   //          //  ShowMessage("����� ������");
   //            return 1; /* �������� */
   //            }
    return 0;  /* ���������� */
}

//============== ������ ����� ������� =========================
void  TForm1::zapis_tabl_my(int nus)
{
 FILE *tr;
 String str;
 int k,j,n_us;
// int kod_fpch;
 float P_izm[13][4][64]={0.0},osl[13][4][64]={0.0};
 int kad_acp[13][4][64]={0},k_f[64]={0};

 str=E_fd->Text;

if((tr = fopen(str.c_str(),"r+")) == NULL)
  {
  ShowMessage("��� �����");
  goto m1;
 }

  /* ������� ������ �� ����� */

   for(n_us=0;n_us<=12;n_us++)
    {
     for(k=0;k<=63;k++)
       {
        fscanf(tr,"%d",&k_f[k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][0][k],&osl[n_us][0][k], &kad_acp[n_us][0][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][1][k],&osl[n_us][1][k], &kad_acp[n_us][1][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][2][k],&osl[n_us][2][k], &kad_acp[n_us][2][k]);
        fscanf(tr,"%f%f%d\n",&P_izm[n_us][3][k],&osl[n_us][3][k],&kad_acp[n_us][3][k]);
      } /* end k*/
    } /* end n_us */
   fclose(tr);

 if(MessageDlg("������������ ����?",
     mtConfirmation,TMsgDlgButtons() << mbYes<< mbNo,0) == mrYes)
    {
      ShowMessage("���� ����� �����������");
    }
   else goto m1;

 if((tr = fopen(str.c_str(),"w+")) == NULL)
  {
  ShowMessage("��� �����");
  goto m1;
  }

 for(n_us=0;n_us<=12;n_us++)
  {
    if(n_us==nus)
     {
      /* ������ � ���� */
     for(k=0;k<=63;k++)    /* ������  */
       {
        fprintf(tr,"%d ",k);
          for(j=1;j<=10;j=j+3)   /* �������  */
           {
             if((j+2)==12)
              {
              fprintf(tr,"%.2f %.2f %d\n",atof((SG_9->Cells[j][k]).c_str()),
               atof((SG_9->Cells[j+1][k]).c_str()),atoi((SG_9->Cells[j+2][k]).c_str()));
              }
            else
              fprintf(tr,"%.2f %.2f %d ",atof((SG_9->Cells[j][k]).c_str()),
               atof((SG_9->Cells[j+1][k]).c_str()),atoi((SG_9->Cells[j+2][k]).c_str()));
          }
       }   /*  end for*/
   }  /* if n_us==nus */
    else
     {
      for(k=0;k<=63;k++) /* ������ � ���� ��������� ����������*/
       {
        fprintf(tr,"%d ",k);
         fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][0][k],osl[n_us][0][k],kad_acp[n_us][0][k]);
         fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][1][k],osl[n_us][1][k],kad_acp[n_us][1][k]);
         fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][2][k],osl[n_us][2][k],kad_acp[n_us][2][k]);
         fprintf(tr,"%.2f %.2f %d\n",P_izm[n_us][3][k],osl[n_us][3][k],kad_acp[n_us][3][k]);
        }  /* end k*/
     } /*  else*/

    if(n_us==12)   fclose(tr);
  } /* end n_us*/

 m1:;
}
//================== ������������ ����� ��� (���������) =======================
void __fastcall TForm1::B2_mrtClick(TObject *Sender)
{
   FILE *tr;
 String str;
 int k,j,n_us,k1,k2,nl;//k_max_mod;
// int kod_fpch;
 float P_izm[13][4][64]={0.0},osl[13][4][64]={0.0};
 int kad_acp[13][4][64]={0},k_f[64]={0};
 // unsigned NIT;

 float P_izm_mod[13]={0.0}; /* ������ ��� ������ � ���� */
  float P_in_att=0.0;
  float P_max_mod=0.0;

  float dP_osl_0[4][64]={0.0},dP_osl_1[4][64]={0.0},dP_osl_2[4][64]={0.0},
        dP_osl_3[4][64]={0.0},dP_osl_4[4][64]={0.0},dP_osl_5[4][64]={0.0},
        dP_osl_6[4][64]={0.0},dP_osl_7[4][64]={0.0},dP_osl_8[4][64]={0.0},
        dP_osl_9[4][64]={0.0},dP_osl_10[4][64]={0.0},dP_osl_11[4][64]={0.0},
        dP_osl_12[4][64]={0.0};

//  if(CB_3_vh->ItemIndex==0){NIT=4;}  /* ���� 1-2 */
//  if(CB_3_vh->ItemIndex==1){NIT=5;}  /* ���� 2-2 */
//  if(CB_3_vh->ItemIndex==2){NIT=6;}  /* ���� 3-2 */
//  if(CB_3_vh->ItemIndex==3){NIT=7;}  /* ���� 4-2 */


   str=E_fd->Text;     /* ��� ��������������� ����� */

if((tr = fopen(str.c_str(),"r+")) == NULL)
  {
  ShowMessage("��� �����");
  goto m1;
 }

  /* ������� ������ �� ����� */

   for(n_us=0;n_us<=12;n_us++)
    {
     for(k=0;k<=63;k++)
       {
        fscanf(tr,"%d",&k_f[k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][0][k],&osl[n_us][0][k], &kad_acp[n_us][0][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][1][k],&osl[n_us][1][k], &kad_acp[n_us][1][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][2][k],&osl[n_us][2][k], &kad_acp[n_us][2][k]);
        fscanf(tr,"%f%f%d\n",&P_izm[n_us][3][k],&osl[n_us][3][k],&kad_acp[n_us][3][k]);
      } /* end k*/
    } /* end n_us */
   fclose(tr);

   if(MessageDlg("������������ ���� ���?",
     mtConfirmation,TMsgDlgButtons() << mbYes<< mbNo,0) == mrYes)
    {
      ShowMessage("���� ����� �����������");
    }
   else goto m1;

//   str="pps_1_2.mrt";
   str=E_mrt->Text;    /* ��� ���������� ����� ��� */
 if((tr = fopen(str.c_str(),"w+")) == NULL)
  {
  ShowMessage("��� �����");
  goto m1;
 }

 for(nl=0;nl<=3;nl++)   /* ���� �� ������ ����*/
  {
  for(k=0; k<=63; k++) /* �� �������*/
   {

    P_izm_mod[0]=osl[0][nl][k];
    P_izm_mod[1]=osl[1][nl][k];
    P_izm_mod[2]=osl[2][nl][k];
    P_izm_mod[3]=osl[3][nl][k];
    P_izm_mod[4]=osl[4][nl][k];
    P_izm_mod[5]=osl[5][nl][k];
    P_izm_mod[6]=osl[6][nl][k];
    P_izm_mod[7]=osl[7][nl][k];
    P_izm_mod[8]=osl[8][nl][k];
    P_izm_mod[9]=osl[9][nl][k];
    P_izm_mod[10]=osl[10][nl][k];
    P_izm_mod[11]=osl[11][nl][k];
    P_izm_mod[12]=osl[12][nl][k];

   for(k1=0,P_max_mod=P_izm_mod[0]; k1<=12; k1+=1)
       {
       if(P_izm_mod[k1]>P_max_mod) {P_max_mod=P_izm_mod[k1];}//k_max_mod=k1;}  /* max �������� � ����� ����� ��������� */
       }

      P_in_att=P_max_mod;

     dP_osl_0[nl][k]=P_izm_mod[0]-P_max_mod;
     dP_osl_1[nl][k]=P_izm_mod[1]-P_max_mod;
     dP_osl_2[nl][k]=P_izm_mod[2]-P_max_mod;
     dP_osl_3[nl][k]=P_izm_mod[3]-P_max_mod;
     dP_osl_4[nl][k]=P_izm_mod[4]-P_max_mod;
     dP_osl_5[nl][k]=P_izm_mod[5]-P_max_mod;
     dP_osl_6[nl][k]=P_izm_mod[6]-P_max_mod;
     dP_osl_7[nl][k]=P_izm_mod[7]-P_max_mod;
     dP_osl_8[nl][k]=P_izm_mod[8]-P_max_mod;
     dP_osl_9[nl][k]=P_izm_mod[9]-P_max_mod;
     dP_osl_10[nl][k]=P_izm_mod[10]-P_max_mod;
     dP_osl_11[nl][k]=P_izm_mod[11]-P_max_mod;
     dP_osl_12[nl][k]=P_izm_mod[12]-P_max_mod;


        fprintf(tr,"%d ",k);
         fprintf(tr,"%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",P_in_att,dP_osl_0[nl][k],
                 dP_osl_1[nl][k],dP_osl_2[nl][k],dP_osl_3[nl][k],dP_osl_4[nl][k],dP_osl_5[nl][k],dP_osl_6[nl][k],
                 dP_osl_7[nl][k],dP_osl_8[nl][k],dP_osl_9[nl][k],dP_osl_10[nl][k],dP_osl_11[nl][k],dP_osl_12[nl][k]);

       }  /* end k �� �������*/

}   /* end nl �� �����*/

   fclose(tr);

m1:;

}
//================== ������ �� ����� ��� (����������) ��������� �������� ���. ���, �������� �����. =======================
int TForm1::chten_mrt(int n_vhod,int ps,int lit)
{
 extern unsigned AT_1[4][64],AT_2[4][64],AT_3[4][64],AT_4[4][64],AT_5[4][64],AT_6[4][64],
        AT_7[4][64],AT_8[4][64],AT_9[4][64],AT_10[4][64],AT_11[4][64],
        AT_12[4][64],AT_13[4][64];  /* ����������� �������� ������. ����������� */
 extern unsigned IN_AT[4][64];  /* ���������� ���������� ����� */
 /* �������� ��� ������ 53 ������� AT_1_53,...,IN_AT_53 */
 extern unsigned AT_1_53[8][160],AT_2_53[8][160],AT_3_53[8][160],AT_4_53[8][160],
         AT_5_53[8][160],AT_6_53[8][160],AT_7_53[8][160],AT_8_53[8][160],
         AT_9_53[8][160],AT_10_53[8][160],AT_11_53[8][160],AT_12_53[8][160],
         AT_13_53[8][160];  /* ����������� �������� ������. ����������� ������ 53*/
 extern unsigned IN_AT_53[8][160];  /* ���������� ���������� ����� ������ 53*/

 unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 �������� 00000, 00001,00010,00100,01000,10000*/
 float Qvh_osl[32]={0.0,-0.75,-1.5,-2.25,-3.0,-3.75,-4.5,-5.25,-6.0,
                     -6.75,-7.5,-8.25,-9.0,-9.75,-10.5,-11.25,-12.0,
                     -12.75,-13.5,-14.25,-15.0,-15.75,-16.5,-17.25,-18.0,
                     -18.75,-19.5,-20.25,-21.0,-21.75,-22.5,-23.25};

                  /* 5 �������� 00000, 00001,00010,00100,01000,10000*/
/* float Qvh_osl[32]={-23.25,-22.5,-21.75,-21.0,-20.25,-19.5,-18.75,-18.0,
                     -17.25,-16.5,-15.75,-15.0,-14.25,-13.5,-12.75,-12.0,
                     -11.25,-10.5,-9.75,-9.0,-8.25,-7.5,-6.75,-6.0,-5.25,
                     -4.5,-3.75,-3.0,-2.25,-1.5,-0.75,0.0};
*/
                     /* 5 �������� 00000, 00001,00010,00100,01000,10000*/

//  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* �������� ��� 4 �������*/
  float Q_vh_zn[16]={0.0,-0.75,-1.5,-2.25,-3.0,-3.75,-4.5,-5.25,-6.0,
                     -6.75,-7.5,-8.25,-9.0,-9.75,-10.5,-11.25};     /* �������� ��� 4 �������*/



 FILE *tr;
 String str;
 int k,j,n_us,k1,k2,k_max_mod,nl,k_f;
 AnsiString SbS,SbL,StrDir,StIn,StNIn;
 AnsiString MyFileName;
// int kod_fpch;
// float P_izm[13][4][64]={0.0},osl[13][4][64]={0.0};
// int kad_acp[13][4][64]={0},k_f[64]={0};
 // unsigned NIT;

 //float P_izm_mod[13]={0.0}; /* ������ ��� ������ � ���� */
  float P_in_att[4][64]={0.0};
  float P_in_att_53[8][160]={0.0};
 // float P_max_mod=0.0;

  float dP_osl_0[4][64]={0.0},dP_osl_1[4][64]={0.0},dP_osl_2[4][64]={0.0},
        dP_osl_3[4][64]={0.0},dP_osl_4[4][64]={0.0},dP_osl_5[4][64]={0.0},
        dP_osl_6[4][64]={0.0},dP_osl_7[4][64]={0.0},dP_osl_8[4][64]={0.0},
        dP_osl_9[4][64]={0.0},dP_osl_10[4][64]={0.0},dP_osl_11[4][64]={0.0},
        dP_osl_12[4][64]={0.0};
      float a,b,c;
  float dP_osl_0_53[8][160]={0.0},dP_osl_1_53[8][160]={0.0},dP_osl_2_53[8][160]={0.0},
        dP_osl_3_53[8][160]={0.0},dP_osl_4_53[8][160]={0.0},dP_osl_5_53[8][160]={0.0},
        dP_osl_6_53[8][160]={0.0},dP_osl_7_53[8][160]={0.0},dP_osl_8_53[8][160]={0.0},
        dP_osl_9_53[8][160]={0.0},dP_osl_10_53[8][160]={0.0},dP_osl_11_53[8][160]={0.0};

//  if(n_vhod==1){NIT=4;}  /* ���� 1-2 � ����������� �� ������ ����� �������� ����*/
//  if(n_vhod==2){NIT=5;}  /* ���� 2-2 */
//  if(n_vhod==3){NIT=6;}  /* ���� 3-2 */
//  if(n_vhod==4){NIT=7;}  /* ���� 4-2 */

 //  str=E_fd->Text;     /* ��� ��������������� ����� */

  // n_vhod=4;

  if(n_vhod==1) StNIn="_1";
  if(n_vhod==2) StNIn="_2";
  if(n_vhod==3) StNIn="_3";
  if(n_vhod==4) StNIn="_4";

 if(ps==0)
 {
   SbS="pps";
  }
 else
  {
   SbS="zps";
  }
 if(lit==0) SbL="_2";
 else SbL="_53";

 StIn=SbS+StNIn+SbL+".mrt";
// MyFileName=StrDir+"\\PowMesh\\"+StIn;
 MyFileName=StIn;

if((tr = fopen(MyFileName.c_str(),"r+")) == NULL)
  {
  ShowMessage("��� �����"); return(1);
 // goto m1;
 }

 if(lit==0) /* ������� ������ �� ����� ��� ������ 2*/
 {
   for(nl=0;nl<=3;nl++)
    {
     for(k=0;k<=63;k++)
       {
         fscanf(tr,"%d",&k_f);
         fscanf(tr,"%f%f%f%f%f%f%f%f%f%f%f%f%f%f\n",&P_in_att[nl][k],&dP_osl_0[nl][k],
         &dP_osl_1[nl][k],&dP_osl_2[nl][k],&dP_osl_3[nl][k],&dP_osl_4[nl][k],&dP_osl_5[nl][k],&dP_osl_6[nl][k],
         &dP_osl_7[nl][k],&dP_osl_8[nl][k],&dP_osl_9[nl][k],&dP_osl_10[nl][k],&dP_osl_11[nl][k],&dP_osl_12[nl][k]);
       } /* end k*/
    } /* end nl */
   fclose(tr);

 for(nl=0;nl<=3;nl++)   /* ���� �� ������ ����*/       /* ��� ������ 53 8 ����� */
  {
  for(k=0; k<=63; k++) /* �� �������*/    /* ��� ������ 53 160 ��������� ����� */
   {

   for(k1=0; k1<=30; k1+=1)
       {
        /*a=P_in_att[nl][k]; b= Qvh_osl[k1]; c=Qvh_osl[k1+1];*/
     //   if(P_in_att[nl][k]==Qvh_osl[31-k1])
        if(P_in_att[nl][k]==Qvh_osl[k1])
        {
         IN_AT[nl][k]=Qv_vh[k1]; goto m_in_att;
        }
        /* ��� ������� ������� �����  ��� �������� ���*/
//       if((P_in_att[nl][k]<Qvh_osl[31-k1])&&(P_in_att[nl][k]>Qvh_osl[31-(k1+1)]))
     if((P_in_att[nl][k]<Qvh_osl[k1])&&(P_in_att[nl][k]>Qvh_osl[k1+1]))
        {
         IN_AT[nl][k]=Qv_vh[k1];goto m_in_att;
        }
        /* ��� ������� ������� �����  ��� �������� ���*/
       }
     m_in_att:;
     AT_1[nl][k]=0xF; AT_2[nl][k]=0xF;AT_3[nl][k]=0xF;
     AT_4[nl][k]=0xF; AT_5[nl][k]=0xF;AT_6[nl][k]=0xF;
     AT_7[nl][k]=0xF; AT_8[nl][k]=0xF;AT_9[nl][k]=0xF;
     AT_10[nl][k]=0xF;AT_11[nl][k]=0xF;AT_12[nl][k]=0xF;
     AT_13[nl][k]=0xF;

     for(k2=0;k2<=15;k2++)  /* ���������� ����� �������� ��� �� �� 16 ���������*/
      {
        if(dP_osl_0[nl][k]==Q_vh_zn[k2]) AT_1[nl][k]=k2;
         else
            {
             if(k2<15)
                {
                 if((dP_osl_0[nl][k]<Q_vh_zn[k2])&&(dP_osl_0[nl][k]>Q_vh_zn[k2+1]))
                      AT_1[nl][k]=k2;
                }
            }
         if(dP_osl_1[nl][k]==Q_vh_zn[k2]) AT_2[nl][k]=k2;
            else
            {
             if(k2<15)
                {
                 if((dP_osl_1[nl][k]<Q_vh_zn[k2])&&(dP_osl_1[nl][k]>Q_vh_zn[k2+1]))
                      AT_2[nl][k]=k2;
                }
            }
          if(dP_osl_2[nl][k]==Q_vh_zn[k2]) AT_3[nl][k]=k2;
             else
            {
             if(k2<15)
                {
                 if((dP_osl_2[nl][k]<Q_vh_zn[k2])&&(dP_osl_2[nl][k]>Q_vh_zn[k2+1]))
                      AT_3[nl][k]=k2;
                }
            }
           if(dP_osl_3[nl][k]==Q_vh_zn[k2]) AT_4[nl][k]=k2;
              else
               {
                if(k2<15)
                 {
                 if((dP_osl_3[nl][k]<Q_vh_zn[k2])&&(dP_osl_3[nl][k]>Q_vh_zn[k2+1]))
                      AT_4[nl][k]=k2;
                 }
               }
            if(dP_osl_4[nl][k]==Q_vh_zn[k2]) AT_5[nl][k]=k2;
               else
                {
                 if(k2<15)
                  {
                 if((dP_osl_4[nl][k]<Q_vh_zn[k2])&&(dP_osl_4[nl][k]>Q_vh_zn[k2+1]))
                      AT_5[nl][k]=k2;
                }
            }
             if(dP_osl_5[nl][k]==Q_vh_zn[k2]) AT_6[nl][k]=k2;
              else
               {
               if(k2<15)
                 {
                 if((dP_osl_5[nl][k]<Q_vh_zn[k2])&&(dP_osl_5[nl][k]>Q_vh_zn[k2+1]))
                      AT_6[nl][k]=k2;
                 }
               }
             if(dP_osl_6[nl][k]==Q_vh_zn[k2]) AT_7[nl][k]=k2;
                 else
                  {
                   if(k2<15)
                    {
                     if((dP_osl_6[nl][k]<Q_vh_zn[k2])&&(dP_osl_6[nl][k]>Q_vh_zn[k2+1]))
                      AT_7[nl][k]=k2;
                    }
                 }
               if(dP_osl_7[nl][k]==Q_vh_zn[k2]) AT_8[nl][k]=k2;
                 else
                   {
                    if(k2<15)
                     {
                     if((dP_osl_7[nl][k]<Q_vh_zn[k2])&&(dP_osl_7[nl][k]>Q_vh_zn[k2+1]))
                     AT_8[nl][k]=k2;
                     }
                   }
               if(dP_osl_8[nl][k]==Q_vh_zn[k2]) AT_9[nl][k]=k2;
                   else
                    {
                     if(k2<15)
                      {
                      if((dP_osl_8[nl][k]<Q_vh_zn[k2])&&(dP_osl_8[nl][k]>Q_vh_zn[k2+1]))
                      AT_9[nl][k]=k2;
                      }
                    }
                 if(dP_osl_9[nl][k]==Q_vh_zn[k2]) AT_10[nl][k]=k2;
                   else
                    {
                     if(k2<15)
                      {
                      if((dP_osl_9[nl][k]<Q_vh_zn[k2])&&(dP_osl_9[nl][k]>Q_vh_zn[k2+1]))
                      AT_10[nl][k]=k2;
                      }
                    }
                  if(dP_osl_10[nl][k]==Q_vh_zn[k2]) AT_11[nl][k]=k2;
                    else
                    {
                     if(k2<15)
                      {
                      if((dP_osl_10[nl][k]<Q_vh_zn[k2])&&(dP_osl_10[nl][k]>Q_vh_zn[k2+1]))
                      AT_11[nl][k]=k2;
                     }
                    }
                   if(dP_osl_11[nl][k]==Q_vh_zn[k2]) AT_12[nl][k]=k2;
                     else
                      {
                       if(k2<15)
                        {
                        if((dP_osl_11[nl][k]<Q_vh_zn[k2])&&(dP_osl_11[nl][k]>Q_vh_zn[k2+1]))
                        AT_12[nl][k]=k2;
                        }
                      }
                    if(dP_osl_12[nl][k]==Q_vh_zn[k2]) AT_13[nl][k]=k2;
                       else
                        {
                         if(k2<15)
                          {
                           if((dP_osl_12[nl][k]<Q_vh_zn[k2])&&(dP_osl_12[nl][k]>Q_vh_zn[k2+1]))
                           AT_13[nl][k]=k2;
                          }
                        }
       }

        if(dP_osl_0[nl][k]<=-11.25) AT_1[nl][k]=0xF;
        if(dP_osl_1[nl][k]<=-11.25) AT_2[nl][k]=0xF;
        if(dP_osl_2[nl][k]<=-11.25) AT_3[nl][k]=0xF;
        if(dP_osl_3[nl][k]<=-11.25) AT_4[nl][k]=0xF;
        if(dP_osl_4[nl][k]<=-11.25) AT_5[nl][k]=0xF;
        if(dP_osl_5[nl][k]<=-11.25) AT_6[nl][k]=0xF;
        if(dP_osl_6[nl][k]<=-11.25) AT_7[nl][k]=0xF;
        if(dP_osl_7[nl][k]<=-11.25) AT_8[nl][k]=0xF;
        if(dP_osl_8[nl][k]<=-11.25) AT_9[nl][k]=0xF;
        if(dP_osl_9[nl][k]<=-11.25) AT_10[nl][k]=0xF;
        if(dP_osl_10[nl][k]<=-11.25) AT_11[nl][k]=0xF;
        if(dP_osl_11[nl][k]<=-11.25) AT_12[nl][k]=0xF;
        if(dP_osl_12[nl][k]<=-11.25) AT_13[nl][k]=0xF;

   }  /* end k �� �������*/
   k=0;
 }   /* end nl �� �����*/
}/* ���� ������ 2*/
else        /*   �������� ������ ��� ������ 53  */
  {
   for(nl=0;nl<=7;nl++)   /* 8 �����*/
    {
     for(k=0;k<=159;k++)
       {
         fscanf(tr,"%d",&k_f);
         fscanf(tr,"%f%f%f%f%f%f%f%f%f%f%f%f%f\n",&P_in_att_53[nl][k],&dP_osl_0_53[nl][k],
         &dP_osl_1_53[nl][k],&dP_osl_2_53[nl][k],&dP_osl_3_53[nl][k],&dP_osl_4_53[nl][k],&dP_osl_5_53[nl][k],&dP_osl_6_53[nl][k],
         &dP_osl_7_53[nl][k],&dP_osl_8_53[nl][k],&dP_osl_9_53[nl][k],&dP_osl_10_53[nl][k],&dP_osl_11_53[nl][k]);//,&dP_osl_12[nl][k]);
       } /* end k*/
    } /* end nl */
   fclose(tr);

 for(nl=0;nl<=7;nl++)   /* ���� �� ������ ����*/       /* ��� ������ 53 8 ����� */
  {
  for(k=0; k<=159; k++) /* �� �������*/    /* ��� ������ 53 160 ��������� ����� */
   {

   for(k1=0; k1<=30; k1+=1)
       {
        /*a=P_in_att_53[nl][k]; b= Qvh_osl[k1]; c=Qvh_osl[k1+1];*/
     //   if(P_in_att[nl][k]==Qvh_osl[31-k1])
        if(P_in_att_53[nl][k]==Qvh_osl[k1])
        {
         IN_AT_53[nl][k]=Qv_vh[k1]; goto m_in_att_53;
        }
        /* ��� ������� ������� �����  ��� �������� ���*/
//       if((P_in_att[nl][k]<Qvh_osl[31-k1])&&(P_in_att[nl][k]>Qvh_osl[31-(k1+1)]))
     if((P_in_att_53[nl][k]<Qvh_osl[k1])&&(P_in_att_53[nl][k]>Qvh_osl[k1+1]))
        {
         IN_AT_53[nl][k]=Qv_vh[k1];goto m_in_att_53;
        }
        /* ��� ������� ������� �����  ��� �������� ���*/
       }
     m_in_att_53:;
     AT_1_53[nl][k]=0xF; AT_2_53[nl][k]=0xF;AT_3_53[nl][k]=0xF;
     AT_4_53[nl][k]=0xF; AT_5_53[nl][k]=0xF;AT_6_53[nl][k]=0xF;
     AT_7_53[nl][k]=0xF; AT_8_53[nl][k]=0xF;AT_9_53[nl][k]=0xF;
     AT_10_53[nl][k]=0xF;AT_11_53[nl][k]=0xF;AT_12_53[nl][k]=0xF;
     AT_13_53[nl][k]=0xF;

     for(k2=0;k2<=15;k2++)  /* ���������� ����� �������� ��� �� �� 16 ���������*/
      {
        if(dP_osl_0_53[nl][k]==Q_vh_zn[k2]) AT_1_53[nl][k]=k2;
         else
            {
             if(k2<15)
                {
                 if((dP_osl_0_53[nl][k]<Q_vh_zn[k2])&&(dP_osl_0_53[nl][k]>Q_vh_zn[k2+1]))
                      AT_1_53[nl][k]=k2;
                }
            }
         if(dP_osl_1_53[nl][k]==Q_vh_zn[k2]) AT_2_53[nl][k]=k2;
            else
            {
             if(k2<15)
                {
                 if((dP_osl_1_53[nl][k]<Q_vh_zn[k2])&&(dP_osl_1_53[nl][k]>Q_vh_zn[k2+1]))
                      AT_2_53[nl][k]=k2;
                }
            }
          if(dP_osl_2_53[nl][k]==Q_vh_zn[k2]) AT_3_53[nl][k]=k2;
             else
            {
             if(k2<15)
                {
                 if((dP_osl_2_53[nl][k]<Q_vh_zn[k2])&&(dP_osl_2_53[nl][k]>Q_vh_zn[k2+1]))
                      AT_3_53[nl][k]=k2;
                }
            }
           if(dP_osl_3_53[nl][k]==Q_vh_zn[k2]) AT_4_53[nl][k]=k2;
              else
               {
                if(k2<15)
                 {
                 if((dP_osl_3_53[nl][k]<Q_vh_zn[k2])&&(dP_osl_3_53[nl][k]>Q_vh_zn[k2+1]))
                      AT_4_53[nl][k]=k2;
                 }
               }
            if(dP_osl_4_53[nl][k]==Q_vh_zn[k2]) AT_5_53[nl][k]=k2;
               else
                {
                 if(k2<15)
                  {
                 if((dP_osl_4_53[nl][k]<Q_vh_zn[k2])&&(dP_osl_4_53[nl][k]>Q_vh_zn[k2+1]))
                      AT_5_53[nl][k]=k2;
                }
            }
             if(dP_osl_5_53[nl][k]==Q_vh_zn[k2]) AT_6_53[nl][k]=k2;
              else
               {
               if(k2<15)
                 {
                 if((dP_osl_5_53[nl][k]<Q_vh_zn[k2])&&(dP_osl_5_53[nl][k]>Q_vh_zn[k2+1]))
                      AT_6_53[nl][k]=k2;
                 }
               }
             if(dP_osl_6_53[nl][k]==Q_vh_zn[k2]) AT_7_53[nl][k]=k2;
                 else
                  {
                   if(k2<15)
                    {
                     if((dP_osl_6_53[nl][k]<Q_vh_zn[k2])&&(dP_osl_6_53[nl][k]>Q_vh_zn[k2+1]))
                      AT_7_53[nl][k]=k2;
                    }
                 }
               if(dP_osl_7_53[nl][k]==Q_vh_zn[k2]) AT_8_53[nl][k]=k2;
                 else
                   {
                    if(k2<15)
                     {
                     if((dP_osl_7_53[nl][k]<Q_vh_zn[k2])&&(dP_osl_7_53[nl][k]>Q_vh_zn[k2+1]))
                     AT_8_53[nl][k]=k2;
                     }
                   }
               if(dP_osl_8_53[nl][k]==Q_vh_zn[k2]) AT_9_53[nl][k]=k2;
                   else
                    {
                     if(k2<15)
                      {
                      if((dP_osl_8_53[nl][k]<Q_vh_zn[k2])&&(dP_osl_8_53[nl][k]>Q_vh_zn[k2+1]))
                      AT_9_53[nl][k]=k2;
                      }
                    }
                 if(dP_osl_9_53[nl][k]==Q_vh_zn[k2]) AT_10_53[nl][k]=k2;
                   else
                    {
                     if(k2<15)
                      {
                      if((dP_osl_9_53[nl][k]<Q_vh_zn[k2])&&(dP_osl_9_53[nl][k]>Q_vh_zn[k2+1]))
                      AT_10_53[nl][k]=k2;
                      }
                    }
                  if(dP_osl_10_53[nl][k]==Q_vh_zn[k2]) AT_11_53[nl][k]=k2;
                    else
                    {
                     if(k2<15)
                      {
                      if((dP_osl_10_53[nl][k]<Q_vh_zn[k2])&&(dP_osl_10_53[nl][k]>Q_vh_zn[k2+1]))
                      AT_11_53[nl][k]=k2;
                     }
                    }
                   if(dP_osl_11_53[nl][k]==Q_vh_zn[k2]) AT_12_53[nl][k]=k2;
                     else
                      {
                       if(k2<15)
                        {
                        if((dP_osl_11_53[nl][k]<Q_vh_zn[k2])&&(dP_osl_11_53[nl][k]>Q_vh_zn[k2+1]))
                        AT_12_53[nl][k]=k2;
                        }
                      }
    //              if(dP_osl_12[nl][k]==Q_vh_zn[k2]) AT_13[nl][k]=k2;
    //                 else
    //                    {
    //                     if(k2<15)
    //                      {
    //                       if((dP_osl_12[nl][k]<Q_vh_zn[k2])&&(dP_osl_12[nl][k]>Q_vh_zn[k2+1]))
    //                       AT_13[nl][k]=k2;
     //                     }
     //                   }
       }

        if(dP_osl_0_53[nl][k]<=-11.25) AT_1_53[nl][k]=0xF;
        if(dP_osl_1_53[nl][k]<=-11.25) AT_2_53[nl][k]=0xF;
        if(dP_osl_2_53[nl][k]<=-11.25) AT_3_53[nl][k]=0xF;
        if(dP_osl_3_53[nl][k]<=-11.25) AT_4_53[nl][k]=0xF;
        if(dP_osl_4_53[nl][k]<=-11.25) AT_5_53[nl][k]=0xF;
        if(dP_osl_5_53[nl][k]<=-11.25) AT_6_53[nl][k]=0xF;
        if(dP_osl_6_53[nl][k]<=-11.25) AT_7_53[nl][k]=0xF;
        if(dP_osl_7_53[nl][k]<=-11.25) AT_8_53[nl][k]=0xF;
        if(dP_osl_8_53[nl][k]<=-11.25) AT_9_53[nl][k]=0xF;
        if(dP_osl_9_53[nl][k]<=-11.25) AT_10_53[nl][k]=0xF;
        if(dP_osl_10_53[nl][k]<=-11.25) AT_11_53[nl][k]=0xF;
        if(dP_osl_11_53[nl][k]<=-11.25) AT_12_53[nl][k]=0xF;
 //       if(dP_osl_12[nl][k]<=-11.25) AT_13[nl][k]=0xF;

   }  /* end k �� �������*/
   k=0;
 }   /* end nl �� �����*/


  } /*end else 53*/
m1:;
 return(0);
}
//===================������� ������ �� ���������� ����� ==========================
void __fastcall TForm1::B2_chtenClick(TObject *Sender)
{

}
//=================== ������ �� ���������� ����� ���  � �������� =================
void __fastcall TForm1::SB4Click(TObject *Sender)
{
AnsiString StNIn;
int indIn;//,colLuch,colOut,colF;
//int Flb,Lit;
int i,j;
AnsiString SbS,SbL,StrDir,StIn,SbS_t;
AnsiString MyFileName;
int n_vh,nl,k,k_f;

   float P_in_att[4][64]={0.0};
 // float P_max_mod=0.0;

  float dP_osl_0[4][64]={0.0},dP_osl_1[4][64]={0.0},dP_osl_2[4][64]={0.0},
        dP_osl_3[4][64]={0.0},dP_osl_4[4][64]={0.0},dP_osl_5[4][64]={0.0},
        dP_osl_6[4][64]={0.0},dP_osl_7[4][64]={0.0},dP_osl_8[4][64]={0.0},
        dP_osl_9[4][64]={0.0},dP_osl_10[4][64]={0.0},dP_osl_11[4][64]={0.0},
        dP_osl_12[4][64]={0.0};

 FILE *tr;
// String str;
// int k,j,n_us,k1,k2,k_max_mod,nl,k_f;


StNIn= InputBox("������� ����� �����", "���� �� ������� (1,2,3,4). ��������� ������ ���� ������� �� ������","1");

if(RG9->ItemIndex==0)
 {
  SbS_t="���";
  SbS="pps";
  }
else
  {
  SbS_t="���";
  SbS="zps";
  }
//SbL="��_2";
  SbL="_2";
/*Flb=Fl;
colLuch=4;
colOut=13;
Lit=0;
colF=((Fb-Fl)/500)*8;
*/
// StrDir=GetCurrentDir();  ��� ����� ����������

 StIn=SbS+"_"+StNIn+SbL+".mrt";
// MyFileName=StrDir+"\\PowMesh\\"+StIn;
 MyFileName=StIn;
 if(FileExists(MyFileName))
 {
   n_vh=StrToInt(StNIn);
 //    chten_mrt(n_vh);
 //   if(n_vhod==1) str="pps_1_2.mrt";
if((tr = fopen(MyFileName.c_str(),"r+")) == NULL)
  {
  ShowMessage("��� �����");
   goto m1;
  }
 /* ������� ������ �� ����� */
  for(nl=0;nl<=3;nl++)     /* �� 4-� ����� */
    {
     for(k=0;k<=63;k++)
       {
         fscanf(tr,"%d",&k_f);
         fscanf(tr,"%f%f%f%f%f%f%f%f%f%f%f%f%f%f\n",&P_in_att[nl][k],&dP_osl_0[nl][k],
         &dP_osl_1[nl][k],&dP_osl_2[nl][k],&dP_osl_3[nl][k],&dP_osl_4[nl][k],&dP_osl_5[nl][k],&dP_osl_6[nl][k],
         &dP_osl_7[nl][k],&dP_osl_8[nl][k],&dP_osl_9[nl][k],&dP_osl_10[nl][k],&dP_osl_11[nl][k],&dP_osl_12[nl][k]);
       } /* end k*/
    } /* end nl */
   fclose(tr);

   P7->Visible=true;
   L20->Caption="�������� �����  �������  ������� ����� (MRT). ���� "+StNIn+". "+"������"+SbL+". "+SbS_t;

   PostMessage(SG2->Handle, WM_MBUTTONDOWN, MK_LBUTTON,0);
   PostMessage(SG2->Handle, WM_MBUTTONUP, MK_LBUTTON,0);


        /* �������� �������*/
for(nl=0;nl<=3;nl++)     /* �� 4-� ����� */
    {
  for(k=1;k<=64;k++)    /* ������  */
   for(j=1;j<=14;j++)   /* �������  */
     {
     SG2->Cells[j][k+nl*64]=" ";
     }
  }
   SG2->Cells[0][0]="�������";
   SG2->Cells[1][0]="��� ��.���";
   SG2->Cells[2][0]="��� ��� 1";
   SG2->Cells[3][0]="��� ��� 2";
   SG2->Cells[4][0]="��� ��� 3";
   SG2->Cells[5][0]="��� ��� 4";
   SG2->Cells[6][0]="��� ��� 5";
   SG2->Cells[7][0]="��� ��� 6";
   SG2->Cells[8][0]="��� ��� 7";
   SG2->Cells[9][0]="��� ��� 8";
   SG2->Cells[10][0]="��� ��� 9";
   SG2->Cells[11][0]="��� ���10";
   SG2->Cells[12][0]="��� ���11";
   SG2->Cells[13][0]="��� ���12";
   SG2->Cells[14][0]="��� ���13";

  for(nl=0;nl<=3;nl++)     /* �� 4-� ����� */
    {
   for(k=1;k<=64;k++)    /* ������  */   /*?????*/
   SG2->Cells[0][k+nl*64+(nl+1)]=FloatToStr(F_rtu[k-1]);
   }

    for(nl=0;nl<=3;nl++)     /* �� 4-� ����� */
    {
         SG2->Cells[5][nl*64+(nl+1)]="��� "+IntToStr(nl+1);
     for(k=0;k<=63;k++)
      {
        SG2->Cells[1][nl*64+k+(nl+2)]=FloatToStrF(P_in_att[nl][k],ffGeneral,4,2);
        SG2->Cells[2][nl*64+k+(nl+2)]=FloatToStrF(dP_osl_0[nl][k],ffGeneral,4,2);
        SG2->Cells[3][nl*64+k+(nl+2)]=FloatToStrF(dP_osl_1[nl][k],ffGeneral,4,2);
        SG2->Cells[4][nl*64+k+(nl+2)]=FloatToStrF(dP_osl_2[nl][k],ffGeneral,4,2);
        SG2->Cells[5][nl*64+k+(nl+2)]=FloatToStrF(dP_osl_3[nl][k],ffGeneral,4,2);
        SG2->Cells[6][nl*64+k+(nl+2)]=FloatToStrF(dP_osl_4[nl][k],ffGeneral,4,2);
        SG2->Cells[7][nl*64+k+(nl+2)]=FloatToStrF(dP_osl_5[nl][k],ffGeneral,4,2);
        SG2->Cells[8][nl*64+k+(nl+2)]=FloatToStrF(dP_osl_6[nl][k],ffGeneral,4,2);
        SG2->Cells[9][nl*64+k+(nl+2)]=FloatToStrF(dP_osl_7[nl][k],ffGeneral,4,2);
        SG2->Cells[10][nl*64+k+(nl+2)]=FloatToStrF(dP_osl_8[nl][k],ffGeneral,4,2);
        SG2->Cells[11][nl*64+k+(nl+2)]=FloatToStrF(dP_osl_9[nl][k],ffGeneral,4,2);
        SG2->Cells[12][nl*64+k+(nl+2)]=FloatToStrF(dP_osl_10[nl][k],ffGeneral,4,2);
        SG2->Cells[13][nl*64+k+(nl+2)]=FloatToStrF(dP_osl_11[nl][k],ffGeneral,4,2);
        SG2->Cells[14][nl*64+k+(nl+2)]=FloatToStrF(dP_osl_12[nl][k],ffGeneral,4,2);
      } /* end k*/
    } /* end nl */

 }  //if
m1:;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::B25Click(TObject *Sender)
{
   P7->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SB_5Click(TObject *Sender)
{
AnsiString StNIn,Str;
//int indIn,colLuch,colOut,colF;
//int Flb,Lit;
int i,j;
AnsiString SbS,SbL,StrDir,StIn,SbS_t;
AnsiString MyFileName;
int n_vh,nl,k,k_f;

   float P_in_att[4][64]={0.0};
 // float P_max_mod=0.0;

  float dP_osl_0[4][64]={0.0},dP_osl_1[4][64]={0.0},dP_osl_2[4][64]={0.0},
        dP_osl_3[4][64]={0.0},dP_osl_4[4][64]={0.0},dP_osl_5[4][64]={0.0},
        dP_osl_6[4][64]={0.0},dP_osl_7[4][64]={0.0},dP_osl_8[4][64]={0.0},
        dP_osl_9[4][64]={0.0},dP_osl_10[4][64]={0.0},dP_osl_11[4][64]={0.0},
        dP_osl_12[4][64]={0.0};

 FILE *tr;
 bool res;

//StNIn= InputBox("������� ����� �����", "���� �� ������� (1,2,3,4). ��������� ������ ���� ������� �� ������","1");
 Str=L20->Caption;//"�������� �����  �������  ������� ����� (MRT). ���� "+StNIn+". "+"������"+SbL+". "+SbS_t;

 int p=Str.Pos("�");
 StNIn=Str.SubString(p+2,1);

 if(RG9->ItemIndex==0)
 {
  SbS_t="���";
  SbS="pps";
  }
else
  {
  SbS_t="���";
  SbS="zps";
  }
//SbL="��_2";
  SbL="_2"; /* ������� � ��� _53 !!!!*/
/*Flb=Fl;
colLuch=4;
colOut=13;
Lit=0;
colF=((Fb-Fl)/500)*8;
*/
//--------------�������� ������������ ���������� �������------------------------
 for(nl=0;nl<=3;nl++)   /* ���� �� ������ ����*/
  {
  for(k=0; k<=63; k++) /* �� �������*/
   {
    res=TryStrToFloat(SG2->Cells[1][nl*64+k+(nl+2)],P_in_att[nl][k]);
      if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ��.���: ��� "+IntToStr(nl+1)+"� ������� 1 � ������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }
   //  P_in_att[nl][k]=StrToFloat(SG2->Cells[1][nl*64+k+(nl+2)]);

     res=TryStrToFloat(SG2->Cells[2][nl*64+k+(nl+2)],dP_osl_0[nl][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ���1: ��� "+IntToStr(nl+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }

     res=TryStrToFloat(SG2->Cells[3][nl*64+k+(nl+2)],dP_osl_1[nl][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ���2: ��� "+IntToStr(nl+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }

     res=TryStrToFloat(SG2->Cells[4][nl*64+k+(nl+2)],dP_osl_2[nl][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ���3: ��� "+IntToStr(nl+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }
      res=TryStrToFloat(SG2->Cells[5][nl*64+k+(nl+2)],dP_osl_3[nl][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ���4: ��� "+IntToStr(nl+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }
      res=TryStrToFloat(SG2->Cells[6][nl*64+k+(nl+2)],dP_osl_4[nl][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ���5: ��� "+IntToStr(nl+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }

      res=TryStrToFloat(SG2->Cells[7][nl*64+k+(nl+2)],dP_osl_5[nl][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ���6: ��� "+IntToStr(nl+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }
      res=TryStrToFloat(SG2->Cells[8][nl*64+k+(nl+2)],dP_osl_6[nl][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ���7: ��� "+IntToStr(nl+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }
      res=TryStrToFloat(SG2->Cells[9][nl*64+k+(nl+2)],dP_osl_7[nl][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ���8: ��� "+IntToStr(nl+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }
      res=TryStrToFloat(SG2->Cells[10][nl*64+k+(nl+2)],dP_osl_8[nl][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ���9: ��� "+IntToStr(nl+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }
       res=TryStrToFloat(SG2->Cells[11][nl*64+k+(nl+2)],dP_osl_9[nl][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ���10: ��� "+IntToStr(nl+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
        }
     res=TryStrToFloat(SG2->Cells[12][nl*64+k+(nl+2)],dP_osl_10[nl][k]);
       if(res==false)
        {
         ShowMessage("����������� ������� �������� ��� ���11: ��� "+IntToStr(nl+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
        }
      res=TryStrToFloat(SG2->Cells[13][nl*64+k+(nl+2)],dP_osl_11[nl][k]);
       if(res==false)
        {
         ShowMessage("����������� ������� �������� ��� ���12: ��� "+IntToStr(nl+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
        }
      res=TryStrToFloat(SG2->Cells[14][nl*64+k+(nl+2)],dP_osl_12[nl][k]);
       if(res==false)
        {
         ShowMessage("����������� ������� �������� ��� ���13: ��� "+IntToStr(nl+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
        }

     }  /* end k �� �������*/
 }   /* end nl �� �����*/

// StrDir=GetCurrentDir();  ��� ����� ����������

 StIn=SbS+"_"+StNIn+SbL+".mrt";
// MyFileName=StrDir+"\\PowMesh\\"+StIn;
 MyFileName=StIn;
 if(FileExists(MyFileName))
 {
   n_vh=StrToInt(StNIn);
 if(MessageDlg("������������ ���� ��� ��� ����� "+StNIn+"������"+SbL+SbS_t+"?",
     mtConfirmation,TMsgDlgButtons() << mbYes<< mbNo,0) == mrYes)
    {
      ShowMessage("���� ����� �����������");
    }
   else goto m1;

//=====================================================
 if((tr = fopen(MyFileName.c_str(),"w+")) == NULL)
  {
  ShowMessage("��� �����");
  goto m1;
 }

 for(nl=0;nl<=3;nl++)   /* ���� �� ������ ����*/
  {
  for(k=0; k<=63; k++) /* �� �������*/
   {
 //    bool res=TryStrToFloat(SG2->Cells[1][nl*64+k+(nl+2)],P_in_att[nl][k]);
 //     if(res==false)
 //      {
 //        ShowMessage("����������� ������� �������� ��� ��.��� � ������� 1 � ������ "+IntToStr(nl*64+k+(nl+2)));
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
                 dP_osl_7[nl][k],dP_osl_8[nl][k],dP_osl_9[nl][k],dP_osl_10[nl][k],dP_osl_11[nl][k],dP_osl_12[nl][k]);

       }  /* end k �� �������*/
 }   /* end nl �� �����*/

}/* if*/
   fclose(tr);

m1:;
}
//--------------������ � �������������� ����� ��������� � �������  ----------------------------
void __fastcall TForm1::SB_fiClick(TObject *Sender)
{
AnsiString StNIn;
//int indIn,colLuch,colOut,colF;
int Flb,Lit,i,j;
AnsiString SbS,SbL,StIn,SbS_t;//,StrDir;
AnsiString MyFileName;
int n_vh;
int nl,k,n_us;

 float P_izm[13][4][64]={0.0},osl[13][4][64]={0.0};
 int kad_acp[13][4][64]={0},k_f[64]={0};
 // unsigned NIT;

 //float P_izm_mod[13]={0.0}; /* ������ ��� ������ � ���� */

 FILE *tr;

StNIn= InputBox("������� ����� �����", "���� �� ������� (1,2,3,4). ��������� ������ ���� ������� �� ������","1");

if(RG9->ItemIndex==0)
 {
  SbS_t="���";
  SbS="pps";
  }
else
  {
  SbS_t="���";
  SbS="zps";
  }
//SbL="��_2";
  SbL="_2";
/*Flb=Fl;
colLuch=4;
colOut=13;
Lit=0;
colF=((Fb-Fl)/500)*8;
*/

// StrDir=GetCurrentDir();  ��� ����� ����������

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
  ShowMessage("��� �����");
   goto m1;
  }
 /* ������� ������ �� ����� */
   for(n_us=0;n_us<=12;n_us++) /* �� 13 ���������� */
    {
     for(k=0;k<=63;k++)
       {
        fscanf(tr,"%d",&k_f[k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][0][k],&osl[n_us][0][k], &kad_acp[n_us][0][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][1][k],&osl[n_us][1][k], &kad_acp[n_us][1][k]);
        fscanf(tr,"%f%f%d",&P_izm[n_us][2][k],&osl[n_us][2][k], &kad_acp[n_us][2][k]);
        fscanf(tr,"%f%f%d\n",&P_izm[n_us][3][k],&osl[n_us][3][k],&kad_acp[n_us][3][k]);
      } /* end k*/
    } /* end n_us */

   fclose(tr);

   P_fi->Visible=true;
   L_fi->Caption="�������  �������� ��������� � ����� ������� �����������. ���� "+StNIn+". "+"������"+SbL+". "+SbS_t;

   PostMessage(SG2->Handle, WM_MBUTTONDOWN, MK_LBUTTON,0);
   PostMessage(SG2->Handle, WM_MBUTTONUP, MK_LBUTTON,0);

        /* �������� �������*/
for(n_us=0;n_us<=12;n_us++)     /* �� 4-� ����� */
    {
  for(k=1;k<=64;k++)    /* ������  */
   for(j=1;j<=12;j++)   /* �������  */
     {
     SG_fi->Cells[j][k+n_us*64]=" ";
     }
  }
  for(n_us=0;n_us<=12;n_us++)     /* �� 13 ���������� */
    {
   for(k=1;k<=64;k++)    /* ������  */   /*?????*/
   SG_fi->Cells[0][k+n_us*64+n_us]=FloatToStr(F_rtu[k-1]);
   }
                /* ������� � ������� */
    for(n_us=0;n_us<=12;n_us++)     /* �� 13 ���������� */
    {
         SG_fi->Cells[4][n_us*64+n_us]="�����";
         SG_fi->Cells[5][n_us*64+n_us]=SbS_t+"-"+IntToStr(n_us+1);
     for(k=0;k<=63;k++)
      {
                         /* ��� 1 */
        SG_fi->Cells[1][n_us*64+k+(n_us+1)]=FloatToStrF(P_izm[n_us][0][k],ffGeneral,3,2);
        SG_fi->Cells[2][n_us*64+k+(n_us+1)]=FloatToStrF(osl[n_us][0][k],ffGeneral,4,2);
        SG_fi->Cells[3][n_us*64+k+(n_us+1)]=FloatToStrF(kad_acp[n_us][0][k],ffGeneral,3,2);
                         /* ��� 2 */
        SG_fi->Cells[4][n_us*64+k+(n_us+1)]=FloatToStrF(P_izm[n_us][1][k],ffGeneral,3,2);
        SG_fi->Cells[5][n_us*64+k+(n_us+1)]=FloatToStrF(osl[n_us][1][k],ffGeneral,4,2);
        SG_fi->Cells[6][n_us*64+k+(n_us+1)]=FloatToStrF(kad_acp[n_us][1][k],ffGeneral,3,2);
                           /* ��� 3*/
        SG_fi->Cells[7][n_us*64+k+(n_us+1)]=FloatToStrF(P_izm[n_us][2][k],ffGeneral,3,2);
        SG_fi->Cells[8][n_us*64+k+(n_us+1)]=FloatToStrF(osl[n_us][2][k],ffGeneral,4,2);
        SG_fi->Cells[9][n_us*64+k+(n_us+1)]=FloatToStrF(kad_acp[n_us][2][k],ffGeneral,3,2);
                           /* ��� 4 */
        SG_fi->Cells[10][n_us*64+k+(n_us+1)]=FloatToStrF(P_izm[n_us][3][k],ffGeneral,3,2);
        SG_fi->Cells[11][n_us*64+k+(n_us+1)]=FloatToStrF(osl[n_us][3][k],ffGeneral,4,2);
        SG_fi->Cells[12][n_us*64+k+(n_us+1)]=FloatToStrF(kad_acp[n_us][3][k],ffGeneral,3,2);
     } /* end k*/
  } /* end n_us */

 }  //if
m1:;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::B_fiClick(TObject *Sender)
{
 P_fi->Visible=false;
}
//----------------------������ ����� ��������� *.dan-------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::SB_fzClick(TObject *Sender)
{
AnsiString StNIn,Str;
int indIn;//,colLuch,colOut,colF;
//int Flb,Lit;
int i,j;
AnsiString SbS,SbL,StrDir,StIn,SbS_t;
AnsiString MyFileName;
int n_vh,nl,k,k_f,n_us;

 float P_izm[13][4][64]={0.0},osl[13][4][64]={0.0};
 int kad_acp[13][4][64]={0};//k_f[64]={0};

 FILE *tr;
 bool res;

//StNIn= InputBox("������� ����� �����", "���� �� ������� (1,2,3,4). ��������� ������ ���� ������� �� ������","1");
 Str=L_fi->Caption;//"�������  �������� ��������� � ����� ������� �����������. ���� "+StNIn+". "+"������"+SbL+". "+SbS_t ";

 int p=Str.Pos(".");
 StNIn=Str.SubString(p+7,1);  /* ��� ����� ????*/

 if(RG9->ItemIndex==0)
 {
  SbS_t="���";
  SbS="pps";
  }
else
  {
  SbS_t="���";
  SbS="zps";
  }
//SbL="��_2";
  SbL="_2"; /* ������� � ��� _53 !!!!*/
/*Flb=Fl;
colLuch=4;
colOut=13;
Lit=0;
colF=((Fb-Fl)/500)*8;
*/
//--------------�������� ������������ ���������� �������------------------------
 for(n_us=0;n_us<=12;n_us++)
  {
       /* ������ � ���� */
     for(k=0;k<=63;k++)    /* ������  */
       {
         /* ��� 1 */
    res=TryStrToFloat(SG_fi->Cells[1][n_us*64+k+(n_us+1)],P_izm[n_us][0][k]);
     if(res==false)
         {
         ShowMessage("����������� ������� �������� ����: ��� 1. ����� "+SbS_t+"-"+IntToStr(n_us+1)+"������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }
     res=TryStrToFloat(SG_fi->Cells[2][n_us*64+k+(n_us+1)],osl[n_us][0][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ���.: ��� 1. ����� "+SbS_t+"-"+IntToStr(n_us+1)+"������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }

     res=TryStrToInt(SG_fi->Cells[3][n_us*64+k+(n_us+1)],kad_acp[n_us][0][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ��: ��� 1. ����� "+SbS_t+"-"+IntToStr(n_us+1)+"������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }

        /* ��� 2*/
     res=TryStrToFloat(SG_fi->Cells[4][n_us*64+k+(n_us+1)],P_izm[n_us][1][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ����: ��� 2. ����� "+SbS_t+"-"+IntToStr(n_us+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }
       res=TryStrToFloat(SG_fi->Cells[5][n_us*64+k+(n_us+1)],osl[n_us][1][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ���.: ��� 2. ����� "+SbS_t+"-"+IntToStr(n_us+1)+"������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }
       res=TryStrToInt(SG_fi->Cells[6][n_us*64+k+(n_us+1)],kad_acp[n_us][1][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ��: ��� 2. ����� "+SbS_t+"-"+IntToStr(n_us+1)+"������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }

           /* ��� 3 */
      res=TryStrToFloat(SG_fi->Cells[7][n_us*64+k+(n_us+1)],P_izm[n_us][2][k]);
      if(res==false)
         {
         ShowMessage("����������� ������� �������� ����: ��� 3. ����� "+SbS_t+"-"+IntToStr(n_us+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }
        res=TryStrToFloat(SG_fi->Cells[8][n_us*64+k+(n_us+1)],osl[n_us][2][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ���.: ��� 3. ����� "+SbS_t+"-"+IntToStr(n_us+1)+"������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }
      res=TryStrToInt(SG_fi->Cells[9][n_us*64+k+(n_us+1)],kad_acp[n_us][2][k]);
      if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ��: ��� 3. ����� "+SbS_t+"-"+IntToStr(n_us+1)+"������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }

          /* ��� 4*/
       res=TryStrToFloat(SG_fi->Cells[10][n_us*64+k+(n_us+1)],P_izm[n_us][3][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ����: ��� 4. ����� "+SbS_t+"-"+IntToStr(n_us+1)+" ������ "+FloatToStr(F_rtu[k]));
         goto m1;
         }
       res=TryStrToFloat(SG_fi->Cells[11][n_us*64+k+(n_us+1)],osl[n_us][3][k]);
       if(res==false)
         {
         ShowMessage("����������� ������� �������� ��� ���.: ��� 4. ����� "+SbS_t+"-"+IntToStr(n_us+1)+"������ "+FloatToStr(F_rtu[k]));
         goto m1;
        }
      res=TryStrToInt(SG_fi->Cells[12][n_us*64+k+(n_us+1)],kad_acp[n_us][3][k]);
       if(res==false)
        {
         ShowMessage("����������� ������� �������� ��� ��: ��� 4. ����� "+SbS_t+"-"+IntToStr(n_us+1)+"������ "+FloatToStr(F_rtu[k]));
         goto m1;
        }
     }  /* end k �� �������*/
 }   /* end n_us */

// StrDir=GetCurrentDir();  ��� ����� ����������

 StIn=SbS+"_"+StNIn+SbL+".dan";
// MyFileName=StrDir+"\\PowMesh\\"+StIn;
 MyFileName=StIn;
 if(FileExists(MyFileName))
 {
   n_vh=StrToInt(StNIn);
 if(MessageDlg("������������ ���� ��������� ��� ����� "+StNIn+"������"+SbL+SbS_t+"?",
     mtConfirmation,TMsgDlgButtons() << mbYes<< mbNo,0) == mrYes)
    {
      ShowMessage("���� ����� �����������");
    }
   else goto m1;

//=====================================================
 if((tr = fopen(MyFileName.c_str(),"w+")) == NULL)
  {
  ShowMessage("��� �����");
  goto m1;
 }

  for(n_us=0;n_us<=12;n_us++)
  {
       /* ������ � ���� */
     for(k=0;k<=63;k++)    /* ������  */
       {
        fprintf(tr,"%d ",k);
        fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][0][k],osl[n_us][0][k],kad_acp[n_us][0][k]);
        fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][1][k],osl[n_us][1][k],kad_acp[n_us][1][k]);
        fprintf(tr,"%.2f %.2f %d ",P_izm[n_us][2][k],osl[n_us][2][k],kad_acp[n_us][2][k]);
        fprintf(tr,"%.2f %.2f %d \n",P_izm[n_us][3][k],osl[n_us][3][k],kad_acp[n_us][3][k]);
       }   /*  end for */
  } /* end n_us*/

}/* if*/
   fclose(tr);

m1:;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::B_16Click(TObject *Sender)
{ //������ FLASH ����
   int nk = 0;
   const int nkio = 1; //����� ��� ����
   const u8 ips_out = 4; //IPS ���������� ������
  // const u8 ips_in = 5; //IPS ��������� ������
   u8 dst=0x0;
   //u8 dst = (RadioButton8->Checked)? DA_PPA52L_UPPU: DA_PPA52P_UPPU;
   // u32 addr = 0x200000, //��������� ����� ������ ������� FLASH
    u32 addr,// = 0x21FFF0 -- ������� 4-��� � 5-��� ��������, ��������� ����� ������ ������� FLASH
     cnt = StrToInt(E1_rd->Text); //0x10000; //���-�� ������� ������
   const u32 sz = 64; //������ �������
    unsigned IPK_UP7;
  u32 buf_my[256/4]; // ����� ��� ��������� ������

  union{
       struct{
                  U32   len     : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8;
            } p_my_v;
             U32 buf_my[256/4];
             } packet_my;

 union{
       struct{
                  U32   len     : 8, /*LEN*/
                        byte1   : 8, /*IPK*/
                        byte2   : 8, /*DST SRC*/
                        byte3   : 8; /*IPS DST*/
             } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;


   FILE *f = fopen(E_1->Text.c_str(), "wb");
   if (!f)
   {
      ShowMessage("�� ���� ������� ���� �� ������!");
      return;
   }

   //Timer2->Enabled = false;
    addr=(strtoul(Ed_adr->Text.c_str(),NULL,16)); /* ������ ��������. ����� */


   Screen->Cursor = crHourGlass;
   Application->ProcessMessages();

  for (u32 i = 0; i < cnt; i += sz)
    {
      memset(&packet_my, 0, sizeof(packet_my));
    //  pack_uppu.p.len = 8; //LEN
    //  pack_uppu.p.byte1 = 0xff; //IPK (��. ������� ���������� ������)
    //  pack_uppu.p.byte2 = dst << 5; //DST (���� ���./����.)
    //  pack_uppu.p.byte3 = ips_out << 2; //IPS
   //   pack_uppu.buf[1] = addr + i; //����� ������ FLASH

      packet_my.p_my_v.len = 8; //LEN
      packet_my.p_my_v.byte1 = 0xff; //IPK (��. ������� ���������� ������)
      packet_my.p_my_v.byte2 = dst << 5; //DST (���� ���./����.)
      packet_my.p_my_v.byte3 = ips_out << 2; //IPS
      packet_my.buf_my[1] = addr + i; //����� ������ FLASH

    if (!UPS_SEND_KIO_PACKET(nkio, packet_my.buf_my))
       {
         ShowMessage("������ ��� �������� ������ �� ��� (����)");
         fclose(f);
          Screen->Cursor = crDefault;
         //Timer2->Enabled = true;
         return;
       }
      Sleep(200);//Wait(100);
   //   UPS_RECIV_KIO_PACKET(&nk, packet_my_km.buf_my); //������� FIFO
      Sleep(200);
      memset(&packet_my_km, 0, sizeof(packet_my_km));
       //|| !(packet_my_km.buf[0] & 0xff) ||
          //(nk != nkio) || ((packet_my_km.p_my_v.byte3 >> 2) != ips_in) || (packet_my_km.p_my_v.byte2 != dst))
       if (!UPS_RECIV_KIO_PACKET(&nk, packet_my_km.buf_my))
         {
          ShowMessage("������ ��� ������ ������ �� ��� (����)");
         fclose(f);
          Screen->Cursor = crDefault;
         //Timer2->Enabled = true;
         return;
         }
      fwrite((u16*)&packet_my_km.buf_my[1], 2, sz, f);
      //fflush(f);
    }
   fclose(f);
    Screen->Cursor = crDefault;
    ShowMessage("������ FLASH ���������");
  }
//----------------------------������� FLASH-----------------------------------------------
 void __fastcall TForm1::Button16Click(TObject *Sender)
{
//������� FLASH ����
   int nk = 0;
   int  j;
   const int nkio = 1; //����� ��� ����
   const u8 ips_out = 2; //IPS ���������� ������
   //const u8 ips_in = 3; //IPS ��������� ������
   u8 dst = 0x0;
   u32 addr = 0x200000, //��������� ����� ������� ������� FLASH
       cnt = 4; //���-�� �������� �������
     unsigned IPK_UP7;
     unsigned sbros_pk;

  U32 abuf[]={0x900011};
  U32 dbuf[]={0};
  U32 len_my=1; /* len_my=10;*/

  u32 buf_my[256/4]; // ����� ��� ��������� ������

  union{
       struct{
                  U32   len     : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8;
            } p_my_v;
             U32 buf_my[256/4];
             } packet_my;

 union{
       struct{
                  U32   len     : 8, /*LEN*/
                        byte1   : 8, /*IPK*/
                        byte2   : 8, /*DST SRC*/
                        byte3   : 8; /*IPS DST*/
             } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;

   //Timer2->Enabled = false;
// for(j=0;j<=1;j++)
//  {
//  if(j==1) Sleep(1000);
   for (u32 i = 0; i < cnt; i++){
      memset(&packet_my, 0, sizeof(packet_my));
     // pack_uppu.p.len = 8; //LEN
     // pack_uppu.p.byte1 = 0xff; //IPK (��. ������� ���������� ������)
    //  pack_uppu.p.byte2 = dst << 5; //DST (���� ���./����.)
    //  pack_uppu.p.byte3 = ips_out << 2; //IPS
    //  pack_uppu.buf[1] = addr + i*0x8000; //����� ������� FLASH

      packet_my.p_my_v.len = 8; //LEN
      packet_my.p_my_v.byte1 = 0xff; //IPK (��. ������� ���������� ������)
      packet_my.p_my_v.byte2 = dst << 5; //DST (���� ���./����.)
      packet_my.p_my_v.byte3 = ips_out << 2; //IPS
      packet_my.buf_my[1] = addr + i*0x8000; //����� ������� FLASH
     // packet_my.buf_my[1] = addr; //����� ������� FLASH

      if (!UPS_SEND_KIO_PACKET(nkio, packet_my.buf_my))
      {
         ShowMessage("������ ��� �������� ������ �� ��� (����)");
         //Timer2->Enabled = true;
         return;
      }
      //Wait(200);
     Sleep(200);
 //3.08.12  UPS_RECIV_KIO_PACKET(&nk, packet_my_km.buf_my); //������� FIFO
      memset(&packet_my_km, 0, sizeof(packet_my_km));
 //     if (!UPS_RECIV_KIO_PACKET(&nk, pack_uppu.buf) || !(pack_uppu.buf[0] & 0xff) ||
  //        (nk != nkio) || ((pack_uppu.p.byte3 >> 2) != ips_in) || (pack_uppu.p.byte2 != dst))
      if (!UPS_RECIV_KIO_PACKET(&nk, packet_my_km.buf_my))
          {
         ShowMessage("������ ��� ������ ������ �� ��� (����)");
         //Timer2->Enabled = true;
         return;
         }
  }

       /* ����� ���� */
     sbros_pk = 0x0;

  dbuf[0]= sbros_pk&0x1;
        Sleep(1000);
       sbros_pk = 0x1;
  dbuf[0]= sbros_pk&0x1;
   // UpsWriteMemBuf32(U32 *addr_buf,U32 *data_buf,U32 len)
    if(FmLib-> UpsWriteMemBuf32(abuf,dbuf,len_my)==true){;}
    //  if(WriteMemBuf32(abuf,dbuf,SIZE(abuf))==true){;}
      else
        {
          ShowMessage("������ ��� ������!");
          goto end;
        }
         //ShowMessage("����� ������!");
//  }/* end j*/
 end:;
    ShowMessage("������� FLASH ���������");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button25Click(TObject *Sender)
{
//������ FLASH ����
   int nk = 0, rd = 0;
   const int nkio = 1; //����� ��� ����
   const u8 ips_out = 6; //IPS ���������� ������
  // const u8 ips_in = 7; //IPS ��������� ������
   u8 dst = 0x0;
   u32 addr = 0x200000;//, addr_h = 0x220000, //��������� �����, ����� ���������
   u32 cnt = 0; //���-�� ������� ������
   const u32 sz = 64; //������ �������
   u16 crc = 0;
   u32 buf_my[256/4]; // ����� ��� ��������� ������
   u32 sh_i=0,sh_i_i=0;

   String str;
   //int n_sh;
   int jk,ret;

  union{
       struct{
                  U32   len     : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8;
            } p_my_v;
             U32 buf_my[256/4];
             } packet_my;

// union{
//       struct{
//                  U32   len     : 8, /*LEN*/
//                        byte1   : 8, /*IPK*/
//                        byte2   : 8, /*DST SRC*/
//                        byte3   : 8, /*IPS DST*/
//                        byte4   : 8; /*ERR*/
//             } p_my_v;
//             U32 buf_my[256/4];
//             } packet_my_km;

    str=E1_zp_fl->Text;
    FILE *f = fopen(str.c_str(), "rb");      /* mrt.000 -������� ����,*/
   if (!f){
      ShowMessage("�� ���� ������� ���� �� ������!");
      return;
   }
   cnt = FileSize(f);
   crc = GetCRC(f, cnt); /* ��������� ����������� ����� */
   cnt >>= 1;   //���-�� 16�� ����. ����

//   //Timer2->Enabled = false;

   Screen->Cursor = crHourGlass;
   Application->ProcessMessages();
   sh_i=0;
  for (u32 i = 0; i < cnt; i += sz){
  // for (u32 i = 0; i<cnt+1; i += sz){
      memset(&packet_my, 0, sizeof(packet_my));
      packet_my.p_my_v.len = 8 + sz * 2; //LEN
      packet_my.p_my_v.byte1 = 0xff; //IPK (��. ������� ���������� ������)
      packet_my.p_my_v.byte2 = dst << 5; //DST (���� ���./����.)
      packet_my.p_my_v.byte3 = ips_out << 2; //IPS
      packet_my.buf_my[1] = addr + i; //����� ������ FLASH
         sh_i=i;
      rd = fread((u16*)&packet_my.buf_my[2], 2, sz, f);    /* ������ 64 ������ ������ ������ 2 ����� � ����� ������ */
      if(i==0x1FFC0){              /*131008*/
                     packet_my.buf_my[33]=packet_my.buf_my[33]|(crc<<16);
                    }


  //25.03.2011     n_sh=0;
  //     m_n_sh:;
  //     Sleep(10);
  //    if (!UPS_SEND_KIO_PACKET(nkio, packet_my.buf_my)){
  //       ShowMessage("������ ��� �������� ������ �� ��� (����)");
  //       fclose(f);
  //       //Timer2->Enabled = true;
  //       Screen->Cursor = crDefault;
  //       return;
  //    }
     // Wait(10);
  //     Sleep(20);


   //  UPS_RECIV_KIO_PACKET(&nk, packet_my_km.buf_my); //������� FIFO
   //   memset(&packet_my_km, 0, sizeof(packet_my_km));
   //  if(!UPS_RECIV_KIO_PACKET(&nk, packet_my_km.buf_my)||(packet_my_km.p_my_v.byte4 & 1))
   //   {
   //       if(n_sh>9)
   //       {
    //     ShowMessage("������ ��� ������ ������ �� ��� (����)");
    //     fclose(f);
    //     //Timer2->Enabled = true;
    //     Screen->Cursor = crDefault;
     //    return;
     //    }
     //    else{n_sh=n_sh+1; goto m_n_sh;}
     // }

    jk=0;
m1:
  Sleep(10);
    if(UPS_SEND_KIO_PACKET (nkio,packet_my.buf_my) == true){;}
         else{
             //ShowMessage("������ �������� ������ 3!");
            //return(1);   ������ �� ������
            }
  /* ����� ��������� ������ */
    ret=otvet_paket_zap();

 if(ret==1)
   {
    jk=jk+1; if(jk<=9) goto m1; else
     {
       ShowMessage("������ ��� ������ ������ �� ��� (����)");
         fclose(f);
        //Timer2->Enabled = true;
         Screen->Cursor = crDefault;
         return;
     }
  }

  if(ret==2){
             //ShowMessage("��� �������� ������� �� ����� 2!");
             ShowMessage("��� �������� ������� �� ����� ������ �� FLASH!");
              fclose(f);
              //Timer2->Enabled = true;
              Screen->Cursor = crDefault;
              return;
              }
   if(ret==0) {;}
 } /*end for i*/
       sh_i_i=sh_i;
  fclose(f); /* ��������� ������ �� ����������� ����� */

//   memset(&packet_my, 0, sizeof(packet_my));
//   packet_my.p_my_v.len = 10; //16 LEN
//   packet_my.p_my_v.byte1 = 0xff; //IPK (��. ������� ���������� ������)
//   packet_my.p_my_v.byte2 = dst << 5; //DST (���� ���./����.)
//   packet_my.p_my_v.byte3 = ips_out << 2; //IPS
//   packet_my.buf_my[1] = addr_h; //����� ���������
//  // packet_my.buf_my[2] = cnt; //���-�� ����
//   packet_my.buf_my[2] = crc; //�����. �����

//25.03.2011 //  if (!UPS_SEND_KIO_PACKET(nkio, packet_my.buf_my)){
//      ShowMessage("������ ��� �������� ������ �� ��� (����)");
////      //Timer2->Enabled = true;
//      Screen->Cursor = crDefault;
//      return;
//   }
//    Sleep(50);
//   UPS_RECIV_KIO_PACKET(&nk, packet_my_km.buf_my); //������� FIFO
//     n_sh=0;
//   m_n_sh_1: memset(&packet_my_km, 0, sizeof(packet_my_km));
//    Sleep(50);
//  if (!UPS_RECIV_KIO_PACKET(&nk, packet_my_km.buf_my)||(packet_my_km.p_my_v.byte4 & 1))
//     {
//      if(n_sh>9)
//       {
//      ShowMessage("������ ��� ������ ������ �� ��� (����)");
////      //Timer2->Enabled = true;
//      Screen->Cursor = crDefault;
//      return;
//      }
//      else{n_sh=n_sh+1; goto m_n_sh_1;}
//    }
//////////////////////////////////////////////////

//       jk=0;
// m1_1:
//  Sleep(10);
//    if(UPS_SEND_KIO_PACKET (nkio,packet_my.buf_my) == true){;}
//         else{
//             //ShowMessage("������ �������� ������ 3!");
//            //return(1);   ������ �� ������
//            }
//  /* ����� ��������� ������ */
//    ret=otvet_paket_zap();
//
// if(ret==1)
//   {
//    jk=jk+1; if(jk<=9) goto m1_1; else
//     {
//       ShowMessage("������ ��� ������ ������ �� ��� (����)");
//         //Timer2->Enabled = true;
//         Screen->Cursor = crDefault;
//         return;
//     }
//  }

//  if(ret==2){
//             //ShowMessage("��� �������� ������� �� ����� 2!");
//             ShowMessage("��� �������� ������� �� ����� ������ �� FLASH!(������ ����������� �����)");
//             //Timer2->Enabled = true;
//              Screen->Cursor = crDefault;
//             return;
//              }
//  if(ret==0) {;}

   //Timer2->Enabled = true;
   Screen->Cursor = crDefault;
   ShowMessage("������ FLASH ���������");

}
//---------------------------------------------------------------------------
unsigned long FileSize(FILE *file)
{//���������� ������ ��������� �����
    unsigned long pos, fsize;
    if (!file)
       return 0;
    pos = ftell(file);
    fseek(file, 0, 2);
    fsize = ftell(file);
    fseek(file, pos, 0);
    return fsize;
}
//---------------------------------------------------------------------------
unsigned long FileSize(const char *file_name)
{//������ ����� �� ��������
    unsigned long pos, fsize;
    FILE *file = fopen(file_name, "rb");
    if (!file)
       return 0;
    fseek(file, 0 , 2);
    fsize = ftell(file);
    fclose(file);
    return fsize;
}
//---------------------------------------------------------------------------
u16 GetCRC(FILE *file,u32 fsize)
{
   u32 pos;
  // const u32 sz = 64; //������ �������
   u16 crc = 0;
   const u32 buf_sz = 131072;
   u16 buf[buf_sz], tmp;

   if ((!file) || (!fsize))
       return 0;
   pos = ftell(file);
   fseek(file, 0, 0);

   fread(buf, 1, fsize, file);
   fsize >>= 1;

   for (u32 i = 0; i < fsize; i++)
      crc += buf[i];
   fseek(file, pos, 0);
   crc = 0x55aa - crc;
   return crc;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::B26_cmpClick(TObject *Sender)
{
 //��������� FLASH ����
   int nk = 0;
   const int nkio = 1; //����� ��� ����
   const u8 ips_out = 4; //IPS ���������� ������
   //const u8 ips_in = 5; //IPS ��������� ������
   u8 dst = 0;
   u32 addr = 0x200000, addr_crcc = 0x21ffff, //��������� ����� ������ ������� FLASH
       cnt = 0, //���-�� ������� ������
       rd = 0;
   const u32 sz = 64; //������ �������
   u16 crc = 0, crcc = 0, buf[sz] = {0};
   u32 buf_my[256/4]; // ����� ��� ��������� ������

   String str;

  union{
       struct{
                  U32   len     : 8,
                        byte1   : 8,
                        byte2   : 8,
                        byte3   : 8;
            } p_my_v;
             U32 buf_my[256/4];
             } packet_my;

 union{
       struct{
                  U32   len     : 8, /*LEN*/
                        byte1   : 8, /*IPK*/
                        byte2   : 8, /*DST SRC*/
                        byte3   : 8; /*IPS DST*/
             } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;

    str=E1_zp_fl->Text;
    FILE *f = fopen(str.c_str(), "rb");      /* mrt.000 -������� ����,mrt.102-- ������ ��� 1-�� ����� ��� 2-� ������  */
   if (!f){
      ShowMessage("�� ���� ������� ���� �� ������!");
      return;
   }
   cnt = FileSize(f);
   crc = GetCRC(f, cnt);
   cnt >>= 1;   //���-�� 16�� ����. ����

   //Timer2->Enabled = false;
   Screen->Cursor = crHourGlass;

   for (u32 i = 0; i < cnt; i += rd){
      memset(&packet_my, 0, sizeof(packet_my));
      packet_my.p_my_v.len = 8; //LEN
      packet_my.p_my_v.byte1 = 0xff; //IPK (��. ������� ���������� ������)
      packet_my.p_my_v.byte2 = dst << 5; //DST (���� ���./����.)
      packet_my.p_my_v.byte3 = ips_out << 2; //IPS
      packet_my.buf_my[1] = addr + i; //����� ������ FLASH

      if (!UPS_SEND_KIO_PACKET(nkio, packet_my.buf_my)){
         ShowMessage("������ ��� �������� ������ �� ��� (����)");
         fclose(f);
         //Timer2->Enabled = true;
         Screen->Cursor = crDefault;
         return;
      }

    //  Wait(10);
      Sleep(20);
   //3.08.12   UPS_RECIV_KIO_PACKET(&nk, packet_my_km.buf_my); //������� FIFO
      memset(&packet_my_km, 0, sizeof(packet_my_km));
      //if (!UPS_RECIV_KIO_PACKET(&nk, packet_my.buf_my) || !(pack_uppu.buf[0] & 0xff) ||
      //    (nk != nkio) || ((pack_uppu.p.byte3 >> 2) != ips_in) || (pack_uppu.p.byte2 != dst)){
      if(!UPS_RECIV_KIO_PACKET(&nk, packet_my_km.buf_my))
        {
         ShowMessage("������ ��� ������ ������ �� ��� (����)");
         fclose(f);
         //Timer2->Enabled = true;
         Screen->Cursor = crDefault;
         return;
      }

      rd = fread(buf, 2, sz, f); /*�� ����� */
      if (memcmp(buf, &packet_my_km.buf_my[1], 2*rd) != 0){
         ShowMessage("������� �������!");
         fclose(f);
         //Timer2->Enabled = true;
         Screen->Cursor = crDefault;
         return;
      }
      //fflush(f);
   }
   fclose(f);

   memset(&packet_my, 0, sizeof(packet_my));
   packet_my.p_my_v.len = 8; //LEN
   packet_my.p_my_v.byte1 = 0xff; //IPK (��. ������� ���������� ������)
   packet_my.p_my_v.byte2 = dst << 5; //DST (���� ���./����.)
   packet_my.p_my_v.byte3 = ips_out << 2; //IPS
   packet_my.buf_my[1] = addr_crcc; //����� ������ FLASH

   if (!UPS_SEND_KIO_PACKET(nkio, packet_my.buf_my)){
      ShowMessage("������ ��� �������� ������ �� ��� (����)");
      //Timer2->Enabled = true;
      Screen->Cursor = crDefault;
      return;
   }

 //  Wait(10);
   Sleep(20);
 //3.08.12  UPS_RECIV_KIO_PACKET(&nk, packet_my_km.buf_my); //������� FIFO
   memset(&packet_my_km, 0, sizeof(packet_my_km));
  // if (!UPS_RECIV_KIO_PACKET(&nk, packet_my_km.buf_my) || !(pack_uppu.buf[0] & 0xff) ||
  //    (nk != nkio) || ((pack_uppu.p.byte3 >> 2) != ips_in) || (pack_uppu.p.byte2 != dst)){
    if (!UPS_RECIV_KIO_PACKET(&nk, packet_my_km.buf_my))
      {
      ShowMessage("������ ��� ������ ������ �� ��� (����)");
      //Timer2->Enabled = true;
      Screen->Cursor = crDefault;
      return;
   }
   crcc = packet_my_km.buf_my[1];
   if (crc != crcc){
      ShowMessage("����������� ����� �� ���������!");
      //Timer2->Enabled = true;
   }
   //Timer2->Enabled = true;
   Screen->Cursor = crDefault;
    ShowMessage("��������� FLASH ���������");
 }

//---------------------------------------------------------------------------
int TForm1::otvet_paket_zap(void) /* 0-- ��� ������; 1-- ���� ������ (ERR=1); 2-- ��� �������� �������*/
{
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  int jk;
  int nk;

  unsigned IPK_UP7;


  u32 buf_my[256/4]; // ����� ��� ��������� ������

   union{
       struct{
                  U32   len     : 8, /*LEN*/
                        byte1   : 8, /*IPK*/
                        byte2   : 8, /*DST SRC*/
                        byte3   : 8, /*IPS DST*/
                        byte4   : 8; /*ERR*/
             } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;

   /* ����� ��������� ������ */
 for(jk=0;jk<=9;jk++)
   {
    memset(&packet_my_km, 0, sizeof(packet_my_km));
    if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
      {
       // ��� �������� �������
       Sleep(1);
       if(jk==9)
       {
     //  ShowMessage("��� �������� ������� �� ����� (2)!");
       return 2; //goto m2_end;
       }
     }
     else break;
   } /* end for*/
        // ������ �����
        LEN=packet_my_km.p_my_v.len;
        IPK=packet_my_km.p_my_v.byte1;
        SRC=packet_my_km.p_my_v.byte2&0x1F;
        DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my_km.p_my_v.byte3&0x3)<<3);  /* ����� ����� DST=0x6, ������ ����� DST=0x7*/
        IPS=(packet_my_km.p_my_v.byte3>>2)&0x3F;
        ERR=packet_my_km.p_my_v.byte4&0x1;
      //�������� 25.03.2011 ������ ��� ������ ����������� ����� if(ERR==1) {
      //              // ShowMessage("������ ��� �������� ������ �� ������ �� FLASH ERR=1");
      //               return 1;
      //              }

  //  m2_end:;
   return 0;
}

void __fastcall TForm1::Write_MRT(TObject *Sender)
{
 extern double F_rtu[224];
  double freq;
 // char buf1[256]={0};

Panel8->Visible=true;
P_1->Visible=false;
Panel1->Visible=false;
Panel2->Visible=false;
PanelPotent->Visible=false;
Mode=1;
}
//-----------------------���----------------------------------------------------
void __fastcall TForm1::Button41Click(TObject *Sender)
{
if(ChkDevs==true)       /** ������ ����������� ��� ������ ***/
 Calib52_ACHX();
 else
 {
 if(FindDevises()==true)
  {
  if(ChekDev()==true)
  Calib52_ACHX();
 }    //FindDevises()
 }//else

}
//---------------------------------------------------------------------------
//---------------------���------------------------------------------------------
void TForm1::Calib52_ACHX(void)
{
extern bool vyh;
  ViStatus stat=0; // ���������� ���������� ���� ViStatus
  extern double F_rtu[224];

   double powerDBM=0.0;
   double m_freqq;
   double power;

   double K_nu=0.0;

 //char buf1[256]={0};
// char buf2[256]={0};

 char buf[256]={0};

  double P[64]={0.0};       /*���������� �������� � ��*/
  double P_dB[64]={0.0};    /*���������� �������� � ��*/

  double p_vt_izm;
  double P_max,P_min;
  float Pmin_v,Pmax_v,dP;
  int j,k,k1;
 //int num=0;
 //char rdbuffer[256]={0};

 int ind; //������ ������� � �������� ����������
 long longdown=0; /* �������� �������� ����������*/

 int m_p;
 float x_m_p;
 double m_p_1;  /* ��������, ���������� �� ����������*/

 //int k_att=0;
 //int k_max=0,k_min=0;

 double m_Pow;
 char buf1[256]={0};
  int n_post;
  unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
   int nk,nu;  /* ����� ���*/
                                  /* ������� ��� */
  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 �������� 00000, 00001,00010,00100,01000,10000*/
/* float Qvh_osl[32]={0.0,-0.75,-1.5,-2.25,-3.0,-3.75,-4.5,-5.25,-6.0,
                     -6.75,-7.5,-8.25,-9.0,-9.75,-10.5,-11.25,-12.0,
                     -12.75,-13.5,-14.25,-15.0,-15.75,-16.5,-17.25,-18.0,
                     -18.75,-19.5,-20.25,-21.0,-21.75,-22.5,-23.25};
*/
                  /* 5 �������� 00000, 00001,00010,00100,01000,10000*/
 /*float Qvh_osl[32]={-23.25,-22.5,-21.75,-21.0,-20.25,-19.5,-18.75,-18.0,
                     -17.25,-16.5,-15.75,-15.0,-14.25,-13.5,-12.75,-12.0,
                     -11.25,-10.5,-9.75,-9.0,-8.25,-7.5,-6.75,-6.0,-5.25,
                     -4.5,-3.75,-3.0,-2.25,-1.5,-0.75,0.0};

*/                     /* 5 �������� 00000, 00001,00010,00100,01000,10000*/


  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* �������� ��� */
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned kod_att[13];
  AnsiString str2[26]={"����� ���-1","����� ���-2","����� ���-3","����� ���-4",
                       "����� ���-5","����� ���-6","����� ���-7","����� ���-8",
                       "����� ���-9","����� ���-10","����� ���-11","����� ���-12","����� ���-13",
                       "����� ���-1","����� ���-2","����� ���-3","����� ���-4",
                       "����� ���-5","����� ���-6","����� ���-7","����� ���-8",
                       "����� ���-9","����� ���-10","����� ���-11","����� ���-12","����� ���-13"};

  AnsiString str1[4]={"1��-2","2��-2","3��-2","4��-2"};

  TChartSeries *Series[4]={LineSeries3,LineSeries4,LineSeries5,LineSeries6};

  u32 buf_my[256/4]; // ����� ��� ��������� ������

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
                        byte17  : 8, /*ADC12 */
                        byte18  : 8; /*ADC13 */

                        } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;
       unsigned ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8,ADC9,ADC10,ADC11,ADC12,ADC13;
       int ADC=0;
       unsigned IPK_UP7;
       float Kod_M[64]={0.0};

       int Kod_DM_izm[64]={0};
       //int Kod_DM_max=0;
       int Kod_min_km=0,Kod_max_km=0;
       int nf,n_jj;
       int mk;


        Series[0]->Clear();
        Series[1]->Clear();
        Series[2]->Clear();
        Series[3]->Clear();

        Chart_kvk->BottomAxis->SetMinMax(0,63);
        Chart_kvk->Title->Text->Clear();
        Chart_kvk->Title->Text->Add("P=P(f)");

       // Series[3]->Repaint();
         E_pmax->Text="";
         L_pmax_no1->Caption="                        ";

          E_km_s->Text="";
          E_max_ka->Text="";

          E_pmx_1->Text="";
          E_dm_2->Text="";

          E_kd_1->Text="";
          E_km_mx->Text="";
          E_kdm_1->Text="";


          Edit13->Text=" ";
          Edit14->Text="";
          Edit15->Text="";
          Edit16->Text="";

          Edit17->Text=" ";
          Edit18->Text="";
          Edit19->Text="";

       ShowMessage("������ ������ � �� ���������� �� ���� "+str1[CB_3_vh->ItemIndex]);

        ShowMessage("���������� ���������� �������� ����� ���������� 30�� � ������ "+str2[CB_10_vyh->ItemIndex]);

    /*    if(comm_vhod(CB_3_vh->ItemIndex))  //1 -- ������, 0 -- ��� ������
           {
             ShowMessage("�� �������� ���������� 1");
             goto end;
             }
     if(comm_vyhod(CB_10_vyh->ItemIndex))//1 -- ������, 0 -- ��� ������
            {
             ShowMessage("�� �������� ���������� 2");
             goto end;
             }
    */         
          Chart_kvk->Repaint();

        /* ����� 3*/
    for(i=0;i<=12;i++)
      {
      // US[i]=0x0;
       kod_att[i]=0xF;
      }
  //============/* �������� ������� ���� �������� ��� */====
   if(CB_10_vyh->ItemIndex<=12)
   {
    n_post=2;    /*���*/
    kod_att[CB_10_vyh->ItemIndex]= 0x0;//Q_vh[CB10_att_vyh->ItemIndex];
   }
  if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
    kod_att[CB_10_vyh->ItemIndex-13]= 0x0;//Q_vh[CB10_att_vyh->ItemIndex];/****?????****/
    }

   if((res=Vkl_att_t(n_post,kod_att))==1)   /*0-- ��� ������, 1-- ���� ������ */
     {
      ShowMessage("������ ��� �������� ��������� 3 ������ � ��7 ERR=1!\n");
      //goto end;
     }
 if(res==2) {ShowMessage("��� �������� ������� �� ����� 3!");}
           Sleep(1);


              /* ����� 1*/
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
 //============/* ��������� ������ ���������, ��������� ��������� ������� ��7 */========================================            /* ����� 1*/
  //n_post=2+(CB_2_ps->ItemIndex);
  if(CB_10_vyh->ItemIndex<=12)  /* 1--0: 2(���), 3(���)*/
   {
    n_post=2;    /*���*/
    nu=(CB_10_vyh->ItemIndex);    /*������ �� 0 �� 12*/  /* nu-- ����� ���������*/
    }
   if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
    nu=(CB_10_vyh->ItemIndex)-13;    /*������ �� 13 �� 25*/  /* nu-- ����� ���������*/
    }
  // nu=0;  /* ???? nu-- nu=(����� ���������*/

   if((res=Vkl_us_vip_t(n_post,nu))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ (1) � ��7!\n");
    // goto end;
    }
  if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");}
    Sleep(1);
 //*************************************************************************
   m_freqq=F_rtu[0];

   powerDBM = strtod(E2_p->Text.c_str(),NULL);

   K_nu = strtod(E_ks_1->Text.c_str(),NULL);
   if((K_nu>3.0)||(K_nu<0.0))
   {
    ShowMessage("�������� �������� ��������� ���������");
    goto end;
   }

    K_nu=(3.0-K_nu)/4.0;

  m_p_1=powerDBM-dPg[0];   /* � ������ ���������� ������ */

 /*15.12.10*/ //    power = -70.0;  //�������

 // ��������� �� ��������� ������� � ��������
 stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // �������
 stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // ��������
  if (stat != VI_SUCCESS)
  {
     ShowMessage("������ ��� ��������� �������� �� ���������");
     goto end;
  }
 // viPrintf(vigen,"PULM:STAT OFF\n");   // �������� ��� ���������
   viPrintf(viG,"OUTPut:STATe ON\n"); //�����.  ������� �� ����� ���-��

    longdown=0;

    viPrintf(viG,"*OPC?\n");

        while(!longdown)
    viScanf(viG,"%d", &longdown);

    viPrintf(viP,"ABORT\n");
   viPrintf(viP,"INIT:CONT ON\n");
   viPrintf(viP,"FETC?\n");
   viScanf(viP,"%t",buf);

    Sleep(1);
            /* ����� 2*/
    /*  ������� ��������� ���������������� ������ ������� ������� �� */
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������� ���  1-�� � 2-�� ������ ��� */=========================
          n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* �� 0 �� 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
      if(CB_10_vyh->ItemIndex>12) /* ���� ������ ���, �� ��������� ���*/
           n_post=3; /*���*/   /* ���� ������ ���, �� ��������� ���*/
           else  n_post=2;  nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
                 n_post=3;
           else  n_post=2; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
         if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
                 n_post=2;
           else  n_post=3;  nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
          if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
              n_post=2;
           else  n_post=3; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7!\n");
     //goto end;
    }

  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
   Sleep(1);
      /* ����� 2*/
 //============/* ��������� ������ ������ ������� �� ��� 1-��� � 2-��� ������ */========================================
//============/* ������� ���� ������� ��� ��� 1-��� � 2-��� ������ */==========================
   /* n_vh1 -- ����� ������ ������� ��� 1-��� ������ ��� 0--0xF (4 �������)*/
   /* n_vh2 -- ����� ������ ������� ��� 2-��� ������ ��� 0--0xF (4 �������)*/

       n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* �� 0 �� 7*/
  if(CB_3_vh->ItemIndex==0){in1_at=Qv_vh[CB10_att_vh->ItemIndex];in2_at=0x1F;n_post=2;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[CB10_att_vh->ItemIndex];n_post=2;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=Qv_vh[CB10_att_vh->ItemIndex];in2_at=0x1F;n_post=3;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[CB10_att_vh->ItemIndex];n_post=3;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

   if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7 ERR=1!\n");
     goto end1;
    }

    /* ����� ��������� ������ */
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
       Sleep(5);

      vyh=true;

  for(j=0; j<=63;j++)  /* ������ 2*/
// for(j=64; j<=223;j++)  /* ������ 53*/
  {
  // Application->ProcessMessages();
 //  if(vyh==false) goto end1;

    m_freqq=F_rtu[j];
    m_p_1=powerDBM-dPg[j];   /* � ������ ���������� ������ */
    stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // �������
     stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // ��������
  if (stat != VI_SUCCESS)
  {
     ShowMessage("������ ��� ��������� �������� �� ���������");
     goto end;
  }

    viPrintf(viP,"ABORT\n");
    viPrintf(viP,"INIT:CONT ON\n");
    viPrintf(viP,"FETC?\n");
    viScanf(viP,"%t",buf);

    m_Pow = atof(buf);
      ind=j;
   m_Pow=m_Pow-dPm[ind];   /*� ������ ���������� ������*/
    P_dB[j]=m_Pow;

        //  Pw=pow(10,Pdbm/10); //���       Pw=pow(10,-3)*pow(10,Pdbm/10);  //��

          m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

          P[j]=m_Pow;  /* �������� � �� */
         //  x_m_p=Qvh_osl[j];

        /* ������ ������� �������� */
                   /* ������ ���� �������� */
                         /* ����� 9*/
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//----------------������ ������ �������� ��� ������� ����������------------------------------
  if(CB_10_vyh->ItemIndex<=12)  /* � ����������� �� ������ */     {
     n_post=2; /*���*/
     }
  if(CB_10_vyh->ItemIndex>12)
     {
     n_post=3; /*���*/
     }
    nf=0x9;
 n_jj=0;

m_jj:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- ��� ������, 1-- ���� ������ */
   {
     ShowMessage("������ ��� �������� ��������� ������� ������ (9) � ��7!\n");
    // 10.01.11 vyh=false; goto end;
   }

  Sleep(10);
//17.07 if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07        // ��� �������� �������
//17.07 //     ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07   }

  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
//17.07        // ��� �������� �������
//17.07 //     ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07      if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("���� �� ����������!");
//17.07       vyh=false; goto end; //goto m2_end_5;
//17.07      }
   }
   else
   {
        // ������ �����

      LEN=packet_my_km.p_my_v.len;
      IPK=packet_my_km.p_my_v.byte1;
      SRC=packet_my_km.p_my_v.byte2&0x1F;
      DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* ����� ����� DST=0x6, ������ ����� DST=0x7*/
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
      ADC13=packet_my_km.p_my_v.byte18;

// 22.12.10
     if(CB_10_vyh->ItemIndex<=12)  /* � ����������� �� ������ */
       {
        if(CB_10_vyh->ItemIndex==0) ADC=ADC1&0xFF;
        if(CB_10_vyh->ItemIndex==1) ADC=ADC2&0xFF;
        if(CB_10_vyh->ItemIndex==2) ADC=ADC3&0xFF;
        if(CB_10_vyh->ItemIndex==3) ADC=ADC4&0xFF;
        if(CB_10_vyh->ItemIndex==4) ADC=ADC5&0xFF;
        if(CB_10_vyh->ItemIndex==5) ADC=ADC6&0xFF;
        if(CB_10_vyh->ItemIndex==6) ADC=ADC7&0xFF;
        if(CB_10_vyh->ItemIndex==7) ADC=ADC8&0xFF;
        if(CB_10_vyh->ItemIndex==8) ADC=ADC9&0xFF;
        if(CB_10_vyh->ItemIndex==9) ADC=ADC10&0xFF;
        if(CB_10_vyh->ItemIndex==10) ADC=ADC11&0xFF;
        if(CB_10_vyh->ItemIndex==11) ADC=ADC12&0xFF;
        if(CB_10_vyh->ItemIndex==12) ADC=ADC13&0xFF;
      }
    if(CB_10_vyh->ItemIndex>12)  /* � ����������� �� ������ */
      {
        if(CB_10_vyh->ItemIndex==13) ADC=ADC1&0xFF;
        if(CB_10_vyh->ItemIndex==14) ADC=ADC2&0xFF;
        if(CB_10_vyh->ItemIndex==15) ADC=ADC3&0xFF;
        if(CB_10_vyh->ItemIndex==16) ADC=ADC4&0xFF;
        if(CB_10_vyh->ItemIndex==17) ADC=ADC5&0xFF;
        if(CB_10_vyh->ItemIndex==18) ADC=ADC6&0xFF;
        if(CB_10_vyh->ItemIndex==19) ADC=ADC7&0xFF;
        if(CB_10_vyh->ItemIndex==20) ADC=ADC8&0xFF;
        if(CB_10_vyh->ItemIndex==21) ADC=ADC9&0xFF;
        if(CB_10_vyh->ItemIndex==22) ADC=ADC10&0xFF;
        if(CB_10_vyh->ItemIndex==23) ADC=ADC11&0xFF;
        if(CB_10_vyh->ItemIndex==24) ADC=ADC12&0xFF;
        if(CB_10_vyh->ItemIndex==25) ADC=ADC13&0xFF;
      }

        if(ERR==1)
         {
          //ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ ���� ��������! ERR=1");
          //goto m1;
           n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj;
            }
          else
            {
             ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ ���� ��������! ERR=1");
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
          Sleep(10);
        x_m_p=j;
        Series[3]->AddXY(x_m_p,P[j]);
        Series[3]->Repaint();

        Series[0]->AddXY(x_m_p,Kod_M[j]);
        Series[0]->Repaint();

        Chart_kvk->Repaint();

   }    /* end for �� ������� */

   for(k1=0,P_max=P_min=P[0]; k1<=63; k1+=1)  /* ���������� max �� ������ */
       {
        if(P[k1]>P_max) {P_max=P[k1];}//k_max=k1;}
        if(P[k1]<P_min) {P_min=P[k1];}//k_min=k1;}
       }

      Pmin_v=(float)P_min;
      Pmax_v=(float)P_max;
      dP=(float)fabs(P_max-P_min);

        memset(&buf1,0,20);
        sprintf(buf1,"%.2f",Pmin_v);
           Edit13->Text=buf1;
           Edit13->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%.2f",Pmax_v);

           Edit14->Text=buf1;
           Edit14->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%.2f",dP);

           Edit15->Text=buf1;
           Edit15->Repaint();

    for(k1=0,Kod_max_km=Kod_min_km=Kod_DM_izm[0]; k1<=63; k1+=1)  /* ���������� max �� ������ */
       {
        if(Kod_DM_izm[k1]>Kod_max_km) {Kod_max_km=Kod_DM_izm[k1];}//k_max=k1;}
        if(Kod_DM_izm[k1]<Kod_min_km) {Kod_min_km=Kod_DM_izm[k1];}//k_min=k1;}
       }

     //  dP=(float)fabs(P_max-P_min);

        memset(&buf1,0,20);
        sprintf(buf1,"%d",Kod_min_km);
           Edit17->Text=buf1;
           Edit17->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%d",Kod_max_km);

           Edit18->Text=buf1;
           Edit18->Repaint();

   end1:;                         /* ����� 2 */
 //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� � ������ ���  1-�� � 2-�� ������ ��� */=========================
          n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* �� 0 �� 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7 ERR=1!\n");
     //goto end;
    }
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
     Sleep(1);
                         /* ����� 1*/
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������ ���������, ���������� ��������� ������� ��7 */=========================
 if(CB_10_vyh->ItemIndex<=12)  /* 1--0: 2(���), 3(���)*/
   {
    n_post=2;    /*���*/
   // nu=(CB_10_vyh->ItemIndex);    /*������ �� 0 �� 12*/  /* nu-- ����� ���������*/
    }
   if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
   // nu=13-(CB_10_vyh->ItemIndex);    /*������ �� 13 �� 25*/  /* nu-- ����� ���������*/
    }
  // nu=0;  /* ???? nu-- nu=(����� ���������*/

   if((res=Vykl_us_vip_t(n_post))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ (1) � ��7 ERR=1!\n");
    // goto end;
    }
    if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");}
    Sleep(1);
   end:;
  viPrintf(viG,"OUTPut:STATe OFF\n"); //����. ������� �� ����� ���-��

    ShowMessage("��������� ���������\n");
//
}
//--------------------------��� (���. �� ����� ���������)-------------------------------------------------
void __fastcall TForm1::Button42Click(TObject *Sender)
{
 if(ChkDevs==true)       /** ������ ����������� ��� ������ ***/
 ACHX52_izm();
 else
 {
if(FindDevises()==true)
 {
 if(ChekDev()==true)
  ACHX52_izm();

 }    //FindDevises()
 }//else

//
}
//---------------------��� �� ����� ��������� ------------------------------------------------------
void TForm1::ACHX52_izm(void)
{
extern bool vyh;
  ViStatus stat=0;  // ���������� ���������� ���� ViStatus
  extern double F_rtu[224];

   double powerDBM=0.0;
   double m_freqq;
   double power;

   double K_nu=0.0;
 char buf[256]={0};

  double P[64]={0.0};       /*���������� �������� � ��*/
  double P_dB[64]={0.0};    /*���������� �������� � ��*/

 // double P_1=0;
  //double dP;
  double p_vt_izm;
  double P_max,P_min;
  float Pmin_v,Pmax_v,dP;
  int j,k,k1;

 int ind; //������ ������� � �������� ����������
 long longdown=0; /* �������� �������� ����������*/

 int m_p;
 float x_m_p;
 double m_p_1;  /* ��������, ���������� �� ����������*/

 //int k_att=0;
 //int k_max=0,k_min=0;

 double m_Pow;
 char buf1[256]={0};
  int n_post;
  unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
   int nk,nu;  /* ����� ���*/
                                 /* ������� ��� */
  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F};/* 5 �������� 00000, 00001,00010,00100,01000,10000*/
 float Qvh_osl_my[32]={0.0,-0.75,-1.5,-2.25,-3.0,-3.75,-4.5,-5.25,-6.0,
                     -6.75,-7.5,-8.25,-9.0,-9.75,-10.5,-11.25,-12.0,
                     -12.75,-13.5,-14.25,-15.0,-15.75,-16.5,-17.25,-18.0,
                     -18.75,-19.5,-20.25,-21.0,-21.75,-22.5,-23.25};


  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* �������� ��� */
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned kod_att[13];

   AnsiString str2[26]={"���1","���2","���3","���4",
                       "���5","���6","���7","���8",
                       "���9","���10","���11","���12","���13",
                       "���1","���2","���3","���4",
                       "���5","���6","���7","���8",
                       "���9","���10","���11","���12","���13"};

   AnsiString str1[4]={"1��-2","2��-2","3��-2","4��-2"};
  TChartSeries *Series[4]={LineSeries3,LineSeries4,LineSeries5,LineSeries6};

  u32 buf_my[256/4]; // ����� ��� ��������� ������

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
                        byte17  : 8, /*ADC12 */
                        byte18  : 8; /*ADC13 */

                        } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;
       unsigned ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8,ADC9,ADC10,ADC11,ADC12,ADC13;
       int ADC=0;
       unsigned IPK_UP7;
       float Kod_M[64]={0.0};

       int Kod_DM_izm[64]={0};
       int Kod_DM_max=0;
       int Kod_min_km=0,Kod_max_km=0;
       int nf,n_jj;
       int mk;
  //================================================
 AnsiString StNIn;
 AnsiString SbS,SbL,StIn;/*SbS_t;*/
 AnsiString MyFileName;
 int n_vh,nl,n_us,N_us;/*k*/

 float PP_izm[13][4][64]={0.0},osl[13][4][64]={0.0};
 int kad_acp[13][4][64]={0},k_f[64]={0};
 float Qsl_my=0.0;
 int kod_att_my=0,km;

 FILE *tr;
 StNIn=IntToStr(CB_3_vh->ItemIndex+1);  /* ������ ����*/

if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���*/
 {
  SbS="pps";
  N_us= CB_10_vyh->ItemIndex;
  }
else
  {
  SbS="zps";
  N_us= CB_10_vyh->ItemIndex-13;
  }
SbL="_2";
// SbL="_53";

 StIn=SbS+"_"+StNIn+SbL+".dan";
 MyFileName=StIn; //MyFileName="pps_1_2.dan";

 if(FileExists(MyFileName))
 {

 if((tr = fopen(MyFileName.c_str(),"r+")) == NULL)
  {
  ShowMessage("���������� ������� ����");
   goto m1;
  }
   /* ������� ������ �� ����� */

 for(n_us=0;n_us<=12;n_us++) /*�� 13 ���������� */
   {
   for(k=0;k<=63;k++)
       {
        fscanf(tr,"%d",&k_f[k]);
        fscanf(tr,"%f%f%d",&PP_izm[n_us][0][k],&osl[n_us][0][k], &kad_acp[n_us][0][k]);
        fscanf(tr,"%f%f%d",&PP_izm[n_us][1][k],&osl[n_us][1][k], &kad_acp[n_us][1][k]);
        fscanf(tr,"%f%f%d",&PP_izm[n_us][2][k],&osl[n_us][2][k], &kad_acp[n_us][2][k]);
        fscanf(tr,"%f%f%d",&PP_izm[n_us][3][k],&osl[n_us][3][k], &kad_acp[n_us][3][k]);
//        fscanf(tr,"%f%f%d",&PP_izm[n_us][4][k],&osl[n_us][4][k], &kad_acp[n_us][4][k]);
//        fscanf(tr,"%f%f%d",&PP_izm[n_us][5][k],&osl[n_us][5][k], &kad_acp[n_us][5][k]);
//        fscanf(tr,"%f%f%d",&PP_izm[n_us][6][k],&osl[n_us][6][k], &kad_acp[n_us][6][k]);
//        fscanf(tr,"%f%f%d\n",&PP_izm[n_us][7][k],&osl[n_us][7][k],&kad_acp[n_us][7][k]);
      } /* end k*/
    } /* end n_us */

   fclose(tr);

  }

        Series[0]->Clear();
        Series[1]->Clear();
        Series[2]->Clear();
        Series[3]->Clear();

        Chart_kvk->BottomAxis->SetMinMax(0,63);
        Chart_kvk->Title->Text->Clear();
        Chart_kvk->Title->Text->Add("P=P(f)");

         E_pmax->Text="";
         L_pmax_no1->Caption="                        ";

          E_km_s->Text="";
          E_max_ka->Text="";

          E_pmx_1->Text="";
          E_dm_2->Text="";

          E_kd_1->Text="";
          E_km_mx->Text="";
          E_kdm_1->Text="";


          Edit13->Text=" ";
          Edit14->Text="";
          Edit15->Text="";
          Edit16->Text="";

          Edit17->Text=" ";
          Edit18->Text="";
          Edit19->Text="";


       ShowMessage("������ ������ � �� ���������� �� ���� "+str1[CB_3_vh->ItemIndex]);

        ShowMessage("���������� ���������� �������� ����� ���������� 30�� � ������ "+str2[CB_10_vyh->ItemIndex]);

    /*  if(comm_vhod(CB_3_vh->ItemIndex))  //1 -- ������, 0 -- ��� ������
           {
             ShowMessage("�� �������� ���������� 1");
             goto end;
             }
     if(comm_vyhod(CB_10_vyh->ItemIndex))//1 -- ������, 0 -- ��� ������
            {
             ShowMessage("�� �������� ���������� 2");
             goto end;
             }
    */
         Chart_kvk->Repaint();

       /* ����� 3*/
    for(i=0;i<=12;i++)
      {
      // US[i]=0x0;
       kod_att[i]=0xF;
      }
  //============/* �������� ������� ���� �������� ��� */====
   if(CB_10_vyh->ItemIndex<=12)
   {
    n_post=2;    /*���*/
    kod_att[CB_10_vyh->ItemIndex]= Q_vh[CB10_att_vyh->ItemIndex];
   }
  if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
    kod_att[CB_10_vyh->ItemIndex-13]= Q_vh[CB10_att_vyh->ItemIndex];/****?????****/
    }

   if((res=Vkl_att_t(n_post,kod_att))==1)  /*0-- ��� ������, 1-- ���� ������ */
     {
      ShowMessage("������ ��� �������� ��������� 3 ������ � ��7 ERR=1!\n");
      //goto end;
     }
 if(res==2) {ShowMessage("��� �������� ������� �� ����� 3!");}
           Sleep(1);

    /* ����� 1*/
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ��������� ������ ���������, ��������� ��������� ������� ��7 */========================================

   if(CB_10_vyh->ItemIndex<=12) /* 1--0: 2(���), 3(���)*/
   {
    n_post=2;    /*���*/
    nu=(CB_10_vyh->ItemIndex);   /*������ �� 0 �� 12*/  /* nu-- ����� ���������*/
    }
   if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
    nu=(CB_10_vyh->ItemIndex)-13;   /*������ �� 13 �� 25*/  /* nu-- ����� ���������*/
    }
  // nu=0;
   if((res=Vkl_us_vip_t(n_post,nu))==1)  /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ (1) � ��7!\n");
    // goto end;
    }
  if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");}
    Sleep(1);
 //*************************************************************************
   m_freqq=F_rtu[0];

   powerDBM = strtod(E2_p->Text.c_str(),NULL);

   K_nu = strtod(E_ks_1->Text.c_str(),NULL);
   if((K_nu>3.0)||(K_nu<0.0))
   {
    ShowMessage("�������� �������� ��������� ���������");
    goto end;
   }

    K_nu=(3.0-K_nu)/4.0;

   m_p_1=powerDBM-dPg[0];  /* � ������ ���������� ������ */

 /*15.12.10*/ //    power = -70.0;  //�������

 // ��������� �� ��������� ������� � ��������
 stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // �������
 stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // ��������
  if (stat != VI_SUCCESS)
  {
     ShowMessage("������ ��� ��������� �������� �� ���������");
     goto end;
  }
 // viPrintf(vigen,"PULM:STAT OFF\n");   // �������� ��� ���������
   viPrintf(viG,"OUTPut:STATe ON\n"); //�����.  ������� �� ����� ���-��

    longdown=0;

    viPrintf(viG,"*OPC?\n");

        while(!longdown)
    viScanf(viG,"%d", &longdown);

    viPrintf(viP,"ABORT\n");
   viPrintf(viP,"INIT:CONT ON\n");
   viPrintf(viP,"FETC?\n");
   viScanf(viP,"%t",buf);

    Sleep(1);
           /* ����� 2*/
/*  ������� ��������� ���������������� ������ ������� ������� �� */
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������� ���  1-�� � 2-�� ������ ��� */=========================
          n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* io 0 ai 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
      if(CB_10_vyh->ItemIndex>12) /* ���� ������ ���, �� ��������� ���*/
           n_post=3;  /*���*/   /* ���� ������ ���, �� ��������� ���*/
           else  n_post=2;  nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           if(CB_10_vyh->ItemIndex<=12)  /* ���� ������ ���, �� ��������� ���*/
                 n_post=3;
           else  n_post=2; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
         if(CB_10_vyh->ItemIndex<=12)  /* ���� ������ ���, �� ��������� ���*/
                 n_post=2;
           else  n_post=3;  nk_svch=1;
        } /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
          if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
              n_post=2;
           else  n_post=3; nk_svch=2;
        } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)  /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7!\n");
     //goto end;
    }

  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
   Sleep(1);

    vyh=true;

 for(j=0; j<=63;j++) /* ������ 2*/
  {
  // Application->ProcessMessages();
 //  if(vyh==false) goto end1;
 /* ����� ������� �������� ���� �������� ���. �� ����� */
  for(km=0;km<=31;km++)
   {
    Qsl_my=osl[N_us][UD_2->Position-1][j];
    if(Qsl_my==Qvh_osl_my[km]) kod_att_my=km;
   }
  /* ����� 2*/
 //============/* ��������� ������ ������ ������� �� ��� 1-��� � 2-��� ������ */========================================
//============/* ������� ���� ������� ��� ��� 1-��� � 2-��� ������ */==========================
   /* n_vh1 -- ����� ������ ������� ��� 1-��� ������ ��� 0--0xF (4 �������)*/
   /* n_vh2 -- ����� ������ ������� ��� 2-��� ������ ��� 0--0xF (4 �������)*/

       n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* 0 - 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=Qv_vh[kod_att_my];in2_at=0x1F;n_post=2;nk_svch=1;
        }  /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[kod_att_my];n_post=2;nk_svch=2;
      }/* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=Qv_vh[kod_att_my];in2_at=0x1F;n_post=3;nk_svch=1;
        }  /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[kod_att_my];n_post=3;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/


   if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1) /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7 ERR=1!\n");
     goto end1;
    }
     /* ����� ��������� ������ */

  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
       Sleep(5);

    m_freqq=F_rtu[j];
    m_p_1=powerDBM-dPg[j];   /* � ������ ���������� ������ */
    stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // �������
     stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // ��������
  if (stat != VI_SUCCESS)
  {
     ShowMessage("������ ��� ��������� �������� �� ���������");
     goto end;
  }

    viPrintf(viP,"ABORT\n");
    viPrintf(viP,"INIT:CONT ON\n");
    viPrintf(viP,"FETC?\n");
    viScanf(viP,"%t",buf);

    m_Pow = atof(buf);
      ind=j;
   m_Pow=m_Pow-dPm[ind];  /*� ������ ���������� ������*/
    P_dB[j]=m_Pow;

        //  Pw=pow(10,Pdbm/10); //       Pw=pow(10,-3)*pow(10,Pdbm/10);  //

          m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

          P[j]=m_Pow;  /* �������� � �� */
         //  x_m_p=Qvh_osl[j];

          /* ������ ������� �������� */
                   /* ������ ���� �������� */
                         /* ����� 9*/
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//----------------������ ������ �������� ��� ������� ����������------------------------------

 if(CB_10_vyh->ItemIndex<=12)  /* � ����������� �� ������ */
  {
     n_post=2; /**/
     }
  if(CB_10_vyh->ItemIndex>12)
     {
     n_post=3; /**/
     }
    nf=0x9;
 n_jj=0;

m_jj:
  if((res=zapr_dan_up7(n_post,nf))==1) /*0-- ��� ������, 1-- ���� ������ */
   {
     ShowMessage("������ ��� �������� ��������� ������� ������ (9) � ��7!\n");
    // 10.01.11 vyh=false; goto end;
   }

  Sleep(10);
//17.07 if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07          // ��� �������� �������
//17.07 //     ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07   }

  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
//17.07        // ��� �������� �������
//17.07 //     ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07      if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("���� �� ����������!");
//17.07       vyh=false; goto end; //goto m2_end_5;
//17.07      }
   }
   else
   {

      LEN=packet_my_km.p_my_v.len;
      IPK=packet_my_km.p_my_v.byte1;
      SRC=packet_my_km.p_my_v.byte2&0x1F;
      DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* ����� ����� DST=0x6, ������ ����� DST=0x7*/
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
      ADC13=packet_my_km.p_my_v.byte18;

// 22.12.10
     if(CB_10_vyh->ItemIndex<=12) /* � ����������� �� ������ */
       {
        if(CB_10_vyh->ItemIndex==0) ADC=ADC1&0xFF;
        if(CB_10_vyh->ItemIndex==1) ADC=ADC2&0xFF;
        if(CB_10_vyh->ItemIndex==2) ADC=ADC3&0xFF;
        if(CB_10_vyh->ItemIndex==3) ADC=ADC4&0xFF;
        if(CB_10_vyh->ItemIndex==4) ADC=ADC5&0xFF;
        if(CB_10_vyh->ItemIndex==5) ADC=ADC6&0xFF;
        if(CB_10_vyh->ItemIndex==6) ADC=ADC7&0xFF;
        if(CB_10_vyh->ItemIndex==7) ADC=ADC8&0xFF;
        if(CB_10_vyh->ItemIndex==8) ADC=ADC9&0xFF;
        if(CB_10_vyh->ItemIndex==9) ADC=ADC10&0xFF;
        if(CB_10_vyh->ItemIndex==10) ADC=ADC11&0xFF;
        if(CB_10_vyh->ItemIndex==11) ADC=ADC12&0xFF;
        if(CB_10_vyh->ItemIndex==12) ADC=ADC13&0xFF;
      }
    if(CB_10_vyh->ItemIndex>12) /* � ����������� �� ������ */
      {
        if(CB_10_vyh->ItemIndex==13) ADC=ADC1&0xFF;
        if(CB_10_vyh->ItemIndex==14) ADC=ADC2&0xFF;
        if(CB_10_vyh->ItemIndex==15) ADC=ADC3&0xFF;
        if(CB_10_vyh->ItemIndex==16) ADC=ADC4&0xFF;
        if(CB_10_vyh->ItemIndex==17) ADC=ADC5&0xFF;
        if(CB_10_vyh->ItemIndex==18) ADC=ADC6&0xFF;
        if(CB_10_vyh->ItemIndex==19) ADC=ADC7&0xFF;
        if(CB_10_vyh->ItemIndex==20) ADC=ADC8&0xFF;
        if(CB_10_vyh->ItemIndex==21) ADC=ADC9&0xFF;
        if(CB_10_vyh->ItemIndex==22) ADC=ADC10&0xFF;
        if(CB_10_vyh->ItemIndex==23) ADC=ADC11&0xFF;
        if(CB_10_vyh->ItemIndex==24) ADC=ADC12&0xFF;
        if(CB_10_vyh->ItemIndex==25) ADC=ADC13&0xFF;
        }

        if(ERR==1)
         {
          //ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ ���� ��������! ERR=1");
          //goto m1;
           n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj;
            }
          else
            {
             ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ ���� ��������! ERR=1");
             goto m1_1;
            }
          }

         Kod_DM_izm[j]=ADC;
         Kod_M[j]=0.017*ADC;
       m1_1:;
     }
//    m2_end_5:;
 //   m2_end_3:;
 //====================================
          Sleep(10);
        x_m_p=j;
        Series[3]->AddXY(x_m_p,P[j]);
        Series[3]->Repaint();

        Series[0]->AddXY(x_m_p,Kod_M[j]);
        Series[0]->Repaint();

        Chart_kvk->Repaint();

   }   /* end for �� ������� */

  for(k1=0,P_max=P_min=P[0]; k1<=63; k1+=1)  /* ���������� max �� ������ */
       {
        if(P[k1]>P_max) {P_max=P[k1];}//k_max=k1;}
        if(P[k1]<P_min) {P_min=P[k1];}//k_min=k1;}
       }

      Pmin_v=(float)P_min;
      Pmax_v=(float)P_max;
      dP=(float)fabs(P_max-P_min);

        memset(&buf1,0,20);
        sprintf(buf1,"%.2f",Pmin_v);
           Edit13->Text=buf1;
           Edit13->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%.2f",Pmax_v);

           Edit14->Text=buf1;
           Edit14->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%.2f",dP);

           Edit15->Text=buf1;
           Edit15->Repaint();

    for(k1=0,Kod_max_km=Kod_min_km=Kod_DM_izm[0]; k1<=63; k1+=1)  /* end for �� ������� */
       {
        if(Kod_DM_izm[k1]>Kod_max_km) {Kod_max_km=Kod_DM_izm[k1];}//k_max=k1;}
        if(Kod_DM_izm[k1]<Kod_min_km) {Kod_min_km=Kod_DM_izm[k1];}//k_min=k1;}
       }

           memset(&buf1,0,20);
        sprintf(buf1,"%d",Kod_min_km);
           Edit17->Text=buf1;
           Edit17->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%d",Kod_max_km);

           Edit18->Text=buf1;
           Edit18->Repaint();

   end1:;
 /* ����� 2 */
 //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� � ������ ���  1-�� � 2-�� ������ ��� */=========================
    n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /*  0 -- 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=1;
        }  /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=1;
        } /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=2;
      }/* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)  /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7 ERR=1!\n");
     //goto end;
    }
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
     Sleep(1);

/* ����� 1*/
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������ ���������, ���������� ��������� ������� ��7 */=========================
 if(CB_10_vyh->ItemIndex<=11)   /* 1--0: 2(���), 3(���)*/
   {
    n_post=2;   /*���*/
       }
   if(CB_10_vyh->ItemIndex>11)
   {
    n_post=3; /*���*/
      }
  // nu=0;
   if((res=Vykl_us_vip_t(n_post))==1)  /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ (1) � ��7 ERR=1!\n");
    // goto end;
    }
    if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");}
    Sleep(1);
   end:;
  viPrintf(viG,"OUTPut:STATe OFF\n"); //����. ������� �� ����� ���-��

    ShowMessage("��������� ���������\n");

 m1:;
}
//------------------------��� (����)---------------------------------------------------
void __fastcall TForm1::Button43Click(TObject *Sender)
{
if(ChkDevs==true)       /** ������ ����������� ��� ������ ***/
 ACHX52_rucn();
 else
 {
if(FindDevises()==true)
 {
 if(ChekDev()==true)
  ACHX52_rucn();
 }    //FindDevises()
 }//else
//
}
//---------------------------------------------------------------------------
//---------------------���  ������ ------------------------------------------------------
void TForm1::ACHX52_rucn(void)
{
 extern bool vyh;
 extern bool circle;
  ViStatus stat=0; // ���������� ���������� ���� ViStatus
  extern double F_rtu[224];

   double powerDBM=0.0;
   double m_freqq;
   double power;

   double K_nu=0.0;

 //char buf1[256]={0};
// char buf2[256]={0};

 char buf[256]={0};

 // double P[160]={0.0};       /*���������� �������� � ��*/
 // double P_dB[160]={0.0};    /*���������� �������� � ��*/

  double P_1=0;
  //double dP;
  double p_vt_izm;
    int j,k,k1;
 //int num=0;
 //char rdbuffer[256]={0};

 int ind; //������ ������� � �������� ����������
 long longdown=0; /* �������� �������� ����������*/

 int m_p;
 float x_m_p;
 double m_p_1;  /* ��������, ���������� �� ����������*/
 int k_att=0;
 int k_max=0,k_min=0;

 double m_Pow;
 float P_izm;
 char buf1[256]={0};
  int n_post;
  unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
   int nk,nu;  /* ����� ���*/
                                  /* ������� ��� */
  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 �������� 00000, 00001,00010,00100,01000,10000*/
/* float Qvh_osl[32]={0.0,-0.75,-1.5,-2.25,-3.0,-3.75,-4.5,-5.25,-6.0,
                     -6.75,-7.5,-8.25,-9.0,-9.75,-10.5,-11.25,-12.0,
                     -12.75,-13.5,-14.25,-15.0,-15.75,-16.5,-17.25,-18.0,
                     -18.75,-19.5,-20.25,-21.0,-21.75,-22.5,-23.25};
*/
                  /* 5 �������� 00000, 00001,00010,00100,01000,10000*/
 float Qvh_osl[32]={-23.25,-22.5,-21.75,-21.0,-20.25,-19.5,-18.75,-18.0,
                     -17.25,-16.5,-15.75,-15.0,-14.25,-13.5,-12.75,-12.0,
                     -11.25,-10.5,-9.75,-9.0,-8.25,-7.5,-6.75,-6.0,-5.25,
                     -4.5,-3.75,-3.0,-2.25,-1.5,-0.75,0.0};

                     /* 5 �������� 00000, 00001,00010,00100,01000,10000*/


  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* �������� ��� */
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned kod_att[13];

  AnsiString str2[26]={"���1","���2","���3","���4",
                       "���5","���6","���7","���8",
                       "���9","���10","���11","���12","���13",
                       "���1","���2","���3","���4",
                       "���5","���6","���7","���8",
                       "���9","���10","���11","���12","���13"};
  AnsiString str1[4]={"1��-2","2��-2","3��-2","4��-2"};

  TChartSeries *Series[4]={LineSeries3,LineSeries4,LineSeries5,LineSeries6};

  u32 buf_my[256/4]; // ����� ��� ��������� ������

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
                        byte17  : 8, /*ADC12 */
                        byte18  : 8; /*ADC13 */

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


        Series[0]->Clear();
        Series[1]->Clear();
        Series[2]->Clear();
        Series[3]->Clear();

        Chart_kvk->BottomAxis->SetMinMax(0,63);
        Chart_kvk->Title->Text->Clear();
        Chart_kvk->Title->Text->Add("P=P(f)");

       // Series[3]->Repaint();

         E_pmax->Text="";
         L_pmax_no1->Caption="                        ";

          E_km_s->Text="";
          E_max_ka->Text="";

          E_pmx_1->Text="";
          E_dm_2->Text="";

          E_kd_1->Text="";
          E_km_mx->Text="";
          E_kdm_1->Text="";


         Edit13->Text="";
         Edit14->Text="";
         Edit15->Text="";

         Edit16->Text="";
         Edit19->Text=" ";

          Edit17->Text="";
          Edit18->Text="";
          Edit6->Text=" ";

          Edit7->Text="";

       ShowMessage("������ ������ � �� ���������� �� ���� "+str1[CB_3_vh->ItemIndex]);

        ShowMessage("���������� ���������� �������� ����� ���������� 30�� � ������ "+str2[CB_10_vyh->ItemIndex]);

     /*    if(comm_vhod(CB_3_vh->ItemIndex))  //1 -- ������, 0 -- ��� ������
           {
             ShowMessage("�� �������� ���������� 1");
             goto end;
             }
     if(comm_vyhod(CB_10_vyh->ItemIndex))//1 -- ������, 0 -- ��� ������
            {
             ShowMessage("�� �������� ���������� 2");
             goto end;
             }
      */       
         Chart_kvk->Repaint();

        /* ����� 3*/
    for(i=0;i<=12;i++)
      {
      // US[i]=0x0;
       kod_att[i]=0xF;
      }
  //============/* �������� ������� ���� �������� ��� */====
   if(CB_10_vyh->ItemIndex<=12)
   {
    n_post=2;    /*���*/
    kod_att[CB_10_vyh->ItemIndex]= Q_vh[CB10_att_vyh->ItemIndex];
   }
  if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
    kod_att[CB_10_vyh->ItemIndex-13]= Q_vh[CB10_att_vyh->ItemIndex];/****?????****/
    }

   if((res=Vkl_att_t(n_post,kod_att))==1)   /*0-- ��� ������, 1-- ���� ������ */
     {
      ShowMessage("������ ��� �������� ��������� 3 ������ � ��7 ERR=1!\n");
      goto end;
     }
 if(res==2) {ShowMessage("��� �������� ������� �� ����� 3!");goto end;}
           Sleep(1);


              /* ����� 1*/
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
 //============/* ��������� ������ ���������, ��������� ��������� ������� ��7 */========================================            /* ����� 1*/
  //n_post=2+(CB_2_ps->ItemIndex);
  if(CB_10_vyh->ItemIndex<=12)  /* 1--0: 2(���), 3(���)*/
   {
    n_post=2;    /*���*/
    nu=(CB_10_vyh->ItemIndex);    /*������ �� 0 �� 12*/  /* nu-- ����� ���������*/
    }
   if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
    nu=(CB_10_vyh->ItemIndex)-13;    /*������ �� 13 �� 25*/  /* nu-- ����� ���������*/
    }
  // nu=0;  /* ???? nu-- nu=(����� ���������*/

   if((res=Vkl_us_vip_t(n_post,nu))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ (1) � ��7!\n");
     goto end;
    }
  if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");goto end;}
    Sleep(1);
 //*************************************************************************
   TrackBar4->Position=29;
   m_freqq=F_rtu[TrackBar4->Position];

   powerDBM = strtod(E2_p->Text.c_str(),NULL);

   K_nu = strtod(E_ks_1->Text.c_str(),NULL);
   if((K_nu>3.0)||(K_nu<0.0))
   {
    ShowMessage("�������� �������� ��������� ���������");
    goto end;
   }

    K_nu=(3.0-K_nu)/4.0;

//  for(k=64; k<=223;k++) /* ����������� ind*/
//     {
//      if(F_rtu[k]==m_freqq){ind=k;break;}
//     }
   m_p_1=powerDBM-dPg[TrackBar4->Position];   /* � ������ ���������� ������ */

 /*15.12.10*/ //    power = -70.0;  //�������

 // ��������� �� ��������� ������� � ��������
 stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // �������
 stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // ��������
  if (stat != VI_SUCCESS)
  {
     ShowMessage("������ ��� ��������� �������� �� ���������");
     goto end;
  }
 // viPrintf(vigen,"PULM:STAT OFF\n");   // �������� ��� ���������
   viPrintf(viG,"OUTPut:STATe ON\n"); //�����.  ������� �� ����� ���-��

    longdown=0;

    viPrintf(viG,"*OPC?\n");

        while(!longdown)
    viScanf(viG,"%d", &longdown);

    viPrintf(viP,"ABORT\n");
   viPrintf(viP,"INIT:CONT ON\n");
   viPrintf(viP,"FETC?\n");
   viScanf(viP,"%t",buf);

    Sleep(1);
            /* ����� 2*/
    /*  ������� ��������� ���������������� ������ ������� ������� �� */
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������� ���  1-�� � 2-�� ������ ��� */=========================
          n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* �� 0 �� 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
      if(CB_10_vyh->ItemIndex>12) /* ���� ������ ���, �� ��������� ���*/
           n_post=3; /*���*/   /* ���� ������ ���, �� ��������� ���*/
           else  n_post=2;  nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
                 n_post=3;
           else  n_post=2; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
         if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
                 n_post=2;
           else  n_post=3;  nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
          if(CB_10_vyh->ItemIndex<=12) /* ���� ������ ���, �� ��������� ���*/
              n_post=2;
           else  n_post=3; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7!\n");
     goto end;
    }

  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
   Sleep(1);
      /* ����� 2*/
 //============/* ��������� ������ ������ ������� �� ��� 1-��� � 2-��� ������ */========================================
//============/* ������� ���� ������� ��� ��� 1-��� � 2-��� ������ */==========================
   /* n_vh1 -- ����� ������ ������� ��� 1-��� ������ ��� 0--0xF (4 �������)*/
   /* n_vh2 -- ����� ������ ������� ��� 2-��� ������ ��� 0--0xF (4 �������)*/

       n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* �� 0 �� 7*/
  if(CB_3_vh->ItemIndex==0){in1_at=Qv_vh[CB10_att_vh->ItemIndex];in2_at=0x1F;n_post=2;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[CB10_att_vh->ItemIndex];n_post=2;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=Qv_vh[CB10_att_vh->ItemIndex];in2_at=0x1F;n_post=3;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[CB10_att_vh->ItemIndex];n_post=3;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

   if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7 ERR=1!\n");
     goto end;
    }

    /* ����� ��������� ������ */
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
       Sleep(5);

   Series[1]->Clear();
   Series[3]->Clear();

  //   TrackBar3->Position=80;

     circle=true;             /*  ���������� */
  while(circle==true)
    {
     Application->ProcessMessages();
     m_freqq=F_rtu[TrackBar4->Position];
   // m_freqq=F_rtu[j];
  //  m_p_1=powerDBM-dPg[j];   /* � ������ ���������� ������ */
    m_p_1=powerDBM-dPg[TrackBar4->Position];   /* � ������ ���������� ������ */
    stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // �������
     stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // ��������
  if (stat != VI_SUCCESS)
  {
     ShowMessage("������ ��� ��������� �������� �� ���������");
     goto end;
  }

    viPrintf(viP,"ABORT\n");
    viPrintf(viP,"INIT:CONT ON\n");
    viPrintf(viP,"FETC?\n");
    viScanf(viP,"%t",buf);

    m_Pow = atof(buf);
    ind=TrackBar4->Position;
    m_Pow=m_Pow-dPm[TrackBar4->Position];   /*� ������ ���������� ������*/
    // P_dB[j-64]=m_Pow;

        //  Pw=pow(10,Pdbm/10); //���       Pw=pow(10,-3)*pow(10,Pdbm/10);  //��

          m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

         P_izm=(float)m_Pow;  /* �������� � �� */

        memset(&buf1,0,20);  /* ����� �� ����� */
        sprintf(buf1,"%.2f",P_izm);
           Edit16->Text=buf1;
           Edit16->Repaint();

           Sleep(10);
       // x_m_p=j-64;
        x_m_p=TrackBar4->Position;
        Series[1]->AddXY(x_m_p,P_izm);
        Series[1]->Repaint();

        Chart_kvk->Repaint();

        /* ������ ������� �������� */
                   /* ������ ���� �������� */
                         /* ����� 9*/
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//----------------������ ������ �������� ��� ������� ����������------------------------------
 if(CB_10_vyh->ItemIndex<=12)  /* � ����������� �� ������ */     {
     n_post=2; /**/
     }
  if(CB_10_vyh->ItemIndex>12)
     {
     n_post=3; /**/
     }
    nf=0x9;
 n_jj=0;

m_jj:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- ��� ������, 1-- ���� ������ */
   {
     ShowMessage("������ ��� �������� ��������� ������� ������ (9) � ��7!\n");
     circle=false; goto end;
   }

  Sleep(10);
//17.07 if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07        // ��� �������� �������
//17.07 //     ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07   }

  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
//17.07        // ��� �������� �������
//17.07 //     ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07      if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("���� �� ����������!");
//17.07       circle=false; goto end; //goto m2_end_5;
//17.07      }
   }
   else
   {
        // ������ �����

      LEN=packet_my_km.p_my_v.len;
      IPK=packet_my_km.p_my_v.byte1;
      SRC=packet_my_km.p_my_v.byte2&0x1F;
      DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* ����� ����� DST=0x6, ������ ����� DST=0x7*/
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
      ADC13=packet_my_km.p_my_v.byte18;

// 22.12.10
     if(CB_10_vyh->ItemIndex<=12)  /* � ����������� �� ������ */
       {
        if(CB_10_vyh->ItemIndex==0) ADC=ADC1&0xFF;
        if(CB_10_vyh->ItemIndex==1) ADC=ADC2&0xFF;
        if(CB_10_vyh->ItemIndex==2) ADC=ADC3&0xFF;
        if(CB_10_vyh->ItemIndex==3) ADC=ADC4&0xFF;
        if(CB_10_vyh->ItemIndex==4) ADC=ADC5&0xFF;
        if(CB_10_vyh->ItemIndex==5) ADC=ADC6&0xFF;
        if(CB_10_vyh->ItemIndex==6) ADC=ADC7&0xFF;
        if(CB_10_vyh->ItemIndex==7) ADC=ADC8&0xFF;
        if(CB_10_vyh->ItemIndex==8) ADC=ADC9&0xFF;
        if(CB_10_vyh->ItemIndex==9) ADC=ADC10&0xFF;
        if(CB_10_vyh->ItemIndex==10) ADC=ADC11&0xFF;
        if(CB_10_vyh->ItemIndex==11) ADC=ADC12&0xFF;
        if(CB_10_vyh->ItemIndex==12) ADC=ADC13&0xFF;
      }
    if(CB_10_vyh->ItemIndex>12)  /* � ����������� �� ������ */
      {
        if(CB_10_vyh->ItemIndex==13) ADC=ADC1&0xFF;
        if(CB_10_vyh->ItemIndex==14) ADC=ADC2&0xFF;
        if(CB_10_vyh->ItemIndex==15) ADC=ADC3&0xFF;
        if(CB_10_vyh->ItemIndex==16) ADC=ADC4&0xFF;
        if(CB_10_vyh->ItemIndex==17) ADC=ADC5&0xFF;
        if(CB_10_vyh->ItemIndex==18) ADC=ADC6&0xFF;
        if(CB_10_vyh->ItemIndex==19) ADC=ADC7&0xFF;
        if(CB_10_vyh->ItemIndex==20) ADC=ADC8&0xFF;
        if(CB_10_vyh->ItemIndex==21) ADC=ADC9&0xFF;
        if(CB_10_vyh->ItemIndex==22) ADC=ADC10&0xFF;
        if(CB_10_vyh->ItemIndex==23) ADC=ADC11&0xFF;
        if(CB_10_vyh->ItemIndex==24) ADC=ADC12&0xFF;
        if(CB_10_vyh->ItemIndex==25) ADC=ADC13&0xFF;
     }

        if(ERR==1)
         {
          //ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ ���� ��������! ERR=1");
          //goto m1;
           n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj;
            }
          else
            {
             ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ ���� ��������! ERR=1");
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
           Edit19->Text=buf1;
           Edit19->Repaint();

           Sleep(10);

   //     x_m_p=TrackBar3->Position;
   //     Series[2]->AddXY(x_m_p,Kod_M);
   //     Series[2]->Repaint();

        Chart_kvk->Repaint();

   }    /* end for �� ������� */

   end1:;                         /* ����� 2 */
 //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� � ������ ���  1-�� � 2-�� ������ ��� */=========================
          n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* �� 0 �� 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7 ERR=1!\n");
     //goto end;
    }
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
     Sleep(1);
                         /* ����� 1*/
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������ ���������, ���������� ��������� ������� ��7 */=========================
 if(CB_10_vyh->ItemIndex<=12)  /* 1--0: 2(���), 3(���)*/
   {
    n_post=2;    /*���*/
   }
   if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*���*/
   }

   if((res=Vykl_us_vip_t(n_post))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ (1) � ��7 ERR=1!\n");
    // goto end;
    }
    if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");}
    Sleep(1);
   end:;
  viPrintf(viG,"OUTPut:STATe OFF\n"); //����. ������� �� ����� ���-��

 //   ShowMessage("��������� ���������\n");
}
//------------------------��������� ���� � ������ -----------------------------
void __fastcall TForm1::Button44Click(TObject *Sender)
{
if(ChkDevs==true)       /** ������ ����������� ��� ������ ***/
 ACHX52_tabl();
 else
 {
if(FindDevises()==true)
 {
 if(ChekDev()==true)
  ACHX52_tabl();
 }    //FindDevises()
 }//else
//
}
//----------------------- ��������� ���� � ������ ----------------------------
void TForm1::ACHX52_tabl(void)
{
 extern double F_rtu[224];
  double freq;
  char buf1[256]={0};
  AnsiString str2[26]={"���1","���2","���3","���4",
                       "���5","���6","���7","���8",
                       "���9","���10","���11","���12","���13",
                       "���1","���2","���3","���4",
                       "���5","���6","���7","���8",
                       "���9","���10","���11","���12","���13"};
  AnsiString str1[4]={"1��-2","2��-2","3��-2","4��-2"};
 int j,k;
Panel11->Visible=true;
Panel9->Visible=false;
Panel10->Visible=false;
Panel1->Visible=false;
Panel2->Visible=false;
PanelPotent->Visible=false;
Mode=1;
 Label99->Caption="�������  P���  (��) � ����� �������� � ������ "+str1[CB_3_vh->ItemIndex];
 if(RG9->ItemIndex==0){
                   Label101->Caption="����� "+str2[0];
                   Label102->Caption="����� "+str2[1];
                   Label103->Caption="����� "+str2[2];
                   Label104->Caption="����� "+str2[3];
                   Label105->Caption="����� "+str2[4];
                   Label106->Caption="����� "+str2[5];
                   Label107->Caption="����� "+str2[6];
                   Label108->Caption="����� "+str2[7];
                   Label109->Caption="����� "+str2[8];
                   Label110->Caption="����� "+str2[9];
                   Label111->Caption="����� "+str2[10];
                   Label112->Caption="����� "+str2[11];
                   Label113->Caption="����� "+str2[12];
                   }

            else
               {
                   Label101->Caption="����� "+str2[13];
                   Label102->Caption="����� "+str2[14];
                   Label103->Caption="����� "+str2[15];
                   Label104->Caption="����� "+str2[16];
                   Label105->Caption="����� "+str2[17];
                   Label106->Caption="����� "+str2[18];
                   Label107->Caption="����� "+str2[19];
                   Label108->Caption="����� "+str2[20];
                   Label109->Caption="����� "+str2[21];
                   Label110->Caption="����� "+str2[22];
                   Label111->Caption="����� "+str2[23];
                   Label112->Caption="����� "+str2[24];
                   Label113->Caption="����� "+str2[25];
                }
        /* �������� �������*/
  for(k=1;k<=27;k++)    /* ������  */
   for(j=0;j<=7;j++)   /* �������  */
     {
     StringGrid2->Cells[j][k]=" ";
     }


}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button47Click(TObject *Sender)
{
 Panel11->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button46Click(TObject *Sender)
{
extern bool vyh;
 vyh=false;
}
//---------------------��������� ���� ����------------------------------------------------------
void __fastcall TForm1::Button45Click(TObject *Sender)
{
extern bool vyh;
  ViStatus stat=0; // ���������� ���������� ���� ViStatus
  extern double F_rtu[224];

   double powerDBM=0.0;
   double m_freqq;
   double power;

   double K_nu=0.0;

 char buf[256]={0};

  double P[64]={0.0};       /*���������� �������� � ��*/
  double P_dB[64]={0.0};    /*���������� �������� � ��*/

  double p_vt_izm;
  double P_max,P_min;
  float Pmin_v;/*,Pmax_v,dP;*/
  int j,k,k1;

 int ind; //������ ������� � �������� ����������
 long longdown=0; /* �������� �������� ����������*/

 int m_p;
 float x_m_p;
 double m_p_1;  /* ��������, ���������� �� ����������*/

 //int k_max=0,k_min=0;

 double m_Pow;
 //char buf1[256]={0};
  int n_post;
  unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
  int nk,nu;  /* ����� ���*/
                                  /* ������� ��� */
  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 �������� 00000, 00001,00010,00100,01000,10000*/

  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* �������� ��� */
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned kod_att[12];

  AnsiString str2[26]={"���1","���2","���3","���4",
                       "���5","���6","���7","���8",
                       "���9","���10","���11","���12","���13",
                       "���1","���2","���3","���4",
                       "���5","���6","���7","���8",
                       "���9","���10","���11","���12","���13"};
  AnsiString str1[4]={"1��-2","2��-2","3��-2","4��-2"};


  u32 buf_my[256/4]; // ����� ��� ��������� ������

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
                        byte17  : 8, /*ADC12 */
                        byte18  : 8; /*ADC13 */

                        } p_my_v;
             U32 buf_my[256/4];
             } packet_my_km;
       unsigned ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8,ADC9,ADC10,ADC11,ADC12,ADC13=0x0;
       int ADC=0;
       unsigned IPK_UP7;
       float Kod_M[64]={0.0};

       int Kod_DM_izm[64]={0};
      // int Kod_DM_max=0;
       int Kod_min_km=0,Kod_max_km=0;
       int nf,n_jj;
       int mk,n_us_t=0,n_l_t=0;

  Label99->Caption="�������  P���  (��) � ����� �������� � ������ "+str1[CB_3_vh->ItemIndex];

   PostMessage(StringGrid3->Handle, WM_MBUTTONDOWN, MK_LBUTTON,0);
   PostMessage(StringGrid3->Handle, WM_MBUTTONUP, MK_LBUTTON,0);

        /* ������� � ������� */
    for(j=0;j<=7;j=j+2)   /* �������  */
     {
      StringGrid3->Cells[j][0]="Pmin";
      StringGrid3->Cells[j+1][0]="��� ���";
     }

  ShowMessage("������ ������ � �� ���������� �� ���� "+str1[CB_3_vh->ItemIndex]);

  /*  if(comm_vhod(CB_3_vh->ItemIndex))  //1 -- ������, 0 -- ��� ������
           {
             ShowMessage("�� �������� ���������� 1");
             goto end;
            }
   */
   //*************************************************************************
   m_freqq=F_rtu[0];
   powerDBM = strtod(E2_p->Text.c_str(),NULL);

   K_nu = strtod(E_ks_1->Text.c_str(),NULL);
   if((K_nu>3.0)||(K_nu<0.0))
   {
    ShowMessage("�������� �������� ��������� ���������");
    goto end;
   }

    K_nu=(3.0-K_nu)/4.0;
   m_p_1=powerDBM-dPg[0];   /* � ������ ���������� ������ */

 /*15.12.10*/ //    power = -70.0;  //�������

 // ��������� �� ��������� ������� � ��������
 stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // �������
 stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // ��������
  if (stat != VI_SUCCESS)
  {
     ShowMessage("������ ��� ��������� �������� �� ���������");
     goto end;
  }
 // viPrintf(vigen,"PULM:STAT OFF\n");   // �������� ��� ���������
   viPrintf(viG,"OUTPut:STATe ON\n"); //�����.  ������� �� ����� ���-��

    longdown=0;

    viPrintf(viG,"*OPC?\n");

        while(!longdown)
    viScanf(viG,"%d", &longdown);

    viPrintf(viP,"ABORT\n");
   viPrintf(viP,"INIT:CONT ON\n");
   viPrintf(viP,"FETC?\n");
   viScanf(viP,"%t",buf);

    Sleep(1);

 for(n_us_t=0;n_us_t<=12;n_us_t++)/* ���� �� ������� */
  {
   if((n_us_t==0)&&(CheckBox21->Checked==false)) goto end_vhod;
   if((n_us_t==1)&&(CheckBox22->Checked==false)) goto end_vhod;
   if((n_us_t==2)&&(CheckBox23->Checked==false)) goto end_vhod;
   if((n_us_t==3)&&(CheckBox24->Checked==false)) goto end_vhod;
   if((n_us_t==4)&&(CheckBox25->Checked==false)) goto end_vhod;
   if((n_us_t==5)&&(CheckBox26->Checked==false)) goto end_vhod;
   if((n_us_t==6)&&(CheckBox27->Checked==false)) goto end_vhod;
   if((n_us_t==7)&&(CheckBox28->Checked==false)) goto end_vhod;
   if((n_us_t==8)&&(CheckBox29->Checked==false)) goto end_vhod;
   if((n_us_t==9)&&(CheckBox30->Checked==false)) goto end_vhod;
   if((n_us_t==10)&&(CheckBox31->Checked==false)) goto end_vhod;
   if((n_us_t==11)&&(CheckBox32->Checked==false)) goto end_vhod;
   if((n_us_t==12)&&(CheckBox33->Checked==false)) goto end_vhod;

    /* �������� ������ */
  for(j=0;j<=7;j++)   /* �������  */
    {
     StringGrid3->Cells[j][2*n_us_t+1]=" ";
    }
   /**** ������ ���������? ��� � ����������� �� ���������  ***/
  if(RG9->ItemIndex==0) ShowMessage("���������� ���������� �������� ����� ���������� 30�� � ������ "+str2[n_us_t]);
   else  ShowMessage("���������� ���������� �������� ����� ���������� 30�� � ������ "+str2[n_us_t+13]);

    //   if(comm_vyhod(n_us_t))//1 -- ������, 0 -- ��� ������
    //        {
    //         ShowMessage("�� �������� ���������� 2");
    //         goto end;
    //         }

    viPrintf(viG,"OUTPut:STATe ON\n"); //�����.  ������� �� ����� ���-��

  for(n_l_t=0;n_l_t<=3;n_l_t++)/* ���� �� ����� ������ ��������� */
    {
           /* ����� 3*/
    for(i=0;i<=12;i++)
      {
      // US[i]=0x0;
       kod_att[i]=0xF;
      }
  //============/* �������� ������� ���� �������� ��� */====
   if(RG9->ItemIndex==0)// (CB_53_vyh->ItemIndex<=11)
   {
    n_post=2;    /*���*/
//    kod_att[CB_10_vyh->ItemIndex]= Q_vh[CB10_att_vyh->ItemIndex];
      kod_att[n_us_t]=Q_vh[CB10_att_vyh->ItemIndex];
   }
  if(RG9->ItemIndex==1)//(CB_10_vyh->ItemIndex>11)
   {
    n_post=3; /*���*/
//    kod_att[CB_10_vyh->ItemIndex-12]= Q_vh[CB10_att_vyh->ItemIndex];/****?????****/
      kod_att[n_us_t]=Q_vh[CB10_att_vyh->ItemIndex];
    }

   if((res=Vkl_att_t(n_post,kod_att))==1)   /*0-- ��� ������, 1-- ���� ������ */
     {
      ShowMessage("������ ��� �������� ��������� 3 ������ � ��7 ERR=1!\n");
      goto end;
     }
 if(res==2) {ShowMessage("��� �������� ������� �� ����� 3!");}
           Sleep(1);


              /* ����� 1*/
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
 //============/* ��������� ������ ���������, ��������� ��������� ������� ��7 */========================================            /* ����� 1*/
  if(RG9->ItemIndex==0) //(CB_53_vyh->ItemIndex<=11)  /* 1--0: 2(���), 3(���)*/
   {
    n_post=2;    /*���*/
      /*������ �� 0 �� 12*/  /* nu-- ����� ���������*/
     nu=n_us_t;
    }
   if(RG9->ItemIndex==1) //(CB_53_vyh->ItemIndex>11)
   {
    n_post=3; /*���*/  /*������ �� 13 �� 25*/  /* nu-- ����� ���������*/
      nu=n_us_t;
    }
  // nu=0;  /* ???? nu-- nu=(����� ���������*/

   if((res=Vkl_us_vip_t(n_post,nu))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ (1) � ��7!\n");
     goto end;
    }
  if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");}
    Sleep(1);
               /* ����� 2*/
    /*  ������� ��������� ���������������� ������ ������� ������� �� */
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������� ���  1-�� � 2-�� ������ ��� */=========================
        //  n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* �� 0 �� 7*/
          n_vh1= n_l_t; n_vh2=n_l_t;  /* �� 0 �� 7*/
  if(CB_3_vh->ItemIndex==0)
    {
    in1_at=0x1F;in2_at=0x1F;
      if(RG9->ItemIndex==1)//(CB_10_vyh->ItemIndex>11) /* ���� ������ ���, �� ��������� ���*/
           n_post=3; /*���*/   /* ���� ������ ���, �� ��������� ���*/
           else  n_post=2;  nk_svch=1;
    }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1)
   {
    in1_at=0x1F;in2_at=0x1F;
           if(RG9->ItemIndex==0)//(CB_10_vyh->ItemIndex<=11) /* ���� ������ ���, �� ��������� ���*/
                 n_post=3;
           else  n_post=2; nk_svch=2;
    } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2)
    {
     in1_at=0x1F;in2_at=0x1F;
       if(RG9->ItemIndex==0)  //(CB_10_vyh->ItemIndex<=11) /* ���� ������ ���, �� ��������� ���*/
                 n_post=2;
           else  n_post=3;  nk_svch=1;
    }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3)
   {
     in1_at=0x1F;in2_at=0x1F;
        if(RG9->ItemIndex==0)//(CB_10_vyh->ItemIndex<=11) /* ���� ������ ���, �� ��������� ���*/
             n_post=2;
          else  n_post=3; nk_svch=2;
   } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7!\n");
     goto end;
    }

  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
   Sleep(1);
      /* ����� 2*/
 //============/* ��������� ������ ������ ������� �� ��� 1-��� � 2-��� ������ */========================================
//============/* ������� ���� ������� ��� ��� 1-��� � 2-��� ������ */==========================
   /* n_vh1 -- ����� ������ ������� ��� 1-��� ������ ��� 0--0xF (4 �������)*/
   /* n_vh2 -- ����� ������ ������� ��� 2-��� ������ ��� 0--0xF (4 �������)*/

   //    n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* �� 0 �� 7*/
           n_vh1= n_l_t; n_vh2=n_l_t;  /* �� 0 �� 7*/
  if(CB_3_vh->ItemIndex==0)
  {in1_at=Qv_vh[CB10_att_vh->ItemIndex];in2_at=0x1F;n_post=2;nk_svch=1;
  }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1)
  {in1_at=0x1F;in2_at=Qv_vh[CB10_att_vh->ItemIndex];n_post=2;nk_svch=2;
  } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2)
  {in1_at=Qv_vh[CB10_att_vh->ItemIndex];in2_at=0x1F;n_post=3;nk_svch=1;
   }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3)
  {in1_at=0x1F;in2_at=Qv_vh[CB10_att_vh->ItemIndex];n_post=3;nk_svch=2;
  } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

   if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7 ERR=1!\n");
     goto end1;
    }

    /* ����� ��������� ������ */
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
       Sleep(5);

      vyh=true;

  for(j=0; j<=63;j++)  /* ������ 2*/
// for(j=64; j<=223;j++)  /* ������ 53*/
  {
   Application->ProcessMessages();
   if(vyh==false) goto end;

    m_freqq=F_rtu[j];
    m_p_1=powerDBM-dPg[j];   /* � ������ ���������� ������ */
    stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // �������
     stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // ��������
  if (stat != VI_SUCCESS)
  {
     ShowMessage("������ ��� ��������� �������� �� ���������");
     goto end;
  }

    viPrintf(viP,"ABORT\n");
    viPrintf(viP,"INIT:CONT ON\n");
    viPrintf(viP,"FETC?\n");
    viScanf(viP,"%t",buf);

    m_Pow = atof(buf);
      ind=j;
   m_Pow=m_Pow-dPm[ind];   /*� ������ ���������� ������*/
    P_dB[j]=m_Pow;

        //  Pw=pow(10,Pdbm/10); //���       Pw=pow(10,-3)*pow(10,Pdbm/10);  //��

          m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

          P[j]=m_Pow;  /* �������� � �� */

        /* ������ ������� �������� */
                   /* ������ ���� �������� */
                         /* ����� 9*/
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//----------------������ ������ �������� ��� ������� ����������------------------------------
 if(RG9->ItemIndex==0)//(CB_10_vyh->ItemIndex<=12)  /* � ����������� �� ������ */
    {
     n_post=2; /**/
     }
  if(RG9->ItemIndex==1)//(CB_10_vyh->ItemIndex>12)
     {
     n_post=3; /**/
     }
    nf=0x9;
 n_jj=0;

m_jj:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- ��� ������, 1-- ���� ������ */
   {
     ShowMessage("������ ��� �������� ��������� ������� ������ (9) � ��7!\n");
    // 10.01.11 vyh=false; goto end;
   }

  Sleep(10);
//17.07 if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
//17.07   {
//17.07        // ��� �������� �������
//17.07//     ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07   }

  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
//17.07        // ��� �������� �������
//17.07 //     ShowMessage("��� �������� ������� ����� ������� ���������!");
//17.07      if(n_jj<=9)
//17.07      {
//17.07      n_jj=n_jj+1;
//17.07      goto m_jj;
//17.07      }
//17.07      else
//17.07      {
//17.07       ShowMessage("���� �� ����������!");
//17.07       vyh=false; goto end; //goto m2_end_5;
//17.07      }
   }
   else
   {
        // ������ �����

      LEN=packet_my_km.p_my_v.len;
      IPK=packet_my_km.p_my_v.byte1;
      SRC=packet_my_km.p_my_v.byte2&0x1F;
      DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* ����� ����� DST=0x6, ������ ����� DST=0x7*/
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
      ADC13=packet_my_km.p_my_v.byte18;

// 22.12.10
     if(RG9->ItemIndex==0)//(CB_53_vyh->ItemIndex<=11)  /* � ����������� �� ������ */
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
        if(n_us_t==12) ADC=ADC13&0xFF;
      }
    if(RG9->ItemIndex==1)//(CB_53_vyh->ItemIndex>11)  /* � ����������� �� ������ */
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
        if(n_us_t==12) ADC=ADC13&0xFF;
       }

        if(ERR==1)
         {
          //ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ ���� ��������! ERR=1");
          //goto m1;
           n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj;
            }
          else
            {
             ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ ���� ��������! ERR=1");
             goto m1_1;
            }
          }

         Kod_DM_izm[j]=ADC;
         Kod_M[j]=0.017*ADC;

       m1_1:;
     }
//    m2_end_5:;
 //   m2_end_3:;
 //====================================
         Sleep(10);

  }    /* end for �� ������� */

   for(k1=0,P_max=P_min=P[0]; k1<=63; k1+=1)  /* ���������� max �� ������ */
       {
        if(P[k1]>P_max) {P_max=P[k1];}//k_max=k1;}
        if(P[k1]<P_min) {P_min=P[k1];}//k_min=k1;}
       }

      Pmin_v=(float)P_min;
     // Pmax_v=(float)P_max;
     // dP=(float)fabs(P_max-P_min);

      StringGrid3->Cells[2*n_l_t][2*n_us_t+1]=CurrToStrF(Pmin_v,ffFixed,2);
      StringGrid3->Repaint();

   for(k1=0,Kod_max_km=Kod_min_km=Kod_DM_izm[0]; k1<=63; k1+=1)  /* ���������� max �� ������ */
       {
        if(Kod_DM_izm[k1]>Kod_max_km) {Kod_max_km=Kod_DM_izm[k1];}//k_max=k1;}
        if(Kod_DM_izm[k1]<Kod_min_km) {Kod_min_km=Kod_DM_izm[k1];}//k_min=k1;}
       }

       StringGrid3->Cells[2*n_l_t+1][2*n_us_t+1]=IntToStr(Kod_min_km);
       StringGrid3->Repaint();

   end1:;                         /* ����� 2 */
 //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������� ���  1-�� � 2-�� ������ ��� */=========================
     //     n_vh1= UD_53->Position-1; n_vh2=UD_53->Position-1;  /* �� 0 �� 7*/
         n_vh1= n_l_t; n_vh2=n_l_t;  /* �� 0 �� 7*/

  if(CB_3_vh->ItemIndex==0)
        {in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==1)
       {in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=2;
       } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==2)
        {in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(CB_3_vh->ItemIndex==3)
      {in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7 ERR=1!\n");
     //goto end;
    }
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
     Sleep(1);
                         /* ����� 1*/
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������ ���������, ���������� ��������� ������� ��7 */=========================
 if(RG9->ItemIndex==0)//(CB_10_vyh->ItemIndex<=11)  /* 1--0: 2(���), 3(���)*/
   {
    n_post=2;    /*���*/  /*������ �� 0 �� 12*/  /* nu-- ����� ���������*/
    }
   if(RG9->ItemIndex==1)//(CB_10_vyh->ItemIndex>11)
   {
    n_post=3; /*���*/ /*������ �� 13 �� 25*/  /* nu-- ����� ���������*/
    }
  // nu=0;  /* ???? nu-- nu=(����� ���������*/

   if((res=Vykl_us_vip_t(n_post))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ (1) � ��7 ERR=1!\n");
    // goto end;
    }
    if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");}
    Sleep(1);
     } /*  ���� �� ����� ������ ��������� */
    end_vhod:;
   viPrintf(viG,"OUTPut:STATe OFF\n"); //�����.  ������� �� ����� ���-��

  }  /*  ���� �� ������� (����������) */

   end:;
     viPrintf(viG,"OUTPut:STATe OFF\n"); //����. ������� �� ����� ���-��
     /*��� ������ �� ���� */
                             /* ����� 1*/
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������ ���������, ���������� ��������� ������� ��7 */=========================
 if(RG9->ItemIndex==0)//(CB_10_vyh->ItemIndex<=11)  /* 1--0: 2(���), 3(���)*/
   {
    n_post=2;    /*���*/  /*������ �� 0 �� 12*/  /* nu-- ����� ���������*/
    }
   if(RG9->ItemIndex==1)//(CB_10_vyh->ItemIndex>11)
   {
    n_post=3; /*���*/ /*������ �� 13 �� 25*/  /* nu-- ����� ���������*/
    }

   if((res=Vykl_us_vip_t(n_post))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ (1) � ��7 ERR=1!\n");
    // goto end;
    }
    if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");}
    Sleep(1);

    ShowMessage("��������� ���������\n");
}

//-------------------��������� ����������� ----------------------------------
int __fastcall TForm1::currentTemperature(int n_post)
{  //  n_post=0,1 - 53���    n_post=2,3 - 2���
	extern bool vyh;
	unsigned NVIP=0x0,TM1=0x0,TM2=0x0;
	int T;
	int nf=0x8;/* ����� ������� 8 ���� 9*/
	int j,k,n_jj;
	//char buf1[256]={0};
	unsigned n_vh1,n_vh2;
	unsigned in1_at,in2_at;
	int res=0,i;
	int nk,nu;  /* ����� ���*/
	unsigned LEN,IPK;
	unsigned DST,SRC,IPS,ERR;
	unsigned nk_svch;
	unsigned IPK_UP7;
   u32 buf_my[256/4]; // ����� ��� ��������� ������
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
	if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- ��� ������, 1-- ���� ������ */
	{
	  ShowMessage("������ ��� �������� ��������� ������� ������ � ��7!\n");
	}
	Sleep(10);
   if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
	{}
  else
	 {
		  // ������ �����
		  LEN=packet_my_t.p_my_v.len;
		  IPK=packet_my_t.p_my_v.byte1;
		  SRC=packet_my_t.p_my_v.byte2&0x1F;
		  DST=((packet_my_t.p_my_v.byte2>>5)&0x7)|((packet_my_t.p_my_v.byte3&0x3)<<3);  /* ����� ����� DST=0x6, ������ ����� DST=0x7*/
		  IPS=(packet_my_t.p_my_v.byte3>>2)&0x3F;
		  ERR=packet_my_t.p_my_v.byte4&0x1;
		  /*ADR_UP7=packet_my_t.p_my_v.byte5;*/
		  IPK_UP7=packet_my_t.p_my_v.byte5;
		  NVIP=packet_my_t.p_my_v.byte6&0x1;
		  TM1=packet_my_t.p_my_v.byte7&0xFF|((packet_my_t.p_my_v.byte8&0xF)<<8);
		  TM2=(packet_my_t.p_my_v.byte8>>4)&0xF|(packet_my_t.p_my_v.byte9&0xFF)<<4;
	 }
    if((TM1==0)||(TM2==0)){;}
	 else {
		T=235-(400*TM1)/TM2;
		return T;
			/* 22.12.10 */
		/*if(n_post==2)
		{
			edtTemperatureDisplay2pps->Text=buf1;
			edtTemperatureDisplay2pps->Repaint();
		}
		else
		{
			edtTemperatureDisplay2zps->Text=buf1;
			edtTemperatureDisplay2zps->Repaint();
		} */
	}
}
//-------------------��������� ����������� ----------------------------------

//-------------------��������� ����������� ----------------------------------
void __fastcall TForm1::Button49Click(TObject *Sender)
{
  extern bool vyh;
  unsigned NVIP=0x0,TM1=0x0,TM2=0x0;
  int T;
  int nf=0x8;/* ����� ������� 8 ���� 9*/

 int j,k,n_jj;
 char buf1[256]={0};
 int n_post;
  unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
	int nk,nu;  /* ����� ���*/
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned IPK_UP7;

  u32 buf_my[256/4]; // ����� ��� ��������� ������

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

			E_2_um->Text=" ";
			E_2_um->Repaint();

         E_t2_0->Text=" ";
         E_t2_0->Repaint();

         E_t2_1->Text=" ";
         E_t2_1->Repaint();

             /* ����� 8*/

              E2_izm_m->Text=" ";
              E2_izm_m->Repaint();

  for(i=0;i<=9;i++)  /* ������ ������� ����������� ��� ��������� */
    {
     if(RG9->ItemIndex==0)// if(CB_10_vyh->ItemIndex<=12)   /*  � ����������� �� ������*/
     {
     n_post=2; /*���*/
     }
      if(RG9->ItemIndex==1) // if(CB_10_vyh->ItemIndex>12)
     {
     n_post=3; /*���*/
     }
        nf=0x8;/* ������ ��������� */
//16.07  n_jj=0;

//16.07 m_jj_1:

 if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- ��� ������, 1-- ���� ������ */
	 {
	  ShowMessage("������ ��� �������� ��������� ������� ������ � ��7!\n");
	  goto end;
	 }

  // ShowMessage("�������� �������� ������� ������ � ��7 ������!\n");


	Sleep(10);
//16.07   if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
//16.07  {
//16.07        // ��� �������� �������//     ShowMessage("��� �������� ������� ����� ������� ���������!");
//16.07  }

	if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
	{
		  // ��� �������� �������
//16.07 //       ShowMessage("��� �������� ������� ����� ������� ���������!");
//16.07     if(n_jj<=9)
//16.07       {
//16.07       n_jj=n_jj+1;
//16.07       goto m_jj_1;
//16.07       }
//16.07       else
//16.07       {
//16.07        ShowMessage("���� �� ����������!");
//16.07        goto m2_end_2;
//16.07       }
	}
  else
	 {
		  // ������ �����
		  LEN=packet_my_t.p_my_v.len;
		  IPK=packet_my_t.p_my_v.byte1;
		  SRC=packet_my_t.p_my_v.byte2&0x1F;
		  DST=((packet_my_t.p_my_v.byte2>>5)&0x7)|((packet_my_t.p_my_v.byte3&0x3)<<3);  /* ����� ����� DST=0x6, ������ ����� DST=0x7*/
		  IPS=(packet_my_t.p_my_v.byte3>>2)&0x3F;
		  ERR=packet_my_t.p_my_v.byte4&0x1;
		  /*ADR_UP7=packet_my_t.p_my_v.byte5;*/
		  IPK_UP7=packet_my_t.p_my_v.byte5;
		  NVIP=packet_my_t.p_my_v.byte6&0x1;
		  TM1=packet_my_t.p_my_v.byte7&0xFF|((packet_my_t.p_my_v.byte8&0xF)<<8);
		  TM2=(packet_my_t.p_my_v.byte8>>4)&0xF|(packet_my_t.p_my_v.byte9&0xFF)<<4;

//10.01.11    if(ERR==1)
//      {
//         //ShowMessage("������ ��� �������� ������ 1 ��7! ERR=1");
//           n_jj=n_jj+1;
//         if(n_jj<=9)
//            {
//             goto m_jj_1;
//            }
//          else
//            {
//             ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ �����������! ERR=1");
//             goto m21;
//            }
//        }
		 // if(NVIP==0x1) ShowMessage("������������� ��������� �������!");
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
    /* ����� 8 ������ �����������*/
        nf=0x8;
    if(RG9->ItemIndex==0) //if(CB_10_vyh->ItemIndex<=12) /*  � ����������� �� ������*/
     {
     n_post=2; /*���*/
     }
     if(RG9->ItemIndex==1) //if(CB_10_vyh->ItemIndex>12)
     {
     n_post=3; /*���*/
     }
	  nf=0x8;/* ������ ��������� */
     n_jj=0;

m_jj_2:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- ��� ������, 1-- ���� ������ */
      {
       ShowMessage("������ ��� �������� ��������� ������� ������ � ��7!\n");
       vyh=false; goto end;
      }

  // ShowMessage("�������� �������� ������� ������ � ��7 ������!\n");

   Sleep(10);
//16.07  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
//16.07     {
//16.07        // ��� �������� �������
//16.07//       ShowMessage("��� �������� ������� ����� ������� ���������!");
//16.07     if(n_jj<=9)
//16.07      {
//16.07      n_jj=n_jj+1;
//16.07      goto m_jj_2;
//16.07      }
//16.07      else
//16.07      {
//16.07       ShowMessage("���� �� ����������!");
//16.07      vyh=false; goto end;// goto m2_end_3;
//16.07      }
//16.07    }

   if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
    {
        // ��� �������� �������
//23.12       ShowMessage("��� �������� ������� ����� ������� ���������!");
    }
   else
      {
        // ������ �����
          LEN=packet_my_t.p_my_v.len;
          IPK=packet_my_t.p_my_v.byte1;
          SRC=packet_my_t.p_my_v.byte2&0x1F;
          DST=((packet_my_t.p_my_v.byte2>>5)&0x7)|((packet_my_t.p_my_v.byte3&0x3)<<3);  /* ����� ����� DST=0x6, ������ ����� DST=0x7*/
          IPS=(packet_my_t.p_my_v.byte3>>2)&0x3F;
          ERR=packet_my_t.p_my_v.byte4&0x1;
        /*ADR_UP7=packet_my.p_my_v.byte5;*/
          IPK_UP7=packet_my_t.p_my_v.byte5;
          NVIP=packet_my_t.p_my_v.byte6&0x1;
          TM1=packet_my_t.p_my_v.byte7&0xFF|((packet_my_t.p_my_v.byte8&0xF)<<8);
          TM2=(packet_my_t.p_my_v.byte8>>4)&0xF|(packet_my_t.p_my_v.byte9&0xFF)<<4;
		  if(ERR==1)
         {
          //ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ �! ERR=1");
             n_jj=n_jj+1;
         if(n_jj<=9)
            {
				 goto m_jj_2;
            }
          else
            {
             ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ T! ERR=1");
				 vyh=false; goto end; // goto m22;
				}
		  }
		//22.12.10  if(NVIP==0x1) ShowMessage("������������� ��������� �������!");
//        T=235-(400*(int)TM1)/(int)TM2;
	 if((TM1==0)||(TM2==0)){;}
			 else
			  {
				 T=235-(400*TM1)/TM2;

				 memset(&buf1,0,20); /* ???????? ?????? */;
				 sprintf(buf1,"%d",T);
  /* 22.12.10 */
	if(n_post==2)
		 {
		  E_t2_0->Text=buf1;
		  E_t2_0->Repaint();
		 }
	else
	 {
	  E_t2_1->Text=buf1;
	  E_t2_1->Repaint();
	 }
  }
    } /*else from recive*/

    Sleep(1);
    }  /* while*/
 end:;
     ShowMessage("��������� ���������\n");
 //
}
//---------------------------------------------------------------------------
