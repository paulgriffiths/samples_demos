#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "stack.h"

/*  Struct to contain stack element  */

struct stack_element {
    union {
        char val_c;
        int val_i;
        long val_l;
        float val_f;
        double val_d;
        void * val_p;
    } data;
};

/*  Struct to contain stack  */

struct stack {
    size_t top;
    size_t capacity;
    enum stack_type type;
    struct stack_element * elements;
};

/*  Creates and returns a new stack of specified type and capacity  */

struct stack * stack_create(const size_t capacity, const enum stack_type type)
{
    struct stack * new_stack = malloc(sizeof *new_stack);
    if ( !new_stack ) {
        perror("couldn't allocate memory for stack");
        exit(EXIT_FAILURE);
    }

    new_stack->capacity = capacity;
    new_stack->top = 0;
    new_stack->type = type;

    new_stack->elements = malloc(sizeof *new_stack->elements * capacity);
    if ( !new_stack->elements ) {
        free(new_stack);
        perror("couldn't allocate memory for stack elements");
        exit(EXIT_FAILURE);
    }

    return new_stack;
}

/*  Destroys a previously created stack  */

void stack_destroy(struct stack * stack)
{
    free(stack->elements);
    free(stack);
}

/*  Pushes an element onto the stack  */

void stack_push(struct stack * stack, ...)
{
    if ( stack->top == stack->capacity ) {
        fprintf(stderr, "Stack full!\n");
        exit(EXIT_FAILURE);
    }

    va_list ap;
    va_start(ap, stack);

    switch ( stack->type ) {
        case STACK_CHAR:
            stack->elements[stack->top++].data.val_c = (char) va_arg(ap, int);
            break;

        case STACK_INT:
            stack->elements[stack->top++].data.val_i = va_arg(ap, int);
            break;

        case STACK_LONG:
            stack->elements[stack->top++].data.val_l = va_arg(ap, long);
            break;

        case STACK_FLOAT:
            stack->elements[stack->top++].data.val_f = (float) va_arg(ap, double);
            break;

        case STACK_DOUBLE:
            stack->elements[stack->top++].data.val_d = va_arg(ap, double);
            break;

        case STACK_POINTER:
            stack->elements[stack->top++].data.val_p = va_arg(ap, void *);
            break;

        default:
            fprintf(stderr, "Unknown type in stack_push()\n");
            exit(EXIT_FAILURE);
    }

    va_end(ap);
}

void stack_pop(struct stack * stack, void * p)
{
    if ( stack->top == 0 ) {
        fprintf(stderr, "Stack empty!\n");
        exit(EXIT_FAILURE);
    }

    switch ( stack->type ) {
        case STACK_CHAR:
            *((char *) p) = stack->elements[--stack->top].data.val_c;
            break;

        case STACK_INT:
            *((int *) p) = stack->elements[--stack->top].data.val_i;
            break;

        case STACK_LONG:
            *((long *) p) = stack->elements[--stack->top].data.val_l;
            break;

        case STACK_FLOAT:
            *((float *) p) = stack->elements[--stack->top].data.val_f;
            break;

        case STACK_DOUBLE:
            *((double *) p) = stack->elements[--stack->top].data.val_d;
            break;

        case STACK_POINTER:
            *((void **) p) = stack->elements[--stack->top].data.val_p;
            break;

        default:
            fprintf(stderr, "Unknown type in stack_pop()\n");
            exit(EXIT_FAILURE);
    }
}
