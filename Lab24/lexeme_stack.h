#pragma once
#include "expression.h"

typedef struct{
    int count;
    lexeme *buff;
    int capacity;
} lex_stack;

bool lex_stack_push(lex_stack *s, lexeme val);
void lex_stack_init(lex_stack *s);
void lex_stack_destroy(lex_stack *s);
bool lex_stack_pop(lex_stack *s, lexeme *popped);
int lex_stack_size(lex_stack *s);
bool lex_stack_is_empty(lex_stack *s);
void lex_stack_print(const lex_stack *s);