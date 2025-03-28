//---------------------------------------------------------------------------


#pragma hdrstop

#include "ARM.h"
#include <math.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)

void __fastcall TForm1::MeashOutPow(TObject *Sender)
{
 Mode=1;
Panel1->Visible=false;
Panel2->Visible=false;
Panel_53->Visible=false;
Panel10->Visible=false;
SpeedButton1->Enabled=false;
PanelPotent->Visible=false;
Panel2->Visible=false;
PanelOUTPow->Visible=true;
StringGrid9->Cells[0][0]="Частота";

InitLt1();
FileCalbGnPm();

}
//---------------------------------------------------------------------------
void TForm1::InitLt1(void)
{
int colRow,i,colCol;
AnsiString St;
ComboBox10->Clear();
ComboBox11->Clear();

 if(RadioGroup8->ItemIndex==0)
  {
   ComboBox10->Items->Add("1ВЧ-2");
   ComboBox10->Items->Add("2ВЧ-2");
   ComboBox10->Items->Add("3ВЧ-2");
   ComboBox10->Items->Add("4ВЧ-2");
   for(i=0;i<13;i++)
    ComboBox11->Items->Add(IntToStr(i+1));

   CheckBox49->Visible=false;
   CheckBox50->Visible=false;
   CheckBox51->Visible=false;
   CheckBox52->Visible=false;
    colRow=65;
    colCol=9;
    StringGrid9->Width=392;

 for(i=0;i<5;i++)
   {
   StringGrid9->Cells[2*i+1][0]="Pвых";
   StringGrid9->Cells[2*i+2][0]="АЦП";
   }

  }
else if(RadioGroup8->ItemIndex==1)
   {
     ComboBox10->Items->Add("1ВЧ-53");
     ComboBox10->Items->Add("2ВЧ-53");
     ComboBox10->Items->Add("3ВЧ-53");
     ComboBox10->Items->Add("4ВЧ-53");

   for(i=0;i<12;i++)
    ComboBox11->Items->Add(IntToStr(i+1));

     colRow=161;
     colCol=17;

     StringGrid9->Width=731;
for(i=0;i<8;i++)
   {
   StringGrid9->Cells[2*i+1][0]="Pвых";
   StringGrid9->Cells[2*i+2][0]="АЦП";
   }

   CheckBox49->Visible=true;
   CheckBox50->Visible=true;
   CheckBox51->Visible=true;
   CheckBox52->Visible=true;
   }
StringGrid9->ColCount=colCol;
StringGrid9->RowCount=colRow;

ComboBox10->ItemIndex=0;
ComboBox11->ItemIndex=0;
}

void __fastcall TForm1::StartMeshPow(TObject *Sender)
{
PStop=false;

Button22->Enabled=false;
Button23->Enabled=true;
if(ChkDevs==true){
if(Res_UPPU()){
MyTimer(1000);
 BeginMeashPw();}
}
Button22->Enabled=true;
Button23->Enabled=false;
}
//---------------------------------------------------------------------------


