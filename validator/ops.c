#include "push_swap.h"

static void	swap(t_ps_llist **l)
{
  t_ps_llist	*a;
  t_ps_llist	*b;

  a = *l;
  b = a->next;
  a->next = b->next;
  a->next->prev = a;
  b->prev = a->prev;
  b->prev->next = b;
  b->next = a;
  a->prev = b;
  *l = b;
}

static void	push(t_ps_llist **dst, t_ps_llist **src)
{
  t_ps_llist	*elem;

  elem = *src;
  if (elem == NULL)
    return ;
  if (elem->next == elem)
    *src = NULL;
  else
    {
      elem->prev->next = elem->next;
      elem->next->prev = elem->prev;
      *src = elem->next;
    }
  if (*dst == NULL)
    {
      elem->prev = elem;
      elem->next = elem;
      *dst = elem;
    }
  else
    {
      elem->next = *dst;
      elem->prev = elem->next->prev;
      elem->next->prev = elem;
      elem->prev->next = elem;
    }
}

static void	rotate(t_ps_llist **l)
{
  if (*l == NULL)
    return ;
  *l = (*l)->next;
}

static void	rrotate(t_ps_llist **l)
{
  if (*l == NULL)
    return ;
  *l = (*l)->prev;
}

void		sa(t_ps_llist **la, t_ps_llist **lb)
{
  swap(la);
}

void		sb(t_ps_llist **la, t_ps_llist **lb)
{
  swap(lb);
}

void		sc(t_ps_llist **la, t_ps_llist **lb)
{
  swap(la);
  swap(lb);
}

void		pa(t_ps_llist **la, t_ps_llist **lb)
{
  push(la, lb);
}

void		pb(t_ps_llist **la, t_ps_llist **lb)
{
  push(lb, la);
}

void		ra(t_ps_llist **la, t_ps_llist **lb)
{
  rotate(la);
}

void		rb(t_ps_llist **la, t_ps_llist **lb)
{
  rotate(lb);
}

void		rr(t_ps_llist **la, t_ps_llist **lb)
{
  rotate(la);
  rotate(lb);
}

void		rra(t_ps_llist **la, t_ps_llist **lb)
{
  rrotate(la);
}

void		rrb(t_ps_llist **la, t_ps_llist **lb)
{
  rrotate(lb);
}

void		rrr(t_ps_llist **la, t_ps_llist **lb)
{
  rrotate(la);
  rrotate(lb);
}
