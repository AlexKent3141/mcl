#ifndef __MCL_PQ_INCLUDED__
#define __MCL_PQ_INCLUDED__

#include "mcl/mcl_bt.h"

/* Priority queue is implemented by wrapping the binary tree we already have and adding
   some extra functions to shortcut access the left-most element. */
#define MCL_PQ(T, cmp) \
MCL_BT(T, cmp) \
struct mcl_pq_##T \
{ \
  struct mcl_bt_##T* bt; \
  T* top_val; \
}; \
\
struct mcl_pq_##T* mcl_pq_push_##T(struct mcl_pq_##T* n, T val) \
{ \
  if (!n) \
  { \
    n = malloc(sizeof(struct mcl_pq_##T)); \
    n->bt = NULL; \
    n->top_val = NULL; \
  } \
  if (!n->top_val) \
  { \
    n->top_val = malloc(sizeof(T)); \
    *n->top_val = val; \
  } \
  else if (cmp(&val, n->top_val) > 0) *n->top_val = val; \
  n->bt = mcl_bt_insert_##T(n->bt, val); \
  return n; \
} \
\
struct mcl_pq_##T* mcl_pq_pop_##T(struct mcl_pq_##T* n) \
{ \
  n->bt = mcl_bt_delete_##T(n->bt, *n->top_val); \
  struct mcl_bt_##T* bt = n->bt; \
  if (!bt) \
  { \
    n->top_val = NULL; \
    return n; \
  } \
  while (bt->right) bt = bt->right; \
  *n->top_val = bt->val; \
  return n; \
}

#endif /* __MCL_PQ_INCLUDED__ */
