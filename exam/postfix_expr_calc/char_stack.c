
#include "char_stack.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h> 

#define MIN_CAP 10

// static int diV(int a, int b)
// {
// 	if(b>0 && a<0)
// 	{	
// 		if((-a) % b == 0) return a / b;
// 		return (a - b) / b;
// 	}
// 	else if(a < 0 && b < 0) 
// 	{
// 		if((-a)%(-b)==0) return (a/b);
// 		return (a+b)/b;
// 	}
// 	else return a / b;
// }

// static int mod(int a, int b)
// {
// 	int d = diV(a, b);
// 	return a - b*d;
// }


static void decrease_if_possible(char_stack *v)
{
    if(v->size >= (v->cap)/4) return;
    int new_cap = (v->cap)/2;
    if (new_cap < MIN_CAP)
    {
        new_cap = MIN_CAP;
    }
    if(new_cap < v->cap)
    {
        if(v->head > new_cap)
        {
            int dif = v->cap - new_cap;
            int old_cap = v->cap;
            for(int i=old_cap - 1; i >= (v->head); i--)
            {
                v->buff[i-dif] = v->buff[i];
                //printf("i-dif: %lf i: %lf ", v->buff[i-dif], v->buff[i]);
            } //printf("\n");
            v->head = v->head - dif;     
        }
        else if (v->head + v->size > new_cap)
        {
            int dif = new_cap - v->head;
            for(int i=v->head + dif; i < (v->head + v->size);i++)
            {
                v->buff[i-new_cap] = v->buff[i];
                //printf("i-dif: %lf i: %lf ", v->buff[i-new_cap], v->buff[i]);
            } //printf("\n");
        }
        v->buff = realloc(v->buff, new_cap*sizeof(char));
        v->cap = new_cap;
    }
}

bool char_stack_pop(char_stack *v)
{
    if(v->size == 0) return false;
    // int tail = (v->head + v->size) % (v->cap) - 1;
    v->size--;
    // decrease_if_possible(v);
    return true;
}


void char_stack_init(char_stack *v)
{
    v->size = 0;
    v->buff = malloc(MIN_CAP * (sizeof(char)));
    v->head = 0;
    v->cap = MIN_CAP;
    // for(int i = 0; i < MIN_CAP; ++i)
    // {
    //     v->buff[i] = '0';
    // }
} 
void char_stack_destroy(char_stack *v)
{
    v->size = 0;
    free(v->buff);
    v->buff = NULL;
}

static void move_vals(char_stack *v, int old_cap)
{
    //printf("I'm moving values to right\n");
    int new_cap = v->cap;
    int dif = new_cap - old_cap;
    for(int i=old_cap - 1; i >= v->head;i--)
    {
        v->buff[i+dif] = v->buff[i];
    }
    v->head = (dif + v->head);
}

static bool increase(char_stack *v)
{
    int new_cap = 2*(v->cap);
    if(new_cap < MIN_CAP)
    {
        new_cap = MIN_CAP;
    }
    char* tmp = realloc(v->buff, new_cap*sizeof(char));
    if (tmp == NULL)
    {
        return false;
    }
    v->cap = new_cap;
    v->buff = tmp;
    return true;
}

bool char_stack_push(char_stack *v, char val)
{
    if(v->cap == v->size)
    {
        int old_cap = v->cap;
        if(!increase(v))
        {
            return false;
        }
        // printf("head+size: %d\n", v->head + v->size);
        if((v->head + v->size ) >= old_cap)
        {
            move_vals(v, old_cap);
        }
    }
    v->buff[(v->head + v->size) % v->cap] = val;
    // printf("val: %c\n", v->buff[(v->head + v->size)%v->cap]);
    //printf("HEAD: %d\n", v->head);
    v->size++;
    return true;
}

bool char_stack_is_empty(char_stack *v)
{
    return v->size == 0;
}

int char_stack_get_size(char_stack *v)
{
    return v->size;
}

char char_stack_top(char_stack *s)
{
    if(s->size < 1)
    {
        return -1;
    }
    char top;
    // printf("s->head + s->size = %d\n", s->head + s->size);
    top = s->buff[(s->head + s->size - 1) % s->cap];
    return top;
}