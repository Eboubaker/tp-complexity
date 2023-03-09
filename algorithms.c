#include "algorithms.h"

int serial_search(Bench *b, int x, int list[], int n)
{
    for (int i = 0; i < n; i++)
    {
        b->iterations++;
        if (aeqb(b, list[i], x))
        {
            return i;
        }
    }
    return -1;
}

int binary_search_iterative(Bench *b, int x, int list[], int n)
{
    int l = 0, r = n - 1;
    while (l <= r)
    {
        b->iterations++;
        // printf("searching for value %d, l=%d,r=%d\n", x, l, r);
        int m = l + (r - l) / 2;

        if (aeqb(b, x, list[m]))
        {
            return m;
        }
        else if (alsb(b, x, list[m]))
        {
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }
    return -1;
}

int binary_search_recursive(Bench *b, int x, int list[], int l, int r)
{
    if (l > r)
    {
        return -1;
    }
    b->iterations++;

    int m = l + (r - l) / 2;

    if (aeqb(b, x, list[m]))
    {
        return m;
    }
    else if (alsb(b, x, list[m]))
    {
        return binary_search_recursive(b, x, list, l, m - 1);
    }
    else
    {
        return binary_search_recursive(b, x, list, m + 1, r);
    }
}
void bubble_sort(Bench *b, int list[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            b->iterations++;
            if (agtb(b, list[j], list[j + 1]))
            {
                swap(b, list, j, j + 1);
            }
        }
    }
}
void bubble_sort_optimized(Bench *b, int list[], int n)
{
    bool swapped;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            b->iterations++;
            if (agtb(b, list[j], list[j + 1]))
            {
                swap(b, list, j, j + 1);
                swapped = true;
            }
        }
        if (!swapped)
            return; // list sorted
    }
}

void max_sort(Bench *b, int list[], int n)
{
    int jmax;
    for (int i = 0; i < n; i++)
    {
        jmax = i;
        for (int j = jmax + 1; j < n; j++)
        {
            b->iterations++;
            if (agtb(b, list[jmax], list[j]))
            {
                jmax = j;
            }
        }
        swap(b, list, i, jmax);
    }
}

int *merge_sort(Bench *b, int list[], int n)
{
    if (n <= 1)
        return lst_cp(list, n);

    int *cp1 = lst_cp(list, n / 2);
    int *cp2 = lst_cp(list + (n / 2), n - n / 2);
    int *lst1 = merge_sort(b, cp1, n / 2);
    int *lst2 = merge_sort(b, cp2, n - n / 2);
    free(cp1);
    free(cp2);

    int i1 = 0, i2 = 0;
    list = lst_mk(n);
    for (int i = 0; i < n; i++)
    {
        b->iterations++;
        if ((alsb(b, lst1[i1], lst2[i2]) && i1 < n / 2) || i2 >= (n - n / 2))
        {
            list[i] = lst1[i1++];
        }
        else
        {
            list[i] = lst2[i2++];
        }
    }
    return list;
}

void insertion_sort(Bench *b, int list[], int n)
{
    int i, k;
    for (i = 1; i < n; i++)
    {
        k = i - 1;
        b->iterations++;
        while (agteb(b, k, 0) && alsb(b, list[k + 1], list[k]))
        {
            b->iterations++;
            swap(b, list, k, k+1);
            k--;
        }
    }
    b->swaps *= 3;// operations
}

void insertion_sort_optimized(Bench *b, int list[], int n)
{
    int i, k, x;
    for (i = 1; i < n; i++)
    {
        k = i - 1;
        x = list[i];
        b->iterations++;
        while (agteb(b, k, 0) && agtb(b, list[k], x))
        {
            list[k + 1] = list[k];
            k -= 1;
            b->iterations++;
            b->swaps++;
        }
        list[k + 1] = x;
    }
    b->swaps *= 2; // operations
}
