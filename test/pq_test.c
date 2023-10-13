#include "mcl/mcl_da.h"
#include "mcl/mcl_pq.h"

#include "stdio.h"

#define ASSERT(x) \
{ \
  if (!(x)) \
  { \
    printf("Failed on line %d: %s\n", __LINE__, #x); \
    return EXIT_FAILURE; \
  } \
}

#define TEST_TARGET 1e6

typedef struct _data
{
  int val1;
  float val2;
} data;

int data_cmp(const data* d1, const data* d2)
{
  if (d1->val1 != d2->val1) return d1->val1 < d2->val1 ? -1 : 1;
  if (d1->val2 != d2->val2) return d1->val2 < d2->val2 ? -1 : 1;
  return 0;
}

MCL_DA(data)
MCL_PQ(data, data_cmp)

int main()
{
  struct mcl_da_data* da = NULL;
  struct mcl_pq_data* pq = NULL;
  int n;

  /* First create all of the data we're interested in. */
  for (n = 0; n < TEST_TARGET; n++)
  {
    data d = { n, (float)n / 2 };
    da = mcl_da_push_back_data(da, d);
  }

  /* Insert the data into a priority queue. */
  for (n = 0; n < TEST_TARGET; n++)
  {
    pq = mcl_pq_push_data(pq, da->data[n]);
  }

  /* Pop each of the elements and check it's the element we expect. */
  for (n = TEST_TARGET - 1; n >= 0; n--)
  {
    /* Check top. */
    ASSERT(memcmp(pq->top_val, &da->data[n], sizeof(data)) == 0);
    pq = mcl_pq_pop_data(pq);
  }

  return EXIT_SUCCESS;
}
