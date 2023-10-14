#ifndef __MCL_DA_INCLUDED__
#define __MCL_DA_INCLUDED__

#include "assert.h"
#include "stdlib.h"
#include "string.h"

#define MCL_DA_DEFAULT_SIZE 1024

#define MCL_DA(T) \
struct mcl_da_##T \
{ \
  int size; \
  int max_size; \
  T* data; \
}; \
\
struct mcl_da_##T* mcl_da_push_back_##T(struct mcl_da_##T* da, T val) \
{ \
  if (!da) \
  { \
    da = malloc(sizeof(struct mcl_da_##T)); \
    da->size = 0; \
    da->max_size = MCL_DA_DEFAULT_SIZE; \
    da->data = malloc(da->max_size * sizeof(T)); \
  } \
  if (da->size + 1 > da->max_size) \
  { \
    da->max_size <<= 1; \
    da->data = realloc(da->data, da->max_size * sizeof(T)); \
  } \
  da->data[da->size++] = val; \
  return da; \
} \
\
struct mcl_da_##T* mcl_da_pop_back_##T(struct mcl_da_##T* const da) \
{ \
  assert(da && da->size > 0); \
  da->size--; \
  return da; \
} \
\
struct mcl_da_##T* mcl_da_free_##T(struct mcl_da_##T* const da) \
{ \
  if (da && da->data) \
  { \
    free(da->data); \
    da->data = NULL; \
  } \
  free(da); \
  return NULL; \
}

#endif /* __MCL_DA_INCLUDED__ */
