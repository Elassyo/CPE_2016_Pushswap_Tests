CC	=	gcc

RM	=	rm -f

CFLAGS	=	-g -c -O3 -I.

LDFLAGS	=

NAME	=	../validate

SRC	=	validator.c	\
		pushswap_ops.c

HDR	=	pushswap.h

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