void TForm1::BeginMeashPw(void)
{
extern unsigned IN_AT[4][64];
extern unsigned IN_AT_53[8][160];
int c,ret;
bool ShtatMode=false;
unsigned i,j,l;
float Pg,Pmm,Pdbm,Pw;
unsigned colSints,colLuch;
int ofs,indIn,indLit, indPSph,indOut;      //смещение индекса вектора калибровки для 53 литеры
float dltPg;
float Ppor;
int Fbeg,Flb,f,ind;
int Kode_ADC,ofchan;
Byte ONV2_0,ONV2_1;
Byte ONV3_0,ONV3_1;
AnsiString St,SPg;
AnsiString Ss,Sl,Swarn;
AnsiString FileNam;
int ofin;
OUTiIn.clear();
ClearStrGrdPow();
SPg=Trim(MaskEdit3->Text);
Pg=StrToInt(SPg);
PStop=false;

indIn=ComboBox10->ItemIndex;

if(RadioGroup7->ItemIndex==0)
{
Ss=" ППС ";
indPSph=0;
}
else
{
Ss=" ЗПС ";
indPSph=1;
}

if(RadioGroup8->ItemIndex==0)
{
 Sl="2";
 colSints=(Fb-Fl)/500;
 Flb=Fl;
 colLuch=4;
 ofchan=0;
 indLit=0;
 ofs=0;
 ofin=4;
 Ppor=2.0;
 if(indPSph==0)
 {
 ONV2_0=0x1;
 ONV2_1=0x0;
 ONV3_0=0x0;
 ONV3_1=0x0;
 }
 else
 {
 ONV2_0=0x0;
 ONV2_1=0x1;
 ONV3_0=0x0;
 ONV3_1=0x0;
 }
}
else
{
 Sl="53";
 colSints=(Fh-Fb)/500;
 Flb=Fb;
 colLuch=8 ;
 ofchan=8;
 ofin=0;
 indLit=1;
 ofs=(Fb-Fl)/500*8;
 Ppor=1.5;        //пороговая мощность
if(indPSph==0)
 {
 ONV2_0=0x0;
 ONV2_1=0x0;
 ONV3_0=0x1;
 ONV3_1=0x0;
 }
 else
 {
 ONV2_0=0x0;
 ONV2_1=0x0;
 ONV3_0=0x0;
 ONV3_1=0x1;
 }
}
indOut=ComboBox11->ItemIndex;

if(RadioGroup9->ItemIndex==1)
 {
  if(Packet_P_CO()==false) goto M1;
  else ShtatMode=true;
  MyTimer(500);
 }
else                         //пультовый
 {
  ShtatMode=false;
  ret=chten_mrt(indIn+1,indPSph,indLit);
  if(ret!=0)   //неудачное чтение
   goto M1;
  GetOutAtt(indLit);
 }

 St="Подключить кабель с генератора на вход "+ComboBox10->Items->Strings[ComboBox10->ItemIndex];
if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
{
St="Подключить кабель ВЧ с выхода"+ ComboBox11->Items->Strings[ComboBox11->ItemIndex]+Ss+"Литеры "+Sl+" на вход измерителя мощности через аттенюатор 30дБ ";
  if( Application->MessageBox(St.c_str(),"Внимание!", MB_ICONINFORMATION| MB_OKCANCEL)== IDOK )
   {
   InitPowMtr();
   InitE825(SPg);
   Pg=StrToInt(SPg);

if(ShtatMode==false)    //пультовый
 {
      InAttOff();//закрыть все вх аттенюаторы, пакет2
      OutAttOnOff(0xff) ; //закрыть все выходные аттенюаторы,  пакет3
      if(SetOUT_EUS( indLit, indPSph,  indOut)==false) goto M1;
 }

for(l=0;l<colLuch;l++)            //цикл по лучам
 {
  if(CheckedLuch(l)==true)
   {
//цикл по частоте
      for(j=0;j<colSints;j++)    // j- синтезаторов по 500МГц
    {
     Fbeg=Flb+26+500*j;
     for(i=0;i<8;i++)    //8 точек частоты в каждом синтезаторе
     {
      f=Fbeg+i*64;    // шаг частоты 64 МГц
      if((PStop==false) )
      {
       if(ShtatMode==false)  //пультовый режим
       {
        if(Att_Luch_Out(indIn, indOut, indLit,indPSph,l,Att_Ini[l][j*8+i],Att_OUTi[l][indOut][j*8+i])==false) goto M1;
       }
       else                           //штатный режим
        {
         Vkl_IP( 1,ONV2_0,ONV2_1,ONV3_0,ONV3_1);
         PaketFOC(indIn+ofin,indPSph,j+ofchan,i,l);
        }

      ind=j*8+i+ofs;
       dltPg=dPg[ind];
       SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
       CorrStrGen(SPg);
       WrGenE825(IntToStr(f),SPg);
       MyTimer(100);

      if((Pmm=StepRdPow())==0)
            goto M1;

       Pdbm=Pmm-dPm[ind];  //с учетом калибровки
//double Rt = RateAntenn53(ind-64 ,STATE_POZ);//K = RateAntenn53(freq_index-64 ,STATE_POZ);
//double Kf= (K_usil_prd[ind]-K_usil_prd[64])*0.25;
//     Val=Val+Kf*Rt;

      Pw=pow(10,-3)*pow(10,Pdbm/10);  //Вт   Pw=pow(10,Pdbm/10); //мВт
      Kode_ADC=GetADC(indLit, indPSph, indOut);

      PowADC.Pw=Pw;
      PowADC.Kode_ADC=Kode_ADC;
      OUTiIn.insert(OUTiIn.end(),PowADC);

      StringGrid9->Cells[0][ind-ofs+1]=IntToStr(f);
      if(Pw<Ppor)
        StringGrid9->Cells[l*2+1][ind-ofs+1]=CurrToStrF(Pw,ffFixed,2)+"  ?";
        else
         StringGrid9->Cells[l*2+1][ind-ofs+1]=CurrToStrF(Pw,ffFixed,2);

         StringGrid9->Cells[l*2+2][ind-ofs+1]=Kode_ADC;

       Application->ProcessMessages();
       }
      else
        goto M1;

  }  //for i
 }  //for j
        OfGenE825();
        InAttOff();//закрыть все вх аттенюаторы, пакет2
        OutAttOnOff(0xff) ; //закрыть все выходные аттенюаторы,  пакет3
    }//l==true
   }//for l

}//if
}//if
  EUSOff(); //выключить все усилители и запретить излучение,  пакет1
  Application->MessageBox("Измерение завершено.\n Спасибо!!!", "Внимание!", MB_ICONINFORMATION|MB_OK);

 FileNam=ComboBox11->Items->Strings[ComboBox11->ItemIndex]+Trim(Ss)+
            ComboBox10->Items->Strings[ComboBox10->ItemIndex].SubString(1,3)+"_"+Sl+".pmm" ;
 if(ShtatMode==true)
 FileNam="Sh"+FileNam;

 WrFileOUTiIn(FileNam,colLuch);

M1:     OfGenE825();
EUSOff(); //выключить все усилители и запретить излучение,  пакет1
        InAttOff();//закрыть все вх аттенюаторы, пакет2
        OutAttOnOff(0xff) ; //закрыть все выходные аттенюаторы,  пакет3




}

