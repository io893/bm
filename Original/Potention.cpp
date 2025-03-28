//---------------------------------------------------------------------------


#pragma hdrstop

#include "ARM.h"
#include <Filectrl.hpp>
#include <math.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

void __fastcall TForm1::PotentionMeash(TObject *Sender)
{
int i;
AnsiString St,StDir;
Mode=1;
Panel1->Visible=false;
Panel2->Visible=false;
PanelOUTPow->Visible=false;
SpeedButton1->Enabled=false;
PanelPotent->Visible=true;
Panel2->Visible=false;

StringGrid6->Cells[0][0]="�������";

for(i=0;i<4;i++)
{
St="P���";
StringGrid6->Cells[3*i+1][0]=St;
St="�����";
StringGrid6->Cells[3*i+2][0]=St;
St="��������";
StringGrid6->Cells[3*i+3][0]=St;
}
St=GetCurrentDir();
StDir=St+"\\PowMesh";
if (!DirectoryExists(StDir))
  {
    if (!CreateDir(StDir))
      throw Exception("Cannot create "+StDir);
  }
//int  indIn=0,indLit=0, indPSph=1,l=3,indF=7;
//PaketFOC(indIn, indLit,indPSph,l, indF );
  CloseTabPt();
InitLiter();

}
//---------------------------------------------------------------------------

void TForm1::InitLiter(void)
{
int colRow,i,colCol;
AnsiString St;
ComboBox3->Clear();

 CloseTabPt();
 ClearStrGrd();
 if(RadioGroup3->ItemIndex==0)
  {
   ComboBox3->Items->Add("1��-2");
   ComboBox3->Items->Add("2��-2");
   ComboBox3->Items->Add("3��-2");
   ComboBox3->Items->Add("4��-2");
    colRow=68;
    colCol=25;
    StringGrid6->Width=603;
    Label9->Visible=false;
  }
else if(RadioGroup3->ItemIndex==1)
   {
     ComboBox3->Items->Add("1��-53");
     ComboBox3->Items->Add("2��-53");
     ComboBox3->Items->Add("3��-53");
     ComboBox3->Items->Add("4��-53");

     for(i=0;i<4;i++)
      {
       St="P���";
       StringGrid6->Cells[3*i+13][0]=St;
       St="�����";
       StringGrid6->Cells[3*i+14][0]=St;
       St="��������";
       StringGrid6->Cells[3*i+15][0]=St;
      }
     StringGrid6->Width=1146;
     Label9->Visible=true;
     colRow=164;
     colCol=25;
  }
StringGrid6->ColCount=colCol;
StringGrid6->RowCount=colRow;
StringGrid6->Visible=true;
Label5->Visible=true;
ComboBox3->ItemIndex=0;
}

void __fastcall TForm1::ChengeLiter(TObject *Sender)
{
  InitLiter();
}
//---------------------------------------------------------------------------

