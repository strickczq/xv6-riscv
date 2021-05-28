#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{  
  int pid; 
  pid = getpid();
  chpri(pid, 19);
  printf("This is a test for priority scheduling!\n");
  printf("[started]  pid %d, priority %d\n", pid, 19);

  if((pid = fork()) != 0){
    chpri(pid, 15);
    printf("[started]  pid %d, priority %d\n", pid, 15);

    if((pid = fork()) != 0){
      chpri(pid, 15);
      printf("[started]  pid %d, priority %d\n", pid, 15);

      if((pid = fork()) != 0){
        chpri(pid, 5);
        printf("[started]  pid %d, priority %d\n", pid, 5);

        if((pid = fork()) != 0){
          chpri(pid, 5);
          printf("[started]  pid %d, priority %d\n", pid, 5);
        }
      }
    }
  }

  sleep(20);
  pid = getpid();
  int i, j, k, data[8];
  for(i = 0; i < 100; i++)
    for(j = 0; j < 1024 * 100; j++)
      for(k = 0; k < 1024; k++)
        data[k % 8] = pid * k;
  printf("[finished] pid %d, result %d\n", pid, data[pid]);
  exit(0);
}
