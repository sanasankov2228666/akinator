#ifndef STACK_H_
#define STACK_H_
#include <stddef.h>
#include "akinator.h"

#define KANAREKA1 NULL
#define KANAREKA2 NULL
#define POISON NULL

typedef node_t* type;

//!структура стека
struct stk
{
    type* stack = NULL;
    size_t size = 0;
    size_t capacity = 0;
};

void stack_creator(struct stk* data, size_t capacity);

void stack_push(struct stk* data, type value);

type stack_pop(struct stk* data);

void stack_deleter(struct stk* data);

type stack_mass(struct stk* data, size_t index);

#endif
