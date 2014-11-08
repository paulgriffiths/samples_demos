#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdarg.h>
#include "gds_common.h"

typedef int (*CompFunc)(const void *, const void *);

static int gdt_compare_char(const void * p1, const void * p2);
static int gdt_compare_uchar(const void * p1, const void * p2);
static int gdt_compare_schar(const void * p1, const void * p2);
static int gdt_compare_int(const void * p1, const void * p2);
static int gdt_compare_uint(const void * p1, const void * p2);
static int gdt_compare_long(const void * p1, const void * p2);
static int gdt_compare_ulong(const void * p1, const void * p2);
static int gdt_compare_longlong(const void * p1, const void * p2);
static int gdt_compare_ulonglong(const void * p1, const void * p2);
static int gdt_compare_sizet(const void * p1, const void * p2);
static int gdt_compare_double(const void * p1, const void * p2);
static int gdt_compare_string(const void * p1, const void * p2);

static CompFunc cfuncs[] = {
    gdt_compare_char,
    gdt_compare_uchar,
    gdt_compare_schar,
    gdt_compare_int,
    gdt_compare_uint,
    gdt_compare_long,
    gdt_compare_ulong,
    gdt_compare_longlong,
    gdt_compare_ulonglong,
    gdt_compare_sizet,
    gdt_compare_double,
    gdt_compare_string
};


/*  Gets a value from a generic datatype  */

void gdt_set_value(struct gdt_generic_datatype * data,
                   const enum gds_datatype type, va_list ap)
{
    data->type = type;

    switch ( type ) {
        case DATATYPE_CHAR:
            data->data.c = (char) va_arg(ap, int);
            break;

        case DATATYPE_SIGNED_CHAR:
            data->data.sc = (signed char) va_arg(ap, int);
            break;

        case DATATYPE_UNSIGNED_CHAR:
            data->data.uc = (unsigned char) va_arg(ap, int);
            break;

        case DATATYPE_INT:
            data->data.i = va_arg(ap, int);
            break;

        case DATATYPE_UNSIGNED_INT:
            data->data.ui = va_arg(ap, unsigned int);
            break;

        case DATATYPE_LONG:
            data->data.l = va_arg(ap, long);
            break;

        case DATATYPE_UNSIGNED_LONG:
            data->data.ul = va_arg(ap, unsigned long);
            break;

        case DATATYPE_LONG_LONG:
            data->data.ll = va_arg(ap, long long);
            break;

        case DATATYPE_UNSIGNED_LONG_LONG:
            data->data.ull = va_arg(ap, unsigned long long);
            break;

        case DATATYPE_SIZE_T:
            data->data.st = va_arg(ap, size_t);
            break;

        case DATATYPE_DOUBLE:
            data->data.d = va_arg(ap, double);
            break;

        case DATATYPE_STRING:
            data->data.pc = va_arg(ap, char *);
            break;

        case DATATYPE_POINTER:
            data->data.p = va_arg(ap, void *);
            break;

        default:
            assert(false);
            break;
    }
}

/*  Sets a value in a generic datatype  */

void gdt_get_value(const struct gdt_generic_datatype * data,
                   const enum gds_datatype type, void * p)
{
    switch ( type ) {
        case DATATYPE_CHAR:
            *((char *) p) = data->data.c;
            break;

        case DATATYPE_SIGNED_CHAR:
            *((signed char *) p) = data->data.sc;
            break;

        case DATATYPE_UNSIGNED_CHAR:
            *((unsigned char *) p) = data->data.uc;
            break;

        case DATATYPE_INT:
            *((int *) p) = data->data.i;
            break;

        case DATATYPE_UNSIGNED_INT:
            *((unsigned int *) p) = data->data.ui;
            break;

        case DATATYPE_LONG:
            *((long *) p) = data->data.l;
            break;

        case DATATYPE_UNSIGNED_LONG:
            *((unsigned long *) p) = data->data.ul;
            break;

        case DATATYPE_LONG_LONG:
            *((long long *) p) = data->data.ll;
            break;

        case DATATYPE_UNSIGNED_LONG_LONG:
            *((unsigned long long *) p) = data->data.ull;
            break;

        case DATATYPE_SIZE_T:
            *((size_t *) p) = data->data.st;
            break;

        case DATATYPE_DOUBLE:
            *((double *) p) = data->data.d;
            break;

        case DATATYPE_STRING:
            *((char **) p) = data->data.pc;
            break;

        case DATATYPE_POINTER:
            *((void **) p) = data->data.p;
            break;

        default:
            assert(false);
            break;
    }
}

/*  Frees the memory pointer to by a generic pointer datatype  */

void gdt_free(struct gdt_generic_datatype * data, const enum gds_datatype type)
{
    if ( type == DATATYPE_POINTER ) {
        free(data->data.p);
        data->data.p = NULL;
    }
    else if ( type == DATATYPE_STRING ) {
        free(data->data.pc);
        data->data.pc = NULL;
    }
}

/*  Compares two generic datatypes  */

