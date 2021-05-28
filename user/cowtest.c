#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{  
  char *data = slab_malloc(128);
  strcpy(data, "hello world");
  int pid = forkcow();
  if(pid != 0) {
    printf("Parent pid: %d, ptr: %p, data: %s\n", getpid(), slab_pa(data), data);
    wait(&pid);
  } else {
    sleep(20);
    printf("Child  pid: %d, ptr: %p, data: %s\n", getpid(), slab_pa(data), data);
    printf("Writing...\n");
    strcpy(data, "copy on write");
    printf("Child  pid: %d, ptr: %p, data: %s\n", getpid(), slab_pa(data), data);
  }
  slab_free(data);
  exit(0);
}
