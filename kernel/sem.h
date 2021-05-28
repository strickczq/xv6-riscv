struct sem {
  struct spinlock lock;
  int resource_count;
  int *procs;
  int allocated;
};
