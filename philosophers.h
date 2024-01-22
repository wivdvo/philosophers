/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:45:28 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/22 16:08:41 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "ft_printf/ft_printf.h"
# include <time.h>

typedef struct s_philo
{
	unsigned int	n_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	unsigned int	n_times_must_eat;

	int				sleeping;
	int				eating;
	int				dead;

	time_t			time_since_eating;
	time_t			times_eaten;

	
}	t_philo;

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

int	ft_strcmp(const char *str1, const char *str2);
int	ft_atoi(const char *str);
char	*ft_itoa(int n);
void	put_error(char *str);
size_t	ft_strlen(char *str);

#endif