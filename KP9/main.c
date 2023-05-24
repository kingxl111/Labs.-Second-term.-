#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max_value_len 1000

//Сортировка: Линейный выбор с подсчетом
//Структура таблицы: комплексный тип ключа длиной 16 байт, 
//ключи хранятся вместе с данными, минимально число элементов - 19

typedef struct
{
    //ключ
    int Re_z; //действительная часть
    int Im_z; //мнимая часть

} Key;


typedef struct 
{
    //Ключ
    Key key;
    
    //Значение
    char value[max_value_len];

} Elem;

typedef struct 
{
    Key key;
    bool is_detected;

} lower_bound_result;


void mix_elems(Elem arr[], int size);
void lin_selection_by_counting_sort(Elem *arr, int size);
void int_lin_selection_by_counting_sort(int arr[], int arr_size);
lower_bound_result lower_bound(Elem arr[], int array_size, Key to_cmp_key, int *array_idx);
int int_lower_bound(int arr[], int size, int key);

void int_testing();

int main()
{
    
    Elem ar[] = 
    {
        {{1,1},"."},
        {{1,2},"⠄⠄⠄⢠⣄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢀⡀"},
        {{1,3},"⠄⠄⠄⢸⣿⣝⠦⣀⠄⢀⣀⣀⠄⠄⠄⣠⣾⣿⡇"},
        {{1,4},"⠄⠄⠄⢸⣿⣿⣿⣾⠿⢯⣿⣿⣯⣷⣾⣾⣿⣿"},
        {{1,5},"⠄⢀⡴⣺⣿⣿⡿⢛⣽⣿⣶⣶⡺⣿⣿⣿⣿⡇"},
        {{1,6},"⢀⣾⣾⣿⣿⣿⣿⢋⡙⣿⣿⣿⡟⣿⣿⣿⣿⡇"},
        {{1,7},"⢸⣿⣿⣿⣿⣿⣧⣈⣡⣿⣿⣿⣧⣙⣛⠿⣿⣿⣀"},
        {{1,8},"⢸⣿⣿⣿⠋⠄⠄⠄⢸⣿⣿⣿⣿⡄⠄⠄⢀⣿⣿⣯⣥⣖⣲⠦⣄⣀"},
        {{1,9},"⢸⣿⣿⣿⣷⡦⢤⡀⢸⣿⣿⣿⣿⣷⣄⣴⣿⣿⣿⣿⣿⣿⣿⣿⣶⣯⣟⣦⡀"},
        {{1,10},"⢸⣿⣿⣿⣿⡇⠄⢹⣯⣶⣿⣿⣿⣿⣿⣹⣿⣿⠄⠄⠉⠉⠛⠻⣿⣿⣿⣿⣿⡄"},
        {{1,11},"⠄⣿⣿⣿⣿⣧⣰⣾⠿⠿⠛⢿⠟⠛⠛⢹⣿⣿⠄⠄⠄⠄⠄⣠⣾⣿⣿⣿⡿⠁"},
        {{1,11},"⠄⣿⣿⣿⣿⣿⠶⣿⠄⠄⠄⣨⣀⣀⠄⢘⣿⣿⠄⠄⣠⣴⣿⣿⣿⣿⡿⠟⠁"},
        {{1,13},"⠄⢿⣿⣿⣿⣿⡖⢻⠖⠒⢻⣤⢾⡏⠉⠙⣿⣿⣶⣿⣿⣿⣿⠿⠋⠁"},
        {{1,14},"⠄⢸⣿⣿⣿⣿⣧⠈⠄⠄⠄⠙⠄⠄⠄⠄⣿⣿⣿⣿⣿⡏"},
        {{1,15},"⠄⢸⣿⣿⣿⣿⣿⣆⠄⠄⠄⠄⠄⠄⠄⠄⣿⣿⣿⣿⡟"},
        {{1,16},"⠄⢸⣿⣿⣿⠉⢿⣿⣄⠄⠄⠄⠄⠄⠄⠄⢹⣿⣿⡉"},
        {{1,17},"⠄⠈⣿⣿⣿⣧⠈⢿⣿⣦⡀⠄⠄⠄⠄⠄⠈⣿⣿⣿⡀"},
        {{1,18},"⠄⠄⢿⣿⣿⣿⣦⠄⠙⢿⣿⣦⡀⠄⠄⠄⠄⢸⣿⣿⣇"},
        {{1,19},"⠄⠄⠘⣿⣿⣿⣿⣧⠄⠄⠻⣿⣿⣦⡀⠄⢀⣼⣿⣿⣿⣵⡀"},
        {{1,20},"⠄⠄⠄⠘⢿⣿⣿⣿⠄⠄⠄⠘⣿⣿⣿⡏⠉⣿⣿⣿⣿⣿⣿⣆"},
        {{1,21},"⠄⠄⠄⠄⠄⠻⣿⢿⢣⠄⠄⠄⢹⣿⣿⡆⠄⣿⣿⣿⣿⣿⣿⣿⡄"},
        {{1,22},"⠄⠄⠄⠄⠄⠄⠘⠈⠄⠄⠄⠄⠘⣿⣿⣷⣤⣿⣿⣿⣷⣽⣿⣿⡇"},
        {{1,23},"⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠻⣿⣿⣿⣿⣿⣿⣿⣿⡇⠉⠁"},
        {{1,24},"⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠁⣸⣿⣿⣿⣿⣿⣿⣄"},
        {{1,24},"⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆"},
        {{5,24},"⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠚⠟⠛⠛⠛⠛⠛⠙⠻⣿⣿⡿⠃"},
        {{7,24},"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"},
        {{9,24},"⣿⣿⣿⣿⣿⡏⠉⠉⠉⠉⠉⠉⠉⠉⢹⡏⠉⠉⠉⣿⣿⣿⣿⣿⡏⠉⠉⣿⣿⣿"},
        {{11,24},"⣿⣿⣿⣿⣿⣇⠄⠄⠄⠄⠄⠄⠄⠄⣸⡇⠄⠄⠄⣿⣿⣿⣿⣿⡇⠄⠄⣿⣿⣿"},
        {{13,23},"⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⣿⣿⣿⡇⠄⠄⠄⣿⣿⣿⣿⣿⡇⠄⠄⣿⣿⣿"},
        {{13,24},"⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⣿⣿⣿⡇⠄⠄⠄⣿⣿⣿⣿⣿⡇⠄⠄⣿⣿⣿"},
        {{15,23},"⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⣿⣿⣿⡇⠄⠄⠄⠙⢿⣿⣿⣿⡇⠄⠄⣿⣿⣿"},
        {{15,24},"⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⠄⣿⣿⣿⡇⠄⠄⠄⠄⠄⠙⢿⣿⡇⠄⠄⣿⣿⣿"},
        {{17,24},"⣿⣿⣿⣿⣿⣿⣿⣿⡆⠄⠄⠄⣿⣿⣿⡇⠄⠄⠄⡀⠄⠄⠈⣿⡇⠄⠄⣿⣿⣿"},
        {{17,24},"⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠄⣿⣿⣿⡇⠄⠄⠄⣿⡄⠄⠄⣿⡇⠄⠄⣿⣿⣿"},
        {{17,24},"⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠄⢻⣿⣿⡇⠄⠄⠄⡿⠄⠄⠄⣿⡇⠄⠄⣿⣿⣿"},
        {{19,24},"⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠄⢸⣿⣿⡇⠄⠄⠄⠄⠄⠄⢠⣿⡇⠄⠄⣿⣿⣿"},
        {{21,23},"⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠄⢸⣿⣿⡇⠄⠄⠄⠄⣀⣴⣿⣿⡇⠄⠄⣿⣿⣿"},
        {{21,24},"⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣾⣿⣿⣷⣶⣶⣾⣿⣿⣿⣿⣿⣷⣶⣶⣿⣿⣿"},
        {{23,23},"⡟⠉⠉⠛⢿⣿⠋⢹⣿⣯⠉⢿⠉⢹⡟⠉⠉⢻⣿⣿⠉⢿⣿⡏⠉⣿⠋⢹⣿⣿"},
        {{25,27},"⣿⣿⣿⠄⢸⣿⠄⠈⣿⣿⡄⠄⠄⣿⠇⢰⣧⠄⣿⡇⠄⢸⣿⡇⠄⡏⠄⢸⣿⣿"},
        {{25,27},"⣿⣏⠄⠠⣾⡇⠄⠄⣿⣿⣷⠄⢠⣿⠄⢸⣿⠄⣿⡇⠄⠈⣿⡇⠄⠄⠄⢸⣿⣿"},
        {{25,27},"⣿⣿⣷⠄⢸⠇⢠⠄⢸⣿⡏⠄⠈⣿⡀⢸⣿⠄⣿⠃⢰⠄⣿⡇⠄⢀⡇⢸⣿⣿"},
        {{25,27},"⠟⠻⠟⠄⣸⠄⢀⠄⢸⡟⠄⣴⠄⢹⣇⠘⠋⢠⡿⠄⠸⠄⠸⡇⠄⣸⡇⢸⣿⣿"},
        {{27,22},"⣶⣶⣶⣶⣿⣤⣾⣧⣼⣷⣶⣿⣧⣴⣿⣶⣶⣿⣷⣶⣶⣶⣶⣷⣶⣿⣧⣼⣧⣼"},
        {{27,23},"⡿⠿⠿⢿⣿⠿⠿⣿⣿⠿⣿⣿⠛⣿⠟⣿⣿⠟⠻⡟⠛⠟⠛⠛⠛⣿⠟⠛⠻⣿"},
        {{27,24},"⡇⠄⣶⣾⠏⢀⣤⣿⣿⠄⢸⣿⠄⡏⠄⢸⣿⠄⠄⡇⠄⣶⡆⠄⣶⡇⠄⣦⠄⢸"},
        {{29,22},"⣿⠄⠿⢿⠄⢸⣿⣿⡟⠄⠸⣿⠄⠄⠄⢸⣿⠄⠄⡇⠄⣿⡇⠄⣿⡇⠄⣿⠄⢸"},
        {{29,23},"⣿⠄⣶⣾⠄⢸⣿⣿⡇⢀⠄⣿⠄⢀⡀⢸⣿⠄⠄⡇⠄⣿⡇⠄⣿⡇⠄⣿⠄⢸"},
        {{29,24},"⣿⠄⠻⢿⡇⠘⠛⢻⠄⣾⠄⣿⠄⣸⡇⢸⣿⣄⠄⠁⠄⣿⡇⠄⣿⡇⠄⣿⠄⢸"},
        {{31,22},"⣿⣶⣶⣾⣿⣶⣶⣿⣶⣿⣶⣾⣶⣿⣷⣾⣿⣿⣿⡇⠄⣿⡇⠄⣿⣇⠄⠁⢀⣼"},
        {{31,23},"⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"},
        {{31,24},""}

    };
    int ar_size = sizeof(ar) / sizeof(Elem);


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

    lin_selection_by_counting_sort(ar, ar_size);

    for (int i = 0; i < ar_size; i++)
    {
        printf(" Key: Re(z): %d, Im(z): %d, value: %s\n",ar[i].key.Re_z, ar[i].key.Im_z, ar[i].value);
    } printf("=================================================\n");

    while(true)
    {
        int Re_z, Im_z;
        printf("\n");
        printf("Введите действительную и мнимую часть ключа через пробел: ");
        scanf("%d%d", &Re_z, &Im_z);
        
        Key cur_key = {Re_z, Im_z};

        int idx = -1; // Индекс искомого элемента в массиве
        lower_bound_result res;
        res = lower_bound(ar, ar_size, cur_key, &idx);
        if(res.is_detected)
        {
            printf("Detected!: Re_z %d, Im_z: %d, position: %d, value: %s\n", res.key.Re_z, res.key.Im_z, idx, ar[idx].value);
        }
        else
        {
            printf("There's not element by the specified key\n");
        }

    }

    return 0;
}

