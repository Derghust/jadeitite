#ifndef JADEITITE_MEMORY_H
#define JADEITITE_MEMORY_H

#include "datatypes.h"

//======================================
//       Data types for memory
//======================================

typedef struct mem_block_u16_rt {
  u16 start, end;
  void *data;
  struct mem_block_u16_rt *next;
} mem_block_u16_t;

//======================================
//          Memory operators
//======================================

mem_block_u16_t *mem_u16_init(u16 p_max_size);
void *mem_u16_alloc(mem_block_u16_t *p_mem_block, u16 p_size);
void mem_u16_free(mem_block_u16_t *p_mem_block);

#endif //JADEITITE_MEMORY_H
