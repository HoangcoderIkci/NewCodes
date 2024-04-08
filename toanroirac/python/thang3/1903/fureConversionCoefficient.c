#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define U64 uint64_t
#define U32 uint32_t
#define U16 uint16_t
#define U8 uint8_t
#define loop(i, a, b) for (U32 i = a; i < b; i++)
#define glo_n 24
// const U32 glo_length = 1 << glo_n;
#define glo_length 16777216ULL // 16 65536ULL // 20 - 1048576 // 24 16777216ULL//28 268435456ULL // 30 1073741824  //32 4294967296
void supportZhegalkin(U8 *lst_coefficients, U8 idx1)
{
    if (idx1 == glo_n)
    {
        return;
    }
    U32 half_len = 1 << idx1;
    U32 full_len = half_len << 1;
    U32 num_turns = glo_length / full_len;
    loop(idx2, 0, num_turns)
    {
        loop(idx3, 0, half_len)
            lst_coefficients[idx2 * full_len + half_len + idx3] ^= lst_coefficients[idx2 * full_len + idx3];
    }
    // loop(i, 0, glo_length)
    //     printf("%d ", lst_coefficients[i]);
    // printf("\n");
    supportZhegalkin(lst_coefficients, idx1 + 1);
}

void fastFindCoefficientsZhegalkin(U8 *lst_coefficients)
{
    U32 half_len;
    U32 full_len;
    U32 num_turns;
    loop(idx1, 0, glo_n)
    {
        half_len = 1 << idx1;
        full_len = half_len << 1;
        num_turns = glo_length / full_len;
        loop(idx2, 0, num_turns)
        {
            loop(idx3, 0, half_len)
                lst_coefficients[idx2 * full_len + half_len + idx3] ^= lst_coefficients[idx2 * full_len + idx3];
        }
    }
}

void fastFindCoefficientsReal(int8_t *lst_coefficients)
{
    U32 half_len;
    U32 full_len;
    U32 num_turns;
    loop(idx1, 0, glo_n)
    {
        half_len = 1 << idx1;
        full_len = half_len << 1;
        num_turns = glo_length / full_len;
        loop(idx2, 0, num_turns)
        {
            loop(idx3, 0, half_len)
                lst_coefficients[idx2 * full_len + half_len + idx3] -= lst_coefficients[idx2 * full_len + idx3];
        }
    }
}

void fastFindCoefficientsFourier(int8_t *lst_coefficients)
{
    U32 half_len;
    U32 full_len;
    U32 num_turns;
    loop(idx1, 0, glo_n)
    {
        half_len = 1 << idx1;
        full_len = half_len << 1;
        num_turns = glo_length / full_len;
        loop(idx2, 0, num_turns)
        {
            loop(idx3, 0, half_len)
            {
                lst_coefficients[idx2 * full_len + idx3] += lst_coefficients[idx2 * full_len + idx3 + half_len];
                lst_coefficients[idx2 * full_len + half_len + idx3] = lst_coefficients[idx2 * full_len + idx3] - 2 * lst_coefficients[idx2 * full_len + half_len + idx3];
            }
        }
    }
}
U8 vesFunction(U32 f)
{
    U8 count = 0;
    while (f)
    {
        count += f & 0b1;
        f >>= 1;
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
U8 *global_table;
void create_dynamic_array()
{
    global_table = (U8 *)malloc(glo_length * sizeof(U8)); // Cấp phát bộ nhớ cho mảng
    memset(global_table, 1, glo_length * sizeof(U8));
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
    loop(t, 0, (glo_n >> 1) - 1)
    {
        recursive(glo_length, t);
        // printf("t = %u ; c = %u\n", t, c);
    }
}

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
    // U8 *table = calcF1Supper();
    //  printArray(table);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Thời gian thực thi giai đoạn 1: %f giây\n", cpu_time_used);
    printf("\n");

    // giai đoạn 2
    start = clock();
    fastFindCoefficientsZhegalkin(global_table);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Thời gian thực thi giai đoạn 2: %f giây\n", cpu_time_used);
    printf("\n");
    // printArray(arrTable);
    free(global_table);
    return 0;
}