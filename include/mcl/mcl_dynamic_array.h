#ifndef __MCL_DARRAY_INCLUDED_H__
#define __MCL_DARRAY_INCLUDED_H__

#include "assert.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#define MCL_DARRAY_TYPE(T) \
struct MCL_DARRAY_##T \
{ \
  uint32_t num_elts; \
  uint32_t max_size; \
  T* data; \
}

#define MCL_DARRAY_INIT(T_, vec_, max_size_) \
{ \
  vec_.num_elts = 0; \
  vec_.max_size = max_size_; \
  vec_.data = malloc(vec_.max_size * sizeof(T_)); \
}

#define MCL_DARRAY_FREE(vec_) \
{ \
  if (vec_.data != NULL) \
  { \
    free(vec_.data); \
    vec_.data = NULL; \
  } \
}

#define MCL_DARRAY_SIZE(vec_) vec_.num_elts

#define MCL_DARRAY_PUSH_BACK(T_, vec_, elt_) \
{ \
  if (vec_.num_elts + 1 > vec_.max_size) \
  { \
    T_* resized_data = malloc(2 * vec_.max_size * sizeof(T_)); \
    memcpy(resized_data, vec_.data, vec_.max_size * sizeof(T_)); \
    free(vec_.data); \
    vec_.max_size <<= 1; \
    vec_.data = resized_data; \
  } \
  vec_.data[vec_.num_elts++] = elt_; \
}

#define MCL_DARRAY_POP_BACK(vec_) \
({ \
   assert(vec_.num_elts > 0); \
   vec_.data[vec_.num_elts-- - 1]; \
})

#define MCL_DARRAY_FRONT(vec_) \
({ \
  assert(vec_.num_elts > 0); \
  vec_.data[0]; \
})

#define MCL_DARRAY_BACK(vec_) \
({ \
  assert(vec_.num_elts > 0); \
  vec_.data[0]; \
})

#define MCL_DARRAY_AT(vec_, idx_) \
({ \
  assert(vec_.num_elts >= idx_ + 1); \
  &vec_.data[idx_]; \
})

#endif /* __MCL_DARRAY_INCLUDED_H__ */
