
#include <vcl.h>
#pragma hdrstop
#include "ARM.h"
#include "Ftd2xx.h"
#include "TFmWriteUps.h"
#include <math.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"



#define INIT_VAL 99999
#define Fl  4000
#define Fh 18000

#pragma link "RzBorder"
#pragma link "RzBorder"
#pragma resource "*.dfm"
TIniFile *Ini;
double FreqStart = 0, FreqStop = 0;
int OLD_POZ=-1; /*начальная позиция поворотника*/
int STATE_POZ=-1;
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
 FmLib  = new TFmLib(Application);
 FmWriteUps = new TFmWriteUps(Application);

 ClbPwm=false;
 PStop=false;
 ChkDevs=false;
 TimeOff=false;
 PowOnOff=false;
}

void TForm1::CheckCalbPm(void)
{

 if(ClbPwm==false)   //калибровать ватметр, если еще не был откалиброван
 {
  Form1->Update();
  CalPm();
 }
}

bool TForm1::FileCalbGnPm(void)
{
 int n,i;
 AnsiString MyFileName,NamFlWGen,NamFlWPm,S ;
 float* buff;
dPm.clear();
dPg.clear();
if(Mode==0)
{
NamFlWGen="W_Gen_Prm.clb";
NamFlWPm ="W_IM_Prm.clb";
}
else if(Mode==1)
 {
  NamFlWGen="W_Gen_Prd.clb";
  NamFlWPm ="W_IM_Prd.clb";
 }
   if(FileExists(NamFlWGen)==true)
     {
      Myfile=new TFileStream(NamFlWGen,fmOpenRead);
       if(Myfile)
       {
        Myfile->Position=0;
        n=(Myfile->Size)/sizeof(float);   //читать данные калибровки генератора
        buff=new float[n];
        Myfile->ReadBuffer(buff,n*sizeof(float));
        for(i=0;i<n ;i++)
         dPg.insert(dPg.end(),buff[i]);

         delete(Myfile);
         Myfile=NULL;
         delete[] buff;
       } //if MyFile
       else    //if MyFile
         {
          S="Не могу открыть файл "+ NamFlWGen;
          Application->MessageBox(S.c_str(),"Ошибка открытия файла", MB_ICONERROR|MB_OK);
          return false;
         }
     if(FileExists(NamFlWPm)==true)
      {
      Myfile=new TFileStream(NamFlWPm,fmOpenRead);
       if(Myfile)
       {
        Myfile->Position=0;
        n=(Myfile->Size)/sizeof(float);   //читать данные калибровки измерителя мощ.
        buff=new float[n];
        Myfile->ReadBuffer(buff,n*sizeof(float));
        for(i=0;i<n ;i++)
         dPm.insert(dPm.end(),buff[i]);

          delete(Myfile);
          Myfile=NULL;
          delete[] buff;
       } //if MyFile
      else     //if MyFile
      {
          S="Не могу открыть файл "+ NamFlWPm;
          Application->MessageBox(S.c_str(),"Ошибка открытия файла", MB_ICONERROR|MB_OK);
          return false;
      }
    }//  FileExists(NamFlWPm)
     else  //  FileExists(NamFlWPm)
      {
       S="Файл "+NamFlWPm+" не найден";
       Application->MessageBox(S.c_str(),"Внимание!", MB_ICONERROR|MB_OK);
       return false;
      }
  } //  FileExists(NamFlWGen)
 else
   {
       S="Файл "+NamFlWGen+" не найден";
       Application->MessageBox(S.c_str(),"Внимание!", MB_ICONERROR|MB_OK);
       return false;
   }

  if(dPg.size()!=dPm.size())
  {
   Application->MessageBox("Размеры файлов калибровки вх и вых кабелей не равны","Ошибка калибровки", MB_ICONERROR| MB_OK);
   return false;
  } //if size

 // }//  FileExists(NamFlWGen)
   return true;
}


