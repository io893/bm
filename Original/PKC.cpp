//---------------------------------------------------------------------------


#pragma hdrstop

#include "ARM.h"
#include "algorithm.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
void TForm1::ClearStrGrd1(void)
{
int i,j;

for(j=0;j<StringGrid8->ColCount;j++)
for (i=1;i<StringGrid8->RowCount;i++)
StringGrid8->Cells[j][i]="";

for(i=0;i<=9;i=i+3)
  StringGrid8->Cells[i][0]="Кпmin";
for(i=1;i<=9;i=i+3)
  StringGrid8->Cells[i][0]="dКп";
for(i=2;i<=9;i=i+3)
  StringGrid8->Cells[i][0]="Кпвыкл";

}


//---------------------------------------------------------------------------

void __fastcall TForm1::PKC_52TrRt(TObject *Sender)
{
Panel2->Visible=true;
Panel1->Visible=false;
SpeedButton1->Enabled=false;
PanelPotent->Visible=false;
ProgressBar2->Visible=false;
Mode=0; //0
ClearStrGrd1();

FileCalbGnPm();

}


void __fastcall TForm1::startPKC(TObject *Sender)
{

Button19->Enabled=false;
Button20->Enabled=true;
///!!!!
//  ChkDevs=true;
if(ChkDevs==true)
 ThroughPKC();
 else
 {
  if(FindDevises()==true)
  {
   if(ChekDev()==true)
   ThroughPKC();

  }    //FindDevises()
 }//else

Button19->Enabled=true;
Button20->Enabled=false;
}

void TForm1::InAtt(Byte indIn,Byte ValAtt)
{
 Byte DATA_UP7[3];
 Byte ON1,ON2;
 Byte N1O=0,N2O=0;
 Byte lN1Att;
 Byte lN2Att;
 Byte ADR_UP7;

// Вкл/Выкл матрицы для 1,2 канала
 if((indIn==0)||(indIn==2)||(indIn==4)||(indIn==6))    //1 канал  литеры 53 и 2
 {
   lN1Att=ValAtt;
   lN2Att=0x1f;// мах затухание
   ON1=1;
   ON2=0;
 }
 else if((indIn==1)||(indIn==3)||(indIn==5)||(indIn==7)) //2 канал  литеры 53 и 2
      {
       lN2Att=ValAtt;
       lN1Att=0x1f;// мах затухание
       ON1=0;
       ON2=1;
      }
//Адрес УП7
if(indIn<2)
ADR_UP7=0x0;
 else if(indIn<4)
      ADR_UP7=0x1;
      else  if(indIn<6)
            ADR_UP7=0x2;
            else if(indIn<8)
                 ADR_UP7=0x3;

DATA_UP7[0]=N1O|(N2O<<4);
DATA_UP7[1]=lN1Att|(ON1<<5);
DATA_UP7[2]=lN2Att|(ON2<<5);

PaketUP7_2( ADR_UP7,DATA_UP7)   ;
}

