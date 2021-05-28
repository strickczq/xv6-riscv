struct slab {
  uint64 obj_size;    // size per object
  uint64 obj_num;     // number of objects
  uint64 start_addr;       // address start
  char used[PGSIZE / 16];
};
