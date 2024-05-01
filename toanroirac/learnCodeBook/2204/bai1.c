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

U32 flip(U32 x) // tim số dạng 2^n gần với x ở dưới
{
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return x - (x >> 1);
}
U32 clip(U32 x) // tim số dạng 2^n gần với x ở trên
{
    x -= 1;
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return x + 1;
}

U8 populationCount1(U32 x)
{
    x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F);
    x = (x & 0x00FF00FF) + ((x >> 8) & 0x00FF00FF);
    x = (x & 0x0000FFFF) + ((x >> 16) & 0x0000FFFF);
    return x;
}

U8 pop4Bit(U32 x)
{
    U32 n;
    n = (x >> 1) & 0x77777777; // Подсчет битов
    x = x - n;                 // в 4-битовых
    n = (n >> 1) & 0x77777777; // полях
    x = x - n;
    n = (n >> 1) & 0x77777777;
    x = x - n;
    x = (x + (x >> 4)) & 0x0F0F0F0F; // Вычисление сумм
    x = x * 0x01010101;              // Сложение байтов
    return x >> 24;
}

U8 litlePop(U32 x)
{
    U8 n;
    n = 0;
    while (x != 0)
    {
        n = n + 1;
        x = x & (x - 1);
    }
    return n;
}

U8 ParityWord(U32 x)
{
    x ^= x >> 1;
    x ^= x >> 2;
    x ^= x >> 4;
    x ^= x >> 8;
    x ^= x >> 16;
    return x & 0x1;
}

int main()
{
    loop(a, 3, 10)
    {
        printf("clip(%u) = %u\n", a, clip(a));
    }
    return 0;
}