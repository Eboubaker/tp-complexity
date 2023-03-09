#include "util.h"

int serial_search(Bench *b, int x, int list[], int n);
int binary_search_iterative(Bench *b, int x, int list[], int n);
int binary_search_recursive(Bench *b, int x, int list[], int l, int r);

void bubble_sort(Bench *b, int list[], int n);
void bubble_sort_optimized(Bench *b, int list[], int n);
void max_sort(Bench *b, int list[], int n);
int *merge_sort(Bench *b, int list[], int n);
void insertion_sort(Bench *b, int list[], int n);
void insertion_sort_optimized(Bench *b, int list[], int n);