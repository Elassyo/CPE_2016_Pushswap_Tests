CC	=	gcc

RM	=	rm -f

CFLAGS	=	-c

LDFLAGS	=

NAME	=	../validate

SRC	=	main.c	\
		ops.c

HDR	=	push_swap.h

OBJ	=	$(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c $(HDR)
	$(CC) $< $(CFLAGS) -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
