#include "kernel/types.h"
#include "user/user.h"

void fn(void *i)
{
  printf("%x\n", i);
}

int
main(int argc, char *argv[])
{
  for(int i=0; i<16; i++){
    uint64 arg = i;
    if(clone() == 0){
      fn((void *)arg);
      t_exit(0);
    }
  }
  wait(0);
  exit(0);
}
