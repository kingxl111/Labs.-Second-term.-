#include <stdio.h>
#include <stdlib.h>


#define max_value_len 1000

//Сортировка: Линейный выбор с подсчетом
//Структура таблицы: комплексный тип ключа длиной 16 байт, 
//ключи хранятся вместе с данными, минимально число элементов - 19

typedef struct 
{
    //ключ
    int Re_z; //действительная часть
    int Im_z; //мнимая часть
    
    //Значение
    char value[max_value_len];

} elem;

void mix_elems(elem arr[], int size);
void lin_selection_by_counting(elem *arr, int size);
void int_lin_selection_by_counting(int arr[], int arr_size);

int main()
{


    int ar_size = 53;
    elem ar[] = 
    {
        {1,1,"."},
        {1,2,"⠄⠄⠄⢠⣄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢀⡀"},
        {1,3,"⠄⠄⠄⢸⣿⣝⠦⣀⠄⢀⣀⣀⠄⠄⠄⣠⣾⣿⡇"},
        {1,4,"⠄⠄⠄⢸⣿⣿⣿⣾⠿⢯⣿⣿⣯⣷⣾⣾⣿⣿"},
        {1,5,"⠄⢀⡴⣺⣿⣿⡿⢛⣽⣿⣶⣶⡺⣿⣿⣿⣿⡇"},
        {1,6,"⢀⣾⣾⣿⣿⣿⣿⢋⡙⣿⣿⣿⡟⣿⣿⣿⣿⡇"},
        {1,7,"⢸⣿⣿⣿⣿⣿⣧⣈⣡⣿⣿⣿⣧⣙⣛⠿⣿⣿⣀"},
        {1,8,"⢸⣿⣿⣿⠋⠄⠄⠄⢸⣿⣿⣿⣿⡄⠄⠄⢀⣿⣿⣯⣥⣖⣲⠦⣄⣀"},
        {1,9,"⢸⣿⣿⣿⣷⡦⢤⡀⢸⣿⣿⣿⣿⣷⣄⣴⣿⣿⣿⣿⣿⣿⣿⣿⣶⣯⣟⣦⡀"},
        {1,10,"⢸⣿⣿⣿⣿⡇⠄⢹⣯⣶⣿⣿⣿⣿⣿⣹⣿⣿⠄⠄⠉⠉⠛⠻⣿⣿⣿⣿⣿⡄"},
        {1,11,"⠄⣿⣿⣿⣿⣧⣰⣾⠿⠿⠛⢿⠟⠛⠛⢹⣿⣿⠄⠄⠄⠄⠄⣠⣾⣿⣿⣿⡿⠁"},
        {1,12,"⠄⣿⣿⣿⣿⣿⠶⣿⠄⠄⠄⣨⣀⣀⠄⢘⣿⣿⠄⠄⣠⣴⣿⣿⣿⣿⡿⠟⠁"},
        {1,13,"⠄⢿⣿⣿⣿⣿⡖⢻⠖⠒⢻⣤⢾⡏⠉⠙⣿⣿⣶⣿⣿⣿⣿⠿⠋⠁"},
        {1,14,"⠄⢸⣿⣿⣿⣿⣧⠈⠄⠄⠄⠙⠄⠄⠄⠄⣿⣿⣿⣿⣿⡏"},
        {1,15,"⠄⢸⣿⣿⣿⣿⣿⣆⠄⠄⠄⠄⠄⠄⠄⠄⣿⣿⣿⣿⡟"},
        {1,16,"⠄⢸⣿⣿⣿⠉⢿⣿⣄⠄⠄⠄⠄⠄⠄⠄⢹⣿⣿⡉"},
        {1,17,"⠄⠈⣿⣿⣿⣧⠈⢿⣿⣦⡀⠄⠄⠄⠄⠄⠈⣿⣿⣿⡀"},
        {1,18,"⠄⠄⢿⣿⣿⣿⣦⠄⠙⢿⣿⣦⡀⠄⠄⠄⠄⢸⣿⣿⣇"},
        {1,19,"⠄⠄⠘⣿⣿⣿⣿⣧⠄⠄⠻⣿⣿⣦⡀⠄⢀⣼⣿⣿⣿⣵⡀"},
        {1,20,"⠄⠄⠄⠘⢿⣿⣿⣿⠄⠄⠄⠘⣿⣿⣿⡏⠉⣿⣿⣿⣿⣿⣿⣆"},
        {1,21,"⠄⠄⠄⠄⠄⠻⣿⢿⢣⠄⠄⠄⢹⣿⣿⡆⠄⣿⣿⣿⣿⣿⣿⣿⡄"},
        {1,22,"⠄⠄⠄⠄⠄⠄⠘⠈⠄⠄⠄⠄⠘⣿⣿⣷⣤⣿⣿⣿⣷⣽⣿⣿⡇"},
        {1,23,"⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠻⣿⣿⣿⣿⣿⣿⣿⣿⡇⠉⠁"},
        {1,24,"⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠁⣸⣿⣿⣿⣿⣿⣿⣄"},
        {3,24,"⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆"},
        {5,24,"⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠚⠟⠛⠛⠛⠛⠛⠙⠻⣿⣿⡿⠃"},
        {7,24,"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"},
        {9,24,"⣿⣿⣿⣿⣿⡏⠉⠉⠉⠉⠉⠉⠉⠉⢹⡏⠉⠉⠉⣿⣿⣿⣿⣿⡏⠉⠉⣿⣿⣿"},
        {11,24,"⣿⣿⣿⣿⣿⣇⠄⠄⠄⠄⠄⠄⠄⠄⣸⡇⠄⠄⠄⣿⣿⣿⣿⣿⡇⠄⠄⣿⣿⣿"},
        {13,23,"⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⣿⣿⣿⡇⠄⠄⠄⣿⣿⣿⣿⣿⡇⠄⠄⣿⣿⣿"},
        {13,24,"⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⣿⣿⣿⡇⠄⠄⠄⣿⣿⣿⣿⣿⡇⠄⠄⣿⣿⣿"},
        {15,23,"⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⣿⣿⣿⡇⠄⠄⠄⠙⢿⣿⣿⣿⡇⠄⠄⣿⣿⣿"},
        {15,24,"⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⣿⣿⣿⡇⠄⠄⠄⠄⠄⠙⢿⣿⡇⠄⠄⣿⣿⣿"},
        {17,23,"⣿⣿⣿⣿⣿⣿⣿⣿⡆⠄⠄⠄⣿⣿⣿⡇⠄⠄⠄⡀⠄⠄⠈⣿⡇⠄⠄⣿⣿⣿"},
        {17,24,"⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠄⣿⣿⣿⡇⠄⠄⠄⣿⡄⠄⠄⣿⡇⠄⠄⣿⣿⣿"},
        {19,23,"⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠄⢻⣿⣿⡇⠄⠄⠄⡿⠄⠄⠄⣿⡇⠄⠄⣿⣿⣿"},
        {19,24,"⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠄⢸⣿⣿⡇⠄⠄⠄⠄⠄⠄⢠⣿⡇⠄⠄⣿⣿⣿"},
        {21,23,"⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠄⢸⣿⣿⡇⠄⠄⠄⠄⣀⣴⣿⣿⡇⠄⠄⣿⣿⣿"},
        {21,24,"⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣾⣿⣿⣷⣶⣶⣾⣿⣿⣿⣿⣿⣷⣶⣶⣿⣿⣿"},
        {23,23,"⡟⠉⠉⠛⢿⣿⠋⢹⣿⣯⠉⢿⠉⢹⡟⠉⠉⢻⣿⣿⠉⢿⣿⡏⠉⣿⠋⢹⣿⣿"},
        {23,24,"⣿⣿⣿⠄⢸⣿⠄⠈⣿⣿⡄⠄⠄⣿⠇⢰⣧⠄⣿⡇⠄⢸⣿⡇⠄⡏⠄⢸⣿⣿"},
        {25,22,"⣿⣏⠄⠠⣾⡇⠄⠄⣿⣿⣷⠄⢠⣿⠄⢸⣿⠄⣿⡇⠄⠈⣿⡇⠄⠄⠄⢸⣿⣿"},
        {25,23,"⣿⣿⣷⠄⢸⠇⢠⠄⢸⣿⡏⠄⠈⣿⡀⢸⣿⠄⣿⠃⢰⠄⣿⡇⠄⢀⡇⢸⣿⣿"},
        {25,24,"⠟⠻⠟⠄⣸⠄⢀⠄⢸⡟⠄⣴⠄⢹⣇⠘⠋⢠⡿⠄⠸⠄⠸⡇⠄⣸⡇⢸⣿⣿"},
        {27,22,"⣶⣶⣶⣶⣿⣤⣾⣧⣼⣷⣶⣿⣧⣴⣿⣶⣶⣿⣷⣶⣶⣶⣶⣷⣶⣿⣧⣼⣧⣼"},
        {27,23,"⡿⠿⠿⢿⣿⠿⠿⣿⣿⠿⣿⣿⠛⣿⠟⣿⣿⠟⠻⡟⠛⠟⠛⠛⠛⣿⠟⠛⠻⣿"},
        {27,24,"⡇⠄⣶⣾⠏⢀⣤⣿⣿⠄⢸⣿⠄⡏⠄⢸⣿⠄⠄⡇⠄⣶⡆⠄⣶⡇⠄⣦⠄⢸"},
        {29,22,"⣿⠄⠿⢿⠄⢸⣿⣿⡟⠄⠸⣿⠄⠄⠄⢸⣿⠄⠄⡇⠄⣿⡇⠄⣿⡇⠄⣿⠄⢸"},
        {29,23,"⣿⠄⣶⣾⠄⢸⣿⣿⡇⢀⠄⣿⠄⢀⡀⢸⣿⠄⠄⡇⠄⣿⡇⠄⣿⡇⠄⣿⠄⢸"},
        {29,24,"⣿⠄⠻⢿⡇⠘⠛⢻⠄⣾⠄⣿⠄⣸⡇⢸⣿⣄⠄⠁⠄⣿⡇⠄⣿⡇⠄⣿⠄⢸"},
        {31,22,"⣿⣶⣶⣾⣿⣶⣶⣿⣶⣿⣶⣾⣶⣿⣷⣾⣿⣿⣿⡇⠄⣿⡇⠄⣿⣇⠄⠁⢀⣼"},
        {31,23,"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"},
        {31,24,""}
    };

    // for (int i = 0; i < ar_size; i++)
    // {
    //     printf("%s\n", ar[i].value);
    // }
    
    mix_elems(ar, ar_size);
    mix_elems(ar, ar_size);
    mix_elems(ar, ar_size);
    mix_elems(ar, ar_size);
    mix_elems(ar, ar_size);


    for (int i = 0; i < ar_size; i++)
    {
        printf("%s\n", ar[i].value);
    } printf("=================================================\n");

    lin_selection_by_counting(ar, ar_size);

    for (int i = 0; i < ar_size; i++)
    {
        printf("%s\n", ar[i].value);
    } printf("=================================================\n");


    // int n;
    // scanf("%d", &n);
    // int array[n];
    // for (int i = 0; i < n; i++)
    // {
    //     scanf("%d", &array[i]);
    // }
    
    // int_lin_selection_by_counting(array, n);

    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d ", array[i]);
    // } printf("\n");
    

    return 0;
}

