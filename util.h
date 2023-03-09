#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#define VIEW_PORTION 8
#define VIEW_TRIM 25

typedef enum
{
    SORT = 0,
    SEARCH_INDEX = 1
} BenchType;

// Benchmark struct
typedef struct
{
    double start, end;
    int iterations;
    int n; // for sort
    int *list_before;// for sort
    int *list_after; // for sort
    int comparisons;
    int swaps;
    int found_index; // if type == SEARCH_INDEX
    BenchType type;
    char **label;
} Bench;


double get_seconds_fractions();
Bench* bench_start(BenchType type, Bench *b);

void bench_end(Bench *b);
void bench_print_statistics(Bench *b, char *label);
void swap(Bench *b, int l[], int i, int j);
bool agtb(Bench *ben, int a, int b); // a greater than b
bool alsb(Bench *ben, int a, int b); // a less than b
bool aeqb(Bench *ben, int a, int b); // a equal b
bool agteb(Bench *ben, int a, int b); // a greater than or equal b

void randomize(int l[], int n, int min, int max);
void print_list_view(char *name, int list[], int n);
int *lst_cp(int l[], int n);
int *lst_mk(int n);

void bench_mark_listb(Bench *b, int l[], int n);// before sort
void bench_mark_lista(Bench *b, int l[], int n);// after sort