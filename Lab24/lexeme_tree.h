#pragma once
#include "expression.h"
#include <stdbool.h>


typedef struct node node;

typedef node* lex_tree;

struct node
{
    lexeme val;
    lex_tree left;
    lex_tree right;
};

bool lex_tree_is_empty(lex_tree t);
lex_tree lex_tree_empty();
lex_tree lex_tree_build(lexeme val, lex_tree l, lex_tree r);
lexeme lex_tree_root_val(lex_tree t);
lex_tree lex_tree_left(lex_tree t);
lex_tree lex_tree_right(lex_tree t);
void lex_tree_print(lex_tree t, int level);

// typedef struct
// {
//     tree new_t;
//     double removed_val;
// } rm_min_res;