void mix_elems(elem arr[], int size)
{
    int n = 10000;
    for(int i = 0; i < n; ++i)
    {
        __int64_t r_idx1 = rand();
        __int64_t r_idx2 = rand();
        elem tmp = arr[r_idx2 % size];
        arr[r_idx2 % size] = arr[r_idx1 % size];
        arr[r_idx1 % size] = tmp;
    }
}

int cmp(elem el1, elem el2)
{
    int sqrt1 = el1.Im_z * el1.Im_z + el1.Re_z * el1.Re_z; //сумма квадратов для вычисления абсолютного значения
    int sqrt2 = el2.Im_z * el2.Im_z + el2.Re_z * el2.Re_z;
    int result = sqrt1 - sqrt2;

    return result;
}

void lin_selection_by_counting(elem arr[], int arr_size)
{   

    int counting[arr_size];
    for(int i = 0; i < arr_size; ++i)
    {
        counting[i] = 0;
    }

    for(int i = 0; i < arr_size; ++i)
    {
        for(int j = i + 1; j < arr_size; ++j)
        {
            int cmp_res = cmp(arr[i], arr[j]);
            if(cmp_res <= 0)
            {
                counting[j]++;
            }
            else if(cmp_res > 0)
            {
                counting[i]++;
            }
        }
    }

    elem result[arr_size]; //Вспомогательный массив
    for (int i = 0; i < arr_size; i++)
    {
        result[i] = arr[i];
    }

    for (int i = 0; i < arr_size; ++i)
    {
        int min_idx = 0; //Индекс самомго "маленького" элемента правее текущего i
        for (int j = 0; j < arr_size; ++j)
        {
            if(counting[min_idx] > counting[j])
            {
                min_idx = j;
            }
        }
        result[i] = arr[min_idx];
        counting[min_idx] = 1e9; //Делаем уже выбранный элемент недоступным для повторного использования
    }

    for (int i = 0; i < arr_size; i++)
    {
        arr[i] = result[i];
    }
}

