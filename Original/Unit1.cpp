//---------------------------------------------------------------------------


#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
int  TForm1::Paket_bmk_prov(int nl)
{
 int n_post;
   unsigned n_vh1,n_vh2;
   unsigned in1_at,in2_at;
   int res=0;
   int i;
   int nk,nu,n_us; //* ����� ���
   unsigned kod_att[13];
   unsigned nk_svch;
        // ����� 3
    for(i=0;i<=12;i++)
      {
      // US[i]=0x0;
      // kod_att[i]=0xF;
        kod_att[i]=0x0;
      }
      //*  ������� ��������� ���������������� ������ ������� ������� ��
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������� ���  1-�� � 2-�� ������ ��� =========================
        n_vh1=nl; n_vh2=nl;  /* �� 0 �� 7*/  /* ���� *//* ����� ���� � ������ */
    if(ComboBox2->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
    /* ���� ������ ���, �� ��������� ���*/
       if(RadioButton2->Checked)
          n_post=3; /*���*/   /* ���� ������ ���, �� ��������� ���*/
           else  n_post=2;  nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/
   if(ComboBox2->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
          /* ���� ������ ���, �� ��������� ���*/
          if(RadioButton1->Checked)
                 n_post=3;
           else  n_post=2; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

   if(ComboBox2->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
         /* ���� ������ ���, �� ��������� ���*/
      if(RadioButton1->Checked)
                 n_post=2;
           else  n_post=3;  nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

   if(ComboBox2->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
          if(RadioButton1->Checked) /* ���� ������ ���, �� ��������� ���*/
              n_post=2;
           else  n_post=3; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7!\n");
     //goto end;
     return 1;
    }

  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!"); return 1;}
   Sleep(1);
                    /* ����� 2*/
 //============/* ��������� ������ ������ ������� �� ��� 1-��� � 2-��� ������ */========================================
//============/* ������� ���� ������� ��� ��� 1-��� � 2-��� ������ */==========================
          n_vh1= nl; n_vh2=nl;  /* �� 0 �� 7*/  /* ���� */
  if(ComboBox2->ItemIndex==0){in1_at=0x0;in2_at=0x1F;
                                 n_post=2; nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(ComboBox2->ItemIndex==1){in1_at=0x1F;in2_at=0x0;
                        n_post=2; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(ComboBox2->ItemIndex==2){in1_at=0x0;in2_at=0x1F;
                      n_post=3;   nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(ComboBox2->ItemIndex==3){in1_at=0x1F;in2_at=0x0;
             n_post=3; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

   if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ������ 2 � ��7 ERR=1!\n");
   //  goto end1;
      return 1;
    }

   /* ����� ��������� ������ */
  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");return 1;}
       Sleep(1);

  //============/* �������� ������� ���� �������� ��� */====

   /* ������ ��� ���� ��� ������ */

     if(RadioButton1->Checked)  n_post=2;    /*���*/
     if(RadioButton2->Checked)  n_post=3;    /*���*/

if((res=Vkl_att_t(n_post,kod_att))==1)   /*0-- ��� ������, 1-- ���� ������ */
     {
      ShowMessage("������ ��� �������� ������ 3 ERR=1");
     // goto end;
      return 1;
     }
 if(res==2) {ShowMessage("��� �������� ������� �� ����� 3!");return 1;}
                 /* ����� 1*/
//-----------------�������� �������� ������ � ��7 -------------------------------------------------------
 //============/* ��������� ������ ���������, ��������� ��������� ������� ��7 */========================================            /* ����� 1*/
 if(RadioButton1->Checked)  /* ��� */
   {
    n_post=2;    /*���*/
  //  nu=(CB_10_vyh->ItemIndex);    /*������ �� 0 �� 12*/  /* nu-- ����� ���������*/
  }
  if(RadioButton2->Checked)
   {
    n_post=3; /*���*/
 //   nu=13-(CB_10_vyh->ItemIndex);    /*������ �� 13 �� 25*/  /* nu-- ����� ���������*/
    }
     n_us=0xD;  /* ��� 13 ���������� */  /* ����� ���� � ������ */
     nu=n_us;

  if((res=Vkl_us_vip_t(n_post,nu))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ������ 1 � ��7 ERR=1!\n");
 //  goto end;
     return 1;
    }
   if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");return 1;}

     Sleep(1);
  return 0; /*��� ��������� */
}
//---------------------------------------------------------------------------
int  TForm1::Paket_bmk_prov_vykl(int nl)
{
   int n_post;
   unsigned n_vh1,n_vh2;
   unsigned in1_at,in2_at;
   int res=0;
   int i;
  int nk,nu,n_us;  /* ����� ���*/
  unsigned nk_svch;
       /* ����� 2 */
 //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������� ���  1-�� � 2-�� ������ ��� */=========================
          n_vh1= nl; n_vh2=nl;  /* �� 0 �� 7*/

  if(ComboBox2->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
                           n_post=2;  nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(ComboBox2->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           // if(CB_10_vyh->ItemIndex<=12)
                 n_post=2;    /*���*/
         //  else  n_post=3;
         nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if(ComboBox2->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
            n_post=3; nk_svch=1;
        }   /* ��� �������� ���. 1-���,2-��� ������ -- 0x1F(5 ��������)*/

  if(ComboBox2->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
            n_post=3; nk_svch=2;
      } /* ��� �������� ���. 1-���,2-��� ������-- 0x1F(5 ��������)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ 2 � ��7!\n");
     //goto end;
     return 1;
    }

  if(res==2){ShowMessage("��� �������� ������� �� ����� 2!");return 1;}
   Sleep(1);
                          /* ����� 1*/
  //-----------------�������� �������� ������ � ��7 -------------------------------------------------------
//============/* ���������� ������ ���������, ���������� ��������� ������� ��7 */=========================
 //if(ComboBox7->ItemIndex<=13)  /* 1--0: 2(���), 3(���)*/
  if(RadioButton1->Checked)  /* ��� */
   {
    n_post=2;    /*���*/
   // nu=(CB_10_vyh->ItemIndex);    /*������ �� 0 �� 12*/  /* nu-- ����� ���������*/
    }
//  if(ComboBox7->ItemIndex>13)
 if(RadioButton2->Checked)  /* ��� */
   {
    n_post=3; /*���*/
   // nu=13-(CB_10_vyh->ItemIndex);    /*������ �� 13 �� 25*/  /* nu-- ����� ���������*/
    }
  // nu=0;  /* ???? nu-- nu=(����� ���������*/

   if((res=Vykl_us_vip_t(n_post))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������ (1) � ��7!\n");
     //goto end;
     return 1;
    }
   if(res==2){ShowMessage("��� �������� ������� �� ����� 1!");return 1;}

     Sleep(1);
   return 0; /* ��� ������*/
}

//-------------------��������� ����������� � ��������---------------------------------
int  TForm1::temp_bmk_prov(void)
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


         Edit39->Text=" ";
         Edit39->Repaint();

         Edit40->Text=" ";
         Edit40->Repaint();

             /* ����� 8*/

  for(i=0;i<=9;i++)  /* ������ ������� ����������� ��� ��������� */
    {
     if(RadioButton1->Checked==true)// if(CB_10_vyh->ItemIndex<=12)   /*  � ����������� �� ������*/
     {
     n_post=2; /*���*/
     }
      if(RadioButton2->Checked==true) // if(CB_10_vyh->ItemIndex>12)
     {
     n_post=3; /*���*/
     }
        nf=0x8;/* ������ ��������� */
 n_jj=0;

m_jj_1:  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������� ������ � ��7!\n");
    // goto end;
     return 1;
    }

  // ShowMessage("�������� �������� ������� ������ � ��7 ������!\n");


   Sleep(10);
   if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
   {
        // ��� �������� �������//     ShowMessage("��� �������� ������� ����� ������� ���������!");
   }

   if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
   {
        // ��� �������� �������
//       ShowMessage("��� �������� ������� ����� ������� ���������!");
     if(n_jj<=9)
      {
      n_jj=n_jj+1;
      goto m_jj_1;
      }
      else
      {
       ShowMessage("���� �� ����������!");
       goto m2_end_2;
      }
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
//      vyh=true;

// while(vyh==true)
//  {
//   Application->ProcessMessages();
//   if(vyh==false) goto end;
    /* ����� 8 ������ �����������*/
        nf=0x8;
    if(RadioButton1->Checked==true) //if(CB_10_vyh->ItemIndex<=12) /*  � ����������� �� ������*/
     {
     n_post=2; /*���*/
     }
     if(RadioButton2->Checked==true) //if(CB_10_vyh->ItemIndex>12)
     {
     n_post=3; /*���*/
     }
     nf=0x8;/* ������ ��������� */
     n_jj=0;

m_jj_2:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- ��� ������, 1-- ���� ������ */
      {
       ShowMessage("������ ��� �������� ��������� ������� ������ � ��7!\n");
       //vyh=false; goto end;
        return 1;
      }

  // ShowMessage("�������� �������� ������� ������ � ��7 ������!\n");

   Sleep(10);
  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my))
     {
        // ��� �������� �������
//       ShowMessage("��� �������� ������� ����� ������� ���������!");
     if(n_jj<=9)
      {
      n_jj=n_jj+1;
      goto m_jj_2;
      }
      else
      {
       ShowMessage("���� �� ����������!");
      //vyh=false; goto end;// goto m2_end_3;
        return 1;

      }
    }

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
            // vyh=false; goto end; // goto m22;
             return 1;
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
        Edit39->Text=buf1;
        Edit39->Repaint();
       }
   else
    {
     Edit40->Text=buf1;
     Edit40->Repaint();
    }
  }
    } /*else from recive*/

    Sleep(1);
 //   }  /* while*/
 end:;
   /*  ShowMessage("��������� ���������\n");*/
 //
 return 0;
} 