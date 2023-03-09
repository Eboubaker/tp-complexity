// Students: Bekkouche Boubaker, Mahmoudi Akram
#include "algorithms.h"

#define LIST_VMIN (int)0
#define LIST_VMAX (int)10000
#define LIST_SIZE 10000

int main(int argc, char **argv)
{
    time_t s = 1;

    Bench *b = bench_start(SEARCH_INDEX, NULL);
    int n = LIST_SIZE;

    int *list = lst_mk(n);
    srand(s);
    randomize(list, n, LIST_VMIN, LIST_VMAX);

    bench_start(SEARCH_INDEX, b);
    b->found_index = serial_search(b, list[400], list, n);
    bench_end(b);
    bench_print_statistics(b, "serial search");

    bench_start(SEARCH_INDEX, b);
    b->found_index = binary_search_iterative(b, list[400], list, n);
    bench_end(b);
    bench_print_statistics(b, "binary search -- iterative");

    srand(s);
    randomize(list, n, LIST_VMIN, LIST_VMAX);

    bench_start(SEARCH_INDEX, b);
    b->found_index = binary_search_recursive(b, list[400], list, 0, n - 1);
    bench_end(b);
    bench_print_statistics(b, "binary search -- recursive");

    bench_mark_listb(b, list, n);
    bench_start(SORT, b);
    bubble_sort(b, list, n);
    bench_end(b);
    bench_mark_lista(b, list, n);
    bench_print_statistics(b, "bubble sort");

    srand(s);
    randomize(list, n, LIST_VMIN, LIST_VMAX);
    bench_mark_listb(b, list, n);
    bench_start(SORT, b);
    insertion_sort(b, list, n);
    bench_end(b);
    bench_mark_lista(b, list, n);
    bench_print_statistics(b, "insertion sort");

    srand(s);
    randomize(list, n, LIST_VMIN, LIST_VMAX);
    bench_mark_listb(b, list, n);
    bench_start(SORT, b);
    insertion_sort_optimized(b, list, n);
    bench_end(b);
    bench_mark_lista(b, list, n);
    bench_print_statistics(b, "insertion sort -- swap optimized");

    return 0;
}
