#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <iostream>
#define U32 uint64_t
#define U16 uint_fast16_t
#define U8 uint_fast8_t
#define loop(i, a, n) for (U32 i = a; i < n; i++)
#define loopBack(i, n, a) for (int i = n; i >= a; i--)
#define getBitIndex(x, idx) (((x) >> (idx)) & 1)     // get bit tại index
#define setBitIndex(x, idx) ((x) |= (1 << (idx)))    // set bit tại index = 1
#define clearBitIndex(x, idx) ((x) &= ~(1 << (idx))) // clear bit tại index = 0
#define size 5
U32 gioihan = 0b11111;
#define registerBit(x) ((x << 1 | x >> (size - 1)) & gioihan)

using namespace std;
void process()
{
    U32 so_luong_bien = (1llu) << size;
    bool static_variables[so_luong_bien];
    loop(i, 0, so_luong_bien)
    {
        static_variables[i] = true;
    }
    U32 res = 0;
    loop(i, 0, size)
    {
        res = 0;
        loop(t, 0, so_luong_bien)
        {
            if (static_variables[t])
            {
                static_variables[t] = false;
                U32 elem = t;
                do
                {
                    loop(k, 0, i)
                        elem = registerBit(elem);
                    static_variables[elem] = false;
                } while (elem != t);
                res++;
            }
        }
        loop(j, 0, so_luong_bien)
        {
            static_variables[j] = true;
        }
        // phục hồi lại bảng trên
        printf("tại i = %d ; số orbit tại dịch i bit = %d\n", i, res);
    }
    // printf("res = %d\n", res);
}

int main()
{
    process();
    return 0;
}