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
#define glo_n 6
// const U32 glo_length = 1 << glo_n;
#define glo_length 64 // 16 16777216ULL
void fastFindCoefficientsZhegalkin(U8 *lst_coefficients)
{
    U32 half_len;
    U32 full_len;
    U32 num_turns;
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
                ptr2[idx3] ^= ptr1[idx3];
        }
    }
}

// U64 fastFindCoefficientsZhegalkinSupper(U64 lst_coefficients)
// {
//     U32 half_len;
//     U32 full_len;
//     U32 num_turns;
//     U64 temp;
//     U64 f;
//     loop(idx1, 0, glo_n)
//     {
//         half_len = 1 << idx1;
//         full_len = half_len << 1;
//         num_turns = glo_length / full_len;
//         f = 0;
//         temp = 1;
//         loop(idx2, 0, num_turns)
//         {
//             // ptr1 = lst_coefficients + idx2 * full_len;
//             // ptr2 = ptr1 + half_len;
//             loop(idx3, 0, half_len)
//             {
//                 f ^= temp;
//                 temp <<= 1;
//             }
//             temp <<= half_len;
//         }
//         lst_coefficients ^= (lst_coefficients & f) << half_len;
//         printf("f = %x\n", lst_coefficients);
//     }
//     return lst_coefficients;
// }

U64 fastFindCoefficientsZhegalkinSupper(U64 lst_coefficients)
{
    U32 half_len;
    U32 full_len;
    U32 num_turns;
    U64 f;
    for (U32 idx1 = 0; idx1 < glo_n; ++idx1)
    {
        half_len = 1U << idx1;
        full_len = half_len << 1;
        num_turns = glo_length / full_len;
        f = 0;
        for (U32 idx2 = 0; idx2 < num_turns; ++idx2)
        {
            // Với mỗi idx2, temp luôn bắt đầu là 1 và được dịch trái idx3 lần trong vòng lặp bên trong.
            // Nhưng vì temp luôn reset về 1 và không phụ thuộc vào idx2 hoặc idx3,
            // chúng ta có thể tính toán trực tiếp f mà không cần sử dụng temp.
            f ^= ((1ULL << half_len) - 1) << (idx2 * full_len);
        }
        lst_coefficients ^= (lst_coefficients & f) << half_len;
    }
    return lst_coefficients;
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

U8 *calcF2Version2()
{
    U8 *table = (U8 *)malloc(sizeof(U8) * glo_length);
    table[0] = 1;
    table[1] = 0;
    U32 current_leng = 2;
    while (current_leng < glo_length)
    {
        loop(i, 0, current_leng)
            table[i + current_leng] = table[i] ^ 1;
        current_leng <<= 1;
    }
    return table;
}

int main()
{
    clock_t start, end;
    double cpu_time_used;
    U8 f = 0;
    U8 *table = calcF2();
    for (int i = 0; i < glo_length; i++)
    {
        f ^= table[i] << i;
    }

    start = clock();
    fastFindCoefficientsZhegalkin(table);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Thời gian thực thi giai đoạn 1: %f giây\n", cpu_time_used);
    printf("\n");

    start = clock();
    // table = calcF2Version2();
    f = fastFindCoefficientsZhegalkinSupper(f);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Thời gian thực thi giai đoạn 1: %f giây\n", cpu_time_used);
    printf("\n");

    for (int i = 0; i < glo_length; i++)
    {
        if (f & 0b1 != table[i])
            printf("khong dung\n");
        f >>= 1;
    }
    free(table);

    // printf("f = %x\n", f);
    return 0;
}