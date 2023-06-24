#include <stdio.h>
#include <stdbool.h>
#include "file_queue.h"


int main()
{

    dbl_queue q;
    dbl_queue_init(&q);

    while(true)
    {
        int c;
        scanf("%d", &c);
        if(c == 1)
        {
            double x;
            scanf("%lf", &x);
            dbl_queue_push(&q, x);
        }
        else if(c == 2)
        {
            printf("first: %lf\n", dbl_queue_first(&q));
            dbl_queue_pop(&q);
        }
        dbl_queue_print(&q);

    }

    return 0;
}