#include <pthread.h>
#include <math.h>

#include "pthread_checker.h"

#define ITER_COUNT (int)pow(10, 9)
#define SQRT_VAL 2

extern void check_res(int, char *, char *);

void *th_func_first(void *arg);
void *th_func_second(void *arg);

char buffer[MSG_BUF_SIZE];

int main(int argc, char *argv)
{
  pthread_t th_first, th_second;
  void *th_second_res;

  check_res(
      pthread_create(&th_first, NULL, th_func_first, NULL), TH_ERR_TMPL_CREATION, TH_FIRST);
  check_res(
    pthread_create(&th_second, NULL, th_func_second, (void *)&th_first), TH_ERR_TMPL_CREATION, TH_SECOND);

  check_res(pthread_join(th_second, &th_second_res), TH_ERR_TMPL_JOIN, TH_SECOND);
  
  printf(TH_TMPL_RESULT, (char *)th_second_res);

  return EXIT_SUCCESS;
}

void *th_func_first(void *arg)
{
  unsigned int i;
  double tmp;

  printf(TH_TMPL_CREATION, TH_FIRST);
  printf(TH_TMPL_WORK, TH_FIRST);
  for (i = 0; i < ITER_COUNT; ++i) tmp = i * sqrt(SQRT_VAL);

  sprintf(buffer, TH_TMPL_STOP, TH_FIRST);
  pthread_exit(buffer);
}

void *th_func_second(void *arg)
{
  void *th_first_res;

  printf(TH_TMPL_CREATION, TH_SECOND);
  check_res(pthread_join(*((pthread_t *)arg), &th_first_res), TH_ERR_TMPL_JOIN, "first");
  printf(TH_TMPL_RESULT, (char *)th_first_res);
  printf(TH_TMPL_WORK, TH_SECOND);

  sprintf(buffer, TH_TMPL_STOP, TH_SECOND);
  pthread_exit(buffer);
}

