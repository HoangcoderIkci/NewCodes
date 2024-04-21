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
U8 arrA[] = {0, 0, 0, 0, 1};
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

void calcF2(mpz_t result)
{
    mpz_t f, temp2, mask, edi;
    mpz_init2(f, 256);
    mpz_init2(temp2, 256);
    mpz_init2(mask, 256); // Khởi tạo biến mask
    mpz_init2(edi, 256);  // Khởi tạo biến mask

    mpz_set_str(f, "1", 16);
    mpz_set_str(edi, "1", 16);
    U32 current_leng = 2;
    while (current_leng < glo_length)
    {
        mpz_com(temp2, f);
        mpz_mul_2exp(mask, edi, current_leng); // Tạo mask với giá trị (1 << current_leng)
        mpz_sub_ui(mask, mask, 1);             // Giảm mask đi 1 để tạo giá trị ((1 << current_leng) - 1)
        gmp_printf("mask: %Zd\n", mask);
        mpz_and(temp2, temp2, mask); // Thực hiện phép AND với mask
        mpz_mul_2exp(temp2, temp2, current_leng);
        mpz_xor(f, f, temp2);
        gmp_printf("f: %Zd\n", f);
        current_leng <<= 1;
    }
    mpz_set(result, f); // Gán kết quả vào biến result

    mpz_clears(f, temp2, mask, NULL);
}

void recurse2(U8 start, U8 k, U8 count, mpz_t f)
{

    if (count < k)
    {
        mpz_t f_temp, temp1;
        mpz_init2(f_temp, 256);
        mpz_init2(temp1, 256);
        // printf("start2\n");
        loop(i, start, glo_n + 1)
        {
            if (arrA[i])
            {
                mpz_com(temp1, mpzArrSupport[i]);
                // mpz_set_ui(temp1, temp2);
                //  f_temp = f & (~arrSupport[i]);
                mpz_and(f_temp, f, temp1);
            }
            else
            {
                // mpz_set(temp1, );
                //  f_temp = f & arrSupport[i];
                mpz_and(f_temp, f, mpzArrSupport[i]);
            }
            // count += 1;
            // printf("start2\n");
            if (count + 1 == k)
            {
                // arrResult[glo_index++] = countBit(f_temp);
                arrResult[glo_index++] = mpz_popcount(f_temp);
            }
            else
                recurse2(i + 1, k, count + 1, f_temp);
        }
        mpz_clears(f_temp, temp1, NULL);
        // printf("start2\n");
    }
}
void mainProcess(mpz_t f)
{
    U8 count;
    arrResult[0] = mpz_popcount(f);

    loop(k, 1, glo_n + 1)
    {
        count = 0;
        recurse2(1, k, count, f);
    }
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
int main()
{
    mpz_t f;
    mpz_init(f);
    initArrayMpz(); // sử dụng F2 - affine function 1 + x1 + x2 + ... + xn
    calcF2(f);      // Sử dụng biến f để nhận kết quả
    gmp_printf("Result: %Zd\n", f);
    createArraySupport();
    loop(i, 0, glo_n + 1)
        gmp_printf("arrsp: %Zd\n", mpzArrSupport[i]);
    printf("\n");
    // printf("start3\n");
    mainProcess(f);
    loop(i, 0, glo_length)
        printf("%u,", arrResult[i]);
    printf("\n");
    mpz_clear(f);
    clearArrayMpz();
    return 0;
}
