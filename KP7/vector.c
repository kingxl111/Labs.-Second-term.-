
#include "vector.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MIN_CAP 10

static int diV(int a, int b)
{
	if(b>0 && a<0)
	{	
		if((-a) % b == 0) return a / b;
		return (a - b) / b;
	}
	else if(a < 0 && b < 0) 
	{
		if((-a)%(-b)==0) return (a/b);
		return (a+b)/b;
	}
	else return a / b;
}

static int mod(int a, int b)
{
	int d = diV(a, b);
	return a - b*d;
}


static void decrease_if_possible(dbl_vec *v)
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
            for(int i=old_cap - 1; i >= (v->head);i--)
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
        v->buff = realloc(v->buff, new_cap*sizeof(double));
        v->cap = new_cap;
    }
}

bool dbl_v_pop_front(dbl_vec *v)
{
    if(v->size == 0) return false;
    (v->size)--;
    v->head = (v->head + 1)%(v->cap);
    decrease_if_possible(v);
    return true;
}

bool dbl_v_pop_back(dbl_vec *v)
{
    if(v->size == 0) return false;
    // int tail = (v->head + v->size) % (v->cap) - 1;
    v->size--;
    decrease_if_possible(v);
    return true;
}


void dbl_v_init(dbl_vec *v)
{
    v->size = 0;
    v->buff = malloc(MIN_CAP*(sizeof(double)));
    v->head = 0;
    for(int i = 0;i<MIN_CAP;++i)
    {
        v->buff[i] = 0;
    }
}

void dbl_v_destroy(dbl_vec *v)
{
    v->size = 0;
    free(v->buff);
    v->buff = NULL;
}

static void move_vals(dbl_vec *v, int old_cap)
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

static bool increase(dbl_vec *v)
{
    int new_cap = 2*(v->cap);
    if(new_cap < MIN_CAP)
    {
        new_cap = MIN_CAP;
    }
    double* tmp = realloc(v->buff, new_cap*sizeof(double));
    if (tmp == NULL)
    {
        return false;
    }
    v->cap = new_cap;
    v->buff = tmp;
    return true;
}

bool dbl_v_push_back(dbl_vec *v, double val)
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
    v->buff[(v->head + v->size)%v->cap] = val;
    // printf("%lf\n", v->buff[(v->head + v->size)%v->cap]);
    //printf("HEAD: %d\n", v->head);
    v->size++;
    return true;
}

bool dbl_v_push_front(dbl_vec *v, double val)
{
    if(v->cap == v->size)
    {
        int old_cap = v->cap;
        if(!increase(v))
        {
            return false;
        }
        if((v->head + v->size ) >= old_cap)
        {
            move_vals(v, old_cap);
        }
    }
    v->head = mod(v->head - 1, v->cap); //Берем математически корректный остаток от деления 
    v->size++;
    v->buff[v->head] = val;
    return true;
}

bool dbl_v_is_empty(dbl_vec *v)
{
    return v->size == 0;
}

int dbl_v_get_size(dbl_vec *v)
{
    return v->size;
}

void dbl_v_set_at(dbl_vec *v, int idx, double val)
{
    v->buff[(idx+(v->head)) % (v->cap)] = val;
}


double dbl_v_get_at(dbl_vec *v, int idx)
{
    return v->buff[(idx+v->head)%(v->cap)];
}

void zero_range(dbl_vec *v, int f, int t)
{
    for(int i=f;i<t;++i)
    {
        dbl_v_set_at(v,i,0);
    }
}

bool dbl_v_set_size(dbl_vec *v, int new_size)
{
    if(new_size <= v->size)
    {
        v->size = new_size;
        decrease_if_possible(v);
        // zero_range(v, (v->head + v->size) % (v->cap), );
        return true;
    }
    if(new_size == v->size + 1)
    {
        if(!increase(v)) return false;
        v->size = new_size;
        return true;
    }
    int new_cap = new_size;
    double *tmp = realloc(v->buff, new_cap*sizeof(double));
    if(tmp == NULL)
    {
        return false;
    }
    move_vals(v, new_cap);
    return true;
}

void dbl_v_show_vector(dbl_vec *v)
{
    for(int i=(v->head);i<(v->head + v->size);++i)
    {
        printf("%.1lf ", v->buff[i%(v->cap)]);
    } printf("\n");
}


