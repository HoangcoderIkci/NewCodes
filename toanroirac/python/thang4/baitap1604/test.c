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
#define limit 0xf
U8 arrA[] = {0, 0, 0, 1};
U16 arrResult[8];
U64 glo_index = 1;
U64 arrSupport[] = {0, 0xf, 0x33, 0x55};
U64 arrIndex[] = {1, 3, 3, 1};
#define glo_length 8 // 16 65536ULL // 20 - 1048576 // 24 16777216ULL//28 268435456ULL // 30 1073741824  //32 4294967296
void printTable(I8 count)
{
    loop(i, 0, count)
        printf("%i,", arrResult[i]);
    printf("\n");
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
void recurse(I8 start, I8 end, I8 count, U64 f, U8 lenBlock, U64 index)
{
    while (start < end)
    {
        U64 f_temp = f;
        if (f)
        {
            U64 temp = arrSupport[start];
            if (arrA[start])
                f_temp &= ~temp;
            else
                f_temp &= temp;
        }
        arrResult[index] = countBit(f_temp);
        printf("index = %u , ", index);
        printf("%u\n", f_temp);
        lenBlock >>= 1;
        // index += arrIndex[count];
        //  xử lý f
        //  tìm t
        //  printTable(count + 1);
        recurse(++start, end, count + 1, f_temp, lenBlock, index + arrIndex[count]);
        // glo_index -= ;
        index++;
    }
}

int main()
{
    U64 f = 0xe8;
    arrResult[0] = countBit(f);
    recurse(1, 4, 1, f, 8, 1);
    loop(i, 0, 8)
        printf("%u,", arrResult[i]);
    printf("\n");
    return 0;
}