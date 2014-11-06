#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int main(void)
{
    /*  Create, push and pop with stack of type int  */

    Stack istk = stack_create(3, DATATYPE_INT, GDS_EXIT_ON_ERROR);

    stack_push(istk, 123);
    stack_push(istk, 456);
    stack_push(istk, 789);

    while ( !stack_is_empty(istk) ) {
        int i;
        stack_pop(istk, &i);
        printf("Popped int %d from stack.\n", i);
    }

    /*  Create, push and pop with stack of type long  */

    if ( sizeof(long) >= 8U ) {
        Stack lstk = stack_create(3, DATATYPE_LONG, GDS_EXIT_ON_ERROR);

        stack_push(lstk, 123000000000L);
        stack_push(lstk, 456000000000L);
        stack_push(lstk, 789000000000L);

        while ( !stack_is_empty(lstk) ) {
            long l;
            stack_pop(lstk, &l);
            printf("Popped long %ld from stack.\n", l);
        }

        stack_destroy(lstk);
    }

    /*  Create, push and pop with stack of type float  */

    Stack cstk = stack_create(3, DATATYPE_CHAR, GDS_EXIT_ON_ERROR);

    stack_push(cstk, 'a');
    stack_push(cstk, 'b');
    stack_push(cstk, 'c');

    while ( !stack_is_empty(cstk) ) {
        char c;
        stack_pop(cstk, &c);
        printf("Popped float '%c' from stack.\n", c);
    }

    /*  Create, push and pop with stack of type double  */

    Stack dstk = stack_create(3, DATATYPE_DOUBLE, GDS_EXIT_ON_ERROR);

    stack_push(dstk, 1.23);
    stack_push(dstk, 4.56);
    stack_push(dstk, 7.89);

    while ( !stack_is_empty(dstk) ) {
        double d;
        stack_pop(dstk, &d);
        printf("Popped double %f from stack.\n", d);
    }

    /*  Create, push and pop with stack of strings  */

    Stack sstk = stack_create(5, DATATYPE_POINTER,
                              GDS_EXIT_ON_ERROR | GDS_FREE_ON_DESTROY);

    stack_push(sstk, strdup("First string"));
    stack_push(sstk, strdup("Second string"));
    stack_push(sstk, strdup("Third string"));
    stack_push(sstk, strdup("Fourth string"));
    stack_push(sstk, strdup("Fifth string"));

    for ( size_t i = 0; i < 3; ++i ) {
        void * p;
        stack_pop(sstk, &p);
        printf("Popped string \"%s\" from stack.\n", (char *) p);
        free(p);
    }

    /*  Create, push and pop with stack of type void *  */

    Stack pstk = stack_create(1, DATATYPE_POINTER,
                              GDS_EXIT_ON_ERROR | GDS_RESIZABLE);

    stack_push(pstk, (void *) &istk);
    stack_push(pstk, (void *) &cstk);
    stack_push(pstk, (void *) &dstk);
    stack_push(pstk, (void *) &sstk);
    stack_push(pstk, (void *) &pstk);

    while ( !stack_is_empty(pstk) ) {
        void * p;
        stack_pop(pstk, &p);
        printf("Popped pointer %p from stack.\n", p);
    }

    /*  Destroy stacks and exit  */

    stack_destroy(pstk);
    stack_destroy(sstk);
    stack_destroy(dstk);
    stack_destroy(cstk);
    stack_destroy(istk);

    return 0;
}
