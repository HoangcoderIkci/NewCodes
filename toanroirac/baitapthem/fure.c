#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#define U64 uint_fast64_t
#define U32 uint_fast32_t
#define U16 uint_fast16_t
#define U8 uint_fast8_t
#define loop(i, a, n) for (U32 i = a; i < n; i++)
#define loopBack(i, n, a) for (int i = n; i >= a; i--)
#define getBitIndex(x, idx) (((x) >> (idx)) & 1)     // get bit tại index
#define setBitIndex(x, idx) ((x) |= (1 << (idx)))    // set bit tại index = 1
#define clearBitIndex(x, idx) ((x) &= ~(1 << (idx))) // clear bit tại index = 0
#define getHighBit(x) ((x >> (size - 1)) & 0b1)
U64 size = 3;
#define registerBit(x) ((x << 1 | x >> (size - 1)) & gioihan)

void process1(U32 F)
{
    U32 len_bit, temp_bit, num_turn, t;
    U32 len_func = (1 << size);
    loop(idx1, 0, size)
    {
        len_bit = (1 << idx1);
        num_turn = len_func / len_bit;
        num_turn >>= 1;
        loop(idx2, 0, num_turn)
        {
            loop(idx3, 0, len_bit)
            {
                temp_bit = getBitIndex(F, (idx2 * len_bit * 2 + idx3));
                if (temp_bit)
                    F ^= (1 << (idx2 * len_bit * 2 + len_bit + idx3));
            }
        }
        t = F;
        loop(idx1, 0, len_func)
        {
            if (F & 0b1)
                printf("1 ");
            else
                printf("0 ");
            F >>= 1;
        }
        printf("\n");
        F = t;
    }
    // printf("F = %d\n", F);
    loop(idx1, 0, len_func)
    {
        if (F & 0b1)
            printf("1 ");
        else
            printf("0 ");
        F >>= 1;
    }

    printf("\n");
}

void process2(U32 F[])
{
    U32 len_bit, temp_bit, num_turn, t, idx_temp;
    U32 len_func = (1 << size);
    loop(idx1, 0, size)
    {
        len_bit = (1 << idx1);
        num_turn = len_func / len_bit;
        num_turn >>= 1;
        loop(idx2, 0, num_turn)
        {
            loop(idx3, 0, len_bit)
            {
                idx_temp = idx2 * len_bit * 2 + idx3;
                F[idx_temp + len_bit] -= F[idx_temp];
            }
        }
    }
    loop(idx1, 0, len_func)
    {
        printf("%d ", F[idx1]);
    }
    printf("\n");

    // printf("\n");
}

int main()
{
    U32 F[] = {0,
               0,
               0,
               1,
               0,
               1,
               1,
               1};
    process2(F);
    return 0;
}