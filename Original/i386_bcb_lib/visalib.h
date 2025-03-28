#ifndef VISALIB_H
#define VISALIB_H

#include <visa.h>
#include <extdefs.h>

typedef struct
{
    ViSession    vis;
    char         name[100];
}G44_HANDLER;

typedef struct
{
    ViSession    vis;
    char         name[100];
}NEX_HANDLER;

typedef struct
{
    ViSession    vis;
    char         name[100];
}LSA_HANDLER;

typedef struct
{
    ViSession    vis;
    char         name[100];
}N19_HANDLER;


#define USA_UNK 0
#define USA_NEX 1
#define USA_LSA 2

typedef struct
{
    int type;
    NEX_HANDLER  nex;
    LSA_HANDLER  lsa;
}USA_HANDLER;


typedef struct
{
    u32     sig[2];
    u32     stat;

}GIU_HANDLER;

extern ViSession  VlHandle;

void OpenVisa(void);
void CloseVisa(void);

bool USA_Open(USA_HANDLER *h,char *name);


void G44_SetIntPulm_mks(G44_HANDLER *h,bool on,int di,int pp);
bool G44_Open(G44_HANDLER *h,char *name);
void G44_Close(G44_HANDLER *h);
void G44_ExtFmOn(G44_HANDLER *h);
void G44_ExtFmOff(G44_HANDLER *h);
void G44_ExtPulmOn(G44_HANDLER *h);
void G44_SetFmFreq_Hz(G44_HANDLER *h, int freq);

void G44_SetRfOn(G44_HANDLER *h);
void G44_SetRfOff(G44_HANDLER *h);
void G44_SetFreq_Hz(G44_HANDLER *h, int freq);
void G44_SetFreq_MHz(G44_HANDLER *h, int freq);

void G44_SetNumFreq(G44_HANDLER *h, int nget);      // установка номера частоты гетеродина
void G44_SetAmp_dBm(G44_HANDLER *h,float amp);
void G44_SetIntPulm_mks(G44_HANDLER *h,bool on,int di,int pp);
void G44_SetModOn(G44_HANDLER *h);
void G44_SetModOff(G44_HANDLER *h);
void G44_Reset(G44_HANDLER *h);


void GIU_Open(GIU_HANDLER *h);
void GIU_Close(GIU_HANDLER *h);
void GIU_SetDelay_mks(GIU_HANDLER *h,int num, float delay);
void GIU_SetDlit_mks(GIU_HANDLER *h,int num, float d);
void GIU_SetPeriod_mks(GIU_HANDLER *h,int num,float d);
void GIU_SetCikl(GIU_HANDLER *h,int num);
void GIU_SetOnce(GIU_HANDLER *h,int num);
void GIU_SetDown(GIU_HANDLER *h,int num);
void GIU_SetUp(GIU_HANDLER *h,int num);
void GIU_Start(GIU_HANDLER *h);
void GIU_Stop(GIU_HANDLER *h);

bool NEX_Open(NEX_HANDLER *h,char *name);
void NEX_Close(NEX_HANDLER *h);
//void NEX_SetCFreq_MHz(NEX_HANDLER *h,float fval);
float NEX_GetMkA(NEX_HANDLER *h);
void NEX_SetCF_MHz(NEX_HANDLER *h,float fval);
void NEX_SetRBW_MHz(NEX_HANDLER *h,float fval);
void NEX_SetSP_MHz(NEX_HANDLER *h,float fval);
void NEX_SetCF_RBW_SP_MHz(NEX_HANDLER *h,float cf,float rbw,float sp);
void NEX_CalOff(NEX_HANDLER *h);

bool LSA_Open(NEX_HANDLER *h,char *name);
void LSA_Close(NEX_HANDLER *h);
float LSA_GetMkA(NEX_HANDLER *h);
void LSA_SetCF_MHz(NEX_HANDLER *h,float fval);
void LSA_SetRBW_MHz(NEX_HANDLER *h,float fval);
void LSA_SetSP_MHz(NEX_HANDLER *h,float fval);
void LSA_SetCF_RBW_SP_MHz(NEX_HANDLER *h,float cf,float rbw,float sp);
void LSA_CalOff(NEX_HANDLER *h);

bool USA_Open(USA_HANDLER *h,char *name);
void USA_Close(USA_HANDLER *h);
float USA_GetMkA(USA_HANDLER *h);
void USA_SetCF_MHz(USA_HANDLER *h,float fval);
void USA_SetRBW_MHz(USA_HANDLER *h,float fval);
void USA_SetSP_MHz(USA_HANDLER *h,float fval);
void USA_SetCF_RBW_SP_MHz(USA_HANDLER *h,float cf,float rbw,float sp);
void USA_CalOff(USA_HANDLER *h);


bool N19_Open(N19_HANDLER *h,char *name);
void N19_Close(N19_HANDLER *h);
float N19_GetA_dBm(int n,N19_HANDLER *h);



#endif
