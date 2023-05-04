#pragma once
#include <stdbool.h>
#include "set.h"

typedef struct node node;

struct node
{
    node* next;
    node* prev;
    my_set set;
};

typedef struct 
{
    node *first;
    int size;
    node *terminator;
    // int version; //Для того, чтобы один из двух итераторов, 
    // применяемых к одному списку не поломал другой
} list;

typedef struct iter
{
    list *lst;
    node *next;
    node *prev;
    // int list_version;
} iter;

iter iter_begin(list *l);
iter iter_end(list *l);
bool iter_eq(iter it1, iter it2);
void iter_inc(iter *it);
void iter_dec(iter *it);
void iter_getval(const iter *it);
void iter_setval(iter *it, my_set s);
void iter_remove(iter *it);
void iter_add(iter *it, my_set s);
void iter_add_to_set(iter *it, int digit);

void list_init(list *l);
void list_destroy(list *lst);
