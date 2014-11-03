#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stddef.h>
#include "numberconv.h"

/*  Returns the number of digits needed to represent
 *  the specified number in the specified base.       */

size_t number_of_digits(const int n, const size_t base)
{
    size_t num_digits = 1;
    int tempnum = abs(n);

    while ( (tempnum /= base) ) {
        ++num_digits;
    }

    return n >= 0 ? num_digits : num_digits + 1;
}

/*  Converts an integer to a string  */

void int_to_str(char * str, const size_t size, const int n, const size_t base)
{
    static const char digits[] = "0123456789abcdefghijlkmnopqrstuvwxyz";

    /*  This function only handles base 2 through base 36  */

    assert(base > 1 && base < 37 && size);
    
    const size_t num_digits = number_of_digits(n, base);

    if ( num_digits > (size - 1) ) {

        /*  Representation will not fit in provided string  */

        *str = 0;
        return;
    }

    size_t i = 0;
    const size_t positive = n >= 0 ? 1: 0;

    if ( !positive ) {

        /*  Add leading negative sign if necessary  */

        str[i++] = '-';
    }

    /*  Convert absolute number to string  */

    int tempnum = abs(n);
    for ( ; i < num_digits; ++i ) {
        str[num_digits - positive - i] = digits[tempnum % base];
        tempnum /= base;
    }

    /*  Add terminating null  */

    str[i] = 0;
}

/*  Converts a string to an integer  */

int str_to_int(const char * str, const char ** endptr, const size_t base)
{
    static const char digits[] = "0123456789abcdefghijlkmnopqrstuvwxyz";

    /*  This function only handles base 2 through base 36  */

    assert(base > 1 && base < 37);

    int result = 0;
    const char * ptr = str;

    /*  Check for leading negative sign  */

    const int sign = (*ptr == '-') ? -1 : 1;
    if ( sign == -1 ) {
        ++ptr;
    }

    while ( *(*endptr = ptr) ) {
        const char * d = strchr(digits, tolower(*ptr));

        if ( !d ) {

            /*  Not a 'numeric' digit  */

            break;
        }

        const ptrdiff_t index = d - digits;

        if ( index >= (ptrdiff_t) base ) {

            /*  Numeric digit is outside range for specified base  */

            break;
        }
        else {

            /*  Numeric digit is OK  */

            result *= base;
            result += index;
            ++ptr;
        }
    }

    return result * sign;
}
