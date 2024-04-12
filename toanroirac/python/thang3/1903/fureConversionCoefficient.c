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
#define loop(i, a, b) for (U32 i = a; i < b; i++)
#define glo_n 24
// const U32 glo_length = 1 << glo_n;
#define glo_length 16777216ULL // 16 65536ULL // 20 - 1048576 // 24 16777216ULL//28 268435456ULL // 30 1073741824  //32 4294967296
void fastFindCoefficientsZhegalkin(U8 *lst_coefficients)
{
    U32 half_len = 1;
    U32 full_len = 2;
    U32 num_turns = glo_length >> 1;
    U8 *ptr1;
    U8 *ptr2;
    loop(idx1, 0, glo_n)
    {
        loop(idx2, 0, num_turns)
        {
            ptr1 = lst_coefficients + idx2 * full_len;
            ptr2 = ptr1 + half_len;
            loop(idx3, 0, half_len)
                ptr2[idx3] ^= ptr1[idx3];
        }
        half_len <<= 1;
        full_len <<= 1;
        num_turns >>= 1;
    }
}
void fastFindCoefficientsReal(I8 *lst_coefficients)
{
    U32 half_len = 1;
    U32 full_len = 2;
    U32 num_turns = glo_length >> 1;
    I8 *ptr1;
    I8 *ptr2;
    loop(idx1, 0, glo_n)
    {
        loop(idx2, 0, num_turns)
        {
            ptr1 = lst_coefficients + idx2 * full_len;
            ptr2 = ptr1 + half_len;
            loop(idx3, 0, half_len)
                ptr2[idx3] -= ptr1[idx3];
        }
        half_len <<= 1;
        full_len <<= 1;
        num_turns >>= 1;
    }
}
void fastFindCoefficientsFourier(I8 *lst_coefficients)
{
    U32 half_len = 1;
    U32 full_len = 2;
    U32 num_turns = glo_length >> 1;
    I8 *ptr1;
    I8 *ptr2;
    loop(idx1, 0, glo_n)
    {
        loop(idx2, 0, num_turns)
        {
            ptr1 = lst_coefficients + idx2 * full_len;
            ptr2 = ptr1 + half_len;
            loop(idx3, 0, half_len)
            {
                ptr1[idx3] += ptr2[idx3];
                ptr2[idx3] = ptr1[idx3] - (ptr2[idx3] << 1);
            }
        }
        half_len <<= 1;
        full_len <<= 1;
        num_turns >>= 1;
    }
}

I8 countBitFast(I64 a)
{
    I8 count = 0;
    while (a)
    {
        ++count;
        a &= (a - 1); // Loại bỏ bit 1 ngoài cùng bên phải
    }
    return count;
}

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

U32 f = 0;
// U8 *global_table = (U8 *)calloc(glo_length, sizeof(U8));
// Gán giá trị 1 cho tất cả các phần tử trong mảng bằng hàm memset
I8 *global_table;
void create_dynamic_array()
{
    global_table = (I8 *)malloc(glo_length * sizeof(I8)); // Cấp phát bộ nhớ cho mảng
    memset(global_table, 1, glo_length * sizeof(I8));
}
void recursive(U32 t1, U16 num_loop)
{
    if (num_loop)
    {
        U32 t2 = 1 << num_loop;
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
        U32 t2 = 1;
        while (t2 < t1)
        {
            f ^= t2;
            // printf("%u,", f);
            global_table[f] = 0;
            f ^= t2;
            t2 <<= 1;
        }
    }
}
void calcF1SpAuto()
{
    global_table[0] = 0;
    f = 0;
    loop(t, 0, (glo_n >> 1) - 1)
    {
        recursive(glo_length, t);
        // printf("t = %u ; c = %u\n", t, c);
    }
}
void calcF1supper()
{
    // global_table[0] = 0;
    U32 half_len = glo_n >> 1;
    loop(a, 0, glo_length)
    {
        if (countBitFast(a) >= half_len)
            global_table[a] = 1;
        // else
        //     global_table[a] = 0;
    }
}
int main()
{
    I8 *table = (I8 *)malloc(sizeof(I8) * glo_length);
    // int8_t arrTable[] = {0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1};
    //   Code mà bạn muốn đo thời gian ở đây
    clock_t start, end;
    double cpu_time_used;
    // giai đoạn 1 :
    create_dynamic_array();
    start = clock();
    calcF1SpAuto();
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Thời gian thực thi giai đoạn 1: %f giây\n", cpu_time_used);
    printf("\n");

    // U8 *table = calcF1Supper();
    //  printArray(table);

    // giai đoạn 2
    start = clock();
    fastFindCoefficientsFourier(global_table);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Thời gian thực thi giai đoạn 2: %f giây\n", cpu_time_used);
    printf("\n");

    // printArray(arrTable);

    free(global_table);
    free(table);
    return 0;
}