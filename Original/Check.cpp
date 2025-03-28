
#pragma hdrstop

#include "ARM.h"
#include "algorithm.h"
#include "math.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
void __fastcall TForm1::MnCheck(TObject *Sender)
{
Panel1->Visible=false;
Panel2->Visible=false;
Panel3->Visible=false;
//Panel4->Visible=false;
P_1->Visible=false;
PanelPotent->Visible=false;
PanelSummPow->Visible=false;
PanelOUTPow->Visible=false;
 }
//---------------------------------------------------------------------------

void __fastcall TForm1::onSMnTrRatio(TObject *Sender)
{

TGridRect myRect;
  myRect.Left = 10;
  myRect.Top = 10;
  myRect.Right = 10;
  myRect.Bottom = 10;

 StringGrid1->Selection=myRect;
   Mode=0;
 StringGrid1->Cells[0][0]="����";
 StringGrid1->Cells[0][1]="����1";
 StringGrid1->Cells[0][2]="����2";
 StringGrid1->Cells[0][3]="��";
 StringGrid1->Cells[1][0]="��min ���.";
 StringGrid1->Cells[2][0]="d�� (��)";
 StringGrid1->Cells[3][0]="��� 11��";
 StringGrid1->Cells[4][0]="��� 12��";
 StringGrid1->Cells[5][0]="��� 23��";
 StringGrid1->Cells[6][0]="��max ����.";
 StringGrid1->Cells[7][0]="���. P��";
 StringGrid1->Cells[8][0]="���.P�����";

  ProgressBar1->Visible=false;
   StringGrid1->Visible=false;
   Button5->Visible=false;
   Button6->Visible=false;
 FileCalbGnPm();

ShowPanel3();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::ChouseChn(TObject *Sender)
{
AnsiString S,St;
S=ComboBox1->Items->Strings[ComboBox1->ItemIndex];

if(ComboBox1->ItemIndex==2)
MaskEdit4->Text="0";
else
 MaskEdit4->Text="-20";
St="���������� ������ � ���������� �� ���� "+S;
if(Application->MessageBox(St.c_str(), "��������!", MB_ICONINFORMATION|MB_OKCANCEL)==IDOK)
{
St="���������� ������ �� � ������ ������� ���3-52 �� ���� ���������� ��������";
  if( Application->MessageBox(St.c_str(),"��������!", MB_ICONINFORMATION| MB_OKCANCEL)== IDOK )
   {
       Label7->Caption = "����������� �������� ��  ������� ���3-52, ����"+S ;
       Label7->Visible = true;
       StringGrid1->Visible=true;

       Button5->Visible=true;
       Button6->Visible=true;
       Button6->Enabled=false;

   } //if
}  //if

}
//---------------------------------------------------------------------------

void TForm1::Check(void)
{
 float Pg,dltPg,dltPm;
 float Pmm,Patt11,Patt12,Patt23;
 float P,P0;    //��������, ����������� � ���������� �������� � ������ ������
 AnsiString SPg,S,Ser;
 int f,i,j;
 int ind; //������ ������� � �������� ����������
 int Fbeg;
 int cnt=0;
 bool errA11=false;
 bool errA12=false;
 bool errA23=false;

 vector < float > TrRt;  // ����������� ��������  ��� ���������� ������
 vector < float > TrRtOff ;//  ����������� ��������  ��� ����������� ������
 float TrRmin,TrRmax, dTr,TrRmaxOff;

 TrRt.clear();
 TrRtOff.clear();
  PStop=false;

 SPg=Trim(MaskEdit4->Text);   //�������� ����������
 Pg=StrToFloat(SPg);
ProgressBar1->Step=((Fh-Fl)/500)*8;
// CheckCalbPm();
 InitPowMtr();
 InitE825(SPg);
 Button6->Enabled=true;      // ����
 ProgressBar1->Position = ProgressBar1->Min;
 ProgressBar1->Visible=true;

 Packet_P_CO();  //������� � ������� �����
 Sleep(1000);
//����� ����������  ��min, K�max, Att11,Att12,Att23
for(j=0;j<28;j++)    // 28 ������������ �� 500���
 {
  Fbeg=Fl+26+500*j;
  for(i=0;i<8;i++)    //8 ����� ������� � ������ �����������
  {
                //����� �������
   f=Fbeg+i*64;    // ��� ������� 64 ���
    if((PStop==false) )
      {
       dltPg=dPg[cnt];
       SPg=CurrToStrF(Pg-dltPg,ffFixed,2);
       CorrStrGen(SPg);
       WrGenE825(IntToStr(f),SPg);
      OutContrFUP(1,0,0);    // ������ , ���=0, KF=0


// Sleep(100);
    if((Pmm=StepRdPow())==0)
      {
      TrRt.clear();
      goto end;
      }
       P=Pmm-dPm[cnt];
       ProgressBar1->StepIt();
       P0=P-Pg;
       TrRt.insert(TrRt.end(),P0);

        OutContrFUP(1,1,0);        // ������ , ��������� Att11 ,KF=0
   Sleep(100);
       if((Patt11=StepRdPow())==0)
        {
         TrRt.clear();
         goto end;
        }
       if(((Patt11-Pmm)<9)||((P0-Patt11)>15))
         errA11=true;

         OutContrFUP(1,2,0);        //// ������ , ��������� Att12 ,KF=0
  Sleep(100);
       if((Patt12=StepRdPow())==0)
        {
         TrRt.clear();
         goto end;
        }
       if(((Patt12-Pmm)<10)||((Patt12-Pmm)>16))
         errA12=true;
        OutContrFUP(1,3,0);        //// ������ , ��������� Att11,Att12 ,KF=0
// Sleep(100);
       if((Patt23=StepRdPow())==0)
        {
         TrRt.clear();
         goto end;
        }
       if(((Patt23-Pmm)<19)||((Patt23-Pmm)>26))
         errA23=true;

      OutContrFUP(0,0,0);        //���������� ������
// Sleep(100);
       if((Patt12=StepRdPow())==0)
        {
         TrRtOff.clear();
         goto end;
        }
         P=Pmm-dPm[cnt];
       ProgressBar1->StepIt();
       P0=P-Pg;
       TrRtOff.insert(TrRtOff.end(),P0);
       cnt++;
       Application->ProcessMessages();
       }
      else
       {
        TrRt.clear();
        TrRtOff.clear();
      goto end;
       }
  }  //for i
 }  //for j


 if(TrRt.size()!=0)
  {
   TrRmin = *min_element(TrRt.begin(), TrRt.end()) ;
   TrRmax = *max_element(TrRt.begin(), TrRt.end()) ;
   dTr=TrRmax-TrRmin;
   i=ComboBox1->ItemIndex;
   if(errA11==true)
      Ser="�� ������";
   else
   Ser="������" ;
   StringGrid1->Cells[3][i+1]=Ser;

   if(errA12==true)
   Ser="�� ������";
   else
   Ser="������" ;
   StringGrid1->Cells[4][i+1]=Ser;
   if(errA23==true)
    Ser="�� ������";
    else
   Ser="������" ;
   StringGrid1->Cells[5][i+1]=Ser;


   StringGrid1->Cells[1][i+1]=CurrToStrF(TrRmin,ffFixed,2);
   StringGrid1->Cells[2][i+1]=CurrToStrF(dTr,ffFixed,3);
  }//if  TrRt.size()

  if(TrRtOff.size()!=0)
  {
   TrRmaxOff = *max_element(TrRtOff.begin(), TrRtOff.end()) ;
   StringGrid1->Cells[6][i+1]=CurrToStrF(TrRmaxOff,ffFixed,3);
  }
end: OfGenE825();
 ProgressBar1->Visible=false;
}


void __fastcall TForm1::startCheck(TObject *Sender)
{

Button5->Enabled=false;     //�����

if(ChkDevs==true)
 Check();
 else
 {

if(FindDevises()==true)
 {
 if(ChekDev()==true)
  Check();

 }    //FindDevises()
 }//else

ProgressBar1->Visible=false;
 Button5->Enabled=true;      // �����
Button6->Enabled=false;     //����



}
//---------------------------------------------------------------------------
 void TForm1::OutContrFUP(Byte mod,Byte Att,Byte KF)
 {

 Byte buff[4]; // 4 ��������� ����� FUP
 memset(buff,0,4);

 buff[1]=mod<<5; // RRPT
 buff[2]=KF;
 buff[3]=Att;
   PaketFUP(buff);
 }
//---------------------------------------------------------------------------
void __fastcall TForm1::ClosePan(TObject *Sender)
{
 PStop=true;
 ComboBox1->ItemIndex=-1;
 StringGrid1->Visible=false;
 Panel3->Visible=false;
 if(viG!=0)
 OfGenE825();
}
//---------------------------------------------------------------------------

void TForm1::ShowPanel3(void)
{
   Panel3->Visible=true;
}

void __fastcall TForm1::onStopCheck(TObject *Sender)
{
  //
  PStop=true;
  Button5->Enabled=true; // �����
  Button6->Enabled=false;// ����
}
//---------------------------------------------------------------------------

