#ifndef VM_H
#define VM_H

#include "types.h";

static int mappages(pde_t *pgdir, void *va, uint size, uint pa, int perm);

#endif