// Для отладки 
// void show_all(dbl_vec *v)
// {
//     printf("HEAD: %d\n", v->head);
//     for(int i=0;i<(v->cap);++i)
//     {
//         printf("%lf ", v->buff[i]);
//     } printf("\n");
// }


// INT VECTOR /////////////////////////////////////////////////////////////////////////////////////

static void move_vals_int(int_vec *v, int old_cap)
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


static void decrease_if_possible_int(int_vec *v)
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
            for(int i=old_cap - 1; i >= (v->head);i--)
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
        v->buff = realloc(v->buff, new_cap*sizeof(int));
        v->cap = new_cap;
    }
}

bool int_v_pop_front(int_vec *v)
{
    if(v->size == 0) return false;
    (v->size)--;
    v->head = (v->head + 1)%(v->cap);
    decrease_if_possible_int(v);
    return true;
}

bool int_v_pop_back(int_vec *v)
{
    if(v->size == 0) return false;
    // int tail = (v->head + v->size) % (v->cap) - 1;
    v->size--;
    decrease_if_possible_int(v);
    return true;
}


void int_v_init(int_vec *v)
{
    v->size = 0;
    v->buff = malloc(MIN_CAP*(sizeof(int)));
    v->head = 0;
    for(int i = 0;i<MIN_CAP;++i)
    {
        v->buff[i] = 0;
    }
}

void int_v_destroy(int_vec *v)
{
    v->size = 0;
    free(v->buff);
    v->buff = NULL;
}

static bool increase_int(int_vec *v)
{
    int new_cap = 2*(v->cap);
    if(new_cap < MIN_CAP)
    {
        new_cap = MIN_CAP;
    }
    int* tmp = realloc(v->buff, new_cap*sizeof(int));
    if (tmp == NULL)
    {
        return false;
    }
    v->cap = new_cap;
    v->buff = tmp;
    return true;
}

bool int_v_push_back(int_vec *v, int val)
{
    if(v->cap == v->size)
    {
        int old_cap = v->cap;
        if(!increase_int(v))
        {
            return false;
        }
        // printf("head+size: %d\n", v->head + v->size);
        if((v->head + v->size ) >= old_cap)
        {
            move_vals_int(v, old_cap);
        }
    }
    v->buff[(v->head + v->size)%v->cap] = val;
    // printf("%lf\n", v->buff[(v->head + v->size)%v->cap]);
    //printf("HEAD: %d\n", v->head);
    v->size++;
    return true;
}

bool int_v_push_front(int_vec *v, int val)
{
    if(v->cap == v->size)
    {
        int old_cap = v->cap;
        if(!increase_int(v))
        {
            return false;
        }
        if((v->head + v->size ) >= old_cap)
        {
            move_vals_int(v, old_cap);
        }
    }
    v->head = mod(v->head - 1, v->cap); //Берем математически корректный остаток от деления 
    v->size++;
    v->buff[v->head] = val;
    return true;
}

bool int_v_is_empty(int_vec *v)
{
    return v->size == 0;
}

int int_v_get_size(int_vec *v)
{
    return v->size;
}

void int_v_set_at(int_vec *v, int idx, int val)
{
    v->buff[(idx+(v->head)) % (v->cap)] = val;
}


int int_v_get_at(int_vec *v, int idx)
{
    return v->buff[(idx+v->head)%(v->cap)];
}

// void zero_range(int_vec *v, int f, int t)
// {
//     for(int i=f;i<t;++i)
//     {
//         int_v_set_at(v,i,0);
//     }
// }

bool int_v_set_size(int_vec *v, int new_size)
{
    if(new_size <= v->size)
    {
        v->size = new_size;
        decrease_if_possible_int(v);
        // zero_range(v, (v->head + v->size) % (v->cap), );
        return true;
    }
    if(new_size == v->size + 1)
    {
        if(!increase_int(v)) return false;
        v->size = new_size;
        return true;
    }
    int new_cap = new_size;
    int *tmp = realloc(v->buff, new_cap*sizeof(int));
    if(tmp == NULL)
    {
        return false;
    }
    move_vals_int(v, new_cap);
    return true;
}

void int_v_show_vector(int_vec *v)
{
    for(int i=(v->head);i<(v->head + v->size);++i)
    {
        printf("%d ", v->buff[i%(v->cap)]);
    } printf("\n");
}
