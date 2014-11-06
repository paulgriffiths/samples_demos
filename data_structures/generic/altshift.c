#include <stdio.h>
#include <math.h>
#include <stdbool.h>

unsigned int ui_pow(unsigned int base, unsigned int exponent)
{
    unsigned int result = 1;
    for ( unsigned int i = 1; i <= exponent; ++i ) {
        result *= base;
    }
    return result;
}

bool bit_is_set_one(unsigned int n, unsigned int bit)
{
    return (n >> bit) & 1;
}

bool bit_is_set_two(unsigned int n, unsigned int bit)
{
    return (n / ui_pow(2, bit)) % 2;
}

int main(void)
{
    bool all_equal = true;

    for ( unsigned int i = 0; i < 65535; ++i ) {
        for ( unsigned int j = 0; j < 16; ++j ) {
            if ( bit_is_set_one(i, j) != bit_is_set_two(i, j) ) {
                all_equal = false;
            }
        }
    }

    printf("Methods%s give equal results.\n", all_equal ? "" : " do not");

    return 0;
}
