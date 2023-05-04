#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "tree_advanced.h"

#define color_size 10
#define colors_n 7
#define max_cmd_length 15
#define commands_num 5

// typedef enum colors
// {
//     None,
//     red,
//     green,
//     blue,
//     yellow,
//     purple,
//     orange,
//     white
// } colors;

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

/*
void color_degree_eq(tree *t, int *result)
{
    colors value = (*t)->color;
    printf("cmp color: %d degr: %d\n", value, count_degree(*t));
    if(count_degree(*t) == value)
    {
        (*result) += 1;
    } 
    return;
}
*/

// Определить число вершин дерева, степень которых совпадает со значением элемента
void my_task(tree t, int *result)
{
    if (t == NULL)
    {
        return;
    }
    int deg = count_degree(t->child);
    colors value = t->color;
    // printf("degree: %d, color: %d\n", deg, value);
    if(deg == value)
    {
        (*result) += 1;
    } 
    my_task(t->child, result);
    my_task(t->next_brother, result);
}



typedef enum command
{
    none,
    help,
    insert,
    print,
    delete,
    task // функция, вычисляющая ответ на задание в соответствии с вариантом
} commands;



commands cmd_parse()
{
    printf("Введите команду в соответствии с ее форматом(help - справка)\n");
    char cmd[max_cmd_length];
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
    char command[commands_num + 1][max_cmd_length] = {"None","help", "insert","print","delete","task"};
    commands result = 0;
    for(int i = 1; i <= commands_num; ++i)
    {
        if(strcmp(cmd, command[i]) == 0)
        {
            // printf("command: %d\n", i);
            result = i;
            break;
        }
    }
    return result;

}

colors color_parse()
{
    // printf("current color: %s\n", color);
    // scanf("%s", color);
    colors color = none;
    char clr[max_cmd_length];
    int i = 0;
    int c;
    while((c = getchar()) == ' ');
    clr[i] = c;
    while(clr[i] != '\n' && clr[i] != ' ')
    {
        if(clr[i] == EOF)
        {
            exit(1);
        }
        i++;
        clr[i] = getchar();
    }
    if(clr[i] == '\n')
    {
        ungetc(clr[i], stdin);
    }
    clr[i] = '\0';
    char clrs[colors_n + 1][color_size] = {"None", "red", "green", "blue", "yellow", "purple", "orange", "white"};
    for (int i = 1; i <= colors_n; ++i)
    {
        // printf("%s\n", clr);
        if (strcmp(clrs[i], clr) == 0) // Если нашли нужный цвет
        {
            color = i;
            break;
        }
    }
    return color;
}

int main()
{
    tree my_tree;
    create(&my_tree, red);
    FILE *Help;
    while (true)
    {
        commands cmd = cmd_parse();
        char path[15];
        switch (cmd)
        {
            case none:
                printf("Команда введена неправильно!\n");
                skip_rest_of_line();
                break;
            case help:
                if (!skip_rest_of_line())
                {
                    printf("Неправильный формат ввода команды: help\n");
                    break;
                }
                Help = fopen("help.txt", "r");
                char ch;
                while ((ch = fgetc(Help)) != EOF)
                {
                    putchar(ch);
                }
                fclose(Help);
                break;
            case insert:
                scanf("%s", path);
                // printf("PATH: %s\n", path);
                colors clr = color_parse();
                if (!skip_rest_of_line())
                {
                    printf("Неправильный формат ввода команды: insert\n");
                    break;
                }
                if (clr == None)
                {
                    printf("Цвет указан некорректно!\n");   
                    break;
                }
                if (!add(&my_tree, clr, path))
                {
                    printf("Указан неверный путь!\n");
                }
                break;
            case print:
                if (!skip_rest_of_line())
                {
                    printf("Неправильный формат ввода команды: print\n");
                    break;
                }
                print_tree_tab(my_tree);
                break;
            case delete:
                scanf("%s", path);
                if (!skip_rest_of_line())
                {
                    printf("Неправильный формат ввода команды: delete\n");
                    break;
                }
                colors col = node_pop(&my_tree, path);
                printf("Deleted color: %s\n", int2color(col));
                break;
            case task:
                if (!skip_rest_of_line())
                {
                    printf("Неправильный формат ввода команды: task\n");
                    break;
                }
                int res = 0;
                my_task(my_tree, &res);
                printf("RESULT: %d\n", res);
                break;
            default:
                break;
        }
    }

    return 0;
}