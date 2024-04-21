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
#define glo_n 8
// const U32 glo_length = 1 << glo_n;
#define glo_length 256 // 16 65536ULL // 20 - 1048576 // 24 16777216ULL//28 268435456ULL // 30 1073741824  //32 4294967296
U8 arrA[] = {0, 1, 1, 1};
U16 arrResult[glo_length];
U64 glo_index = 1;
// U64 arrSupport[glo_n + 1]; //{0, 0xf, 0x33, 0x55};
U64 arrSupport[glo_n + 1] = {0, 0xf};

U8 *calcF2()
{
    U8 *table = (U8 *)malloc(sizeof(U8) * glo_length);
    table[0] = 1;
    table[1] = 0;
    U32 current_leng = 2;
    U8 *ptr;
    while (current_leng < glo_length)
    {
        ptr = table + current_leng;
        memcpy(ptr, table, current_leng);
        loop(i, 0, current_leng)
            ptr[i] ^= 1;
        current_leng <<= 1;
    }
    return table;
}
U64 calcF2Supper()
{
    U64 f = 0x1;
    U32 current_leng = 2;
    while (current_leng < glo_length)
    {
        f ^= ((~f) & (((1ULL) << current_leng) - 1)) << current_leng;
        current_leng <<= 1;
    }
    printf("f = %llu\n", f);
    return f;
}
void printfBinary(U64 f)
{
    loop(i, 0, glo_length)
    {
        printf("%u", f & 0b1);
        f >>= 1;
    }
}
U64 calcZhegalkin3bit(U64 f)
{
    f ^= ((f & 0x55) << 1) & 0xff; //
    f ^= ((f & 0x33) << 2) & 0xff; //
    f ^= (f & 0xf) << 4;           //
    printf("f = %llu\n", f);
    printfBinary(f);
    return f;
}
// U64 calcZhegalkin8bit(U64 f)
// {
//     f
//     f ^= (f & 0xffffffff) << 32;       //
//     f ^= (f & 0xffff0000ffff) << 16;   //
//     f ^= (f & 0xff00ff00ff00ff) << 8;  //
//     f ^= (f & 0xf0f0f0f0f0f0f0f) << 4; //
//     f ^= (f & 0xf0f0f0f0f0f0f0f) << 2; //
//     // f ^= ((f & 0x33) << 2) & 0xff;     //
//     // f ^= ((f & 0x55) << 1) & 0xff;     //
//     printf("f = %llu\n", f);
//     printfBinary(f);
//     return f;
// }
void createArraySupport()
{
    U64 doubleLenBlock = glo_length >> 1;
    U64 limitBlock = ((1ULL) << (glo_length >> 2)) - 1;
    U64 limitCurrentBlock = limitBlock;
    U64 numTurn = 2;
    U64 sp = 0;
    loop(k, 2, glo_n + 1)
    {
        sp = 0;
        loop(id, 0, numTurn)
        {
            sp ^= limitBlock;
            limitBlock <<= doubleLenBlock;
        }
        arrSupport[k] = sp;
        doubleLenBlock >>= 1;
        limitCurrentBlock >>= (doubleLenBlock >> 1);
        limitBlock = limitCurrentBlock;
        numTurn <<= 1;
    }
    // return;
}
U16 countBit(U64 n)
{
    U16 count = 0;
    while (n)
    {
        n &= (n - 1);
        ++count;
        /* code */
    }
    return count;
}
void recurse(U8 start, U8 k, U8 count, U64 f)
{
    if (count < k)
    {
        U64 f_temp;
        loop(i, start, glo_n + 1)
        {
            if (arrA[i])
                f_temp = f & (~arrSupport[i]);
            else
                f_temp = f & arrSupport[i];
            // count += 1;
            if (count + 1 == k)
            {
                arrResult[glo_index++] = countBit(f_temp);
            }
            else
                recurse(i + 1, k, count + 1, f_temp);
        }
    }
}
void mainProcess(U64 f)
{
    U8 count;
    arrResult[0] = countBit(f);
    loop(k, 1, glo_n + 1)
    {
        count = 0;
        recurse(1, k, count, f);
    }
}

int main()
{
    // mpz_t num1, num2, result;
    // mpz_inits(num1, num2, result, NULL);

    // mpz_set_ui(num1, 0b1010); // Đặt giá trị cho num1 là 1010 (10 ở hệ thập phân)
    // mpz_set_ui(num2, 0b1100); // Đặt giá trị cho num2 là 1100 (12 ở hệ thập phân)

    // // Phép XOR
    // mpz_xor(result, num1, num2);
    // gmp_printf("XOR result: %Zd\n", result);

    // // Dịch trái 1 bit
    // mpz_mul_2exp(result, num1, 1);
    // gmp_printf("Left shift result: %Zd\n", result);

    // mpz_clears(num1, num2, result, NULL);
    U64 f = calcF2Supper();
    FILE *file = fopen("output.txt", "a");
    if (file == NULL)
    {
        printf("can't open file.");
        return 1;
    }
    // U64 zheg = calcZhegalkin3bit(f);
    createArraySupport();
    mainProcess(f);
    loop(i, 0, glo_length)
        fprintf(file, "%u,", arrResult[i]);
    fprintf(file, "\n");
    fclose(file);
    return 0;
}