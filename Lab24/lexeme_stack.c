
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "lexeme_stack.h"

#define MIN_CAP 10


void lex_stack_init(lex_stack *s)
{   
    s->count = 0;
    s->capacity = MIN_CAP;
    s->buff = malloc(MIN_CAP * sizeof(lexeme));
}

void lex_stack_destroy(lex_stack *s)
{
    s->count = 0;
    free(s->buff);
    s->capacity = MIN_CAP;
}

int lex_stack_size(lex_stack *s)
{
    return s->count;
}

bool lex_stack_is_empty(lex_stack *s)
{
    return lex_stack_size(s) == 0;
}

static bool increase(lex_stack *s)
{
    int new_cap = 2 * (s->capacity);
    if(new_cap < MIN_CAP)
    {
        new_cap = MIN_CAP;
    }
    lexeme *tmp = realloc(s->buff, new_cap*sizeof(lexeme));
    if (tmp == NULL)
    {
        return false;
    }
    s->capacity = new_cap;
    s->buff = tmp;
    return true;
}

bool lex_stack_push(lex_stack *s, lexeme val)
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
/*
static void decrease_if_possible(lex_stack *s)
{
    if(s->count >= (s->capacity) / 4) return;
    int new_cap = (s->capacity) / 2;
    if (new_cap < MIN_CAP)
    {
        new_cap = MIN_CAP;
    }
    if(new_cap < s->capacity)
    {
        s->buff = realloc(s->buff, new_cap*sizeof(lexeme));
        s->capacity = new_cap;
    }
}*/

bool lex_stack_pop(lex_stack *s, lexeme *popped)
{
    if(lex_stack_is_empty(s))
    {
        return false;
    }
    lexeme res = s->buff[s->count - 1];
    s->count--;
    // decrease_if_possible(s);
    *popped = res;
    return true;
}

void lex_stack_print(const lex_stack *s)
{
    for(int i = 0; i < s->count; ++i)
    {
        if(s->buff[i].type == LEX_CONST)
        {
            printf("%lf\n", s->buff[i].cnst);
        }
        else if(s->buff[i].type == LEX_VAR_NAME)
        {
            printf("%s\n", s->buff[i].var_name);
        }
        else if(s->buff[i].type == LEX_BR_L)
        {
            printf("(\n");
        }
        else if(s->buff[i].type == LEX_BR_R)
        {
            printf(")\n");
        }
        else if(s->buff[i].type == LEX_OPER)
        {
            printf("%c\n", s->buff[i].oper);
        }
    }
}