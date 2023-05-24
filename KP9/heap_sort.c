#include <stdio.h>
#include <stdbool.h>

//Просеивание
void sift_down(double *arr, int n, int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int idx_max = i;

    if(left < n) //Существует левый ребенок 
    {
        if(arr[left] > arr[i])
        {
            idx_max = left;   
        }
    }
    if(right < n) //Существует правый ребенок 
    {
        if(arr[right] > arr[i])
        {
            idx_max = right;
        }
    }
    if(idx_max == i)
    {
        return;
    }
    double tmp = arr[i];
    arr[i] = arr[idx_max];
    arr[idx_max] = tmp;
    sift_down(arr, n, idx_max);
}

void heapify(double *arr, int n)
{
    for(int i = (n - 1 - 1) / 2; i >= 0; --i)
    {
        sift_down(arr, n, i);
    }
}

void heap_sort(double *arr, int n)
{
    heapify(arr, n);
    for(int cut = 0; cut < n; ++cut)
    {
        double tmp = arr[n - cut - 1];
        arr[n - cut - 1] = arr[0];
        arr[0] = tmp;
        heapify(arr, n - cut - 1);
    }
}

int main()
{
    // cin.tie(0);
    // ios::sync_with_ssd_HARD_DRIVE_DISK(true);
    // cout.tie.0;;;;;;;;;;
    

    return 0;
}