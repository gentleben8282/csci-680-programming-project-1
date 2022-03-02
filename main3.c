/* CSCI 680: Programming Project #1: Process Scheduling
 * Programmer (Student ID): Ben Corriette (@02956064)
 * Last modified date: 03/02/2022
 * 
 * Summary: A program that simulates the execution of a stream
 * of interactive processes by a laptop with a very large 
 * memory, a quad-core processor and one hard drive.
 *
 * References:
https://github.com/gentleben8282/csci-401-lab-2-intro-to-processes/
https://stackoverflow.com/questions/10909011/how-to-use-fork-to-create-only-2-child-processes
 */ 

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


void ChildProcess()
{
  printf("A child process (PID # %d) has been created from its parent process (PID # %d)\n", getpid(), getppid());
  exit(0);
}

void ParentProcess()
{ 
  int childStatus;
  int terminatedChildPid = wait(&childStatus);
  
  if (terminatedChildPid > -1) {
    printf("A child process (PID # %d) has terminated\n", terminatedChildPid); 
  }
  else {
    perror("A child process has not been successfully terminated.");
    exit(EXIT_FAILURE);
  }
}

int main()
{
	int i;
  int sleep_status;
  int sleep_duration = 10;
  int number_of_processes = 4;
  pid_t process_id = -1;

  if (process_id == -1) {
    printf("Four foreground processes will be created, run for 10 seconds, then terminate...\n");
  }
 
  for (i = 0; i < number_of_processes; ++i) {
    process_id = fork();
    if (process_id > 0) {   /* I am the parent, create more children */
      continue;
    } else if (process_id == 0) { /* I am a child, get to work */
      ChildProcess();
    } else {
      perror("An error has occurred while forking the process.");
      exit(EXIT_FAILURE);
    }
  }

  if (i == 4) {
    sleep_status = sleep(sleep_duration);
    if (sleep_status == 0) {
        while (number_of_processes > 0) {
          number_of_processes--;
          ParentProcess();
        }
    }
  }
   
  return 0;
}