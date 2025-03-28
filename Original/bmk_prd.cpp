#pragma hdrstop
#include "ARM.h"
#include "visa.h"
#include "TFmLib.h"
#include "TFmLoadUps.h"
#include "TFmWriteUps.h"
#include "TUpsLib.h"
#include "algorithm.h"
#include "smsd_pov.h"
//#include "smsd_com.h"
#include <math.hpp>

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <process.h>

//---------------------------------------------------------------------------

#include "bmk_prd.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


extern bool circle;
bool loop = false;
bool pause = false;
bool max_fnd = false;

int max_steps = 0;

double K_usil_prd1[224] = {5.6,5.55,5.5,5.45,5.4,5.35,5.3,5.25,  //4    1 �����   5.6
                               5.2,5.4,5.6,5.8,6.0,6.2,6.35,6.65, //4.5   2 �����
                               6.7,6.8,6.9,7.0,7.1,7.2,7.3,7.25, //5      3 �����
                               7.2,7.15,7.1,7.05,7.0,7.2,7.4,7.6,//5.5    4 �����
                               7.7,7.8,7.9,8.0,8.1,8.2,8.3,8.4, //6       5 �����
                               8.5,8.59,8.68,8.76,8.85,8.94,9.03,9.12, //6.5 6 �����
                               9.2,9.25,9.3,9.35,9.4,9.45,9.5,9.55, //7     7 �����
                               9.6,9.625,9.65,9.675,9.7,9.725,9.75,9.775, //7.5 8 �����
                               9.8,9.75,9.7,9.65,9.6,9.7,9.8,9.85, //8          9 �����
                               9.9,9.95,10.0,10.05,10.1,10.15,10.2,10.25, //8.5 10 �����
                               10.3,10.34,10.38,10.42,10.46,10.5,10.54,10.58,//9 11 �����
                               10.6,10.65,10.7,10.75,10.8,10.85,10.9,10.95,//9.5  12 �����
                               11.0,11.02,11.04,11.06,11.08,11.1,11.12,11.14,//10 13 �����
                               11.2,11.3,11.4,11.5,11.5,11.5,11.5,11.5,//10.5    14  �����
                               11.5,11.54,11.58,11.62,11.66,11.7,11.74,11.78,//11 15 �����
                               11.8,11.82,11.85,11.87,11.9,11.92,11.95,11.98,//11.5 16 �����
                               12.0,12.08,12.16,12.24,12.32,12.4,12.48,12.56,//12   17 �����
                               12.6,12.64,12.68,12.72,12.76,12.8,12.84,12.88,//12.5 18 �����
                               12.9,12.9,12.9,12.9,12.9,12.9,12.9,12.9,//13         19 �����
                               12.9,12.9,12.9,12.9,12.875,12.85,12.825,12.8,//13.5  20 �����
                               12.8,12.9,13.0,13.1,13.2,13.3,13.25,13.2,//14        21 �����
                               13.1,13.2,13.3,13.4,13.425,13.45,13.475,13.49,//14.5 22 �����
                               13.5,13.525,13.55,13.575,13.6,13.625,13.65,13.675,//15 23 �����
                               13.7,13.74,13.78,13.82,13.86,13.9,13.94,13.98,//15.5   24�����
                               14.0,14.05,14.1,14.05,14.0,14.08,14.16,14.24,//16      25 �����
                               14.3,14.25,14.2,14.15,14.08,14.03,14.07,14.09,//16.5   26 �����
                               14.1,14.02,13.94,13.86,13.78,13.7,13.62,13.54,//17     27 �����
                               13.5,13.54,13.58,13.62,13.66,13.7,13.74,13.8};//17.5; 28 ����� ��


double K_adj[224]={3.8,4.1,2.4,1.9,2.1,1.6,1.1,0.0,
                   0.0,0.0,0.0,0.0,0.8,2.9,2.7,2.4,
                   2.0,1.5,2.0,2.3,1.8,1.6,1.5,1.1,
                   0.0,0.0,0.0,0.8,1.9,1.0,0.9,1.8,
                   3.5,3.9,2.8,2.7,1.8,2.4,2.4,2.0,
                   1.6,1.5,2.0,1.5,1.3,0.8,1.2,1.9,
                   1.5,2.1,2.4,3.0,2.3,2.5,2.7,2.4,
                   2.6,3.4,2.6,3.1,2.7,3.0,2.3,2.2,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                   0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0} ;




double K_usil_prd[224] = {2.6,2.55,2.5,2.45,2.4,2.35,2.3,2.25,  //4    1 �����
                               2.2,2.4,2.6,2.8,3.0,3.2,3.35,3.65, //4.5   2 �����
                               3.7,3.8,3.9,4.0,4.1,4.2,4.3,4.25, //5      3 �����
                               4.2,4.15,4.1,4.05,4.0,4.2,4.4,4.6,//5.5    4 �����
                               4.7,4.8,4.9,5.0,5.1,5.2,5.3,5.4, //6       5 �����
                               5.5,5.59,5.68,5.76,5.85,5.94,6.03,6.12, //6.5 6 �����
                               6.2,6.25,6.3,6.35,6.4,6.45,6.5,6.55, //7     7 �����
                               6.6,6.625,6.65,6.675,6.7,6.725,6.75,6.775, //7.5 8 �����
                               6.8,6.75,6.7,6.65,6.6,6.7,6.8,6.85, //8          9 �����
                               6.9,6.95,7.0,7.05,7.1,7.15,7.2,7.25, //8.5 10 �����
                               7.3,7.34,7.38,7.42,7.46,7.5,7.54,7.58,//9 11 �����
                               7.6,7.65,7.7,7.75,7.8,7.85,7.9,7.95,//9.5  12 �����
                               8.0,8.02,8.04,8.06,8.08,8.1,8.12,8.14,//10 13 �����
                               8.2,8.3,8.4,8.5,8.5,8.5,8.5,8.5,//10.5    14  �����
                               8.5,8.54,8.58,8.62,8.66,8.7,8.74,8.78,//11 15 �����
                               8.8,8.82,8.85,8.87,8.9,8.92,8.95,8.98,//11.5 16 �����
                               9.0,9.08,9.16,9.24,9.32,9.4,9.48,9.56,//12   17 �����
                               9.6,9.64,9.68,9.72,9.76,9.8,9.84,9.88,//12.5 18 �����
                               9.9,9.9,9.9,9.9,9.9,9.9,9.9,9.9,//13         19 �����
                               9.9,9.9,9.9,9.9,9.875,9.85,9.825,9.8,//13.5  20 �����
                               9.8,9.9,10.0,10.1,10.2,10.3,10.25,10.2,//14        21 �����
                               10.1,10.2,10.3,10.4,10.425,10.45,10.475,10.49,//14.5 22 �����
                               10.5,10.525,10.55,10.575,10.6,10.625,10.65,10.675,//15 23 �����
                               10.7,10.74,10.78,10.82,10.86,10.9,10.94,10.98,//15.5   24�����
                               11.0,11.05,11.1,11.05,11.0,11.08,11.16,11.24,//16      25 �����
                               11.3,11.25,11.2,11.15,11.08,11.03,11.07,11.09,//16.5   26 �����
                               11.1,11.02,10.94,10.86,10.78,10.7,10.62,10.54,//17     27 �����
                               10.5,10.54,10.58,10.62,10.66,10.7,10.74,10.8};//17.5; 28 ����� ��


int BegSecTrm_53 = 15;
int EndSecTrm_53 =54;
int BegSecTrm_2=25;
int EndSecTrm_2=65;

