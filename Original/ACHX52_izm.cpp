extern bool vyh;
  ViStatus stat=0; // iauyaeaiea ia?aiaiiie oeia ViStatus
  extern double F_rtu[224];

   double powerDBM=0.0;
   double m_freqq;
   double power;

   double K_nu=0.0;
 char buf[256]={0};

  double P[64]={0.0};       /*ecia?aiiia cia?aiea a Ao*/
  double P_dB[64]={0.0};    /*ecia?aiiia cia?aiea a aA*/

 // double P_1=0;
  //double dP;
  double p_vt_izm;
  double P_max,P_min;
  float Pmin_v,Pmax_v,dP;
  int j,k,k1;
 //int num=0;
 //char rdbuffer[256]={0};

 int ind; //eiaaen ainooia e ianneaai eaeea?iaee
 long longdown=0; /* i?eaaiea iia?aoee caaa?oaiey*/

 int m_p;
 float x_m_p;
 double m_p_1;  /* iiuiinou, caaaaaaiay ia aaia?aoi?a*/

 int k_att=0;
 int k_max=0,k_min=0;

 double m_Pow;
 char buf1[256]={0};
  int n_post;
  unsigned n_vh1,n_vh2;
  unsigned in1_at,in2_at;
  int res=0,i;
   int nk,nu;  /* iiia? EEI*/
                                  /* aoiaiie aoo */
  unsigned Qv_vh[32]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF,
                      0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F}; /* 5 ?ac?yaia 00000, 00001,00010,00100,01000,10000*/
 float Qvh_osl_my[32]={0.0,-0.75,-1.5,-2.25,-3.0,-3.75,-4.5,-5.25,-6.0,
                     -6.75,-7.5,-8.25,-9.0,-9.75,-10.5,-11.25,-12.0,
                     -12.75,-13.5,-14.25,-15.0,-15.75,-16.5,-17.25,-18.0,
                     -18.75,-19.5,-20.25,-21.0,-21.75,-22.5,-23.25};

                  /* 5 ?ac?yaia 00000, 00001,00010,00100,01000,10000*/
//float Qvh_osl[32]={-23.25,-22.5,-21.75,-21.0,-20.25,-19.5,-18.75,-18.0,
//                     -17.25,-16.5,-15.75,-15.0,-14.25,-13.5,-12.75,-12.0,
//                     -11.25,-10.5,-9.75,-9.0,-8.25,-7.5,-6.75,-6.0,-5.25,
//                     -4.5,-3.75,-3.0,-2.25,-1.5,-0.75,0.0};
//                     /* 5 ?ac?yaia 00000, 00001,00010,00100,01000,10000*/

  unsigned Q_vh[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF}; /* auoiaiie aoo */
  unsigned LEN,IPK;
  unsigned DST,SRC,IPS,ERR;
  unsigned nk_svch;
  unsigned kod_att[12];

   AnsiString str2[26]={"Auoia IIN-1","Auoia IIN-2","Auoia IIN-3","Auoia IIN-4",
                       "Auoia IIN-5","Auoia IIN-6","Auoia IIN-7","Auoia IIN-8",
                       "Auoia IIN-9","Auoia IIN-10","Auoia IIN-11","Auoia IIN-12","Auoia IIN-13",
                       "Auoia CIN-1","Auoia CIN-2","Auoia CIN-3","Auoia CIN-4",
                       "Auoia CIN-5","Auoia CIN-6","Auoia CIN-7","Auoia CIN-8",
                       "Auoia CIN-9","Auoia CIN-10","Auoia CIN-11","Auoia CIN-12","Auoia CIN-13"};
  AnsiString str1[4]={"1A?-53","2A?-53","3A?-53","4A?-53"};

  TChartSeries *Series[4]={LineSeries1,LineSeries2,LineSeries7,LineSeries8};

  u32 buf_my[256/4]; // Aooa? aey i?eiyoiai iaeaoa

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
 StNIn=IntToStr(CB_3_vh->ItemIndex+1); /* aua?ai aoia*/

