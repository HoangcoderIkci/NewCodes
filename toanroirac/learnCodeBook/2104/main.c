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
#define gloN 5
#define gloLength 32
U8 *globalTable = NULL;

I32 popWord(U32 x)
{
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x0000003F;
}

U32 snoob(U32 x)
{
    U32 smallest, ripple, ones;    // x = xxx0 1111 0000
    smallest = x & -x;             // 0000 0001 0000
    ripple = x + smallest;         // xxx1 0000 0000
    ones = x ^ ripple;             // 0001 1111 0000
    ones = (ones >> 2) / smallest; // 0000 0000 0111
    return ripple | ones;          // xxx1 0000 0111
}

U32 snoob2(U32 x)
{
    U32 smallest, ripple, ones; // x = xxx0 1111 0000
    smallest = x & -x;          // 0000 0001 0000
    ripple = x + smallest;      // xxx1 0000 0000
    return ripple | ((1 << (popWord(x ^ ripple) - 2)) - 1);
}

void thresholdFunction()
{
    globalTable[0] = 0;
    U32 f = 0;
    f = 0x1;
    loop(i, 1, (1 + gloN) >> 1)
    {
        f = (1 << i) - 1;
        while (f < gloLength)
        {
            globalTable[f] = 0;
            printf("f = %u\n", f);
            f = snoob2(f);
        }
    }
}

I32 myAbs(I32 x)
{
    I32 y = x >> 31;
    printf("y = %u\n", y);
    printf("x^y = %u\n", x ^ y);
    return (x ^ y) - y;
}
int ntz(unsigned x)
{
    int n;
    if (x == 0)
        return (32);
    n = 1;
    if ((x & 0x0000FFFF) == 0)
    {
        n = n + 16;
        x = x >> 16;
    }
    if ((x & 0x000000FF) == 0)
    {
        n = n + 8;
        x = x >> 8;
    }
    if ((x & 0x0000000F) == 0)
    {
        n = n + 4;
        x = x >> 4;
    }
    if ((x & 0x00000003) == 0)
    {
        n = n + 2;
        x = x >> 2;
    }
    return n - (x & 1);
}
int nlz(unsigned x)
{
    int n;
    if (x == 0)
        return (32);
    n = 1;
    if ((x >> 16) == 0)
    {
        n = n + 16;
        x = x << 16;
    }
    if ((x >> 24) == 0)
    {
        n = n + 8;
        x = x << 8;
    }
    if ((x >> 28) == 0)
    {
        n = n + 4;
        x = x << 4;
    }
    if ((x >> 30) == 0)
    {
        n = n + 2;
        x = x << 2;
    }
    n = n - (x >> 31);
    return n;
}
unsigned flp2(unsigned x)
{
    return 0x80000000 >> nlz(x);
}
int main() // trang 58
{
    unsigned x = 17;
    I8 y = -8;
    printf("x = %u\n", flp2(x));
    // globalTable = (U8 *)malloc(sizeof(U8) * gloLength);
    // memset(globalTable, 1, gloLength);
    // thresholdFunction();
    // loop(i, 0, gloLength)
    //     printf("%u,", globalTable[i]);
    // printf("\n");
    // free(globalTable);
    return 0;
}