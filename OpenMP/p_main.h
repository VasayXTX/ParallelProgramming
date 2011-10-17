#ifndef P_MAIN_H
#define P_MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>

int run_main(int argc, char *argv[], void (*f)(int, char *[], int *, size_t));
void run_sort(int *arr, size_t n, void (*f)(int *, size_t), char *title);

#endif
