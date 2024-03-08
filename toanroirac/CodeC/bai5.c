#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define U32 int_fast32_t
#define U64 int_fast64_t
#define U8 int_fast8_t
#define U16 int_fast16_t
#define loop(i, a, b) for (int i = a; i < b; i++)

#define getBit(x, i) ((x >> i) & 0b1)

U16 powerofInertiaClass(U16 trustTable)
{
    U16 res;
    U8 flag, count = 0;
    loop(alpha, 0, 16)
    {
        res = 0;
        loop(j, 0, 16)
        {
            flag = getBit(trustTable, (j ^ alpha));
            if (flag)
                res ^= (1 << j);
        }
        if (res == trustTable)
            ++count;
    }
    return count;
}

U16 convertBinaryStringToNumber(char *str)
{
    U16 num = 0;
    while (*str != '\0')
    {
        num <<= 1;
        if (*str == '1')
            num |= 1;
        str++;
    }
    return num;
}

int main()
{
    char binaryString[17];
    printf("Enter a 16-bit binary number (e.g. 0b1110101010010101): ");
    scanf("%16s", binaryString);

    // Check if the input starts with '0b' and adjust the pointer if it does
    if (binaryString[0] == '0' && binaryString[1] == 'b')
    {
        printf("%u\n", powerofInertiaClass(convertBinaryStringToNumber(binaryString + 2)));
    }
    else
    {
        printf("%u\n", powerofInertiaClass(convertBinaryStringToNumber(binaryString)));
    }
    //  getchar();
    return 0;
}
