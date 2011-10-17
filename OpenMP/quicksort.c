#include <omp.h>
#include <stdio.h>

#include "quicksort.h"

#define _mid(a, x, y, z) ( ((a[z]) < (a[x])) ? (x) : ( ((a[y]) < (a[z])) ? (y) : (z) ) )

void swap(int *arr, int i_first, int i_second)
{
  int foo;
  foo = arr[i_first]; 
  arr[i_first] = arr[i_second]; 
  arr[i_second] = foo;
}

int median(int *a, int l, int h)
{
  int i = (l + h) / 2;
  return (a[l] < a[h]) ? _mid(a, l, h, i) : _mid(a, h, l, i);
}

int partition(int *arr, int low, int high)
{
  int j, x;
  int i = low - 1;
  swap(arr, high, median(arr, low, high));
  x = arr[high];

  for (j = low; j < high; ++j)
  {
    if (x >= arr[j])
    {
      ++i;
      swap(arr, i, j);
    }
  }
  swap(arr, i + 1, high);
  return i + 1;
}

/***************** QSort (Single thread || Using a Nested Rapallel Region) *****************/

void __qsort(int *arr, int low, int high)
{
  int q;
  if (low >= high) return;
  q = partition(arr, low, high);
  __qsort(arr, low, q - 1);
  __qsort(arr, q + 1, high);
}

void _qsort(int *arr, size_t size, int is_mt)
{
  int q;
  if (size <= 1 ) return;
  q = partition(arr, 0, size - 1);

  #pragma omp parallel sections if (is_mt) num_threads(2)
  {
    #pragma omp section
    __qsort(arr, 0, q - 1);
    
    #pragma omp section
    __qsort(arr, q + 1, size - 1);
  }
}

void sqsort(int *arr, size_t n)
{
  _qsort(arr, n, 0);
}

void pqsort_sections(int *arr, size_t n)
{
  _qsort(arr, n, 1);
}

/***************** QSort (Using a Task from OpenMP 3.0) *****************/

void _pqsort_tasks(int *arr, int low, int high)
{
  int q;
  if (low >= high) return;
  q = partition(arr, low, high);

  #pragma omp task
  _pqsort_tasks(arr, low, q - 1);

  #pragma omp task
  _pqsort_tasks(arr, q + 1, high);
}

void pqsort_tasks(int *arr, size_t size)
{
  #pragma omp parallel
  {
    #pragma omp single nowait
    _pqsort_tasks(arr, 0, size - 1);
  }
}

