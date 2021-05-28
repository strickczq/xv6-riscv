#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sem.h"

int sh_var;

uint64
sys_sh_var_read(void)
{
  return sh_var;
}

uint64
sys_sh_var_write(void)
{
  int n;

  if(argint(0, &n) < 0)
    return -1;
  sh_var = n;
  return sh_var;
}

uint64
sys_sem_create(void)
{
  int initvalue;

  if(argint(0, &initvalue) < 0)
    return -1;
  return sem_create(initvalue);
}

uint64
sys_sem_free(void)
{
  int sid;

  if(argint(0, &sid) < 0)
    return -1;
  sem_free(sid);
  return 0;
}

uint64
sys_sem_p(void)
{
  int sid;

  if(argint(0, &sid) < 0)
    return -1;
  sem_p(sid);
  return 0;
}

uint64
sys_sem_v(void)
{
  int sid;

  if(argint(0, &sid) < 0)
    return -1;
  sem_v(sid);
  return 0;
}
