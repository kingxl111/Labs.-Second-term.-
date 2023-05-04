#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "stack_of_lexeme_trees.h"


#define MIN_CAP 10


void stack_of_lex_trees_init(stack_of_lex_trees *s)
{   
    s->count = 0;
    s->capacity = MIN_CAP;
    s->buff = malloc(MIN_CAP * sizeof(node));
}

void stack_of_lex_trees_destroy(stack_of_lex_trees *s)
{
    s->count = 0;
    free(s->buff);
    s->capacity = MIN_CAP;
}

int stack_of_lex_trees_size(stack_of_lex_trees *s)
{
    return s->count;
}

bool stack_of_lex_trees_is_empty(stack_of_lex_trees *s)
{
    return stack_of_lex_trees_size(s) == 0;
}

static bool increase(stack_of_lex_trees *s)
{
    int new_cap = 2 * (s->capacity);
    if(new_cap < MIN_CAP)
    {
        new_cap = MIN_CAP;
    }
    lex_tree *tmp = realloc(s->buff, new_cap * sizeof(node));
    if (tmp == NULL)
    {
        return false;
    }
    s->capacity = new_cap;
    s->buff = tmp;
    return true;
}

bool stack_of_lex_trees_push(stack_of_lex_trees *s, lex_tree val)
{
    if(s->capacity == s->count)
    {
        if(!increase(s))
        {
            return false;
        }
    }
    s->buff[s->count] = val;
    s->count++;
    return true;
}   


bool stack_of_lex_trees_pop(stack_of_lex_trees *s, lex_tree *popped)
{
    if(stack_of_lex_trees_is_empty(s))
    {
        return false;
    }
    lex_tree res = s->buff[s->count - 1];
    s->count--;
    // decrease_if_possible(s);
    *popped = res;
    return true;
}

