#include "lexeme_queue.h"
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

void lex_queue_init(lex_queue *q)
{
    q->size = 0;
    q->buff = malloc(MIN_CAP * (sizeof(lexeme)));
    q->head = 0;
    q->cap = MIN_CAP;
    // for(int i = 0;i<MIN_CAP;++i)
    // {
    //     q->buff[i] = 0;
    // }
}


bool lex_queue_pop(lex_queue *q, lexeme *popped)
{
    if(lex_queue_is_empty(q))
    {
        return false;
    }
    lexeme lex = q->buff[q->head];
    (q->size)--;
    q->head = (q->head + 1) % q->cap;
    *popped = lex;
    return true;
}


void lex_queue_destroy(lex_queue *q)
{
    q->size = 0;
    free(q->buff);
    q->buff = NULL;
}

static void move_vals(lex_queue *q, int old_cap)
{
    //printf("I'm moving values to right\n");
    int new_cap = q->cap;
    int dif = new_cap - old_cap;
    for(int i=old_cap - 1; i >= q->head;i--)
    {
        q->buff[i+dif] = q->buff[i];
    }
    q->head = (dif + q->head);
}

static bool increase(lex_queue *q)
{
    int new_cap = 2 * (q->cap);
    if(new_cap < MIN_CAP)
    {
        new_cap = MIN_CAP;
    }
    lexeme* tmp = realloc(q->buff, new_cap*sizeof(lexeme));
    if (tmp == NULL)
    {
        return false;
    }
    q->cap = new_cap;
    q->buff = tmp;
    return true;
}

bool lex_queue_push(lex_queue *q, lexeme val)
{
    if(q->cap == q->size)
    {
        int old_cap = q->cap;
        if(!increase(q))
        {
            return false;
        }
        // printf("head+size: %d\n", v->head + v->size);
        if((q->head + q->size ) > old_cap)
        {
            move_vals(q, old_cap);
        }
    }
    q->buff[(q->head + q->size) % q->cap] = val;
    // printf("%lf\n", v->buff[(v->head + v->size)%v->cap]);
    //printf("HEAD: %d\n", v->head);
    q->size++;
    return true;
}

bool lex_queue_is_empty(lex_queue *q)
{
    return q->size == 0;
}

int lex_queue_get_size(lex_queue *q)
{
    return q->size;
}

void lex_queue_print(lex_queue *q)
{
    for(int i = q->head; i < (q->head + q->size); ++i)
    {
        if(q->buff[i].type == LEX_CONST)
        {
            printf("%lf\n", q->buff[i%(q->cap)].cnst);
        }
        else if(q->buff[i].type == LEX_VAR_NAME)
        {
            printf("%s\n", q->buff[i%(q->cap)].var_name);
        }
        else if(q->buff[i].type == LEX_BR_L)
        {
            printf("(\n");
        }
        else if(q->buff[i].type == LEX_BR_R)
        {
            printf(")\n");
        }
        else if(q->buff[i].type == LEX_OPER)
        {
            printf("%c\n", q->buff[i%(q->cap)].oper);
        }
    }
}
