
//---------------------------------------------------------------------------

#pragma hdrstop

#include "ARM.h"

//#include "smsd_com.h"
#include <stdio.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

#pragma link "CSPIN"
//---------------------------------------------------------------------------
#define AGL_BUF_SIZE 256
//#define ONE_DEG 109 //��� 12.5
#define ONE_DEG 218 //��� 100
#define INIT_VAL 99999
//---------------------------------------------------------------------------
//bool loop = false,
//     max_fnd = false;
//int max_steps = 0;
//double FreqStart = 4000,
//       FreqStop = 8000;
const double G_db[17] = {5.3, 5.2, 5.1, 6.5, 6.6, 7.2, 7.1, 7.0, 7.6, 7.7, 8.4, 8.6, 9.2, 9.4, 9.6, 9.7, 9.8};
//AnsiString adr_gnr = "TCPIP0::192.168.1.5::inst0::INSTR", //������ ��������
//           adr_pwm = "GPIB0::13::INSTR",
//           calibr_in = "D:\\Doc_Stend\\in.cbr", //����� ����������
//           calibr_out = "D:\\Doc_Stend\\out.cbr";
//ViSession drm = 0, gnr = 0, pwm = 0;

//---------------------------------------------------------------------------
bool __fastcall TForm1::SmsdWrCmd(char *cmd)
{
   char s[AGL_BUF_SIZE];
   DWORD t = 0;
   int cmd_len = strlen(cmd),
       slen = 0, len = 0,
       err_code = 0;
   bool res = false;

   if (!cmd_len || !strchr(cmd, '*')){
      MsgErr("�������� ������� ���������� " + AnsiString(cmd));
      return false;
   }

   sm->ReadCom(s, AGL_BUF_SIZE - 1); //������� FIFO

   if (!sm->WriteCom(cmd, strlen(cmd))){ //������
      MsgErr("������ ������ � ���� ������� " + AnsiString(cmd));
      return false;
   }

   memset(s, 0, AGL_BUF_SIZE);
   t = GetTickCount() + MAX_TMO;
   do{
      Application->ProcessMessages();
      len = sm->ReadCom(&s[slen], AGL_BUF_SIZE - (slen + 1)); //������
      if (len){
         slen += len;
         s[slen] = 0;
         if ((slen == cmd_len + 4) || (slen == cmd_len + 8)){
            if ((s[slen-4] == 'E') && (s[slen-1] == '*')){
               err_code = atoi(&s[slen-3]);
               res = ((err_code == 10) || (err_code == 14))? true: false;
            }
            else{
               MsgErr("������ ������ �� ����� �� ������� " + AnsiString(cmd));
               return false;
            }
         }
      }
   }while (!res && (GetTickCount() <= t));
   if (!res)
      MsgErr("������ ������ �� ����� �� ������� " + AnsiString(cmd));
   return res;
}
//---------------------------------------------------------------------------
bool __fastcall TForm1::SmsdWrCmdList(char **cmd_list, BYTE len)
{
  if (!len)
     return false;

  for (int i = 0; i < len; i++)
     if (!SmsdWrCmd(cmd_list[i]))
        return false;
  return true;
}
//---------------------------------------------------------------------------
bool __fastcall TForm1::SearchZero(unsigned Speed,bool rev)
{ //����� 0
  char *cmd_list0[] = {"LD1*", "BG*", "EN*", "AL0*"};
  char *cmd_list1[3] = {"DR*", "HM*", "ED*"};

if(rev==true)
cmd_list1[0]="DL*";

AnsiString s = "SD" + IntToStr(Speed) + "*";

  if (!SmsdWrCmdList(cmd_list0, 4))
     return false;
  if (!SmsdWrCmd(s.c_str()))
     return false;
  if (!SmsdWrCmdList(cmd_list1, 3))
     return false;

  return true;
}
//---------------------------------------------------------------------------
bool __fastcall TForm1::MeasByStep(unsigned StepsCount)
{ //��������� �����������
  char *cmd_list[] = {"LD1*", "BG*", "EN*", "AL0*", "SD100*", "DL*"}; //MV19680* ��� ��������� 1/16
  int len = sizeof(cmd_list) / 4;
  AnsiString s = "MV" + IntToStr(StepsCount) + "*";

  if (!SmsdWrCmdList(cmd_list, len))
     return false;
  if (!SmsdWrCmd(s.c_str()))
     return false;
  SmsdWrCmd("ED*");
  return true;
}
//---------------------------------------------------------------------------
bool __fastcall TForm1::WrCmdsAndMove(DWORD Mv, bool Revers = false)
{ //��������� �����������
  char *cmd_list[] = {"LD1*", "BG*", "EN*", "AL0*", "SD100*"};
   int len = sizeof(cmd_list) / 4;
  AnsiString s = "";
  if (!SmsdWrCmdList(cmd_list, len))
     return false;
  s = (Revers)? "DR*": "DL*";
  if (!SmsdWrCmd(s.c_str()))
     return false;
  s = "MV" + IntToStr(Mv) + "*";
  if (!SmsdWrCmd(s.c_str()))
     return false;
  if (!SmsdWrCmd("ED*"))
     return false;
  return true;
}
//---------------------------------------------------------------------------
bool __fastcall TForm1::WrCmdsAndMove_speed(DWORD Mv, bool Revers, char **velocity)
{ //��������� �����������
 // char *cmd_list[] = {"LD1*", "BG*", "EN*", "AL0*", "SD100*"};
//   char *cmd_list[] = {"LD1*", "BG*", "EN*", "AL0*", "SD300*"};
   char *cmd_list[] = {"LD1*", "BG*", "EN*", "AL0*", velocity[0]};
  int len = sizeof(cmd_list) / 4;
  AnsiString s = "";
  if (!SmsdWrCmdList(cmd_list, len))
     return false;
  s = (Revers)? "DR*": "DL*";
  if (!SmsdWrCmd(s.c_str()))
     return false;
  s = "MV" + IntToStr(Mv) + "*";
  if (!SmsdWrCmd(s.c_str()))
     return false;
  if (!SmsdWrCmd("ED*"))
     return false;
  return true;
}
//---------------------------------------------------------------------------

