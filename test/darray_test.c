#include "mcl/mcl_dynamic_array.h"

#include "stdio.h"
#include "stdlib.h"

#define ASSERT(x) \
{ \
  if (!(x)) \
  { \
    printf("Failed on line %d: %s\n", __LINE__, #x); \
    return EXIT_FAILURE; \
  } \
}

/* Declares the vector struct for int elements. */
MCL_DARRAY_TYPE(int);

int main()
{
  struct MCL_DARRAY_int v;
  uint32_t i;
  int val, *val2;

  MCL_DARRAY_INIT(int, v, 8);

  for (i = 0; i < 16; i++) MCL_DARRAY_PUSH_BACK(int, v, i);

  ASSERT(MCL_DARRAY_SIZE(v) == 16);

  val = MCL_DARRAY_POP_BACK(v);
  ASSERT(val == 15);

  for (i = 0; i < MCL_DARRAY_SIZE(v); i++)
  {
    *MCL_DARRAY_AT(v, i) <<= 1;
  }

  val2 = MCL_DARRAY_AT(v, 5);

  ASSERT(*val2 == 10);

  *val2 = 20;

  val2 = MCL_DARRAY_AT(v, 5);
  ASSERT(*val2 == 20);

  ASSERT(MCL_DARRAY_SIZE(v) == 15);

  MCL_DARRAY_FREE(v);

  return EXIT_SUCCESS;
}
