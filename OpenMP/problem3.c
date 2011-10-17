#include "p_main.h"
#include "mergesort.h"

#define SINGLE_TH "Mergesort. Single thread"
#define MULTI_TH_SEC "Mergesort. Multi threads using nested parallel regions"

void handle(int argc, char *argv[], int *arr, size_t n);

int main(int argc, char *argv[])
{
  return run_main(argc, argv, handle);
}

void handle(int argc, char *argv[], int *arr, size_t n)
{
  if (argc < 4)
  {
    run_sort(arr, n, smergesort, SINGLE_TH);
  }
  else if (!strcmp(argv[3], "-m"))
  {
    run_sort(arr, n, pmergesort, MULTI_TH_SEC);
  }
  else if (!strcmp(argv[3], "-a"))
  {
    int *arr_foo = (int *)malloc(n * sizeof(int));
    memcpy(arr_foo, arr, n * sizeof(int));

    run_sort(arr, n, smergesort, SINGLE_TH);
    run_sort(arr_foo, n, pmergesort, MULTI_TH_SEC);

    free(arr_foo);
  }
  else exit(EXIT_FAILURE);
}

