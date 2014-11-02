#ifndef PG_SAMPLES_AND_DEMOS_STACK_MULTITYPE_H
#define PG_SAMPLES_AND_DEMOS_STACK_MULTITYPE_H

#include <stdbool.h>

enum stack_type {
    STACK_CHAR,
    STACK_INT,
    STACK_LONG,
    STACK_FLOAT,
    STACK_DOUBLE,
    STACK_POINTER
};

typedef struct stack * Stack;

Stack stack_create(const size_t capacity);
void stack_destroy(Stack stack);
void stack_push(Stack stack, const enum stack_type type, ...);
void stack_pop(Stack stack, void * p);
enum stack_type stack_type_peek(Stack stack);
bool stack_is_empty(Stack stack);

#endif      /*  PG_SAMPLES_AND_DEMOS_STACK_MULTITYPE_H  */