bool TForm1::Att_Luch_Out1(int indIn,int indOut,int indLit,int indPSph,int luch,Byte ValInAtt,Byte ValOutAtt)
{
	int i;
	double frac,integ;

	Byte ON1,ON2;     //���/���� �������
	Byte lN2Att,lN1Att;
	Byte ADR_UP7;

	Byte N1O,N2O;   // ����� ������ �������
	Byte DATA_UP7_2[3];
	Byte DATA_UP7_3[7];

	if(indOut<13){        //���� �������� �� ��� ���������
//�����3 ��7_____________________________
		for(i=0;i<7;i++)
			DATA_UP7_3[i]=0xff;   //��� �������

//����� ��7
		ADR_UP7=GetAdrUp7Post(indLit,indPSph);
//���� �����������
		modf(indOut/2,&integ);
		frac=indOut%2;
		if(frac)
			DATA_UP7_3[int(integ)]=0x0f|(ValOutAtt<<4);
		else
			DATA_UP7_3[int(integ)]=0xf0|ValOutAtt;

		if(PaketUP7_3(ADR_UP7, DATA_UP7_3)==false) return false;
	}//indOut<13

	//Sleep(200);
 //�����2 ��7____________________________________
 if(indPSph==1){indIn = 1;} ;
 // ���/���� ������� ��� 1,2 ������
	if((indIn==0)||(indIn==2))    //1 �����
	{
		ON1=1;
		ON2=1;
		if(indLit==0)            //������2
		{
			if(indPSph==0)          //���
				N1O=luch;
			else        //���
				N1O=luch+4;
		}//indLit==0  ������2

		else
		if(indLit==1)   //������ 53
		{
			if(indPSph==0)          //���
				N1O=luch;
			else        //���
				N1O=luch+8;
		}
		N2O=0;       //���������� �����������
		lN1Att=ValInAtt; //������� ���������� 1 ������
		lN2Att=ValInAtt; //������� ��������� 2 ������  0x1f

	}
	else if((indIn==1)||(indIn==3))  //2  �����
	{
	ON1=1;
	ON2=1;
	if(indLit==0)            //������2
	{
		if(indPSph==0)          //���
		N2O=luch;
		else        //���
		N2O=luch+4;
	}//indLit==0  ������2

  else
  if(indLit==1)   //������ 53
	{
	  if(indPSph==0)          //���
	  N2O=luch;
	 else        //���
	 N2O=luch+8;
	}
	  N1O=0;
	  lN1Att=ValInAtt;
	  lN2Att=ValInAtt; //������� ��������� 2 ������
 }
//����� ��7 ��� ������
if((indIn==0)||(indIn==1))
{
 if(indLit==0)
ADR_UP7=0x2;
 else
 if(indLit==1)
ADR_UP7=0x0;
}
else
if((indIn==2)||(indIn==3))
{
  if(indLit==0)
ADR_UP7=0x3;
 else
 if(indLit==1)
ADR_UP7=0x1;
}

DATA_UP7_2[0]=N1O|(N2O<<4);
DATA_UP7_2[1]=lN1Att|(ON1<<5);
DATA_UP7_2[2]=lN2Att|(ON2<<5);

if(PaketUP7_2(ADR_UP7,DATA_UP7_2)==false) return false; //����� 2 ��7
 return true;
}
bool TForm1::Att_Luch_Out(int indIn,int indOut,int indLit,int indPSph,int luch,Byte ValInAtt,Byte ValOutAtt)
{
 int i;
 double frac,integ;

 Byte ON1,ON2;     //���/���� �������
 Byte lN2Att,lN1Att;
 Byte ADR_UP7;

 Byte N1O,N2O;   // ����� ������ �������
 Byte DATA_UP7_2[3];
 Byte DATA_UP7_3[7];

if(indOut<13){        //���� �������� �� ��� ���������
//�����3 ��7_____________________________
for(i=0;i<7;i++)
DATA_UP7_3[i]=0xff;   //��� �������

//����� ��7
ADR_UP7=GetAdrUp7Post(indLit,indPSph);
//���� �����������
modf(indOut/2,&integ);
frac=indOut%2;
if(frac)
  DATA_UP7_3[int(integ)]=0x0f|(ValOutAtt<<4);
else
DATA_UP7_3[int(integ)]=0xf0|ValOutAtt;

if(PaketUP7_3(ADR_UP7, DATA_UP7_3)==false) return false;
}//indOut<13

Sleep(200);
 //�����2 ��7____________________________________
 // ���/���� ������� ��� 1,2 ������
 if((indIn==0)||(indIn==2))    //1 �����
 {
  ON1=1;
  ON2=0;
  if(indLit==0)            //������2
  {
   if(indPSph==0)          //���
   N1O=luch;
   else        //���
   N1O=luch+4;
  }//indLit==0  ������2

  else
  if(indLit==1)   //������ 53
   {
     if(indPSph==0)          //���
     N1O=luch;
    else        //���
    N1O=luch+8;
   }
     N2O=0;       //���������� �����������
     lN1Att=ValInAtt; //������� ���������� 1 ������
     lN2Att=0x1f; //������� ��������� 2 ������

 }
else if((indIn==1)||(indIn==3))  //2  �����
 {
  ON1=0;
  ON2=1;
  if(indLit==0)            //������2
  {
   if(indPSph==0)          //���
   N2O=luch;
   else        //���
   N2O=luch+4;
  }//indLit==0  ������2

  else
  if(indLit==1)   //������ 53
   {
     if(indPSph==0)          //���
     N2O=luch;
    else        //���
    N2O=luch+8;
   }
     N1O=0;
     lN1Att=0x1f;
     lN2Att=ValInAtt; //������� ��������� 2 ������
 }
//����� ��7 ��� ������
if((indIn==0)||(indIn==1))
{
 if(indLit==0)
ADR_UP7=0x2;
 else
 if(indLit==1)
ADR_UP7=0x0;
}
else
if((indIn==2)||(indIn==3))
{
  if(indLit==0)
ADR_UP7=0x3;
 else
 if(indLit==1)
ADR_UP7=0x1;
}

DATA_UP7_2[0]=N1O|(N2O<<4);
DATA_UP7_2[1]=lN1Att|(ON1<<5);
DATA_UP7_2[2]=lN2Att|(ON2<<5);

if(PaketUP7_2(ADR_UP7,DATA_UP7_2)==false) return false; //����� 2 ��7
 return true;
}

