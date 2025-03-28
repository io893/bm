#ifndef ___HEXCVT_H___

#define ___HEXCVT_H___

#include "asbuf.h"
/*
#ifdef __cplusplus
extern "C"
{
#endif
*/
void HexFileCvt(char* file,PASBUF binbuf);
void HexBufCvt(PASBUF hexbuf,PASBUF binbuf);

/*
#ifdef __cplusplus
};
#endif

*/

#endif  /* ___HEXCVT_H___ */
