#include <stdio.h>
#include <stdbool.h>
#include "expression.h"
#include "lexeme_queue.h"
#include "lexeme_stack.h"
#include "lexeme_tree.h"
#include "stack_of_lexeme_trees.h"

LEX_READ_RESULT read_lex(LEXTYPE prev_type, lexeme *out);
EXPR_READ_RESULT read_expr(lex_queue *out);
// lex_queue postfix_to_infix(lex_queue *in);
bool Dijkstra_sort_station(lex_queue *in, lex_queue *out);
lex_tree postfix_to_tree(lex_queue *q);
void from_bin_to_n_tree(lex_tree tree);


int main()
{
    lex_queue in;
    lex_queue_init(&in);
    read_expr(&in);

    lex_queue output;
    lex_queue_init(&output);
    // lex_queue_print(&in);
    
    // printf("-----------------------------\n");
    // lex_queue_print(&in);
    // printf("-----------------------------\n");

    if(Dijkstra_sort_station(&in, &output))
    {
        printf("ВЫРАЖЕНИЕ СОСТАВЛЕНО ВЕРНО!\n");
        // lex_queue_print(&output);
        lex_tree expr_tree = postfix_to_tree(&output);
        lex_tree_print(expr_tree, 1);
        from_bin_to_n_tree(expr_tree); // 
    }
    else 
    {
        printf("ОШИБКА В ВЫРАЖЕНИИ!\n");
    }
    // printf("Size: %d\n", lex_queue_get_size(&exp));

    return 0;
}

bool is_operator(char letter)
{
    return (letter == '*' || letter == '/' || letter == '+' || letter == '-' || letter == '~' || letter == '^');
}

LEX_READ_RESULT read_lex(LEXTYPE prev_type, lexeme *out)
{
    int letter;
    while ((letter = getchar()) == ' ')
    {
    }
    if (letter >= '0' && letter <= '9')
    {
        ungetc(letter, stdin);
        double num;
        scanf("%lf", &num);
        out->type = LEX_CONST;
        out->cnst = num;
        return LEX_READ_OK;
    }
    else if (letter == '(')
    {
        out->type = LEX_BR_L;
        out->oper_assoc = right;
        out->oper_priority = high;
        return LEX_READ_OK;
    }
    else if (letter == ')')
    {   
        out->type = LEX_BR_R;
        out->oper_assoc = right;
        out->oper_priority = high;
        return LEX_READ_OK;
    }
    else if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') || letter == '_')
    {
        ungetc(letter, stdin);
        scanf("%[A-Za-z0-9_]", out->var_name);
        out->type = LEX_VAR_NAME;
        return LEX_READ_OK;
    }
    else if(is_operator(letter))
    {
        if(letter == '-')
        {
            if(prev_type == LEX_NONE || prev_type == LEX_BR_L || prev_type == LEX_OPER)
            {
                out->oper = '~';
                out->oper_priority = high;
                out->oper_assoc = right;
            }
            else
            {
                out->oper = '-';
                out->oper_priority = low;
                out->oper_assoc = left;
            }
        }
        else
        {
            out->oper = letter;
            if(letter == '-' || letter == '+')
            {
                out->oper_priority = low;
                out->oper_assoc = left;
            }
            else if(letter == '*' || letter == '/')
            {
                out->oper_priority = middle;
                out->oper_assoc = left;
            }
            else if(letter == '^') 
            {
                out->oper_priority = high;
                out->oper_assoc = right;
            }
        }
        out->type = LEX_OPER;
        return LEX_READ_OK;
    }
    else if(letter == '\n' || letter == EOF)
    {
        out->type = LEX_NONE;
        return LEX_READ_END;
    }
    else
    {
        out->type = LEX_NONE;
        return LEX_READ_ERROR;
    }
}

EXPR_READ_RESULT read_expr(lex_queue *out)
{
    lexeme cur_lex;
    LEXTYPE prev_lex_type = LEX_NONE;
    LEX_READ_RESULT read_res;
    while ((read_res = read_lex(prev_lex_type, &cur_lex)) == LEX_READ_OK)
    {
        lex_queue_push(out, cur_lex);
        prev_lex_type = cur_lex.type;
    }
    if (read_res == LEX_READ_ERROR)
    {
        return EXPR_READ_ERROR;
    }
    else
    {
        return EXPR_READ_OK;
    }
}

