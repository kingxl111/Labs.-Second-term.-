#include <stdio.h>


int main()
{
    //Пусть даны два файла. Надо произвести их слияние.
    FILE* f1 = fopen("f1", "rb");
    FILE* f2 = fopen("f2", "rb");

    FILE* f1_bin = fopen("f1_bin", "wb");
    FILE* f2_bin = fopen("f2_bin", "wb");

    char c;
    int f1_size = 0;
    int f2_size = 0;
    while(fscanf(f1, "%c", &c) != EOF)
    {
        fwrite(&c, sizeof(char), 1, f1_bin);
        f1_size++;
    }
    while(fscanf(f2, "%c", &c) != EOF)
    {
        fwrite(&c, sizeof(char), 1, f2_bin);
        f2_size++;
    }
    fclose(f1);
    fclose(f1_bin);
    fclose(f2);
    fclose(f2_bin);

    f1_bin = fopen("f1_bin", "rb");
    f2_bin = fopen("f2_bin", "rb");
    
    int i = 0, j = 0;
    char c1, c2;
    fread(&c1, sizeof(char), 1, f1_bin);
    fread(&c2, sizeof(char), 1, f2_bin);
    
    FILE* result = fopen("result", "w");

    while(i < f1_size && j < f2_size)
    {
        if(c1 < c2)
        {
            fprintf(result, "%c", c1);
            i++;
            fread(&c1, sizeof(char), 1, f1_bin);
        }
        else
        {
            fprintf(result, "%c", c2);
            j++;
            fread(&c2, sizeof(char), 1, f2_bin);
        }
    }
    while(i < f1_size)
    {
        fread(&c1, sizeof(char), 1, f1_bin);
        fprintf(result, "%c", c1);
        i++;
    }
    while(j < f2_size)
    {
        fread(&c1, sizeof(char), 1, f2_bin);
        fprintf(result, "%c", c2);
        j++;
    }

    fclose(f1_bin);
    fclose(f2_bin);
    fclose(result);

    return 0;
}
