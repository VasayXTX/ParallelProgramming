#include <pthread.h>
#include <semaphore.h>

#include "pthread_checker.h"

#define LIM 10

void *th_func_first(void *arg);
void *th_func_second(void *arg);

int counter;

sem_t bin_sem;

int main(int argc, char *argv[])
{
  pthread_t th_first, th_second;

  counter = 0;
  check_res(sem_init(&bin_sem, 0, 0), SEM_ERR_INIT, NULL);

  check_res(
      pthread_create(&th_first, NULL, th_func_first, NULL), TH_ERR_TMPL_CREATION, TH_FIRST);
  check_res(
    pthread_create(&th_second, NULL, th_func_second, NULL), TH_ERR_TMPL_CREATION, TH_SECOND);

  check_res(pthread_join(th_first, NULL), TH_ERR_TMPL_JOIN, TH_FIRST);
  check_res(pthread_join(th_second, NULL), TH_ERR_TMPL_JOIN, TH_SECOND);

  check_res(sem_destroy(&bin_sem), SEM_ERR_DESTROY, NULL);

  return EXIT_SUCCESS;
}

void *th_func_first(void *arg)
{
  int i;
  for (i = 2; i <= LIM; i += 2)
  {
    check_res(sem_wait(&bin_sem), SEM_ERR_WAIT, NULL);
    counter = i;
    printf("TH1: %i\n", counter);
  }
  pthread_exit(NULL);
}

void *th_func_second(void *arg)
{
  int i;
  for (i = 1; i <= LIM; i += 2)
  {
    counter = i;
    printf("TH2: %i\n", counter);
    check_res(sem_post(&bin_sem), SEM_ERR_POST, NULL);
    while (counter % 2) sleep(1);
  }
  pthread_exit(NULL);
}

