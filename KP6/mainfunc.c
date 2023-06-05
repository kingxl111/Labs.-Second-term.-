#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define N 9  // Число параметров автомобиля

typedef struct
{
    char brand[18];
    char model[18];
    int manufact_year;
    char gear[18];
    char drive[18];
    int fuel_cons_per_100km;
    int mileage;
    int price;
    int top_speed;
} Car;

// Brand:Model:Manufacturer Year:Gear-box type:Drive:Consumption:Mileage:Price:Top speed
// Пользователь должен ввести либо два, либо три аргумента. Первый - это файл из которого
// будет производиться чтение, второй - бинарный файл(может и не существовать), третий - файл с результатом.
// В файле с результатом будет записан ответ на задачу(все автомобили, удовлетворяющие условию). 
// Если указано 3 аргумента, ответ будет записан в третьем файле, если 2 аргумента, ответ будет выведен на консоль

int main(int argc, char* argv[])
{
    if((argc > 3 + 1) || (argc < 2 + 1)) //Нам нужно 2 или 3 аргумента, но нулевой(саму программу) Си тоже считывает
    {
        fprintf(stderr, "Неверное число аргументов!\n");
        return 1;
    }

    FILE* input = fopen(argv[1], "rb"); //Чтобы избежать проблем с кодировками, пишем "rb"
    FILE* output = fopen(argv[2], "wb"); 

    // fread() возвращает количество успешно считанных элементов, так же как и scanf

    if(input == NULL || output == NULL) //error
    {
        fprintf(stderr, "Не удалось открыть один из файлов");
        return 1;
    }
    
    Car current_car;

    while(fscanf(input, "%[^:]:%[^:]:%d:%[^:]:%[^:]:%d:%d:%d:%d\n", current_car.brand, current_car.model, 
    &current_car.manufact_year, current_car.gear, current_car.drive, &current_car.fuel_cons_per_100km, 
    &current_car.mileage, &current_car.price, &current_car.top_speed) == N)  //[^;] - считывание до того, как встретим ;
    {
        // char *c;
        // int size = sizeof(Car); // количество записываемых байтов
        // // устанавливаем указатель на начало структуры
        // c = (char *)&current_car;
        // // посимвольно записываем в файл структуру
        // for (int i = 0; i < size; i++)
        // {
        //     if(putc(*c++, output) == EOF)
        //     {
        //         printf("Возникла ошибка во время записи файла!\n");
        //         return 2;
        //     }
        // }
        
        if(fwrite(&current_car, sizeof(Car), 1, output) != 1)
        {
            printf("Ошибка при попытке записи в файл\n");
            return 1;
        }
        
    }

    fclose(input);
    fclose(output);
    if(input == NULL || output == NULL) //error
    {
        fprintf(stderr, "Не удалось открыть один из файлов");
        return 1;
    }

    input = fopen(argv[2], "rb");

    int ans = 0; //Ответ на задачу
    double average_mileage = 0.0;
    double average_top_speed = 0.0;
    int cnt = 0; // количество автомобилей, участвующих в сравнении
    printf("Исходная таблица: \n");
    printf("Brand:Model:Manufacturer Year:Gear-box type:Drive:Consumption per 100 km:Mileage:Price:Top speed\n");
    while(fread(&current_car, sizeof(Car), 1, input) == 1)
    {
        printf("%s:%s:%d:%s:%s:%d:%d:%d:%d\n", current_car.brand, current_car.model, 
        current_car.manufact_year, current_car.gear, current_car.drive, current_car.fuel_cons_per_100km, 
        current_car.mileage, current_car.price, current_car.top_speed);

        average_mileage += current_car.mileage;
        average_top_speed += current_car.top_speed;
        cnt++;
    }
    average_mileage = average_mileage / cnt;
    average_top_speed = average_top_speed / cnt;
    fclose(input);
    printf("--------------------------------------------------------------------------------------\n");
    // printf("Средняя максимальная скорость(км/ч): %lf, средний пробег(км): %lf\n", average_top_speed, average_mileage);

    printf("Автомобили расположены в хоронологическом порядке их попадания на авторынок.\nНеобходимо посчитать в множестве каждого третьего автомобиля количество автомобилей, максимальная скорость которых выше (speed),\nпробег ниже (mileage), а год выпуска не более (year).\n");
    int speed, mileage, cmp_m_year; //Год выпуска для сравнения 
    printf("Введите скорость(speed) для сравнения: ");
    scanf("%d", &speed);
    printf("Введите пробег(mileage) для сравнения: ");
    scanf("%d", &mileage);
    printf("Введите год выпуска(year) для сравнения: ");
    scanf("%d", &cmp_m_year);
    printf("--------------------------------------------------------------------------------------\n");

    // int fs_pos = 0;
    // int first_jump = sizeof(current_car.brand) + sizeof(current_car.model);
    // int second_jump = sizeof(current_car.gear) + sizeof(current_car.drive) + sizeof(current_car.fuel_cons_per_100km);
    // int third_jump = sizeof(current_car.price);

    // offsetof(Car, current_car.manufact_year);
    // #define offsetof(t, f) &(((t*)0)->f)
    
    input = fopen(argv[2], "rb");
    if(argc == 3 + 1)
    {
        output = fopen(argv[3], "w");
    }
    fseek(input, 0, SEEK_SET);
    int counter = 0;

    while(fread(&current_car, sizeof(Car), 1, input) == 1)
    {
        counter++;

        // int cur_year;
        // fseek(input, first_jump, SEEK_CUR);
        // fread(&cur_year, sizeof(int), 1, input);
        // // printf("jump size: %d, cur_year: %d\n", first_jump, cur_year);

        // int cur_mileage;
        // fseek(input, second_jump, SEEK_CUR);
        // fread(&cur_mileage, sizeof(int), 1, input);

        // int cur_top_speed;
        // fseek(input, third_jump, SEEK_CUR);
        // fread(&cur_top_speed, sizeof(int), 1, input);

        if((current_car.top_speed > speed) && (current_car.mileage < mileage) && (current_car.manufact_year <= cmp_m_year))
        {
            ans++;
            FILE* stream;
            if(argc == 3 + 1)
            {
                stream = output;
            }
            else 
            {
                stream = stdout;
            }
            fprintf(stream, "%s:%s:%d:%s:%s:%d:%d:%d:%d\n", current_car.brand, current_car.model, 
                current_car.manufact_year, current_car.gear, current_car.drive, current_car.fuel_cons_per_100km, 
                current_car.mileage, current_car.price, current_car.top_speed);
            
        }
        fseek(input, sizeof(Car) * 3, SEEK_CUR);
        // printf("cur year: %d, cur mileage: %d, cur top speed: %d\n", cur_year, cur_mileage, cur_top_speed);
        // fs_pos = fs_pos + first_jump + second_jump + third_jump + 3 * sizeof(int);
    }
    fclose(input);
    if(argc == 3 + 1)
    {
        fclose(output);     
    }
    printf("Ответ: %d\n", ans);

    return 0;
}

