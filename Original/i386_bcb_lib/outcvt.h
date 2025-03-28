#ifndef ___OUTCVT_H___

#define ___OUTCVT_H___

#include "asbuf.h"

#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>

enum OCMODE {VC33SL,VC33F8,VC33F16};

void OutFileCvt(OCMODE mode,AnsiString file,PASBUF binbuf);


#endif  /* ___OUTCVT_H___ */