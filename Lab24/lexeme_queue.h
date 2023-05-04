#pragma once 
#include <stdbool.h>
#include "expression.h"

typedef struct {
    int head;
    lexeme *buff;
    int size;
    int cap;
} lex_queue;


void lex_queue_init(lex_queue *q);
void lex_queue_destroy(lex_queue *q);
bool lex_queue_push(lex_queue *q, lexeme lex);
bool lex_queue_pop(lex_queue *q, lexeme *popped);
bool lex_queue_is_empty(lex_queue *q);
int lex_queue_get_size(lex_queue *q);
void lex_queue_print(lex_queue *q);
