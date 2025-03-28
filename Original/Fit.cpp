


#pragma hdrstop

#include "ARM.h"
#include <algorithm.h>
#include <Math.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)
void __fastcall TForm1::MnFit(TObject *Sender)
{

 Panel1->Visible=false;
 Panel2->Visible=false;
 Panel3->Visible=false;
 Panel5->Visible=false;
 PanelPotent->Visible=false;
PanelSummPow->Visible=false;
P_1->Visible=false;
Panel2->Visible=false;
PanelOUTPow->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FitTrRate(TObject *Sender)
{
 ComboBox2->Items->Add("1");
 ComboBox2->Items->Add("2");
 ComboBox2->Items->Add("КС");
 ComboBox2->ItemIndex=-1;

 FileCalbGnPm();
Chart2->BottomAxis->Maximum=((Fh-Fl)/500)*8; //шкала х графика
TrackBar1->Max=((Fh-Fl)/500)*8;
TrackBar1->Position=TrackBar1->Max/2;
TrackBar1->Brush->Color=clWhite;
TrackBar1->Enabled=false;
ShowPanel4();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
int pos;
int f;
double integ;
double frack;
 float Pg,dltPg,dltPm;
 float Pmm;
 float P;    //мошность, считываемая с измерителя мощности с учетом калибр
 AnsiString SPg,S;
dl=true;
if(TrackBar1->Enabled==true)
{
 pos=TrackBar1->Position;
 modf(pos/8, &integ);
 frack=pos-integ*8;
 f=integ*500+frack*64+Fl+26;

  SPg=Trim(MaskEdit5->Text);   //мощность генератора
 Pg=StrToFloat(SPg);


      dltPg=dPg[pos];
       SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
       CorrStrGen(SPg);
       WrGenE825(IntToStr(f),SPg);
       Pmm=StepRdPow();
       P=Pmm-dPm[pos];
       OutChart4(pos,P-Pg) ;
}

}

//---------------------------------------------------------------------------
void __fastcall TForm1::ChouseFitChn(TObject *Sender)
{
AnsiString S,St;
int BgTrBr;
S=ComboBox2->Items->Strings[ComboBox2->ItemIndex];

St="Подключить кабель с генератора на вход "+S;
if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
{
St="Подключить кабель ВЧ с выхода прибора ПКУ3-52 на вход измерителя мощности";
  if( Application->MessageBox(St.c_str(),"Внимание!", MB_ICONINFORMATION| MB_OKCANCEL)== IDOK )
   {
        Label17->Caption = "Коэффициент передачи Кп  прибора ПКУ3-52, вход "+S ;

       TrackBar1->Max=((Fh-Fl)/500)*8;
       BgTrBr=TrackBar1->Max/2;
       TrackBar1->Position=BgTrBr;
       Panel5->Visible=true;
}
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrRate(TObject *Sender)
{

CStop=false;
TrackBar1->Position=TrackBar1->Max/2;
TrackBar1->Enabled=false;
CleanDraw1(Sender) ;
 if(RadioGroup2->ItemIndex==0)
 TrRateStep();
 else if(RadioGroup2->ItemIndex==1)
        TrRateCycl();

}

void TForm1::TranslateRateStp(void)
{
  int Fbeg;
 float Pg,dltPg,dltPm,Pmm;
 float P;    //мошность, считываемая с измерителя мощности с учетом калибр
 AnsiString SPg;
 int f,i,j;
 int cnt=0;
 int ind; //индекс доступа к массивам калибровки
 vector < float > TrRt;  // коэффициент передачи
 float TrRmin,TrRmax, dTr;


 Chart2->BottomAxis->Maximum=((Fh-Fl)/500)*8;

 TrRt.clear();
  PStop=false;

 SPg=Trim(MaskEdit5->Text);   //мощность генератора
 Pg=StrToFloat(SPg);
 // CheckCalbPm();
  InitPowMtr();
 InitE825(SPg);
  Button11->Enabled=true;   // стоп
for(j=0;j<28;j++)    // 28 синтезаторов по 500МГц
 {
  Fbeg=Fl+26+500*j;
  for(i=0;i<8;i++)    //8 точек частоты в каждом синтезаторе
  {
                //точки частоты
   f=Fbeg+i*64;    // шаг частоты 64 МГц
     if((PStop==false) )
      {
        dltPg=dPg[cnt];
       SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
       CorrStrGen(SPg);
       WrGenE825(IntToStr(f),SPg);

      if((Pmm=StepRdPow())==0)
      {
       TrRt.clear();
       goto M1;
      }
       P=Pmm-dPm[cnt];
       TrRt.insert(TrRt.end(),(P-Pg));
       OutChart3(cnt,P-Pg) ;
        cnt++;
       Application->ProcessMessages();
       }
       else
       {
        TrRt.clear();
        goto M1;
       }
     } //i
    } //j

 if(TrRt.size()!=0)
  {
   TrRmin = *min_element(TrRt.begin(), TrRt.end()) ;
   TrRmax = *max_element(TrRt.begin(), TrRt.end()) ;
   dTr=TrRmax-TrRmin;
   Label14->Caption="Кпmin="+CurrToStrF(TrRmin,ffFixed,2);
   Label15->Caption="dКп="+CurrToStrF(dTr,ffFixed,2);
  }//if  TrRt.size()
 M1:;
}

void TForm1::TrRateStep()
{

//Button11->Enabled=true;   // стоп
Button9->Enabled=false;   //Кп
Button10->Enabled=false;  // Кп ручн
Button13->Enabled=false;  // Очистить график
TrackBar1->Enabled=false;

if(ChkDevs==true)
 TranslateRateStp();
 else
 {
if(FindDevises()==true)
 {
 if(ChekDev()==true)
  TranslateRateStp();

 }    //FindDevises()
 }//else
Button11->Enabled=false;   // стоп
Button9->Enabled=true;   //Кп
Button10->Enabled=true;  // Кп ручн
Button13->Enabled=true;  // Очистить график
if(viG!=0)
OfGenE825();
}

void TForm1:: TranslateRateCycl(void)
{

for(;;)
{
if(CStop!=true)
{
TranslateRateStp();
Series3->Clear();
 Application->ProcessMessages();
}
else break;
}
}

void TForm1::TrRateCycl(void)
{
 //Button11->Enabled=true;   // стоп
Button9->Enabled=false;   //Кп
Button10->Enabled=false;  // Кп ручн
Button13->Enabled=false;  // Очистить график
TrackBar1->Enabled=false;

if(ChkDevs==true)
 TranslateRateCycl();
 else
 {
  if(FindDevises()==true)
  {
   if(ChekDev()==true)
   TranslateRateCycl();

  }    //FindDevises()
 }//else

Button11->Enabled=false;   // стоп
Button9->Enabled=true;   //Кп
Button10->Enabled=true;  // Кп ручн
Button13->Enabled=true;  // Очистить график
if(viG!=0)
 OfGenE825();
}





void TForm1::ShowPanel4(void)
{

Panel4->Visible=true;

}
void TForm1:: ShowPanel5(void)
{
       Button11->Enabled=false;
       CStop=false;
       PStop=false;
       Button9->Visible=true;
       Button10->Visible=true;
       Button13->Visible=true;

}

void __fastcall TForm1::StopFit(TObject *Sender)
{
PStop=true;
if(RadioGroup2->ItemIndex==1)
CStop=true;
Button9->Enabled=true;   //Кп
Button10->Enabled=true;  // Кп ручн
Button13->Enabled=true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CloseOfFit(TObject *Sender)
{
 //
 PStop=false;
 CStop=false;
 Panel4->Visible=false;
 Series3->Clear();
 if(viG!=0)
 OfGenE825();
}

void __fastcall TForm1::TrRateManual(TObject *Sender)
{

if(ChkDevs==false)
 {
  if(FindDevises()==true)
  {
   if(ChekDev()==true)
   {
   TrackBar1->Position=TrackBar1->Max/2;;
   TrackBar1->Enabled=true;
   }
  }    //FindDevises()
 }   //if
else
{
TrackBar1->Position=TrackBar1->Max/2;;
TrackBar1->Enabled=true;
}
// CheckCalbPm();
}
//---------------------------------------------------------------------------
void TForm1::OutChart3(int F,float P)
{
//if(Series3->SeriesColor==clBlue)
//Series3->ValueColor[F]=clRed;
//else
//Series3->ValueColor[F]=clBlue;

 Series3->AddXY(F,P);
}//---------------------------------------------------------------------------
void TForm1::OutChart4(int F,float P)
{
 Series4->AddXY(F,P);
}//---------------------------------------------------------------------------
void __fastcall TForm1::CleanDraw1(TObject *Sender)
{
Series3->Clear();
Series4->Clear();
TrackBar1->Position=TrackBar1->Max/2;;

}
