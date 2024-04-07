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
#define _Pi1(x) gpow(x, gamma)
#define _Pi2(x) gpow(x, teta)
#define S(x) ((Y1(x) << 16) | Y2(x))

// 3 5 9 11 13 15 17 19
U32 alpha = 9;
U32 beta = 11;
U32 gamma = 13;
U32 teta = 11;
// Thời gian thực thi: 34.791000 giây giây
const U32 hsPole = 0x1100b; // x^16+x^12+x^3+x+1
// a*b
U32 gmul(uint32_t _a, uint32_t b_)
{
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
U32 gpow(U32 a, U32 x)
{
    U32 res = 1;
    while (x != 0)
    {
        if (x & 0b1)
        {
            res = gmul(res, a);
        }
        a = gmul(a, a);
        x >>= 1;
    }
    return res;
}

U32 Pi1(U32 x)
{
    return gpow(x, alpha);
}

U32 Pi2(U32 x)
{
    return gpow(x, beta);
}

U32 Y1(U32 x)
{
    U32 x1 = x >> 16;
    U32 x2 = x & 0xFFFF;
    if (x2)
        return gmul(x1, gpow(x2, alpha));
    return _Pi1(x1);
}

U32 Y2(U32 x)
{
    U32 x1 = x >> 16;
    U32 x2 = x & 0xFFFF;
    if (x1)
        return gmul(gpow(x1, beta), gpow(x2, alpha * beta + 1));
    return _Pi2(x2);
}

int main()
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    U64 MAX = (1ULL << 32);
    U32 sep = (1 << 9);
    U32 begin = 1 << 16;
    for (U64 i = 1; i < MAX; i = i + sep)
    {
        S(i);
    }
    for (U64 i = begin; i < MAX; i = i + sep)
    {
        S(i);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Thời gian thực thi: %f giây\n", cpu_time_used);
    return 0;
}