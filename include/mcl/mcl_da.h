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
struct mcl_da_##T* mcl_da_create_##T() \
{ \
  struct mcl_da_##T* da = malloc(sizeof(struct mcl_da_##T)); \
  da->size = 0; \
  da->max_size = MCL_DA_DEFAULT_SIZE; \
  da->data = malloc(da->max_size * sizeof(T)); \
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
} \
\
struct mcl_da_##T* mcl_da_push_back_##T(struct mcl_da_##T* const da, T val) \
{ \
  if (da->size + 1 > da->max_size) \
  { \
    T* resized_data = malloc(2 * da->max_size * sizeof(T)); \
    memcpy(resized_data, da->data, da->max_size * sizeof(T)); \
    free(da->data); \
    da->max_size <<= 1; \
    da->data = resized_data; \
  } \
  da->data[da->size++] = val; \
  return da; \
} \
\
struct mcl_da_##T* mcl_da_pop_back(struct mcl_da_##T* const da) \
{ \
  assert(da->size > 0); \
  da->size--; \
  return da; \
}

#endif /* __MCL_DA_INCLUDED__ */
