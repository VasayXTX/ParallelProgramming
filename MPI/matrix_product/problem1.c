#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <time.h>

#define BOOL int
#define TRUE 1
#define FALSE 0
#define uint unsigned int

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/*Structure to represent the block*/

struct Block
{
  uint r_low_first, r_low_second;
  uint c_low_first, c_low_second;
  size_t r_num_first, c_num_second;
  size_t r_c_num;
};
#define BLOCK struct Block

/*Params of the matrix*/

#define N (size_t)pow(10, 3)
#define NN N * N
#define M 1
#define K 1

#define T int
#define T_MPI MPI_INT

#define VAL_A 1
#define VAL_B 2
#define VAL_C 2000

/*Implementation*/

void generate_mat(T *mat, size_t num, T val)
{
  for (size_t i  = 0; i < num; ++i)
    mat[i] = val;
}

BOOL check_res(T *mat, size_t num, T val)
{
  for (size_t i = 0; i < num; ++i)
    if (mat[i] != VAL_C) return FALSE;
  return TRUE;
}

int main(int argc, char *argv[])
{
  int proc_num, proc_rank;
  MPI_Status status;

  size_t b_muls_num, b_col_num, b_row_num;
  BLOCK *b_muls;

  uint i, j, k, l;

  T *mat_a = (T *)malloc(NN * sizeof(T));
  T *mat_b = (T *)malloc(NN * sizeof(T));
  T *mat_c = (T *)malloc(NN * sizeof(T));

  generate_mat(mat_c, NN, 0);
  
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

  if (proc_rank == 0)
  {
    generate_mat(mat_a, NN, VAL_A);
    generate_mat(mat_b, NN, VAL_B);
  }

  MPI_Bcast(mat_a, NN, T_MPI, 0, MPI_COMM_WORLD);
  MPI_Bcast(mat_b, NN, T_MPI, 0, MPI_COMM_WORLD);

  b_muls_num = M * K * MAX(M, K);
  b_muls = (BLOCK *)malloc(b_muls_num * sizeof(BLOCK));
  b_row_num = N / K;  //Count of rows in the single block
  b_col_num = N / M;  //Count of cols in the single block
  for (l = i = 0; i < K; ++i)
  {
    uint row_low = i * b_row_num;
    uint row_num = (i == K - 1 ? N : (i + 1) * b_row_num) - row_low;  //Count of rows in the first matrix
    for (j = 0; j < M; ++j)
    {
      uint col_low = j * b_col_num;
      uint col_num = (j == M - 1 ? N : (j + 1) * b_col_num) - col_low;  //Count of cols/rows in the first/second matrix
      for (k = 0; k < K; ++k, ++l)
      {
        b_muls[l].r_low_first = row_low;
        b_muls[l].c_low_first = col_low;

        b_muls[l].r_low_second = col_low;
        b_muls[l].c_low_second = k * b_row_num;

        b_muls[l].r_num_first = row_num;
        b_muls[l].c_num_second = (k == K - 1 ? N : (k + 1) * b_row_num) - b_muls[l].c_low_second;
        b_muls[l].r_c_num = col_num;
      }
    }
  }

  for (l = proc_rank; l < b_muls_num; l += proc_num)
    for (i = b_muls[l].r_low_first; i < b_muls[l].r_low_first + b_muls[l].r_num_first; ++i)
      for (j = b_muls[l].c_low_second; j < b_muls[l].c_low_second + b_muls[l].c_num_second; ++j)
        for (k = 0; k < b_muls[l].r_c_num; ++k)
          mat_c[i * N + j] += 
            mat_a[i * N + k + b_muls[l].c_low_first] * 
            mat_b[(k + b_muls[l].r_low_second) * N + j];
  
  if (proc_rank == 0)
  {
    T *foo = (T *)malloc(NN * sizeof(T));
    for (i = 1; i < proc_num; ++i)
    {
      MPI_Recv(foo, NN, T_MPI, i, 0, MPI_COMM_WORLD, &status);
      for (j = 0; j < N; ++j)
        for (k = 0; k < N; ++k)
          mat_c[j*N+k] += foo[j*N+k];
    }
    free(foo);
  }
  else
    MPI_Send(mat_c, NN, T_MPI, 0, 0, MPI_COMM_WORLD);

  MPI_Finalize();

  if (proc_rank == 0)
    printf("Result: %i\n", check_res(mat_c, NN, VAL_C));

  free(mat_a);
  free(mat_b);
  free(mat_c);

  return EXIT_SUCCESS;
}

