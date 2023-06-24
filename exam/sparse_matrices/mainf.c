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
    for(int i = 0;i < A_size;++i)
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
                    idx += 2;
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
    matrix mtx_r;
    dbl_v_init(&mtx_r.A);
    int_v_init(&mtx_r.M);

    matrix mtx1 = read_matrix();
    matrix mtx2 = read_matrix();

    int A1_size = dbl_v_get_size(&mtx1.A);

    show_matrix(&mtx1);
    show_matrix(&mtx2);
    // int M1_size = int_v_get_size(&mtx1.M);

    // int A2_size = dbl_v_get_size(&mtx2.A);
    // int M2_size = int_v_get_size(&mtx2.M);

    if((mtx1.n != mtx2.n) || (mtx1.m != mtx2.m))
    {
        return -1; //Размеры матриц не совпадают
    }
    
    int i = 0;
    
    show_matrix(&mtx1);
    show_matrix(&mtx2);
    

    

    




    show_matrix(&mtx_r);
    return 0;
}


/*
Способ хранения матрицы:
1. Цепочка ненулевых элементов в векторе A со строчным индексированием (индексы в массиве M равны 0, если
соответствующая строка матрицы содержит только нули)

Задание:
Сложить две разреженные матрицы
*/

