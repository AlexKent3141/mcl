#include "mcl/mcl_da.h"

#include "stdio.h"

#define ASSERT(x) \
{ \
  if (!(x)) \
  { \
    printf("Failed on line %d: %s\n", __LINE__, #x); \
    return EXIT_FAILURE; \
  } \
}

#define TARGET_SIZE 1e6

MCL_DA(int);

int main()
{
  struct mcl_da_int* v;
  int i, val;

  for (i = 0; i < TARGET_SIZE; i++)
  {
    v = mcl_da_push_back_int(v, i);
  }

  ASSERT(v->size == TARGET_SIZE);

  val = v->data[v->size - 1];
  v = mcl_da_pop_back(v);

  ASSERT(val == TARGET_SIZE - 1);
  ASSERT(v->size == TARGET_SIZE - 1);

  v = mcl_da_free_int(v);
  ASSERT(!v);

  return EXIT_SUCCESS;
}
