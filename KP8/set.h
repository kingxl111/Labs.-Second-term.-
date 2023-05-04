#pragma once
#include <stdbool.h>

typedef struct 
{
    unsigned long long s;
    int size;
} my_set;

bool is_in_set(int n, my_set *set);
void add_digit_to_set(int digit, my_set *set);
void print_set(my_set *set);
bool set_parse(int num, my_set *result);
