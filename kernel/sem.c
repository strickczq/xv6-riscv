// Semaphore.

#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "sem.h"

int sem_used = 0;
struct sem sem[MAXSEM];

// initialize the sem at boot time.
void
seminit(void)
{
  int sid;
  for(sid = 0; sid < MAXSEM; sid++){
    initlock(&sem[sid].lock, "semaphore");
    sem[sid].allocated = 0;
  }
}

int
sem_create(int initvalue)
{
  int sid;
  for(sid = 0; sid < MAXSEM; sid++){
    acquire(&sem[sid].lock);
    if(sem[sid].allocated == 0){
      sem[sid].allocated = 1;
      sem[sid].resource_count = initvalue;
      release(&sem[sid].lock);
      return sid;
    }
    release(&sem[sid].lock);
  }
  return 0;
}

void
sem_free(int sid)
{
  acquire(&sem[sid].lock);
  sem[sid].allocated = 0;
  sem[sid].resource_count = 0;
  sem[sid].procs = 0;
  release(&sem[sid].lock);
}

void
sem_p(int sid)
{
  acquire(&sem[sid].lock);
  sem[sid].resource_count--;
  if(sem[sid].resource_count < 0)
    sleep(&sem[sid], &sem[sid].lock);
  release(&sem[sid].lock);
}

void
sem_v(int sid)
{
  acquire(&sem[sid].lock);
  sem[sid].resource_count++;
  if(sem[sid].resource_count < 1)
    wakeup1p(&sem[sid]);
  release(&sem[sid].lock);
}
