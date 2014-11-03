#include <stdio.h>
#include <stdlib.h>
#include "numberconv.h"

/*  Tests string to int function  */

void test_str_to_int(const char * str, const size_t base)
{
    const char * endptr;
    int n = str_to_int(str, &endptr, base);
    printf("'%s' in base %zu converts to [%d] - *endptr is %s\n",
           str, base, n, *endptr ? "not zero" : "zero");
}

/*  Tests int to string function  */

void test_int_to_str(const int n, const size_t base) {
    char buffer[number_of_digits(n, base) + 1];
    int_to_str(buffer, sizeof buffer, n, base);
    printf("[%d] converts to '%s' in base %zu\n", n, buffer, base);
}

/*  Main function  */

int main(void)
{
    test_str_to_int("1024", 10);
    test_str_to_int("-1024", 10);
    test_str_to_int("FF", 16);
    test_str_to_int("-ff", 16);
    test_str_to_int("0", 2);
    test_str_to_int("123a", 10);
    test_str_to_int("1012", 2);

    test_int_to_str(1024, 10);
    test_int_to_str(-1024, 10);
    test_int_to_str(5, 2);
    test_int_to_str(-5, 2);
    test_int_to_str(48879, 16);
    test_int_to_str(-48879, 16);
    test_int_to_str(1023, 2);
    test_int_to_str(1024, 2);

    return 0;
}
