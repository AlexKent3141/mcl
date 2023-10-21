#include "mcl/mcl_ll.h"

#include "stdio.h"

#define ASSERT(x) \
{ \
  if (!(x)) \
  { \
    printf("Failed on line %d: %s\n", __LINE__, #x); \
    abort(); \
  } \
}

MCL_LL(int);

/* Structure of this test:
 * - Insert N elements in random order
 * - Remove elements in random order, checking each time that we have the expected number of
 *   elements remaining.
 */

#define SEED 0xDEADBEEF
#define MAX_ELEMENTS 1e3

struct mcl_ll_int* run_insertion_test()
{
  struct mcl_ll_int* l = NULL;
  int i, val;
  for (i = 0; i < MAX_ELEMENTS; i++)
  {
    val = rand();
    struct mcl_ll_node_int* insert_point = l ? l->head : NULL;
    if (insert_point)
    {
      insert_point = mcl_ll_advance_int(insert_point, rand() % mcl_ll_size_int(l));
    }

    l = mcl_ll_insert_after_node_int(l, insert_point, val);
    ASSERT(l);
    ASSERT(l->tail->val = val);
    ASSERT(mcl_ll_size_int(l) == i + 1);
  }

  return l;
}

void run_removal_test(struct mcl_ll_int* l)
{
  int i;
  for (i = 0; i < MAX_ELEMENTS; i++)
  {
    struct mcl_ll_node_int* removal_point = l ? l->head : NULL;
    if (removal_point)
    {
      int offset = rand() % mcl_ll_size_int(l);
      removal_point = mcl_ll_advance_int(removal_point, offset);
    }

    l = mcl_ll_remove_int(l, removal_point);
    ASSERT(l);
    ASSERT(mcl_ll_size_int(l) == MAX_ELEMENTS - i - 1);
  }
}

int main()
{
  int t;
  srand(SEED);

  for (t = 0; t < 10; t++)
  {
    struct mcl_ll_int* l = run_insertion_test();
    run_removal_test(l);
  }

  return EXIT_SUCCESS;
}
