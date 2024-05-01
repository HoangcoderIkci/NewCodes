#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define U64 uint64_t
#define U32 uint32_t
#define U16 uint16_t
#define U8 uint8_t

#define I64 int64_t
#define I32 int32_t
#define I16 int16_t
#define I8 int8_t
#define loop(i, a, b) for (U64 i = a; i < b; i++)

U8 zbytel(U32 x)
{
    if ((x >> 24) == 0)
        return 0;
    if ((x & 0x00FF0000) == 0)
        return 1;
    if ((x & 0x0000FF00) == 0)
        return 2;
    if ((x & 0x000000FF) == 0)
        return 3;
    return 4;
}

U8 zbyter(U32 x)
{
    if ((x >> 24) == 0)
        return 3;
    if ((x & 0x00FF0000) == 0)
        return 2;
    if ((x & 0x0000FF00) == 0)
        return 1;
    if ((x & 0x000000FF) == 0)
        return 0;
    return 4;
}

int main()
{

    return 0;
}