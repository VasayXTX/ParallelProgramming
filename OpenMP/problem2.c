#include "p_main.h"
#include "quicksort.h"

#define SINGLE_TH "Quicksort. Single thread"
#define MULTI_TH_SEC "Quicksort. Multi threads using nested parallel regions"
#define MULTI_TH_TASK "Quicksort. Multi threads using tasks from OpenMP 3.0"

void handle(int argc, char *argv[], int *arr, size_t n);

int main(int argc, char *argv[])
{
  return run_main(argc, argv, handle);
}

void handle(int argc, char *argv[], int *arr, size_t n)
{
  if (argc < 4)
  {
    run_sort(arr, n, sqsort, SINGLE_TH);
  }
  else if (!strcmp(argv[3], "-ms"))
  {
    run_sort(arr, n, pqsort_sections, MULTI_TH_SEC);
  }
  else if (!strcmp(argv[3], "-mt"))
  {
    run_sort(arr, n, pqsort_tasks, MULTI_TH_TASK);
  }
  else if (!strcmp(argv[3], "-a"))
  {
    int *arr_foo = (int *)malloc(n * sizeof(int));
    memcpy(arr_foo, arr, n * sizeof(int));
    int *arr_bar = (int *)malloc(n * sizeof(int));
    memcpy(arr_bar, arr, n * sizeof(int));

    run_sort(arr, n, sqsort, SINGLE_TH);
    run_sort(arr_foo, n, pqsort_sections, MULTI_TH_SEC);
    run_sort(arr_bar, n, pqsort_tasks, MULTI_TH_TASK);

    free(arr_bar); free(arr_foo);
  }
  else exit(EXIT_FAILURE);
}