void mix_elems(Elem arr[], int size)
{
    int n = 10000;
    for(int i = 0; i < n; ++i)
    {
        __int64_t r_idx1 = rand();
        __int64_t r_idx2 = rand();
        Elem tmp = arr[r_idx2 % size];
        arr[r_idx2 % size] = arr[r_idx1 % size];
        arr[r_idx1 % size] = tmp;
    }
}

int key_cmp(Key k1, Key k2)
{
    return k1.Re_z - k2.Re_z + k1.Im_z - k2.Im_z;
}

int cmp(Elem el1, Elem el2)
{
    return key_cmp(el1.key, el2.key);
}

void lin_selection_by_counting_sort(Elem arr[], int arr_size)
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

    Elem result[arr_size]; //Вспомогательный массив
    for (int i = 0; i < arr_size; i++)
    {
        result[counting[i]] = arr[i];
        // Elem tmp = arr[i];
        // arr[i] = arr[counting[i]];
        // arr[counting[i]] = tmp;
    }

    // for (int i = 0; i < arr_size; ++i)
    // {
    //     int min_idx = 0; //Индекс самомго "маленького" элемента правее текущего i
    //     for (int j = 0; j < arr_size; ++j)
    //     {
    //         if(counting[min_idx] > counting[j])
    //         {
    //             min_idx = j;
    //         }
    //     }
    //     result[i] = arr[min_idx];
    //     counting[min_idx] = 2e9; //Делаем уже выбранный элемент недоступным для повторного использования
    // }

    for (int i = 0; i < arr_size; i++)
    {
        arr[i] = result[i];
    }
}


