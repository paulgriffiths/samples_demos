#ifndef PG_SAMPLES_AND_DEMOS_GENERIC_STACK_H
#define PG_SAMPLES_AND_DEMOS_GENERIC_STACK_H

#include <stdbool.h>
#include <stddef.h>

#include "datatypes.h"

typedef struct stack * Stack;

Stack stack_create(const size_t capacity,
                   const enum gds_datatype type,
                   const int opts);
void stack_destroy(Stack stack);
bool stack_push(Stack stack, ...);
bool stack_pop(Stack stack, void * p);
bool stack_is_full(Stack stack);
bool stack_is_empty(Stack stack);
size_t stack_capacity(Stack stack);
size_t stack_free_space(Stack stack);

#endif      /*  PG_SAMPLES_AND_DEMOS_GENERIC_STACK_H  */