bool __fastcall TForm1::SmsdWrCmd_start(char *cmd)
{
   extern bool loop;
   char s[AGL_BUF_SIZE];
   DWORD t = 0;
   int cmd_len = strlen(cmd);
   //char s_my[13],s_ans[5]="E14*";

     int  slen = 0, len = 0,
       err_code = 0;
   bool res10 = false,res14=false;

   if (!cmd_len || !strchr(cmd, '*')){
      MsgErr("�������� ������� ���������� " + AnsiString(cmd));
      return false;
   }

   sm->ReadCom(s, AGL_BUF_SIZE - 1); //������� FIFO

   if (!sm->WriteCom(cmd, strlen(cmd))){ //������
      MsgErr("������ ������ � ���� ������� " + AnsiString(cmd));
      return false;
   }

   memset(s, 0, AGL_BUF_SIZE);
  // memset(s_my, 0, 12);
  t = GetTickCount() + MAX_TMO*60000; /* 3��� */
    loop=true;
   do{
      Application->ProcessMessages();
      if(loop==false) {SmsdWrCmd("ST1*");res14=false; goto end;}
      len = sm->ReadCom(&s[slen], AGL_BUF_SIZE - (slen + 1)); //������
      if (len)
      {
         slen += len;
           s[slen] = 0;
          //  memcpy(&s_my,s,slen);  /*����� ������ �� s � s_my */
          //  if(memcmp(s_my,s_ans,4)==0) res10=true;
         if(slen == cmd_len + 4)
           {
            if ((s[slen-4] == 'E') && (s[slen-1] == '*'))
              {
              err_code = atoi(&s[slen-3]);
              if(err_code== 10) {res14=false;res10=true;}
              if(err_code== 14) {res14=true;res10=true;}
              else{
                   if(res10==true){res14=false;res10=true;} /*��� ��� ����� E10*/
                  }
             }
           }
           if (slen == cmd_len + 9)    /* +������ \a  ���� �������� ������ ST1*E10*E14*\a*/
           {
             if ((s[slen-5] == 'E') && (s[slen-2] == '*'))
              {
               err_code = atoi(&s[slen-4]);
               if(err_code== 14){res14=true;res10=true;}
               else{if(res10==true){res14=false;res10=true;}}
            }
           else{
                MsgErr("������ ������ �� ����� �� ������� ��������� ��������� (��� E14)");
               return false;
             }
           }
        } /*if len*/
  // }while (!res10 && !res14 && (GetTickCount() <= t));
     }while ((res14==false) && (GetTickCount() <= t));
   if (!res14)
      MsgErr("������ ������ �� ����� �� ��������� ��������� (��� E14)" );
   end:;
   return res14;
}
//---------------------------------------------------------------------------


