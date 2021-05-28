#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "slab.h"

uint64
sys_slab_malloc(void)
{
  int size;

  if(argint(0, &size) < 0)
    return -1;
  struct proc *p = myproc();
  int offset = allocslab(p->pagetable, p->sz, size);
  uint64 oldsize = p->sz;
  p->sz += PGSIZE;
  return oldsize + offset;
}

uint64
sys_slab_free(void)
{
  uint64 va;

  if(argaddr(0, &va) < 0)
    return -1;
  struct proc *p = myproc();
  return freeslab(p->pagetable, va);
}

uint64
sys_slab_pa(void)
{
  uint64 va;

  if(argaddr(0, &va) < 0)
    return -1;
  struct proc *p = myproc();
  return walkaddr(p->pagetable, va) + (va & (PGSIZE - 1));
}
