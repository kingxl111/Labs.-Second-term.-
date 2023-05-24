#include <stdio.h>
#include "functions.h"
#include "other_functions.h"

int main()
{
    int n;  
    int k;
    printf("Введите число для возведения в квадрат и умножения на 100: ");
    scanf("%d", &n);

    int sq = square(n);
    int mul_100 = mul100(n);

    printf("Квадрат числа: %d\n", sq);
    printf("Число, умноженное на 100: %d\n", mul_100);

    return 0;
}