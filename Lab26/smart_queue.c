#include "smart_queue.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MIN_CAP 10

static void decrease_if_possible(dbl_queue *q)
{
    if(q->size >= (q->cap)/4) return;
    int new_cap = (q->cap)/2;
    if (new_cap < MIN_CAP)
    {
        new_cap = MIN_CAP;
    }
    if(new_cap < q->cap)
    {
        if(q->head > new_cap)
        {
            int dif = q->cap - new_cap;
            int old_cap = q->cap;
            for(int i=old_cap - 1; i >= (q->head); i--)
            {
                q->buff[i-dif] = q->buff[i];
                //printf("i-dif: %lf i: %lf ", q->buff[i-dif], q->buff[i]);
            } //printf("\n");
            q->head = q->head - dif;     
        }
        else if (q->head + q->size > new_cap)
        {
            int dif = new_cap - q->head;
            for(int i = q->head + dif; i < (q->head + q->size);i++)
            {
                q->buff[i-new_cap] = q->buff[i];
                //printf("i-dif: %lf i: %lf ", q->buff[i-new_cap], q->buff[i]);
            } //printf("\n");
        }
        q->buff = realloc(q->buff, new_cap * sizeof(double));
        q->cap = new_cap;
    }
}

bool dbl_queue_pop(dbl_queue *q, double *popped)
{
    if(q->size == 0) 
    {
        return false; //error
    }
    (q->size)--;
    double result = q->buff[q->head]; //
    q->head = (q->head + 1) % (q->cap);
    decrease_if_possible(q);
    *popped = result;
    return true;
}

void dbl_queue_init(dbl_queue *q)
{
    q->size = 0;
    q->cap = MIN_CAP;
    q->buff = malloc(MIN_CAP * (sizeof(double)));
    q->head = 0;
    for(int i = 0; i < MIN_CAP; ++i)
    {
        q->buff[i] = 0;
    }
}

void dbl_queue_destroy(dbl_queue *q)
{
    q->size = 0;
    free(q->buff);
    q->head = 0;
    q->buff = NULL;
}

static void move_vals(dbl_queue *q, int old_cap)
{
    //printf("I'm moving values to right\n");
    int new_cap = q->cap;
    int dif = new_cap - old_cap;
    for(int i = old_cap - 1; i >= q->head; i--)
    {
        q->buff[i + dif] = q->buff[i];
    }
    q->head = (dif + q->head);
}

static bool increase(dbl_queue *q)
{
    int new_cap = 2 * (q->cap);
    if(new_cap < MIN_CAP)
    {
        new_cap = MIN_CAP;
    }
    double *tmp = realloc(q->buff, new_cap * sizeof(double));
    if (tmp == NULL)
    {
        return false;
    }
    q->cap = new_cap;
    q->buff = tmp;
    return true;
}

bool dbl_queue_push(dbl_queue *q, double val)
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
    // printf("push' idx: %d\n", (q->head + q->size) % q->cap);
    // printf("%lf\n", v->buff[(v->head + v->size)%v->cap]);
    //printf("HEAD: %d\n", v->head);
    q->size++;
    return true;
}

bool dbl_queue_is_empty(dbl_queue *q)
{
    return q->size == 0;
}

int dbl_queue_get_size(dbl_queue *q)
{
    return q->size;
}

void dbl_queue_print(const dbl_queue *q)
{
    for(int i = (q->head); i < (q->head + q->size); ++i)
    {
        printf("%lf ", q->buff[i % (q->cap)]);
    } printf("\n");
}

// static int diV(int a, int b)
// {
// 	if(b > 0 && a < 0)
// 	{	
// 		if((-a) % b == 0) 
//         {
//             return a / b;
//         }
// 		return (a - b) / b;
// 	}
// 	else if(a < 0 && b < 0) 
// 	{
// 		if((-a) % (-b) == 0)
//         {
//             return (a / b);
//         } 
// 		return (a + b) / b;
// 	}
// 	else 
//         return a / b;
// }

// static int mod(int a, int b)
// {
// 	int d = diV(a, b);
// 	return a - b * d;
// }