lower_bound_result lower_bound(Elem arr[], int size, Key key, int *arr_idx)
{
    int l = 0;
    int r = size - 1;

    lower_bound_result result;
    result.is_detected = false;

    while(r - l != 1)
    {
        int mid = (l + r) / 2;
        int key_cmp_result = key_cmp(key, arr[mid].key);
        
        if(key_cmp_result <= 0) //Значит, нужно двигать границу влево
        {
            r = mid;
            if(key_cmp_result == 0)
            {
                result.is_detected = true;
                result.key = arr[mid].key;
            }
        }
        else if(key_cmp_result > 0)
        {
            l = mid;
        }
    }

    if(key_cmp(key, arr[l].key) == 0)
    {
        result.is_detected = true;
        result.key = arr[l].key;
        *arr_idx = l;
    }
    else if(key_cmp(key, arr[r].key) == 0)
    {
        result.is_detected = true;
        result.key = arr[r].key;
        *arr_idx = r;
    }


    return result;
}

void int_testing()
{
    int n;
    scanf("%d", &n);
    int array[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
    
    int_lin_selection_by_counting_sort(array, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    } printf("\n");
    
    while(true)
    {
        int key;
        scanf("%d", &key);
        int result = int_lower_bound(array, n, key);
        if(result != n)
        {
            printf("lower bound result: %d\n", array[result]);
        }
        else
        {
            printf("There's not element by the specified key\n");
        }
    }
}
void int_lin_selection_by_counting_sort(int arr[], int arr_size)
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
int int_lower_bound(int arr[], int size, int n) //будет возвращать индекс искомого элемента. 
{                                            // Если таких несколько, вернет самый первый по порядку в массиве
    int l = 0;
    int r = size - 1;
    int result = size;
    while(r - l != 1)
    {
        int mid = (l + r) / 2;
        int key_cmp_result = n - arr[mid];
        if(key_cmp_result <= 0) //Значит, нужно двигать границу влево
        {
            r = mid;
            if(key_cmp_result == 0)
            {
                result = mid;
            }
        }
        else if(key_cmp_result > 0)
        {
            l = mid;

        }
        // printf("current left: %d, current right: %d\n", l, r);
    }

    if(arr[l] == n)
    {
        result = l;
    }
    else if(arr[r] == n)
    {
        result = r;
    }

    return result;
}
