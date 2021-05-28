#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  char *m[8][2];

  for(int j = 0; j < 2; j++){
    for(int i = 0; i < 8; i++){
      m[i][j] = (char *)slab_malloc(16 << i);
      printf("slab[%d][%d] ", i, j);
      printf("size: %d ", 16 << i);
      printf("va: %p ", m[i][j]);
      printf("pa: %p\n", slab_pa(m[i][j]));
    }
  }

  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 2; j++){
      slab_free(m[i][j]);
    }
  }
  exit(0);
}
