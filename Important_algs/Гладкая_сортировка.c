
leo = {1, 1, 3, 5, 9, 15, 25, 41};//Числа Леонардо

void sort_roots(double *arr, int *heap_leo_idx, int heap_cnt, int root)
{
    int root_leo_idx = heap_leo_idx[heap_cnt - 1];
    if(heap_cnt <= 1)
    {
        sift_leo(arr, root, root_leo_idx);
        return;
    }
    int prev_idx = root - leo[root_leo_idx]; //Индекс корня предпоследней кучи

    int left = root_leo_idx < 2 ? -1 : root - 1 - leo[root_leo_idx - 2]; //Индекс левого ребенка
    //leo[root_leo_idx - 2] - размер правого ребенка

    int right = root_leo_idx < 2 ? -1 : root - 1; 

    if(arr[prev_idx] > arr[root] && (left < 0 || arr[prev_idx] > arr[left]) 
    && (right < 0 || arr[prev_idx] > arr[right]))
    {
        swap(&arr[prev_idx], &arr[root]);
        sort_roots(arr, heap_leo_idx, heap_cnt - 1, prev_idx);
    }
    else
    {
        sift_leo(arr, root, root_leo_idx);
    }

}

void smooth_sort(double *arr, int n)
{
    int heap_leo_idx[64];
    int heap_cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if(heap_cnt >= 2 && heap_leo_idx[heap_cnt - 2] == heap_leo_idx[heap_cnt - 1] + 1)
        {
            heap_leo_idx[heap_cnt - 2];
            heap_cnt--;
        }
        else 
        {
            heap_leo_idx[heap_cnt] = heap_leo_idx[heap_cnt - 1] == 1 ? 0 : 1;
            heap_cnt++;
        }
        sort_roots(arr, heap_leo_idx, heap_cnt, i);
    }
    while(n > 0)
    {
        int root = n - 1;
        n--;
        int leo_idx = heap_leo_idx[heap_cnt - 1]; 
        if(leo_idx < 2)
        {
            heap_cnt--;
            continue;
        }

        heap_cnt++;
        heap_leo_idx[heap_cnt - 2] = leo_idx - 1;
        heap_leo_idx[heap_cnt - 1] = leo_idx - 2;

        int left = root - 1 - leo[leo_idx - 2];
        int right = root - 1;

        sort_roots(arr, heap_leo_idx, heap_cnt - 1, left);
        sort_roots(arr, heap_leo_idx, heap_cnt, right);
    }
}

