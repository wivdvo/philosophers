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


all: $(NAME)


$(NAME):	$(OBJS)
				$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
