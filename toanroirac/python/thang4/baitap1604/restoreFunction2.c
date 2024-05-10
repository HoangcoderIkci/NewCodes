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

U8 **table;
U8 *supportIndexesRow;
// U8 supportIndexesRow[] = {0, 4, 2, 1, 0b110, 0b101, 0b011, 7};
U32 supportCreateIndexTablesupportIndexesRow(U32 x)
{
    U32 smallest, ripple, ones; // x = xxx0 1111 0000
    smallest = x & -x;          // 0000 0001 0000
    return (x ^ smallest) | (smallest >> 1);
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
void createIndexTablesupportIndexesRow()
{
    U32 f = 1;
    supportIndexesRow = (U8 *)malloc(glo_length * sizeof(U8));
    U8 *arrSupport = (U8 *)malloc(glo_length * sizeof(U8));
    supportIndexesRow[0] = 0;
    U8 count = 1;
    U8 count2 = 0;
    U32 bound = 0;
    loop(round, 1, glo_n + 1)
    {
        f = (1 << round) - 1;
        do
        {
            arrSupport[count2++] = f;
            f = snoob(f);
        } while (f < glo_length);
        while (count2)
        {
            supportIndexesRow[count++] = arrSupport[--count2];
        }
    }
    // loop(round, 0, glo_length)
    // {
    //     printf("%x,", supportIndexesRow[round]);
    // }
    // printf("\n");
    free(arrSupport);
}
int countBitFast(U8 n)
{
    int count = 0;
    while (n)
    {
        ++count;
        n &= (n - 1);
    }
    return count;
}
// In kết quả với mode = 0 theo default là in ra fullTable, with mode 1 is only truthTable
void printTable(U8 mode = 0)
{
    if (mode)
    {
        printf("truth table : \n");
        U32 idR = glo_length - 1;
        loop(j, 0, glo_length)
        {
            printf("%x,", table[idR][j]);
        }
        printf("\n");
    }
    else
        loop(i, 0, glo_length)
        {
            loop(j, 0, glo_length)
            {
                printf("%x,", table[supportIndexesRow[i]][j]);
            }
            printf("\n");
        }
}
void initTable()
{                                                                           //[0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1]
    U8 supportIndexes[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // phần khởi tạo
    U8 supportValues[] = {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // phần khởi tạo
    // U8 supportIndexesRow[] = {0, 4, 2, 1, 0b110, 0b101, 0b011, 7};
    //  Cap phat dong cho mang 2 chieu 8x8
    table = (U8 **)malloc(glo_length * sizeof(U8 *));
    U8 idSupportRow;
    for (int i = 0; i < glo_length; i++)
    {
        idSupportRow = supportIndexesRow[i];
        table[idSupportRow] = (U8 *)malloc(glo_length * sizeof(U8));
        memset(table[idSupportRow], 2, glo_length * sizeof(U8));
        table[idSupportRow][supportIndexes[i]] = supportValues[i];
    }
    // printTable();
}

void mainProcess()
{
    U8 *used = (U8 *)calloc(glo_length, sizeof(U8));
    U8 numValued = 0;
    U8 currentCol = 0;
    U8 neighborCol = 0;
    U8 indexRowSum = 0;
    // xử lý hàng 0
    loop(idx1, 0, glo_length)
    {
        if (table[idx1][idx1] != 2)
        {
            memset(table[0], table[0][idx1], glo_length * sizeof(U8));
        }
    }
    loop(currentRow, 1, glo_length)
    {
        numValued = 1;
        memset(used, 0, glo_length * sizeof(U8));
        currentCol = 0;
        // tìm cột đã có giá trị
        loop(idx1, 0, glo_length)
        {
            if (table[currentRow][idx1] != 2)
            {
                currentCol = idx1;
                used[currentCol] = 1;
                break;
            }
        }
        // sử lý
        do
        {
            // b1 tìm những cột fix giống col hiện tại
            neighborCol = currentCol;
            loop(numCol, 0, glo_length)
            {
                if (numCol != currentCol && ((numCol ^ currentCol) & currentRow) == 0)
                {
                    // th thỏa mãn
                    table[currentRow][numCol] = table[currentRow][currentCol];
                    used[numCol] = 1;
                    ++numValued;
                }
            }
            if (numValued == glo_length)
                break;
            // b2 tìm neighbor
            loop(numCol, 0, glo_length)
            {
                if (countBitFast((numCol ^ currentCol) & currentRow) == 1 && used[numCol] == 0)
                {
                    // th thỏa mãn
                    neighborCol = numCol;
                    // xử lý neighborCol (tìm giá trị cho nó)
                    // tìm hàng ở trên
                    indexRowSum = ((neighborCol ^ currentCol) & currentRow) ^ currentRow;
                    table[currentRow][neighborCol] = table[currentRow][currentCol] ^ table[indexRowSum][currentCol];
                    used[neighborCol] = 1;
                    ++numValued;
                    currentCol = neighborCol;
                    break;
                }
            }

        } while (numValued < glo_length);
    }
    free(used);
}

int main()
{
    createIndexTablesupportIndexesRow();
    initTable();
    mainProcess();
    printTable(1);
    free(table);
    free(supportIndexesRow);
    return 0;
}