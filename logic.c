/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:49:18 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/25 13:21:43 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_write(char *s, int id)
{
	printf("Philo %d %s\n", id, s);
}

void	philo_logic(t_philo *philo)
{
	while (1)
	{
		if (*philo->dead == 1)
			return ;
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->write_mutex);
		philo_write("is eating", philo->id);
		pthread_mutex_unlock(philo->write_mutex);
		//pthread_mutex_lock(philo->check_mutex);


		
	}
}

int	monitor_logic(t_main *main)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < main->n_philo)
		{
			if (get_time() - main->philo[i].time_last_meal >= main->time_to_die)
			{
				main->dead = 1;
				return (printf("philo %d died:(", i), 0);
			}
			if (main->philo[i].times_eaten == main->n_times_must_eat)
			{
				main->dead = 1;
				return (printf("sim ended"), 1);
			}
			i++;
		}
	}
}
