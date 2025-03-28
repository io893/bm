//---------------------------------------------------------------------------


#pragma hdrstop

#include "ARM.h"
#include "StrUtils.hpp"

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool TForm1::FindDevises(void)
{
	ViSession vi;
	char  instrDesc[256];
	ViUInt32 retcnt;
	int koldev;
	ViUInt32    Cnt;
	char buff[256];
	ViFindList  findList;
	AnsiString S,Str,StrTCP;
	Devs.clear();
	Panel6->Visible=true;
	Label8->Caption="Обнаружение и идентификация измерительных приборов";
	Label8->Repaint();
	Label8->Visible=true;
	//Panel6->Show();
	if(rm!=0)
	 viClose(rm);
	status = viOpenDefaultRM(&rm);
	if (status < VI_SUCCESS)
	{
		viClose(rm);
		Application->MessageBox("Ошибка менеджера ресурсов","VISA", MB_ICONERROR| MB_OK);
		Panel6->Visible=false;
		return false;
	}
	status=viFindRsrc(rm,"?*INSTR",&findList, &retcnt,instrDesc);
	if(status<VI_SUCCESS)
	{
		if(status==VI_ERROR_RSRC_NFOUND)
			Application->MessageBox("Подключите генератор и измеритель мощности к компьютеру","Нет подключений", MB_ICONERROR| MB_OK);
		else
			Application->MessageBox("Ошибка подключения","VISA", MB_ICONERROR| MB_OK);
		viClose(rm);
		Panel6->Visible=false;
		return false;
	} //if    ststus findRsrc
	koldev=retcnt;
	StrTCP=Trim(AnsiString(instrDesc)) ;
	status = viOpen(rm, StrTCP.c_str(), VI_NULL, VI_NULL, &vi);
	if(!(status<VI_SUCCESS))
	{
		S="*IDN?\n";
		status = viWrite(vi, (ViBuf)S.c_str(),S.Length(), &Cnt);
		if(status<VI_SUCCESS)
		{
			Str="Ошибка запроса"+S;
			Application->MessageBox(Str.c_str(),StrTCP.c_str(), MB_ICONERROR| MB_OK);
			viClose(vi);
			viClose(rm);
			Panel6->Visible=false;
			return false;
		}
		status = viRead(vi, buff, sizeof(buff), &Cnt);
		if(status<VI_SUCCESS)
		{
			Str="Ошибка чтения";
			Application->MessageBox(Str.c_str(),StrTCP.c_str(), MB_ICONERROR| MB_OK);
			viClose(vi);
			viClose(rm);
			Panel6->Visible=false;
			return false;
		}
		S=AnsiString(buff,Cnt) ;
		lstDevice->Items->Strings[0] = S;
 if(IdtfDev(S,StrTCP,vi)==false)
		{
			Panel6->Visible=false;
			return false;
		}                          /*    */
		Devs.insert(Devs.end(),MDvs);

	}// if status
	koldev--;   // первый прибор уже идентифицирован
	// искать следующие приборы
	int i = 1;
	while (koldev>0)
	{
		status=viFindNext(findList, instrDesc);
		if(!(status<VI_SUCCESS))
		{
			StrTCP=Trim(AnsiString(instrDesc)) ;
			status = viOpen(rm, StrTCP.c_str(), VI_NULL, VI_NULL, &vi);
			if(!(status<VI_SUCCESS))
			{
				S="*IDN?\n";
				status = viWrite(vi, (ViBuf)S.c_str(),S.Length(), &Cnt);
				if(status<VI_SUCCESS)
				{
					Str="Ошибка запроса"+S;
					Application->MessageBox(Str.c_str(),StrTCP.c_str(), MB_ICONERROR| MB_OK);
					viClose(vi);
					viClose(rm);
					Panel6->Visible=false;
					return false;
				}
				status = viRead(vi, buff, sizeof(buff), &Cnt);
				if(status<VI_SUCCESS)
				{
					Str="Ошибка чтения";
					Application->MessageBox(Str.c_str(),StrTCP.c_str(), MB_ICONERROR| MB_OK);
					viClose(vi);
					viClose(rm);
					Panel6->Visible=false;
					return false;
				}
				S = AnsiString(buff,Cnt) ;
				lstDevice->Items->Strings[i] = S.c_str();
	 if(IdtfDev(S,StrTCP,vi)==false)
				{
					Panel6->Visible=false;
					return false;
				}                      /*  */
				Devs.insert(Devs.end(),MDvs);      
			}//  status
			koldev--;     i++;
		}//status
	}
	viClose(vi);
	viClose(rm);
	Panel6->Visible=false;
	return true;
}

