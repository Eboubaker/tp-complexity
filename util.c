#include "util.h"

Bench *bench_start(BenchType type, Bench *b)
{
    if (b == NULL)
    {
        b = (Bench *)malloc(sizeof(Bench));
    }
    b->start = get_seconds_fractions();
    b->end = 0;
    b->swaps = 0;
    b->found_index = -1;
    b->type = type;
    b->iterations = 0;
    b->comparisons = 0;
    return b;
}
void bench_mark_listb(Bench *b, int l[], int n)
{
    b->n = n;
    b->list_before = lst_cp(l, n);
}
void bench_mark_lista(Bench *b, int l[], int n)
{
    b->n = n;
    b->list_after = lst_cp(l, n);
}
void bench_end(Bench *b)
{
    b->end = get_seconds_fractions();
}

char* get_list_view(char *name, int list[], int n)
{
    char *s = (char*) malloc(sizeof(char) * 1000);
    char *r = s;
    if (n == 0)
    {
        s += sprintf(s, "%s=[empty list]", name);
        return s;
    }
    s += sprintf(s, "%s=[", name);
    if (n > VIEW_TRIM)
    {
        for (int i = 0; i < VIEW_PORTION; i++)
        {
            s += sprintf(s, "%d%s", list[i], i == VIEW_PORTION - 1 ? "" : ", ");
        }
        s += sprintf(s, ", ...,");
        for (int i = n - 1 - VIEW_PORTION; i < n; i++)
        {
            s += sprintf(s, "%d%s", list[i], i == n - 1 ? "" : ", ");
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            s += sprintf(s, "%d%s", list[i], i == n - 1 ? "" : ", ");
        }
    }
    s += sprintf(s, "]");
    return r;
}
void bench_print_statistics(Bench *b, char *label)
{
    printf("--------- Statistics for %s ---------\n", label);
    if (b->type == SEARCH_INDEX)
    {
        printf("|  index=%d\n|  iterations=%d\n|  comparisons=%d\n|  time=%f seconds\n",
               b->found_index,
               b->iterations,
               b->comparisons,
               b->end - b->start);
    }
    else if (b->type == SORT)
    {
        printf("|  iterations=%d\n|  comparisons=%d\n|  swaps=%d\n|  time=%f seconds\n|  %s\n|  %s\n",
               b->iterations,
               b->comparisons,
               b->swaps,
               b->end - b->start,
               get_list_view("before", b->list_before, b->n),
               get_list_view("after", b->list_after, b->n));
    }
}

double get_seconds_fractions()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_usec + (unsigned long long)now.tv_sec * 1000000) / 1000000.0L;
}

void swap(Bench *b, int l[], int i, int j)
{
    int t = l[i];
    l[i] = l[j];
    l[j] = t;
    b->swaps++;
}
// a greater than b
bool agtb(Bench *ben, int a, int b)
{
    ben->comparisons++;
    return a > b;
}
// a less than b
bool alsb(Bench *ben, int a, int b)
{
    ben->comparisons++;
    return a < b;
}
// a greater than or equal b
bool agteb(Bench *ben, int a, int b)
{
    ben->comparisons++;
    return a >= b;
}
// a equal b
bool aeqb(Bench *ben, int a, int b)
{
    ben->comparisons++;
    return a == b;
}

void randomize(int l[], int n, int min, int max)
{
    for (int i = 0; i < n; i++)
    {
        l[i] = min + rand() / (RAND_MAX / (max - min + 1) + 1);
    }
}

int min(int a, int b)
{
    return a > b ? b : a;
}


void print_list_view(char* name, int list[], int n)
{
    if (n == 0)
    {
        printf("%s=[empty list]\n", name);
        return;
    }
    printf("%s=[", name);
    if (n > VIEW_TRIM)
    {
        for (int i = 0; i < VIEW_PORTION; i++)
        {
            printf("%d%s", list[i], i == VIEW_PORTION - 1 ? "" : ", ");
        }
        printf(", ...,");
        for (int i = n - 1 - VIEW_PORTION; i < n; i++)
        {
            printf("%d%s", list[i], i == n - 1 ? "" : ", ");
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            printf("%d%s", list[i], i == n - 1 ? "" : ", ");
        }
    }
    printf("]\n");
}

int* lst_cp(int l[], int n)
{
    int *nl = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        nl[i] = l[i];
    }
    return nl;
}

int *lst_mk(int n)
{
    return (int *)malloc(sizeof(int) * n);
}
