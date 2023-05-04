#include "set.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_in_set(int num, my_set *set)
{
    return ((set->s) & (1ull << num));
}

void print_set(my_set *set)
{
    int c = 0;
    unsigned long long cur_set = set->s;
    while(cur_set > 0)
    {
        if(cur_set & 1)
        {
            printf("%d ", c);
        }
        cur_set = cur_set >> 1;
        ++c;
    }
    printf("\n");
}

void add_digit_to_set(int digit, my_set *set)
{
    if(digit >= 0 && digit <= 63)
    {
        set->s = (1ull << digit) | (set->s);
        set->size++;
    }
    return;
}

bool set_parse(int num, my_set *result)
{
    result->s = 0;
    result->size = 0;
    int c = getchar();
    while(num != 0)
    {
        if(c >= '0' && c <= '9')
        {
            result->s = (1ull << (c - '0')) | (result->s);
            result->size++;
            num--;
            if(num == 0)
            {
                break;
            }
        }
        else if(c == EOF)
        {
            exit(1);
        }
        else if(c != ' ' && c != '\n')
        {
            return false;
        }
        c = getchar();
    }

    return true;
}