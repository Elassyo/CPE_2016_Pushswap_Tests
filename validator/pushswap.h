#ifndef PUSHSWAP_H_
# define PUSHSWAP_H_

# define PS_OP_COUNT 11

typedef struct		s_llist_node
{
  int			data;
  struct s_llist_node	*prev;
  struct s_llist_node	*next;
}			t_llist_node;

typedef struct		s_llist
{
  struct s_llist_node	*first;
  int			size;
}			t_llist;

void	swap(t_llist *l);
void	push(t_llist *dst, t_llist *src);
void	rotate(t_llist *l);
void	rrotate(t_llist *l);

void	sa(t_llist *la, t_llist *lb);
void	sb(t_llist *la, t_llist *lb);
void	sc(t_llist *la, t_llist *lb);
void	pa(t_llist *la, t_llist *lb);
void	pb(t_llist *la, t_llist *lb);
void	ra(t_llist *la, t_llist *lb);
void	rb(t_llist *la, t_llist *lb);
void	rr(t_llist *la, t_llist *lb);
void	rra(t_llist *la, t_llist *lb);
void	rrb(t_llist *la, t_llist *lb);
void	rrr(t_llist *la, t_llist *lb);

typedef struct s_ps_ops
{
  char		*code;
  void		(*func)(t_llist *la, t_llist *lb);
}		t_ps_ops;

#endif /* !PUSHSWAP_H_ */
