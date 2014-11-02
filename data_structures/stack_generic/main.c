#include <stdio.h>
#include "stack.h"

int main(void)
{
    /*  Create, push and pop with stack of type int  */

    Stack istk = stack_create(3, STACK_INT);

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
        Stack lstk = stack_create(3, STACK_LONG);

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

    Stack fstk = stack_create(3, STACK_FLOAT);

    stack_push(fstk, 1.23);
    stack_push(fstk, 4.56);
    stack_push(fstk, 7.89);

    while ( !stack_is_empty(fstk) ) {
        float f;
        stack_pop(fstk, &f);
        printf("Popped float %f from stack.\n", f);
    }

    /*  Create, push and pop with stack of type double  */

    Stack dstk = stack_create(3, STACK_DOUBLE);

    stack_push(dstk, 1.23);
    stack_push(dstk, 4.56);
    stack_push(dstk, 7.89);

    while ( !stack_is_empty(dstk) ) {
        double d;
        stack_pop(dstk, &d);
        printf("Popped double %f from stack.\n", d);
    }

    /*  Create, push and pop with stack of type void *  */

    Stack pstk = stack_create(3, STACK_POINTER);

    stack_push(pstk, (void *) &istk);
    stack_push(pstk, (void *) &fstk);
    stack_push(pstk, (void *) &dstk);

    while ( !stack_is_empty(pstk) ) {
        void * p;
        stack_pop(pstk, &p);
        printf("Popped pointer %p from stack.\n", p);
    }

    /*  Destroy stacks and exit  */

    stack_destroy(pstk);
    stack_destroy(dstk);
    stack_destroy(fstk);
    stack_destroy(istk);

    return 0;
}