void TForm1::ProcessPKC(Byte& indIn,Byte& indOut,int Nout)
{
int indLit,ofs;
AnsiString St,StRez;
 float Pg,dltPg,dltPm;
 float Pmm,Pz;
 float P;    //мошность, считываемая с измерителя мощности с учетом калибр
 AnsiString SPg,S;
 int f,i,j,bj;
 int ind,colSints; //индекс доступа к массивам калибровки
 int Fbeg,Flb;
 vector < float > TrRt;  // коэффициент передачи
// vector < float > Poff;
 float TrRmin,TrRmax, dTr;

 TrRt.clear();
// Poff.clear();
  PStop=false;

if(indIn>3)        // литера 2
{
 colSints=(Fb-Fl)/500;
 Flb=Fl;
 ofs=0;
}
else                  // литера 53
{
 colSints=(Fh-Fb)/500;
 Flb=Fb;
 ofs=(Fb-Fl)/500*8;
}

//ShiftOutPKC(indIn,0); //отключить все выходы ПКС-52
SPg=Edit20->Text;

   Pg=StrToInt(SPg);
ProgressBar2->Max=colSints*8;
ProgressBar2->Position=ProgressBar2->Min;
ProgressBar2->Visible=true;

InAtt(indIn,0);   //Включить входной аттенюатор
MyTimer(100);
ShiftOutPKC(indIn,indOut);//подключить выход ПКС-52

for(j=0;j<colSints;j++)    //  синтезаторов по 500МГц
    {
     Fbeg=Flb+26+500*j;
     for(i=0;i<8;i++)    //8 точек частоты в каждом синтезаторе
     {
      f=Fbeg+i*64;    // шаг частоты 64 МГц
      if((PStop==false) )
      {

      ind=j*8+i+ofs;
       dltPg=dPg[ind];

      ShiftOutPKC(indIn,indOut);//подключить выход ПКС-52

       SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
       CorrStrGen(SPg);
       WrGenE825(IntToStr(f),SPg);

     if((Pmm=StepRdPow())==0)
           goto M1;

       P=Pmm-dPm[ind];

       ProgressBar2->StepIt();
       TrRt.insert(TrRt.end(),(P-Pg));

//       ShiftOutPKC(indIn,0); //отключить все выходы ПКС-52
//       Sleep(1000);
 //      if((Pmm=StepRdPow())==0)
//           goto M1;

//       P=Pmm-dPm[ind];
//       Poff.insert(Poff.end(),(P-Pg));

       Application->ProcessMessages();
       }
      else
       {
        TrRt.clear();
      goto M1;
       }

  }  //for i
 }  //for j
M1:   ProgressBar2->Visible=false;
  if(indIn<4)
   bj=5;
  else
   bj=-3;
 if(TrRt.size()!=0)
  {
   TrRmin = *min_element(TrRt.begin(), TrRt.end()) ;
   TrRmax = *max_element(TrRt.begin(), TrRt.end()) ;
   dTr=TrRmax-TrRmin;
  if(indOut!=0)
  {
   StringGrid8->Cells[(Nout-1)*3][bj+indIn]=CurrToStrF(TrRmin,ffFixed,2);
   StringGrid8->Cells[(Nout-1)*3+1][bj+indIn]=CurrToStrF(dTr,ffFixed,2);
  }//if  TrRt.size()
else//if(Poff.size()!=0)
 {
//    Pz = *max_element(Poff.begin(), Poff.end()) ;
  // StringGrid8->Cells[(Nout-1)*3+2][bj+indIn]=CurrToStrF(Pz,ffFixed,2);
  StringGrid8->Cells[(Nout-1)*3+2][bj+indIn]=CurrToStrF(TrRmax,ffFixed,2);
 }
 }// TrRt.size()!=0
}


Byte TForm1::ShiftOutPKC(int indIn,int OutPKS, Byte Attn)//подать код на ПКС-52
{
 Byte bytes[4];
 Byte NKSK0=1,NKSK1=1;
 Byte SKS=indIn<<2;
 Byte DKS=OutPKS;
 Byte RRPT=0x2<<5;
 Byte retdan=0x0 ;
bytes[0]=NKSK1<<3|NKSK0;
bytes[1]=DKS|SKS|RRPT;
bytes[2]=0;
bytes[3]=Attn&0x3;
if(PaketFUP(bytes,retdan))
return retdan;
else
return 0;
}

void TForm1::CycleOut(Byte& indIn)
{
AnsiString St;
 Byte indOut;

 // выходы

 if(CheckBox44->Checked==true)
 {
 St="Подключить кабель ВЧ с Выхода1 ПКС-52 на вход измерителя мощности";
  if( Application->MessageBox(St.c_str(),"Внимание!", MB_ICONINFORMATION| MB_OKCANCEL)== IDOK )
  {

   indOut=1;
   ProcessPKC(indIn,indOut,1);
   indOut=0;
   ProcessPKC(indIn,indOut,1); // при выключенных выходах ПКС
  }
 }
 if(CheckBox34->Checked==true)
 {
 St="Подключить кабель ВЧ с Выхода2 ПКС-52 на вход измерителя мощности";
  if( Application->MessageBox(St.c_str(),"Внимание!", MB_ICONINFORMATION| MB_OKCANCEL)== IDOK )
  {

   indOut=2;
   ProcessPKC(indIn,indOut,2);
   indOut=0;
   ProcessPKC(indIn,indOut,2);// при выключенных выходах ПКС
  }
 }
 if(CheckBox35->Checked==true)
 {
 St="Подключить кабель ВЧ с Выхода3 ПКС-52 на вход измерителя мощности";
  if( Application->MessageBox(St.c_str(),"Внимание!", MB_ICONINFORMATION| MB_OKCANCEL)== IDOK )
  {

   indOut=3;
   ProcessPKC(indIn,indOut,3);
   indOut=0;
   ProcessPKC(indIn,indOut,3); // при выключенных выходах ПКС
  }
 }

}
void TForm1::ThroughPKC(void)
{
Byte indIn ;
AnsiString St,StRez;
  PStop=false;
   InitPowMtr();
   InitE825();

if(Packet_P_CO()==true)
{
 MyTimer(1000);
 InAttOff() ; //отключить входные аттенюаторы

 MyTimer(100);
ShiftOutPKC(0,0); //отключить все выходы ПКС-52

 //входы
if(CheckBox36->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на Вход 1ВЧ-2";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
    {
     indIn=0x4;
     CycleOut(indIn);
    }
 }

 if(CheckBox37->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на Вход 2ВЧ-2";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
    {
     indIn=0x5;
     CycleOut(indIn);
    }
 }

 if(CheckBox38->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на Вход 3ВЧ-2";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
    {
     indIn=0x6;
     CycleOut(indIn);
    }
 }
 if(CheckBox39->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на Вход 4ВЧ-2";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
    {
     indIn=0x7;
     CycleOut(indIn);
    }
 }

 if(CheckBox40->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на вход 1ВЧ-53";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
    {
     indIn=0x0;
     CycleOut(indIn);
    }
 }
 if(CheckBox41->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на вход 2ВЧ-53";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
    {
     indIn=0x1;
     CycleOut(indIn);
    }
 }
 if(CheckBox42->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на вход 3ВЧ-53";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
    {
     indIn=0x2;
     CycleOut(indIn);
    }
 }
 if(CheckBox43->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на вход 4ВЧ-53";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
    {
     indIn=0x3;
     CycleOut(indIn);
    }
 }

 OfGenE825();
ProgressBar2->Visible=false;
  }
}

