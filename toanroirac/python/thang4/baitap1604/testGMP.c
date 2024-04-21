#include <stdio.h>
#include <gmp.h>

int main()
{
    mpz_t num;
    mpz_init(num);

    mpz_set_str(num, "12345678901234567890123456789012345678", 10);
    gmp_printf("Number: %Zd\n", num);

    mpz_clear(num);

    return 0;
}
