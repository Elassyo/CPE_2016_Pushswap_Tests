#ifndef PUSH_SWAP_H_
# define PUSH_SWAP_H_

# define PS_MAX_FUNCS 11

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct		s_ps_llist
{
  int			data;
  struct s_ps_llist	*prev;
  struct s_ps_llist	*next;
}			t_ps_llist;

typedef struct	s_ps_funcmap
{
  char		*opcode;
  void		(*opfunc)(t_ps_llist **la, t_ps_llist **lb);
}		t_ps_funcmap;

void	sa(t_ps_llist **la, t_ps_llist **lb);
void	sb(t_ps_llist **la, t_ps_llist **lb);
void	sc(t_ps_llist **la, t_ps_llist **lb);
void	pa(t_ps_llist **la, t_ps_llist **lb);
void	pb(t_ps_llist **la, t_ps_llist **lb);
void	ra(t_ps_llist **la, t_ps_llist **lb);
void	rb(t_ps_llist **la, t_ps_llist **lb);
void	rr(t_ps_llist **la, t_ps_llist **lb);
void	rra(t_ps_llist **la, t_ps_llist **lb);
void	rrb(t_ps_llist **la, t_ps_llist **lb);
void	rrr(t_ps_llist **la, t_ps_llist **lb);

#endif /* !PUSH_SWAP_H_ */
