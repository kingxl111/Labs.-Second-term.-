#pragma once
#include <stdbool.h>

typedef struct {
    int head;
    double *buff;
    int size;
    int cap;
} dbl_queue;


void dbl_queue_init(dbl_queue *q);
void dbl_queue_destroy(dbl_queue *q);
bool dbl_queue_push(dbl_queue *q, double val);
bool dbl_queue_pop(dbl_queue *q, double *popped);
bool dbl_queue_is_empty(dbl_queue *q);
int dbl_queue_get_size(dbl_queue *q);
void dbl_queue_print(const dbl_queue *q);
