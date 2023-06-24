#include <stdio.h>
#include "char_stack.h"

#define MAX_LEN 100

int main()
{
    //Задача: вычислить значение выражения по его постифксной записи

    //Решение: пусть каждый знак входной строки представляет собой лексему
    // Будем использовать десятичные цифры в качестве констант
    // а также операции + - / *
    //Проблема: данная штука работает только для случаев, в которых промежуточные значения выражения
    // не превышает 10 

    char_stack stack;
    char_stack_init(&stack);

    char s[MAX_LEN];
    scanf("%s", s);
    printf("%s\n", s);

    int len = 0;
    while(s[len] != '\0')
    {
        len++;
    }
    // printf("len: %d\n", len);
    int i = 0;
    while(i < len)
    {
        if(s[i] >= '0' && s[i] <= '9')
        {
            char cur = s[i];
            char_stack_push(&stack, cur);
            
        }
        else if(s[i] == '+')
        {
            // printf("%c\n", char_stack_top(&stack));
            int b = char_stack_top(&stack) - '0';
            char_stack_pop(&stack);
            int a = char_stack_top(&stack) - '0';
            char_stack_pop(&stack);
            int result = a + b;
            char_stack_push(&stack, (char)(result + '0')); 
            
        }
        else if(s[i] == '-')
        {
            int b = char_stack_top(&stack) - '0';
            char_stack_pop(&stack);
            int a = char_stack_top(&stack) - '0';
            char_stack_pop(&stack);
            int result = a - b;
            char_stack_push(&stack, (char)(result + '0')); 
        }
        else if(s[i] == '/')
        {
            int b = char_stack_top(&stack) - '0';
            char_stack_pop(&stack);
            int a = char_stack_top(&stack) - '0';
            char_stack_pop(&stack);
            int result = a / b;
            char_stack_push(&stack, (char)(result + '0')); 
            
        }
        else if(s[i] == '*')
        {
            int b = char_stack_top(&stack) - '0';
            char_stack_pop(&stack);
            int a = char_stack_top(&stack) - '0';
            char_stack_pop(&stack);
            int result = a * b;
            char_stack_push(&stack, (char)(result + '0')); 
            
        }
        else 
        {
            printf("В выражении допущена ошибка!\n");
            return 0;
        }
        i++;
    }
    int answer = char_stack_top(&stack) - '0';
    char_stack_pop(&stack);
    char_stack_destroy(&stack);

    printf("result: %d\n", answer);


    return 0;
}