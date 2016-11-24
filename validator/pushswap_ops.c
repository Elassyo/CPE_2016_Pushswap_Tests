#include <stdlib.h>
#include <pushswap.h>

void	swap(t_llist *l)
{
  int	tmp;

  tmp = l->first->data;
  l->first->data = l->first->next->data;
  l->first->next->data = tmp;
}

void		push(t_llist *dst, t_llist *src)
{
  t_llist_node	*node;

  if (src->size == 0)
    return ;
  node = src->first;
  if (--src->size == 0)
    src->first = NULL;
  else
    {
      src->first->prev->next = src->first->next;
      src->first->next->prev = src->first->prev;
      src->first = src->first->next;
    }
  node->prev = dst->size == 0 ? node : dst->first->prev;
  node->next = dst->size == 0 ? node : dst->first;
  if (dst->size != 0)
    {
      dst->first->prev->next = node;
      dst->first->prev = node;
    }
  dst->first = node;
  dst->size++;
}

void	rotate(t_llist *l)
{
  l->first = l->first->next;
}

void	rrotate(t_llist *l)
{
  l->first = l->first->prev;
}



void	sa(t_llist *la, t_llist *lb)
{
  swap(la);
}

void	sb(t_llist *la, t_llist *lb)
{
  swap(lb);
}

void	sc(t_llist *la, t_llist *lb)
{
  swap(la);
  swap(lb);
}

void	pa(t_llist *la, t_llist *lb)
{
  push(la, lb);
}

void	pb(t_llist *la, t_llist *lb)
{
  push(lb, la);
}

void	ra(t_llist *la, t_llist *lb)
{
  rotate(la);
}

void	rb(t_llist *la, t_llist *lb)
{
  rotate(lb);
}

void	rr(t_llist *la, t_llist *lb)
{
  rotate(la);
  rotate(lb);
}

void	rra(t_llist *la, t_llist *lb)
{
  rrotate(la);
}

void	rrb(t_llist *la, t_llist *lb)
{
  rrotate(lb);
}

void	rrr(t_llist *la, t_llist *lb)
{
  rrotate(la);
  rrotate(lb);
}