void int_lin_selection_by_counting(int arr[], int arr_size)
{   
    int counting[arr_size];
    for(int i = 0; i < arr_size; ++i)
    {
        counting[i] = 0;
    }

    for(int i = 0; i < arr_size; ++i)
    {
        for(int j = i + 1; j < arr_size; ++j)
        {
            int cmp_res = arr[i] - arr[j];
            if(cmp_res <= 0)
            {
                counting[j]++;
            }
            else if(cmp_res > 0)
            {
                counting[i]++;
            }
        }
    }
    // printf("counting: ");
    // for (int i = 0; i < arr_size; i++)
    // {
    //     printf("%d ", counting[i]);
    // } printf("\n"); 
    
    int result[arr_size]; //Вспомогательный массив
    for (int i = 0; i < arr_size; i++)
    {
        result[i] = arr[i];
    }

    for (int i = 0; i < arr_size; ++i)
    {
        int min_idx = 0; //Индекс самого "маленького" элемента правее текущего i
        for (int j = 0; j < arr_size; ++j)
        {
            if(counting[min_idx] > counting[j])
            {
                min_idx = j;
            }
        }
        result[i] = arr[min_idx];
        counting[min_idx] = 1e9;
        // printf("min: %d, idx: %d\n", arr[i], min_idx);

        // for (int j = 0; j < arr_size; j++)
        // {
        //     printf("%d ", counting[j]);
        // }   printf("\n");
        // for (int j = 0; j < arr_size; j++)
        // {
        //     printf("%d ", arr[j]);
        // }   printf("\n--------------------------\n");
    }

    for (int i = 0; i < arr_size; i++)
    {
        arr[i] = result[i];
    }
}
