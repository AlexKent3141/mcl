#include "mcl/mcl_bt.h"
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
MCL_BT(data, data_cmp)

int main()
{
  struct mcl_bt_data* bt = NULL;
  struct mcl_da_data* da = NULL;
  int n;

  /* First create all of the data we're interested in. */
  for (n = 0; n < TEST_TARGET; n++)
  {
    data d = { n, (float)n / 2 };
    da = mcl_da_push_back_data(da, d);
  }

  /* Insert the data into a binary tree. */
  for (n = 0; n < TEST_TARGET; n++)
  {
    bt = mcl_bt_insert_data(bt, da->data[n]);
  }

  /* Check that all elements are present. */
  for (n = 0; n < TEST_TARGET; n++)
  {
    ASSERT(mcl_bt_contains_data(bt, da->data[n]));
  }

  for (n = 0; n < TEST_TARGET; n++)
  {
    bt = mcl_bt_delete_data(bt, da->data[n]);
    ASSERT(!mcl_bt_contains_data(bt, da->data[n]));
  }

  return EXIT_SUCCESS;
}
