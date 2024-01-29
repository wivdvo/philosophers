# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 10:42:00 by wvan-der          #+#    #+#              #
#    Updated: 2023/09/22 15:09:33 by wvan-der         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRCS =		ft_printf.c ft_printf_x.c ft_printf_x_cap.c ft_printf_u.c \
			ft_printf_s.c ft_printf_p.c ft_printf_d.c ft_printf_c.c

OBJS =		$(SRCS:.c=.o)

CC = 		cc
RM =		rm -f
CFLAGS =	-Wall -Werror -Wextra

NAME =		libftprintf.a

all:		$(NAME)

$(NAME):	$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
