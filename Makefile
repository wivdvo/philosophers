NAME = philosophers

SRCS = 	main.c \
init.c \
logic.c \
utils.c

OBJS = $(SRCS:.c=.o)

HEADERS = philosophers.h

CC = cc

RM = rm -rf

#CFLAGS = -Wall -Werro -Wextra

PRINTF = ft_printf/libftprintf.a


all: $(NAME)

$(PRINTF):
			make -C ft_printf

$(NAME):	$(OBJS)	$(PRINTF) $(HEADERS)
				$(CC) $(OBJS) $(CFLAGS) -g $(PRINTF) -o philosophers

clean:
				make clean -C ft_printf
				$(RM) $(OBJS)

fclean:		clean
				make fclean -C ft_printf
				$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re