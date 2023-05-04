#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"
#include "circular_bidirectional_list.h"

#define max_cmd_length 15

enum commands 
{
    None,
    printlist,
    insert,
    addtoset,
    sizeoflist,
    delete,
    cyclicshift,
    help,
    destroy
};

//ТИП ЭЛЕМЕНТА СПИСКА: множество
//ВИД СПИСКА: кольцевой двунаправленный

//  Пусть у нас будет список, элементами которого являются множества цифр,
// которые будут представлены в виде беззнакового целого числа

//Нестандартное действие - циклический сдвиг элментов на один вперед

int get_command();

bool skip_rest_of_line() //Данную функцию будем запускать после считывания команды и всех ее аргументов
{
    int c;
    bool is_right = true;
    while((c = getchar()) != '\n')
    {
        if(c == EOF)
        {
            exit(1);
        }
        if((c != ' ') && (c != '\0'))
        {
            is_right = false;
        }
    } 
    return is_right;
}


void list_cyclic_shift_right(list *lst)
{
    if(lst->size <= 1)
    {
        return;
    }
    
    // lst->first = &new_first;
    node *last = lst->terminator->prev;
    node *first = lst->first;

    last->next = first;
    lst->terminator->next = last;
    last->prev->next = lst->terminator;
    lst->terminator->prev = last->prev;
    lst->terminator->next->prev = lst->terminator;
    last->next->prev = lst->terminator->next;

    lst->first = last;
}


int main()
{
    list lst;
    list_init(&lst);
    // printf("command: %d, %d\n", get_command(), sizeoflist);
    // char for_help[] = "printlist\ninsert\naddtoset\nsizeoflist\npop\ncyclicshift\nhelp\n";
    FILE *HELP;
    int ch;
    while(true)
    {
        int digit, num;//num - число считанных цифр в будущем множестве
        int pos;
        iter it;
        my_set cur_set;
        switch (get_command())
        {
            case printlist:
                if(!skip_rest_of_line())
                {
                    printf("Неправильный формат ввода команды: printlist\n");
                    break;
                }
                for(it = iter_begin(&lst); !iter_eq(it, iter_end(&lst)); iter_inc(&it))
                {
                    iter_getval(&it);
                } // printf("\n");
                break;
            case insert:
                scanf("%d%d", &pos, &num);
                if((pos - 1 < 0) || (pos - 1 > lst.size))
                {
                    printf("Указана некорректная позиция для вставки!\n");
                    skip_rest_of_line();
                    break;
                }
                if(!set_parse(num, &cur_set))
                {
                    printf("Множество введено некорректно!\n");
                    skip_rest_of_line();
                    break;
                }
                if(!skip_rest_of_line())
                {   
                    printf("Неправильный формат ввода команды: insert\n");
                    break;
                }
                it = iter_begin(&lst);
                for(int i = 0;i < pos - 1; ++i)
                {
                    iter_inc(&it);
                }
                iter_add(&it, cur_set);
                // printf("Ok!\n");
                break;
            case addtoset:
                scanf("%d%d", &pos, &digit);
                if(!skip_rest_of_line())
                {   
                    printf("Неправильный формат ввода команды: addtoset\n");
                    break;
                }
                if((pos - 1 < 0) || (pos - 1 > lst.size))
                {
                    printf("Указана некорректная позиция для вставки\n");
                    break;
                }
                it = iter_begin(&lst);
                for(int i = 0; i < pos-1; ++i)
                {
                    iter_inc(&it);
                }
                // my_set* set = get_set_from_it(&it);
                add_digit_to_set(digit, &(it.prev->next->set));
                break;
            case sizeoflist:
                if(!skip_rest_of_line())
                {
                    printf("Неправильный формат ввода команды: sizeoflist\n");
                    break;
                }
                printf("List size: %d\n", lst.size);
                break;
            case delete:
                scanf("%d", &pos);
                if(!skip_rest_of_line())
                {   
                    printf("Неправильный формат ввода команды: delete\n");
                    break;
                }
                if((pos - 1 > lst.size) || (pos - 1 < 0))
                {
                    printf("Указана некорректная позиция для удаления\n");
                    break;
                }
                it = iter_begin(&lst);
                for(int i = 0; i < pos - 1; ++i)
                {
                    iter_inc(&it);
                }
                iter_remove(&it);
                break;
            case cyclicshift:
                if(!skip_rest_of_line())
                {
                    printf("Неправильный формат ввода команды: cyclicshift\n");
                    break;
                }
                list_cyclic_shift_right(&lst);
                break;
            case help:
                if(!skip_rest_of_line())
                {
                    printf("Неправильный формат ввода команды: help\n");
                    break;
                }
                HELP = fopen("help.txt", "r");
                while((ch = fgetc(HELP)) != EOF)
                {
                    putchar(ch);
                }
                fclose(HELP);
                break;
            case destroy:
                if(!skip_rest_of_line())
                {
                    printf("Неправильный формат ввода команды: destroy\n");
                    break;
                }
                list_destroy(&lst);
                printf("Завершение работы программы\n");
                exit(1);
            default:
                printf("Команда введена неправильно!\n");
                while((ch = getchar()) != '\n')
                {
                    if(ch == EOF)
                    {
                        exit(1);
                    }
                }
                break;
        }
        printf("---------------------------------------------------------------------------------\n");
    }                                                                                  
    return 0;
}

int get_command()
{
    char cmd[max_cmd_length];
    printf("Введите команду(для справки используйте help): \n");
    int i = 0;
    cmd[i] = getchar();
    while(cmd[i] != '\n' && cmd[i] != ' ')
    {
        if(cmd[i] == EOF)
        {
            exit(1);
        }
        i++;
        cmd[i] = getchar();
    }
    if(cmd[i] == '\n')
    {
        ungetc(cmd[i], stdin);
    }
    cmd[i] = '\0';
    char command[9][max_cmd_length] = {"None","printlist", "insert","addtoset","sizeoflist","delete","cyclicshift","help","destroy"};
    int result = 0;
    for(int i = 1; i < 9; ++i)
    {
        if(strcmp(cmd, command[i])==0)
        {
            // printf("command: %d\n", i);
            result = i;
            break;
        }
    }
    return result;
}

