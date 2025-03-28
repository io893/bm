//---------------------------------------------------------------------------


#pragma hdrstop

#include "ARM.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void __fastcall TForm1::CheckSummPower(TObject *Sender)
{
 int i;
AnsiString St,StDir;
Mode=1;
Panel1->Visible=false;
Panel2->Visible=false;
SpeedButton1->Enabled=false;
PanelPotent->Visible=false;
Panel2->Visible=false;
StringGrid7->Cells[0][0]="×àñòîòà";
StringGrid7->Cells[1][0]="";
StringGrid7->Cells[2][0]="";
InitLt();
FileCalbGnPm();
}
//---------------------------------------------------------------------------

void TForm1::InitLt(void)
{
 int colRow,i,colCol;
AnsiString St;
ComboBox5->Clear();
ComboBox6->Clear();
ComboBox7->Clear();


 if(RadioGroup6->ItemIndex==0)
  {
   ComboBox5->Items->Add("1Â×-2");
   ComboBox5->Items->Add("2Â×-2");
   ComboBox5->Items->Add("3Â×-2");
   ComboBox5->Items->Add("4Â×-2");
   for(i=0;i<13;i++)
    ComboBox6->Items->Add(IntToStr(i+1));
    colRow=65;
    colCol=5;
   StringGrid7->Width=232;
  }
else if(RadioGroup6->ItemIndex==1)
   {
     ComboBox5->Items->Add("1Â×-53");
     ComboBox5->Items->Add("2Â×-53");
     ComboBox5->Items->Add("3Â×-53");
     ComboBox5->Items->Add("4Â×-53");

 for(i=0;i<4;i++)
  {
   St="Ëó÷"+IntToStr(i+5);
   StringGrid7->Cells[i+5][0]=St;
  }
   for(i=0;i<12;i++)
    ComboBox6->Items->Add(IntToStr(i+1));

     colRow=161;
     colCol=9;
  StringGrid7->Width=400;
   }
StringGrid7->ColCount=colCol;
StringGrid7->RowCount=colRow;

ComboBox5->ItemIndex=0;
ComboBox6->ItemIndex=0;
}
