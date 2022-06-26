#include "memory.h"

#include <memory.h>
#include <stdlib.h>

mem_block_u16_t *mem_u16_init(u16 p_max_size) {
  mem_block_u16_t *l_block = malloc(sizeof (mem_block_u16_t));
  l_block->next = NULL;
  l_block->data = NULL;
  l_block->start = 0;
  l_block->end = p_max_size;

  return l_block;
}

void *mem_u16_alloc(
  mem_block_u16_t *p_mem_block,
  u16 p_size
) {
  const int l_calc = p_mem_block->start + p_size <= p_mem_block->end;
  if (p_mem_block->next == NULL && p_mem_block->data == NULL && l_calc) {
    mem_block_u16_t *l_block = malloc(sizeof(mem_block_u16_t));
    l_block->next = NULL;
    l_block->data = NULL;
    l_block->start = p_size + 1;
    l_block->end = p_mem_block->end;
    void *l_data = malloc(p_size);
    p_mem_block->data = l_data;
    p_mem_block->end = p_size;
    p_mem_block->next = l_block;
    return l_data;
  } else if (p_mem_block->next != NULL && l_calc) {
    return mem_u16_alloc(p_mem_block->next, p_size);
  } else {
    return NULL;
  }
}

void mem_u16_free(mem_block_u16_t *p_mem_block) {
  if (p_mem_block->next == NULL) {
    if (p_mem_block->data != NULL) {
      free(p_mem_block->data);
    }
  } else {
    mem_u16_free(p_mem_block->next);
    if (p_mem_block->data != NULL) {
      free(p_mem_block->data);
    }
  }
  free(p_mem_block);
}
