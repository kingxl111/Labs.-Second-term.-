#include <stdio.h>
#include <stdbool.h>
#include "file_queue.h"

#define QUEUE_CAP 50

void dbl_queue_init(dbl_queue *q)
{
    q->buf = fopen("buffer_for_queue", "wb");
    q->size = 0;
    q->capacity = QUEUE_CAP;
    q->head = 0;
    fclose(q->buf);
}

int dbl_queue_size(dbl_queue *q)
{
    return q->size;
}

bool dbl_queue_empty(dbl_queue *q)
{
    return q->size == 0;
}

void dbl_queue_push(dbl_queue *q, double x)
{
    q->buf = fopen("buffer_for_queue", "rb");
    FILE* tmp = fopen("tmp", "wb");
    for(int i = 0; i < q->size; ++i)
    {
        double t;
        fseek(q->buf, ((q->head + i) % q->capacity) * sizeof(double), SEEK_SET);
        fread(&t, sizeof(double), 1, q->buf);
        fwrite(&t, sizeof(double), 1, tmp);
    }
    fclose(q->buf);
    q->head = 0;
    int tail = ((q->head + q->size) % q->capacity) * sizeof(double);
    fseek(tmp, tail, SEEK_SET);
    fwrite(&x, sizeof(double), 1, tmp);
    q->size++;

    fclose(tmp);

    tmp = fopen("tmp", "rb");
    q->buf = fopen("buffer_for_queue", "wb");
    for(int i = 0; i < q->size; ++i)
    {
        double t;
        fread(&t, sizeof(double), 1, tmp);
        // printf("t: %lf\n", t);
        fwrite(&t, sizeof(double), 1, q->buf);
    }
    fclose(q->buf);
    fclose(tmp);
}

void dbl_queue_pop(dbl_queue *q)
{
    if(q->size < 1)
    {
        return;
    }
    q->head = (q->head + 1) % q->capacity;
}

double dbl_queue_first(dbl_queue *q)
{
    if(q->size < 1)
    {
        return -1;
    }
    q->buf = fopen("buffer_for_queue", "rb");
    fseek(q->buf, q->head * sizeof(double), SEEK_SET);
    double x;
    fread(&x, sizeof(double), 1, q->buf);
    q->size--;
    fclose(q->buf);
    return x;
}
void dbl_queue_destroy(dbl_queue *q)
{
    
}

void dbl_queue_print(dbl_queue *q)
{
    q->buf = fopen("buffer_for_queue", "rb");
    for(int i = 0; i < q->size; ++i)
    {
        fseek(q->buf, ((q->head + i) % q->capacity) * sizeof(double), SEEK_SET);
        double x;
        fread(&x, sizeof(double), 1, q->buf);
        printf("%lf ", x);
    } printf("\n");
    fclose(q->buf);
}