void __fastcall TForm1::Poten(TObject *Sender)
{
AnsiString SbS,SbL,SbIn,StrDir,MyFileName,SIn;
int i,j;
//int sz;
int n;//�����
int l; //���
int k; //������ �������
int ind,indn;
int Lit;
float Pw,sump,ptn; // �  ��
int Flb;
float PSmmin, Potmin;

int colLuch,colOut,colF;

//struct Poteni  Ptl;
 ClearStrGrd();
if(RadioGroup1->ItemIndex==0)
SbS="���";
else
SbS="���";
if(RadioGroup3->ItemIndex==0)
{
SbL="��_2";
Flb=Fl;
colLuch=4;
colOut=13;
Lit=0;
colF=((Fb-Fl)/500)*8;
}
else
{
SbL="��_53";
Flb=Fb;
colLuch=8;
colOut=12;
Lit=1;
colF=((Fh-Fb)/500)*8;
}
StrDir=GetCurrentDir();


i=ComboBox3->ItemIndex +1;

OUTiIn.clear();
Ptl.PtIn.clear();
Ptl.SumPw.clear();
UsPerFrq.clear();

for(j=1;j<=colOut;j++)  // ������
{
 SbIn=IntToStr(i)+SbL;
 SIn=IntToStr(j)+SbS+IntToStr(i)+SbL+".pmm";

 if(RadioGroup2->ItemIndex==1)            //������� �����
 SIn="Sh"+SIn;

 MyFileName=StrDir+"\\PowMesh\\"+SIn;
 if(FileExists(MyFileName))
   RdFileOUTiIn( MyFileName,  colLuch);   //       ReadOUT(MyFileName,colLuch);
 else
 {
  Application->MessageBox("������������ ��������� ��� ���������� ����������",SbIn.c_str(), MB_ICONINFORMATION| MB_OK);
  OUTiIn.clear();
  break;
 }
} //j
//sz=OUTiIn.size();
if(OUTiIn.size()!=0)
{
for(l=0;l<colLuch;l++)         // ����
{
 for(k=0;k<colF;k++)          // �������
 {
 ptn=0.0;
 sump=0.0;
// StAnUs="���";
  for(n=0;n<colOut;n++)        // ������
   {
    ind=n*colLuch*colF+l*colF+k;
    Pw=OUTiIn[ind].Pw; //���       Pw=pow(10,-3)*pow(10,RdIn[ind]/10);  //��
    sump+=Pw;              //��������� ��� ������ ���� l �� ����� �������  �� ���� �������
    AnADC(ind);
   }//n
  Ptl.SumPw.insert(Ptl.SumPw.end(),sump);
  ptn=sump*RatePoten(k,Flb,Lit,l);
  Ptl.PtIn.insert( Ptl.PtIn.end(),ptn);

 // sz=Ptl.PtIn.size();
//  sz=Ptl.SumPw.size();
 }//k       //���������  ���� l �� ������ ������� ����� i

 }//l      // ���������� ���� ����� �����  i  �� ������ �������
 Ptl.in=i;

 OutTabPot(colLuch,colF,colOut,Flb);
// sz=sizeof(Ptl);
// Potential.insert(Potential.end(),Ptl);
 }//if


  SpeedButton1->Enabled=true;
}
//---------------------------------------------------------------------------
void TForm1::AnADC(int ind)
{
int bound;

int Kod_ADC;
bound=StrToInt(Trim(MaskEdit2->Text));
Kod_ADC=OUTiIn[ind].Kode_ADC;

if(Kod_ADC<bound)
 UsPerFrq.insert(UsPerFrq.end(),false); //���� ��� ������ �������,�� ������ ������� �� ������ ���� �� �������
else
 UsPerFrq.insert(UsPerFrq.end(),true);
}


