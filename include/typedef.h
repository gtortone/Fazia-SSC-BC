#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

#include <Generic.h>

#define __EXTENSION __extension__
#define __PACKED

typedef unsigned long long UINT64;

typedef union
{
    UINT64 Val;
    UINT32 d[2] __PACKED;
    UINT16 w[4] __PACKED;
    UINT8 v[8] __PACKED;

    struct __PACKED
    {
        UINT32 LD;
        UINT32 HD;
    } dword;

    struct __PACKED
    {
        UINT16 LW;
        UINT16 HW;
        UINT16 UW;
        UINT16 MW;
    } word;

    struct __PACKED
    {
        __EXTENSION UINT8 b0:1;
        __EXTENSION UINT8 b1:1;
        __EXTENSION UINT8 b2:1;
        __EXTENSION UINT8 b3:1;
        __EXTENSION UINT8 b4:1;
        __EXTENSION UINT8 b5:1;
        __EXTENSION UINT8 b6:1;
        __EXTENSION UINT8 b7:1;
        __EXTENSION UINT8 b8:1;
        __EXTENSION UINT8 b9:1;
        __EXTENSION UINT8 b10:1;
        __EXTENSION UINT8 b11:1;
        __EXTENSION UINT8 b12:1;
        __EXTENSION UINT8 b13:1;
        __EXTENSION UINT8 b14:1;
        __EXTENSION UINT8 b15:1;
        __EXTENSION UINT8 b16:1;
        __EXTENSION UINT8 b17:1;
        __EXTENSION UINT8 b18:1;
        __EXTENSION UINT8 b19:1;
        __EXTENSION UINT8 b20:1;
        __EXTENSION UINT8 b21:1;
        __EXTENSION UINT8 b22:1;
        __EXTENSION UINT8 b23:1;
        __EXTENSION UINT8 b24:1;
        __EXTENSION UINT8 b25:1;
        __EXTENSION UINT8 b26:1;
        __EXTENSION UINT8 b27:1;
        __EXTENSION UINT8 b28:1;
        __EXTENSION UINT8 b29:1;
        __EXTENSION UINT8 b30:1;
        __EXTENSION UINT8 b31:1;
        __EXTENSION UINT8 b32:1;
        __EXTENSION UINT8 b33:1;
        __EXTENSION UINT8 b34:1;
        __EXTENSION UINT8 b35:1;
        __EXTENSION UINT8 b36:1;
        __EXTENSION UINT8 b37:1;
        __EXTENSION UINT8 b38:1;
        __EXTENSION UINT8 b39:1;
        __EXTENSION UINT8 b40:1;
        __EXTENSION UINT8 b41:1;
        __EXTENSION UINT8 b42:1;
        __EXTENSION UINT8 b43:1;
        __EXTENSION UINT8 b44:1;
        __EXTENSION UINT8 b45:1;
        __EXTENSION UINT8 b46:1;
        __EXTENSION UINT8 b47:1;
        __EXTENSION UINT8 b48:1;
        __EXTENSION UINT8 b49:1;
        __EXTENSION UINT8 b50:1;
        __EXTENSION UINT8 b51:1;
        __EXTENSION UINT8 b52:1;
        __EXTENSION UINT8 b53:1;
        __EXTENSION UINT8 b54:1;
        __EXTENSION UINT8 b55:1;
        __EXTENSION UINT8 b56:1;
        __EXTENSION UINT8 b57:1;
        __EXTENSION UINT8 b58:1;
        __EXTENSION UINT8 b59:1;
        __EXTENSION UINT8 b60:1;
        __EXTENSION UINT8 b61:1;
        __EXTENSION UINT8 b62:1;
        __EXTENSION UINT8 b63:1;
    } bits;
} UINT64_VAL;

#endif

// EOF
