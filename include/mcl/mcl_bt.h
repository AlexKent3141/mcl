#ifndef __MCL_BT_INCLUDED__
#define __MCL_BT_INCLUDED__

#include "assert.h"
#include "stdlib.h"

#define MIN(x, y) (x < y ? x : y)

#define MCL_BT(T, cmp) \
struct mcl_bt_##T \
{ \
  struct mcl_bt_##T* left; \
  struct mcl_bt_##T* right; \
  T val; \
  int level; \
}; \
\
struct mcl_bt_##T* mcl_bt_split_##T(struct mcl_bt_##T* t) \
{ \
  if (t == NULL) return t; \
  if (t->right == NULL || t->right->right == NULL) return t; \
  if (t->level == t->right->right->level) \
  { \
    struct mcl_bt_##T* r = t->right; \
    t->right = r->left; \
    r->left = t; \
    r->level++; \
    return r; \
  } \
  return t; \
} \
\
struct mcl_bt_##T* mcl_bt_skew_##T(struct mcl_bt_##T* t) \
{ \
  if (t == NULL) return t; \
  if (t->left == NULL) return t; \
  if (t->left->level == t->level) \
  { \
    struct mcl_bt_##T* l = t->left; \
    t->left = l->right; \
    l->right = t; \
    return l; \
  } \
  return t; \
} \
\
struct mcl_bt_##T* mcl_bt_insert_##T(struct mcl_bt_##T* n, T val) \
{ \
  if (!n) \
  { \
    n = malloc(sizeof(struct mcl_bt_##T)); \
    n->left = NULL; \
    n->right = NULL; \
    n->val = val; \
    n->level = 1; \
    return n; \
  } \
  int c = cmp(&val, &n->val); \
  if (c < 0) n->left = mcl_bt_insert_##T(n->left, val); \
  else if (c > 0) n->right = mcl_bt_insert_##T(n->right, val); \
  else return n; \
  n = mcl_bt_skew_##T(n); \
  n = mcl_bt_split_##T(n); \
  return n; \
} \
\
struct mcl_bt_##T* mcl_bt_decrease_level_##T(struct mcl_bt_##T* n) \
{ \
  int should_be = n->left && n->right ? MIN(n->left->level, n->right->level) + 1 : 1; \
  if (should_be < n->level) \
  { \
    n->level = should_be; \
    if (n->right && should_be < n->right->level) n->right->level = should_be; \
  } \
\
  return n; \
} \
\
struct mcl_bt_##T* mcl_bt_predecessor_##T(struct mcl_bt_##T* n) \
{ \
  assert(n->left); \
  n = n->left; \
  while (n->right) n = n->right; \
  return n; \
} \
\
struct mcl_bt_##T* mcl_bt_successor_##T(struct mcl_bt_##T* n) \
{ \
  assert(n->right); \
  n = n->right; \
  while (n->left) n = n->left; \
  return n; \
} \
\
struct mcl_bt_##T* mcl_bt_delete_##T(struct mcl_bt_##T* n, T val) \
{ \
  if (!n) return n; \
  int c = cmp(&val, &n->val); \
  if (c < 0) n->left = mcl_bt_delete_##T(n->left, val); \
  else if (c > 0) n->right = mcl_bt_delete_##T(n->right, val); \
  else \
  { \
    if (n->left) \
    { \
      struct mcl_bt_##T* l = mcl_bt_predecessor_##T(n); \
      n->left = mcl_bt_delete_##T(n->left, l->val); \
      n->val = l->val; \
    } \
    else if (n->right) \
    { \
      struct mcl_bt_##T* l = mcl_bt_successor_##T(n); \
      n->right = mcl_bt_delete_##T(n->right, l->val); \
      n->val = l->val; \
    } \
    else return n->right; \
  } \
  n = mcl_bt_decrease_level_##T(n); \
  n = mcl_bt_skew_##T(n); \
  n->right = mcl_bt_skew_##T(n->right); \
  if (n->right) n->right->right = mcl_bt_skew_##T(n->right->right); \
  n = mcl_bt_split_##T(n); \
  n->right = mcl_bt_split_##T(n->right); \
  return n; \
} \
\
int mcl_bt_contains_##T(struct mcl_bt_##T* const n, T val) \
{ \
  if (n == NULL) return 0; \
  int c = cmp(&val, &n->val); \
  if (c == 0) return 1; \
  if (c < 0) return mcl_bt_contains_##T(n->left, val); \
  return mcl_bt_contains_##T(n->right, val); \
} \
\
int mcl_bt_size_##T(struct mcl_bt_##T* const n) \
{ \
  if (n == NULL) return 0; \
  return 1 + mcl_bt_size_##T(n->left) + mcl_bt_size_##T(n->right); \
}

#endif /* __MCL_BT_INCLUDED__ */
