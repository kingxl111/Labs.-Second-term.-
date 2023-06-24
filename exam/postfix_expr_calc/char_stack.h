#pragma once
#include <stdbool.h>

typedef struct {
    int head;
    char *buff;
    int size;
    int cap;
} char_stack; 

void char_stack_init(char_stack *s);
void char_stack_destroy(char_stack *s);
bool char_stack_push(char_stack *s, char val);
bool char_stack_pop(char_stack *s);
bool char_stack_is_empty(char_stack *s);
int char_stack_get_size(char_stack *s);
char char_stack_top(char_stack *s);

