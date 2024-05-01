#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
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
#define glo_length 16 // 16 65536ULL // 20 - 1048576 // 24 16777216ULL//28 268435456ULL // 30 1073741824  //32 4294967296
// U8 arrA[] = {0, 1, 1, 1, 0, 0, 0, 0, 1};

//[0, 0, 0, 0]
// [ 0, 0, 0, 1 ]
//     [0, 0, 1, 0]
//     [0, 0, 1, 1]
//     [0, 1, 0, 0]
//     [0, 1, 0, 1]
//     [0, 1, 1, 0]
//     [0, 1, 1, 1]
//     [1, 0, 0, 0]
//     [1, 0, 0, 1]
//     [1, 0, 1, 0]
//     [1, 0, 1, 1]
//     [1, 1, 0, 0]
//     [1, 1, 0, 1]
//     [1, 1, 1, 0]
//     [1, 1, 1, 1]
// U8 arrA[] = {0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1};

U16 arrResult[glo_length];
U64 glo_index = 1;

mpz_t *mpzArrSupport;
void createArraySupport()
{
    mpz_t limitBlock, limitCurrentBlock, sp, one, temp1, temp2;
    // printf("start2\n");
    //  mpz_init2(doubleLenBlock, 256);
    mpz_init2(limitBlock, glo_length);
    mpz_init2(limitCurrentBlock, glo_length);
    mpz_init2(sp, glo_length);
    mpz_init2(one, glo_length);
    mpz_init2(temp1, glo_length);
    mpz_init2(temp2, glo_length);
    U64 doubleLenBlock = glo_length >> 1;
    // mpz_set_ui(doubleLenBlock, glo_length >> 1);
    // mpz_set_ui(lengthBlock, glo_length >> 2);
    mpz_set_ui(one, 1);
    mpz_mul_2exp(temp1, one, glo_length >> 2);
    mpz_mul_2exp(temp2, one, glo_length >> 1);
    mpz_sub(limitBlock, temp1, one);
    mpz_sub(temp2, temp2, one);

    mpz_set(mpzArrSupport[1], temp2);

    mpz_set(limitCurrentBlock, limitBlock);
    mpz_set_ui(sp, 0);

    // U64 doubleLenBlock = glo_length >> 1;
    // U64 limitBlock = ((1ULL) << (glo_length >> 2)) - 1;
    // U64 limitCurrentBlock = limitBlock;
    U64 numTurn = 2;
    // U64 sp = 0;
    loop(k, 2, glo_n + 1)
    {
        mpz_set_ui(sp, 0);
        loop(id, 0, numTurn)
        {
            // sp ^= limitBlock;
            mpz_xor(sp, sp, limitBlock);
            mpz_mul_2exp(limitBlock, limitBlock, doubleLenBlock);
            // limitBlock <<= doubleLenBlock;
        }
        // arrSupport[k] = sp;
        mpz_set(mpzArrSupport[k], sp);
        // mpz_tdiv_q_2exp(doubleLenBlock, doubleLenBlock, 1); // Dịch phải f đi n bit
        doubleLenBlock >>= 1;
        // limitCurrentBlock >>= (doubleLenBlock >> 1);
        mpz_tdiv_q_2exp(limitCurrentBlock, limitCurrentBlock, (doubleLenBlock >> 1)); // Dịch phải f đi n bit
        // limitBlock = limitCurrentBlock;
        mpz_set(limitBlock, limitCurrentBlock);
        numTurn <<= 1;
    }
    // printf("start2\n");
    mpz_clears(limitBlock, limitCurrentBlock, sp, one, temp1, temp2, NULL);
    // return;
}

void initArrayMpz()
{
    U16 array_size = glo_n + 1;
    mpzArrSupport = (mpz_t *)malloc(array_size * sizeof(mpz_t));

    for (int i = 0; i < array_size; i++)
    {
        mpz_init(mpzArrSupport[i]); // Khởi tạo từng phần tử trong mảng
    }
}
void clearArrayMpz()
{
    U16 array_size = glo_n + 1;
    for (int i = 0; i < array_size; i++)
    {
        mpz_clear(mpzArrSupport[i]); // xóa từng phần tử trong mảng
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

void fastZhegalkin(mpz_t f)
{
    mpz_t temp1;
    mpz_init(temp1);
    U64 halfLengthBlock = glo_length >> 1;
    loop(i, 1, glo_n + 1)
    {
        mpz_and(temp1, f, mpzArrSupport[i]);
        mpz_mul_2exp(temp1, temp1, halfLengthBlock); // Dịch phải f đi n bit
        mpz_xor(f, f, temp1);
        // gmp_printf("Result: %Zx\n", f);
        halfLengthBlock >>= 1;
    }
    mpz_clear(temp1);
    // return f;
}

U32 countRank(mpz_t f)
{
    fastFourierTransform(f);
    U32 temp;
    for (U8 k = 1; k <= glo_n; k++)
    {
        temp = (1 << k) - 1; //
        do
        {
            if (mpz_tstbit(f, temp))
                return k - 1;
            // printf("temp = %u\n", temp);
            temp = snoob(temp);
        } while (temp < glo_length);
    }
    return 0; //
}

void findFunctionWithRankCI(U8 rank)
{
    mpz_t f;
    mpz_init2(f, glo_length);
    mpz_set_str(f, "1", 16);

    U8 currentRank = 0;
    U64 maxSize = 1ULL << glo_length;

    // U64 start = maxSize - (maxSize >> 6);
    loop(i, 1, 3)
    {
        printf("i = %u\n", i);
        mpz_set_ui(f, i);
        gmp_printf("f: %Zx\n", f);
        fastFourierTransform(f);
        gmp_printf("f: %Zx\n", f);
    }
    // loop(i, 1, 3)
    // {
    //     mpz_set_ui(f, i);
    //     // fastFourierTransform(f);
    //     currentRank = countRank(f);
    //     // printf("currentRank = %llu\n", currentRank);
    //     if (currentRank >= rank)
    //     {
    //         gmp_printf("f: %Zx\n", f);
    //         printf("currentRank = %u\n", currentRank);
    //         // break;
    //     }
    // }
    mpz_clear(f);
}

int main()
{
    initArrayMpz();
    createArraySupport();
    printf("array support\n");
    loop(i, 0, glo_n + 1)
        gmp_printf("arrsp: %Zx\n", mpzArrSupport[i]);
    printf("\n");
    // printf("start3\n");

    findFunctionWithRankCI(2);
    clearArrayMpz();
    return 0;
}