int gdt_compare(const struct gdt_generic_datatype * d1,
                const struct gdt_generic_datatype * d2)
{
    if ( d1->type != d2->type ) {
        gds_assert_quit("types are not compatible (%s, line %d)",
                   __FILE__, __LINE__);
    }

    if ( d1->type == DATATYPE_CHAR ) {
        return gdt_compare_char(&d1->data.c, &d2->data.c);
    }
    else if ( d1->type == DATATYPE_UNSIGNED_CHAR ) {
        return gdt_compare_uchar(&d1->data.uc, &d2->data.uc);
    }
    else if ( d1->type == DATATYPE_SIGNED_CHAR ) {
        return gdt_compare_schar(&d1->data.sc, &d2->data.sc);
    }
    else if ( d1->type == DATATYPE_INT ) {
        return gdt_compare_int(&d1->data.i, &d2->data.i);
    }
    else if ( d1->type == DATATYPE_UNSIGNED_INT ) {
        return gdt_compare_uint(&d1->data.ui, &d2->data.ui);
    }
    else if ( d1->type == DATATYPE_LONG ) {
        return gdt_compare_long(&d1->data.l, &d2->data.l);
    }
    else if ( d1->type == DATATYPE_UNSIGNED_LONG ) {
        return gdt_compare_ulong(&d1->data.ul, &d2->data.ul);
    }
    else if ( d1->type == DATATYPE_LONG_LONG ) {
        return gdt_compare_longlong(&d1->data.ll, &d2->data.ll);
    }
    else if ( d1->type == DATATYPE_UNSIGNED_LONG_LONG ) {
        return gdt_compare_ulonglong(&d1->data.ull, &d2->data.ull);
    }
    else if ( d1->type == DATATYPE_SIZE_T ) {
        return gdt_compare_sizet(&d1->data.st, &d2->data.st);
    }
    else if ( d1->type == DATATYPE_DOUBLE ) {
        return gdt_compare_double(&d1->data.d, &d2->data.d);
    }
    else if ( d1->type == DATATYPE_STRING ) {
        return gdt_compare_string(&d1->data.pc, &d2->data.pc);
    }
    else if ( d1->type == DATATYPE_POINTER ) {
        gds_assert_quit("pointer comparison not yet implemented");
    }
    else {
        gds_assert_quit("unrecognized type (%s, line %d)", __FILE__, __LINE__);
    }

    return 0;
}

/*  Element compare functions  */

static int gdt_compare_char(const void * p1, const void * p2)
{
    char c1 = *((char *) p1);
    char c2 = *((char *) p2);
    
    if ( c1 < c2 ) {
        return -1;
    }
    else if ( c1 > c2 ) {
        return 1;
    }
    else {
        return 0;
    }
}

static int gdt_compare_uchar(const void * p1, const void * p2)
{
    unsigned char c1 = *((unsigned char *) p1);
    unsigned char c2 = *((unsigned char *) p2);
    
    if ( c1 < c2 ) {
        return -1;
    }
    else if ( c1 > c2 ) {
        return 1;
    }
    else {
        return 0;
    }
}

static int gdt_compare_schar(const void * p1, const void * p2)
{
    signed char c1 = *((signed char *) p1);
    signed char c2 = *((signed char *) p2);
    
    if ( c1 < c2 ) {
        return -1;
    }
    else if ( c1 > c2 ) {
        return 1;
    }
    else {
        return 0;
    }
}

static int gdt_compare_int(const void * p1, const void * p2)
{
    int n1 = *((int *) p1);
    int n2 = *((int *) p2);
    
    if ( n1 < n2 ) {
        return -1;
    }
    else if ( n1 > n2 ) {
        return 1;
    }
    else {
        return 0;
    }
}

static int gdt_compare_uint(const void * p1, const void * p2)
{
    unsigned int n1 = *((unsigned int *) p1);
    unsigned int n2 = *((unsigned int *) p2);
    
    if ( n1 < n2 ) {
        return -1;
    }
    else if ( n1 > n2 ) {
        return 1;
    }
    else {
        return 0;
    }
}

static int gdt_compare_long(const void * p1, const void * p2)
{
    long n1 = *((long *) p1);
    long n2 = *((long *) p2);
    
    if ( n1 < n2 ) {
        return -1;
    }
    else if ( n1 > n2 ) {
        return 1;
    }
    else {
        return 0;
    }
}

static int gdt_compare_ulong(const void * p1, const void * p2)
{
    unsigned long n1 = *((unsigned long *) p1);
    unsigned long n2 = *((unsigned long *) p2);
    
    if ( n1 < n2 ) {
        return -1;
    }
    else if ( n1 > n2 ) {
        return 1;
    }
    else {
        return 0;
    }
}

static int gdt_compare_longlong(const void * p1, const void * p2)
{
    long long n1 = *((long long *) p1);
    long long n2 = *((long long *) p2);
    
    if ( n1 < n2 ) {
        return -1;
    }
    else if ( n1 > n2 ) {
        return 1;
    }
    else {
        return 0;
    }
}

static int gdt_compare_ulonglong(const void * p1, const void * p2)
{
    unsigned long long n1 = *((unsigned long long *) p1);
    unsigned long long n2 = *((unsigned long long *) p2);
    
    if ( n1 < n2 ) {
        return -1;
    }
    else if ( n1 > n2 ) {
        return 1;
    }
    else {
        return 0;
    }
}

static int gdt_compare_sizet(const void * p1, const void * p2)
{
    size_t s1 = *((size_t *) p1);
    size_t s2 = *((size_t *) p2);
    
    if ( s1 < s2 ) {
        return -1;
    }
    else if ( s1 > s2 ) {
        return 1;
    }
    else {
        return 0;
    }
}

static int gdt_compare_double(const void * p1, const void * p2)
{
    double d1 = *((double *) p1);
    double d2 = *((double *) p2);
    
    if ( d1 < d2 ) {
        return -1;
    }
    else if ( d1 > d2 ) {
        return 1;
    }
    else {
        return 0;
    }
}

static int gdt_compare_string(const void * p1, const void * p2)
{
    char * s1 = *((char **) p1);
    char * s2 = *((char **) p2);

    return strcmp(s1, s2);
}
