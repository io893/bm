#ifndef EXTDEFS_H
#define EXTDEFS_H

typedef unsigned long ULONG;
typedef unsigned int  UINT;
typedef unsigned char UCHAR;

typedef unsigned __int64    U64;
typedef unsigned int        U32;
typedef int  		        I32;
typedef unsigned char       U8;
typedef char  		        I8;
typedef unsigned short      U16;
typedef short  		        I16;

typedef U32           PKWORD;

typedef unsigned __int64    u64;
typedef __int64    i64;
typedef unsigned int        u32;
typedef int  		        i32;
typedef unsigned char       u8;
typedef char  		        i8;
typedef unsigned short      u16;
typedef short  		        i16;



#ifndef NULL
#define NULL 0
#endif

#ifndef __cplusplus

#ifndef TRUE
    typedef unsigned char BOOL;
    #define TRUE (!0)
    #define FALSE 0
#endif
#endif


#define SIZE(dim) (sizeof((dim))/sizeof((dim)[0]))
#define MIN(a,b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

#define SET_MASK(v,m) (v) |= (m)
#define CLR_MASK(v,m) (v) &= (~m)


/*
 *   val   - данные
 *   base  - базовый адр
 *   byte  - номер байта
 *
 */

#define PACKCHAR(val, base, byte) ( ((byte)%4 == 0) ?                   \
	 (*((base) + ((byte)/4))  = ((val) & 0xFF)) :                       \
	 (*((base) + ((byte)/4)) |= ((val) & 0xFF) << (((byte)%4) * 8)) )

#define PACK8(val, base, byte) ( ((byte)%4 == 0) ?                   \
	 (*((base) + ((byte)/4))  = ((val) & 0xFF)) :                       \
	 (*((base) + ((byte)/4)) |= ((val) & 0xFF) << (((byte)%4) * 8)) )

#define UNPACK8(base, byte) \
         ( (*((base) + ((byte)/4)) >> (((byte)%4) * 8)) & 0xFF )

#define PACK16(val, base, n16) ( ((n16)%2 == 0) ?                    	\
	 (*((base) + ((n16)/2))   = ((val) & 0xFFFF)) :                     \
	 (*((base) + ((n16)/2))  |= ((val) & 0xFFFF) << 16) )

#define UNPACK16(base, n16) \
     ((*((base) + ((n16)/2)) >> (((n16)%2) * 16)) & 0xFFFF)



#endif  // EXTDEFS_H