bool TForm1::IdtfDev(AnsiString S,AnsiString STCP, ViSession vi)
{
	int i;
	AnsiString SubStr[6]={"E8257D", "N5181A", "N1911A", "E4412A","E4407B","N1912A"};
	for(i=0;i<6;i++)
	{
		if(AnsiContainsText(S, SubStr[i]))
		{
			if((SubStr[i]=="N1911A")||(SubStr[i]=="E4412A")||(SubStr[i]=="N1912A") )
				MDvs.distn=2;                 //измеритель мощности
			else if((SubStr[i]=="N5118A")||(SubStr[i]=="E8257D"))
				MDvs.distn=1;                  //генератор
			else if(SubStr[i]=="E4407B")           //анализатор спектра
				MDvs.distn=3;
			MDvs.TCP=STCP;
			MDvs.Vi=vi;
			return true;
		}
	  // if
	}  //for
	Application->MessageBox("Измерительная аппаратура не идентифицированна" ,"", MB_ICONERROR| MB_OK);
 	return false;
}


bool TForm1::ChekDev(void)
{
	// ViSession rm;
	int n, i;
	AnsiString SPg;
	ChkDevs=false;
	n=Devs.size();
	for(i=0; i<n; i++)
	{
		if(Devs[i].distn==1)
		{
			viG=Devs[i].Vi;
			TCPG= Devs[i].TCP;
		}
		else if( Devs[i].distn==2)
		{
			viP=Devs[i].Vi ;
			TCPP=Devs[i].TCP;
		}
		else if( Devs[i].distn==3)
		{
			viA=Devs[i].Vi ;
			TCPA=Devs[i].TCP;
		}
	}  //for
	status =  viOpenDefaultRM(&rm);
	if(status<0){
		Application->MessageBox("Ошибка менеджера ресурсов","VISA", MB_ICONERROR| MB_OK);
		return false;
	}
	else {
		if(viOpen(rm, TCPP.c_str(), VI_NULL, VI_NULL, &viP)<0)
		{
			while(Application->MessageBox("Подключите измеритель мощности","Ошибка подключения", MB_ICONINFORMATION|MB_OKCANCEL)!=IDCANCEL)
			{


				if(viOpen(rm, TCPP.c_str(), VI_NULL, VI_NULL, &viP)>=0) break;
			}
			return true;

		}

		if(viOpen(rm, TCPG.c_str(), VI_NULL, VI_NULL, &viG)<0)
		{
			while( Application->MessageBox("Подключите генератор","Ошибка подключения", MB_ICONINFORMATION|MB_OKCANCEL)!=IDCANCEL)
			{
				int s=viOpen(rm, TCPP.c_str(), VI_NULL, VI_NULL, &viG);
				if(s>=0) break;// goto M1;    //(viOpen(rm, TCPP.c_str(), VI_NULL, VI_NULL, &viG)>0)
			}
			return true;
		}
		if((viP!=0)&&(viG!=0))
			ChkDevs=true;
		return ChkDevs;
	}
	//return true;
}
bool TForm1::ChekPrib(String adress, ViSession *vi)
{
	if(rm==0)
		status =  viOpenDefaultRM(&rm);
	if(status<0){
		Application->MessageBox("Ошибка менеджера ресурсов","VISA", MB_ICONERROR| MB_OK);
		return false;
	}
	else {

		if(status = viOpen(rm, adress.c_str(), VI_NULL, VI_NULL, vi)<0)
		{
			while( Application->MessageBox("Подключите прибор" ,"Ошибка подключения", MB_ICONINFORMATION|MB_OKCANCEL)!=IDCANCEL)
			{
				int s=viOpen(rm, TCPP.c_str(), VI_NULL, VI_NULL, vi);
				if(s>=0) {
					status = s;
					break;
				}// goto M1;    //(viOpen(rm, TCPP.c_str(), VI_NULL, VI_NULL, &viG)>0)
			}

		}

	}
	if(*vi>0) {return true;} else {return false;}
}

void TForm1::InitPowMtr(void)
{
 AnsiString SUp;
  SUp="DBM\n" ;
Init1911A(SUp);
}

