#include <iostream>
#include <time.h>
#include <cstdint>

#define COUNT_BITS1(n) n, n + 1, n + 1, n + 2, n + 1, n + 2, n + 2, n + 3, n + 1, n + 2, n + 2, n + 3, n + 2, n + 3, n + 3, n + 4
#define COUNT_BITS2(n) COUNT_BITS1(n), COUNT_BITS1(n + 1), COUNT_BITS1(n + 1), COUNT_BITS1(n + 2), COUNT_BITS1(n + 1), COUNT_BITS1(n + 2), COUNT_BITS1(n + 2), COUNT_BITS1(n + 3), COUNT_BITS1(n + 1), COUNT_BITS1(n + 2), COUNT_BITS1(n + 2), COUNT_BITS1(n + 3), COUNT_BITS1(n + 2), COUNT_BITS1(n + 3), COUNT_BITS1(n + 3), COUNT_BITS1(n + 4)

// #define COUNT_BITS1(n) n, n + 1, n + 1, n + 2
// #define COUNT_BITS2(n) COUNT_BITS1(n), COUNT_BITS1(n + 1), COUNT_BITS1(n + 1), COUNT_BITS1(n + 2) // ứng với 1 byte
// #define COUNT_BITS3(n) COUNT_BITS2(n), COUNT_BITS2(n + 1), COUNT_BITS2(n + 1), COUNT_BITS2(n + 2)
// #define COUNT_BITS4(n) COUNT_BITS3(n), COUNT_BITS3(n + 1), COUNT_BITS3(n + 1), COUNT_BITS3(n + 2)
using namespace std;
int countBitFast(int64_t n)
{
    int count = 0;
    while (n)
    {
        ++count;
        n &= (n - 1);
    }
    return count;
}

int faster_popcount(unsigned x)
{
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = ((x + (x >> 4) & 0xF0F0F0F) * 0x1010101) >> 24;
    return x;
}
const uint8_t popcount_table[256] = {
    COUNT_BITS2(0)};
int lookup_popcount(unsigned x)
{
    // Bảng tra cứu với số lượng bit bằng 1 tương ứng cho mỗi giá trị từ 0 đến 255

    int count = 0;
    // Đếm số lượng bit bằng 1 bằng cách tra cứu từng byte trong từ x
    for (size_t i = 0; i < 256; i++)
    {
        if (popcount_table[i] != countBitFast(i))
        {
            printf("error :%d\n", i);
            break;
        }
    }
    // cout << endl;
    // for (; x; x >>= 8)
    // {
    //     count += popcount_table[x & 0xFF];
    // }

    return count;
}

int main()
{
    clock_t start, end;
    double elapsed;
    int64_t n = 1012412412422493123; // Số nguyên cần tính số bit 1
    start = clock();
    int count;
    count = lookup_popcount(n);

    // int count = __builtin_popcount(n); // Đếm số bit 1 trong số nguyên n
    end = clock();
    elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("time elapsed = %f\n", elapsed);
    std::cout << "Số bit 1 của " << n << " là: " << count << std::endl;

    return 0;
}