void __fastcall TForm1::StopPKC(TObject *Sender)
{
//
PStop=true;
OfGenE825();
ShiftOutPKC(0,0); //отключить все выходы ПКС-52
InAttOff();//отключить входные аттенюаторы

}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClosePKC(TObject *Sender)
{
PStop=true;
ClearStrGrd1();
Panel2->Visible=false;
}
//---------------------------------------------------------------------------

//------ПКС-ПКУ-----

void __fastcall TForm1::ChekPKC_PKU(TObject *Sender)
{
ShowPanel(Panel_PKC_PKU);
Mode=0; //0
dPm.clear();
dPg.clear();
FileCalbGnPm();
ClearStrGrd5();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Beg_PKC_PKU(TObject *Sender)
{

if(ChkDevs==true)
 {
 if(Res_UPPU()){
   MyTimer(1000);
  ThroughPKC_PKU();  }
 }


}

void  TForm1:: ThroughPKC_PKU(void)
{

AnsiString St;
int indIn,col;
PStop=false;
//ClearStrGrd5();
if(Packet_P_CO()==true)
{
 MyTimer(1000);
 InAttOff() ; //отключить входные аттенюаторы

 MyTimer(100);
if(!ShiftOutPKC(0,0)) return;//отключить все выходы ПКС-52

 //входы
if(CheckBox65->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на Вход 1ВЧ-2";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
   {      indIn=0x4;
          col=1;
      WorkPKC_PKU(indIn,0x3,col);}
 }

 if(CheckBox66->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на Вход 2ВЧ-2";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
  {  indIn=0x5;
     col=3  ;
  WorkPKC_PKU(indIn,0x3,col);}
 }

 if(CheckBox67->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на Вход 3ВЧ-2";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
   { indIn=0x6;
    col=5;
   WorkPKC_PKU(indIn,0x3,col);}
 }
 if(CheckBox68->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на Вход 4ВЧ-2";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
  {   indIn=0x7;
      col=7;
  WorkPKC_PKU(indIn,0x3,col);
  }
 }

 if(CheckBox69->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на вход 1ВЧ-53";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
   {  indIn=0x0;
      col=9;
   WorkPKC_PKU(indIn,0x3,col);}
 }
 if(CheckBox70->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на вход 2ВЧ-53";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
   {  indIn=0x1;
      col=11;
   WorkPKC_PKU(indIn,0x3,col);}
 }
 if(CheckBox71->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на вход 3ВЧ-53";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
   {  indIn=0x2;
      col=13;
   WorkPKC_PKU(indIn,0x3,col);}
 }
 if(CheckBox72->Checked==true)
 {
  St="Подключить кабель ВЧ с генератора на вход 4ВЧ-53";
   if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
    {
     indIn=0x3;
     col=15;
     WorkPKC_PKU(indIn,0x3,col);
    }
 }

}
 OfGenE825();
 InAttOff() ; //отключить входные аттенюаторы
  MyTimer(100);
ShiftOutPKC(0,0); //отключить все выходы ПКС-52

}
//---------------------------------------------------------------------------


void TForm1::WorkPKC_PKU(int indIn,int indOut,int col)
{
int indLit,ofs;
AnsiString St,StRez;
 float Pg,dltPg,dltPm;
 float Pmm,Kmin=INIT_VAL ;
 float P;    //мошность, считываемая с измерителя мощности с учетом калибр
 AnsiString SPg,S;
 int f,i,j,bj;
 int ind,colSints; //индекс доступа к массивам калибровки
 int Fbeg,Flb;

if(indIn>3)        // литера 2
{
 colSints=(Fb-Fl)/500;
 Flb=Fl;
 ofs=0;
}
else                  // литера 53
{
 colSints=(Fh-Fb)/500;
 Flb=Fb;
 ofs=(Fb-Fl)/500*8;
}

SPg=Edit24->Text;
   Pg=StrToInt(SPg);

InAtt(indIn,0);   //Включить входной аттенюатор
MyTimer(100);
if(!ShiftOutPKC(indIn,indOut)) return;//подключить выход ПКС на вход ПКУ-52

for(j=0;j<colSints;j++)    //  синтезаторов по 500МГц
    {
     Fbeg=Flb+26+500*j;
     for(i=0;i<8;i++)    //8 точек частоты в каждом синтезаторе
     {
      f=Fbeg+i*64;    // шаг частоты 64 МГц
      if((PStop==false) )
      {
      ind=j*8+i+ofs;
       dltPg=dPg[ind];
//      ShiftOutPKC(indIn,indOut);//подключить выход ПКУ-52

       SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
       CorrStrGen(SPg);
       WrGenE825(IntToStr(f),SPg);

     if((Pmm=StepRdPow())==0)
           goto M1;
       P=Pmm-dPm[ind];
if(Kmin > (P-Pg)) Kmin=P-Pg;
   StringGrid5->Cells[0][ind+1]=IntToStr(f);
   StringGrid5->Cells[col][ind+1]=CurrToStrF(P,ffFixed,2);
   StringGrid5->Cells[col+1][ind+1]=CurrToStrF(P-Pg,ffFixed,2);

       Application->ProcessMessages();
}
      else {
      goto M1;
       }

  }  //for i
 }  //for j
 StringGrid5->Cells[1][226]= "Kmin";
 StringGrid5->Cells[col+1][226]= CurrToStrF(Kmin,ffFixed,2);
M1:;
}

void __fastcall TForm1::StopPKC_PKU(TObject *Sender)
{
PStop=true;
}
//---------------------------------------------------------------------------
void TForm1::ClearStrGrd5(void)
{
int i,j;

for(j=0;j<StringGrid5->ColCount;j++)
for (i=1;i<StringGrid5->RowCount;i++)
StringGrid5->Cells[j][i]="";

for(i=1;i<=16;i=i+2)
  StringGrid5->Cells[i][0]="Pвых";
for(i=2;i<=16;i=i+2)
  StringGrid5->Cells[i][0]="Кп";
StringGrid5->Cells[0][0]="F";
}

void __fastcall TForm1::ClosePKU_PKC(TObject *Sender)
{
PStop=true;
Panel_PKC_PKU->Visible=false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N41Click(TObject *Sender)
{

//ShowPanel(Panel15);
//FileCalbGnPm();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ChekAtten(TObject *Sender)
{
AnsiString St;
Button67->Enabled=false;
Button68->Enabled=false;
Button69->Enabled=false;
Button70->Enabled=false;
Button69->Enabled=true;
float Pg=-35.0;

if(ChkDevs==true)
 {
  OfGenE825();
//if(!ShiftOutPKC(0,0)) return; //отключить все выходы ПКС-52

St="Подключить выход генератора на вход КС ПКУ";
if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK){
St="Подключить выход ПКУ к измерителю мощности ";
if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK){
Edit39->Text=CurrToStrF(Pg,ffFixed,2);
if(WorkAtt())
Application->MessageBox("Аттенюаторы исправны", "", MB_ICONINFORMATION|MB_OK);
}
}
}//ChkDevs

Button69->Enabled=true; //CompKC
Button70->Enabled=true; // out
Button67->Enabled=true;  // Att
Button68->Enabled=true;  //VCH
Button71->Enabled=false; //stop
}
//---------------------------------------------------------------------------
bool TForm1:: WorkAtt(void)
{
AnsiString StF;
 float Pg,dltPg,dltPm;
 float Pmm,f ;
 float Patt;    //мошность, считываемая с измерителя мощности с учетом калибр
 AnsiString SPg;
 Byte KodeAtt;
 int ind; //индекс доступа к массивам калибровки

  PStop=false;

f=CSpinEdit2->Value;
ind= GetFreqIndex(f);
dltPg=dPg[ind];
StF=CurrToStrF(f,ffFixed,0);
SPg=Edit39->Text;
Pg=StrToInt(SPg)-dltPg;
SPg=CurrToStrF(Pg,ffFixed,2);
CorrStrGen(SPg);

KodeAtt=(CheckBox73->Checked)|( (CheckBox74->Checked)<<1);
ShiftOutPKC(0,0,KodeAtt);//Подключить вход КС ПКУ и установить аттенюаторы
WrGenE825(StF,SPg);
for(;;)
    {
      Application->ProcessMessages();
     if(PStop==true)  break;
     if((Pmm=StepRdPow())==0){
         OfGenE825();
           return false; }
       Patt=Pmm-dPm[ind];
     StaticText16->Caption=CurrToStrF(Patt,ffFixed,2);
    }
OfGenE825();
return true;
}


void __fastcall TForm1::StopPKU_PKC(TObject *Sender)
{
PStop=true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1:: StartCheckComparVch(TObject *Sender)
{
AnsiString St;
float Pg=-10.0;
Button69->Enabled=false; //CompKC
Button70->Enabled=false; // out
Button67->Enabled=false;  // Att
Button68->Enabled=false;  //VCH
Button71->Enabled=true; //stop

if(ChkDevs==true)
 {
if(!ShiftOutPKC(0,0)) return; //отключить все выходы ПКС-52

St="Подключить выход генератора на вход КС ПКУ";
if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK){
Edit39->Text=CurrToStrF(Pg,ffFixed,2);
if(WorkCompVch()==false)
Application->MessageBox("Ошибка  компаратора ВЧ", "", MB_ICONERROR|MB_OK); }
}//ChkDevs
Button69->Enabled=true; //CompKC
Button70->Enabled=true; // out
Button67->Enabled=true;  // Att
Button68->Enabled=true;  //VCH
Button71->Enabled=false; //stop
}



bool TForm1::WorkCompVch(void)
{
AnsiString StF;
 float Pg,dltPg,dltPm;
 float Pmm,f ;
 float Patt;    //мошность, считываемая с измерителя мощности с учетом калибр
 AnsiString SPg;
 Byte KodeAtt;
 float per=100.0;
 float rang=50.0;
 Byte dan[3];
memset(dan,0,3);
 int ind; //индекс доступа к массивам калибровки

  PStop=false;

f=CSpinEdit2->Value;
ind= GetFreqIndex(f);
dltPg=dPg[ind];
StF=CurrToStrF(f,ffFixed,0);
SPg=Edit39->Text;
Pg=StrToInt(SPg)-dltPg;
SPg=CurrToStrF(Pg,ffFixed,2);
CorrStrGen(SPg);

ShiftOutPKC(0,0);//Подключить вход КС ПКУ и установить аттенюаторы
ModGenE825( per,  rang );//модуляция генератора
WrGenE825(StF,SPg);
for(;;)
    {
      Application->ProcessMessages();
     if(PStop==true)  break;
    if(!PaketFZD(0x1,dan))return false;
Byte PVCH=(dan[0]&0x10)>>4;
StaticText15->Caption=IntToStr(PVCH);
Application->ProcessMessages();
if(PStop==true) break;
     StaticText13->Caption=IntToStr(PVCH);
    }
OfGenE825();
return true;
}


void __fastcall TForm1::CheckCompKC(TObject *Sender)
{
float Pg;
AnsiString St;
Button69->Enabled=false; //CompKC
Button70->Enabled=false; // out
Button67->Enabled=false;  // Att
Button68->Enabled=false;  //VCH
Button71->Enabled=true; //stop
if(ChkDevs==true)
 {
St="Подключить выход генератора на вход КС ПКУ";
if(Application->MessageBox(St.c_str(), "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK){
Edit39->Text=CurrToStrF(Pg,ffFixed,2);
if(WorkCompKC()==false)
Application->MessageBox("Ошибка значения компаратора КС", "", MB_ICONERROR|MB_OK);
}
}//ChkDevs
Button69->Enabled=true; //CompKC
Button70->Enabled=true; // out
Button67->Enabled=true;  // Att
Button68->Enabled=true;  //VCH
Button71->Enabled=false; //stop
}
//---------------------------------------------------------------------------


bool TForm1::WorkCompKC(void)
{
int ofs;
 float Pg,dltPg;
 float P,Pacc;
 AnsiString SPg;

 int ind,colSints; //индекс доступа к массивам калибровки
// int Fbeg,Flb,indIn;
 float per=100.0;
 float rang=50.0;
  PStop=false;
Byte dan[3];
memset(dan,0,3);

SPg=Edit39->Text;
Pg=StrToInt(SPg);
int f=CSpinEdit2->Value;
AnsiString Sf= IntToStr(f);
Byte Kode=StrToInt(Edit40->Text);

//сигнал с генератора отключен
OfGenE825();

if(!PaketP_WRD( Kode,DA_PPA52P_UPPU)) return false ;//DA_PPA52L_UPPU=6
ModGenE825( per,  rang );//модуляция генератора
WrGenE825(Sf,SPg);
for(;;)
{
if(!PaketFZD(0x1,dan))return false;
Byte PKS=(dan[0]&0x20)>>5;
StaticText15->Caption=IntToStr(PKS);
Application->ProcessMessages();
if(PStop==true) break;
}
OfGenE825();
return true ;

}

void __fastcall TForm1::Fit_Att_Comp(TObject *Sender)
{
ShowPanel(Panel15);
FileCalbGnPm();
Screen->Cursor = crHourGlass;
if(Packet_P_CO()==true)
 MyTimer(10000);
else
 Application->MessageBox("Ошибка при переходе в штатный режим", "Внимание!", MB_ICONERROR|MB_OK) ;
 Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------





















void __fastcall TForm1::PZU_WRP(TObject *Sender)
{
/*AnsiString StDir=ExtractFilePath(Application->ExeName);
AnsiString fname=StDir+"pku3_1_rom_wr.dat";

 const u16 page_sz = 64;
//             addr_h =0x1ffe;
   u16 addr = 0;
const   int sz_rd=1024;
const   int sz_wr=8192;
  u8 buf[sz_rd];
  u8 buff_wr[sz_wr];             //  u8 buff_wr[AT256_ROM_SIZE];

memset(buf, 0, AT256_ROM_SIZE);
   //u16 crc = 0;
   if (!RdFile_PZU(fname.c_str(), buf, sz)) //чтение из файла  1024 байта
      return;

   Screen->Cursor = crHourGlass;
   Application->ProcessMessages();

 memcpy(buff_wr, buf, sz);

PaketP_WRP( buf_dan,64,DA_PPA52P_UPPU); */




//   Screen->Cursor = crDefault;
   /*crc = GetCrcSku6Pku3Rom(buf, AT256_ROM_SIZE);
   pck_uppu->buf[1] = (crc << 24) | addr_h;
   if (MsgErr(pck_uppu->SendPultCmd(8, 0x1e, DA_PPA52P_UPPU, 20)))
      return;
   if (pck_uppu->buf[1] & 1)
      MsgErr("Ошибка записи контрольной суммы ПЗУ");*/
}
//---------------------------------------------------------------------------
bool  TForm1::RdFile_PZU(char* file, u8 *buf,  int buf_sz)
{
/*   FILE *f = fopen(file, "rb");
   if (!f){
      MsgErr("Не могу открыть файл " + AnsiString(file)+ " на чтение!");
      return false;
   }
   long int fsize = FileSize(f);
   if (fsize > buf_sz){
      MsgErr("Не верен размер файла "+ AnsiString(file) + "!");
      fclose(f);
      return false;
   }
   int rd = fread(buf, 1, fsize, f);
   if (rd != fsize){
      MsgErr("Прочитано " + IntToStr(rd) + " данных, вместо "+IntToStr(fsize) + "!");
      fclose(f);
      return false;
   }
   fclose(f);*/
   return true;
}


 void __fastcall TForm1::ClosePanel15(TObject *Sender)
{
Panel15->Visible =false;
}

void __fastcall TForm1::onChenSpEd2(TObject *Sender)
{
AnsiString s = IntToStr(CSpinEdit2->Value);
      if ((s[s.Length() - 1] == '3') && (s[s.Length()] == '8'))
         CSpinEdit2->Value -= 12;
      else if ((s[s.Length() - 1] == '6') && (s[s.Length()] == '2'))
         CSpinEdit2->Value += 12;
}
//---------------------------------------------------------------------------


