#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "stack1.h"

//!фунция создания кода
void stack_creator(struct stk* data, size_t capacity)
{
    data->stack = (type*) calloc (capacity, sizeof(data->stack[0]));

    data->size = 0;
    data->capacity = capacity;
}

//!функция внесения в стек
void stack_push(struct stk* data, type value)
{
    if (data->capacity == data->size)
    {
        data->stack = (type*) realloc (data->stack, (data->capacity ) * 2 * sizeof(data->stack[0]));

        data->capacity = (data->capacity) * 2;

        for (size_t i = data->size; i < data->capacity; i++)
        {
            data->stack[i] = POISON;
        }
    }

    data->stack[data->size] = value;
    data->size = data->size + 1;
}

//!функция доставания из стека
node_t* stack_pop(struct stk* data)
{
    if (data->size == 0)
    {
        return NULL;
    }

    data->size = data->size - 1; 
    type parametr = data->stack[data->size];
    data->stack[data->size] = POISON;

    return parametr;
}

//!функция удаления стека
void stack_deleter(struct stk* data)
{
    if (data->stack == NULL)
    {
        printf("ERROR IN stack_deleter\n");
    }

    data->capacity = 0;
    data->size = 0;
    free (data->stack);
    data->stack = NULL;
}

type stack_mass(struct stk* data, size_t index)
{
    return data->stack[index];
}