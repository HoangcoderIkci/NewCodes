#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define U64 uint64_t
#define U32 uint32_t
#define U16 uint16_t
#define U8 uint8_t
#define SIZEPOLE 65536
#define CHAR 2
#define DEGREE 16
// 3 5 9 11 13 15 17 19
uint32_t alpha = 13;
uint32_t beta = 15;
uint32_t gamma = 9;
uint32_t teta = 11;

// const uint32_t hsPole = 7; // x^2+x+1
const uint32_t hsPole = 0x1100b; // x8 + x4 + x3 + x + 1
const uint32_t limit = 0xFFFF;

// a*b
uint32_t gmul2(uint32_t a, uint32_t b)
{
    uint32_t temp = 0;
    while (a != 0 && b != 0)
    {
        if (b & 0x1)
            temp ^= a;
        if (a & 0x8000)
            a = (a << 1) ^ hsPole; // x^32+x^22+x^2+x+1
        else
            a <<= 1;
        b >>= 1;
    }
    return temp;
}

U32 gmul(uint32_t a, uint32_t b)
{
    U32 _a = a;
    U32 b_ = b;
    U32 c = 0;

    while (b_ != 0)
    {
        if (b_ & 0x1)
        {
            c ^= _a; // Sử dụng ^= để thực hiện phép XOR và gán kết quả cho c
        }
        _a <<= 1; // Dịch trái _a một bit
        b_ >>= 1; // Dịch phải b_ một bit

        if (_a & 0x10000)
        {
            _a ^= hsPole; // Nếu bit cao nhất của _a được set, thực hiện XOR với hsPole
        }
    }
    return c;
}

int main()
{
    U32 t1, t2;
    for (U64 i = 1; i < (1ULL << 22); i += (1 << 10))
    {
        for (U64 j = 1; j < (1ULL << 25); j += (1 << 10))
        {
            t1 = gmul(i, j);
            t2 = gmul2(i, j);
            if (t1 != t2)
                printf("t1 = %d, t2 = %u\n", t1, t2);
        }
    }
    return 0;
}