void TForm1::OutTabPot(int colLuch,int colF,int colOut,int Flb)
{
 int k,l,ind,f,n;
 int indk;
 double integ;
 double frack;
 AnsiString StAnUs;
 int colRw;
 float  Pmin,Potmin;

 colRw=StringGrid6->RowCount;
for(l=0;l<colLuch;l++)
{
Pmin=1000.0;
Potmin=1000.0;
 for(k=0;k<colF;k++)
 {
  StAnUs="������";
  for(n=0;n<colOut;n++)
  {
   indk=l*colF*colOut+k*colOut+n;
   if(UsPerFrq[indk]==false)
     StAnUs="�� �����";
  } //n
   ind=l*colF+k;
  modf(k/8, &integ);
  frack=k-integ*8;
 f=integ*500+frack*64+Flb+26;

     StringGrid6->Cells[3*l+1][k+1]=CurrToStrF(Ptl.SumPw[ind],ffFixed,2);
     StringGrid6->Cells[3*l+2][k+1]=CurrToStrF(Ptl.PtIn[ind],ffFixed,2);
     StringGrid6->Cells[3*l+3][k+1]=StAnUs;
     StringGrid6->Cells[0][k+1]=IntToStr(f);

   if(Ptl.SumPw[ind]<Pmin)
   Pmin=Ptl.SumPw[ind];

   if(Ptl.PtIn[ind]<Potmin)
   Potmin=Ptl.PtIn[ind];

 }//k
    StringGrid6->Cells[3*l+1][colRw-2]="Pmin";
    StringGrid6->Cells[3*l+2][colRw-2]="���min";

    StringGrid6->Cells[3*l+1][colRw-1]=CurrToStrF(Pmin,ffFixed,2);
    StringGrid6->Cells[3*l+2][colRw-1]=CurrToStrF(Potmin,ffFixed,2);
} //l

}

void __fastcall TForm1::savePotential(TObject *Sender)
{
AnsiString Ss,Sl,Str,Sin;
AnsiString StrDir,MyFileName;
int in,n,k,c,b;
int i,j;
float* buff;

if(RadioGroup1->ItemIndex==0)
Ss="���";
else
Ss="���";
if(RadioGroup3->ItemIndex==0)
Sl="��_2";
else
Sl="��_53";

StrDir=GetCurrentDir()+"\\PowMesh\\";

in=Ptl.in  ;
Str="��������� ������ ���������� ��� �����";

 Sin=Str+IntToStr(in)+Sl+Ss+" ?";
 if(Application->MessageBox(Sin.c_str() ,"��������!", MB_ICONINFORMATION|MB_OKCANCEL)==ID_OK)
 {
  MyFileName=StrDir+Ss+IntToStr(in)+Sl+".ptl";

 if(FileExists(MyFileName))
     {
      if(Application->MessageBox("���� ��� ����������. ����������?","��������!", MB_ICONINFORMATION|MB_OKCANCEL)!=ID_OK)
      goto M1;
     }
      Myfile=new TFileStream(MyFileName,fmCreate|fmOpenWrite);
 if(Myfile)
  {
    Myfile->Position=0;
    k=sizeof(int);
   Myfile->WriteBuffer(&Ptl.in,k);

    n=Ptl.SumPw.size();
    c=n*2; //  2 ���������� �������
    //b=c/sizeof(float);
   buff= new float[c];
      for(i=0,j=0;j<n;j++,i++)
       buff[i]=Ptl.SumPw[j];
      for(j=0;j<n;j++,i++)
       buff[i]=Ptl.PtIn[j];

    Myfile->Position=k;
    Myfile->WriteBuffer(buff,c*sizeof(float));


   delete(Myfile);
   Myfile=NULL;
   delete[] buff;
  }
 }
M1:;

}

