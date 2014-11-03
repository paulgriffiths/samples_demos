#ifndef PG_SAMPLES_AND_DEMOS_NUMBERCONV_H
#define PG_SAMPLES_AND_DEMOS_NUMBERCONV_H

size_t number_of_digits(const int n, const size_t base);
void int_to_str(char * str, const size_t size, const int n, const size_t base);
int str_to_int(const char * str, const char ** endptr, const size_t base);

#endif      /*  PG_SAMPLES_AND_DEMOS_NUMBERCONV_H  */
