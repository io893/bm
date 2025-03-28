//---------------------------------------------------------------------------


#pragma hdrstop

#include "ARM.h"
#include "math.h"
#include "algorithm.h"
#include <math.hpp>
//---------------------------------------------------------------------------

#pragma package(smart_init)

bool StopTrack=false;
bool Saved=false;

void __fastcall TForm1::onMenuCalibr(TObject *Sender)
{
/*Panel1->Visible=true;
Panel2->Visible=false;
Panel_53->Visible=false;
Panel10->Visible=false;
PanelPotent->Visible=false;
PanelOUTPow->Visible=false;

P_1->Visible=false;   */
ShowPanel(Panel1);
InitModClb();

}

void __fastcall TForm1::ChnLitera(TObject *Sender)
{
 InitModClb();
}
//---------------------------------------------------------------------------

void TForm1::StartTrack(void)
{
 int pos,i;
 int EndPnt;
int f,F;
double integ;
double frack;
 float Pg;
 float P;
 float dP;    //мошность, считываемая с измерителя мощности с учетом калибр
 AnsiString SPg;
 dl=true;
 StopTrack=false;

 Series5->Clear();
 if(RadioGroup10->ItemIndex==0)  //литера 2
{
//     BgPnt=0;
     F=Fl;
}
else {
      if(RadioGroup10->ItemIndex==1)  //литера 53
//      BgPnt=64;
      F=Fb;
     }
EndPnt=TrackBar2->Max;
 SPg=StaticText1->Caption;   //мощность генератора
 Pg=StrToInt(SPg);
 TrackBar2->Position=EndPnt/2;
 while(StopTrack==false)
 {
   pos=TrackBar2->Position;
   modf(pos/8, &integ);
   frack=pos-integ*8;
   f=integ*500+frack*64+F+26;
  WrGenE825(IntToStr(f),SPg);
   Sleep(100);
if((P=StepRdPow())==0)
  break;
  else {
        dP=P-Pg;
        OutChart5(pos,dP);
       }
  Application->ProcessMessages();
 } //Stop
   OfGenE825();
}

void __fastcall TForm1::ManualCallbr(TObject *Sender)
{
 int pos;
 int BgPnt,EndPnt,n;
int f;
double integ;
double frack;
 float Pg,dltPg,dltPm;
 float Pmm;
 float P;    //мошность, считываемая с измерителя мощности с учетом калибр
 AnsiString SPg,S;
 dl=true;
 StopTrack=false;
 InitModClb();
 SpeedButton8->Enabled=false;
 SpeedButton9->Enabled=true;

if(ChkDevs==true)
{
 StartTrack();
}
 else
 {
if(FindDevises()==true)
 {
 if(ChekDev()==true)
 {
 StartTrack();
 }
 }    //FindDevises()
 }
}
//---------------------------------------------------------------------------


void TForm1::InitModClb(void)
{
Button3->Enabled=false;  // сохранить
Button8->Enabled=false;  //  погрешность
Button1->Enabled=false;  //  стоп
Button2->Enabled=true;   // калибровка
SpeedButton9->Enabled=false;
SpeedButton8->Enabled=true;

int colSints;

 Series1->Clear();
 Series2->Clear();
 if(RadioGroup4->ItemIndex==0)   //режим передатчика
 {
  if(ComboBox4->ItemIndex==0) //кабель генератора
  {
  StaticText1->Caption="-10";
  Chart1->LeftAxis->Maximum=2 ;
  Chart1->LeftAxis->Minimum=-16 ;
  }
   else                            // кабель измерителя мощности
   {
   StaticText1->Caption="0";
   Chart1->LeftAxis->Minimum=-50 ;
   Chart1->LeftAxis->Maximum=-30 ;
  }
 }
 else if(RadioGroup4->ItemIndex==1) //режим СОВЧ
 {
  StaticText1->Caption="-50";
 }

if ( RadioGroup10->ItemIndex==0)  //литера 2
   {
    colSints=(Fb-Fl)/500;
   }
 else  if ( RadioGroup10->ItemIndex==1)  //литера 53
    {
       colSints=(Fh-Fb)/500;
    }
 Chart1->BottomAxis->Maximum=8*colSints-1;
 TrackBar2->Max=8*colSints-1;
 TrackBar2->Min=0;
}

