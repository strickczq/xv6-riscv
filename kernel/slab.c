#include "param.h"
#include "types.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"
#include "slab.h"

struct slab slab[NSLAB];

void
slabinit(void)
{
  int i, size;
  for(i = 0, size = 16; i < NSLAB; i++, size *= 2){
    slab[i].obj_size = size;
    slab[i].obj_num = PGSIZE / size;
    slab[i].start_addr = (uint64)kalloc();
    memset(slab[i].used, 0, PGSIZE / 16);
  }
}

int
allocslab(pagetable_t pagetable, uint64 va, uint64 realsize)
{
  // Find the right slab.
  int i, size;
  for(i = 0, size = 16; i < NSLAB; i++, size *= 2)
    if(size >= realsize) break;
  // Illegal realsize.
  if(realsize <= 0 || realsize > size) return -1;
  // Find unused object offset.
  int j;
  for(j = 0; j < slab[i].obj_num; j++){
    if(!slab[i].used[j]) break;
  }
  // Map the slab object
  uint64 pa = slab[i].start_addr + j * slab[i].obj_size;
  if(mappages(pagetable, va, PGSIZE, pa, PTE_W|PTE_X|PTE_R|PTE_U) == 0){
    // Change state.
    slab[i].used[j] = 1;
    return j * slab[i].obj_size;
  } else return -1;
}

int
freeslab(pagetable_t pagetable, uint64 va)
{
  // Get original physical address.
  uint64 pa = walkaddr(pagetable, va) + (va & (PGSIZE - 1));
  // Find the origin slab and object offset.
  int i, j;
  for(i = 0; i < NSLAB; i++){
    if(slab[i].start_addr <= pa && pa < slab[i].start_addr + PGSIZE) break;
  }
  // Not found error.
  if(i == NSLAB) return -1;
  // Change state.
  j = (pa - slab[i].start_addr) / slab[i].obj_size;
  slab[i].used[j] = 0;
  // Unmap the slab object
  pte_t *pte = walk(pagetable, va, 0);
  *pte = 0;
  return -1;
}
