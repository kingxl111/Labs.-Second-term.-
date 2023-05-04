#include <stdio.h>
#include <stdbool.h>
#include "smart_queue.h"

//Тип данных: очередь 
//Процедура: слияние двух очередей, упорядоченных по возрастанию, с сохранением порядка
//Метод: merge sort

void merge_sort(dbl_queue *q);
dbl_queue merge(dbl_queue *q1, dbl_queue *q2);

int main()
{

    int n;
    printf("Введите длину очереди: ");
    scanf("%d", &n);

    printf("Введите очередь(вещественные числа через пробел): ");
    
    dbl_queue q;
    dbl_queue_init(&q);

    for(int i = 0; i < n; ++i)
    {
        double tmp;
        scanf("%lf", &tmp);
        dbl_queue_push(&q, tmp);
    }

    merge_sort(&q);

    printf("Отсортированная очередь: ");
    dbl_queue_print(&q);
    

    return 0;
}

void merge_sort(dbl_queue *q)
{
    int q_size = dbl_queue_get_size(q);
    if(q_size <= 1)
    {
        return;
    }
    dbl_queue queue_half;
    dbl_queue_init(&queue_half);

    int middle = q_size / 2;
    for(int i = 0; i < middle; ++i)
    {
        double tmp;
        dbl_queue_pop(q, &tmp);
        dbl_queue_push(&queue_half, tmp);
    }

    merge_sort(&queue_half);
    merge_sort(q);

    *q = merge(&queue_half, q);

    return;
}

dbl_queue merge(dbl_queue *q1, dbl_queue *q2)
{
    dbl_queue result;
    dbl_queue_init(&result);

    int n1 = dbl_queue_get_size(q1);
    int n2 = dbl_queue_get_size(q2);
    int i = 0, j = 0;

    double popped1, popped2;
    dbl_queue_pop(q1, &popped1);
    dbl_queue_pop(q2, &popped2);
    while(i < n1 && j < n2)
    {
        if(popped1 <= popped2)
        {
            i++;
            dbl_queue_push(&result, popped1);
            if(!dbl_queue_pop(q1, &popped1))
            {
                break;
            }
        }
        else if(popped2 < popped1)
        {
            j++;
            dbl_queue_push(&result, popped2);
            if(!dbl_queue_pop(q2, &popped2))
            {
                break;
            }
        }
    }
    while(i < n1)
    {
        dbl_queue_push(&result, popped1);
        i++;
        if(!dbl_queue_pop(q1, &popped1))
        {
            break;
        }
    }
    while(j < n2)
    {
        dbl_queue_push(&result, popped2);
        j++;
        if(!dbl_queue_pop(q2, &popped2))
        {
            break;
        }
    }
    return result;
}