/*
User level thread library
Test of SJF policy

misuse case - we hope to catch it and not have undefined behavior

calling thread_join before creating it should cause an error
we print "thread_join failure"

*/

#include <ucontext.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <stdint.h>

#include "userthread.h"
#include "scheduler.h"

void f(void* args) {
  printf("thread running...\n");
}


int main() {
  int tid, tid2;

  if (thread_libinit(SJF) != 0) {
    return EXIT_FAILURE;
  }

  if (thread_join(tid) != 0) {
    printf("thread_join failure\n");
    return EXIT_FAILURE;
  }

  if (thread_join(tid2) != 0) {
    printf("thread_join failure\n");
    return EXIT_FAILURE;
  }

  if (thread_create(tid) != 0) {
    printf("thread_create failure\n");
    return EXIT_FAILURE;
  }

  if (thread_create(tid2) != 0) {
    printf("thread_create failure\n");
    return EXIT_FAILURE;
  }

  if (thread_libterminate() != 0) {
    return EXIT_FAILURE;
  } else {
    printf("terminated\n");
  }
  return EXIT_SUCCESS;
}
