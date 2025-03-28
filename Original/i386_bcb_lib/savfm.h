//---------------------------------------------------------------------------

#ifndef savfmH
#define savfmH
//---------------------------------------------------------------------------
#include <RzCommon.hpp>

void GetSectionName(AnsiString &Name,TComponent *Component);
void SaveFormState(TRzRegIniFile *IniFile,TForm *Form);
void LoadFormState(TRzRegIniFile *IniFile,TForm *Form);

extern bool IsLoadFormState;
extern TRzRegIniFile *ConfigIni;


#define  WMU_FORM_SHOW   (WM_USER+1000)
#define  WMU_FORM_CREATE (WM_USER+1001)


// Ставвится в конструкторе формы
#define RESTORE_FORM_VISIBLE \
        if(ConfigIni == NULL){\
            ConfigIni = new TRzRegIniFile(NULL);\
            ConfigIni->PathType = ptIniFile;\
        }\
        PostMessage(Handle,WMU_FORM_CREATE,0,0);\
        if(ConfigIni->ReadBool(Name,Name+"_Visible",false)){\
            PostMessage(Handle,WMU_FORM_SHOW,0,0);\
        }
// Ставится внутри событий OnHide и OnShow
#define SAVE_FORM_VISIBLE \
        if(ConfigIni == NULL){\
            ConfigIni = new TRzRegIniFile(NULL);\
            ConfigIni->PathType = ptIniFile;\
        }\
        if(Application->Terminated == false){\
            ConfigIni->WriteBool(Name,Name+"_Visible",Visible);\
        }


#define SAVE_FORM_STATE  SaveFormState(NULL,this)
#define LOAD_FORM_STATE  LoadFormState(NULL,this)


#endif
