#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef enum colors 
{
    None,
    red,
    green,
    blue,
    yellow,
    purple,
    orange,
    white
} colors;

typedef struct node node;

struct node 
{
    colors color;
    node *child;
    node *next_brother;
};

typedef node* tree;


tree *get_node(tree *t, char *path);
bool add(tree *t, colors val, char* path);
// void print_tree(tree t);
char* int2color(colors clr);
void print_tree_tab(tree t);
int tree_depth(tree t);
colors node_pop(tree *t, char *path);
void create(tree *t, colors color);
int count_degree(tree t);
