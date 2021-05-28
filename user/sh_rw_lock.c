#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  sh_var_write(0);
  int sid = sem_create(1);
  int pid = fork();
  int i;
  for(i = 0; i < 100000; i++){
    sem_p(sid);
    sh_var_write(sh_var_read() + 1);
    sem_v(sid);
  }
  if(pid != 0){
    wait(&pid);
    sem_free(sid);
  }
  printf("sum = %d\n", sh_var_read());
  exit(0);
}
