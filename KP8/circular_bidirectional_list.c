#include "circular_bidirectional_list.h"
#include <stdlib.h>
#include "set.h"
#include <stdbool.h>
#include <stdio.h>

iter iter_begin(list *l)
{
    iter it;
    it.prev = l->first->prev;
    it.next = l->first->next;
    it.lst = l;
    return it;
}

iter iter_end(list *l)
{
    iter it;
    it.prev = l->terminator->prev;
    it.next = l->terminator->next;
    it.lst = l;
    return it;
}

bool iter_eq(iter it1, iter it2)
{
    return (it1.prev->next == it2.prev->next) && (it1.lst == it2.lst);
}

void iter_inc(iter *it)
{
    it->next = it->next->next;
    it->prev = it->prev->next;
}

void iter_getval(const iter *it)
{
    if (it->prev->next != it->lst->terminator)
    {
        // printf("I'm going to print the set!\n");
        print_set(&(it->prev->next->set));
    }
    return;
}

void iter_setval(iter *it, my_set set)
{
    if (it->prev->next != it->lst->terminator)
    {
        it->prev->next->set.s = set.s;
        it->prev->next->set.size = set.size;
    }
    return;

}

void iter_remove(iter *it)
{
    node *to_remove = it->prev->next;
    if (to_remove == it->lst->terminator) // если вдруг хотим удалить "несуществующий" элемент
        return;
    if (it->prev == it->lst->terminator)
    {
        it->lst->terminator->next = it->next;
        it->next->prev = it->lst->terminator;
        it->lst->first = it->next; // it->lst->first = it->prev->next;
    }
    else if (it->next == it->lst->terminator)
    {
        it->lst->terminator->prev = it->prev;
        it->prev->next = it->lst->terminator;
    }
    else
    {
        it->prev->next = it->next;
        it->next->prev = it->prev;
    }
    free(to_remove);
    it->lst->size--;
}

void iter_add(iter *it, my_set set)
{
    node *new_elem = malloc(sizeof(node));
    //add_digit_to_set(digit, &(new_elem->set)); 
    new_elem->set.s = set.s;
    new_elem->set.size = set.size;
    if (it->prev == it->lst->terminator) // Ситуация добавления в начало
    {
        new_elem->prev = it->lst->terminator;
        new_elem->next = it->prev->next;
        // new_elem->next = it->lst->first;
        it->prev->next->prev = new_elem;
        it->lst->terminator->next = new_elem;
        // it->lst->first->prev = new_elem;
        it->lst->first = new_elem;
    }
    else if (it->prev->next == it->lst->terminator) //Ситуция добавления в конец
    {
        new_elem->next = it->lst->terminator;
        new_elem->prev = it->prev;
        it->prev->next = new_elem;
        it->lst->terminator->prev = new_elem;
    }
    else
    {
        new_elem->next = it->prev->next;
        new_elem->prev = it->prev;
        new_elem->next->prev = new_elem;
        new_elem->prev->next = new_elem;
        // printf("INSERTED: ");
        // print_set(&(it->prev->set));
    }
    it->lst->size++;
}

    
void list_init(list *l)
{
    l->terminator = malloc(sizeof(node));
    l->terminator->prev = l->terminator;
    l->terminator->next = l->terminator;
    l->first = l->terminator;
    l->size = 0;
}

void iter_dec(iter *it)
{
    it->next = it->prev->next;
    it->prev = it->prev->prev;
}
/*
static void cyclic_shift_right_intern(iter *old_begin)
{

    if(old_begin->lst->size<=1)
    {
        return;
    }
    iter_dec(old_begin);
    iter_dec(old_begin);
    node new_it = *(old_begin->prev->next);
    iter begin = iter_begin(old_begin->lst);
    iter_add(&begin, 0);
    iter_setval(&begin, new_it.set);
    iter_remove(old_begin);

    // it->lst->terminator->prev->next = it->lst->terminator->next;
    // it->lst->terminator->next = it->lst->terminator->prev;
    // it->lst->terminator->prev->prev->next = it->lst->terminator;
    // it->lst->terminator->prev = it->lst->terminator->prev->prev;
    // it->lst->terminator->next->prev = it->lst->terminator;
    // it->lst->terminator->next->next->prev = it->lst->terminator->next;

    // it->lst->first = it->lst->terminator->next;

    // node *last = it->lst->terminator->prev;
    // node *first = it->lst->terminator->next;

    // printf("last->set: ");
    // print_set(&(last->set));
    // printf("last->prev->prev->set: ");
    // print_set(&(last->prev->prev->set));
    // it->lst->terminator->prev = last->prev;
    // printf("it->lst->terminator->prev->set: ");
    // print_set(&(it->lst->terminator->prev->set));
    // last->prev->next = it->lst->terminator;

    // first->prev = last;
    // it->lst->terminator->next = last;

    // last->prev = it->lst->terminator;
    // last->next = first;
    
    // it->lst->first = last;
}
*/

void list_destroy(list *lst)
{
    node* cur = lst->first;
    node* nxt = NULL;
    for(int i = 0; i < lst->size; ++i)
    {
        nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    free(lst->terminator);
    lst->size = 0;
}

my_set* get_set_from_it(iter *it)
{
    return &(it->prev->next->set);
}