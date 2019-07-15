#ifndef _TYPEDF_H
#define _TYPEDF_H

#define true	1
#define false	0

#define __AT_SEC(X)			__attribute__((section(X)))
#define __AT_ADDR(X)	  __attribute__((AT(X)))
#define __USED          __attribute__((used))
#define __ALIGN(n)      __attribute__((aligned(n)))

typedef char			bool;			

/* exact-width signed integer types */
typedef signed           char s8;
typedef signed short     int s16;
typedef signed           int s32;


/* exact-width unsigned integer types */
typedef unsigned          char u8;
typedef unsigned short    int u16;
typedef unsigned          int u32;
typedef unsigned long long	  u64;



















#endif









