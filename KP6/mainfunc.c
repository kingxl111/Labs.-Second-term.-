#include <stdio.h>

typedef struct
{
    char brand[25];
    char model[25];
    int manufact_year;
    char gear[15];
    char drive[20];
    int fuel_cons_per_100km;
    int mileage;
    int price;
} Car;


//Brand:Model:Manufacture year:Gear:Drive:Fuel consumption per 100 km:Mileage:Price

int main(int argc, char* argv[])
{
    if(argc != 2 + 1) //Нам нужно 2 аргумента, но нулевой(саму программу) Си тоже считывает
    {
        fprintf(stderr, "Неверное число аргументов!\n");
        return 1;
    }
    FILE* input = fopen(argv[1], "rb"); //Чтобы избежать проблем с кодировками, пишем "rb"
    FILE* output = fopen(argv[2], "w"); 

    // fread() возвращает количество успешно считанных элементов, так же как и scanf

    if(input == NULL || output == NULL) //error
    {
        fprintf(stderr, "Не удалось открыть один из файлов");
        return 1;
    }
    
    Car current_car;

    while(fscanf(input, "%[^:]:%[^:]:%d:%[^:]:%[^:]:%d:%d:%d", current_car.brand, current_car.model, 
    &current_car.manufact_year, current_car.gear, current_car.drive, &current_car.fuel_cons_per_100km, 
    &current_car.mileage, &current_car.price)!= EOF)  //[^;] - считывание до того, как встретим ;
    {
        printf("Car:\n");
        printf("brand: %s\n", current_car.brand);
        printf("model: %s\n", current_car.model);
        printf("m_year: %d\n", current_car.manufact_year);
        printf("gear: %s\n", current_car.gear);
        printf("drive: %s\n", current_car.drive);
        printf("-------------------------------------------------\n");
        
        if(fwrite(&current_car, sizeof(Car), 8, output) != 8)
        {
            printf("Ошибка при попытке записи в файл\n");
            return 1;
        }

        //Тут еще проверка на ошибку

        //Если fwrite успешно выполнилась, то она вернет количество записанных байтов(третий аргумент)



        //printf("%s, %s, %d, %s, %s, %d, %d, %d", c.brand, 
        //c.model, c.manufact_year, c.gear, c.drive, c.fuel_cons_per_100km, c.mileage, c.price);
    }

    //Следующая программка будет читать бинарный файл с помощью fread 

    // FILE* nf = fopen(argv[3], "w");

    // //stdout потом надо будет заменить на файл какой-нибудь
    // while(fread(stdout, sizeof(c.brand), 1, output)
    //      && fread(stdout, sizeof(c.model), 1, output)
    //      && fread(stdout, sizeof(c.manufact_year), 1, output)
    //      && fread(stdout, sizeof(c.gear), 1, output)
    //      && fread(stdout, sizeof(c.drive), 1, output)
    //      && fread(stdout, sizeof(c.fuel_cons_per_100km), 1, output)
    //      && fread(stdout, sizeof(c.mileage), 1, output)
    //      && fread(stdout, sizeof(c.price), 1, output))
    // {
        
    //     printf("Ok\n");
    // }



    fclose(input);
    fclose(output);
    // fclose(nf);


    return 0;
}