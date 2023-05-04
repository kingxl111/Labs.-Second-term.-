#pragma once
#include "expression.h"
#include "lexeme_tree.h"

typedef struct{
    int count;
    lex_tree *buff;
    int capacity;
} stack_of_lex_trees;

bool stack_of_lex_trees_push(stack_of_lex_trees *s, lex_tree val);
void stack_of_lex_trees_init(stack_of_lex_trees *s);
void stack_of_lex_trees_destroy(stack_of_lex_trees *s);
bool stack_of_lex_trees_pop(stack_of_lex_trees *s, lex_tree *popped);
int stack_of_lex_trees_size(stack_of_lex_trees *s);
bool stack_of_lex_trees_is_empty(stack_of_lex_trees *s);