//Запись в фал вых мощности и кодов с i входа j выхода
void TForm1::WrFileOUTiIn(AnsiString FileNam, int colLuch)
{
AnsiString MyFileName,StDir;
unsigned  int i;
StDir=GetCurrentDir();
MyFileName=StDir+"\\PowMesh\\"+FileNam;

 if(FileExists(MyFileName))
     {
     if(Application->MessageBox("Файл уже существует. Переписать?","Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)!=ID_OK)
      goto M1;
     }
      Myfile=new TFileStream(MyFileName,fmCreate|fmOpenWrite);

 if(Myfile)
  {
    Myfile->Position=0;
    for(i=0;i<OUTiIn.size() ;i++)
    Myfile->WriteBuffer(&OUTiIn[i],sizeof(PowADC));

   delete(Myfile);
   Myfile=NULL;
  }
//  RdFileOUTiIn( MyFileName,  colLuch) ;
M1:    ;
}

//Чтение из фала вых мощности и кодов с i входа j выхода
void TForm1::RdFileOUTiIn(AnsiString MyFileName, int colLuch)
{
struct PowOutADC* buff;
  int n,i,sz;
   Myfile=new TFileStream(MyFileName,fmOpenRead);
       if(Myfile)
       {
        sz=sizeof(PowOutADC);
        n=Myfile->Size;

        n=(Myfile->Size)/sizeof(PowOutADC);
        buff=new PowOutADC[n];
          Myfile->Position=0;
        Myfile->ReadBuffer(buff,n*sizeof(PowOutADC));
        for(i=0;i<n ;i++)
         OUTiIn.insert(OUTiIn.end(),buff[i]);
          sz=OUTiIn.size();

         delete(Myfile);
         Myfile=NULL;
         delete[] buff;
       }
}

 //Читать файлы вых мощности и кодов с одного входы и всех выходов
void __fastcall TForm1::ReadFliIn(TObject *Sender)
{
AnsiString StNIn;
int indIn,colLuch,colOut;
int i,j;
AnsiString SbS,SbL,StrDir,StIn;
AnsiString MyFileName;

ComboBox10->Enabled=false;
ComboBox11->Enabled=false;
Label35->Enabled=false;
Label36->Enabled=false;
Label37->Enabled=false;
MaskEdit3->Enabled=false;

ClearStrGrdPow();
StringGrid9->RowCount=1;

//StNIn= InputBox("Введите номер входа", "один из четырех (1,2,3,4). Литера и Полусфера должны быть выбраны на панели","1");
StNIn=IntToStr(ComboBox10->ItemIndex+1);

if(RadioGroup7->ItemIndex==0)
SbS="ППС";
else
SbS="ЗПС";
if(RadioGroup8->ItemIndex==0)
{
 SbL="ВЧ_2";
//Flb=Fl;
colLuch=4;
colOut=13;
//Lit=0;
//colF=((Fb-Fl)/500)*8;
}
else
{
 SbL="ВЧ_53";
//Flb=Fb;
colLuch=8;
colOut=12;
//Lit=1;
//colF=((Fh-Fb)/500)*8;
}

StrDir=GetCurrentDir();

OUTiIn.clear();
//Ptl.PtIn.clear();
for(j=1;j<=colOut;j++)  // выходы
{
 OUTiIn.clear();
 StIn=IntToStr(j)+SbS+StNIn+SbL+".pmm";
 
 if(RadioGroup9->ItemIndex==1)  // штатный режим
 StIn="Sh"+StIn;

 MyFileName=StrDir+"\\PowMesh\\"+StIn;

 if(FileExists(MyFileName))
 {
  RdFileOUTiIn( MyFileName, colLuch);
  OutTabFls(j);
 }
}
ComboBox10->Enabled=true;
ComboBox11->Enabled=true;
Label35->Enabled=true;
Label36->Enabled=true;
Label37->Enabled=true;
MaskEdit3->Enabled=true;
}
//---------------------------------------------------------------------------

void  TForm1::OutTabFls(int NOut)
{
 int sz,colRow,ncolRow,colLuch;
 int i,l,j,ind,indk;
 int colSints,Flb,Fbeg,f;

if(RadioGroup8->ItemIndex==0)
{
 colSints=(Fb-Fl)/500;
 Flb=Fl;
 colLuch=4;
}
else
{
 colSints=(Fh-Fb)/500;
 Flb=Fb;
 colLuch=8 ;
}

sz=OUTiIn.size();
colRow=StringGrid9->RowCount;
StringGrid9->Cells[1][colRow]="Вых"+IntToStr(NOut);
ncolRow=colRow+sz/colLuch+1;    //число частотных точек
StringGrid9->RowCount=ncolRow;
for(l=0;l<colLuch;l++)            //цикл по лучам
 {
  //цикл по частоте
      for(j=0;j<colSints;j++)    // j- синтезаторов по 500МГц
    {
     Fbeg=Flb+26+500*j;
     for(i=0;i<8;i++)    //8 точек частоты в каждом синтезаторе
     {
      f=Fbeg+i*64;    // шаг частоты 64 МГц
       ind=j*8+i+colRow+1;
        indk=l*colSints*8+j*8+i;
      StringGrid9->Cells[0][ind]=IntToStr(f);
      StringGrid9->Cells[l*2+1][ind]=CurrToStrF(OUTiIn[indk].Pw,ffFixed,2);
      StringGrid9->Cells[l*2+2][ind]=IntToStr(OUTiIn[indk].Kode_ADC);
     }//i
    } // j
}  //l
}


int TForm1::GetADC(int indLit,int indPSph, int indOut)
{
int Kode_ADC;
Byte Adr_UP7;
int nf=9,k=0,nk,t;
//Byte LEN,IPK;
Byte ADC[13];
Byte ERR;
bool res;
union{
       struct{
                  U32   len     : 8, /*LEN*/
                        byte1   : 8, /*IPK*/
                        byte2   : 8, /*DST SRC*/
                        byte3   : 8, /*IPS DST*/
                        byte4   : 8, /*ERR*/
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

                        } p;
             U32 buf_my[256/4];
             } packet_ADC;

Adr_UP7=GetAdrUp7Post(indLit,indPSph);

/*M1:;
if( zapr_dan_up7( Adr_UP7, nf)==0)   //запрос прошел
{
MyTimer(10);
if(!UPS_RECIV_KIO_PACKET(&nk,packet_ADC.buf_my))  ;

     if(!UPS_RECIV_KIO_PACKET(&nk,packet_ADC.buf_my))
      {
       if(k<=9)
       {
        k++;
        goto M1;
       }//k
       else
       {
        Application->MessageBox("Ошибка приема запрошенного пакета!","УП7", MB_ICONERROR| MB_OK);
        return false;
       }
      } */


if((res=zapr_dan_up7(Adr_UP7,nf))==1)   /*0-- нет ошибок, 1-- есть ошибки */
    {
     ShowMessage("Ошибка при передаче формуляра запроса данных в УП7!\n");
     return 0;
    }

  t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = UPS_RECIV_KIO_PACKET(&nk,packet_ADC.buf_my);
   }while (!res && (GetTickCount() <= t));
   if (!res){
         ShowMessage("Нет принятых пакетов после запроса состояния!");
   return 0 ;
   }
     if( (ERR=packet_ADC.p.byte4&0x1)!=0) {
       ShowMessage("Ошибка передачи ответа на запрос данных");
     return 0;}

 else
 {
 /* Прием ответного пакета */
     // LEN=packet_ADC.p.len;
    //  IPK=packet_ADC.p.byte1;
     // SRC=packet_ADC.p.byte2&0x1F;
    //  DST=((packet_ADC.p.byte2>>5)&0x7)|((packet_ADC.p.byte3&0x3)<<3);  /* левое крыло DST=0x6, правое крыло DST=0x7*/
     // IPS=(packet_ADC.p.byte3>>2)&0x3F;
   //   ERR=packet_ADC.p.byte4&0x1;
    //  IPK_UP7=packet_ADC.p.byte5;
      ADC[0]=packet_ADC.p.byte6;
      ADC[1]=packet_ADC.p.byte7;
      ADC[2]=packet_ADC.p.byte8;
      ADC[3]=packet_ADC.p.byte9;
      ADC[4]=packet_ADC.p.byte10;
      ADC[5]=packet_ADC.p.byte11;
      ADC[6]=packet_ADC.p.byte12;
      ADC[7]=packet_ADC.p.byte13;
      ADC[8]=packet_ADC.p.byte14;
      ADC[9]=packet_ADC.p.byte15;
      ADC[10]=packet_ADC.p.byte16;
      ADC[11]=packet_ADC.p.byte17;
      ADC[12]=packet_ADC.p.byte18;

 }


  return int(ADC[indOut]);
}


void __fastcall TForm1::ChngLt(TObject *Sender)
{
InitLt1();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CloseOutPow(TObject *Sender)
{
 StopMshPow(Sender) ;
 PanelOUTPow->Visible=false;
}
//---------------------------------------------------------------------------
void TForm1::ClearStrGrdPow()
{
 int i,j;

for(j=0;j<StringGrid9->ColCount;j++)
{
for (i=1;i<StringGrid9->RowCount;i++)
 StringGrid9->Cells[j][i]="";
}
}

void TForm1::GetOutAtt(int indLit)
{
int i,j,k;
int col_fr,col_luch,out_lit;
 extern unsigned AT_1[4][64],AT_2[4][64],AT_3[4][64],AT_4[4][64],AT_5[4][64],AT_6[4][64],
         AT_7[4][64],AT_8[4][64],AT_9[4][64],AT_10[4][64],AT_11[4][64],
         AT_12[4][64],AT_13[4][64];  /* аттенюаторы выходных усилит. передатчика */
extern unsigned  AT_1_53[8][160],AT_2_53[8][160],AT_3_53[8][160],AT_4_53[8][160],
         AT_5_53[8][160],AT_6_53[8][160],AT_7_53[8][160],AT_8_53[8][160],
         AT_9_53[8][160],AT_10_53[8][160],AT_11_53[8][160],AT_12_53[8][160],
         AT_13_53[8][160];  /* аттенюаторы выходных усилит. передатчика литера 53*/
 extern unsigned IN_AT[4][64];
 extern unsigned IN_AT_53[8][160];

if(indLit==0){
 col_fr=64;
 col_luch=4;
 out_lit=13;
 }
else if(indLit==1){
 col_fr=160;
 col_luch=8;
 out_lit=12;

 }
if(indLit==0)     //litera2
{
for(j=0;j<col_luch;j++)
{
 for(i=0;i<col_fr;i++){
      Att_Ini[j][i]=IN_AT[j][i];
  }
}
for(k=0;k<out_lit;k++)
 {
for(j=0;j<col_luch;j++)
{
 for(i=0;i<col_fr;i++)
  {
   if(k==0)         Att_OUTi[j][k][i]=AT_1[j][i];
    else if(k==1)    Att_OUTi[j][k][i]=AT_2[j][i];
     else if(k==2)    Att_OUTi[j][k][i]=AT_3[j][i];
      else if(k==3)    Att_OUTi[j][k][i]=AT_4[j][i];
       else if(k==4)    Att_OUTi[j][k][i]=AT_5[j][i];
        else if(k==5)     Att_OUTi[j][k][i]=AT_6[j][i];
         else if(k==6)    Att_OUTi[j][k][i]=AT_7[j][i];
          else if(k==7)    Att_OUTi[j][k][i]=AT_8[j][i];
           else if(k==8)    Att_OUTi[j][k][i]=AT_9[j][i];
            else if(k==9)    Att_OUTi[j][k][i]=AT_10[j][i];
             else if(k==10)   Att_OUTi[j][k][i]=AT_11[j][i];
              else if(k==11)   Att_OUTi[j][k][i]=AT_12[j][i];
               else if(k==12)   Att_OUTi[j][k][i]=AT_13[j][i];
  }
}
}
}
else  if(indLit==1)    //53
{
for(j=0;j<col_luch;j++)
{
 for(i=0;i<col_fr;i++){
      Att_Ini[j][i]=IN_AT_53[4][64];
  }
}
for(k=0;k<out_lit;k++)
 {
for(j=0;j<col_luch;j++)
{
 for(i=0;i<col_fr;i++)
  {
   if(k==0)         Att_OUTi[j][k][i]=AT_1_53[j][i];
    else if(k==1)    Att_OUTi[j][k][i]=AT_2_53[j][i];
     else if(k==2)    Att_OUTi[j][k][i]=AT_3_53[j][i];
      else if(k==3)    Att_OUTi[j][k][i]=AT_4_53[j][i];
       else if(k==4)    Att_OUTi[j][k][i]=AT_5_53[j][i];
        else if(k==5)     Att_OUTi[j][k][i]=AT_6_53[j][i];
         else if(k==6)    Att_OUTi[j][k][i]=AT_7_53[j][i];
          else if(k==7)    Att_OUTi[j][k][i]=AT_8_53[j][i];
           else if(k==8)    Att_OUTi[j][k][i]=AT_9_53[j][i];
            else if(k==9)    Att_OUTi[j][k][i]=AT_10_53[j][i];
             else if(k==10)   Att_OUTi[j][k][i]=AT_11_53[j][i];
              else if(k==11)   Att_OUTi[j][k][i]=AT_12_53[j][i];
               else if(k==12)   Att_OUTi[j][k][i]=AT_13_53[j][i];
  }
 }
 }
}
}


void __fastcall TForm1::StopMshPow(TObject *Sender)
{
//
PStop=true;
// OfGenE825();
// EUSOff(); //выключить все усилители и запретить излучение,  пакет1
// InAttOff();//закрыть все вх аттенюаторы, пакет2
// OutAttOnOff(0xff) ; //закрыть все выходные аттенюаторы,  пакет3
}
//---------------------------------------------------------------------------
bool TForm1::CheckedLuch(unsigned l)
{
if(l==0)
return (CheckBox45->Checked);
if(l==1)
return (CheckBox46->Checked);
if(l==2)
return (CheckBox47->Checked);
if(l==3)
return (CheckBox48->Checked);
if(l==4)
return (CheckBox49->Checked);
if(l==5)
return (CheckBox50->Checked);
if(l==6)
return (CheckBox51->Checked);
if(l==7)
return (CheckBox52->Checked);
else
return false;
}

