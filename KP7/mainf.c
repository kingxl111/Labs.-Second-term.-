#include <stdio.h>
#include "vector.h"
#include <stdbool.h>


typedef struct {
    int n, m;
    int_vec M; //Вектор для хранения индексов начал строк матрицы
    dbl_vec A; //Вектор для хранения значений и индексов столбцов
} matrix;


matrix read_matrix()
{
    int n, m;
    scanf("%d%d", &n, &m);
    matrix mt;
    mt.n = n;
    mt.m = m;   
    dbl_v_init(&(mt.A));
    int_v_init(&(mt.M));
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            double val;
            scanf("%lf", &val);
            if(val != 0)
            {   
                dbl_v_push_back(&mt.A, j);//Указываем индекс элемента в строке
                dbl_v_push_back(&mt.A, val);//Добавляем сам элемент после его индекса
            }
        }
        dbl_v_push_back(&mt.A, -1); //Конец строки будем обозначать с помощью -1
    }
    bool is_new_string = true;
    int A_size = dbl_v_get_size(&mt.A);
    for(int i=0;i<A_size;++i)
    {
        double val = dbl_v_get_at(&mt.A, i);
        if(val != -1 && is_new_string)
        {
            is_new_string = false;
            int_v_push_back(&mt.M, i); //Добавляем индекс первого  
        }                              //вхождения ненулевого элемента в строке
        else if(val == -1 && is_new_string)
        {
            int_v_push_back(&mt.M, -1);//Добавляем -1, если строка 
        }                              //полностью состоит из нулей
        else if(val == -1)
        {
            is_new_string = true;
        }
    }
    return mt;
}

void show_matrix(matrix *mt)
{
    printf("Vector A: ");
    dbl_v_show_vector(&(mt->A));
    printf("Vector M: ");
    int_v_show_vector(&(mt->M));
    int idx;
    for(int i=0;i<mt->n;++i)
    {
        idx = int_v_get_at(&(mt->M), i);
        if(idx == -1)
        {
            for(int j=0;j<mt->m;++j)
            {
                printf("%.1lf ", 0.0);
            } 
        }
        else
        {
            int k = 0;
            while(k != mt->m)
            {
                
                if(dbl_v_get_at(&(mt->A), idx) == k)
                {
                    printf("%.1lf ", dbl_v_get_at(&(mt->A), idx + 1)); 
                    idx+=2;
                }
                else
                {
                    printf("%.1lf ", 0.0);
                }
                ++k;
            }
        }
        printf("\n");
    }
}

int main()
{
    matrix mtx = read_matrix();

    int A_size = dbl_v_get_size(&mtx.A);
    int M_size = int_v_get_size(&mtx.M);

    int_vec raws_n; //Индексы строк, содержащих наибольшее количество ненулевых элментов
    dbl_vec raws_sums; //Суммы элементов строк с наибольшим количеством ненулевых элментов

    int_v_init(&raws_n);
    dbl_v_init(&raws_sums);

    double max_n = 0;
    int i = 0;
    int str_idx;
    double cur_sum;
    int cur_n;

    while(i<M_size)
    {
        str_idx = int_v_get_at(&mtx.M, i);//Получаем индекс первого ненулевого 
        if(str_idx==-1)                   //элемента в  текущей i-той строке
        {
            ++i;
            dbl_v_push_back(&raws_sums, 0);
            int_v_push_back(&raws_n, 0);
            continue;
        }
        cur_sum = 0;
        cur_n = 0;//число ненулевых элементов в строке
        while((str_idx < A_size) && dbl_v_get_at(&mtx.A, str_idx)!=(-1))
        {
            cur_sum += dbl_v_get_at(&mtx.A, str_idx + 1); //Получаем значение в i-той строке
            str_idx += 2;                                   //под индексом, следующим за str_idx
            cur_n++;
        }
        if(cur_n > max_n)
        {
            max_n = cur_n; //Находим максимальное количество элементов в строке
        }
        dbl_v_push_back(&raws_sums, cur_sum);
        int_v_push_back(&raws_n, cur_n);
        ++i;
    }
    // dbl_v_show_vector(&raws_sums);
    //int_v_show_vector(&raws_n);
    for(i = 0; i < dbl_v_get_size(&raws_sums);++i)
    {
        cur_n = int_v_get_at(&raws_n, i);
        if(cur_n == max_n)
        {
            printf("Raw index: %d\nSum of the raw elements: %.1lf\n", i, dbl_v_get_at(&raws_sums, i));
        }
    }
    show_matrix(&mtx);
    return 0;
}


/*
Способ хранения матрицы:
1. Цепочка ненулевых элементов в векторе A со строчным индексированием (индексы в массиве M равны 0, если
соответствующая строка матрицы содержит только нули)

Задание:
7. Найти строку, содержащую наибольшее количество ненулевых элементов, и напечатать ее номер и сумму элементов
этой строки. Если таких строк несколько, обработать все.
*/

