#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  printf("Hello, world!\n");
  printf("my pid: %d\n", getpid());
  exit(0);
}