if(CB_10_vyh->ItemIndex<=12) /* anee aua?ai IIN*/
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
  ShowMessage("Iaaicii?ii ioe?uou oaee");
   goto m1;
  }
 /* nia?aea ?oaiea ec oaeea */

 for(n_us=0;n_us<=12;n_us++) /* ii 13 oneeeoaeyi */
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

        ShowMessage("Iiaaou neaiae n A? aaia?aoi?a ia aoia "+str1[CB_3_vh->ItemIndex]);

        ShowMessage("Iiaee??eou ecia?eoaeu iiuiinoe ?a?ac aooai?aoi? 30aA e auoiao "+str2[CB_10_vyh->ItemIndex]);

         Chart_kvk->Repaint();

        /* iaeao 3*/
    for(i=0;i<=12;i++)
      {
      // US[i]=0x0;
       kod_att[i]=0xF;
      }
  //============/* oi?ioey? caaaiea eiaa auoiaiuo aoo */====
   if(CB_10_vyh->ItemIndex<=12)
   {
    n_post=2;    /*IIN*/
    kod_att[CB_10_vyh->ItemIndex]= Q_vh[CB10_att_vyh->ItemIndex];
   }
  if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*CIN*/
    kod_att[CB_10_vyh->ItemIndex-13]= Q_vh[CB10_att_vyh->ItemIndex];/****?????****/
    }

   if((res=Vkl_att_t(n_post,kod_att))==1)   /*0-- iao ioeaie, 1-- anou ioeaee */
     {
      ShowMessage("Ioeaea i?e ia?aaa?a oi?ioey?a 3 aaiiuo a OI7 ERR=1!\n");
      //goto end;
     }
 if(res==2) {ShowMessage("Iao ioaaoiuo iaeaoia ia iaeao 3!");}
           Sleep(1);


              /* iaeao 1*/
//-----------------oi?ioey? ia?aaa?e aaiiuo a OI7 -------------------------------------------------------
 //============/* aee??aiea eaiaea oneeeoaey, aee??aiea enoi?ieea ieoaiey OI7 */========================================            /* iaeao 1*/
   if(CB_10_vyh->ItemIndex<=12)  /* 1--0: 2(IIN), 3(CIN)*/
   {
    n_post=2;    /*IIN*/
    nu=(CB_10_vyh->ItemIndex);    /*eiaaen io 0 ai 12*/  /* nu-- iiia? oneeeoaey*/
    }
   if(CB_10_vyh->ItemIndex>12)
   {
    n_post=3; /*CIN*/
    nu=(CB_10_vyh->ItemIndex)-13;    /*eiaaen io 13 ai 25*/  /* nu-- iiia? oneeeoaey*/
    }
  // nu=0;  /* ???? nu-- nu=(iiia? oneeeoaey*/

   if((res=Vkl_us_vip_t(n_post,nu))==1)   /*0-- iao ioeaie, 1-- anou ioeaee */
    {
     ShowMessage("Ioeaea i?e ia?aaa?a oi?ioey?a aaiiuo (1) a OI7!\n");
    // goto end;
    }
  if(res==2){ShowMessage("Iao ioaaoiuo iaeaoia ia iaeao 1!");}
    Sleep(1);
 //*************************************************************************
   m_freqq=F_rtu[0];

   powerDBM = strtod(E2_p->Text.c_str(),NULL);

   K_nu = strtod(E_ks_1->Text.c_str(),NULL);
   if((K_nu>3.0)||(K_nu<0.0))
   {
    ShowMessage("Iaaa?iia cia?aiea eiinoaiou ianuuaiey");
    goto end;
   }

    K_nu=(3.0-K_nu)/4.0;

   m_p_1=powerDBM-dPg[0];   /* n o?aoii eaeea?iaee eaaaey */

 /*15.12.10*/ //    power = -70.0;  //ioeaaea

 // Onoaiiaea ia aaia?aoi? ?anoiou e iiuiinoe
 stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // ?anoioa
 stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // iiuiinou
  if (stat != VI_SUCCESS)
  {
     ShowMessage("Ioeaea i?e onoaiiaea cia?aiee ia aaia?aoi?");
     goto end;
  }
 // viPrintf(vigen,"PULM:STAT OFF\n");   // AEE??eou eii iiaoeyoe?
   viPrintf(viG,"OUTPut:STATe ON\n"); //iiaee.  neaiaea ia auoia aai-?a

    longdown=0;

    viPrintf(viG,"*OPC?\n");

        while(!longdown)
    viScanf(viG,"%d", &longdown);

    viPrintf(viP,"ABORT\n");
   viPrintf(viP,"INIT:CONT ON\n");
   viPrintf(viP,"FETC?\n");
   viScanf(viP,"%t",buf);

    Sleep(1);
            /* iaeao 2*/
    /*  nia?aea auee??aai iaeniieucuaaaiua iiia?a auoiaia iao?eou II */
  //-----------------oi?ioey? ia?aaa?e aaiiuo a OI7 -------------------------------------------------------
