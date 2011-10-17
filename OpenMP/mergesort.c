#include <string.h>

#include "mergesort.h"
#include "quicksort.h"

#define MERGE_LIM 1000

void merge(int *arr, size_t size, size_t a_size, size_t b_size)
{
  int i, j, k;
  int *a = arr, *b = arr + a_size;
  int *c;

  if (a[a_size-1] <= b[0]) return;

  c = (int *)malloc(b_size * sizeof(int));
  memcpy(c, b, b_size * sizeof(int));

  i = a_size - 1; j = b_size - 1; k = size - 1;
  while (i >= 0 && j >= 0)
  {
    if (a[i] > c[j])
      arr[k--] = a[i--];
    else 
      arr[k--] = c[j--];
  }
  while (j >= 0) arr[k--] = c[j--];
  free(c);
}

void smergesort(int *arr, size_t size)
{
  size_t a_size = size / 2;
  size_t b_size = size - a_size;

  if (size <= MERGE_LIM)
    sqsort(arr, size);
  else
  {
    if (size <= 1) return;
    smergesort(arr, a_size);
    smergesort(arr + a_size, b_size);
  }

  merge(arr, size, a_size, b_size);
}

void pmergesort(int *arr, size_t size)
{
  size_t a_size = size / 2;
  size_t b_size = size - a_size;

  if (size <= MERGE_LIM)
    sqsort(arr, size);
  else
  {
    if (size <= 1) return;
    #pragma omp parallel sections
    {
      #pragma omp section
      smergesort(arr, a_size);

      #pragma omp section
      smergesort(arr + a_size, b_size);
    }
  }

  merge(arr, size, a_size, b_size);
}