bool Dijkstra_sort_station(lex_queue *in, lex_queue *out)
{
    lex_stack operators;
    lex_stack_init(&operators);
    while(!lex_queue_is_empty(in))
    {
        lexeme cur_lex;
        if(lex_queue_pop(in, &cur_lex)) //feature
        {
            if(cur_lex.type == LEX_CONST || cur_lex.type == LEX_VAR_NAME)
            {
                lex_queue_push(out, cur_lex);
            }
            else if(cur_lex.type == LEX_OPER)
            {
                lexeme op2;
                if(lex_stack_pop(&operators, &op2)) //feature
                {
                    while(!lex_stack_is_empty(&operators) 
                    && ((cur_lex.oper_priority <= op2.oper_priority && cur_lex.oper_assoc == left)
                    || (cur_lex.oper_assoc == right && cur_lex.oper_priority < op2.oper_priority)))
                    {
                        if(op2.type == LEX_BR_L)
                        {
                            break;
                        }
                        lex_queue_push(out, op2);
                        lex_stack_pop(&operators, &op2);
                    }
                    lex_stack_push(&operators, op2);
                    lex_stack_push(&operators, cur_lex);
                }
                else
                {
                    lex_stack_push(&operators, cur_lex);
                }
            }
            else if(cur_lex.type == LEX_BR_L)
            {
                lex_stack_push(&operators, cur_lex);
            }
            else if(cur_lex.type == LEX_BR_R)
            {
                lexeme cur_oper;
                do 
                {
                    lex_stack_pop(&operators, &cur_oper);
                    if(cur_oper.type != LEX_BR_L)
                    {
                        lex_queue_push(out, cur_oper);
                    }
                } while (!lex_stack_is_empty(&operators) && cur_oper.type != LEX_BR_L);
                if(cur_oper.type != LEX_BR_L)
                {
                    return false;
                }
            }
        }
        // printf("STACK:\n");
        // lex_stack_print(&operators);
        // printf("====================\n");
        // printf("OUTQUEUE:\n");
        // lex_queue_print(out);
        // printf("====================\n\n");
    }
    while(!lex_stack_is_empty(&operators))
    {
        lexeme cur_oper;
        lex_stack_pop(&operators, &cur_oper);
        if(cur_oper.type == LEX_BR_L)
        {
            return false;
        }
        lex_queue_push(out, cur_oper);
    }
    return true;
}

lex_tree postfix_to_tree(lex_queue *q)
{
    lexeme cur_lex;
    lex_tree cur_tree;
    stack_of_lex_trees operands;
    stack_of_lex_trees_init(&operands);
    while(lex_queue_pop(q, &cur_lex))
    {
        if(cur_lex.type == LEX_CONST || cur_lex.type == LEX_VAR_NAME)
        {
            stack_of_lex_trees_push(&operands, lex_tree_build(cur_lex, lex_tree_empty(), lex_tree_empty()));
        }
        else
        {
            lex_tree operand1;
            lex_tree operand2;
            if(cur_lex.oper == '~')
            {
                if(stack_of_lex_trees_pop(&operands, &operand1))
                {
                    cur_tree = lex_tree_build(cur_lex, operand1, lex_tree_empty());
                    stack_of_lex_trees_push(&operands, cur_tree);
                }
                else
                {
                    return lex_tree_empty(); //Возврат пустого дерева, т.к. нашли ошибку
                }
            }
            else 
            {
                if(stack_of_lex_trees_pop(&operands, &operand1) && stack_of_lex_trees_pop(&operands, &operand2))
                {
                    cur_tree = lex_tree_build(cur_lex, operand2, operand1);
                    stack_of_lex_trees_push(&operands, cur_tree);
                }
            }
        }
    }
    if(stack_of_lex_trees_size(&operands) == 1)
    {
        lex_tree result;
        stack_of_lex_trees_pop(&operands, &result);
        stack_of_lex_trees_destroy(&operands);
        return result;
    }
    else
    {
        return lex_tree_empty();
    }
}


void from_bin_to_n_tree(lex_tree tree)
{
    //TODO: написать функцию конвертирования бинарного дерева в n-мерное! 
    return;
}