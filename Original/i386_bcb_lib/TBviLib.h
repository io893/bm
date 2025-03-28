//---------------------------------------------------------------------------

#ifndef TBviLibH
#define TBviLibH
//---------------------------------------------------------------------------
#include <TFmLib.h>

typedef void __fastcall (__closure *TBlOnRcvPack) (int src,int nkio,u32 *buf);

class TBviLib
{
    private:
        TOnRcvKioPack   FOnRcvKioPack;
        TBlOnRcvPack    FOnRcv;

        void __fastcall OnRcvKioPack(u32 nk,u32* buf);

    public:
        __fastcall TBviLib();
        __fastcall ~TBviLib(){};

        void __fastcall ProcessRcv(void);
        bool __fastcall SendPack(int dst,int nkio,u32* buf32);



    __property TBlOnRcvPack OnRcvPack  = { read  = FOnRcv,
                                           write = FOnRcv  };

};

extern TBviLib *BviLib;


#endif