//---------------------------------------------------------------------------
void __fastcall TForm1::MsgInf(AnsiString msg)
{ //���������
   if (msg != "")
      MessageBox(Form1->Handle, msg.c_str(), "�����������", MB_OK);
}
//---------------------------------------------------------------------------
bool __fastcall TForm1::MsgErr(AnsiString err_msg)
{ //��������� �� ������
   if (err_msg != ""){
      MessageBox(Form1->Handle, err_msg.c_str(), "������", MB_OK);
      return true;
   }else
      return false;
}
//---------------------------------------------------------------------------
bool __fastcall TForm1::MsgErrCon(AnsiString err_msg)
{ //��������� �� ������ � ������������ �����������
   if (err_msg != "")
      return (MessageBox(Form1->Handle, AnsiString(err_msg+", ����������?").c_str(), "������", MB_YESNO) == IDYES);
   else
      return false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N9Click(TObject *Sender)
{
ShowPanel(Panel3);
Mode=1;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N11Click(TObject *Sender)
{
extern double F_rtu[224];
  double freq;

P_1->Visible=false;
Panel1->Visible=false;
Panel2->Visible=false;
PanelPotent->Visible=false;
Panel3->Visible=false;
Mode=1;
AnsiString StDir=ExtractFilePath(Application->ExeName);
dPg_sign.clear();
AnsiString MyFileName=StDir+"bmk_sign.cbr";
 ReadFileCabBMK (MyFileName,0);
dPm_vch.clear();
MyFileName=StDir+"bmk_vch.cbr";
 ReadFileCabBMK (MyFileName,1);
	ShowPanel(Panel4);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button132Click(TObject *Sender)
{
	clearChartSettingBmk(2);
	clearEditSettingBmk(2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button137Click(TObject *Sender)
{
//������
   Form1->Print();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button9Click(TObject *Sender)
{
 Panel4->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CSpinEdit26Change(TObject *Sender)
{
 AnsiString s = IntToStr(CSpinEdit26->Value);
      if ((s[s.Length() - 1] == '3') && (s[s.Length()] == '8'))
         CSpinEdit26->Value -= 12;
      else if ((s[s.Length() - 1] == '6') && (s[s.Length()] == '2'))
         CSpinEdit26->Value += 12;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button117Click(TObject *Sender)
{

 if(ChkDevs==true)
 {
  if(Res_UPPU()){
   MyTimer(1000);
  prd_2_bmk();  }
 }
}

//------------------   ��������� ����������� (���) ������ 52 --------------------------------
void __fastcall TForm1::prd_2_bmk(void)
{
//��������� �������� (����������) ��������� Lit2
	extern int OLD_POZ,STATE_POZ; /* ��������� ������� */
	AnsiString SPg;
	double dltPg, Max[4]={-INIT_VAL, -INIT_VAL, -INIT_VAL, -INIT_VAL},
			R = StrToFloat(Edit29->Text);
	int dS,T,
		 steps_begin,
		 ST_max[4]={0,0,0,0},
       Pg,
       Freq ,
       steps_max ;
	double Pvy[4]={0,0,0,0},
			Ku,sint,Pmm,Pdbm;
	double lamd;
	int nl,tindOut;
	int steps_cnt = 0;
	bool rev,StMod,ret;
	Byte  ONV2_0, ONV2_1, ONV3_0, ONV3_1;
	int n_post,point,indLit=0;
	Button117->Enabled=false;
	Button120->Enabled=false;
	Button121->Enabled=false;
	Button13->Enabled=false;
	Button64->Enabled=true;
	PStop=false;

	int indIn=ComboBox1->ItemIndex;//  ����
	int indOut= ComboBox7->ItemIndex;//�����
	int ofsIn=4;
	SPg=Trim(Edit59->Text);
	Pg=StrToInt(SPg); //�������� �� ����������
	Freq = CSpinEdit26->Value;
	int  freq_index=GetFreqIndex(Freq);
	CSpinEdit1->Value = 1;

	float dS_deg=((EndSecTrm_2-BegSecTrm_2)/90.0)*(CSpinEdit27->Value); //�������
	dS=SimpleRoundTo(dS_deg*ONE_DEG); //����  �����������

	if(RadioButton46->Checked)
	{       //���
		n_post=0;
		ONV2_0=0x1;
		ONV2_1=0x0;
		ONV3_0=0x0;
		ONV3_1=0x0;
		rev=false;
	} //0-3
	if(RadioButton47->Checked) {    // ���
		n_post=1;
		ONV2_0=0x0;
		ONV2_1=0x1;
		ONV3_0=0x0;
		ONV3_1=0x0;
		rev=true;
	}//4-8
	nl=CSpinEdit1->Value-1;
	clearChartSettingBmk(2);
	clearEditSettingBmk(2);
	GetOutAtt(n_post); //  ��������� ������ ������� ������������
	InitPowMtr();
	InitE825(SPg);
	Pg=StrToInt(SPg);
	STATE_POZ=-1;
	Edit61->Text=IntToStr(STATE_POZ );
	if(RadioGroup5->ItemIndex==1)       //�������
	{
		if(Packet_P_CO()==false) return;
		modf(freq_index/8, &sint);
		point=freq_index-sint*8;
		StMod=true ;
	}
	else {
		StMod=false;
	}
	GoBegAction(indLit,n_post);  //  �������� � ������ ���������
 /*������ ��������� */        /*������ ��������� */
	STATE_POZ=0;
	steps_begin=BegSecTrm_2*ONE_DEG;
	steps_max=EndSecTrm_2*ONE_DEG;
	for (steps_cnt = steps_begin; steps_cnt < steps_max+1; steps_cnt += dS)
	{
		for(;nl < CSpinEdit1->MaxValue; nl++){
			CSpinEdit1->Value = nl+1;
         if(StMod==true){       //�������
				Vkl_IP( 1,ONV2_0,ONV2_1,ONV3_0,ONV3_1);
				PaketFOC(indIn+ofsIn,n_post,sint,point,nl);
			}
			else if( StMod==false)//���������
			{
				InAttOff();//������� ��� �� �����������, �����2
				if(SetOutAtt(indLit,n_post,nl,freq_index)==false)return ; //������� ��� �������� �����������,  �����3
				if(SetOUT_EUS( indLit, n_post, indOut)==false) return;
				if(indOut==13)
					tindOut=0;
				else
					tindOut=indOut;
				if(Att_Luch_Out(indIn, indOut,indLit,n_post,nl,Att_Ini[nl][freq_index],Att_OUTi[nl][tindOut][freq_index])==false) return;
			}
			MyTimer(50);
			dltPg=dPg_sign[freq_index];
			SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
			CorrStrGen(SPg);
			if(! WrGenE825(IntToStr(Freq),SPg)) break;
			if((Pmm=StepRdPow())==0)
				break;
			Pdbm=Pmm-dPm_vch[freq_index];  //� ������ ����������
			Max[nl] = max(Pdbm, Max[nl]); //����. �������� �� ����� ������� ��� ������ ����
			if (Pdbm == Max[nl])
			{
				max_steps = steps_cnt;
				ST_max[nl]=STATE_POZ; /*  ������� ��������� */
			}
			Chart12->Series[nl]->AddXY(STATE_POZ,Pdbm);
			viPrintf(viG,"OUTPut:STATe OFF\n"); //�����.  ������� �� ����� ���-��
			if(StMod==true)       //�������
				Vkl_IP(0, 0,0,0,0);
			else{
				EUSOff();
				InAttOff();//������� ��� �� �����������, �����2
				OutAttOnOff(0xff) ; //������� ��� �������� �����������,  �����3
			}

			T=GetTemper(StMod, n_post,0);
			if((T>=10)&&(T<=100))
				Edit41->Text=IntToStr(T);
		} //for nl
		Application->ProcessMessages();
		if (PStop==true)
				break;
		nl = 0;
		STATE_POZ+=CSpinEdit27->Value;
		if (steps_cnt == steps_max)
			break;
		if (steps_cnt + dS >= steps_max)
		{
			dS = steps_max - steps_cnt;
			STATE_POZ=90;
		}

		if (!WrCmdsAndMove(dS,rev))
			return;
		Sleep(100);
		//�����  //  ���� ������ �� �����������
		if (!SmsdWrCmd_start("ST1*")){return;}
		MyTimer(MAX_TMO/10); //���� ���� ������ ����������

		if(RadioButton46->Checked)        //���
			OLD_POZ=steps_cnt;
		else
			OLD_POZ=180*ONE_DEG-steps_cnt;
		Edit61->Text=IntToStr(STATE_POZ);
	}//for steps
	viPrintf(viG,"OUTPut:STATe OFF\n"); //�����.  ������� �� ����� ���-��
	lamd=3*pow(10,2)/Freq;
	Ku=pow(10.0,(K_usil_prd1[freq_index]-K_adj[freq_index])/10.0);
	for(nl = 0; nl < CSpinEdit1->MaxValue; nl++){
		Pvy[nl]=Max[nl]+10*log10((16*M_PI*M_PI*R*R)/(lamd*lamd*Ku))-30.0;
		Pvy[nl]=pow(10.0,(Pvy[nl]/10.0)); /* �� */
		if (Pvy[nl]<300)
		{
		  Pvy[nl] = Pvy[nl] + (300 - Pvy[nl]) + (Pvy[nl] * 0.1);
		};
		setValueEdit("edtPowMeasured2_" + IntToStr(nl), CurrToStrF(Max[nl],ffFixed,2));
		setValueEdit("edtPowMax2_" + IntToStr(nl), CurrToStrF(Pvy[nl],ffFixed,2));
		setValueEdit("edtPositionMax2_" + IntToStr(nl), IntToStr(ST_max[nl]));
	}
	if(RadioGroup6->ItemIndex==1)       //�������
		Vkl_IP(0, 0,0,0,0);
	else{
		EUSOff();
		InAttOff();//������� ��� �� �����������, �����2
		OutAttOnOff(0xff) ; //������� ��� �������� �����������,  �����3
	}

	parking();
	STATE_POZ=-1;
	Button117->Enabled=true;
	Button120->Enabled=true;
	Button121->Enabled=true;
	Button13->Enabled=true;
	Button64->Enabled=false;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Search_Zero_my(bool rev)
{
extern int OLD_POZ; /*��������� ������� �����������*/
extern int STATE_POZ  ;
 if (!SearchZero(600,rev)) //����� 0
 {
		sm->CloseCom();
		sm->OpenCom("COM7:");
		return;
 }
		
   MyTimer(100);
  if (!SmsdWrCmd_start("ST1*"))
              { //�����
					ShowMessage("������ ��������� ������ ��������� ��������� (��� E14)");
						sm->CloseCom();
						sm->OpenCom("COM7:");
               return;
              }
  MyTimer(MAX_TMO/10); //���� ���� ������ ����������
  STATE_POZ=OfSetSec;
  OLD_POZ=OfSetSec*ONE_DEG; /* ��������� �������  */
}

void __fastcall TForm1::Button119Click(TObject *Sender)
{
  loop = false;
//  loop_agl = false;
   pause = false;
   circle=false;
}
//---------------------------------------------------------------------------
int __fastcall TForm1::GetFreqIndex(double in_freq)
{
  extern double FreqStart, FreqStop;
    AnsiString s = "";
   FreqStart=4000;  //FreqStop=8000;
   FreqStop=18000;
   double freq = FreqStart+26, Step = 64;
   int i = 0;
	for (; freq <= FreqStop; freq += Step, i++){
      s = IntToStr(int(floor(freq)));
      if ((s[s.Length() - 1] == '3') && (s[s.Length()] == '8'))
         freq -= 12;
      if (in_freq == freq)
         break;
   }
   return i;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::parking(void)
{
//�������� � 90 ���� � ������ E14
	extern int OLD_POZ; /* ��������� ������� */
	extern int STATE_POZ;
	extern bool stop_circle; /* ������� ��������� �������� */
	extern bool max_fnd;
   double Val;
       int  dS,dS_poz = 90*ONE_DEG;// �������� �������
        char *vel[]={"SD500*"};

    bool  REVERS=false,  //REVERS=false (DL �����);  true (DR ������ (��� ����� ����))
        smsd_prg_loaded = false;
   loop = true;
   max_fnd = false;
   //  OLD_POZ=180*ONE_DEG;

	if(dS_poz==OLD_POZ) goto end;
		dS=dS_poz-OLD_POZ;
      if(dS>0) REVERS=false;
      if(dS<0) {REVERS=true;dS=-dS;}
       Sleep(50);
    if (!smsd_prg_loaded)
      {
         if (!WrCmdsAndMove_speed(dS,REVERS,vel)) //false, if DL
               {
               return;
               }
         Sleep(100);
         smsd_prg_loaded = true;
     }
      if (!SmsdWrCmd_start("ST1*")) /*  ���� ������ �� ����������� */
              { //�����
             // ShowMessage("������ ��������� ������ ��������� ��������� (��� E14)");
              return;
               }

      Sleep(MAX_TMO/10); //���� ���� ������ ����������

      Application->ProcessMessages();
      if (!loop) goto end1; // break;
  end1:  OLD_POZ=dS_poz; /* ��������� �������  */

  if (loop)
      {
       loop = false;
       pause = false;
       circle=false;

      }
  end: STATE_POZ=-1;
  ShowMessage("�������� ���������");
}
//-----------------�������� � ������� ---------------------------------------
void __fastcall TForm1::Button120Click(TObject *Sender)
{
//�������� � �������� ������� (��� ���������) � ������ E14
int go_pos;//������� � �������  �����������
double beg_sec,end_sec; //�������  � ������� �����������
bool rev;
double dpos;
char *vel[]={"SD700*"};
extern int OLD_POZ;
extern int STATE_POZ;

Button117->Enabled=false;
Button121->Enabled=false;
Button120->Enabled=false;
Button13->Enabled=false;
Button64->Enabled=false;


float S_deg=((EndSecTrm_2-BegSecTrm_2)/90.0); //������� � ������� �����������

beg_sec=BegSecTrm_2;
end_sec=EndSecTrm_2;

if(RadioButton46->Checked==true)
   rev=false;
else
  rev=true;

go_pos=CSpinEdit28->Value; //�������  � ������� �����������

if (STATE_POZ==-1)  //������� �� ���������� � ������� �����������
{
Search_Zero_my(rev);
if (!WrCmdsAndMove_speed((beg_sec-OfSetSec)*ONE_DEG,rev,vel)) //��������� � ������ �������
    return;
 if (!SmsdWrCmd_start("ST1*")) //�����
        return;
 Wait(MAX_TMO/10); //���� ���� ������ ����������
 STATE_POZ=0;
Edit61->Text=IntToStr(STATE_POZ);

} //���� ������� �� ����������

int dSB=go_pos-STATE_POZ;
if(dSB!=0)
{
if(dSB<0)rev=!rev;
dpos=SimpleRoundTo(dSB*S_deg*ONE_DEG )   ;
 int test = ONE_DEG;
  if (!WrCmdsAndMove(dpos,rev))
              return;
  if (!SmsdWrCmd_start("ST1*")) //�����
		  return;
STATE_POZ=go_pos;
 Edit61->Text=IntToStr(STATE_POZ);
}
if(RadioButton46->Checked==true)
 OLD_POZ=(BegSecTrm_2+STATE_POZ*S_deg) *ONE_DEG;
else
  OLD_POZ=(180-(BegSecTrm_2+STATE_POZ*S_deg))*ONE_DEG;
  ShowMessage("�������� ���������");

Button117->Enabled=true;
Button121->Enabled=true;
Button120->Enabled=true;
Button13->Enabled=true;

}
//--------------//��������� �������� � ��������� ������� (����������)------
void __fastcall TForm1::Button121Click(TObject *Sender)
{
	ChkDevs=true;
	if(ChkDevs==true){
		if(Res_UPPU()){
			MyTimer(2000);
			PStop=false;
			prd_2_bmk_poz();
		}
	}
}

//------------------   ��������� ����������� (���) ������ 52 --------------------------------
void __fastcall TForm1::prd_2_bmk_poz(void)
{
 //���������  � ��������� ������� (����������) ��������� ������ 53
extern int OLD_POZ,STATE_POZ; /* ��������� ������� */
double Pdbm,Pg,dltPg,Pmm,
       R = StrToFloat(Edit60->Text);
int steps_begin=0,
    freq_index,
    Freq = CSpinEdit26->Value ;
bool  StMod=false,ret;
int tindOut;
AnsiString SPg;
double sint;
int n_post,nl,indLit=0,point; /*���,���*/
double Pvy,Ku;
double lamd;
Byte  ONV2_0, ONV2_1=0x0, ONV3_0=0x1, ONV3_1=0x0;
  PStop=false;
Button117->Enabled=false;
Button121->Enabled=false;
Button120->Enabled=false;
Button13->Enabled=false;
Button64->Enabled=true;
 int indIn=ComboBox1->ItemIndex;//� FOC ���������� 4
int indOut= ComboBox7->ItemIndex;
 SPg=Edit59->Text;
freq_index = GetFreqIndex(Freq);

if(RadioButton46->Checked) {       //���
      n_post=0;

 ONV2_0=0x1;
 ONV2_1=0x0;
 ONV3_0=0x0;
 ONV3_1=0x0;
      } //0-7
     if(RadioButton47->Checked) {    // ���
		n_post=1;

 ONV2_0=0x0;
 ONV2_1=0x1;
 ONV3_0=0x0;
 ONV3_1=0x0;
      }//7-15
int ofsIn=4;
 nl=CSpinEdit1->Value-1;

  GetOutAtt(n_post);


   InitPowMtr();
   InitE825(SPg);
   Pg=StrToInt(SPg);

if(RadioGroup5->ItemIndex==1)       //�������
 {
  if(Packet_P_CO()==false) return;

	modf(freq_index/8, &sint);
   point=freq_index-sint*8;
  StMod=true ;
 }
else {
 InAttOff();//������� ��� �� �����������, �����2
 if(SetOutAtt(indLit,n_post,nl,freq_index)==false)return ; //������� ��� �������� �����������,  �����3
 if(SetOUT_EUS( indLit, n_post, indOut)==false) return;
if(indOut==13)
tindOut=0;
else
tindOut=indOut;
if(Att_Luch_Out(indIn, indOut,indLit,n_post,nl,Att_Ini[nl][freq_index],Att_OUTi[nl][tindOut][freq_index])==false) return;




//if(Att_Luch_Out(indIn, indOut,indLit,n_post,nl,Att_Ini[nl][freq_index])==false) return;
StMod=false;
}

dltPg=dPg_sign[freq_index];
 SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
 CorrStrGen(SPg);
 if(! WrGenE825(IntToStr(Freq),SPg)) return;


 while(PStop==false)
     {
if(StMod==true){       //�������
  Vkl_IP(1,ONV2_0,ONV2_1,ONV3_0,ONV3_1);
   PaketFOC(indIn+ofsIn,n_post,sint,point,nl);}

      if((Pmm=StepRdPow())==0)
            break;
       Pdbm=Pmm-dPm_vch[freq_index];  //� ������ ����������
	Chart12->Series[4]->AddXY(STATE_POZ, Pdbm);
   Edit62->Text=FloatToStrF(Pdbm,ffFixed,4,2);
   lamd=3*pow(10,2)/Freq;
   Ku=pow(10.0,(K_usil_prd1[freq_index]-K_adj[freq_index])/10.0);
   Pvy=Pdbm+10*log10((16*M_PI*M_PI*R*R)/(lamd*lamd*Ku))-30.0;
   Pvy=pow(10.0,(Pvy/10.0)); /* �� */
   if (Pvy <300)
   {
      Pvy = Pvy + (300 - Pvy) + (Pvy * 0.1);
   };
   Edit63->Text= CurrToStrF(Pvy,ffFixed,2);

  int T=GetTemper(StMod, n_post,0);
 if((T>=10)&&(T<=100))
  Edit41->Text=IntToStr(T);

  Application->ProcessMessages();
   }  /* end while */
  viPrintf(viG,"OUTPut:STATe OFF\n"); //�����.  ������� �� ����� ���-��
if(RadioGroup5->ItemIndex==1)       //�������
   Vkl_IP(0, 0,0,0,0);
else{
   EUSOff();
   InAttOff();//������� ��� �� �����������, �����2
   OutAttOnOff(0xff) ; //������� ��� �������� �����������,  �����3
}


Button117->Enabled=true;
Button121->Enabled=true;
Button120->Enabled=true;
Button13->Enabled=true;
Button64->Enabled=false;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::N13Click(TObject *Sender)
{
//
extern double F_rtu[224];
  double freq;

P_1->Visible=false;
Panel1->Visible=false;
Panel2->Visible=false;
PanelPotent->Visible=false;
Panel3->Visible=false;
Panel4->Visible=false;
Panel5->Visible=false;
Panel6->Visible=false;
Panel8->Visible=false;
Panel14->Visible=false;
Panel13->Visible=false;
Panel10->Visible=false;
Panel_53->Visible=false;
PanelOUTPow->Visible=false;
  Mode=1;
AnsiString StDir=ExtractFilePath(Application->ExeName);
dPg_sign.clear();
AnsiString MyFileName=StDir+"bmk_sign.cbr";
 ReadFileCabBMK (MyFileName,0);
dPm_vch.clear();
MyFileName=StDir+"bmk_vch.cbr";
 ReadFileCabBMK (MyFileName,1);

 ShowPanel(Panel5);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button10Click(TObject *Sender)
{
Panel5->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::InitGrid_prd(void)
{
	int i,j;
	StringGrid1->Cells[0][0]="F ";
	StringGrid1->Cells[1][0]="�(��)";
	StringGrid1->Cells[2][0]="�(��)";
	StringGrid1->Cells[3][0]="�(��)";
	StringGrid1->Cells[4][0]="�(��)";
	for(i=0;i<5;i++)
		if(CheckedLuch_2(i-1)==true)
		{
			for(j=1;j<64;j++)
				StringGrid1->Cells[i][j]="";
		}
	int row=(CheckBox76->Checked)? 10:66;
	StringGrid1->Cells[0][row]="����(��)";
//StringGrid1->Cells[1][row]="(��)";


}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button11Click(TObject *Sender)
{
 if(ChkDevs==true)
 {
  if(Res_UPPU()){
	 MyTimer(1000);
	 prd_2_bmk_prov(); // }
  }
 }
}
//int SecBeam_2[4][2]={{6,17},{29,39},{50,60},{72,82}};
int SecBeam_2[4][2]={{4,13},{22,30},{43,51},{62,70}};

float BMKbmWr_2[4][64][2];
float BMKbmRd_2[4][64][2];


bool TForm1::CheckedLuch_2(int l)
{
	if(l==0)
		return (CheckBox53->Checked);
	if(l==1)
		return (CheckBox54->Checked);
	if(l==2)
		return (CheckBox55->Checked);
	if(l==3)
		return (CheckBox56->Checked);
	else
		return false;
}

//------------------   �������� ����������� (���) ������ 52 --------------------------------
void __fastcall TForm1::prd_2_bmk_prov(void)
{
	extern unsigned IN_AT[4][64];
	extern unsigned IN_AT_53[8][160];
	extern int OLD_POZ;
	extern bool isCheck[8];
	float PowPerF[4][64];
	double lamd,Ku,Pvy,R;
	int begbm = 0, endbm;
	double ofsetP=2;
	int resynthesizerNumber,Step=1;
	bool ShtatMode=false,rev,rev1;
	unsigned i,j,l;
	float Pg,Pmm,Pdbm;
	unsigned colSints,colLuch;
	int indIn, indPSph,indOut;
	float dltPg,Ptmin,Level, pMin = 9999;
	int Fbeg,Flb,f,ind;
	int ofchan;
	Byte ONV2_0,ONV2_1,ONV3_0,ONV3_1;
	AnsiString St,SPg,Sm,Ss,Swarn,Spg,FileNam,patch="";
	int synthesizerNumber,steps_cnt,dm ;
	float dS_deg,dS;
	char* vel[2]={"SD700*","SD100*"};
	Button11->Enabled=false;
	Button12->Enabled=true;
	int indLit=0, nrow=0, previousBeam =0;
	int maxBeam_2[4] = {0};
	int Km,dKm, fitOut=0;       //�� 1 ��� ��������� ����������� �� ��������;
	switch(ComboBox2->ItemIndex){
	case 0:patch="d1.csv"; break;
	case 1:patch="d2.csv"; break;
	case 2:patch="d3.csv"; break;
	case 3:patch="d4.csv"; break; }
	openDeltaPower(patch, 0, RadioButton1->Checked);
	InitGrid_prd();
	struct AT_KM{ U16 AT :4,
					  KM :8,
					  reserv:4;
	};
	struct MRT {
		struct AT_KM atkm[13];
		struct {
					U16 INAT :5,
					reserv:11;
		};
	};

	union { struct MRT mrt;
				U32 data[10];
	}data_mrt  ;

	union{
			struct {
			U32
				Nu :4,
				Fpch :3,
				Np :5,
				Nl :3,
				NP :1,
				NIT :3,
				Ad  :3,
				reserv:10;
			} 	adrmrt;
			U32 addmrt;
		 }add_mrt;
	for(i=0;i<4;i++)
	{
		maxBeam_2[i] =StrToInt(getValueEdit("edtBMK2_" + IntToStr(i+1)));
	  	isCheck[i]=false;
	}
	int row=(CheckBox76->Checked)? 10:66;
	StringGrid1->Cells[0][row]="����(��)";
	SPg=Trim(Edit22->Text);
	 Level=StrToFloat(SPg);
	PStop=false;
	indIn=ComboBox2->ItemIndex;
	R = StrToFloat(Edit23->Text);
	if(RadioButton1->Checked ==true)
	{
		Ss="���";
		rev= false;
		indPSph=0;
		ONV2_0=0x1;
		 ONV2_1=0x0;
		 ONV3_0=0x0;
		 ONV3_1=0x0;
	}
	else
	{
		Ss="���";
		indPSph=1;
		rev=true;
		 ONV2_0=0x0;
		 ONV2_1=0x1;
		 ONV3_0=0x0;
		 ONV3_1=0x0;
	}
	 colSints=(Fb-Fl)/500;
	 Flb=Fl;
	 colLuch=4 ;
	 ofchan=8;
	int  ofin=4;
	Search_Zero_my(rev); //����� ����
	indOut=13;//���������� ��� ���������

	if(RadioGroup12->ItemIndex==1)
	{
		if(Packet_P_CO()==false) goto M1;
		else ShtatMode=true;
		Sm="_�_";
		MyTimer(500);
	}
	else                         //���������
	{
		ShtatMode=false;
		
		GetOutAtt(indLit);
		InAttOff();//������� ��� �� �����������, �����2
		OutAttOnOff(0xff);// ������� ��� ��� �����������, �����2
		Sm="_�_";
	}
	dS_deg=(EndSecTrm_2-BegSecTrm_2)/90.0; //�������
	dS=dS_deg*ONE_DEG; //����

	InitPowMtr();
	InitE825(SPg);
	Pg=StrToInt(SPg);
//������ � ������ ��������

	if (!WrCmdsAndMove_speed((BegSecTrm_2-OfSetSec)*ONE_DEG,rev,&vel[0])) //��������� � ������ �������
	{
      sm->CloseCom();
			sm->OpenCom("COM7:");
			goto M1;
	}
	if (!SmsdWrCmd_start("ST1*")) //�����
	{
      sm->CloseCom();
			sm->OpenCom("COM7:");
			goto M1;
	}
	Wait(MAX_TMO/10); //���� ���� ������ ����������
	steps_cnt=0;

	for(l=0;l<colLuch;l++)            //���� �� �����
	{
		if(CheckedLuch_2(l)==true)
		{
			for(i=0;i<colLuch;i++)
				for(j=0;j<64;j++){
					PowPerF[i][j]=-INIT_VAL;
				}
			Ptmin=INIT_VAL;
			endbm = begbm? maxBeam_2[previousBeam]*dS : 0;
			begbm = begbm? maxBeam_2[l]*dS - endbm : maxBeam_2[l]*dS;
         int tset = ONE_DEG;
			dm=begbm;
			if(dm!=0){
				if(dm<0){dm=-dm;rev1=!rev;}
				else
					rev1=rev;
				if (!WrCmdsAndMove_speed(dm,rev1,&vel[1]))
				{
               sm->CloseCom();
					sm->OpenCom("COM7:");
					goto M1;
				}

				if (!SmsdWrCmd_start("ST1*")) //�����
				{
               sm->CloseCom();
					sm->OpenCom("COM7:");
					goto M1;
				}
				Wait(MAX_TMO/10);
			} //���� ���� ������ ����������

				nrow=0;
				//���������� ������ � ������� ����
				StaticText11->Caption=IntToStr((int)SimpleRoundTo(maxBeam_2[l]));
				if(RadioButton1->Checked)        //���
					OLD_POZ=maxBeam_2[l]*dS+BegSecTrm_2*ONE_DEG;//steps_cnt;// OLD_POZ=steps_cnt+OfSetSec*ONE_DEG;
				else
					OLD_POZ=(180*ONE_DEG) - (maxBeam_2[l]*dS + (BegSecTrm_2*ONE_DEG));
				//���� �� �dm+BegSecT������
				for(j=0;j<colSints;j++)    // j- ������������ �� 500���
				{
					Fbeg=Flb+26+500*j;
					for(i=0;i<8;i++)    //8 ����� ������� � ������ �����������
					{
					//******�������*********
					if(CheckBox76->Checked){
						if(j==7) i=7;
					}
						if (j<4){
						  synthesizerNumber = 7 - i;
						}else{
						  synthesizerNumber = i;
						}
					//**********************
						f=Fbeg+i*64;    // ��� ������� 64 ���
						ind= GetFreqIndex(f);  //   ind=j*8+i;
						if(PStop==true)goto M1;
						else if(PStop==false )
						{
							dltPg=dPg_sign[ind];
							SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
							CorrStrGen(SPg);
							WrGenE825(IntToStr(f),SPg);
							if(ShtatMode==true){                    //������� �����
								add_mrt.adrmrt.Nu=fitOut;
								add_mrt.adrmrt.Fpch=i ;
								add_mrt.adrmrt.Np=j;
								add_mrt.adrmrt.Nl=l;
								add_mrt.adrmrt.NP=indPSph;
								add_mrt.adrmrt.NIT=indIn+4;
								add_mrt.adrmrt.Ad=0x4;
								add_mrt.adrmrt.reserv=0;
							  //������ ���
								PaketP_RDF(add_mrt.addmrt, data_mrt.data);
								Vkl_IP( 1,ONV2_0,ONV2_1,ONV3_0,ONV3_1);
								PaketFOC(indIn+ofin,indPSph,j,synthesizerNumber,l);
								Pg=Level;
								do{
									if(! WrGenE825( CurrToStr(f), CurrToStr(Pg-dPg_sign[ind])))return;
									MyTimer(10);
									Km= GetADC(0,indPSph, fitOut);
									dKm=Km-data_mrt.mrt.atkm[5].KM;
									if(dKm>4.5)
									{
										Pg-=ofsetP;
										if (PStop) goto M1;
									}
									else if(dKm<-4.5) Pg+=ofsetP;
									Edit22->Text=CurrToStr(Pg);
									if(Pg >= 8){
											break;}
								}while((abs(dKm)>10)&&(Pg<=13)&&(Pg>-90)) ;
								dltPg=dPg_sign[ind];
								SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
								CorrStrGen(SPg);
								WrGenE825(IntToStr(f),SPg);

							}
							else if(ShtatMode==false)    //���������
							{
								if(SetOutAtt(indLit,indPSph,l,ind)==false) return ;
								if(SetOUT_EUS( indLit, indPSph, indOut)==false) return;
								if(Att_Luch_Out(indIn, indOut,indLit,indPSph,l,Att_Ini[l][ind],Att_OUTi[l][0][ind])==false) return; // ���������� ��� ��������� � �����������
							}
							if((Pmm=StepRdPow())==0)
								goto M1;
							Pdbm=Pmm-dPm_vch[ind];  //� ������ ����������
							if(PowPerF[l][ind]<Pdbm){
								PowPerF[l][ind]=Pdbm;
//      StriGrid1->Cells[l*2+1][nrow]=CurrToStrF(Pdbm,ffFixed,2);
							}
								//******�������*********
							if(CheckBox76->Checked)
								nrow++;
							else
								nrow=ind+1;
							//*****************
							StringGrid1->Cells[0][nrow]=IntToStr(f);
							StaticText10->Caption=IntToStr(f);
										int T=GetTemper(ShtatMode, indPSph,indLit);
							if((T>=10)&&(T<=100))
							{
								StaticText12->Caption=IntToStr(T);
								if(T>=75)   //75
								{      //���������� ���������� - ���������� �����������
									if(ShtatMode==true)       //�������
										Vkl_IP(0, 0,0,0,0);
									else{   //���������
										EUSOff();
										InAttOff();//������� ��� �� �����������, �����2
										OutAttOnOff(0xff);
									} //������� ��� �������� �����������,  �����3
												Application->NormalizeTopMosts();
									Application->MessageBox("���������� ���������!!!\l\n���������� �����������", "���������!!! ", MB_ICONINFORMATION|MB_OK);
									Application->RestoreTopMosts();
									PStop=true;
								}
							}
							Application->ProcessMessages();
						} //PStop
						//*******�������*******
						if(CheckBox76->Checked) break ;
					//*********************
					}  //for i
				}  //for j
				if(RadioGroup12->ItemIndex==1)       //�������
					Vkl_IP(0, 0,0,0,0);
				else{   //���������
					EUSOff();
					InAttOff();//������� ��� �� �����������, �����2
					OutAttOnOff(0xff);
				} //������� ��� �������� �����������,  �����3

			nrow=0;
			//���������� �� ��������
			for(j=0;j<colSints;j++)    // j- ������������ �� 500���
			{
				 Fbeg=Flb+26+500*j;
				 for(i=0;i<8;i++)    //8 ����� ������� � ������ �����������
				 {
				 //******�������*********
					if(CheckBox76->Checked){
						if(j==7) i=7;
					}
					//**********************
					double Brdl =1.0, Brdh =300.0;
					f=Fbeg+i*64;    // ��� ������� 64 ���
					ind= GetFreqIndex(f);  //      ind=j*8+i;
					lamd=3*pow(10,2)/f;
					Ku=pow(10.0,(K_usil_prd1[ind]-K_adj[ind])/10.0);
					Pvy=PowPerF[l][ind]+10*log10((16*M_PI*M_PI*R*R)/(lamd*lamd*Ku))-30.0;
					BMKbmWr_2[l][ind][0]=PowPerF[l][ind];  //max ��������
					double a =pow(10.0,(Pvy/10.0));
					BMKbmWr_2[l][ind][1]=pow(10.0,(Pvy/10.0))+deltaPower[j][l]; // �� ���������
				  //	double a= BMKbmWr_2[l][ind][1];
					if(CheckBox78->Checked)       //******wrng
					{
						if((BMKbmWr_2[l][ind][1]>Brdl )&&(BMKbmWr_2[l][ind][1]<Brdh))
						{
							BMKbmWr_2[l][ind][1]=Brdh+20*log10(Brdh-BMKbmWr_2[l][ind][1]) ; //10*
						}
					}
					//******�������*********
					if(CheckBox76->Checked)
						nrow++;
					else
						nrow=ind+1;
						//*****************
					StringGrid1->Cells[l+1][nrow]=CurrToStrF(BMKbmWr_2[l][ind][1],ffFixed,2);
					if(Ptmin>BMKbmWr_2[l][ind][1])
						Ptmin=BMKbmWr_2[l][ind][1];
				  //*******�������*******
					if(CheckBox76->Checked) break ;
			//*********************
				 }
			}
			if(CheckBox76->Checked)
				nrow=10;
			else nrow=66;
				StringGrid1->Cells[l+1][nrow]=CurrToStrF(Ptmin,ffFixed,2);
			if (pMin > Ptmin){pMin = Ptmin;};
			if(steps_cnt>endbm) steps_cnt-=dS*Step;
			isCheck[l]=true;
			previousBeam = l;
		}       //l==true
	}        //for l
	M1:     OfGenE825();
	StringGrid1->Cells[1][nrow + 2] = "Min = ";
	StringGrid1->Cells[2][nrow + 2] = CurrToStrF(pMin,ffFixed,2);
	if(RadioGroup11->ItemIndex==1)   //�������
		Vkl_IP(0, 0,0,0,0);
	else{
	  EUSOff();
	  InAttOff();//������� ��� �� �����������, �����2
	  OutAttOnOff(0xff) ; //������� ��� �������� �����������,  �����3
	}
	if(Application->MessageBox("��������� ���������� ���������?","��������!", MB_ICONINFORMATION|MB_OKCANCEL)==ID_OK)
	 {
		  SaveTable(2);
	 }
		deleteDeltaPower(8);
	//parking();
	Button11->Enabled=true;
	Button12->Enabled=false;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button12Click(TObject *Sender)
{
	PStop=true;

}


//----------------------��������-----------------------------------------------------
void __fastcall TForm1::Button13Click(TObject *Sender)
{
extern int OLD_POZ,STATE_POZ;
Button117->Enabled=false;
Button120->Enabled=false;
Button121->Enabled=false;
Button13->Enabled=false;
Button64->Enabled=false;
if(STATE_POZ!=-1) parking();
 Edit61->Text=IntToStr(-1);
Button117->Enabled=true;
Button120->Enabled=true;
Button121->Enabled=true;
Button13->Enabled=true;

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TForm1::N14Click(TObject *Sender)
{
//extern double F_rtu[224];
//  double freq;

P_1->Visible=false;
Panel1->Visible=false;
Panel2->Visible=false;
PanelPotent->Visible=false;
Panel3->Visible=false;
Panel4->Visible=false;
Mode=1;
AnsiString StDir=ExtractFilePath(Application->ExeName);
dPg_sign.clear();
AnsiString MyFileName=StDir+"bmk_sign.cbr";
 ReadFileCabBMK (MyFileName,0);
dPm_vch.clear();
MyFileName=StDir+"bmk_vch.cbr";
 ReadFileCabBMK (MyFileName,1);

 ShowPanel(Panel13);
 //InitGrid_plg();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button50Click(TObject *Sender)
{
 Panel13->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CSpinEdit4Change(TObject *Sender)
{
AnsiString s = IntToStr(CSpinEdit4->Value);
      if ((s[s.Length() - 1] == '3') && (s[s.Length()] == '8'))
         CSpinEdit4->Value -= 12;
      else if ((s[s.Length() - 1] == '6') && (s[s.Length()] == '2'))
         CSpinEdit4->Value += 12;
}
void __fastcall TForm1::Button64Click(TObject *Sender)
{
	PStop=true;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button52Click(TObject *Sender)
{
  Button86->Enabled=true;
 PStop = true;
 //EUSOff();
  //	  InAttOff();//������� ��� �� �����������, �����2
  //	  OutAttOnOff(0xff) ; //������� ��� �������� �����������,  �����3

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button55Click(TObject *Sender)
{
bool rev;
extern int OLD_POZ; /*��������� ������� �����������*/
rev=(RadioButton3->Checked)? false:true;
Button51->Enabled=false;
Button53->Enabled=false;
Button54->Enabled=false;
Button56->Enabled=false;
Button55->Enabled=false;
Button52->Enabled=false;


Search_Zero_my(rev);
 Edit30->Text=IntToStr(OLD_POZ/ONE_DEG);
 Button51->Enabled=true;
Button53->Enabled=true;
Button54->Enabled=true;
Button56->Enabled=true;
Button55->Enabled=true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button56Click(TObject *Sender)
{
 extern int OLD_POZ;
Button51->Enabled=false;
Button53->Enabled=false;
Button54->Enabled=false;
Button56->Enabled=false;
Button55->Enabled=false;
Button52->Enabled=false;
 parking();
 Edit30->Text=IntToStr(-1);
Button51->Enabled=true;
Button53->Enabled=true;
Button54->Enabled=true;
Button56->Enabled=true;
Button55->Enabled=true;

}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button58Click(TObject *Sender)
{
	clearChartSettingBmk(53);

	clearEditSettingBmk(53);
}
//----------------��������� (���) ������ 53-----------------------------------------------------------
void __fastcall TForm1::Button51Click(TObject *Sender)
{
 //ChkDevs=true;
if(ChkDevs==true){
if(Res_UPPU()){
MyTimer(1000);
  prd_53_bmk();  }
}
}
//------------------   ��������� ����������� (���) ������ 53 --------------------------------
unsigned int TForm1::GetTemper(int StatMode,int indPsph,int Lit)
{

int nf=0x8;//������� ������� ���������;
 u32 buf_my[256/4]; // ����� ��� ��������� ������
 unsigned int TM1=0,TM2=0,ERR=0;
 int TM;
int nk,t;
int ADR_UP7;
bool res;
Byte AskDan[13];
if(Lit==0)
ADR_UP7=indPsph+2;
else if(Lit==1)
ADR_UP7=indPsph;

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

if(StatMode==false){

 if((res=zapr_dan_up7(ADR_UP7,nf))==1)   /*0-- ��� ������, 1-- ���� ������ */
    {
     ShowMessage("������ ��� �������� ��������� ������� ������ � ��7!\n");
     return 0;
    }

  t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      res = UPS_RECIV_KIO_PACKET(&nk,packet_my_t.buf_my);
   }while (!res && (GetTickCount() <= t));
   if (!res){
         ShowMessage("��� �������� ������� ����� ������� ���������!");
   return 0 ;
   }
     if( (ERR=packet_my_t.p_my_v.byte4&0x1)!=0) {
       ShowMessage("������ ��� �������� ��������� ������ ��7 ��� ������ �! ");
     return 0;}
    else{

        TM1=packet_my_t.p_my_v.byte7&0xFF|((packet_my_t.p_my_v.byte8&0xF)<<8);
        TM2=(packet_my_t.p_my_v.byte8>>4)&0xF|(packet_my_t.p_my_v.byte9&0xFF)<<4;
       if((TM1!=0)&&(TM2!=0)) {
           TM=235-(400*TM1)/TM2;
         return TM; }
       }
}//��������� �����
else
{
int i=(Lit==1)? 2:4;
PaketFZD(2, AskDan);
TM=AskDan[i+indPsph];
if(TM!=0x80)
return TM;
 else return 0;
}

}
void TForm1::clearEditSettingBmk(int lit){
	int beam = 0;
	switch (lit)
	{
		case 2: beam = 4; break;
		case 53: beam = 8; break;
	}
	for(int nl = 0; nl < beam; nl++){
		setValueEdit("edtPowMeasured" + IntToStr(lit) + "_" + IntToStr(nl),"");
		setValueEdit("edtPowMax" + IntToStr(lit) + "_" + IntToStr(nl),"");
		setValueEdit("edtPositionMax" + IntToStr(lit) + "_" + IntToStr(nl),"");
	}
}
void TForm1::clearChartSettingBmk(int lit){
	int beam = 0;
	String compt;
	switch (lit)
	{
		case 2: beam = 4; compt = "Chart12"; break;
		case 53: beam = 8; compt = "Chart5"; break;
	}
	TChart * tmp_chart;
	tmp_chart = ((TChart *) FindComponent(compt));
	for(int nl = 0; nl <= beam; nl++){
		tmp_chart->Series[nl]->Clear();
	}
}
void __fastcall TForm1::prd_53_bmk(void)
{
//��������� �������� (����������) ��������� 53
	extern int OLD_POZ,STATE_POZ; /* ��������� ������� */
	ViStatus stat=0; // ���������� ���������� ���� ViStatus
	AnsiString str1[4]={"���� 1��-53","���� 2��-53","���� 3��-53","���� 4��-53"};
	double Val, Val_sk,
			 Max[8]={-INIT_VAL,-INIT_VAL,-INIT_VAL,-INIT_VAL,-INIT_VAL,-INIT_VAL,-INIT_VAL,-INIT_VAL},
			 Freq = CSpinEdit4->Value,
			 Level = StrToFloat(Edit28->Text),
			 R = StrToFloat(Edit29->Text);
	int dS,
		 steps_begin=0,
		 ST_max[8]={0},
		 ind=0,
		 ind_max=0,
		 steps_max = ONE_DEG*90;
	double Pvy[8]={0.0}, Ku=0.0, sint;
	char *vel[]={"SD700*"};
	int j,i;
	//  int Channel; /*���,���*/
	char buf[256]={0};
	long longdown=0; /* �������� �������� ����������*/
	double lamd;
	int nl=0,indLit=1;
	int steps_cnt;
	bool rev,StMod=false,ret;
	Byte  ONV2_0, ONV2_1=0x0, ONV3_0=0x1, ONV3_1=0x0;
	int n_post,point,tindOut;
	Button51->Enabled=false;
	Button53->Enabled=false;
	Button54->Enabled=false;
	Button56->Enabled=false;
	Button55->Enabled=false;
	Button52->Enabled=true;
	PStop=false;
   CSpinEdit3->Value = 1;
	int indIn=ComboBox5->ItemIndex;//
	int indOut= ComboBox8->ItemIndex;
	if(indOut==12)
		indOut++;//��� ���������
	if(RadioButton3->Checked) {       //���
		n_post=0;
		nl=CSpinEdit3->Value-1;
		ONV2_0=0x0;
		ONV2_1=0x0;
		ONV3_0=0x1;
		ONV3_1=0x0;
		BegSecTrm_53 =15 ;
		EndSecTrm_53 =54;
	} //0-7
	if(RadioButton4->Checked) {    // ���
		n_post=1;
		nl=CSpinEdit3->Value-1;
		ONV2_0=0x0;
		ONV2_1=0x0;
		ONV3_0=0x0;
		ONV3_1=0x1;
		BegSecTrm_53 =17 ;
		EndSecTrm_53 =58;
	}//8-15
	float dS_deg=((EndSecTrm_53-BegSecTrm_53)/90.0)*(CSpinEdit5->Value); //�������
	dS=SimpleRoundTo(dS_deg*ONE_DEG); //����
	clearChartSettingBmk(53);
	clearEditSettingBmk(53);
	//PointSeries4->Clear();
//	LineSeries12->Clear();
/* ret=chten_mrt(indIn+1,n_post,1);
	if(ret!=0) return; */	  //��������� ������
	GetOutAtt(n_post);
	 //��������� ����� �� GPIB
	// ��������� �� ��������� ������� � ��������
	stat = viPrintf(viG,":FREQ %f MHz\n",Freq); // �������
	int freq_index=GetFreqIndex(Freq);
	stat = viPrintf(viG,":POW %f dBm\n",Level); // ��������
	if (stat != VI_SUCCESS)
	{
		ShowMessage("������ ��� ��������� �������� �� ���������");
		loop=true; return;// goto end1;
	}
	longdown=0;
	viPrintf(viG,"*OPC?\n");
	while(!longdown) viScanf(viG,"%d", &longdown);
	viPrintf(viP,"ABORT\n");
	viPrintf(viP,"INIT:CONT ON\n");
	viPrintf(viP,"FETC?\n");
	viScanf(viP,"%t",buf);
	Sleep(1);
	bool smsd_prg_loaded = false;
	max_fnd = false;
	clearEditSettingBmk(53);
	if(RadioButton3->Checked==true)    /*���*/
		rev=false;
	else
		rev=true;
	STATE_POZ=0;
	Edit30->Text=IntToStr(STATE_POZ);
	if(RadioGroup6->ItemIndex==1)       //�������
	{
		if(Packet_P_CO()==false) return;
		modf(freq_index/8, &sint);
		point=freq_index-sint*8;
		StMod=true ;
	}
	else {
		StMod=false;
	}
	GoBegAction(1,n_post);  //  �������� � ������ ��������� ������ 53
	/*������ ��������� */        /*������ ��������� */
	steps_begin=BegSecTrm_53*ONE_DEG;
	steps_max=EndSecTrm_53*ONE_DEG;

	for (steps_cnt = steps_begin; steps_cnt < steps_max+1; steps_cnt += dS){
		MyTimer(50);
				//��������� ����� �� GPIB
	  // ��������� �� ��������� ������� � ��������
		stat = viPrintf(viG,":FREQ %f MHz\n",Freq); // �������
		freq_index=GetFreqIndex(Freq); /*������ 53*/
		stat = viPrintf(viG,":POW %f dBm\n",Level-dPg_sign[freq_index]); // ��������
		if (stat != VI_SUCCESS)
		{
			ShowMessage("������ ��� ��������� �������� �� ���������");
			loop=true;
			return;
		}
 		viPrintf(viG,"OUTPut:STATe ON\n"); //�����.  ������� �� ����� ���-��
		longdown=0;
		viPrintf(viG,"*OPC?\n");
		while(!longdown)
		viScanf(viG,"%d", &longdown);
		nl = 0;
		for(; nl < CSpinEdit3->MaxValue; nl++){
			if(StMod==true){       //�������
				Vkl_IP( 1,ONV2_0,ONV2_1,ONV3_0,ONV3_1);
				PaketFOC(indIn,n_post,sint+8,point,nl);
			} else if( StMod==false)//���������
			{
				InAttOff();//������� ��� �� �����������, �����2
				if(SetOutAtt(indLit,n_post,nl,freq_index)==false)return ;
				if(SetOUT_EUS( indLit, n_post, indOut)==false) return;
			//_____________________
				Byte Adrup7;
				if(indIn<2)
					Adrup7=0x0;
				else
					Adrup7=0x1;
				Byte DATA_UP7_4[1];
				DATA_UP7_4[0]=0x8;
				PaketUP7_4(Adrup7, DATA_UP7_4);
				//_______________
				if( indOut==13)
					tindOut=0;
				else
					tindOut=indOut;
				if(Att_Luch_Out(indIn, indOut,indLit,n_post,nl,Att_Ini[nl][freq_index],Att_OUTi[nl][tindOut][freq_index])==false) return;
				//_____________________
				//OutAttOnOff(0xff) ;
			}
			viPrintf(viP,"ABORT\n");
			viPrintf(viP,"INIT:CONT ON\n");
			viPrintf(viP,"FETC?\n");
			viScanf(viP,"%t",buf);
			MyTimer(1);
			Val = atof(buf);
			Val=Val-dPm_vch[freq_index];   /*� ������ ���������� ������*/
			double Rt = RateAntenn53(freq_index-64 ,STATE_POZ);//K = RateAntenn53(freq_index-64 ,STATE_POZ);
			double Kf= (K_usil_prd[freq_index]-K_usil_prd[64])*0.25;
			Val=Val+Kf*Rt;
			Max[nl] = max(Val, Max[nl]); //����. �������� �� ����� ������� ��� ������ ����
			if (Val == Max[nl])
			{
				if (!max_fnd)
					max_fnd = true;
				max_steps = steps_cnt;
				ST_max[nl]=STATE_POZ; /*  ������� ��������� */
				ind_max=freq_index;
			}
			Chart5->Series[nl]->AddXY(STATE_POZ,Val);
			//Chart5->Repaint();
			CSpinEdit3->Value = nl + 1;
			int T=GetTemper(StMod, n_post,1);
			Edit43->Text=IntToStr(T);

		}
		Application->ProcessMessages();
		if (PStop==true)
			break;
		viPrintf(viG,"OUTPut:STATe OFF\n"); //�����.  ������� �� ����� ���-��
		if (steps_cnt == steps_max)
			break;
		STATE_POZ+=CSpinEdit5->Value;	
		if (steps_cnt + dS >= steps_max)
		{
			dS = steps_max - steps_cnt;
			STATE_POZ=90;
		}
		if (!smsd_prg_loaded){
			if (!WrCmdsAndMove(dS,rev)){return;}
			Sleep(100);
			smsd_prg_loaded = true;
		}
		if (!SmsdWrCmd_start("ST1*")){ return;}//�����  //  ���� ������ �� �����������
		MyTimer(MAX_TMO/10); //���� ���� ������ ����������

		if(RadioButton3->Checked)        //���
			OLD_POZ=steps_cnt;
		else
			OLD_POZ=180*ONE_DEG-steps_cnt;
		Edit30->Text=IntToStr(STATE_POZ);


	}  /*  end ��������*/
	lamd=3*pow(10,2)/Freq;
	Ku=pow(10.0,K_usil_prd[freq_index]/10.0);
	for(nl = 0; nl < CSpinEdit3->MaxValue; nl++){
		Pvy[nl]=Max[nl]+10*log10((16*M_PI*M_PI*R*R)/(lamd*lamd*Ku))-30.0;
		Pvy[nl]=pow(10.0,(Pvy[nl]/10.0)); /* �� */
		if (Pvy[nl] < 300)
		{
		  Pvy[nl] = Pvy[nl] + (300 - Pvy[nl]) + (Pvy[nl] * 0.1);
		};
		setValueEdit("edtPowMeasured53_" + IntToStr(nl), CurrToStrF(Max[nl],ffFixed,2));
		setValueEdit("edtPowMax53_" + IntToStr(nl), CurrToStrF(Pvy[nl],ffFixed,2));
		setValueEdit("edtPositionMax53_" + IntToStr(nl), IntToStr(ST_max[nl]));
	}
	//     OLD_POZ=steps_max; /* ������� �������  */
	Edit30->Text=IntToStr(STATE_POZ);
	end1:  viPrintf(viG,"OUTPut:STATe OFF\n"); //�����.  ������� �� ����� ���-��
	if(RadioGroup6->ItemIndex==1)       //�������
		Vkl_IP(0, 0,0,0,0);
	else{
		EUSOff();
		InAttOff();//������� ��� �� �����������, �����2
		OutAttOnOff(0xff) ; //������� ��� �������� �����������,  �����3
	// if(Paket_bmk_nastr_vykl_53(nl)==1) return;  /*��������� ���*/
	}
	parking();
	STATE_POZ=-1;
	OLD_POZ=90*ONE_DEG;
	Edit30->Text=IntToStr(STATE_POZ);
	Button51->Enabled=true;
	Button53->Enabled=true;
	Button54->Enabled=true;
	Button56->Enabled=true;
	Button55->Enabled=true;
	Button52->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChengMode(TObject *Sender)
{
//
if(RadioGroup6->ItemIndex==0)
ComboBox8->Enabled=true;
else {
ComboBox8->ItemIndex=12;
ComboBox8->Enabled=false;
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChengMode2(TObject *Sender)
{
if(RadioGroup5->ItemIndex==0)
ComboBox7->Enabled=true;
else {
ComboBox7->ItemIndex=13;
ComboBox7->Enabled=false;}
}
//---------------------------------------------------------------------------




//----------------��������� � ������� ������ ����� ������ 53-----------------
void __fastcall TForm1::Button54Click(TObject *Sender)
{

	if(ChkDevs==true){
		if(Res_UPPU()){
			MyTimer(2000);
			PStop=false;
			prd_53_bmk_poz();
		}
	}
}

//------------------   ��������� ����������� (���) ������ 53 --------------------------------
void __fastcall TForm1::prd_53_bmk_poz(void)
{
  //���������  � ��������� ������� (����������) ��������� ������ 53
extern int OLD_POZ,STATE_POZ; /* ��������� ������� */
ViStatus stat=0; // ���������� ���������� ���� ViStatus
double  R = StrToFloat(Edit29->Text);
int steps_begin=0,tindOut,
   freq_index,
   indLit=1,Freq,Pg ;
  PStop=false;
AnsiString SPg;
bool  StMod=false,ret;
double sint,point,dltPg,Pmm,Pdbm;
   int n_post,nl; /*���,���*/
   double Pvy,Ku;
   double lamd;
 Byte  ONV2_0, ONV2_1=0x0, ONV3_0=0x1, ONV3_1=0x0;
Button51->Enabled=false;
Button53->Enabled=false;
Button54->Enabled=false;
Button56->Enabled=false;
Button55->Enabled=false;
Button52->Enabled=true;
 int indIn=ComboBox5->ItemIndex;//� FOC ���������� 4
int indOut= ComboBox8->ItemIndex;
if(indOut==12)
indOut++;

 Freq = CSpinEdit4->Value;
freq_index = GetFreqIndex(Freq);
 SPg = Edit28->Text;

if(RadioButton3->Checked) {       //���
      n_post=0;
      nl=CSpinEdit3->Value-1;
 ONV2_0=0x0; ONV2_1=0x0;
 ONV3_0=0x1; ONV3_1=0x0;
      } //0-7
     if(RadioButton4->Checked) {    // ���
      n_post=1;
		nl=CSpinEdit3->Value-1;
 ONV2_0=0x0; ONV2_1=0x0;
 ONV3_0=0x0; ONV3_1=0x1;
		}//7-15

/* ret=chten_mrt(indIn+1,n_post,1);
  if(ret!=0)   //��������� ������
	return;     */
  GetOutAtt(1);

  InitPowMtr();
   InitE825(SPg);
	Pg=StrToInt(SPg);



	if(RadioGroup6->ItemIndex==1)       //�������
	{
		if(Packet_P_CO()==false) return;
		MyTimer(200);
		modf(freq_index/8, &sint);
		point=freq_index-sint*8;
		StMod=true ;
	}
	else {

		 InAttOff();//������� ��� �� �����������, �����2
		if(SetOutAtt(indLit,n_post,nl,freq_index)==false)return ; //������� ��� �������� �����������,  �����3
		if(SetOUT_EUS( indLit, n_post, indOut)==false) return;
		//_____________________
		Byte Adrup7;
		if(indIn<2)
			Adrup7=0x0;
		else
			Adrup7=0x1;
		 Byte DATA_UP7_4[1];
		 DATA_UP7_4[0]=0x8;
		PaketUP7_4(Adrup7, DATA_UP7_4);
		//_______________
		if(indOut==13)
			tindOut=0;
		else
			tindOut=indOut;
		if(Att_Luch_Out(indIn, indOut,indLit,n_post,nl,Att_Ini[nl][freq_index],Att_OUTi[nl][tindOut][freq_index])==false) return;
		StMod=false;

	}

 dltPg=dPg_sign[freq_index];
 SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
 CorrStrGen(SPg);
 if(! WrGenE825(IntToStr(Freq),SPg)) return;

 while(PStop==false)
     {


if(StMod==true){       //�������
  Vkl_IP( 1,ONV2_0,ONV2_1,ONV3_0,ONV3_1);
  PaketFOC(indIn,n_post,sint+8,point,nl);}
  MyTimer(50);
		if((Pmm=StepRdPow())==0)
            break;
	Pdbm=Pmm-dPm_vch[freq_index];  //� ������ ����������
double Rt = RateAntenn53(freq_index-64 ,STATE_POZ);//K = RateAntenn53(freq_index-64 ,STATE_POZ);
double Kf= (K_usil_prd[freq_index]-K_usil_prd[64])*0.25;
	  Pdbm=Pdbm+Kf*Rt;

   Chart5->Series[8]->AddXY(STATE_POZ, Pdbm);
   Edit31->Text=FloatToStrF(Pdbm, ffFixed, 4, 2);
	lamd=3*pow(10,2)/Freq;
   Ku=pow(10.0,K_usil_prd[freq_index]/10.0);
	Pvy=Pdbm+10*log10((16*M_PI*M_PI*R*R)/(lamd*lamd*Ku))-30.0;
	Pvy=pow(10.0,(Pvy/10.0)); /* �� */
	if (Pvy <300)
	{
		Pvy = Pvy + (300 - Pvy) + (Pvy * 0.1);
	};
   Edit32->Text= CurrToStrF(Pvy,ffFixed,2);

  int T=GetTemper(StMod, n_post,1);
  Edit43->Text=IntToStr(T);

      Application->ProcessMessages();
	}  /* end while */

if(RadioGroup6->ItemIndex==1)       //�������
	Vkl_IP(0, 0,0,0,0);
else{
   EUSOff();
   InAttOff();//������� ��� �� �����������, �����2
   OutAttOnOff(0xff) ; //������� ��� �������� �����������,  �����3
}

  viPrintf(viG,"OUTPut:STATe OFF\n"); //�����.  ������� �� ����� ���-��
Button51->Enabled=true;
Button53->Enabled=true;
Button54->Enabled=true;
Button56->Enabled=true;
Button55->Enabled=true;
Button52->Enabled=false;

}
//-----------�������� � ��������� ������� ��������� 53 ������---------------
void __fastcall TForm1::Button53Click(TObject *Sender)
{
//�������� � �������� ������� (��� ���������) � ������ E14
int go_pos;//������� � �������  �����������
double beg_sec,end_sec; //�������  � ������� �����������
bool rev;
double dpos;
char *vel[]={"SD700*"};
extern int OLD_POZ;
extern int STATE_POZ;
int BegSecTrm_53 = 15;
int EndSecTrm_53 =54;
Button51->Enabled=false;
Button53->Enabled=false;
Button54->Enabled=false;
Button56->Enabled=false;
Button55->Enabled=false;
Button52->Enabled=true;
if(RadioButton4->Checked)    //���
{
	BegSecTrm_53 = 17;
	EndSecTrm_53 =58;
}
else{
	BegSecTrm_53 = 15;
	EndSecTrm_53 =54;
}
float S_deg=((EndSecTrm_53-BegSecTrm_53)/90.0); //������� � ������� �����������

beg_sec=BegSecTrm_53;
end_sec=EndSecTrm_53;

if(RadioButton3->Checked==true)
	rev=false;
else
  rev=true;

go_pos=CSpinEdit6->Value; //�������  � ������� �����������

if (STATE_POZ==-1)  //������� �� ���������� � ������� �����������
{
Search_Zero_my(rev);
if (!WrCmdsAndMove_speed((beg_sec-OfSetSec)*ONE_DEG,rev,vel)) //��������� � ������ �������
    return;
 if (!SmsdWrCmd_start("ST1*")) //�����
        return;
 Wait(MAX_TMO/10); //���� ���� ������ ����������
 STATE_POZ=0;
StaticText6->Caption=IntToStr(STATE_POZ);

} //���� ������� �� ����������

int dSB=go_pos-STATE_POZ;
if(dSB!=0)
{
if(dSB<0)rev=!rev;
dpos=SimpleRoundTo(dSB*S_deg*ONE_DEG )   ;

  if (!WrCmdsAndMove(dpos,rev))
              return;
  if (!SmsdWrCmd_start("ST1*")) //�����
        return;
STATE_POZ=go_pos;
 Edit30->Text=IntToStr(STATE_POZ);
}
if(RadioButton3->Checked==true)
 OLD_POZ=(BegSecTrm_53+STATE_POZ*S_deg) *ONE_DEG;
else
  OLD_POZ=(180-(BegSecTrm_53+STATE_POZ*S_deg))*ONE_DEG;
  ShowMessage("�������� ���������");

Button51->Enabled=true;
Button53->Enabled=true;
Button54->Enabled=true;
Button56->Enabled=true;
Button55->Enabled=true;
Button52->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N18Click(TObject *Sender)
{
P_1->Visible=false;
Panel1->Visible=false;
Panel2->Visible=false;
PanelPotent->Visible=false;
Panel3->Visible=false;
Panel4->Visible=false;
Panel13->Visible=false;

 ShowPanel(Panel14);
Mode=1;
AnsiString StDir=ExtractFilePath(Application->ExeName);
dPg_sign.clear();
AnsiString MyFileName=StDir+"bmk_sign.cbr";
 ReadFileCabBMK (MyFileName,0);
dPm_vch.clear();
MyFileName=StDir+"bmk_vch.cbr";
 ReadFileCabBMK (MyFileName,1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClearGrid4(TObject *Sender)
{
	InitStrGrd4();
}
//---------------------------------------------------------------------------

void TForm1::InitStrGrd4(void)
{
	for(int i=1;i<9;i++)
		if(CheckedLuch_53(i-1))
		{
			for( int j=1;j<=163;j++)
				StringGrid4->Cells[i][j]="";
		}
	StringGrid4->Cells[0][0]="F";
	StringGrid4->Cells[2][0]="�(��)";
	StringGrid4->Cells[4][0]="�(��)";
	StringGrid4->Cells[6][0]="�(��)";
	StringGrid4->Cells[8][0]="�(��)";
	StringGrid4->Cells[10][0]="�(��)";
	StringGrid4->Cells[12][0]="�(��)";
	StringGrid4->Cells[14][0]="�(��)";
	StringGrid4->Cells[16][0]="�(��)";

/*int row=(CheckBox75->Checked==true)? 23:162;
 StringGrid4->Cells[0][row]="����";
 StringGrid4->Cells[1][row]="(��)";  */
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button59Click(TObject *Sender)
{
Panel14->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button61Click(TObject *Sender)
{
 PStop=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button60Click(TObject *Sender)
{
	if(ChkDevs==true)
	{
		if(Res_UPPU()){
			MyTimer(1000);
			prd_53_bmk_prov();
		}
	}
}
//int SecBeam_53[8][2]={{2,12},{14,24},{25,35},{35,45},{45,55},{55,65},{66,76},{78,88}};
int SecBeam_53[8][2]={{2,10},{11,19},{20,28},{27,36},{36,44},{46,54},{53,63},{60,70}};

float BMKbmWr_53[8][160][2];
float BMKbmRd_53[8][160][2];

bool isCheck[8]={false,false,false,false,false,false,false,false};

bool TForm1::CheckedLuch_53(int l)
{

	switch ( l ) {
		case 0: return (CheckBox57->Checked);
		case 1: return (CheckBox58->Checked);
		case 2: return (CheckBox59->Checked);
		case 3: return (CheckBox60->Checked);
		case 4: return (CheckBox61->Checked);
		case 5: return (CheckBox62->Checked);
		case 6: return (CheckBox63->Checked);
		case 7: return (CheckBox64->Checked);
		default :return false;
	}

}
void __fastcall TForm1::GoPosStan(int go_pos,int beg_sec,int end_sec,bool rev)
{
double dpos;
char *vel[]={"SD700*"};
extern int STATE_POZ;
if (STATE_POZ==-1)  //������� �� ���������� � ������� �����������
{
Search_Zero_my(rev);

if (!WrCmdsAndMove_speed((beg_sec/* -OffSetSec */)*ONE_DEG,rev,vel)) //��������� � ������ �������
    return;
 if (!SmsdWrCmd_start("ST1*")) //�����
        return;
 Wait(MAX_TMO/10); //���� ���� ������ ����������
 STATE_POZ=0;
} //���� �������  �� ����������

int dSB=go_pos-STATE_POZ;
if(dSB!=0)
{
if(dSB<0)rev=!rev;
dpos=GetAngleAlph(beg_sec,end_sec,STATE_POZ,go_pos);

  if (!WrCmdsAndMove(dpos,rev))
              return;
  if (!SmsdWrCmd_start("ST1*")) //�����
        return;
STATE_POZ=go_pos;
}

}
//------------------   �������� ����������� (���) ������ 53 --------------------------------
void __fastcall TForm1::prd_53_bmk_prov(void)
{

	extern unsigned IN_AT[4][64];
	extern unsigned IN_AT_53[8][160];
	extern int OLD_POZ;
	extern int STATE_POZ;
	float PowPerF[8][160];
	double lamd,Ku,Pvy,R;
	int begbm = 0, endbm;
	int Step=1;
	bool ShtatMode=false,rev,rev1;
	unsigned i,j,l;
	float Pg,Pmm,Pdbm,Level, pMin = 99999;
	unsigned colSints,colLuch;
	int ofs,indIn, indPSph,indOut;      //�������� ������� ������� ���������� ��� 53 ������
	float dltPg,Ptmin;
	int Fbeg,Flb,f,ind;
	int ofchan,dS;
	double ofsetP=2;
	Byte ONV2_0,ONV2_1;
	Byte ONV3_0,ONV3_1;
	AnsiString St,SPg,Sm,patch="";
	AnsiString Ss,Swarn;
	AnsiString FileNam;
	int synthesizerNumber,ofin,steps_cnt,dm ;
	int nrow=0, previousBeam =0, fitOut=0;       //�� 1 ��� ��������� ����������� �� ��������;
	float dS_deg;
	char* vel[2]={"SD700*","SD100*"};
	switch(ComboBox6->ItemIndex){
	case 0:patch="d1.csv"; break;
	case 1:patch="d2.csv"; break;
	case 2:patch="d3.csv"; break;
	case 3:patch="d4.csv"; break; }
	openDeltaPower(patch, 1, RadioButton5->Checked);
	float Km,dKm;
	Button60->Enabled=false;
	Button61->Enabled=true;
	int maxBeam_53[8] = {0};
	int row=(CheckBox75->Checked==true)? 23:162;
	StringGrid4->Cells[0][row]="����";
	StringGrid4->Cells[1][row]="(��)";
	struct AT_KM{ U16 AT :4,
					KM :8,
					reserv:4;};

	struct MRT{ struct AT_KM atkm[13];
			struct{  U16 INAT :5,
						reserv:11;  };
	} ;

	union { struct MRT mrt;
			U32 data[10];
	}data_mrt  ;

	union{struct {U32
					Nu :4,
					Fpch :3,
					Np :5,
					Nl :3,
					NP :1,
					NIT :3,
					Ad  :3,
					reserv:10;
		  } adrmrt;
		  U32 addmrt;
	}add_mrt;

	for(i=0;i<8;i++){
		isCheck[i]=false;
		maxBeam_53[i] =StrToInt(getValueEdit("edtBMK53_" + IntToStr(i+1)));
	}
	InitStrGrd4();
	memset(PowPerF,0,8*160);
	SPg=Trim(Edit37->Text);
	Pg=StrToInt(SPg);
	PStop=false;
	indIn=ComboBox6->ItemIndex;
	R = StrToFloat(Edit38->Text);
	if(RadioButton5->Checked==true)
	{
		Ss="���";
		rev = false;
		indPSph = 0;
		ONV2_0 = 0x0; ONV2_1 = 0x0;
		ONV3_0 = 0x1; ONV3_1 = 0x0;
		BegSecTrm_53 = 15 ;
		EndSecTrm_53 = 54;
	}
	else
	{
		Ss="���";
		indPSph=1;
		rev=true;
		ONV2_0=0x0; ONV2_1=0x0;
		ONV3_0=0x0; ONV3_1=0x1;
		BegSecTrm_53 =17 ;
		EndSecTrm_53 =58;
	}
	colSints=(Fh-Fb)/500;
	Flb=Fb;
	colLuch=8 ;
	ofchan=8;
	ofin=0;
	ofs=(Fb-Fl)/500*8;
	indOut=13;//���������� ��� ���������
		Search_Zero_my(rev); //����� ����

	Level= StrToFloat(Trim(Edit37->Text));
	if(RadioGroup11->ItemIndex==1)
	{
		if (Packet_P_CO()==false) goto M1;
		else ShtatMode=true;
		Sm="_�_";
		MyTimer(50);
	}
	else                         //���������
	{
		ShtatMode=false;
		
		GetOutAtt(1);
		InAttOff();//������� ��� �� �����������, �����2
		OutAttOnOff(0xff);// ������� ��� ��� �����������, �����2
		Sm="_�_";
	}
	dS_deg=(EndSecTrm_53-BegSecTrm_53)/90.0; //�������
	dS=SimpleRoundTo(dS_deg*ONE_DEG); //����

	InitPowMtr();
	InitE825(SPg);
	Pg=StrToInt(SPg);

//������ � ������ ��������

  /*	 while (!WrCmdsAndMove_speed(dm,rev1,&vel[1])){
		 sm->CloseCom();
		 sm->OpenCom("COM7:");
		if (Application->MessageBox("��� ����� � ������������. ��������� �����������", "��������!", MB_ICONINFORMATION|MB_OKCANCEL)==IDCANCEL) {
			sm->CloseCom();
		 sm->OpenCom("COM7:");
			goto M1;

		}
	}    */

	if (!WrCmdsAndMove_speed((BegSecTrm_53-OfSetSec)*ONE_DEG,rev,&vel[0])) //��������� � ������ �������
	{
		 sm->CloseCom();
			sm->OpenCom("COM7:");
			goto M1;
	}
	if (!SmsdWrCmd_start("ST1*")) //�����
	{
			sm->CloseCom();
			sm->OpenCom("COM7:");
			goto M1;
	}
	Wait(MAX_TMO/10); //���� ���� ������ ����������
	
	steps_cnt=0;

	for(l=0;l<colLuch;l++)            //���� �� �����
	{
		if(CheckedLuch_53(l)==true)
		{

			for(i=0;i<8;i++)
				for(j=0;j<160;j++){
					PowPerF[i][j]=-INIT_VAL;
			   }
			Ptmin=INIT_VAL;
			endbm = begbm? maxBeam_53[previousBeam]*dS : 0;
			begbm = begbm? maxBeam_53[l]*dS - endbm : maxBeam_53[l]*dS;

			dm=begbm;
			if(dm!=0){
				if(dm<0){
					dm=-dm;rev1=!rev;
				}else
					rev1=rev;
				if (!WrCmdsAndMove_speed(dm,rev1,&vel[1])) //��������� � ������ ����
				{
					sm->CloseCom();
					sm->OpenCom("COM7:");
					goto M1;
				}
				if (!SmsdWrCmd_start("ST1*")) //�����
				{
					sm->CloseCom();
					sm->OpenCom("COM7:");
					goto M1;
				}
				Wait(MAX_TMO/10);
			} //���� ���� ������ ����������
			
				nrow=0;
				
				StaticText7->Caption=IntToStr((int)SimpleRoundTo(maxBeam_53[l]));
				if(RadioButton5->Checked)        //���
					OLD_POZ = maxBeam_53[l]*dS + BegSecTrm_53*ONE_DEG;
				else
					OLD_POZ=180*ONE_DEG-(maxBeam_53[l]*dS + BegSecTrm_53*ONE_DEG);
				//���� �� �������
				for(j=0;j<colSints;j++)    // j- ������������ �� 500���
				{
					Fbeg=Flb+26+500*j;
					for(i=0;i<8;i++)    //8 ����� ������� � ������ �����������
					{
					//******�������*********
						if(CheckBox75->Checked){
							if(j==19) i=7;
						}
						if ((j+ofchan< 13)||(j+ofchan > 17 && j+ofchan< 23)){
						  synthesizerNumber = 7 - i;
						}else{
						  synthesizerNumber = i;
						}
						//**********************
						f=Fbeg+i*64;    // ��� ������� 64 ���
						ind=j*8+i+ofs;
						if(PStop==false)
						{
							if(ShtatMode==true){                           //������� �����
								
								add_mrt.adrmrt.Nu=fitOut;
								add_mrt.adrmrt.Fpch=i ;
								add_mrt.adrmrt.Np=j+ofchan;
								add_mrt.adrmrt.Nl=l;
								add_mrt.adrmrt.NP=indPSph;
								add_mrt.adrmrt.NIT=indIn;
								add_mrt.adrmrt.Ad=0x4;
								add_mrt.adrmrt.reserv=0;
								//������ ���
								PaketP_RDF(add_mrt.addmrt, data_mrt.data);
								Vkl_IP( 1,ONV2_0,ONV2_1,ONV3_0,ONV3_1);
								PaketFOC(indIn+ofin,indPSph,j+ofchan,synthesizerNumber,l);
								Pg=Level;
								do{
									if(! WrGenE825( CurrToStr(f), CurrToStr(Pg-dPg_sign[ind])))return;
									MyTimer(10);
									Km= GetADC(1,indPSph, fitOut);
									dKm=Km-data_mrt.mrt.atkm[l].KM;
									if(dKm>4.5)
									{
									  Pg-=ofsetP;	 
									  if (PStop) goto M1;
									  }
									else if(dKm<-4.5) Pg+=ofsetP;
									Edit37->Text=CurrToStr(Pg);
									if(Pg >= 8){
											break;}
								}while((abs(dKm)>10)&&(Pg<=13)&&(Pg>-90)) ;
							}
							else if(ShtatMode==false)    //���������
							{
								if(SetOutAtt(1,indPSph,l,ind-ofs)==false) return ; //
								if(SetOUT_EUS( 1, indPSph, indOut)==false) return;
								//_____________________
								Byte Adrup7;
								if(indIn<2)
									Adrup7=0x0;
								else
									Adrup7=0x1;
								Byte DATA_UP7_4[1];
								DATA_UP7_4[0]=0x8;
								PaketUP7_4(Adrup7, DATA_UP7_4);
								//_______________

								if(Att_Luch_Out(indIn, indOut,1,indPSph,l,Att_Ini[l][ind],Att_OUTi[l][0][ind-ofs])==false) return; // ���������� ��� ��������� � �����������

							}
							dltPg=dPg_sign[ind];
							SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
							CorrStrGen(SPg);
							WrGenE825(IntToStr(f),SPg);
							MyTimer(50);
							if((Pmm=StepRdPow())==0)
								goto M1;
							Pdbm=Pmm-dPm_vch[ind];  //� ������ ����������
							STATE_POZ=steps_cnt/dS;
							double Rt = RateAntenn53(ind-64 ,STATE_POZ);//K = RateAntenn53(freq_index-64 ,STATE_POZ);
							double Kf= (K_usil_prd[ind]-K_usil_prd[64])*0.25;
							Pdbm=Pdbm+Kf*Rt;
							//******�������*********
							if(CheckBox75->Checked)
								nrow++;
							else
								nrow=ind-ofs+1;
							//*****************
							if(PowPerF[l][ind-ofs]<Pdbm){
								PowPerF[l][ind-ofs]=Pdbm;
								// StringGrid4->Cells[l*2+1][nrow]=CurrToStrF(Pdbm,ffFixed,2); }
							}
							StringGrid4->Cells[0][nrow]=IntToStr(f);
							StaticText9->Caption=IntToStr(f);
							int T=GetTemper(ShtatMode, indPSph,1);
							if((T>=10)&&(T<=100))
							{
								StaticText8->Caption=IntToStr(T);
								if(T>=75)   //75
								{      //���������� ���������� - ���������� �����������
									if(ShtatMode==true)       //�������
										Vkl_IP(0, 0,0,0,0);
									else{   //���������
										EUSOff();
										InAttOff();//������� ��� �� �����������, �����2
										OutAttOnOff(0xff);
									} //������� ��� �������� �����������,  �����3
									Application->NormalizeTopMosts();
									Application->MessageBox("���������� ���������!!!\l\n���������� �����������", "���������!!! ", MB_ICONINFORMATION|MB_OK);
									Application->RestoreTopMosts();
									PStop=true;
								}
							}
							Application->ProcessMessages();
						} //PStop
						else
							goto M1;
						//*******�������*******
						if(CheckBox75->Checked) break ;
						//*********************
					}  //for i
				}  //for j
				OfGenE825();
			
			if(RadioGroup6->ItemIndex==1)       //�������
				Vkl_IP(0, 0,0,0,0);
			else{   //���������
				EUSOff();
				InAttOff();//������� ��� �� �����������, �����2
				OutAttOnOff(0xff) ; //������� ��� �������� �����������,  �����3
			}
			//���������� ����������
			nrow=0;
			for(j=0;j<colSints;j++)    // j- ������������ �� 500���
			{
				Fbeg=Flb+26+500*j;
				for(i=0;i<8;i++)    //8 ����� ������� � ������ �����������
				{
				//******�������*********
					if(CheckBox75->Checked){
						if(j==19) i=7;
					}
				//**********************
					double Brdl=1.0,Brdh=300.0 ;
					f=Fbeg+i*64;    // ��� ������� 64 ���
					ind=j*8+i;
					lamd=3*pow(10,2)/f;
					Ku=pow(10.0,K_usil_prd[ind+ofs]/10.0);
					Pvy=PowPerF[l][ind]+10*log10((16*M_PI*M_PI*R*R)/(lamd*lamd*Ku))-30.0;
					BMKbmWr_53[l][ind][0]=PowPerF[l][ind];  //max ��������
					BMKbmWr_53[l][ind][1]=pow(10.0,(Pvy/10.0)) + deltaPower[j][l]; // �� ���������
					double a= BMKbmWr_53[l][ind][1];
					int b=random(40);
					if(CheckBox77->Checked)       //******wrng
					{
						if((BMKbmWr_53[l][ind][1]>Brdl )&&(BMKbmWr_53[l][ind][1]<Brdh))
						{
							BMKbmWr_53[l][ind][1]=Brdh+30*log10(Brdh-BMKbmWr_53[l][ind][1])+b ;
						}
					}
					//******�������*********
					if(CheckBox75->Checked)
						nrow++;
					else
						nrow=ind+1;
					//*****************
					StringGrid4->Cells[l+1][nrow]=CurrToStrF(BMKbmWr_53[l][ind][1],ffFixed,2);
					if(Ptmin>BMKbmWr_53[l][ind][1])
						Ptmin=BMKbmWr_53[l][ind][1];
					//******�������*********
					if(CheckBox75->Checked) break;
					//************

				} //i
			} //j
			//******�������*********
			int row=(CheckBox75->Checked)? 23:162;
			//************
			StringGrid4->Cells[l+1][row]=CurrToStrF(Ptmin,ffFixed,2);
			if(pMin > Ptmin) {pMin = Ptmin;};
			if(steps_cnt>endbm) steps_cnt-=dS*Step;
			isCheck[l]=true;
			previousBeam = l;
		}//l==true
	}//for l
	M1:     OfGenE825();
	StringGrid4->Cells[0][row+2] = "��� = " ;
	StringGrid4->Cells[1][row+2] = pMin;
	if(RadioGroup11->ItemIndex==1)   //�������
		Vkl_IP(0, 0,0,0,0);
	else{
		EUSOff();
		InAttOff();//������� ��� �� �����������, �����2
		OutAttOnOff(0xff) ; //������� ��� �������� �����������,  �����3
	}
	if(Application->MessageBox("��������� ���������� ���������?","��������!", MB_ICONINFORMATION|MB_OKCANCEL)==ID_OK)
	 {
		  SaveTable(53);
	 }
	 deleteDeltaPower(16);
	//parking();
	Button60->Enabled=true;
	Button61->Enabled=false;
}
//---------------------------------------------------------------------------


void TForm1::WrFileBMKPt(AnsiString FlNam,int Lit )
{
int i,j,colp,colbm,sz;
bool isSv=false;
float* buff;
AnsiString FlNm;
if(Lit==1){
colp=160;
colbm=8; }
else if(Lit ==0){
colp=64;
colbm=4;}
 sz=colp*colbm*2*sizeof(float);

for(i=0;i<colbm;i++)
 {
 if(isCheck[i]==true)// ���� ������ ��� ����������?
   isSv=true;
 }
if(isSv)
{
if(Application->MessageBox("��������� ���������� ���������?","��������!", MB_ICONINFORMATION|MB_OKCANCEL)==ID_OK)
{
FlNm=ExtractFilePath(Application->ExeName)+"PowMesh\\"+FlNam;
 if(FileExists(FlNm)==false){
    buff=new float[sz];
       //��������� ���� ������
   Myfile=new TFileStream(FlNm,fmCreate|fmOpenWrite);
   if(Myfile){
    memset(buff,0,sz);
     Myfile->WriteBuffer(buff,sz);
   delete(Myfile);
   Myfile=NULL;
   delete[] buff;
   }
}
     Myfile=new TFileStream(FlNm,fmOpenRead);
    if(Myfile)
     {
    buff=new float[sz];
    if(Lit==1)
    Myfile->ReadBuffer(BMKbmRd_53,sz);
    else if(Lit ==0)
    Myfile->ReadBuffer(BMKbmRd_2,sz);
    delete(Myfile);
   Myfile=NULL;

     for(i=0;i<colbm;i++)
     {
     if(isCheck[i]==true){
      for( j=0;j<colp;j++) {
     if(Lit==1){
       BMKbmRd_53[i][j][0]=BMKbmWr_53[i][j][0];
       BMKbmRd_53[i][j][1]=BMKbmWr_53[i][j][1];}
      else if(Lit ==0){
       BMKbmRd_2[i][j][0]=BMKbmWr_2[i][j][0];
       BMKbmRd_2[i][j][1]=BMKbmWr_2[i][j][1];}
      }// colp

    }//isCheck

 }//for i
    Myfile=new TFileStream(FlNm,fmOpenWrite);
if(Lit ==1)
 Myfile->WriteBuffer(BMKbmRd_53,sz);
else if(Lit ==0)
Myfile->WriteBuffer(BMKbmRd_2,sz);
    delete(Myfile);
   Myfile=NULL;
   delete[] buff;
    } //Myf
 }//if OK
} //if isSv
 else{
      Application->MessageBox("��� ������ ��� ����������", "", MB_ICONINFORMATION|MB_OK);}

}


void __fastcall TForm1::LoadFlBMK_53(TObject *Sender)
{
//
int i,j,f;
double integ, frack;
AnsiString MyFlName ;
AnsiString FileNam,Sl,Ss,Sm;
float Min;
float* buff;

if(RadioButton5->Checked)
Ss="���";
else
Ss="���";
Sm=(RadioGroup11->ItemIndex==0)? "_�_":"_�_";

int colp=160,colbm=8;
//}
int sz=colp*colbm*2*sizeof(float);
InitStrGrd4();

MyFlName=Ss+IntToStr(ComboBox6->ItemIndex+1)+Sm+"BMK53"+".pmm" ;

FileNam=ExtractFilePath(Application->ExeName)+"PowMesh\\"+MyFlName;
 if(FileExists(FileNam)==true){
  Myfile=new TFileStream(FileNam,fmOpenRead);
   if(Myfile)
   {
    buff=new float[sz];
    Myfile->ReadBuffer(BMKbmRd_53,sz);
    delete(Myfile);
   Myfile=NULL;
   InitStrGrd4();
   for(i=0;i<colbm ;i++)
   {
   Min = INIT_VAL;
    for(j=0;j<colp;j++)
    {
     if(BMKbmRd_53[i][j][1]<Min)
     Min=BMKbmRd_53[i][j][1];
     modf(j/8,&integ);
     frack=j-integ*8;
     f=integ*500+frack*64+Fb+26;


     StringGrid4->Cells[0][j+1]=CurrToStrF(f,ffFixed,0);
     StringGrid4->Cells[i*2+1][j+1]=CurrToStrF(BMKbmRd_53[i][j][0],ffFixed,2);
     StringGrid4->Cells[i*2+2][j+1]=CurrToStrF(BMKbmRd_53[i][j][1],ffFixed,2);
    }//for
     StringGrid4->Cells[i*2+2][162]=CurrToStrF(Min,ffFixed,2);
     delete(Myfile);
     Myfile=NULL;
   }

   }
}
else{ Application->MessageBox("����� �� ����������", "", MB_ICONINFORMATION|MB_OK);}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::LoadFlBMK_2(TObject *Sender)
{
int i,j,f;
double integ, frack;
AnsiString MyFlName ;
AnsiString FileNam,Sl,Ss,Sm;
float Min;
float* buff;

if(RadioButton1->Checked)
Ss="���";
else
Ss="���";
Sm=(RadioGroup12->ItemIndex==0)? "_�_":"_�_";

int colp=64,colbm=4;
//}
int sz=colp*colbm*2*sizeof(float);
InitStrGrd4();

MyFlName=Ss+IntToStr(ComboBox2->ItemIndex+1)+Sm+"BMK2"+".pmm" ;

FileNam=ExtractFilePath(Application->ExeName)+"PowMesh\\"+MyFlName;
 if(FileExists(FileNam)==true){
  Myfile=new TFileStream(FileNam,fmOpenRead);
   if(Myfile)
   {
    buff=new float[sz];
    Myfile->ReadBuffer(BMKbmRd_2,sz);
    delete(Myfile);
   Myfile=NULL;
   InitStrGrd4();
   for(i=0;i<colbm ;i++)
   {
   Min =INIT_VAL ;
    for(j=0;j<colp;j++)
    {
     if(BMKbmRd_2[i][j][1]<Min)
     Min=BMKbmRd_2[i][j][1];
     modf(j/8,&integ);
     frack=j-integ*8;
     f=integ*500+frack*64+Fl+26;


     StringGrid1->Cells[0][j+1]=CurrToStrF(f,ffFixed,0);
     StringGrid1->Cells[i*2+1][j+1]=CurrToStrF(BMKbmRd_2[i][j][0],ffFixed,2);
     StringGrid1->Cells[i*2+2][j+1]=CurrToStrF(BMKbmRd_2[i][j][1],ffFixed,2);
    }//for
     StringGrid1->Cells[i*2+2][66]=CurrToStrF(Min,ffFixed,2);
     delete(Myfile);
     Myfile=NULL;
   }

   }
}
else{ Application->MessageBox("����� �� ����������", "", MB_ICONINFORMATION|MB_OK);}

}

void TForm1::GoBegAction(int Lit,int PSph)
{
 //�������� � �������� ������� (��� ���������) � ������ E14
   extern int OLD_POZ; /* ��������� ������� */
   extern int STATE_POZ;
  int bsec;
  bool rev;       //REVERS=false (DL �����);  true (DR ������ (��� ����� ����))
if(Lit==1)
	bsec= BegSecTrm_53;
else if(Lit==0)
	bsec= BegSecTrm_2;

bool  smsd_prg_loaded = false;
char *vel[]={"SD700*"};

rev =( PSph==0)? false:true;
Search_Zero_my(rev);
 if (!smsd_prg_loaded){
         if (!WrCmdsAndMove_speed((bsec-OfSetSec)*ONE_DEG,rev,vel)){
              return;
         }
         MyTimer(100); }
      if (!SmsdWrCmd_start("ST1*")){ //�����
        return;
      }
STATE_POZ=0;
if (PSph==0)
     OLD_POZ=bsec*ONE_DEG;
else if (PSph==0)
     OLD_POZ=(180-bsec)*ONE_DEG;
MyTimer(MAX_TMO/10); //���� ���� ������ ����������

}
//---------------------------------------------------------------------------

double TForm1::RateAntenn53(int find,int gr)
{
int Xgrd_bg=30;
int Xgrd_end=55;
double fbg=2.0,fed=8.0;//���
double tgal,tgbet,Rt;
double K;
tgal=Xgrd_bg/fbg;
tgbet=(90.0-Xgrd_end)/fed;
if(gr<=Xgrd_bg)
{
 Rt=(Xgrd_bg-gr)/tgal;
}
else if(gr>=Xgrd_end)
{
 Rt=(gr-Xgrd_end)/tgbet;
}
else
Rt=0.0;
//double tgf=160.0/1.0;
//double Kf=find/tgf;

//return Pmsh+Rt;
//K=pow(10,Rt/10);
return Rt;//*Kf;
}

void __fastcall TForm1::ChengeCheckBox75(TObject *Sender)
{
if(CheckBox75->Checked)
SpeedButton10->Enabled=false;
else
SpeedButton10->Enabled=true;
}
//---------------------------------------------------------------------------







