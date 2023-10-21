#ifndef __MCL_LL_INCLUDED__
#define __MCL_LL_INCLUDED__

#include "assert.h"
#include "stdlib.h"

#define MCL_LL(T) \
struct mcl_ll_node_##T \
{ \
  struct mcl_ll_node_##T* prev, *next; \
  T val; \
}; \
\
struct mcl_ll_##T \
{ \
  struct mcl_ll_node_##T* head, *tail; \
}; \
\
/* Create a new node with this value and insert after the given node.
 * If `n` is NULL it signals that the node should go before the current head
 * (and become the head of the list).
 */ \
struct mcl_ll_##T* mcl_ll_insert_after_node_##T( \
  struct mcl_ll_##T* l, \
  struct mcl_ll_node_##T* n, \
  T val) \
{ \
  struct mcl_ll_node_##T* new_node = malloc(sizeof(struct mcl_ll_node_##T)); \
  new_node->prev = NULL; \
  new_node->next = NULL; \
  new_node->val = val; \
  if (!l) \
  { \
    l = malloc(sizeof(struct mcl_ll_##T)); \
    l->head = NULL; \
    l->tail = NULL; \
  } \
  if (!l->head && !l->tail) \
  { \
    l->head = new_node; \
    l->tail = new_node; \
    return l; \
  } \
  if (n == NULL) /* Become the head. */ \
  { \
    new_node->next = l->head; \
    l->head->prev = new_node; \
    l->head = new_node; \
    return l; \
  } \
  if (l->head == l->tail) \
  { \
    l->tail = new_node; \
    l->head->next = l->tail; \
    l->tail->prev = l->head; \
    return l; \
  } \
  if (n == l->tail) l->tail = new_node; \
  if (n->next) n->next->prev = new_node; \
  new_node->next = n->next; \
  n->next = new_node; \
  new_node->prev = n; \
  return l; \
} \
\
struct mcl_ll_##T* mcl_ll_remove_##T(struct mcl_ll_##T* const l, struct mcl_ll_node_##T* n) \
{ \
  if (!n) return l; \
  if (n == l->head) l->head = l->head->next; \
  if (n == l->tail) l->tail = l->tail->prev; \
  if (!l->head && !l->tail) return l; \
  if (n->prev) n->prev->next = n->next; \
  if (n->next) n->next->prev = n->prev; \
  return l; \
} \
\
struct mcl_ll_node_##T* mcl_ll_advance_##T(struct mcl_ll_node_##T* n, int offset) \
{ \
  if (!offset) return n; \
  while (offset-- > 0) n = n->next; \
  while (offset++ < 0) n = n->prev; \
  return n; \
} \
\
int mcl_ll_size_##T(const struct mcl_ll_##T* const l) \
{ \
  int count = 0; \
  struct mcl_ll_node_##T* n = l->head; \
  if (!n) return count; \
  do \
  { \
    ++count; \
    n = n->next; \
  } while (n); \
  return count; \
}

#endif /* __MCL_LL_INCLUDED__ */