//---------------------------------------------------------------------------
void __fastcall TForm1::ReadPotential(TObject *Sender)
{
AnsiString SbS,StrDir,MyFileName,S,SbL;
int n,i,j,b;
float* buff;
int Flb;
int colLuch,colOut,colF;

Ptl.PtIn.clear();
Ptl.SumPw.clear();

 ClearStrGrd();
if(RadioGroup1->ItemIndex==0)
SbS="���";
else
SbS="���";
if(RadioGroup3->ItemIndex==0)
{
SbL="��_2";
Flb=Fl;
colLuch=4;
colOut=13;
colF=((Fb-Fl)/500)*8;
}
else
{
SbL="��_53";
Flb=Fb;
colLuch=8;
colOut=12;
colF=((Fh-Fb)/500)*8;
}
StrDir=GetCurrentDir();

MyFileName=StrDir+"\\PowMesh\\"+SbS+IntToStr((ComboBox3->ItemIndex+1))+SbL+".ptl";
 if(FileExists(MyFileName))
 {
     Myfile=new TFileStream(MyFileName,fmOpenRead);
     if(Myfile)
     {
      n=(Myfile->Size-sizeof(int));
      b=n/sizeof(float);
      buff= new float[b];

      Myfile->Position=0;
      Myfile->ReadBuffer(&Ptl.in,sizeof(int));

      Myfile->Position=sizeof(int);
      Myfile->ReadBuffer(buff,n);

      for(i=0,j=0;i<(b/2);i++,j++)
        Ptl.SumPw.insert(Ptl.SumPw.end(),buff[j]);
      for(i=0;i<(b/2);i++,j++)
        Ptl.PtIn.insert(Ptl.PtIn.end(),buff[j]);


       RdOutTabPot(colLuch,colF,colOut,Flb);

       delete(Myfile);
       Myfile=NULL;
       delete[] buff;
     }
    else
    {
     S="�� ���� ������� ����"+MyFileName;
     Application->MessageBox(S.c_str(),"������ ������ �����", MB_ICONERROR| MB_OK);
    }

 } //FileExists
 else
 {
  S="���� "+MyFileName+" �� ����������";
  Application->MessageBox(S.c_str(),"����", MB_ICONINFORMATION| MB_OK);
 }


}
//---------------------------------------------------------------------------

void TForm1::RdOutTabPot(int colLuch,int colF,int colOut,int Flb)
{

int k,l,ind,f,n;
 int indk;
 double integ;
 double frack;
 AnsiString StAnUs;
 int colRw;
 float  Pmin,Potmin;

 colRw=StringGrid6->RowCount;
for(l=0;l<colLuch;l++)
{
Pmin=1000.0;
Potmin=1000.0;
 for(k=0;k<colF;k++)
 {
/*  StAnUs="������";
  for(n=0;n<colOut;n++)
  {
   indk=l*colF*colOut+k*colOut+n;
   if(UsPerFrq[indk]==false)
     StAnUs="�� �����";
  } //n   */
   ind=l*colF+k;
  modf(k/8, &integ);
  frack=k-integ*8;
 f=integ*500+frack*64+Flb+26;

     StringGrid6->Cells[3*l+1][k+1]=CurrToStrF(Ptl.SumPw[ind],ffFixed,2);
     StringGrid6->Cells[3*l+2][k+1]=CurrToStrF(Ptl.PtIn[ind],ffFixed,2);
//     StringGrid6->Cells[3*l+3][k+1]=StAnUs;
     StringGrid6->Cells[0][k+1]=IntToStr(f);

   if(Ptl.SumPw[ind]<Pmin)
   Pmin=Ptl.SumPw[ind];

   if(Ptl.PtIn[ind]<Potmin)
   Potmin=Ptl.PtIn[ind];

 }//k
    StringGrid6->Cells[3*l+1][colRw-2]="Pmin";
    StringGrid6->Cells[3*l+2][colRw-2]="���min";

    StringGrid6->Cells[3*l+1][colRw-1]=CurrToStrF(Pmin,ffFixed,2);
    StringGrid6->Cells[3*l+2][colRw-1]=CurrToStrF(Potmin,ffFixed,2);
} //l

}



