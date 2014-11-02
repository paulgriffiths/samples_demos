#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(void)
{
    Stack stk = stack_create(5);

    stack_push(stk, STACK_CHAR, 'x');
    stack_push(stk, STACK_INT, 123);
    stack_push(stk, STACK_FLOAT, 4.56);
    stack_push(stk, STACK_DOUBLE, 7.89);
    stack_push(stk, STACK_POINTER, (void *) &stk);

    while ( !stack_is_empty(stk) ) {
        char c;
        int i;
        float f;
        double d;
        void * p;

        switch ( stack_type_peek(stk) ) {
            case STACK_CHAR:
                stack_pop(stk, &c);
                printf("Popped char '%c' from stack.\n", c);
                break;

            case STACK_INT:
                stack_pop(stk, &i);
                printf("Popped int %d from stack.\n", i);
                break;

            case STACK_FLOAT:
                stack_pop(stk, &f);
                printf("Popped float %f from stack.\n", f);
                break;

            case STACK_DOUBLE:
                stack_pop(stk, &d);
                printf("Popped double %f from stack.\n", d);
                break;

            case STACK_POINTER:
                stack_pop(stk, &p);
                printf("Popped pointer %p from stack.\n", p);
                break;

            default:
                fprintf(stderr, "Unknown type.\n");
                return EXIT_FAILURE;
        }
    }

    stack_destroy(stk);

    return 0;
}
