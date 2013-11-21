#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <assert.h>

#define true 1
#define false 0

#define PROCESSES 1

void producer(void)
{
  while(true)
  {
    // producing code here
    printf("Produced\n");
  }
}

void consumer(void)
{
  while(true)
  {
    // consuming code here
    printf("Consumed\n");
  }
}

void run_tests(void);

int main(void)
{
  run_tests();

  // something is going to happen here
  int id;
  for (int i = 0; i < PROCESSES; ++i)
  {
    id = fork();
    if(id < 0)
    {
      perror("Fork failed.\n");
      exit(1);
    }
    else if (id == 0)
    {
      //consumer();
      printf("Consumer (child) process started\n");
      exit(0);
    }
    else if (id > 0)
      printf("Producent (parent) process here\n");
  }
  //producer();
  // end of something happening here


  // finishing
  printf("Finished\n");

  return 0;
}

void run_tests(void)
{
  assert(true  == 1);
  assert(false == 0);
  assert(PROCESSES > 0);
}
