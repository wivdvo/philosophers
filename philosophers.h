/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:45:28 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/25 12:18:06 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "ft_printf/ft_printf.h"
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	unsigned int	n_philo;


	int				*dead;

	size_t			time_last_meal;
	size_t			times_eaten;



	pthread_mutex_t	*r_fork;
	pthread_mutex_t *l_fork;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*check_mutex;
}	t_philo;

typedef struct s_main
{
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	unsigned int	n_times_must_eat;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	check_mutex;
	t_philo			*philo;
	unsigned int	n_philo;
	pthread_mutex_t	*forks;
	int				dead;
}	t_main;


int		ft_strcmp(const char *str1, const char *str2);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
void	put_error(char *str);
size_t	ft_strlen(char *str);
int		init_main_struct(t_main *main, int ac, char **av);
int		init_philos(t_main *main);
int		init_philo_struct(t_philo *philo, int *dead, char **av, int i);
void	philo_logic(t_philo *philo);
int		monitor_logic(t_main *main);
int		init_philos(t_main *main);
int		init_main_struct(t_main *main, int ac, char **av);
int		convert_and_check_input(char *str);
size_t	get_time(void);

#endif