void __fastcall TForm1::ChengeDistCalb(TObject *Sender)
{
 InitModClb();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::onCalibrate(TObject *Sender)
{
 AnsiString Stm;
 InitModClb();
 Button3->Enabled=false;
 Button8->Enabled=false;
 Button2->Enabled=false;
 SpeedButton9->Enabled=false;
 SpeedButton8->Enabled=false;

 PStop=false;
 Saved=false;
 dl=true;

 Pwr.clear();
 Series1->Clear();
 Series2->Clear();
 Series5->Clear();
 StopTrack=true;

if(ComboBox4->ItemIndex==0)
Stm="Подключить измерительные приборы к компьютеру,\n а калибруемый кабель к измерительным приборам";
else
Stm="Подключить измерительные приборы к компьютеру,\n а калибруемый кабель с аттенюатором (30дБ)к измерительным приборам";

if(Application->MessageBox(Stm.c_str(),"Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==ID_OK)
{

if(ChkDevs==true)
{
 Calibrate();
}
 else
 {
if(FindDevises()==true)
 {
 if(ChekDev()==true)
 {
 Calibrate();
 }

 }    //FindDevises()
 }//else
}//OK_CANSEL
 SpeedButton9->Enabled=true;
 SpeedButton8->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::onSaveCalibrate(TObject *Sender)
{
int n;
AnsiString MyFileName;
unsigned int i;
int cntbyte ;

Dbl.insert(Dbl.begin(),224,0);

if(RadioGroup4->ItemIndex==0)
{
 if(ComboBox4->ItemIndex==0)
 MyFileName="W_Gen_Prd.clb";
 else
 MyFileName="W_IM_Prd.clb";
}
 else if(RadioGroup4->ItemIndex==1) //режим СОВЧ
 {
  if(ComboBox4->ItemIndex==0)
 MyFileName="W_Gen_Prm.clb";
 else
 MyFileName="W_IM_Prm.clb";
 }
     if(FileExists(MyFileName) )
     {
     if(Application->MessageBox("Файл уже существует. Переписать?","Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)!=ID_OK)
      goto M1;
      else
       ReadFileCalb(MyFileName);
     }
      Myfile=new TFileStream(MyFileName,fmCreate|fmOpenWrite);

 if(Myfile)
  {
   if(RadioGroup10->ItemIndex==0)
   {
    for(i=0;i<64;i++)                  //64 точки частоты
   Dbl.erase(Dbl.begin());
  for(i=0,n=63;i<64;i++,n--)
   Dbl.insert(Dbl.begin(),Pwr[n]);
   }
  else if(RadioGroup10->ItemIndex==1)
  {
   for(i=0;i<160;i++)
   Dbl.pop_back();
  for(i=0;i<160;i++)
  Dbl.push_back(Pwr[i]);
  }
    n= Dbl.size();
    for(i=0;i<Dbl.size();i++)
    Myfile->WriteBuffer(&Dbl[i] ,sizeof(float));

   delete(Myfile);
   Myfile=NULL;
   Saved=true;
  }
M1:;
 Dbl.clear();
}

void TForm1::Calibrate(void)
{
unsigned int i,j,cnt=0;
 int Fbeg,f,Flb;
 AnsiString SPg;
 float mx,mn;
float Pg,dP,P;
unsigned colSints;
    SPg=Trim(StaticText1->Caption);   //мощность генератора
    Pg=StrToFloat(SPg);
Pwr.clear();


if(RadioGroup10->ItemIndex==0)     //"2";
{
 colSints=(Fb-Fl)/500;
 Flb=Fl;
}
else                             //"53"
{
 colSints=(Fh-Fb)/500;
 Flb=Fb;
}

 CheckCalbPm();
 InitPowMtr();
 InitE825(SPg);
    Button1->Enabled=true; //  стоп
 for(j=0;j<colSints;j++)    // 28 синтезаторов по 500МГц
 {
  Fbeg=Flb+26+500*j;
  for(i=0;i<8;i++)    //8 точек частоты в каждом синтезаторе
  {
                //точки частоты
   f=Fbeg+i*64;    // шаг частоты 64 МГц
    if((PStop==false) )
      {
       WrGenE825(IntToStr(f),Pg);
       Sleep(100);
      if((P=StepRdPow())==0)
      {
      Pwr.clear();
      goto M1;
      }
       dP=P-Pg;
       Pwr.insert(Pwr.end(),dP);
       OutChart(cnt,dP);
       cnt++;
       Application->ProcessMessages();
       }
      else
       {
        Pwr.clear();
        break;
       }
  }  //for i
 }  //for j

M1:   OfGenE825();
if(Pwr.size()!=0)
  {
   Beep();
   Application->MessageBox("Калибровка завершена", "Внимание!", MB_ICONINFORMATION|MB_OK);

   mn = *min_element(Pwr.begin(), Pwr.end()) ;
   mx = *max_element(Pwr.begin(), Pwr.end()) ;

  Label1->Caption="Pmin="+CurrToStrF(mx,ffFixed,2); //наоборот верно!
  Label2->Caption="Pmax="+CurrToStrF(mn,ffFixed,2);
  Label3->Caption="dP=" + CurrToStrF(fabs(fabs(mx)-fabs(mn)),ffFixed,2);
if(Pwr.size()!=0)
{
  Button8->Enabled=true; //  оценка
  Button3->Enabled=true; // сохранить
}
  }
  Button2->Enabled=true; //калибровка
  Button1->Enabled=false; //  стоп
  }

void __fastcall TForm1::onOutCalibrate(TObject *Sender)
{
//
PStop=true;
StopTrack=true;
Panel1->Visible=false;
if(viG!=0)
OfGenE825();

}


void __fastcall TForm1::EstimErr(TObject *Sender)
{

 Button2->Enabled=false;          // калибровка
 Button3->Enabled=false;          // оценка
 Button1->Enabled=true;          //  стоп
 Button8->Enabled=false;        //  оценка
 PStop=false;
 StopTrack=true;



  Chart1->LeftAxis->Maximum=2 ;
  Chart1->LeftAxis->Minimum=-10 ;
  Series1->Clear();
  if(ComboBox4->ItemIndex==1)
  StaticText1->Caption ="-40" ;

if(ChkDevs==true)
{
  Estim();
}
 else
 {
if(FindDevises()==true)
 {
 if(ChekDev()==true)
     Estim();
 }
 }
M1: Button2->Enabled=true;    // калибровка
 Button1->Enabled=false;   //стоп
 Button8->Enabled=true;   // оценка
 Button3->Enabled=true;   // сохранить
}
//---------------------------------------------------------------------------


void TForm1::Estim(void)
{
 AnsiString SPg,S;
// AnsiString MyFileName;
int f;
unsigned int i,j;
float Pg,P,dltPg;
float Emin,Emax,dE;
int cnt;
int Fbeg,Flb ;
unsigned colSints;
cnt=0;
vector< float > EsmErr;

if(RadioGroup10->ItemIndex==0)     //"2";
{
 colSints=(Fb-Fl)/500;
 Flb=Fl;

}
else                             //"53"
{
 colSints=(Fh-Fb)/500;
 Flb=Fb;
// cnt=64;
// point=0;
}

Chart1->BottomAxis->Maximum=8*colSints;        //

    Button1->Enabled=true; //  стоп

Series2->Clear();
SPg=Trim(StaticText1->Caption);   //мощность генератора
 Pg=StrToFloat(SPg);

 InitPowMtr();
 InitE825(SPg);
 Button1->Enabled=true; //  стоп

for(j=0;j<colSints;j++)    //colSints   синтезаторов по 500МГц
 {
  Fbeg=Flb+26+500*j;
  for(i=0;i<8;i++)    //8 точек частоты в каждом синтезаторе
  {
                //точки частоты
   f=Fbeg+i*64;    // шаг частоты 64 МГц
    if((PStop==false) )
      {
       dltPg=Pwr[cnt];
       SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
       CorrStrGen(SPg);
       WrGenE825(IntToStr(f),SPg);

     if((P=StepRdPow())==0)
        goto M1;


       EsmErr.insert(EsmErr.end(),Pg-P);
       OutChart1(cnt,Pg-P);
       cnt++;
//       point++;
       Application->ProcessMessages();
       }
      else
        break;


  }  //for i
 }  //for j

M1:   OfGenE825();
  if(EsmErr.size()!=0)
  {
   Emin = *min_element(EsmErr.begin(), EsmErr.end()) ;
   Emax = *max_element(EsmErr.begin(), EsmErr.end()) ;
   dE=Emax-Emin;
   Label1->Caption="Pmin="+CurrToStrF(fabs(Emin),ffFixed,2);
   Label2->Caption="Pmax="+CurrToStrF(fabs(Emax),ffFixed,2);
   Label3->Caption="dP=" + CurrToStrF(fabs(dE),ffFixed,2);
  }

}

void TForm1::OutChart(int F,float P)
{
 Series1->AddXY(F,P);
}

void TForm1::OutChart1(int F,float P)
{
 Series2->AddXY(F,P);
}

void TForm1::OutChart5(int pos,float P)
{
 Series5->AddXY(pos,P);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::onStopCalibrate(TObject *Sender)
{
SpeedButton9->Enabled=false;
SpeedButton8->Enabled=true;

PStop=true;
}
//---------------------------------------------------------------------------
 void __fastcall TForm1::CalibratePm(TObject *Sender)
{
if(ChkDevs==true)
  CalPm();
 else
 {
if(FindDevises()==true)
 {
 if(ChekDev()==true)
   CalPm();

 }    //FindDevises()
 }
}
//---------------------------------------------------------------------------

void TForm1::ReadFileCalb(AnsiString MyFileName)
{
 int n,i;
 float* buff;
 Dbl.clear();
 Myfile=new TFileStream(MyFileName,fmOpenRead);
       if(Myfile)
       {
        Myfile->Position=0;
        n=(Myfile->Size)/sizeof(float);   //читать данные калибровки генератора
        buff=new float[n];
        Myfile->ReadBuffer(buff,n*sizeof(float));
        for(i=0;i<n ;i++)
         Dbl.insert(Dbl.end(),buff[i]);

         delete(Myfile);
         Myfile=NULL;
         delete[] buff;
      }
}


void __fastcall TForm1::StopManualCall(TObject *Sender)
{
StopTrack=true;
SpeedButton8->Enabled=true;
SpeedButton9->Enabled=false;
Series5->Clear();
}
//---------------------------------------------------------------------------

//Калибровка БМК

void __fastcall TForm1::zButton134Click(TObject *Sender)
{
 // калибровка автоматически
   double Val,// Min = INIT_VAL, Max = -INIT_VAL,
			 Level = StrToFloat(zEdit50->Text)/*,R = StrToFloat(Edit51->Text)*/;
	extern int OLD_POZ;
	extern int STATE_POZ;

	int freq_index_my=GetFreqIndex(zCSpinEdit23->Value),
		ind=0,
		dS = elCSpinEdit21->Value*ONE_DEG,
		dS_90=ONE_DEG*(90-OfSetSec),
		steps_begin;
	int f,Fbeg;
	AnsiString St,SPg;
	PStop=false;
	int colSints=(Fh-Fl)/500;
	int kp,i,j;
	char *vel[]={"SD700*"};
          InitGrid_klb();
         // zLabel158->Font->Color = clGren;
          zLabel158->Caption=" ";
          zLabel158->Visible=false;

	zButton134->Enabled=false;
	zButton138->Enabled=false;
	zButton139->Enabled=false;
	zButton142->Enabled=false;
	HaltPos->Enabled=true;
	bool  smsd_prg_loaded = false;
	PStop= false;
	PM_clb.clear();
	zChart11->Series[0]->Clear();
	zChart11->Series[1]->Clear();
	StaticText4->Caption=IntToStr(0);
	StaticText3->Caption="";
	zChart11->BottomAxis->SetMinMax(0,180);


	//----------------------------------------------------------
     for(j=0;j<colSints;j++)    // j- синтезаторов по 500МГц
	  {
        Fbeg=Fl+26+500*j;
        for(i=0;i<8;i++)    //8 точек частоты в каждом синтезаторе
		  {
          f=Fbeg+i*64;    // шаг частоты 64 МГц
          ind=j*8+i;

			 SPg= CurrToStrF(Level-dPg_sign[ind],ffFixed,2);

			 St=IntToStr(f);
			 WrGenE825(St,SPg);


			 StaticText3->Caption=CurrToStrF(f,ffFixed,1);
			 StaticText4->Repaint();
			 StaticText3->Repaint();
 //----------------------------------------------------------
			 Val = StepRdPow() - dPm_vch[ind]; //с калибровкой
			 PM_clb.insert(PM_clb.end(),Val);   // всего 20384 = 224 частотные точки *91 позицию

                /* вывод графика, выбранной для примера частоты  */
			 if(freq_index_my==ind)
				zChart11->Series[0]->AddXY((90),PM_clb[ind]); /* индекс частоты, взятой с экрана */
			 zChart11-> Series[0]->Repaint();
			 Application->ProcessMessages();
			 if (PStop==true)
				break;
		  }//i
		  if (PStop==true)
		  break;
	  } //j
     
	  //kp=kp+1; /* переход к следующей позиции */
	  OfGenE825();
	if(!PStop){
		OutGrid_klb(); /* вывод в таблицу */
	}
	zButton134->Enabled=true;
	zButton138->Enabled=true;
	zButton139->Enabled=true;
	zButton142->Enabled=true;
	HaltPos->Enabled=false;
}
 void TForm1::saveFileGainFactor(){
	 extern double K_usil_prd1[224];
	SetCurrentDir(ExtractFilePath(Application->ExeName));
	string path = "ku";
    ofstream fout;
    fout.open(path.c_str());
	// ??????? ??? ??????? ????
	if (!fout.is_open())//
	{
		zLabel158->Caption = "Error_open";  //?????? ???????? ?????
	}
	else
	{
        for(int i=0; i<=224; i++){
				fout << K_usil_prd1[i]<<endl;
        }

	}
	fout.close();
};
void TForm1::downloadFileGainFactor()
{
    extern double K_usil_prd1[224];
	char path[10] = "ku";
	ifstream fin;
	fin.open(path); /* ,ofstream::app ?????? ???????? ?????? open ??? ?????????? ?????? ? ????? ?????*/
	if (!fin.is_open()) // ???????? ?????? ?? ????
	{
		if (Application->MessageBox("Нет файла калибровки БМК! Выполнить калибровку БМК?","Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==ID_OK){
			N10->Click();
		};
	}
	else
	{
		char ch;
		string str;
        for(int i=0; i<=224; i++){
				getline(fin,str);
			 K_usil_prd1[i] =  StrToFloat(str.c_str());
		  }

	}
	fin.close();
}
//---------------------------------------------------------------------------
void TForm1::OutGrid_klb(void)
{
	int i,j,colSints=(Fh-Fl)/500;
	double Pmax, Pvy,p;
	//unsigned int Ngrad,Indgrad;
	int Ngrad;//,Indgrad;
	int beg_pos, end_pos;
	unsigned int ind;
	//int Degmax;
	double f,Fbeg;
	double lamd;
	double Level,R;

	extern double K_usil_prd1[224];

	int StepDeg=elCSpinEdit21->Value;  /* по умолчанию 3 град*/
	double integ,frack;
	double dP_zad,dP_izm,dPmax;

	Ngrad=ceil(30/StepDeg)+1;
	Level = StrToFloat(zEdit50->Text);
	R = StrToFloat(zEdit51->Text);
	dP_zad = StrToInt(zEdit57->Text);
	zLabel158->Font->Color = clBlack;
	zLabel158->Caption=" ";
	zLabel158->Repaint();
	for(j=0;j<colSints;j++)    // j- синтезаторов по 500МГц
	{
		Fbeg=Fl+26+500*j;
		for(i=0;i<8;i++)    //8 точек частоты в каждом синтезаторе
		{
			f=Fbeg+i*64;    // шаг частоты 64 МГц
			ind= j*8+i;
			zStringGrid6->Cells[0][ind+1]=CurrToStr(f);
		}
   }
	dPmax=-10;
	for(j=0;j<224;j++)
	{
		Pmax=-INIT_VAL;
		p=PM_clb[j] ;
		if(p>Pmax)
		{
			Pmax=p;
			// Degmax=i*StepDeg;
			ind=j;
		}
		modf(ind/8, &integ);
		frack=ind-integ*8;
		f=integ*500+frack*64+26+4000;
		lamd=300/f;
		frack = 20*log10(lamd/(4*M_PI*R));
		Pvy = -13.78+log10(f) + log10(R) + (Level-Pmax)/2;
		K_usil_prd1[ind] = (Pmax-Level- frack)/2;
		zStringGrid6->Cells[1][j+1]=CurrToStrF(Pmax,ffFixed,2);
	  //	zStringGrid6->Cells[2][j+1]=CurrToStrF(Pvy,ffFixed,2);
		zStringGrid6->Cells[3][j+1]=CurrToStrF(K_usil_prd1[ind],ffFixed,2);
		dP_izm=fabs(Pmax-Pvy);
	//if(dP_izm>dPmax){dPmax=dP_izm;}
	} //j
	if(dP_izm<=dP_zad) {
		zLabel158->Font->Color = clGreen;
		zLabel158->Caption="БМК исправна!     dPизмер. max = "+CurrToStrF(dP_izm,ffFixed,2);

	}
	else{
       zLabel158->Font->Color = clRed;
		 zLabel158->Caption="БМК неисправна!      dPизмер. max = "+CurrToStrF(dP_izm,ffFixed,2);
	}
	saveFileGainFactor();
	zLabel158->Visible = true;

}

void __fastcall TForm1::SetZero(void)
{
// Поиск нуля--
extern int STATE_POZ;
if (!SearchZero(600,false))//поиск 0
      return;
   Sleep(100);
  // SmsdWrCmd("ST1*"); //старт
  if (!SmsdWrCmd_start("ST1*"))
              { //старт
              ShowMessage("Ошибка получения ответа окончания программы (нет E14)");
              return;
               }
  MyTimer(1000); //ждем пока штанга успокоится

  STATE_POZ=OfSetSec; /* начальная позиция  */
  StaticText4->Caption=IntToStr(STATE_POZ);
  StaticText2->Caption=IntToStr(STATE_POZ);

//  zEdit55->Repaint();
//  zEdit56->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::HaltPosClick(TObject *Sender)
{
 PStop = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::zButton138Click(TObject *Sender)
{
extern int OLD_POZ;
extern int STATE_POZ;
double go_pos;//
bool rev=false;
double dpos;

zButton139->Enabled=false;
zButton142->Enabled=false;
zButton134->Enabled=false;
HaltPos->Enabled=false;

go_pos=zCSpinEdit24->Value;

if (STATE_POZ==-1)  //позиция не определена в системе поворотника
SetZero();// Установка в 0

double dSB=go_pos-STATE_POZ;
if(dSB!=0)
{
if(dSB<0)rev=!rev;
dpos=dSB*ONE_DEG;

  if (!WrCmdsAndMove(dpos,rev))
              return;
  if (!SmsdWrCmd_start("ST1*")) //старт
        return;
STATE_POZ=go_pos;

}
StaticText2->Caption=IntToStr(STATE_POZ);
 OLD_POZ= STATE_POZ*ONE_DEG;
  ShowMessage("Движение закончено");
zButton139->Enabled=true;
zButton142->Enabled=true;
zButton134->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::zButton139Click(TObject *Sender)
{
// калибровка в выбранной позиции на заданной частоте

 extern int STATE_POZ;
extern double K_usil_prd1[224];
    double Val,Puzm;// Min = INIT_VAL, Max = -INIT_VAL,
int  Freq = zCSpinEdit23->Value;
double   Level, Pmm, F,R;
      int freq_index = GetFreqIndex(zCSpinEdit23->Value);
    double lamd;
R = StrToFloat(zEdit51->Text);
     StaticText5->Caption=" ";
     StaticText6->Caption=" ";
     zLabel158->Caption=" ";
PStop=false;
zButton134->Enabled=false;
zButton138->Enabled=false;
zButton139->Enabled=false;
zButton142->Enabled=false;
HaltPos->Enabled=true;


AnsiString Spg= Trim(zEdit50->Text);

InitPowMtr();
 InitE825(Spg);
 MyTimer(10);

Level=StrToFloat(Spg)-dPg_sign[freq_index];
WrGenE825(IntToStr(Freq),CurrToStrF(Level,ffFixed,2));

 zChart11->Series[0]->Clear();
 zChart11->Series[1]->Clear();

    while(PStop==false)
     {
     MyTimer(50);
      if((Pmm=StepRdPow())==0)
            break;

     Val =Pmm - dPm_vch[freq_index]; //с калибровкой
     zChart11->Series[0]->AddXY(STATE_POZ, Val);

       lamd=3*pow(10,2)/Freq;

  Puzm=StrToFloat(Spg)+K_usil_prd1[freq_index]+K_usil_prd1[freq_index]+10*log10((lamd*lamd)/(16*M_PI*M_PI*R*R));

      StaticText5->Caption=FloatToStrF(Val, ffFixed, 4, 2);
      StaticText6->Caption=FloatToStrF(Puzm, ffFixed, 4, 2);


      Application->ProcessMessages();
  }  // end while
 OfGenE825();
 zButton134->Enabled=true;
zButton138->Enabled=true;
zButton139->Enabled=true;
zButton142->Enabled=true;
HaltPos->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::zButton142Click(TObject *Sender)
{
//Калибровка ручная
extern int OLD_POZ ;
extern int STATE_POZ ;
int steps_cnt ;
PStop=false;
extern double K_usil_prd1[224];
double Val, Min = INIT_VAL, Max = -INIT_VAL;
int    Freq = zCSpinEdit23->Value;
double          Level = StrToFloat(zEdit50->Text),
          R = StrToFloat(zEdit51->Text);
int     freq_index = GetFreqIndex(zCSpinEdit23->Value),
        dS = elCSpinEdit21->Value*ONE_DEG,
        steps_begin=0,
        steps_max = ONE_DEG*180;
 double lamd,F,Pmm;
double Pvy;
bool max_fnd;
    zLabel158->Caption=" ";
zButton134->Enabled=false;
zButton138->Enabled=false;
zButton139->Enabled=false;
zButton142->Enabled=false;
HaltPos->Enabled=true;

AnsiString Spg=Trim(zEdit50->Text);

zChart11->Series[0]->Clear();
zChart11->Series[1]->Clear();

 Search_Zero_my(false);
STATE_POZ=OfSetSec;
 StaticText2->Caption=IntToStr(STATE_POZ);

   StaticText5->Caption="";
   StaticText6->Caption ="";

        steps_begin=ONE_DEG*OfSetSec;
        steps_max=ONE_DEG*(180-OfSetSec);
//        zChart11->BottomAxis->SetMinMax(0,180);

InitPowMtr();
 InitE825(Spg);
 MyTimer(10);

 Spg=CurrToStrF(Level-dPg_sign[freq_index],ffFixed,2);//,ffFixed,2);
AnsiString SFreq=IntToStr(Freq);
F=StrToInt(SFreq);
WrGenE825(SFreq,Spg);

bool smsd_prg_loaded = false;

   for ( steps_cnt = steps_begin; steps_cnt <= steps_max; steps_cnt += dS){


MyTimer(50);
      if((Pmm=StepRdPow())==0)
           break;

     Val = Pmm-dPm_vch[freq_index]; //с калибровкой

      Min = min(Val, Min); //мин. Кп
      Max = max(Val, Max); //макс. Кп
      if (Val == Max){
         if (!max_fnd)
            max_fnd = true;
// int        max_steps = steps_cnt;
      }

     StaticText5->Caption=CurrToStrF(Max,ffFixed,2);
     zChart11->Series[0]->AddXY((int)(steps_cnt / ONE_DEG), Val);
     StaticText2->Caption=IntToStr(steps_cnt / ONE_DEG);
     zChart11->Repaint();

OfGenE825();
      if (steps_cnt >= steps_max)
         break;

      if (!smsd_prg_loaded){
         if (!WrCmdsAndMove(dS,false))
                     return;

         MyTimer(50);
         smsd_prg_loaded = true;
      }

        if (!SmsdWrCmd_start("ST1*")) //старт  //  ждем ответа от контроллера
                  return;

    MyTimer(100); //ждем пока штанга успокоится
    STATE_POZ=( steps_cnt+dS )/ONE_DEG;
   WrGenE825(SFreq,Spg);
      Application->ProcessMessages();
      if (PStop==true)
         break;
   }

   if (PStop==true){
     HaltPosClick(Sender);

   }

OfGenE825();
    OLD_POZ=STATE_POZ*ONE_DEG; /* текущая позиция */
//    StaticText2->Caption=IntToStr(STATE_POZ);
   /* вычисления мощности приемной антенны */

 lamd=3*pow(10,2)/F;

  Pvy=Level+K_usil_prd1[freq_index]+K_usil_prd1[freq_index]+10*log10((lamd*lamd)/(16*M_PI*M_PI*R*R)) ;
    StaticText6->Caption=CurrToStrF(Pvy,ffFixed,2);
       parking();
STATE_POZ=-1;
    StaticText2->Caption=IntToStr(STATE_POZ);
zButton134->Enabled=true;
zButton138->Enabled=true;
zButton139->Enabled=true;
zButton142->Enabled=true;
HaltPos->Enabled=false;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::zButton140Click(TObject *Sender)
{
  zChart11->Series[0]->Clear();
  zChart11->Series[1]->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClosePanel26(TObject *Sender)
{
Panel26->Visible=false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Calibr_BMK(TObject *Sender)
{
extern int STATE_POZ;
AnsiString StDir=ExtractFilePath(Application->ExeName);
AnsiString MyFileName=StDir+"bmk_sign.cbr";
dPg_sign.clear();

 ReadFileCabBMK (MyFileName,0);
dPm_vch.clear();
MyFileName=StDir+"bmk_vch.cbr";
 ReadFileCabBMK (MyFileName,1);

ShowPanel(Panel26);
zCSpinEdit24->MinValue=OfSetSec;
zCSpinEdit24->MaxValue=180-OfSetSec;
zCSpinEdit24->Value=OfSetSec;
StaticText4->Caption=IntToStr(STATE_POZ);
StaticText2->Caption=IntToStr(STATE_POZ);
HaltPos->Enabled=false;
InitGrid_klb();
}
//---------------------------------------------------------------------------

void  TForm1::ShowPanel(TPanel *Panel)
{
   TPanel *tmp;
   for (int i = 1; i < 32; i++){
      tmp = (TPanel*)(FindComponent("Panel" + IntToStr(i)));
      if (tmp)
         tmp->Visible = false;
	}
	 if(Panel!=NULL){
      if(Panel->Width<640){
         Form1->ClientWidth = 640;
         Panel->Left = (Form1->ClientWidth - Panel->Width)/2;
      }
      else{
        Panel->Left = 1;
        Form1->ClientWidth = Panel->Left + Panel->Width ;
        //Panel->Left = (Form1->ClientWidth - Panel->Width)/2;
     }
      Panel->Top = 38;
      Form1->ClientHeight = Panel->Top + Panel->Height;
      //Panel->Top = (Form1->ClientHeight - Panel->Height)/2;
      Panel->Visible = true;
	}


  // Form1->ClientWidth = Panel->Left + Panel->Width + 10;
 //  Form1->ClientHeight = Panel->Top + Panel->Height + 10;

	
}

void  TForm1::InitGrid_klb(void)
{
int i,j;
 AnsiString S  ;
//const char c= 0xb0;

for(i=0;i<4;i++)
 for(j=0;j<225;j++)
   zStringGrid6->Cells[i][j]="";

 zStringGrid6->Cells[0][0]="F ";
 zStringGrid6->Cells[1][0]="Pmax изм.";
 zStringGrid6->Cells[2][0]="Pmax выч.";
 zStringGrid6->Cells[3][0]="dP изм.";
 }

//------------------   калибровка кабелей БМК  --------------------------------
void __fastcall TForm1::Button129Click(TObject *Sender)
{

 if(ChkDevs==true){
   Calib2kabl();}

  else {
 if(FindDevises()==true)
  {
  if(ChekDev()==true){
    Calib2kabl();}

  }    //FindDevises()
 }//else
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
 PStop=true;
 Panel3->Visible=false;
}


void TForm1::Calib2kabl(void)
{
  //калибровка Кабелей БМК
//   ViStatus stat=0; // объявление переменной типа ViStatus
   int Level,i,j;
    double m_Pow;
    int Fbeg,f;
      float mx,mn;
      AnsiString s = "",SPg;
SPg=Trim(Edit21->Text);
Level=StrToFloat(SPg);

 Series0->Clear();
 LineSeries11->Clear();
  if(RadioButton44->Checked) dPg_sign.clear();
  if(RadioButton45->Checked) dPm_vch.clear();
   PStop=false;

 Button129->Enabled=false;
 Button130->Enabled=false;
 Button131->Enabled=false;
 Button136->Enabled=false;
 Button7->Enabled=true;

   InitPowMtr();
   InitE825(Edit21->Text);
int colSints=(Fh-Fl)/500;

   /* 224 частотные точки */
 for(j=0;j<colSints;j++)    //colSints   синтезаторов по 500МГц
 {
  Fbeg=Fl+26+500*j;
 for(i=0;i<8;i++)    //8 точек частоты в каждом синтезаторе
  {
   //точки частоты
  f=Fbeg+i*64;    // шаг частоты 64 МГц
   WrGenE825(IntToStr(f),Level);
    MyTimer(100);
     if((m_Pow=StepRdPow())==0)
          return;

     if(RadioButton44->Checked){
      dPg_sign.insert(dPg_sign.end(),m_Pow-Level);
        Chart2->Series[0]->AddXY(f,m_Pow-Level);}

     if(RadioButton45->Checked){
      dPm_vch.insert(dPm_vch.end(),m_Pow-Level);
        Chart2->Series[1]->AddXY(f,m_Pow-Level);}

        Application->ProcessMessages();
        if(PStop==true) goto end;
  }//i
} //j
  if(RadioButton44->Checked)
   {
   mn = *min_element(dPg_sign.begin(), dPg_sign.end()) ;
   mx = *max_element(dPg_sign.begin(), dPg_sign.end()) ;
   }
  if(RadioButton45->Checked)
   {
   mn = *min_element(dPm_vch.begin(), dPm_vch.end()) ;
   mx = *max_element(dPm_vch.begin(), dPm_vch.end()) ;
   }

  Label10->Caption="Pmin="+CurrToStrF(mx,ffFixed,2); //наоборот верно!
  Label12->Caption="Pmax="+CurrToStrF(mn,ffFixed,2);
  Label13->Caption="dP=" + CurrToStrF(fabs(fabs(mx)-fabs(mn)),ffFixed,2);

    end: OfGenE825();  ;
 Button129->Enabled=true;
 Button130->Enabled=true;
 Button131->Enabled=true;
 Button136->Enabled=true;
 Button7->Enabled=false;

    ShowMessage("Калибровка закончена\n");
}
//---------------------------------------------------------------------------
void  __fastcall TForm1::Button7Click(TObject *Sender)
{
PStop=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button136Click(TObject *Sender)
{
//сохранить калибровку кабелей БМК
AnsiString MyFileName,StDir;
unsigned int i;


StDir=ExtractFilePath(Application->ExeName);

if(RadioButton44->Checked)
 MyFileName=StDir+"bmk_sign.cbr";
 else
 MyFileName=StDir+"bmk_vch.cbr";

   if(FileExists(MyFileName) )
     {
     if(Application->MessageBox("Файл уже существует. Переписать?","Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)!=ID_OK)
      return;
     }
      Myfile=new TFileStream(MyFileName,fmCreate|fmOpenWrite);

 if(Myfile)
 {
  if(RadioButton44->Checked)
  {

    for(i=0;i<dPg_sign.size();i++)
    Myfile->WriteBuffer(&dPg_sign[i],sizeof(float));
   }
  else if(RadioButton45->Checked)
  {

    for(i=0;i<dPm_vch.size();i++)
    Myfile->WriteBuffer(&dPm_vch[i],sizeof(float));
  }

   delete(Myfile);
   Myfile=NULL;

 }
}
//---------------------------------------------------------------------------

bool TForm1::ReadFileCabBMK (AnsiString MyFileName,int ind)
{
int n,i;
 float* buff;
AnsiString s;
 if(FileExists(MyFileName)==true)
     {
      Myfile=new TFileStream(MyFileName,fmOpenRead);
       if(Myfile)
       {
        Myfile->Position=0;
        n=(Myfile->Size)/sizeof(float);   //читать данные калибровки генератора
        buff=new float[n];
        Myfile->ReadBuffer(buff,n*sizeof(float));
        for(i=0;i<n ;i++)
        {
         if(ind==0)
         dPg_sign.insert(dPg_sign.end(),buff[i]);
         else
         dPm_vch.insert(dPm_vch.end(),buff[i]);
        }

         delete(Myfile);
         Myfile=NULL;
         delete[] buff;
         return true;
       } //if MyFile
       else    //if MyFile
         {
          s="Не могу открыть файл "+MyFileName;
          Application->MessageBox(s.c_str(),"Ошибка открытия файла", MB_ICONERROR|MB_OK);
          return false;
         }
     } /* FileExists */
   else{
        s="Файл "+MyFileName+"не найден";
        Application->MessageBox(s.c_str(),"", MB_ICONERROR| MB_OK);
        return false;
      }
}

void __fastcall TForm1::Button130Click(TObject *Sender)
{
//загрузить калибровочный файл
 AnsiString MyFileName,StDir,s ;
 int index;
StDir=ExtractFilePath(Application->ExeName);
 if(RadioButton44->Checked)
{
 s="bmk_sign.cbr";
MyFileName=StDir+s;
dPg_sign.clear();
index=0;
}
else if(RadioButton45->Checked)
 {
  s="bmk_vch.cbr";
MyFileName=StDir+s;
  dPm_vch.clear();
index=1;
 }
ReadFileCabBMK( MyFileName,index);
BuildCalibrGraph_bmk(index);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BuildCalibrGraph_bmk(int index)
{
   double Fa, Fz , Step, /*Count = 0,*/
          pow = 0, Min = INIT_VAL, Max = -INIT_VAL;
  int i=0;
  AnsiString s = "";
   if(RadioButton44->Checked)index=0; //Сигн.
   if(RadioButton45->Checked)index=1; //ВЧ

      Chart2->Series[index]->Clear();

   Fa = 4026;;
   Step = 64;
     Fz=17974;
    i=0;
  for (double freq = Fa; freq <= Fz;freq += Step)
  {
      s = IntToStr(int(floor(freq)));
      if ((s[s.Length() - 1] == '3') && (s[s.Length()] == '8'))
         freq -= 12;
     // pow = ((Calibr*)(cb))->GetData(freq);
      if(RadioButton44->Checked) pow = dPg_sign[i];
      if(RadioButton45->Checked) pow = dPm_vch[i];
      Min = min(pow, Min);
      Max = max(pow, Max);
      Chart2->Series[index]->AddXY(freq, pow);
      i=i+1;
   }
 Label10->Caption="Pmin="+CurrToStrF(Min,ffFixed,2);
 Label12->Caption="Pmax="+CurrToStrF(Max,ffFixed,2);
 Label13->Caption="dP="+CurrToStrF(Max-Min,ffFixed,2);
}


void __fastcall TForm1::EstimBMKCab(TObject *Sender)
{
AnsiString SPg,S;

int f,n;
unsigned int i,j,ind;
float Pg,P,dltPg;
float Emin,Emax,dE;
int Fbeg,Flb ;
unsigned colSints;

vector< float > EsmErr;
vector< float > Sour;
 colSints=(Fh-Fl)/500;
 Flb=Fl;
Chart2->Series[0]->Clear();
Chart2->Series[1]->Clear();

 Button129->Enabled=false;
 Button130->Enabled=false;
 Button131->Enabled=false;
 Button136->Enabled=false;
 Button7->Enabled=true; //  стоп

if(RadioButton44->Checked){
Sour=dPg_sign;
n=0;}
else if(RadioButton45->Checked){
Sour=dPm_vch;
n=1;}

SPg=Trim(Edit21->Text);   //мощность генератора
 Pg=StrToFloat(SPg);

 InitPowMtr();
 InitE825(SPg);

for(j=0;j<colSints;j++)    //colSints   синтезаторов по 500МГц
 {
  Fbeg=Flb+26+500*j;
  for(i=0;i<8;i++)    //8 точек частоты в каждом синтезаторе
  {
    ind=j*8+i;  //точки частоты
   f=Fbeg+i*64;    // шаг частоты 64 МГц
    if((PStop==false) )
      {
       dltPg=Sour[ind];
       SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
       CorrStrGen(SPg);
       WrGenE825(IntToStr(f),SPg);
         MyTimer(100);
    if((P=StepRdPow())==0)
        goto M1;

       EsmErr.insert(EsmErr.end(),P-Pg);
       Chart2->Series[n]->AddXY(f,P-Pg);
       Application->ProcessMessages();

       }
      else
        break;
  }  //for i
 }  //for j

M1:   OfGenE825();
  if(EsmErr.size()!=0)
  {
   Emin = *min_element(EsmErr.begin(), EsmErr.end()) ;
   Emax = *max_element(EsmErr.begin(), EsmErr.end()) ;
   dE=Emax-Emin;
   Label10->Caption="Pmin="+CurrToStrF(fabs(Emin),ffFixed,2);
   Label12->Caption="Pmax="+CurrToStrF(fabs(Emax),ffFixed,2);
   Label13->Caption="dP=" + CurrToStrF(fabs(dE),ffFixed,2);
  }
 Button129->Enabled=true;
 Button130->Enabled=true;
 Button131->Enabled=true;
 Button136->Enabled=true;
 Button7->Enabled=false;

}
//Конец калибровки кабелей БМК-------------------------------------------------------------------------