//============/* auee??aiea iao?eou aey  1-ai e 2-ai eaiaea NA? */=========================
          n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* io 0 ai 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;
      if(CB_10_vyh->ItemIndex>11) /* anee aua?ai IIN, oi auee??aai CIN*/
           n_post=3; /*CIN*/   /* anee aua?ai IIN, oi auee??aai CIN*/
           else  n_post=2;  nk_svch=1;
        }   /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea -- 0x1F(5 ?ac?yaia)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;
           if(CB_10_vyh->ItemIndex<=11) /* anee aua?ai IIN, oi auee??aai CIN*/
                 n_post=3;
           else  n_post=2; nk_svch=2;
      } /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea-- 0x1F(5 ?ac?yaia)*/

  if(CB_3_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;
         if(CB_10_vyh->ItemIndex<=11) /* anee aua?ai CIN, oi auee??aai IIN*/
                 n_post=2;
           else  n_post=3;  nk_svch=1;
        }   /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea -- 0x1F(5 ?ac?yaia)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;
          if(CB_10_vyh->ItemIndex<=11) /* anee aua?ai CIN, oi auee??aai IIN*/
              n_post=2;
           else  n_post=3; nk_svch=2;
      } /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea-- 0x1F(5 ?ac?yaia)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- iao ioeaie, 1-- anou ioeaee */
    {
     ShowMessage("Ioeaea i?e ia?aaa?a oi?ioey?a aaiiuo 2 a OI7!\n");
     //goto end;
    }

  if(res==2){ShowMessage("Iao ioaaoiuo iaeaoia ia iaeao 2!");}
   Sleep(1);

    vyh=true;

 for(j=0; j<=63;j++)  /* eeoa?a 2*/
  {
  // Application->ProcessMessages();
 //  if(vyh==false) goto end1;

   /* auai? io?iiai cia?aiey eiaa aoiaiiai aoo. ec oaeea */
   for(km=0;km<=31;km++)
   {
    Qsl_my=osl[N_us][UD_2->Position-1][j];
    if(Qsl_my==Qvh_osl_my[km]) kod_att_my=km;
   }

      /* iaeao 2*/
 //============/* aee??aiea iiia?a auoiaa iao?eou II aey 1-iai e 2-iai eaiaea */========================================
//============/* caaaiea eiaa aoiaiuo aoo aey 1-iai e 2-iai eaiaea */==========================
   /* n_vh1 -- iiia? auoiaa iao?eou aey 1-iai eaiaea NA? 0--0xF (4 ?ac?yaa)*/
   /* n_vh2 -- iiia? auoiaa iao?eou aey 2-iai eaiaea NA? 0--0xF (4 ?ac?yaa)*/

       n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* io 0 ai 7*/
//  if(CB_3_vh->ItemIndex==0){in1_at=Qv_vh[CB10_att_vh->ItemIndex];in2_at=0x1F;n_post=0;nk_svch=1;
//        }   /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea -- 0x1F(5 ?ac?yaia)*/

//  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[CB10_att_vh->ItemIndex];n_post=0;nk_svch=2;
//      } /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea-- 0x1F(5 ?ac?yaia)*/

//  if(CB_3_vh->ItemIndex==2){in1_at=Qv_vh[CB10_att_vh->ItemIndex];in2_at=0x1F;n_post=1;nk_svch=1;
//        }   /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea -- 0x1F(5 ?ac?yaia)*/

//  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[CB10_att_vh->ItemIndex];n_post=1;nk_svch=2;
//      } /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea-- 0x1F(5 ?ac?yaia)*/

  if(CB_3_vh->ItemIndex==0){in1_at=Qv_vh[kod_att_my];in2_at=0x1F;n_post=2;nk_svch=1;
        }   /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea -- 0x1F(5 ?ac?yaia)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=Qv_vh[kod_att_my];n_post=2;nk_svch=2;
      } /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea-- 0x1F(5 ?ac?yaia)*/

  if(CB_3_vh->ItemIndex==2){in1_at=Qv_vh[kod_att_my];in2_at=0x1F;n_post=3;nk_svch=1;
        }   /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea -- 0x1F(5 ?ac?yaia)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=Qv_vh[kod_att_my];n_post=3;nk_svch=2;
      } /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea-- 0x1F(5 ?ac?yaia)*/


   if((res=Vkl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- iao ioeaie, 1-- anou ioeaee */
    {
     ShowMessage("Ioeaea i?e ia?aaa?a oi?ioey?a aaiiuo 2 a OI7 ERR=1!\n");
     goto end1;
    }

    /* I?eai ioaaoiiai iaeaoa */
  if(res==2){ShowMessage("Iao ioaaoiuo iaeaoia ia iaeao 2!");}
       Sleep(5);

    m_freqq=F_rtu[j];
    m_p_1=powerDBM-dPg[j];   /* n o?aoii eaeea?iaee eaaaey */
    stat = viPrintf(viG,":FREQ %f MHz\n",m_freqq); // ?anoioa
     stat = viPrintf(viG,":POW %f dBm\n", m_p_1); // iiuiinou
  if (stat != VI_SUCCESS)
  {
     ShowMessage("Ioeaea i?e onoaiiaea cia?aiee ia aaia?aoi?");
     goto end;
  }

    viPrintf(viP,"ABORT\n");
    viPrintf(viP,"INIT:CONT ON\n");
    viPrintf(viP,"FETC?\n");
    viScanf(viP,"%t",buf);

    m_Pow = atof(buf);
      ind=j;
   m_Pow=m_Pow-dPm[ind];   /*n o?aoii eaeea?iaee eaaaey*/
    P_dB[j]=m_Pow;

        //  Pw=pow(10,Pdbm/10); //iAo       Pw=pow(10,-3)*pow(10,Pdbm/10);  //Ao

          m_Pow = pow(10.0,(m_Pow/10.0))*pow(10.0,-3.0); /*mBt -> Bt*/

          P[j]=m_Pow;  /* cia?aiea a Ao */
         //  x_m_p=Qvh_osl[j];

        /* ?oaiea aao?eea iiuiinoe */
                   /* cai?in eiaa iiuiinoe */
                         /* iaeao 9*/
//-----------------oi?ioey? ia?aaa?e aaiiuo a OI7 -------------------------------------------------------
//----------------?oaiea o?iaiy iiuiinoe aey eaiaeia oneeeoaeae------------------------------
 // if((CB_3_vh->ItemIndex==0)||(CB_3_vh->ItemIndex==1))
//   {
//  n_post=2; /*IIN*/
//   }
//  if((CB_3_vh->ItemIndex==2)||(CB_3_vh->ItemIndex==3))
//    {
//      n_post=3; /*CIN*/
//    }
 if(CB_10_vyh->ItemIndex<=11)  /* a caaeneiinoe io auoiaa */     {
     n_post=2; /**/
     }
  if(CB_10_vyh->ItemIndex>11)
     {
     n_post=3; /**/
     }
    nf=0x9;
 n_jj=0;

m_jj:
  if((res=zapr_dan_up7(n_post,nf))==1)   /*0-- iao ioeaie, 1-- anou ioeaee */
   {
     ShowMessage("Ioeaea i?e ia?aaa?a oi?ioey?a cai?ina aaiiuo (9) a OI7!\n");
    // 10.01.11 vyh=false; goto end;
   }

  Sleep(10);
 if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
        // Iao i?eiyouo iaeaoia
//     ShowMessage("Iao i?eiyouo iaeaoia iinea cai?ina ninoiyiey!");
   }

  if(!UPS_RECIV_KIO_PACKET(&nk,packet_my_km.buf_my))
   {
        // Iao i?eiyouo iaeaoia
//     ShowMessage("Iao i?eiyouo iaeaoia iinea cai?ina ninoiyiey!");
      if(n_jj<=9)
      {
      n_jj=n_jj+1;
      goto m_jj;
      }
      else
      {
       ShowMessage("Naie ii iaaeno?aea!");
       vyh=false; goto end; //goto m2_end_5;
      }
   }
   else
   {
        // I?eiyo iaeao

      LEN=packet_my_km.p_my_v.len;
      IPK=packet_my_km.p_my_v.byte1;
      SRC=packet_my_km.p_my_v.byte2&0x1F;
      DST=((packet_my_km.p_my_v.byte2>>5)&0x7)|((packet_my.p_my_v.byte3&0x3)<<3);  /* eaaia e?uei DST=0x6, i?aaia e?uei DST=0x7*/
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
     if(CB_10_vyh->ItemIndex<=12)  /* a caaeneiinoe io auoiaa */
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
    if(CB_10_vyh->ItemIndex>12)  /* a caaeneiinoe io auoiaa */
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
          //ShowMessage("Ioeaea i?e ia?aaa?a ioaaoiiai iaeaoa OI7 i?e ?oaiee eiaa iiuiinoe! ERR=1");
          //goto m1;
           n_jj=n_jj+1;
         if(n_jj<=9)
            {
             goto m_jj;
            }
          else
            {
             ShowMessage("Ioeaea i?e ia?aaa?a ioaaoiiai iaeaoa OI7 i?e ?oaiee eiaa iiuiinoe! ERR=1");
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

   }    /* end for ii ?anoioa */

  for(k1=0,P_max=P_min=P[0]; k1<=63; k1+=1)  /* au?eneaiea max ia e?eaie */
       {
        if(P[k1]>P_max) {P_max=P[k1];k_max=k1;}
        if(P[k1]<P_min) {P_min=P[k1];k_min=k1;}
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

    for(k1=0,Kod_max_km=Kod_min_km=Kod_DM_izm[0]; k1<=63; k1+=1)  /* au?eneaiea max ia e?eaie */
       {
        if(Kod_DM_izm[k1]>Kod_max_km) {Kod_max_km=Kod_DM_izm[k1];k_max=k1;}
        if(Kod_DM_izm[k1]<Kod_min_km) {Kod_min_km=Kod_DM_izm[k1];k_min=k1;}
       }

           memset(&buf1,0,20);
        sprintf(buf1,"%d",Kod_min_km);
           Edit17->Text=buf1;
           Edit17->Repaint();

        memset(&buf1,0,20);
        sprintf(buf1,"%d",Kod_max_km);

           Edit18->Text=buf1;
           Edit18->Repaint();

   end1:;                         /* iaeao 2 */
 //-----------------oi?ioey? ia?aaa?e aaiiuo a OI7 -------------------------------------------------------
//============/* auee??aiea i ao?eou aey  1-ai e 2-ai eaiaea NA? */=========================
          n_vh1= UD_2->Position-1; n_vh2=UD_2->Position-1;  /* io 0 ai 7*/

  if(CB_3_vh->ItemIndex==0){in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=1;
        }   /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea -- 0x1F(5 ?ac?yaia)*/

  if(CB_3_vh->ItemIndex==1){in1_at=0x1F;in2_at=0x1F;n_post=2;nk_svch=2;
      } /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea-- 0x1F(5 ?ac?yaia)*/

  if(CB_3_vh->ItemIndex==2){in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=1;
        }   /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea -- 0x1F(5 ?ac?yaia)*/

  if(CB_3_vh->ItemIndex==3){in1_at=0x1F;in2_at=0x1F;n_post=3;nk_svch=2;
      } /* eia aoiaiiai aoo. 1-iai,2-iai eaiaea-- 0x1F(5 ?ac?yaia)*/

  if((res=Vykl_nk_att_t(n_post,n_vh1,n_vh2,in1_at,in2_at,nk_svch))==1)   /*0-- iao ioeaie, 1-- anou ioeaee */
    {
     ShowMessage("Ioeaea i?e ia?aaa?a oi?ioey?a aaiiuo 2 a OI7 ERR=1!\n");
     //goto end;
    }
  if(res==2){ShowMessage("Iao ioaaoiuo iaeaoia ia iaeao 2!");}
     Sleep(1);
                         /* iaeao 1*/
  //-----------------oi?ioey? ia?aaa?e aaiiuo a OI7 -------------------------------------------------------
//============/* auee??aiea eaiaea oneeeoaey, auee??aiea enoi?ieea ieoaiey OI7 */=========================
 if(CB_10_vyh->ItemIndex<=11)  /* 1--0: 2(IIN), 3(CIN)*/
   {
    n_post=2;    /*IIN*/
   // nu=(CB_10_vyh->ItemIndex);    /*eiaaen io 0 ai 12*/  /* nu-- iiia? oneeeoaey*/
    }
   if(CB_10_vyh->ItemIndex>11)
   {
    n_post=3; /*CIN*/
   // nu=13-(CB_10_vyh->ItemIndex);    /*eiaaen io 13 ai 25*/  /* nu-- iiia? oneeeoaey*/
    }
  // nu=0;  /* ???? nu-- nu=(iiia? oneeeoaey*/

   if((res=Vykl_us_vip_t(n_post))==1)   /*0-- iao ioeaie, 1-- anou ioeaee */
    {
     ShowMessage("Ioeaea i?e ia?aaa?a oi?ioey?a aaiiuo (1) a OI7 ERR=1!\n");
    // goto end;
    }
    if(res==2){ShowMessage("Iao ioaaoiuo iaeaoia ia iaeao 1!");}
    Sleep(1);
   end:;
  viPrintf(viG,"OUTPut:STATe OFF\n"); //auee. neaiaea ia auoia aai-?a

    ShowMessage("Ecia?aiea caeii?aii\n");

 m1:;