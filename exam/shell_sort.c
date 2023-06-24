#include <stdio.h>


void shell_sort(double *ar, int size)
{
    int step = size / 2;
    while(step > 0)
    {
        for(int k = 0; k < size; ++k)
        {
            for(int i = k; i < size; i += step)
            {
                if(i + step < size)
                {
                    if(ar[i] > ar[i + step])
                    {
                        double t = ar[i];
                        ar[i] = ar[i + step];
                        ar[i + step] = t;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        step /= 2;
    }
}

int main()
{

    int n;
    scanf("%d", &n);
    double ar[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &ar[i]);
    }
    shell_sort(ar, n);
    for (int i = 0; i < n; i++)
    {
        printf("%lf ", ar[i]);
    } printf("\n");
    

    return 0;
}

