#ifndef PG_SAMPLES_AND_DEMOS_STACK_GENERIC_H
#define PG_SAMPLES_AND_DEMOS_STACK_GENERIC_H

enum stack_type {
    STACK_CHAR,
    STACK_INT,
    STACK_LONG,
    STACK_FLOAT,
    STACK_DOUBLE,
    STACK_POINTER
};

typedef struct stack * Stack;

Stack stack_create(const size_t capacity, const enum stack_type type);
void stack_destroy(Stack stack);
void stack_push(Stack stack, ...);
void stack_pop(Stack stack, void * p);

#endif      /*  PG_SAMPLES_AND_DEMOS_STACK_GENERIC_H  */
