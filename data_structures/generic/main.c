#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "queue.h"

void test_stack(void)
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

    Stack sstk = stack_create(5, DATATYPE_STRING,
                              GDS_EXIT_ON_ERROR | GDS_FREE_ON_DESTROY);

    stack_push(sstk, strdup("First string"));
    stack_push(sstk, strdup("Second string"));
    stack_push(sstk, strdup("Third string"));
    stack_push(sstk, strdup("Fourth string"));
    stack_push(sstk, strdup("Fifth string"));

    for ( size_t i = 0; i < 3; ++i ) {
        char * p;
        stack_pop(sstk, &p);
        printf("Popped string \"%s\" from stack.\n", p);
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
}

void test_queue(void)
{
    /*  Create, push and pop with queue of type int  */

    Queue ique = queue_create(3, DATATYPE_INT, GDS_EXIT_ON_ERROR);

    queue_push(ique, 123);
    queue_push(ique, 456);
    queue_push(ique, 789);

    while ( !queue_is_empty(ique) ) {
        int i;
        queue_pop(ique, &i);
        printf("Popped int %d from queue.\n", i);
    }

    /*  Create, push and pop with queue of type long  */

    if ( sizeof(long) >= 8U ) {
        Queue lque = queue_create(3, DATATYPE_LONG, GDS_EXIT_ON_ERROR);

        queue_push(lque, 123000000000L);
        queue_push(lque, 456000000000L);
        queue_push(lque, 789000000000L);

        while ( !queue_is_empty(lque) ) {
            long l;
            queue_pop(lque, &l);
            printf("Popped long %ld from queue.\n", l);
        }

        queue_destroy(lque);
    }

    /*  Create, push and pop with queue of type float  */

    Queue cque = queue_create(3, DATATYPE_CHAR, GDS_EXIT_ON_ERROR);

    queue_push(cque, 'a');
    queue_push(cque, 'b');
    queue_push(cque, 'c');

    while ( !queue_is_empty(cque) ) {
        char c;
        queue_pop(cque, &c);
        printf("Popped float '%c' from queue.\n", c);
    }

    /*  Create, push and pop with queue of type double  */

    Queue dque = queue_create(3, DATATYPE_DOUBLE, GDS_EXIT_ON_ERROR);

    queue_push(dque, 1.23);
    queue_push(dque, 4.56);
    queue_push(dque, 7.89);

    while ( !queue_is_empty(dque) ) {
        double d;
        queue_pop(dque, &d);
        printf("Popped double %f from queue.\n", d);
    }

    /*  Create, push and pop with queue of strings  */

    Queue sque = queue_create(5, DATATYPE_STRING,
                              GDS_EXIT_ON_ERROR | GDS_FREE_ON_DESTROY);

    queue_push(sque, strdup("First string"));
    queue_push(sque, strdup("Second string"));
    queue_push(sque, strdup("Third string"));
    queue_push(sque, strdup("Fourth string"));
    queue_push(sque, strdup("Fifth string"));

    for ( size_t i = 0; i < 3; ++i ) {
        char * p;
        queue_pop(sque, &p);
        printf("Popped string \"%s\" from queue.\n", p);
        free(p);
    }

    /*  Create, push and pop with queue of type void *  */

    Queue pque = queue_create(1, DATATYPE_POINTER,
                              GDS_EXIT_ON_ERROR | GDS_RESIZABLE);

    queue_push(pque, (void *) &ique);
    queue_push(pque, (void *) &cque);
    queue_push(pque, (void *) &dque);
    queue_push(pque, (void *) &sque);
    queue_push(pque, (void *) &pque);

    while ( !queue_is_empty(pque) ) {
        void * p;
        queue_pop(pque, &p);
        printf("Popped pointer %p from queue.\n", p);
    }

    /*  Destroy queues and exit  */

    queue_destroy(pque);
    queue_destroy(sque);
    queue_destroy(dque);
    queue_destroy(cque);
    queue_destroy(ique);
}

int main(int argc, char ** argv)
{
    bool stack = false, queue = false;

    if ( argc < 2 ) {
        stack = true;
        queue = true;
    }
    else {
        size_t i = 0;

        while ( argv[++i] ) {
            if ( !strcmp(argv[i], "stack") ) {
                stack = true;
            }
            else if ( !strcmp(argv[i], "queue") ) {
                queue = true;
            }
        }
    }

    if ( stack ) {
        test_stack();
    }

    if ( queue ) {
        test_queue();
    }

    return 0;
}
