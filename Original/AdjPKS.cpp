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


void __fastcall TForm1::AdjastPKS(TObject *Sender)
{
extern double F_rtu[224];
  double freq;
 // char buf1[256]={0};

Panel10->Visible=true;
Panel1->Visible=false;
Panel2->Visible=false;
PanelPotent->Visible=false;
Mode=0;/* �������� */
FileCalbGnPm();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button30Click(TObject *Sender)
{
 Panel10->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button33Click(TObject *Sender)
{
 extern bool vyh;
 vyh=false;
}
//----------------����������� �������� (���)-----------------------------------------------------------
void __fastcall TForm1::Button31Click(TObject *Sender)
{
 if(ChkDevs==true)       /** ������ ����������� ��� ������ ***/
   PKU_avt();
 else
 {
if(FindDevises()==true)
  {
   if(ChekDev()==true)
   PKU_avt();
  }    //FindDevises()
 }//else
 }
//-----    �������������� �����  --------------------------------
void TForm1::PKU_avt(void)
{
 extern bool vyh;
  ViStatus stat=0; // ���������� ���������� ���� ViStatus
  extern double F_rtu[224];

   double powerDBM=0.0;
   double m_freqq;
   double power;


 char buf[256]={0};
 // double P[160]={0.0};       /*���������� �������� � ��*/
  double P_dB[160]={0.0};    /*���������� �������� � ��*/


  double p_vt_izm;
  double P_max,P_min;
  float Pmin_v,Pmax_v,dP;
  int j,k,k1;

 int ind,ind_my; //������
 long longdown=0; /* �������� �������� ����������*/

 int m_p;
 float x_m_p;
 double m_p_1;  /* ��������, ���������� �� ����������*/

 int k1_max=0;

 int j_n,j_v;
 double m_Pow;
 char buf1[256]={0};
 int n_post;
 unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
  int nu;  /* ����� ��� ???*/

  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 �������� 00000, 00001,00010,00100,01000,10000*/

  unsigned nk_svch;
  int n_n;//,n_n_1,n_n_2;

  AnsiString str2[4]={"����","����� 1","����� 2","����� 32"};

  AnsiString str1[8]={"1��-2","2��-2","3��-2","4��-2","1��-53","2��-53","3��-53","4��-53"};

  TChartSeries *Series[4]={LineSeries9,PointSeries1,PointSeries2,LineSeries10};

        Series[0]->Clear();
        Series[1]->Clear();
        Series[2]->Clear();
        Series[3]->Clear();

      if(ComboBox12->ItemIndex>=4)          //if(RadioGroup12->ItemIndex==1)/* 53 */
        {
        Chart4->BottomAxis->SetMinMax(0,159);
        Chart4->LeftAxis->SetMinMax(-50,40);
        Chart4->Title->Text->Clear();
        //Chart4->Title->Text->Add("P=P(f)");
        }
      if(ComboBox12->ItemIndex<=3)    //if(RadioGroup12->ItemIndex==0) /* 2 */
        {
        Chart4->BottomAxis->SetMinMax(0,63);
        Chart4->LeftAxis->SetMinMax(-50,30);
        Chart4->Title->Text->Clear();
        //Chart4->Title->Text->Add("P=P(f)");
         }
         Chart4->Repaint();
          Edit8->Text=" ";
          Edit9->Text=" ";
          Edit10->Text=" ";

     ShowMessage("������ ������ � �� ���������� �� ���� "+str1[ComboBox12->ItemIndex]);
     ShowMessage("���������� ���������� �������� � ������ "+str2[ComboBox13->ItemIndex]);

             Chart4->Repaint();

       /* ������� � ������� ����� */
   if(shtat_rejim()!=0)
     {
      ShowMessage("������ ��� �������� � ������� �����"); goto end1;
     }
    Sleep(2000);
    /* ����� 2*/
 //============/* ��������� ������ ������ ������� �� ��� 1-��� � 2-��� ������ */========================================
//============/* ������� ���� ������� ��� ��� 1-��� � 2-��� ������ */==========================
   /* n_vh1 -- ����� ������ ������� ��� 1-��� ������ ��� 0--0xF (4 �������)*/
   /* n_vh2 -- ����� ������ ������� ��� 2-��� ������ ��� 0--0xF (4 �������)*/

 if(ComboBox12->ItemIndex>=4)  //if(RadioGroup12->ItemIndex==1)/* 53*/
   {
      n_vh1= 0x0; n_vh2=0x0;  /* �� 0 �� 7*/
   if(ComboBox12->ItemIndex==4){in1_at=Qv_vh[ComboBox14->ItemIndex];in2_at=0x1F;n_post=0;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(ComboBox12->ItemIndex==5){in1_at=0x1F;in2_at=Qv_vh[ComboBox14->ItemIndex];n_post=0;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(ComboBox12->ItemIndex==6){in1_at=Qv_vh[ComboBox14->ItemIndex];in2_at=0x1F;n_post=1;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(ComboBox12->ItemIndex==7){in1_at=0x1F;in2_at=Qv_vh[ComboBox14->ItemIndex];n_post=1;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

   if((res=Vkl_nk_att_t_pks(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7 ERR=1!\n");
     goto end1;
    }
    Sleep(1);

    /* ����� ��������� ������ */
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
       Sleep(5);
   }
 if(ComboBox12->ItemIndex<=3) // if(RadioGroup12->ItemIndex==0)/* 2*/
   {
       n_vh1= 0x0; n_vh2=0x0;  /* �� 0 �� 7*/
  if(ComboBox12->ItemIndex==0){in1_at=Qv_vh[ComboBox14->ItemIndex];in2_at=0x1F;n_post=2;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(ComboBox12->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[ComboBox14->ItemIndex];n_post=2;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(ComboBox12->ItemIndex==2){in1_at=Qv_vh[ComboBox14->ItemIndex];in2_at=0x1F;n_post=3;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(ComboBox12->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[ComboBox14->ItemIndex];n_post=3;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

   if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7 ERR=1!\n");
     goto end1;
    }

    /* ����� ��������� ������ */
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
       Sleep(5);
   }

   // Sleep(2000);

 //*************************************************************************
   m_freqq=F_rtu[64];

   powerDBM = strtod(Edit12->Text.c_str(),NULL);

   m_p_1=powerDBM-dPg[64];   /* � ������ ���������� ������ */

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
  /*�������� ��4-53, ��4-2, �������� ��3 � ����������� �� ����� */
    if(paket_FUP_my()!=0)
    {
     ShowMessage("������ ��� �������� FUP");
      goto end;
    }
      vyh=true;
 if(ComboBox12->ItemIndex>=4)  //if(RadioGroup12->ItemIndex==1)
                          {j_n=64;j_v=223;//n_n_1=8;n_n_2=27;j=j_n;} /* ������ 53*/
                              }
 if(ComboBox12->ItemIndex<=3)    //if(RadioGroup12->ItemIndex==0)
       {j_n=0;j_v=63;//n_n_1=0;n_n_2=7;j=j_n;} /* ������ 2*/
                              }
 for(j=j_n; j<=j_v;j++)  /* ���� �� ������� */
  {
  // Application->ProcessMessages();
 //  if(vyh==false) goto end1;

   /*�������� ��4-53, ��4-2, �������� ��3 � ����������� �� ����� */
 //--------------------------------------------------------
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
    if(ComboBox12->ItemIndex>=4) // if(RadioGroup12->ItemIndex==1)
        {ind_my=j-64;}
    if(ComboBox12->ItemIndex<=3) // if(RadioGroup12->ItemIndex==0)
       {ind_my=j;}
    m_Pow=m_Pow-dPm[ind];   /*� ������ ���������� ������*/
    P_dB[ind_my]=m_Pow-powerDBM;

        //  Pw=pow(10,Pdbm/10); //���       Pw=pow(10,-3)*pow(10,Pdbm/10);  //��

       //   m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

       //   P[ind_my]=m_Pow;  /* �������� � �� */


 //====================================
          Sleep(10);
        if(ComboBox12->ItemIndex>=4)  // if(RadioGroup12->ItemIndex==1)
              {x_m_p=j-64;ind_my=j-64;k1_max=159;}
       if(ComboBox12->ItemIndex<=3) // if(RadioGroup12->ItemIndex==0)
                  {x_m_p=j;ind_my=j;k1_max=63;}

        Series[3]->AddXY(x_m_p,P_dB[ind_my]);
        Series[3]->Repaint();

        Chart4->Repaint();

   }    /* end for �� ������� */
//  }
   for(k1=0,P_max=P_min=P_dB[0]; k1<=k1_max; k1+=1)  /* ���������� max �� ������ */
       {
        if(P_dB[k1]>P_max) {P_max=P_dB[k1];//k_max=k1;
                        }
        if(P_dB[k1]<P_min) {P_min=P_dB[k1];//k_min=k1;
                        }
       }

      Pmin_v=(float)P_min;
      Pmax_v=(float)P_max;
      dP=(float)fabs(P_max-P_min);

        memset(&buf1,0,20);
        sprintf(buf1,"%.2f",Pmin_v);
           Edit8->Text=buf1;
           Edit8->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%.2f",Pmax_v);

           Edit9->Text=buf1;
           Edit9->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%.2f",dP);

           Edit10->Text=buf1;
           Edit10->Repaint();

   end1:;
    Sleep(1);
   end:;
  viPrintf(viG,"OUTPut:STATe OFF\n"); //����. ������� �� ����� ���-��

  if(paket_FUP_my_vkl()!=0)       /* ��������� ��� ������ � ���*/
    {
     ShowMessage("������ ��� �������� FUP");
      goto end;
    }
    ShowMessage("��������� ���������\n");

}
//-----------------------����� ����-----------------------
int TForm1::ResetUPPU_pks(void)
{
 unsigned sbros_pk;

  U32 abuf[]={0x900011};
  U32 dbuf[]={0};
  U32 len_my=1; /* len_my=10;*/

          sbros_pk = 0x0;

  dbuf[0]= sbros_pk&0x1;

//if(Application->MessageBox("������� 1���-52 ��������?", "��������!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
//{
   // UpsWriteMemBuf32(U32 *addr_buf,U32 *data_buf,U32 len)
    if(FmLib-> UpsWriteMemBuf32(abuf,dbuf,len_my)==true){;}
    //  if(WriteMemBuf32(abuf,dbuf,SIZE(abuf))==true){;}
      else
         {
          ShowMessage("������ ��� ������!");
          return(0);//goto end;
          }

        Sleep(1000);

       sbros_pk = 0x1;

  dbuf[0]= sbros_pk&0x1;
   // UpsWriteMemBuf32(U32 *addr_buf,U32 *data_buf,U32 len)
    if(FmLib-> UpsWriteMemBuf32(abuf,dbuf,len_my)==true){;}
    //  if(WriteMemBuf32(abuf,dbuf,SIZE(abuf))==true){;}
      else
        {
          ShowMessage("������ ��� ������!");
          return(0); //goto end;
        }

        return(1);//   ShowMessage("����� ������!");
// end:;
}


//---------------����������� �������� (����) -----------------------------------------------------------
void __fastcall TForm1::Button32Click(TObject *Sender)
{
 if(ChkDevs==true)       /** ������ ����������� ��� ������ ***/
 PKU_ru();
 else
 {
 if(FindDevises()==true)
 {
  if(ChekDev()==true)
  PKU_ru();
 }    //FindDevises()
 }//else
}
//---------------------------------------------------------------------------
int TForm1::shtat_rejim(void)
{
 //int nk=1;
 Byte LEN =4;
 Byte IPK=0xff;   //������� �����
// Byte IPS=0x1a;
 unsigned DST=0x6,SRC=0x0;
 unsigned ips_out=0x1A;

 int jk,ret;
 union{
      struct{
             U32 len     : 8,
                 byte1   : 8,
                 byte2   : 8,
                 byte3   : 8;
            } p;
      U32 buf[256/4];
     }  packet;

  memset(&packet, 0, sizeof(packet));
     packet.p.len=LEN;
     packet.p.byte1=IPK;
   //  packet.p.byte2=0x0;
     packet.p.byte2 = (SRC&0x1F)|((DST<<5))&0x7;
     packet.p.byte3 = ips_out << 2; //IPS
/*********************************************/
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
//=========================================================================
int TForm1::otvet_paket_FKU(void) /* 0-- ��� ������; 1-- ���� ������ (ERR=1); 2-- ��� �������� �������*/
{

  int jk;
  int nk;
  unsigned LEN,IPK;
  unsigned SCH=0x0,PSK0=0x0,PSK1=0x0,PVCH=0x0,PKS=0x0,RDY=0x0,IFU=0x0,KRDY=0x0,NAP=0x0;

  u32 buf_my[256/4]; // ����� ��� ��������� ������

    union{
       struct{
                  U32   len     : 8, /*LEN*/
                        byte1   : 8, /*IPK*/
                        byte2   : 8, /* NAP? RDY,...,SCH */
                        byte3   : 8, /*IFU */
                        byte4   : 8; /* KRDY */
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
//          LEN= packet_my_km.p_my_v.len;
 //         IPK=packet_my_km.p_my_v.byte1;
 //         SCH= (packet_my_km.p_my_v.byte2)&0x3;
//          PSK0=(packet_my_km.p_my_v.byte2>>2)&0x1;
//          PSK1=(packet_my_km.p_my_v.byte2>>3)&0x1;
 //         PVCH=(packet_my_km.p_my_v.byte2>>4)&0x1;
//          PKS=(packet_my_km.p_my_v.byte2>>5)&0x1;
//          RDY=(packet_my_km.p_my_v.byte2>>6)&0x1;
//          NAP=(packet_my_km.p_my_v.byte2>>7)&0x1;
//          IFU=packet_my_km.p_my_v.byte3;
          KRDY=packet_my_km.p_my_v.byte4;

        if(KRDY!=0) {
                    ShowMessage("��� ���������� KRDY �� ����� 0 � FKU");
                    return 1;
                    }

  //  m2_end:;
   return 0;
}
//---------------------------------------------------------------------------
int TForm1::paket_FUP_my(void)
{
  //int nk=1;
 // unsigned LEN=6,IPK=0x13;
  unsigned NKSK0=0x0,NKSK1=0x0,NAP=0x0,SKS=0x0,DKS=0x0,RRPT=0x0,KF=0x0,
  AT11=0x0,AT12=0x0,NL0=0x0,NL1=0x0;

 int jk,ret;

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

   NKSK0=0x1;
   NKSK1=0x1;
   if(ComboBox12->ItemIndex>=4) // if(RadioGroup12->ItemIndex==1)/*53*/
   {
   SKS=(ComboBox12->ItemIndex+4)&0x7;
   }
  if(ComboBox12->ItemIndex<=3)  //   if(RadioGroup12->ItemIndex==0) /* 2*/
   {
   SKS=(ComboBox12->ItemIndex-4)&0x7;
   }
   DKS=(ComboBox13->ItemIndex)&0x7;
   RRPT=0x2;
   AT11=0x1;
   AT12=0x1;
   NL0=0x0;
   NL1=0x0;
   NAP=0x0;
   KF=0x0;

     memset(&packet_my, 0, sizeof(packet_my));
      packet_my.p_my_v.len = 6; //LEN
      packet_my.p_my_v.byte1 = 0x13; //IPK (��. ������� ���������� ������)
      packet_my.p_my_v.byte2 = (NKSK0&0x7)|((NKSK1&0x7)<<3)|((NAP&0x1)<<7);
      packet_my.p_my_v.byte3 = (DKS&0x3)|((SKS&0x7)<<2)|((RRPT&0x3)<<5);
      packet_my.p_my_v.byte4 = KF&0xFF; //
      packet_my.p_my_v.byte5 = AT11|(AT12<<1)|((NL0&0x7)<<2)|((NL1&0x7)<<5);

/*********************************************/
   jk=0;
m1:  if(UPS_SEND_KIO_PACKET (1,packet_my.buf_my) == true){;}
         else{
             //ShowMessage("������ �������� ������ 3!");
            //return(1);   ������ �� ������
            }
   /* ����� ��������� ������ */
    ret=otvet_paket_FKU();

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
//---------------��������� ��� ������ � ��� ------------------------------------------------------------
int TForm1::paket_FUP_my_vkl(void)
{
 //int nk=1;
  //unsigned LEN=6,IPK=0x13;
  unsigned NKSK0=0x0,NKSK1=0x0,NAP=0x0,SKS=0x0,DKS=0x0,RRPT=0x0,KF=0x0,
  AT11=0x0,AT12=0x0,NL0=0x0,NL1=0x0;
   int jk,ret;

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

   NKSK0=0x1;
   NKSK1=0x1;
  if(ComboBox12->ItemIndex>=4) //  if(RadioGroup12->ItemIndex==1)/*53*/
   {
   SKS=(ComboBox12->ItemIndex+4)&0x7;
   }
  if(ComboBox12->ItemIndex<=3) //   if(RadioGroup12->ItemIndex==0) /* 2*/
   {
   SKS=(ComboBox12->ItemIndex-4)&0x7;
   }
  // DKS=(ComboBox13->ItemIndex)&0x7;
   DKS=0x0;/* ��������� ��� ������ 0*/
   RRPT=0x2;
   AT11=0x1;
   AT12=0x1;
   NL0=0x0;
   NL1=0x0;
   NAP=0x0;
   KF=0x0;

     memset(&packet_my, 0, sizeof(packet_my));
      packet_my.p_my_v.len = 6; //LEN
      packet_my.p_my_v.byte1 = 0x13; //IPK (��. ������� ���������� ������)
      packet_my.p_my_v.byte2 = (NKSK0&0x7)|((NKSK1&0x7)<<3)|((NAP&0x1)<<7);
      packet_my.p_my_v.byte3 = (DKS&0x3)|((SKS&0x7)<<2)|((RRPT&0x3)<<5);
      packet_my.p_my_v.byte4 = KF&0xFF; //
      packet_my.p_my_v.byte5 = AT11|(AT12<<1)|((NL0&0x7)<<2)|((NL1&0x7)<<5);

/*********************************************/
   jk=0;
m1:  if(UPS_SEND_KIO_PACKET (1,packet_my.buf_my) == true){;}
         else{
             //ShowMessage("������ �������� ������ 3!");
            //return(1);   ������ �� ������
            }
   /* ����� ��������� ������ */
    ret=otvet_paket_FKU();

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

//-----  ������ �����  --------------------------------
void TForm1::PKU_ru(void)
{
 extern bool vyh;
  ViStatus stat=0; // ���������� ���������� ���� ViStatus
  extern double F_rtu[224];

   double powerDBM=0.0;
   double m_freqq;
   double power;


 char buf[256]={0};

  double p_vt_izm;
  float P_izm;

  int j,k,k1;

 //int ind;//������
 long longdown=0; /* �������� �������� ����������*/

 int m_p;
 float x_m_p;
 double m_p_1;  /* ��������, ���������� �� ����������*/

 unsigned nk_svch;

 int j_n,j_v;
 double m_Pow;
 char buf1[256]={0};
  int res=0,i;
  int nu;  /* ����� ��� ???*/
  int n_post;
 unsigned n_vh1,n_vh2;
 unsigned in1_at,in2_at;

  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 �������� 00000, 00001,00010,00100,01000,10000*/

  AnsiString str2[4]={"����","����� 1","����� 2","����� 32"};

  AnsiString str1[8]={"1��-2","2��-2","3��-2","4��-2","1��-53","2��-53","3��-53","4��-53"};

  TChartSeries *Series[4]={LineSeries9,PointSeries1,PointSeries2,LineSeries10};

        Series[0]->Clear();
        Series[1]->Clear();
        Series[2]->Clear();
        Series[3]->Clear();
 if(ComboBox12->ItemIndex>=4) //      if(RadioGroup12->ItemIndex==1)
        {
        Chart4->BottomAxis->SetMinMax(0,159);
        Chart4->Title->Text->Clear();
        Chart4->LeftAxis->SetMinMax(-50,40);
        TrackBar5->Max=159;
        TrackBar5->Position=80;
        m_freqq=F_rtu[TrackBar5->Position+64];
       }

  if(ComboBox12->ItemIndex<=3) //      if(RadioGroup12->ItemIndex==0)
        {
        Chart4->BottomAxis->SetMinMax(0,63);
        Chart4->Title->Text->Clear();
        Chart4->LeftAxis->SetMinMax(-50,30);
        TrackBar5->Max=63;
        TrackBar5->Position=30;
        m_freqq=F_rtu[TrackBar5->Position];
        }

          Chart4->Repaint();
          Edit8->Text=" ";
          Edit9->Text=" ";
          Edit10->Text=" ";
          Edit11->Text=" ";

   ShowMessage("������ ������ � �� ���������� �� ���� "+str1[ComboBox12->ItemIndex]);
   ShowMessage("���������� ���������� �������� � ������ "+str2[ComboBox13->ItemIndex]);
          Chart4->Repaint();

  //   if(ResetUPPU_pks()){;} /*����� ���� */
  //  else{
  //       ShowMessage("������ ��� ������ ����!"); goto end;
  //       }
   //    Sleep(5000);
       /* ������� � ������� ����� */
   if(shtat_rejim()!=0)
     {
      ShowMessage("������ ��� �������� � ������� �����"); goto end1;
     }
    Sleep(2000);
    /* ����� 2*/
 //============/* ��������� ������ ������ ������� �� ��� 1-��� � 2-��� ������ */========================================
//============/* ������� ���� ������� ��� ��� 1-��� � 2-��� ������ */==========================
   /* n_vh1 -- ����� ������ ������� ��� 1-��� ������ ��� 0--0xF (4 �������)*/
   /* n_vh2 -- ����� ������ ������� ��� 2-��� ������ ��� 0--0xF (4 �������)*/
 if(ComboBox12->ItemIndex>=4) // if(RadioGroup12->ItemIndex==1)/* 53*/
   {
      n_vh1= 0x0; n_vh2=0x0;  /* �� 0 �� 7*/
  if(ComboBox12->ItemIndex==4){in1_at=Qv_vh[ComboBox14->ItemIndex];in2_at=0x1F;n_post=0;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(ComboBox12->ItemIndex==5){in1_at=0x1F;in2_at=Qv_vh[ComboBox14->ItemIndex];n_post=0;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(ComboBox12->ItemIndex==6){in1_at=Qv_vh[ComboBox14->ItemIndex];in2_at=0x1F;n_post=1;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(ComboBox12->ItemIndex==7){in1_at=0x1F;in2_at=Qv_vh[ComboBox14->ItemIndex];n_post=1;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

   if((res=Vkl_nk_att_t_pks(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7 ERR=1!\n");
     goto end1;
     }
      Sleep(1);

    /* ����� ��������� ������ */
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
       Sleep(5);
   }

 if(ComboBox12->ItemIndex<=3)  // if(RadioGroup12->ItemIndex==0)/* 2*/
   {
       n_vh1= 0x0; n_vh2=0x0;  /* �� 0 �� 7*/
  if(ComboBox12->ItemIndex==0){in1_at=Qv_vh[ComboBox14->ItemIndex];in2_at=0x1F;n_post=2;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(ComboBox12->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[ComboBox14->ItemIndex];n_post=2;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(ComboBox12->ItemIndex==2){in1_at=Qv_vh[ComboBox14->ItemIndex];in2_at=0x1F;n_post=3;nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(ComboBox12->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[ComboBox14->ItemIndex];n_post=3;nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

   if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7 ERR=1!\n");
     goto end1;
    }

    /* ����� ��������� ������ */
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");}
       Sleep(5);
   }

 //*************************************************************************

   powerDBM = strtod(Edit12->Text.c_str(),NULL);
 if(ComboBox12->ItemIndex>=4)  //   if(RadioGroup12->ItemIndex==1)
    {
    m_p_1=powerDBM-dPg[TrackBar5->Position+64];   /* ???????? � ������ ���������� ������ */
    }
   if(ComboBox12->ItemIndex<=3) // if(RadioGroup12->ItemIndex==0)
   {
    m_p_1=powerDBM-dPg[TrackBar5->Position];   /* ???????? � ������ ���������� ������ */
   }

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
  /*�������� ��4-53, ��4-2, �������� ��3 � ����������� �� ����� */
    if(paket_FUP_my()!=0)
    {
     ShowMessage("������ ��� �������� FUP");
      goto end;
    }
      vyh=true;
                 /*  ���������� */
  while(vyh==true)
    {
     Application->ProcessMessages();
  if(ComboBox12->ItemIndex>=4) //  if(RadioGroup12->ItemIndex==1)
    {
    m_freqq=F_rtu[TrackBar5->Position+64];
    m_p_1=powerDBM-dPg[TrackBar5->Position+64];   /* � ������ ���������� ������ */
    }
    if(ComboBox12->ItemIndex<=3) // if(RadioGroup12->ItemIndex==0)
     {
      m_freqq=F_rtu[TrackBar5->Position];
      m_p_1=powerDBM-dPg[TrackBar5->Position];   /* � ������ ���������� ������ */
     }

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

    if(ComboBox12->ItemIndex>=4) //if(RadioGroup12->ItemIndex==1)
    {
    // ind=TrackBar5->Position+64;
     m_Pow=m_Pow-dPm[TrackBar5->Position+64];   /*� ������ ���������� ������*/
    }
    if(ComboBox12->ItemIndex<=3) //   if(RadioGroup12->ItemIndex==0)
    {
    // ind=TrackBar5->Position;
     m_Pow=m_Pow-dPm[TrackBar5->Position];   /*� ������ ���������� ������*/
    }

    P_izm=m_Pow-powerDBM;

        //  Pw=pow(10,Pdbm/10); //���       Pw=pow(10,-3)*pow(10,Pdbm/10);  //��

        //   m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

        //   P[ind_my]=m_Pow;  /* �������� � �� */
  //====================================
          Sleep(10);
        memset(&buf1,0,20);  /* ����� �� ����� */
        sprintf(buf1,"%.2f",P_izm);
           Edit11->Text=buf1;
           Edit11->Repaint();

           Sleep(10);

        x_m_p=TrackBar5->Position;
        Series[1]->AddXY(x_m_p,P_izm);
        Series[1]->Repaint();

        Chart4->Repaint();
          }    /* end for �� ������� */

   end1:;
    Sleep(1);
   end:;
  viPrintf(viG,"OUTPut:STATe OFF\n"); //����. ������� �� ����� ���-��

  if(paket_FUP_my_vkl()!=0)       /* ��������� ��� ������ � ���*/
    {
     ShowMessage("������ ��� �������� FUP");
      goto end;
    }

//    ShowMessage("��������� ���������\n");
}
//============/* ���������� ������ ������ ������� �� ��� 1-��� � 2-��� ������ */========================================
//============/* ������� ���� ������� ��� ��� 1-��� � 2-��� ������ */==========================
int TForm1::Vkl_nk_att_t_pks(int n_post,unsigned n_vh1,unsigned n_vh2,unsigned in1_at,unsigned in2_at,unsigned nk_svch)   /*0-- ��� ������, 1-- ���� ������ */
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

      //   ON_1=0x0; ON_2=0x0;

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
