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
#define glo_n 4
// const U32 glo_length = 1 << glo_n;
#define glo_length 16
void fastFindCoefficientsFourier(I8 *lst_coefficients)
{
    U64 half_len;
    U64 full_len;
    U64 num_turns;
    I8 *ptr1;
    I8 *ptr2;
    loop(idx1, 0, glo_n)
    {
        half_len = 1 << idx1;
        full_len = half_len << 1;
        num_turns = glo_length / full_len;
        loop(idx2, 0, num_turns)
        {
            ptr1 = lst_coefficients + idx2 * full_len;
            ptr2 = ptr1 + half_len;
            loop(idx3, 0, half_len)
            {
                ptr1[idx3] += ptr2[idx3];
                ptr2[idx3] = ptr1[idx3] - (ptr2[idx3] * 2);
            }
        }
    }
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

U8 rankResilient(I8 *trustTable)
{
    // bien doi Walsha
    // loop(i, 0, glo_length) if (trustTable[i])
    //     trustTable[i] = -1;
    // else trustTable[i] = 1;
    // printf("\n");
    fastFindCoefficientsFourier(trustTable);
    I32 sum = 0; //
    loop(i, 0, glo_length)
        sum += trustTable[i];
    if (sum)
        return 0;
    U32 temp;
    for (U8 k = 1; k <= glo_n; k++)
    {
        temp = (1 << k) - 1; //
        do
        {
            if (trustTable[temp])
                return k - 1;
            // printf("temp = %u\n", temp);
            temp = snoob(temp);
        } while (temp < glo_length);
    }
    return 0; //
}
U8 rankCorrelationImmune(I8 *trustTable)
{
    // bien doi Walsha
    // loop(i, 0, glo_length) if (trustTable[i])
    //     trustTable[i] = -1;
    // else trustTable[i] = 1;
    // printf("\n");
    fastFindCoefficientsFourier(trustTable);
    // I32 sum = 0; //
    // loop(i, 0, glo_length)
    // {
    //     sum += trustTable[i];
    //     printf("%d,", trustTable[i]);
    // }
    // printf("\nsum = %d\n", sum); //
    // check k
    U32 temp;
    for (U8 k = 1; k <= glo_n; k++)
    {
        temp = (1 << k) - 1; //
        do
        {
            if (trustTable[temp])
                return k - 1;
            // printf("temp = %u\n", temp);
            temp = snoob(temp);
        } while (temp < glo_length);
    }
    return 0; //
}
I8 *findFunctionWithRankCI(U8 rank)
{
    I8 *trustTable = (I8 *)malloc(sizeof(I8) * glo_length);
    U64 f_temp = 0;
    U64 idx1 = 0;
    U8 currentRank = 0;
    U64 maxSize = 1ULL << glo_length;

    U64 start = maxSize - (maxSize >> 6);
    loop(f, start, maxSize)
    {
        f_temp = f;
        memset(trustTable, 0, glo_length);

        idx1 = 0;
        while (f_temp)
        {
            trustTable[idx1++] = f_temp & 0b1;
            f_temp >>= 1;
        }
        // loop(i, 0, glo_length)
        //     printf("%d,", trustTable[i]);
        // printf("\n");
        currentRank = rankCorrelationImmune(trustTable);
        // printf("currentRank = %llu\n", currentRank);
        if (currentRank >= rank)
        {
            printf("f = %llx ,currentRank = %u\n", f, currentRank);
            // break;
        }
    }

    return trustTable; //
}

int main()
{
    // I8 tab[4] = {0, 0, 0, 1};
    // //  1,-1,-1,1,-1,1,1,-1,-1,1,1,-1,1,-1,-1,1
    I8 tab[16] = {0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1};
    // fastFindCoefficientsFourier(tab);
    int res = rankResilient(tab);
    printf("%d", res);
    printf("\n");
    // loop(i, 0, glo_n)
    //     printf("%d,", tab[i]);
    // printf("\n");
    //   U8 res = rankCorrelationImmune(tab);
    // I8 *trustTable = findFunctionWithRankCI(2);
    // loop(i, 0, glo_length)
    //     printf("%d,", trustTable[i]);
    // printf("\n");
    // free(trustTable);
    return 0;
}