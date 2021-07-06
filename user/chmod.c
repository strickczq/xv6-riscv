#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 3){
    fprintf(2, "Usage: chmod mode file\n");
    exit(1);
  }
  if(chmod(atoi(argv[1]), argv[2]) < 0)
    fprintf(2, "chmod %s %s: failed\n", argv[1], argv[2]);
  exit(0);
}
