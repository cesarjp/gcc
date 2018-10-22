#include <assert.h>
#include <stdlib.h>

struct node
{
  struct node *next;
  int val;
};

int
sum_nodes (struct node *head)
{
  int i = 0, sum = 0;

#pragma acc parallel reduction(+:sum) present(head[:1])
  {
    for (; head != NULL; head = head->next)
      sum += head->val;
  }

  return sum;
}

void
insert (struct node *head, int val)
{
  struct node *n = (struct node *) malloc (sizeof (struct node));

  if (head->next)
    {
#pragma acc exit data detach(head->next)
    }
  
  n->val = val;
  n->next = head->next;
  head->next = n;

#pragma acc enter data copyin(n[:1])
#pragma acc enter data attach(head->next)
  if (n->next)
    {
#pragma acc enter data attach(n->next)
    }
}

void
destroy (struct node *head)
{
  while (head->next != NULL)
    {
#pragma acc exit data detach(head->next)
      struct node * n = head->next;
      head->next = n->next;
#pragma acc exit data detach(n->next)
#pragma acc exit data delete (n)
      if (head->next)
	{
#pragma acc enter data attach(head->next)
	}
      free (n);
    }
}

int
main ()
{
  struct node list = { .next = NULL, .val = 0 };
  int i;

#pragma acc enter data copyin(list)
  
  for (i = 0; i < 10; i++)
    insert (&list, 2);

  assert (sum_nodes (&list) == 10 * 2);

  destroy (&list);

#pragma acc exit data delete(list)

  return 0;
}
