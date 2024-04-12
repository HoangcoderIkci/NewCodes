// program cacl parity word for rank = 32
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t parityWord(uint8_t x)
{
    x ^= x >> 1;
    x ^= x >> 2;
    x ^= x >> 4;
    x ^= x >> 8;
    return x & 0b1;
}
uint8_t parityWord2(uint8_t x)
{
    x ^= x >> 1;
    x ^= x >> 2;
    x &= 0x11111111;
    x *= 0x11111111;
    return (x >> 28) & 0x1;
}
int main()
{
    uint8_t res = parityWord(11);
    printf(" parity x = %u\n", res);
    return 0;
}