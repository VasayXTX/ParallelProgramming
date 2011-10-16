#ifndef PTHREAD_CHECKER_H
#define PTHREAD_CHECKER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/***************** Threads *****************/

#define TH_ERR_TMPL_CREATION "Thread creation failed: %s"
#define TH_ERR_TMPL_JOIN "Thread join failed: %s"

#define TH_TMPL_CREATION "Creation of thread: %s\n"
#define TH_TMPL_WORK "Working of thread: %s\n"
#define TH_TMPL_STOP "Stop of thread: %s"
#define TH_TMPL_RESULT "Result: %s\n"

#define TH_FIRST "first"
#define TH_SECOND "second"
#define TH_THIRD "third"

/***************** Semaphores *****************/

#define SEM_ERR_INIT "Semaphore initialization failed"
#define SEM_ERR_WAIT "Semaphore waiting failed"
#define SEM_ERR_POST "Semaphore posting failed"
#define SEM_ERR_DESTROY "Semaphore destruction failed"

/**********************************************/

#define MSG_BUF_SIZE 1024
#define TRUE 1
#define FALSE 0
#define BOOL int

void check_res(int res, char *msg_template, char *name)
{
  if (res != 0)
  {
    printf(msg_template, name);  
    exit(EXIT_FAILURE);
  }
}

#endif

