#ifndef __ASBUF_H__
#define __ASBUF_H__
#include <stdlib.h>
#include <extdefs.h>
#include <vcl.h>

typedef unsigned char UCHAR;
typedef struct
{
    int     size;           // размер
    int     length;         // размер данных в байтах
    int     minsize;        // минимальный размер
    int     maxsize;        // максимальный размер
    int     capacity;       // размер для realock-а
    UCHAR*  buf;            // сам буфер.
}ASBUF;

typedef ASBUF* PASBUF;


#define AsbBufPtr(asb)              asb->buf
#define AsbLength(asb)              asb->length
#define AsbPutVal(asb,index,val)    AsbPutBuf(asb,index,(UCHAR*)&val,sizeof(val))


/*
#ifdef __cplusplus
extern "C"
{
#endif
*/
PASBUF  NewAsb(int minsize, int maxsize, int capacity);
void    DelAsb(PASBUF asb);
int     AsbGetCh(PASBUF asb, int index);
int     AsbGetBuf(PASBUF asb, int index,UCHAR *buf, int siz);
int     AsbPutBuf(PASBUF asb, int index, UCHAR* buf, int siz);

/*
#ifdef __cplusplus
};
#endif

*/



#endif