void __fastcall TForm1::ResetUPS(TObject *Sender)
{

if(Application->MessageBox("Отключить питание 1ППА-52", "Внимание!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
 {
   bool lock = FmLib->Lock();
   RESET_UPS_GUI("Сброс",NULL);
   //RESET_DEVICE_GUI("Сброс 1ППА-52",NULL);
   FmLib->RestoreLock(lock);
   Sleep(1000);
   //ResetUPPU(Sender);//сброс УППУ
  }
}

void __fastcall TForm1::CreatScrn(TObject *Sender)
{
//

 float UserScrH,UserScrW;
	float FmH,FmW,n,k;
	TScreen* UserScrn;
	UserScrH=UserScrn->Height;
	UserScrW=UserScrn->Width;
	FmH=Form1->Height;
	FmW=Form1->Width;
	SetDate();
	SetTime();
	if((FmW>UserScrW)||(FmH>UserScrH))
	{
		k= FmW/UserScrW;
		n= FmH/UserScrH;
		if(n>k)
			Form1->ScaleBy(UserScrH,FmH) ;
		else
			Form1->ScaleBy(UserScrW,FmW) ;
	}
  //	ReadMeashDevises();
	dwnibst();
	downloadFileGainFactor();
 
}


//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{

 sm->CloseCom(); //31.08.11
 delete sm;      //31.08.11
SaveMeashDevises();

}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------


void __fastcall TForm1::N19Click(TObject *Sender)
{
//Поиск измерительных приборов
/* if(FindDevises())
  ChekDev(); */

  ShowPanel(Panel12);
}
//---------------------------------------------------------------------------
bool CreateEmptyFile(const char *file_name)
{//создает пустой файл
	FILE *file;
   file = fopen(file_name, "w");
   if (!file)
      return false;
   fclose(file);
   return true;
}

void TForm1::SaveMeashDevises(void)
{
AnsiString s;
AnsiString SDir=GetCurrentDir();
AnsiString DevFileName=SDir+"\\devs.ini";
if(Devs.size()!=0)
{
 if(Devs.size()>2)
  Application->MessageBox("Отключите лишние измерительные приборы ", "Внимание!", MB_ICONERROR|MB_OK) ;

 else
 {
  if (!CreateEmptyFile(DevFileName.c_str())){
     Application->MessageBox("Ошибка при сохранении ini-файла ", "Внимание!", MB_ICONERROR|MB_OK) ;
      return ;
   }

s="Devise1";
   Ini->WriteInteger(s, "Distination1",Devs[0].distn);
   Ini->WriteString(s, "TCP1",Devs[0].TCP);
   Ini->WriteInteger(s, "VI1", Devs[0].Vi);
s="Devise2";
   Ini->WriteInteger(s, "Distination2", Devs[1].distn);
   Ini->WriteString(s, "TCP2", Devs[1].TCP);
   Ini->WriteInteger(s, "VI2", Devs[1].Vi);

   delete Ini;
 }
}
}

void TForm1::ReadMeashDevises(void)
{
AnsiString SDir=GetCurrentDir();
AnsiString DevFileName=SDir+"\\devs.ini";
   Ini = new TIniFile(DevFileName.c_str());

AnsiString s="Devise1";
  MDvs.distn = Ini->ReadInteger(s, "Distination1", 1);
  MDvs.TCP = Ini->ReadString(s, "TCP1", "");
  MDvs.Vi = Ini->ReadInteger(s, "VI1", 1);

Devs.insert(Devs.end(),MDvs);

s="Devise2";
  MDvs.distn = Ini->ReadInteger(s, "Distination2",2);
  MDvs.TCP = Ini->ReadString(s, "TCP2", "");
  MDvs.Vi = Ini->ReadInteger(s, "VI2",2 );

Devs.insert(Devs.end(),MDvs);

if( ChekDev()==true)
ChkDevs=true;

}



void __fastcall TForm1::ChenFr23(TObject *Sender)
{
//
 AnsiString s = IntToStr(zCSpinEdit23->Value);
      if ((s[s.Length() - 1] == '3') && (s[s.Length()] == '8'))
         zCSpinEdit23->Value -= 12;
      else if ((s[s.Length() - 1] == '6') && (s[s.Length()] == '2'))
         zCSpinEdit23->Value += 12;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::TimerDelayOn(TObject *Sender)
{
TDateTime startTime=Now();
TDateTime tm,dtm=0.0014;
AnsiString St;
ShowPanel(PanelTimer);

Word hour,min,sec,msec;
Timer2->Enabled=true;
while((tm=Now()-startTime)<=dtm )
{
DecodeTime(tm,hour,min,sec,msec);
RzLEDDisplay1->Caption=IntToStr(min)+":"+IntToStr(sec);
}

}
void TForm1::ShowTemperatureEletric()
{
	int t2pps = 0,t2zps = 0, t53pps = 0, t53zps = 0;
	edtTemperatureDisplay2pps->Text = t2pps = currentTemperature(2);
	edtTemperatureDisplay2zps->Text = t2zps = currentTemperature(3);
	edtTemperatureDisplay53pps->Text = t53pps = currentTemperature(0);
	edtTemperatureDisplay53zps->Text = t53zps = currentTemperature(1);
	if (t2pps > 51 || t2zps >51 || t53pps >51 || t53zps > 51){
		Button87->Click();
		Application->MessageBox("Перегрев! Аппаратура отключена!", "Внимание!", MB_ICONERROR|MB_OK) ;
	}    
};
void __fastcall TForm1::TimerInCurrentConsumption()
{
	TDateTime startTime=Now();
	TDateTime tm = 0,dtm=0.0014;
	Word day = 0, hour = 0, min = 0, sec = 0, msec = 0;
	while(!PStop )
	{
		ShowTemperatureEletric();
		tm = Now() - startTime;//<=dtm
		DecodeTime(tm, hour,min,sec,msec);
		if (hour == 23 && min == 59 && sec == 59){
			day +=1;
		}
		timeEdt->Text=IntToStr(day)+"д"+":"+IntToStr(hour)+":"+IntToStr(min)+":"+IntToStr(sec);
		Application->ProcessMessages();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::onTimer2(TObject *Sender)
{
Timer2->Enabled=false;
PanelTimer->Visible=false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Go_Stat_Mode(TObject *Sender)
{
	Byte AskDan[13];
	Screen->Cursor = crHourGlass;
	if(Packet_P_CO()==true)
		MyTimer(1000);

	else
		Application->MessageBox("Ошибка при переходе в штатный режим", "Внимание!", MB_ICONERROR|MB_OK) ;
	Screen->Cursor = crDefault;
   PaketFZD(2,AskDan);
}

//--------------------------------------------------------------------------------------------------
void TForm1::readValueForTurnOnAmpl(int indLit, int& indIn, int& indOut, int& Freq, AnsiString& SPg, int& nl)
{
	if (indLit)
	{
		indIn=ComboBox18->ItemIndex;//в FOC вычитается 4
		indOut= ComboBox19->ItemIndex;
		Freq = CSpinEdit13->Value ;
		SPg=Edit36->Text;
		nl=CSpinEdit14->Value-1;
	}
	else
	{
		indIn=ComboBox21->ItemIndex;//в FOC вычитается 4
		indOut= ComboBox22->ItemIndex;
		if(indOut==12)	indOut++;
		Freq = CSpinEdit16->Value;
		SPg = Edit42->Text;
		nl=CSpinEdit15->Value-1;
	}
}
//--------------------------------------------------------------------------------------------------
void TForm1::turnOnAmplifielrs( int n_post, int indLit)
{
	int tindOut,
		 freq_index,
		 indIn, indOut,
		 Freq, Pg;
		 PStop=false;
	AnsiString SPg;
	double dltPg;
	int nl;
	Mode = 1;
	readValueForTurnOnAmpl(indLit, indIn, indOut, Freq, SPg, nl);
	freq_index = GetFreqIndex(Freq);
	InitE825(SPg);
	Pg=StrToInt(SPg);
		dltPg=dPg_sign[freq_index];
	SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
	CorrStrGen(SPg);
	if(! WrGenE825(IntToStr(Freq),SPg)) return;
	if(SetOutAtt(indLit,n_post,nl,freq_index)==false)return ; //закрыть все выходные аттенюаторы,  пакет3
	if(SetOUT_EUS( indLit, n_post, indOut)==false) return;
	if(indOut==13)
		tindOut=0;
	else
		tindOut=indOut;
	if(Att_Luch_Out1(indIn, indOut,indLit,n_post,nl,Att_Ini[nl][freq_index],Att_OUTi[nl][tindOut][freq_index])==false) return;
}
//--------------------------------------------------------------------------------------------------
void TForm1::turnOnAllAmplifielrs()
{
	turnOnAmplifielrs( 0, 0);
	turnOnAmplifielrs( 1, 0);
	turnOnAmplifielrs( 0, 1);
	turnOnAmplifielrs( 1, 1);
}
void __fastcall TForm1::Button86Click(TObject *Sender)

{
	PStop	= False;
   Button86->Enabled=false;
	turnOnAllAmplifielrs();
	TimerInCurrentConsumption();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N25Click(TObject *Sender)
{
	Mode=1;
	AnsiString StDir=ExtractFilePath(Application->ExeName);
	dPg_sign.clear();
	AnsiString MyFileName=StDir+"bmk_sign.cbr";
	ReadFileCabBMK (MyFileName,0);
	dPm_vch.clear();
	MyFileName=StDir+"bmk_vch.cbr";
	ReadFileCabBMK (MyFileName,1);
	ShowPanel(Panel18);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button88Click(TObject *Sender)
{
Panel18->Visible=false;
}
//--------------------------------------------------------------------------------------------------
void TForm1::SetTime()
{
	TDateTime startTime=Now();
	Word hour,min,sec,msec;
	String valueTime;
	DecodeTime(startTime,hour,min,sec,msec);
	if (IntToStr(hour).Length() == 1){valueTime = "0";};
	valueTime = valueTime + IntToStr(hour)+" : ";
	if (IntToStr(min).Length() == 1){valueTime = valueTime + "0";};
	valueTime = valueTime + IntToStr(min);
	setValueEdit("edtEdt1",valueTime);
};
//--------------------------------------------------------------------------------------------------
void TForm1::SetDate()
{
	TDateTime startTime=Now();
	Word year,month,day;
	String valueDate;
	DecodeDate(startTime, year, month, day);
	if (IntToStr(day).Length() == 1){valueDate = "0";};
	valueDate = valueDate + IntToStr(day)+" / ";
	if (IntToStr(month).Length() == 1){valueDate = valueDate + "0";};
	valueDate = valueDate + IntToStr(month)+" / ";
	if (IntToStr(year).Length() == 1){valueDate = valueDate + "0";};
	valueDate = valueDate + IntToStr(year);
	setValueEdit("edtEdt2",valueDate);
};
//--------------------------------------------------------------------------------------------------
void TForm1::setValueEdit(AnsiString compt, String str)
{
	TEdit * tmp_edt;
	tmp_edt = ((TEdit *) FindComponent(compt));
	tmp_edt->Text = str;
};
//--------------------------------------------------------------------------------------------------
AnsiString TForm1::getValueEdit(AnsiString compt)
{
	TEdit * tmp_edt;
	tmp_edt = ((TEdit *) FindComponent(compt));
	return tmp_edt->Text;
};
//--------------------------------------------------------------------------------------------------


void __fastcall TForm1::Button72Click(TObject *Sender)
{
//   OpenDialog3->FileName = (RadioGroup3->ItemIndex==0)? "ППС_": "ЗПС_";
//   OpenDialog3->FileName =SaveDialog3->FileName +Edt3->Text;
	if (OpenDialog1->Execute()){
		string path = OpenDialog1->FileName.c_str();
		 //char path[20] = "IBST.txt";
		 ifstream fin;
	fin.open(path.c_str()); /* ,ofstream::app второй параметр метода open для добавления данных в конец файла*/
	if (!fin.is_open()) // проверка открыт ли файл
	{
		edtBMK53_1->Text = "Err";  //ошибка открытия файла
	}
	else
	{
		char ch;
		string str;
		getline(fin,str);
		if (str == "0")
		{
			RadioButton5->Checked = 0;
			RadioButton6->Checked = 1;
		} else {
			RadioButton5->Checked = 1;
			RadioButton6->Checked = 0;
		};
		int i = 0;
		while (i<8/*!fin.eof()*/)/*пока не конец файла или  fin.get(ch)-считывать посимвольно*/
		{					/*fin >> str; читать целое слово до пробела */
			getline(fin,str);	/*читать строку до перехода на новую строку*/
					/* или fin.getline(char,кол-во символов)*/
		 //  cout << str << endl ;   //вывести символы
		 WriteEdit("edtBMK53_", 1 + i++,str.c_str());
		}
	//      fin.get();
			  //Edit1->Text =  str.c_str();
	}
   fin.close();
  }

}
//---------------------------------------------------------------------------

void  TForm1::WriteEdit(AnsiString nameEdit, int start, AnsiString str_edit)
{
		((TEdit *)FindComponent(nameEdit+IntToStr(start)))->Text = str_edit;
}
//==================================================================================================
double __fastcall TForm1::GetAngleAlph(int begin_sec,int end_sec,int now_deg,int go_deg)
{
	double alph1,alph2;
	alph1=ResAlph( begin_sec, end_sec, now_deg);
	alph2=ResAlph( begin_sec, end_sec, go_deg);
	double dpos=SimpleRoundTo(fabs(alph2-alph1)*ONE_DEG,0);  //шаги поворотника
	return dpos;
}

double __fastcall TForm1 ::ResAlph(int begin_sec,int end_sec,int bet)
{
	double betrad,B,radbeg,radend,radal,alph;
	double E,radE,Q,Qrad,rade,gam,radgam,radet,et ;
	bool rang_out=false;

	radbeg=DegToRad(begin_sec);
	radend=DegToRad(end_sec);
	betrad=DegToRad(bet);
	Qrad=atan(cos(radend) /sin(radbeg));
	//Q=RadToDeg(Qrad);
	if((Qrad+M_PI/2+betrad)>M_PI)
	{
		rang_out=true;
		radet=M_PI-Qrad+M_PI/2-betrad;
	}
	else
		radet=Qrad+M_PI/2+betrad;
	B=sin(radbeg)*sin(radbeg)+cos(radend)*cos(radend);
	//Формула треугольника
	radE=asin( sqrt(B)*sin(radet));
	radgam=M_PI-(radet+radE);
	if(rang_out)
		radal=(M_PI/2-Qrad)+radgam;
	else
		radal=(M_PI/2-Qrad)-radgam;
	alph=RadToDeg(radal);
	return alph;

}



bool __fastcall TForm1::SaveBeamMax(AnsiString nameRadioButtonHemisphere, int lit)
{
	int hemisphere = ((TRadioButton *)FindComponent(nameRadioButtonHemisphere))->Checked;
	SaveDialog1->FileName = edtSerialNumber->Text;
	SaveDialog1->FilterIndex = 2;
	AnsiString filename = "";
   if (SaveDialog1->Execute()){
      filename =filename + SaveDialog1->FileName;
      AnsiString nameEditPosition = lit == 0 ? "edtPositionMax2_" : "edtPositionMax53_";
      int lastBeamNumber = lit == 0 ? 4 : 8;
      TStringList *temp_log = new TStringList;
      if (FileExists(filename)) {
        temp_log->LoadFromFile(filename);
      }
      const AnsiString nameLit = lit == 0 ? "lit2" + IntToStr(hemisphere) : "lit53" + IntToStr(hemisphere);
      int isLitHemisphereInFile = temp_log->IndexOf(nameLit); //вынести проверку в функцию
	if (isLitHemisphereInFile>-1){ return false;}//запись существует
      temp_log->Add(nameLit);
      for (int i = 0; i < (lastBeamNumber); i++){
        temp_log->Add(getValueEdit(nameEditPosition + IntToStr(i)).c_str());
      };
      temp_log->SaveToFile(filename);
		temp_log->Clear();
      delete temp_log;
      return true;
  }
}
bool TForm1::openMaxPosition(AnsiString patch, int lit, bool hemisphere){
	AnsiString nameLit = lit == 0? "lit2" : "lit53";
	nameLit = hemisphere? nameLit + "1": nameLit + "0";
	TStringList *temp_log = new TStringList;
	 if (FileExists(patch)) {
		  temp_log->LoadFromFile(patch);
	}
	 int isLitHemisphereInFile = temp_log->IndexOf(nameLit);
	if (!~isLitHemisphereInFile){
		//запись не существует
		return false;
	}
	AnsiString nameEditPosition = lit == 0 ? "edtBMK2_" : "edtBMK53_";
	int lastBeamNumber = lit == 0 ? 4 : 8;

	for (int i =  1; i < (lastBeamNumber + 1); i++){
		  setValueEdit(nameEditPosition + IntToStr(i) ,temp_log->Strings[isLitHemisphereInFile + i]);
		};
	 temp_log->Clear();
	 delete temp_log;
	 return true;
}

void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
	SaveBeamMax("RadioButton3",1);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
	 if (OpenDialog1->Execute()){
		AnsiString patch = OpenDialog1->FileName;
		openMaxPosition(patch, 1, RadioButton5->Checked);
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn2Click(TObject *Sender)
{
 SaveBeamMax("RadioButton46",0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn1Click(TObject *Sender)
{
if (OpenDialog1->Execute()){
		AnsiString patch = OpenDialog1->FileName;
		openMaxPosition(patch, 0, RadioButton1->Checked);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edtSerialNumberKeyPress(TObject *Sender, char &Key)
{
	if (Key == 13)
	{
		save_ibst();
   }	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edtSerialNumberExit(TObject *Sender)
{
	save_ibst();
}
//---------------------------------------------------------------------------
 void TForm1::save_ibst(){
	SetCurrentDir(ExtractFilePath(Application->ExeName));
	string path = "IBST.txt";
	//char path[10] = "IBST.txt";
  ofstream fout;
  fout.open(path.c_str());
	// открыть или создать файл
	if (!fout.is_open())//
	{
		edtSerialNumber->Text = "Error_open";  //ошибка открытия файла
	}
	else
	{
		 fout << edtSerialNumber->Text.c_str();
	}
	fout.close();
};
void TForm1::dwnibst()
{
	char path[10] = "IBST.txt";
	ifstream fin;
	fin.open(path); /* ,ofstream::app второй параметр метода open для добавления данных в конец файла*/
	if (!fin.is_open()) // проверка открыт ли файл
	{
		edtSerialNumber->Text = "Error_open";  //ошибка открытия файла
	}
	else
	{
		char ch;
		string str;
			getline(fin,str);
			  edtSerialNumber->Text =  str.c_str();
	}
	fin.close();
}
void __fastcall TForm1::Button73Click(TObject *Sender)
{
	InitStrGrd1();
}
//---------------------------------------------------------------------------
void TForm1::InitStrGrd1(void)
{
	for(int i=0;i<5;i++)
	{
		if(CheckedLuch_2(i))
		{
			for( int j=1;j<=163;j++)
				StringGrid1->Cells[i][j]="";
		}

	}
}
void __fastcall TForm1::FormActivate(TObject *Sender)
{

 sm = new SmsdCom;    //31.08.11
 sm->OpenCom("COM7:"); //31.08.11
}
//---------------------------------------------------------------------------
 bool __fastcall TForm1::CheckedFlags(AnsiString NameCheckFlag)
{
	bool we = ((TCheckBox *)FindComponent(NameCheckFlag.c_str()))->Checked;
	return we;
}

//--------------------------------------------------------------------------------------------------
void __fastcall TForm1::SaveTable(int litera)
{
	bool FlagPS;
	int countRowTable = 0, countColTable = 0, numberStringGrid = 0;
	AnsiString filename="", NameStringGrid = "StringGrid";

	if (litera == 2)
	{
		countColTable = 9;
		if	(CheckedFlags("CheckBox76")){
			countRowTable = 17;
		} else{
			countRowTable = 71;
		}
		numberStringGrid = 1;
		SaveDialog1->FileName = "Проверка " + ComboBox2->Text;
		if (RadioButton1->Checked){SaveDialog1->FileName = SaveDialog1->FileName +" " +  RadioButton1->Caption;}
		if (RadioButton2->Checked){SaveDialog1->FileName = SaveDialog1->FileName +" "+ RadioButton2->Caption;	}
	}
	else
	{
		countColTable = 17;
		if	(CheckedFlags("CheckBox75")){
			countRowTable = 27;
		} else{
			countRowTable = 171;
		}
		numberStringGrid = 4;
		SaveDialog1->FileName = "Проверка " + ComboBox6->Text;
		if (RadioButton5->Checked){SaveDialog1->FileName = SaveDialog1->FileName +" " +  RadioButton5->Caption;}
		if (RadioButton6->Checked){SaveDialog1->FileName = SaveDialog1->FileName +" "+ RadioButton6->Caption;	}
	}

	
	TStringGrid * TableCalebr;
	TableCalebr = ((TStringGrid *)FindComponent(NameStringGrid.c_str() + IntToStr(numberStringGrid)));
	SaveDialog1->FilterIndex = 1;
	ofstream fout;
	if (SaveDialog1->Execute()){
	  filename = SaveDialog1->FileName;
	  fout.open(filename.c_str());
	  for (int row_for = 0; row_for <= countRowTable; row_for++){
		  for(int col_for = 0; col_for < countColTable; col_for++) {

			  fout << TableCalebr->Cells[col_for][row_for].c_str() << ";";
		  }
		  fout << endl;
	  };
	  fout.close();
	}
	//delete	TableCalebr;
}


void __fastcall TForm1::btn3Click(TObject *Sender)
{
	SaveTable(2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn4Click(TObject *Sender)
{
	SaveTable(53);	
}
//---------------------------------------------------------------------------



void __fastcall TForm1::btnSeatchDeviceClick(TObject *Sender)
{
	FindDevises();
	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::lstDeviceClick(TObject *Sender)
{
  //lstDevice->Selected
}
//---------------------------------------------------------------------------



void __fastcall TForm1::btn5Click(TObject *Sender)
{
/* viP=1;
	viG=2; */

	switch ( rgPowerMetr->ItemIndex ) {

		case 0 : {
			TCPP = "TCPIP0::" + edtLanPowerMetr->Text  + "::inst0::INSTR";
		} break;
		case 1 : {
			TCPP = "GPIB::" + edtGpibPowerMetr->Text +"::INSTR";
		}; break;
	}
	if (pnl1->Tag == 0)
		if	(ChekPrib(TCPP, &viP)){pnl1->Color = clMoneyGreen; pnl1->Tag = 1;};
	switch ( rgGen->ItemIndex ) {
		case 0 : {
			TCPG = "TCPIP0::" + edtLanGen->Text + "::inst0::INSTR";
		}; break;
		case 1:{
			TCPG = "GPIB::" + edtGpibGen->Text + "::INSTR";
		};  break;
	}
	if (pnl2->Tag == 0)
		if	(	ChekPrib(TCPG, &viG)){pnl2->Color = clMoneyGreen;pnl2->Tag = 1;};
	if (pnl2->Tag == 1 && pnl1->Tag == 1)
		ChkDevs=true;

	
} //---------------------------------------------------------------------------

void __fastcall TForm1::btnConnectDeviceClick(TObject *Sender)
{
if( ChekDev()==true)
ChkDevs=true;
}
//---------------------------------------------------------------------------


bool TForm1::openDeltaPower(AnsiString directory, int lit, bool hemisphere){
	AnsiString SDir=ExtractFilePath(Application->ExeName);
	AnsiString patch=SDir+directory;
	AnsiString nameLit = lit == 0? "lit2" : "lit53";
	nameLit = hemisphere? nameLit + "1": nameLit + "0";
	TStringList *csvData = new TStringList;
	csvData->CaseSensitive =false;
	TStringList *temp_log = new TStringList;
	TStringList *t_log = new TStringList;
	 if (FileExists(patch)) {
		  csvData->LoadFromFile(patch);
	}
	 int isLitHemisphereInFile = csvData->IndexOf(nameLit);
	if (!~isLitHemisphereInFile){
	   if (csvData) {
		csvData->Free();
		csvData = NULL;
		temp_log->Clear();
	 delete temp_log;
	 delete t_log;
	}
		//запись не существует
		return false;
	}
	int lastBeamNumber = lit == 0 ? 8 : 20;
	int n=  lit == 0 ? 4 : 8;
	deltaPower = new float *[lastBeamNumber];
	for (int i=0; i< lastBeamNumber; i++)
		deltaPower[i] = new float[n];
	t_log->Delimiter = ';';
	AnsiString s="";
	for (int i =  1; i <= (lastBeamNumber); i++){
	t_log-> DelimitedText =	s= csvData->Strings[isLitHemisphereInFile + i];
		int itEnd = t_log->Count;
		  for (int j =  0; j < itEnd; ++j){
			 deltaPower[i-1][j]= StrToFloat(t_log->Strings[j]);
		  };

	};
	if (csvData) {
		csvData->Free();
		csvData = NULL;
	}
	 temp_log->Clear();
	 delete temp_log;
	 delete t_log;
/* 	 for (int i=0; i<lastBeamNumber; i++){
		 delete deltaPower[i];
	 }
	 delete deltaPower; */
	 return true;
}
void TForm1::deleteDeltaPower(int rows)
{
	for (int i=0; i<rows; i++){
		 delete deltaPower[i];
	 }
	 delete deltaPower;
}
void __fastcall TForm1::ComboBox2Click(TObject *Sender)
{
/* 	if (OpenDialog1->Execute()){
		AnsiString patch = OpenDialog1->FileName;
		openDeltaPower(patch, 0, RadioButton1->Checked);
	} */
}
//---------------------------------------------------------------------------




