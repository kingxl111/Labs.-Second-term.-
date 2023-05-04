#pragma once
#include <stdbool.h>

typedef struct {
    int head;
    double *buff;
    int size;
    int cap;
} dbl_vec;


typedef struct {
    int head;
    int *buff;
    int size;
    int cap;
} int_vec;

void dbl_v_init(dbl_vec *v);
void dbl_v_destroy(dbl_vec *v);
bool dbl_v_push_back(dbl_vec *v, double val);
bool dbl_v_push_front(dbl_vec *v, double val);
bool dbl_v_pop_front(dbl_vec *v);
bool dbl_v_pop_back(dbl_vec *v);
bool dbl_v_is_empty(dbl_vec *v);
int dbl_v_get_size(dbl_vec *v);
bool dbl_v_set_size(dbl_vec *v, int new_size);
double dbl_v_get_at(dbl_vec *v, int idx);
void dbl_v_set_at(dbl_vec *v, int idx, double val);
void dbl_v_show_vector(dbl_vec *v);


void int_v_init(int_vec *v);
void int_v_destroy(int_vec *v);
bool int_v_push_back(int_vec *v, int val);
bool int_v_push_front(int_vec *v, int val);
bool int_v_pop_front(int_vec *v);
bool int_v_pop_back(int_vec *v);
bool int_v_is_empty(int_vec *v);
int int_v_get_size(int_vec *v);
bool int_v_set_size(int_vec *v, int new_size);
int int_v_get_at(int_vec *v, int idx);
void int_v_set_at(int_vec *v, int idx, int val);
void int_v_show_vector(int_vec *v);

