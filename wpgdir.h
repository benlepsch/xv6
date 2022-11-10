#ifndef WALKPGDIR_H
#define WALKPGDIR_H

pte_t* walkpgdir(pde_t *pgdir, const void *va, int alloc);

#endif