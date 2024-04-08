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
#define loop(i, a, b) for (I64 i = a; i < b; i++)
#define glo_n 30
// const U32 glo_length = 1 << glo_n;
#define glo_length 1073741824ULL // 16 65536ULL // 20 - 1048576ULL // 24 16777216ULL//28 268435456ULL // 30 1073741824ULL  //32 4294967296ULL //34 17179869184ULL

void fastFindCoefficientsZhegalkin(U8 *lst_coefficients)
{
    U64 half_len;
    U64 full_len;
    U64 num_turns;
    U8 *ptr1;
    U8 *ptr2;
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
                ptr2[idx3] ^= ptr1[idx3];
            }
        }
    }
}

void fastFindCoefficientsReal(I8 *lst_coefficients)
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
                ptr2[idx3] -= ptr1[idx3];
            }
        }
    }
}

void fastFindCoefficientsFourier(I8 *lst_coefficients)
{
    U32 half_len;
    U32 full_len;
    U32 num_turns;
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
                ptr2[idx3] = ptr1[idx3] - 2 * ptr2[idx3];
            }
        }
    }
}
// U8 vesFunction(U64 f)
// {
//     U8 count = 0;
//     while (f)
//     {
//         count += f & 0b1;
//         f >>= 1;
//     }
//     return count;
// }
// U8 *calcF1()
// {
//     U8 *table = (U8 *)malloc(sizeof(U8) * glo_length);
//     U8 vec = 0;
//     U8 hafl_length = glo_n >> 1;
//     loop(i, 0, glo_length)
//     {
//         vec = vesFunction(i);
//         table[i] = (vec >= hafl_length);
//     }
//     return table;
// }

I8 *calcF2()
{
    I8 *table = (I8 *)malloc(sizeof(I8) * glo_length);
    table[0] = 1;
    table[1] = 0;
    U64 current_leng = 2;
    I8 *part2_table;
    while (current_leng < glo_length)
    {
        memcpy(table + current_leng, table, current_leng * sizeof(I8));
        part2_table = table + current_leng;
        loop(i, 0, current_leng)
            part2_table[i] ^= 1;
        // part2_table[i] = table[i] ^ 1;
        current_leng <<= 1;
    }
    return table;
}

// U16 c = 0;
I64 f = 0;
// U8 *global_table = (U8 *)calloc(glo_length, sizeof(U8));
// Gán giá trị 1 cho tất cả các phần tử trong mảng bằng hàm memset
I8 *global_table;
void create_dynamic_array()
{
    global_table = (I8 *)malloc(glo_length * sizeof(I8)); // Cấp phát bộ nhớ cho mảng
    memset(global_table, 1, glo_length * sizeof(I8));
}
void recursive(I64 t1, I16 num_loop)
{
    if (num_loop)
    {
        I64 t2 = 1 << num_loop;
        while (t2 < t1)
        {
            f ^= t2;
            recursive(t2, num_loop - 1);
            f ^= t2;
            t2 <<= 1;
        }
    }
    else
    {
        I64 t2 = 1;
        while (t2 < t1)
        {
            f ^= t2;
            global_table[f] = 0;
            f ^= t2;
            t2 <<= 1;
        }
    }
}

void calcF1SpAuto()
{
    global_table[0] = 0;
    loop(t, 0, (glo_n >> 1) - 1)
    {
        recursive(glo_length, t);
    }
}
// void checkF1()
// {
//     U8 *table1 = calcF1();
//     calcF1SpAuto();
//     // U8 *table2 = calcF1Supper();
//     loop(i, 0, glo_length) if (table1[i] != global_table[i])
//     {
//         printf("failed %u %u %u\n", i, table1[i], global_table[i]);
//     }
//     free(table1);
//     // free(table2);
// }
U8 *copyArray(U8 *arr, U32 size)
{
    U8 *arrCp = (U8 *)malloc(sizeof(U8) * size);
    loop(i, 0, size)
        arrCp[i] = arr[i];
    ////
    return arrCp;
}
void printArray(int8_t *arr)
{
    loop(i, 0, glo_length)
        printf("%d,", arr[i]);
    printf("\n");
}
// void printArray(U8 *arr)
// {
//     loop(i, 0, glo_length)
//         printf("%d,", arr[i]);
//     printf("\n");
// }
int main()
{
    // int8_t *table = (U8 *)malloc(sizeof(int8_t) * glo_length);
    // int8_t arrTable[] = {0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1};
    //   Code mà bạn muốn đo thời gian ở đây
    clock_t start, end;
    double cpu_time_used;

    // giai đoạn 1 :
    start = clock();
    create_dynamic_array();
    calcF1SpAuto();
    // calcF2();
    //  U8 *table = calcF1Supper();
    //   printArray(table);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Thời gian thực thi giai đoạn 1: %f giây\n", cpu_time_used);
    printf("\n");

    // giai đoạn 2
    start = clock();
    fastFindCoefficientsReal(global_table);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Thời gian thực thi giai đoạn 2: %f giây\n", cpu_time_used);
    printf("\n");
    // printArray(arrTable);
    free(global_table);
    return 0;
}