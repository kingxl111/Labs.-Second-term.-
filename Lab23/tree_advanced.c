#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "tree_advanced.h"

int max(int a, int b)
{
    return a > b ? a : b;
}

void create(tree *t, colors c)
{
    (*t) = malloc(sizeof(node));
    (*t)->child = NULL;
    (*t)->next_brother = NULL;
    (*t)->color = c;
    // printf("%d\n", c);
    // printf("%d\n", (*t)->color);
}

tree *get_node(tree *t, char *path)
{

    if (path[0] == '\0')
    {
        return t;
    }
    else if (path[0] == 'c' && (*t) != NULL)
    {
        return get_node(&((*t)->child), path + 1);
    }
    else if (path[0] == 'b' && (*t) != NULL)
    {
        return get_node(&((*t)->next_brother), path + 1);
    }
    else
    {
        return NULL;
    }
}

bool add(tree *t, colors val, char *path)
{
    tree *place = get_node(t, path);
    if (place == NULL)
    {
        return false;
    }
    node *new_node = malloc(sizeof(node));
    new_node->next_brother = (*place);
    new_node->color = val;
    new_node->child = NULL;
    *place = new_node;
    return true;
}

// void print_tree(tree t)
// {
//     if(t==NULL)
//     {
//         return;
//     }
//     print_tree(t->next_brother); //Левое значение -> корень -> правое значение
//     printf("%lf ", t->color);
//     print_tree(t->child);
// }

char *int2color(colors clr)
{
    /* None, red, green, blue, yellow, purple, orange, white */
    char *color;
    if (clr == red)
        color = "red";
    else if (clr == green)
        color = "green";
    else if (clr == blue)
        color = "blue";
    else if (clr == yellow)
        color = "yellow";
    else if (clr == purple)
        color = "purple";
    else if (clr == orange)
        color = "orange";
    else if (clr == white)
        color = "white";
    else
        color = "None";
    // printf("CLR: %s\n", color);
    return color;
}

static void print_tree_tab_intern(tree t, int depth)
{
    if (t == NULL)
    {
        return;
    }
    for (int i = 0; i < depth; ++i)
    {
        printf("    ");
    }
    char *color;
    color = int2color(t->color);
    printf("%s (degree: %d)\n", color, count_degree(t->child));
    print_tree_tab_intern(t->child, depth + 1);
    print_tree_tab_intern(t->next_brother, depth);
}

void print_tree_tab(tree t)
{
    print_tree_tab_intern(t, 0);
}

int tree_depth(tree t)
{
    if (t == NULL)
    {
        return 0;
    }
    return max(tree_depth(t->next_brother), 1 + tree_depth(t->child));
}

static void remove_node(tree t)
{
    if (t == NULL)
    {
        return;
    }
    remove_node(t->child);
    remove_node(t->next_brother);
    free(t);
}

colors node_pop(tree *t, char *path)
{
    tree to_pop = NULL;
    tree *prev = NULL;
    bool is_child = false;   // Является ли удаляемый узел первым ребенком
    bool is_brother = false; // Является ли удаляемый узел чьим-то братом
    if (t == NULL)
        return -1;
    while (path[0] != '\0')
    {
        if (path[0] == 'c' && t != NULL)
        {
            prev = t;
            t = &((*t)->child);
            is_brother = false;
            is_child = true;
        }
        else if (path[0] == 'b' && t != NULL)
        {
            prev = t;
            t = &((*t)->next_brother);
            is_brother = true;
            is_child = false;
        }
        if ((*t) == NULL || (path[0] != 'b' && path[0] != 'c'))
        {
            is_brother = false;
            is_child = false;
            return -1; // Обработка случая, когда пользователь ввёл некорректный путь к узлу(или узла по такому пути нет)
        }
        path = path + 1;
    }
    to_pop = (*t);
    // printf("is_child: %d is_brother: %d\n", is_child, is_brother);
    remove_node(to_pop->child);
    if (is_brother)
    {
        (*prev)->next_brother = to_pop->next_brother;
    }
    else if (is_child)
    {
        (*prev)->child = to_pop->next_brother;
    }
    colors color = to_pop->color;
    free(to_pop);
    return color;
}

int count_degree(tree t)
{
    if (t == NULL)
    {
        return 0;
    }
    return 1 + count_degree(t->next_brother);
}
