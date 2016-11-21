#include "push_swap.h"

t_ps_funcmap	g_ps_funcmap[PS_MAX_FUNCS] = {
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
  { "rrr", rrr }
};

int	oplen(char *out)
{
  int	len;

  len = 0;
  while (out[len] != ' ' && out[len] != '\n' && out[len] != 0)
    len++;
  return (len);
}

int		validate(t_ps_llist *la, int size, char *out)
{
  t_ps_llist	*lb;
  int		i;
  int		ops;

  lb = NULL;
  ops = 0;
  if (*out == ' ')
    {
      printf("syntax error: space at beginning of output");
      return (2);
    }
  while (*out != '\n' && *out != 0)
    {
      ops++;
      i = 0;
      while (i < PS_MAX_FUNCS)
	{
	  if (strncmp(out, g_ps_funcmap[i].opcode, oplen(out)) == 0)
	    {
	      g_ps_funcmap[i].opfunc(&la, &lb);
	      i = PS_MAX_FUNCS - 1;
	    }
	  out += oplen(out);
	  if (*out != ' ' && *out != '\n' && *out != 0)
	    {
	      printf("syntax error: missing space between ops");
	      return (2);
	    }
	  else if (*out == ' ')
	    {
	      out++;
	      if (*out == '\n' || *out == 0)
		{
		  printf("syntax error: space at end of output");
		  return (2);
		}
	    }
	  i++;
	}
    }
  if (*out != '\n')
    {
      printf("syntax error: no carriage return at end of sequence");
      return (2);
    }
  if (lb == NULL)
    {
      printf("error: list B not empty after operations");
      return (2);
    }
  i = 0;
  while (i++ < size - 1)
    {
      if (la->data > la->next->data)
	{
	  printf("error: list not sorted after operations");
	  return (2);
	}
      la = la->next;
    }
  printf("PASSED (%n ops)", ops);
  return (0);
}

t_ps_llist	*read_nbrs(int argc, char **argv)
{
  int		i;
  t_ps_llist	*nbrs;

  if (!(nbrs = malloc(argc * sizeof(t_ps_llist))))
    return (NULL);
  i = 0;
  while (i < argc)
    {
      nbrs[i].data = atoi(argv[i]);
      nbrs[i].prev = nbrs + (i - 1 + argc) % argc;
      nbrs[i].next = nbrs + (i + 1) % argc;
      i++;
    }
  return (nbrs);
}

char	*read_out()
{
  int	r_sz;
  int	off;
  int	buf_off;
  char	*buf;
  char	*tmp_buf;

  if (!(buf = malloc(65536)))
    return (NULL);
  off = 0;
  buf_off= 0;
  while ((r_sz = read(STDIN_FILENO, buf + off, 65536 - buf_off)) > 0)
    {
      off += r_sz;
      buf_off += r_sz;
      if (buf_off == 65536)
	{
	  if (!(tmp_buf = malloc(off + 65536)))
	    return (NULL);
	  memcpy(tmp_buf, buf, off);
	  free(buf);
	  buf = tmp_buf;
	  buf_off = 0;
	}
    }
  buf[off] = 0;
  return (buf);
}

int		main(int argc, char **argv)
{
  int		ret;
  char		*out;
  t_ps_llist	*nbrs;

  if (argc < 2)
    {
      printf("usage: ./pushswap n_1 n_2 ... n_i | %s n_1 n_2 ... n_i\n", argv[0]);
      return (1);
    }
  nbrs = read_nbrs(argc - 1, argv + 1);
  out = read_out();
  if (!nbrs || !out)
    {
      printf("error: malloc failed");
      return (2);
    }
  ret = validate(nbrs, argc - 1, out);
  free(nbrs);
  free(out);
  return (ret);
}
