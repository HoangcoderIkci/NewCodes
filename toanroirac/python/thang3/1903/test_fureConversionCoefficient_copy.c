#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define U64 uint64_t
#define U32 uint32_t
#define U16 uint16_t
#define U8 uint8_t
#define loop(i, a, b) for (U64 i = a; i < b; i++)
#define glo_n 30
// const U32 glo_length = 1 << glo_n;
#define glo_length 1073741824ULL // 20 - 1048576 // 30 1073741824ULL  //32 4294967296
U8 *calcF2()
{
    U8 *table = (U8 *)malloc(sizeof(U8) * glo_length);
    table[0] = 1;
    table[1] = 0;
    U64 current_leng = 2;
    U8 *part2_table;
    while (current_leng < glo_length)
    {
        memcpy(table + current_leng, table, current_leng * sizeof(U8));
        part2_table = table + current_leng;
        loop(i, 0, current_leng)
            part2_table[i] ^= 1;
        current_leng <<= 1;
    }
    return table;
}
int main()
{
    U8 *expected_table = (U8 *)malloc(sizeof(U8) * 8);
    expected_table[0] = 1;
    expected_table[1] = 0;
    expected_table[2] = 0;
    expected_table[3] = 1;
    expected_table[4] = 0;
    expected_table[5] = 1;
    expected_table[6] = 1;
    expected_table[7] = 0;

    U8 *actual_table = calcF2();

    for (int i = 0; i < 8; i++)
    {
        if (actual_table[i] != expected_table[i])
        {
            printf("Test failed: calcF2() - Mismatch at index %d\n", i);
            printf("Expected: %d, Actual: %d\n", expected_table[i], actual_table[i]);
            return -1;
        }
    }

    printf("All tests passed: calcF2()\n");

    free(expected_table);
    free(actual_table);
    return 0;
}