NAME = philo

SRCS = 	main.c \
init.c \
init2.c \
logic.c \
logic2.c \
logic3.c \
monitor_logic.c \
utils.c \
utils2.c \
free_utils.c

OBJS = $(SRCS:.c=.o)

CC = cc

RM = rm -rf

CFLAGS = -Wall -Werror -Wextra

PRINTF = ft_printf/libftprintf.a


all: $(NAME)

$(PRINTF):
				make -C ft_printf

$(NAME):	$(OBJS) $(PRINTF)
				$(CC) $(OBJS) $(CFLAGS) -g $(PRINTF) -o philo

clean:
				make clean -C ft_printf
				$(RM) $(OBJS)

fclean:		clean
				make fclean -C ft_printf
				$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
