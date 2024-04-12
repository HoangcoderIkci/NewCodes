#include <stdio.h>
int countBitsFast(unsigned int n)
{
    int count = 0;
    while (n)
    {
        n &= (n - 1); // Loại bỏ bit 1 cuối cùng
        count++;
    }
    return count;
}

int main()
{
    unsigned int f = 0b110101;
    printf("count: %d\n", countBitsFast(f));
    return 0;
}