float TForm1::RatePoten(int k,int Flb,int& Lit,int& luch)
{
int i,j;
double f;
double rdb ;
double Prate;
 double integ;
 double frack;

modf(k/8, &integ);
  frack=k-integ*8;
 f=(integ*500+frack*64+Flb+26)/1000; //���


if(Lit==0)
{

 if((f>=4.0)&&(f<=6.0))
  rdb=((11.7-8.7)/(6.0-4.0))*(f-4.0)+8.7+CorrectionOfBeam(f,luch,Lit);
 else
 if((f>6.0)&&(f<=6.5))
 rdb=((13.3-11.7)/(6.5-6.0))*(f-6.0)+11.7+CorrectionOfBeam(f,luch,Lit);
 else
 if((f>6.5)&&(f<=8.0))
 rdb=((14.7-13.3)/(8.0-6.5))*(f-6.5)+13.3+CorrectionOfBeam(f,luch,Lit);
}
else  if(Lit==1)
 {
 if((f>=8.0)&&(f<=12.0))
  rdb=((14.4-11.4)/(12.0-8.0))*(f-8.0)+11.4+CorrectionOfBeam(f,luch,Lit);
 else
 if((f>12.0)&&(f<=13.0))
 rdb=((13.7-14.4)/(13.0-12.0))*(f-12.0)+14.4+CorrectionOfBeam(f,luch,Lit);
 else
 if((f>13.0)&&(f<=18.0))            //(f<=17.0))  �������� ������ ���� ������ �� 17���
 rdb=((13.6-13.7)/(17.0-13.0))*(f-13.0)+13.7+CorrectionOfBeam(f,luch,Lit);
 }

return pow(10,rdb/10);
}

float TForm1::CorrectionOfBeam(double f,int& luch,int& Lit)
{
double x1,x2,y1,y2,x,y;
int lch;
double corr;
lch=luch+1;

  if(Lit==0)        //�� 3 ����
  {
   if((f>=4.0)&&(f<=5.0))
   {
   x1=4.0; x2=5.0;

   switch(lch) {
    case 1 :
     y1=-2.0 ;y2=0.5;break;
    case 2 :
     y1=-1.0 ;y2=1.5;break;
    case 3 :
     y1=0.0 ;y2=0.0;break;
    case 4 :
    y1=-2.5 ;y2=1.0;break; }
   }//f
   else if((f>5.0)&&(f<=6.0))
    {
    x1=5.0; x2=6.0;
    switch(lch) {
     case 1 :
     y1=0.5 ;y2=-0.5;break;
    case 2 :
     y1=1.5 ;y2=1.0;break;
    case 3 :
     y1=0.0 ;y2=0.0;break;
    case 4 :
    y1=1.0 ;y2=0.0;break; }
    }//f
   else if((f>6.0)&&(f<=7.0))
    {
    x1=6.0; x2=7.0;
    switch(lch) {
     case 1 :
     y1=-0.5 ;y2=-0.7; break;
    case 2 :
     y1=1.0 ;y2=0.5; break;
    case 3 :
     y1=0.0 ;y2=0.0; break;
    case 4 :
    y1=0.0 ;y2=-0.5;break; }
    }//f
  else if((f>7.0)&&(f<=8.0))
    {
    x1=7.0; x2=8.0;
    switch(lch) {
     case 1 :
     y1=-0.7 ;y2=-1.5;break;
    case 2 :
     y1=0.5 ;y2=0.0;break;
    case 3 :
     y1=0.0 ;y2=0.0; break;
    case 4 :
    y1=-0.5 ;y2=0.0;break; }
    }//f

  } //Lit
  else if(Lit==1)        //litera 53
  {
   if((f>8.0)&&(f<=10.0))
    {
    x1=8.0; x2=10.0;
    switch(lch) {
     case 1 :
     y1=-0.5; y2=-3.0;break;
    case 2 :
     y1=-0.2; y2=-1.0;break;
    case 3 :
     y1=0.5; y2=0.5; break;
    case 4 :
     y1=0.0; y2=0.0;break;       //4 luch
     case 5 :
     y1=0.0; y2=0.1;break;
    case 6 :
     y1=0.0; y2=0.0;break;
    case 7 :
     y1=0.0; y2=-1.0;break;
    case 8 :
     y1=0.0; y2=-3.0;break;}
    }//f
  else if((f>10.0)&&(f<=12.0))
    {
    x1=10.0; x2=12.0;
    switch(lch) {
     case 1 :
     y1=-3.0; y2=-2.2;break;
    case 2 :
     y1=-1.0; y2=-0.5;break;
    case 3 :
     y1=0.5; y2=0.2;break;
    case 4 :
     y1=0.0; y2=0.0;break;       //4 luch
     case 5 :
     y1=0.1; y2=0.0;break;
    case 6 :
     y1=0.0; y2=0.0;break;
    case 7 :
     y1=-1.0; y2=0.0;break;
    case 8 :
     y1=-3.0; y2=-1.5;break; }
    }//f
  else if((f>12.0)&&(f<=14.0))
    {
    x1=12.0; x2=14.0;
    switch(lch) {
     case 1 :
     y1=-2.2; y2=-2.5; break;
    case 2 :
     y1=-0.5; y2=-0.5;break;
    case 3 :
     y1=0.2; y2=-0.1; break;
    case 4 :
     y1=0.0; y2=0.0;break;       //4 luch
     case 5 :
     y1=0.0; y2=0.0;break;
    case 6 :
     y1=0.0; y2=0.0;break;
    case 7 :
     y1=0.0; y2=-0.1;break;
    case 8 :
     y1=-1.5; y2=-2.1;break; }
    }//f
   else if((f>14.0)&&(f<=16.0))
    {
    x1=14.0; x2=16.0;
    switch(lch) {
     case 1 :
     y1=-2.5; y2=-3.0;break;
    case 2 :
     y1=-0.5; y2=-2.0;break;
    case 3 :
     y1=-0.1; y2=0.0;break;
    case 4 :
     y1=0.0; y2=0.0;break;       //4 luch
     case 5 :
     y1=0.0; y2=-0.2;break;
    case 6 :
     y1=0.0; y2=-0.1;break;
    case 7 :
     y1=-0.1; y2=-2.2;break;
    case 8 :
     y1=-2.1; y2=-2.2;break; }
    }//f
   else if((f>16.0)&&(f<=18.0))
    {
    x1=16.0; x2=18.0;
    switch(lch) {
     case 1 :
     y1=-3.0; y2=-2.5;break;
    case 2 :
     y1=-2.0; y2=-0.2;break;
    case 3 :
     y1=0.0; y2=0.2; break;
    case 4 :
     y1=0.0; y2=0.0;break;       //4 luch
     case 5 :
     y1=-0.2; y2=0.0;break;
    case 6 :
     y1=-0.1; y2=-0.1;break;
    case 7 :
     y1=-2.2; y2=-0.1;break;
    case 8 :
     y1=-2.2; y2=-2.2;break; }
    }//f
  }// litera 53
 corr=((y2-y1)/(x2-x1))*(f-x1)+y1;

return corr;
}


