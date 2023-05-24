#include "lexeme_tree.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
// #include "vector.h"

int max(int a, int b)
{
    return a > b ? a : b;
}

bool lex_tree_is_empty(lex_tree t)
{
    return t == NULL;
}

lex_tree lex_tree_empty()
{
    return NULL;
}

lex_tree lex_tree_build(lexeme val, lex_tree l, lex_tree r)
{
    lex_tree new_lex_tree = malloc(sizeof(node));
    new_lex_tree->left = l;
    new_lex_tree->right = r;
    new_lex_tree->val = val;
    return new_lex_tree;
}

lexeme lex_tree_root_val(lex_tree t)
{
    return t->val;
}

lex_tree lex_tree_left(lex_tree t)
{
    return t->left;
}

lex_tree lex_tree_right(lex_tree t)
{
    return t->right;
}

int depth(lex_tree t)
{
    if (t == NULL)
    {
        return 0;
    }
    return 1 + max(depth(t->left), depth(t->right));
}

void lex_tree_print(lex_tree t, int level)
{
    if (t == NULL)
    {
        return;
    }
    // Обход ЛКП
    lex_tree_print(t->left, level + 1);
    for (int i = 0; i < level; ++i)
    {
        printf("\t");
    }
    if (t->val.type == LEX_CONST)
    {
        printf("%lf\n", t->val.cnst);
    }
    else if (t->val.type == LEX_VAR_NAME)
    {
        printf("%s\n", t->val.var_name);
    }
    else if (t->val.type == LEX_BR_L)
    {
        printf("(\n");
    }
    else if (t->val.type == LEX_BR_R)
    {
        printf(")\n");
    }
    else if (t->val.type == LEX_OPER)
    {
        printf("%c\n", t->val.oper);
    }
    lex_tree_print(t->right, level + 1);
}

void lex_tree_destroy(lex_tree tree)
{
    if(tree == NULL)
    {
        return;
    }
    lex_tree_destroy(tree->left);
    lex_tree_destroy(tree->right);
    free(tree);
}

// static void width_intern(lex_tree t, int_vec *v, int depth)
// {
//     if(t==NULL)
//     {
//         return;
//     }
//     int_vec_setval(v, depth, v_get_val(v, depth)+1);
//     width_intern(t->left, v, depth+1);
//     width_intern(t->right, v, depth+1);
// }

// int width(lex_tree t)
// {
//     int_vec cnt_width;//вектор ширин
//     int_vec(&cnt_width);//на i-той позиции хранится ширина i-того уровня
//     int depth = depth(t);
//     int_v_set_size(&cnt_width, depth);
//     width_intern(t, &cnt_width, 0);
//     int max_width = 0;
//     for(int i=0;i<depth;++i)
//     {
//         int wd = int_v_get_val(&cnt_width, i);
//         if(wd > max_width)
//         {
//             max_width = wd;
//         }
//     }
//     int_v_destroy(&cnt_width);
//     return max_width;

// }
