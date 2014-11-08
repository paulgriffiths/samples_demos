#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdarg.h>
#include "gdt.h"

/*  Gets a value from a generic datatype  */

void gdt_set_value(struct gdt_generic_datatype * data,
                   const enum gds_datatype type, va_list ap)
{
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
    }
    else if ( type == DATATYPE_STRING ) {
        free(data->data.pc);
    }
}
