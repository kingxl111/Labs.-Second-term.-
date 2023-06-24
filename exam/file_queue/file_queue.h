#include <stdio.h>
#include <stdbool.h>
#pragma once

typedef struct
{
    int size;
    int head;
    int capacity;
    FILE* buf;

} dbl_queue;

void dbl_queue_init(dbl_queue *q);
int dbl_queue_size(dbl_queue *q);
bool dbl_queue_empty(dbl_queue *q);
void dbl_queue_push(dbl_queue *q, double x);
void dbl_queue_pop(dbl_queue *q);
double dbl_queue_first(dbl_queue *q);
void dbl_queue_destroy(dbl_queue *q);
void dbl_queue_print(dbl_queue *q);