void TForm1::CloseTabPt(void)
{
Label5->Visible=false;
Label9->Visible=false;
//StringGrid6->Visible=false;
SpeedButton1->Enabled=false;
}

void TForm1::ClearStrGrd(void)
{
int i,j;

for(j=0;j<StringGrid6->ColCount;j++)
for (i=1;i<StringGrid6->RowCount;i++)
StringGrid6->Cells[j][i]="";

}

void __fastcall TForm1::onClosePoten(TObject *Sender)
{
PStop=true;
ClearStrGrd();
PanelPotent->Visible=false;
}
//---------------------------------------------------------------------------

/*void __fastcall TForm1::PotenStop(TObject *Sender)
{

PStop=true;

} */

void __fastcall TForm1::ChengeModPot(TObject *Sender)
{
 ClearStrGrd();
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//�������������� �������
/*void TForm1::ThroughLuch()
{
AnsiString St,SPg;
AnsiString Ss,Sl;
AnsiString FileNam;
int Fbeg,Flb,f,ind;

float Pg,Pmm,Pdbm,Pw;
int colSints,colLuch,i,j,l,n;
int ofs,indIn,indInFOC,indLit, indPSph,indOut;             //�������� ������� ������� ���������� ��� 53 ������
float dltPg;
 vector <float> OUTi;    // ������ ���������� �������� ������ i �� ���� ����� ������

PStop=false ;
 CloseTabPt();
 ClearStrGrd();
 Label9->Visible=true;

 SPg=StaticText1->Caption;

indIn=ComboBox3->ItemIndex;

if(RadioGroup1->ItemIndex==0)
{
Ss=" ��� ";
indPSph=0;
}
else
{
Ss=" ��� ";
indPSph=1;
}

if(RadioGroup3->ItemIndex==0)
{
 Sl="2";
 colSints=(Fb-Fl)/500;
 Flb=Fl;
 colLuch=4;
 indLit=0;
 ofs=0;
 indInFOC=indIn+4;
}
else
{
 Sl="53";
 colSints=(Fh-Fb)/500;
 Flb=Fb;
 colLuch=8 ;
 indLit=1;
 ofs=(Fb-Fl)/500*8;
 indInFOC=indIn;
}

indOut=ComboBox4->ItemIndex;
 St="���������� ������ � ���������� �� ���� "+ComboBox3->Items->Strings[ComboBox3->ItemIndex];
if(Application->MessageBox(St.c_str(), "��������!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
{
St="���������� ������ �� � ������"+ ComboBox4->Items->Strings[ComboBox4->ItemIndex]+Ss+"������ "+Sl+" �� ���� ���������� ��������";
  if( Application->MessageBox(St.c_str(),"��������!", MB_ICONINFORMATION| MB_OKCANCEL)== IDOK )
   {
   InitPowMtr();
   InitE825(SPg);
   Pg=StrToInt(SPg);
for(l=0;l<colLuch;l++)            //���� �� �����
 {
    Att_Luch_Out(indIn, indOut, indLit,indPSph,0,0,l);

    for(j=0;j<colSints;j++)    //  ������������ �� 500���
    {
     Fbeg=Flb+26+500*j;
     for(i=0;i<8;i++)    //8 ����� ������� � ������ �����������
     {
      f=Fbeg+i*64;    // ��� ������� 64 ���
      if((PStop==false) )
      {

      ind=j*8+i+ofs;
       dltPg=dPg[ind];
       SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
       CorrStrGen(SPg);
       WrGenE825(IntToStr(f),SPg);

      if((Pmm=StepRdPow())==0)
            goto M1;

       Pdbm=Pmm-dPm[ind];
      Pw=pow(10,Pdbm/10); //���       Pw=pow(10,-3)*pow(10,Pdbm/10);  //��
        StringGrid2->Cells[0][ind-ofs+1]=IntToStr(f);
        StringGrid2->Cells[l+1][ind-ofs+1]=CurrToStrF(Pw,ffFixed,2);
        OUTi.insert(OUTi.end(),Pw);
       Application->ProcessMessages();
       }
      else
        goto M1;

  }  //for i
 }  //for j
 n=OUTi.size();

 }  //for l

 FileNam=ComboBox4->Items->Strings[ComboBox4->ItemIndex]+Trim(Ss)+
            ComboBox3->Items->Strings[ComboBox3->ItemIndex].SubString(1,3)+"_"+Sl+".pmm" ;
 WrFileOUTi(FileNam,OUTi,colLuch);
}
 }

M1:   OfGenE825();

}  */
//---------------------------------------------------------------------------





/*void __fastcall TForm1::startThroughLuch(TObject *Sender)
{

Button4->Enabled=false;
Button18->Enabled=false;
Button16->Enabled=true;

if(ChkDevs==true)
 ThroughLuch();
 else
 {
  if(FindDevises()==true)
  {
   if(ChekDev()==true)
   ThroughLuch();

  }    //FindDevises()
 }//else
 Button4->Enabled=true;
Button18->Enabled=true;
Button16->Enabled=false;
}
void TForm1::WrFileOUTi(AnsiString FileNam, vector< float > OUTi,int colLuch)
{
AnsiString MyFileName,StDir;
  int i;
StDir=GetCurrentDir();
MyFileName=StDir+"\\PowMesh\\"+FileNam;

 if(FileExists(MyFileName))
     {
     if(Application->MessageBox("���� ��� ����������. ����������?","��������!", MB_ICONINFORMATION|MB_OKCANCEL)!=ID_OK)
      goto M1;
     }
      Myfile=new TFileStream(MyFileName,fmCreate|fmOpenWrite);

 if(Myfile)
  {
    Myfile->Position=0;
    for(i=0;i<OUTi.size() ;i++)
    Myfile->WriteBuffer(&OUTi[i],sizeof(float));

   delete(Myfile);
   Myfile=NULL;
  }
M1:;
}

 */

