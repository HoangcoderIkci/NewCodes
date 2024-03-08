#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#define U64 uint64_t
#define U32 uint32_t
#define U16 uint16_t
#define U8 uint8_t
#define loop(i, a, n) for (U32 i = a; i < n; i++)
#define loopBack(i, n, a) for (int i = n; i >= a; i--)
#define getBitIndex(x, idx) (((x) >> (idx)) & 1)     // get bit tại index
#define setBitIndex(x, idx) ((x) |= (1 << (idx)))    // set bit tại index = 1
#define clearBitIndex(x, idx) ((x) &= ~(1 << (idx))) // clear bit tại index = 0
#define getHighBit(x) ((x >> (size - 1)) & 0b1)
#define registerBit(x) ((x << 1 | x >> (size - 1)) & gioihan)

U64 size = 4;

U64 multiplyTwoElemInRing(U64 a, U64 b, U64 module)
{
    U64 result = 0, temp, turn = 0;
    while (b)
    {
        temp = 0;
        if (b & 0b1)
        {
            temp = a;
            loop(idx1, 0, turn)
            {
                temp <<= 1;
                if (temp >= module)
                    temp -= module;
            }
        }
        result += temp;
        if (result >= module)
            result -= module;
        ++turn;
        b >>= 1;
    }
    return result;
}

void process1(U64 F)
{
    U64 len_bit, temp_bit, num_turn, t;
    U64 len_func = (1 << size);
    t = F;
    loop(idx1, 0, len_func)
    {
        if (t & 0b1)
        {
            printf("1 ");
        }
        else
        {
            printf("0 ");
        }
        t >>= 1;
    }
    printf("\n");
    loop(idx1, 0, size)
    {
        len_bit = (1 << idx1);
        num_turn = len_func / len_bit;
        num_turn >>= 1;
        loop(idx2, 0, num_turn)
        {
            loop(idx3, 0, len_bit)
            {
                temp_bit = getBitIndex(F, (idx2 * len_bit * 2 + idx3));
                if (temp_bit)
                    F ^= (1 << (idx2 * len_bit * 2 + len_bit + idx3));
            }
        }
        t = F;
        // loop(idx1, 0, len_func)
        // {
        //     if (F & 0b1)
        //         printf("1 ");
        //     else
        //         printf("0 ");
        //     F >>= 1;
        // }
        // printf("\n");
        F = t;
    }
    // printf("F = %d\n", F);
    U64 degree = 0;
    U64 turn = 0, temp, temp_degree;
    loop(idx1, 0, len_func)
    {
        if (F & 0b1)
        {
            printf("1 ");
            temp = turn;
            temp_degree = 0;
            while (temp)
            {
                if (temp & 0b1)
                    ++temp_degree;
                temp >>= 1;
            }
            if (temp_degree > degree)
                degree = temp_degree;
        }
        else
        {
            printf("0 ");
        }
        F >>= 1;
        turn++;
    }

    printf("\n");
    printf("degree of polynomial = %d\n", degree);
    // buoc 2 tim bac da thuc
}

U8 createTable()
{
    U64 module = (1llu) << size;
    U64 res;
    U64 flag = 1;
    U64 F;
    loop(c, 0, module)
    {
        // printf(" c = %d   : ,", c);
        F = 0;
        loop(set, 0, module)
        {
            // res = (set * c) % module;
            res = multiplyTwoElemInRing(set, c, module);
            flag = getHighBit(res);
            loop(idx1, 0, set)
            {
                flag <<= 1;
                if (flag >= module)
                    flag %= module;
            }
            // F <<= 1;
            F |= flag;
            // printf("In i = %d, res = %d \n", set, getHighBit(res));
            // printf(" %d,", getHighBit(res));
        }
        printf("F = %016llx\n", F);
        process1(F);
        // printf("================================================================================\n");
    }
    return flag;
}

int main()
{
    createTable();
    return 0;
}