#include "p_main.h"

#define _MAX_RAND (int)pow(10, 6)

#define BOOL int
#define TRUE 1
#define FALSE 0

int run_main(int argc, char *argv[], void (*f)(int, char *[], int *, size_t))
{
  int i;
  size_t n;
  int *arr;
  FILE *f_in, *f_out;

  BOOL is_file = FALSE;

  if (argc < 3) exit(EXIT_FAILURE);

  if (!strcmp(argv[1], "-r"))
  {
    /*Randomize data for computation*/
    n = atoi(argv[2]);

    arr = (int *)malloc(n * sizeof(int));
    if (!arr) exit(EXIT_FAILURE);

    for (i = 0; i < n; ++i) arr[i] = rand() % _MAX_RAND;
  }
  else
  {
    /*Read data from input file (argv[1]) and write result to output file (argv[2])*/
    char *name_f_in = argv[1];
    char *name_f_out = argv[2];

    f_in = fopen(name_f_in, "r");
    f_out = fopen(name_f_out, "w");
    if (!f_in || !f_out) exit(EXIT_FAILURE);

    fscanf(f_in, "%i", &n);

    arr = (int *)malloc(n * sizeof(int));
    if (!arr) exit(EXIT_FAILURE);

    for (i = 0; i < n; ++i)
      fscanf(f_in, "%i", &arr[i]);

    is_file = TRUE;
  }

  (*f)(argc, argv, arr, n);

  if (is_file)
  {
    for (i = 0; i < n; ++i)
      fprintf(f_out, "%i ", arr[i]);
    fprintf(f_out, "\n\n");

    fclose(f_in);
    fclose(f_out);
  }
  
  free(arr);

  return EXIT_SUCCESS;
}

void run_sort(int *arr, size_t n, void (*f)(int *, size_t), char *title)
{
  struct timeval t_begin, t_end;
  float t_diff;

  printf("%s\n", title);
  gettimeofday(&t_begin, NULL);
  (*f)(arr, n);
  gettimeofday(&t_end, NULL);
  t_diff = t_end.tv_sec - t_begin.tv_sec + 0.000001 * (t_end.tv_usec - t_begin.tv_usec);
  printf("Work time of sorting at %f seconds\n", t_diff);
}

