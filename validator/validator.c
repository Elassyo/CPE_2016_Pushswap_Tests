#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pushswap.h>

const t_ps_ops	op_map[PS_OP_COUNT] = {
  { "sa", sa },
  { "sb", sb },
  { "sc", sc },
  { "pa", pa },
  { "pb", pb },
  { "ra", ra },
  { "rb", rb },
  { "rr", rr },
  { "rra", rra },
  { "rrb", rrb },
  { "rrr", rrr },
};

int	op_len(char *str)
{
  int	len;

  len = 0;
  while (str[len] != ' ' && str[len] != '\n' && str[len] != '0')
    len++;
  return (len);
}

char	*read_stdin()
{
  int	rd_sz;
  int	off;
  int	boff;
  char	*buf;
  char	*btmp;

  if (!(buf = malloc(4096)))
    {
      fprintf(stderr, "./validate: malloc failed\n");
      return (NULL);
    }
  off = 0;
  boff = 0;
  while ((rd_sz = read(STDIN_FILENO, buf + off, 4096 - boff)) > 0)
    {
      off += rd_sz;
      boff += rd_sz;
      if (boff >= 4096)
	{
	  if (!(btmp = malloc(off + 4096)))
	    {
	      free(buf);
	      fprintf(stderr, "./validate: malloc failed\n");
	      return (NULL);
	    }
	  memcpy(btmp, buf, off);
	  free(buf);
	  buf = btmp;
	  boff = 0;
	}
    }
  buf[off] = 0;
  return (buf);
}

char	*stdin_to_optab(char *in)
{
  int	i;
  int	j;
  int	k;
  int	len;
  int	count;
  char	in_op;
  char	*tab;

  i = 0;
  in_op = 0;
  count = 0;
  if (*in == ' ')
    printf("Syntax error: space at beginning of sequence");
  while ((len = op_len(in + i)) > 0)
    {
      i += len;
      if (in[i] == ' ')
	i++;
      count++;
    }
  if (in[i] != '\n')
    {
      printf("Syntax error: %s at end of sequence", in[i] == ' ' ? "double space or space" : "no carriage return\n");
      return (NULL);
    }

  if (!(tab = malloc(count + 1)))
    {
      fprintf(stderr, "./validate: malloc failed\n");
      return (NULL);
    }
  i = 0;
  j = 0;
  while ((len = op_len(in + i)) > 0)
    {
      k = 0;
      while (k < PS_OP_COUNT && k != -1)
	{
	  if (strncmp(in + i, op_map[k].code, len) == 0)
	    {
	      tab[j++] = k;
	      k = -1;
	      break;
	    }
	  k++;
	}
      if (k != -1)
	{
	  printf("Error: unknown operation %.*s", len, in + i);
	  return (NULL);
	}
      i += len;
      if (in[i] == ' ')
	i++;
    }
  tab[j] = -1;
  return (tab);
}

t_llist_node	*get_nbr_nodes(int argc, char **argv)
{
  int		i;
  t_llist_node	*nodes;

  if (!(nodes = malloc(argc * sizeof(t_llist_node))))
    {
      fprintf(stderr, "./validate: malloc failed\n");
      return (NULL);
    }
  i = 0;
  while (i < argc)
    {
      nodes[i].data = atoi(argv[i]);
      nodes[i].prev = nodes + (i + argc - 1) % argc;
      nodes[i].next = nodes + (i + 1) % argc;
      i++;
    }
  return (nodes);
}

int		main(int argc, char **argv)
{
  int		i;
  char		*in;
  char		*tab;
  t_llist	la;
  t_llist	lb;
  t_llist_node	*nodes;
  t_llist_node	*current;

  if (argc < 2)
    {
      fprintf(stderr, "usage: ./validate NUMBER_LIST\n");
      return (1);
    }
  if (!(in = read_stdin()))
    return (1);
  if (!(tab = stdin_to_optab(in)))
    return (1);
  if (!(nodes = get_nbr_nodes(argc - 1, argv + 1)))
    return (1);
  la.first = nodes;
  la.size = argc - 1;
  lb.first = NULL;
  lb.size = 0;
  i = 0;
  while (tab[i] >= 0)
    op_map[tab[i++]].func(&la, &lb);
  if (lb.size != 0)
    {
      printf("Error: list B not empty after final operation");
      return (1);
    }
  current = la.first;
  while (current != la.first->prev)
    {
      if (current->data > current->next->data)
	{
	  printf("Error: list not sorted after final operation");
	  return (1);
	}
      current = current->next;
    }
  printf("PASSED (%d ops)", i);
  free(in);
  free(tab);
  free(nodes);
  return (0);
}
