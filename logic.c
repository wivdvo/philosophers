/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:49:18 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/26 17:27:56 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_write(char *s, int id)
{
	printf("%zu %d %s\n", get_time(), id, s);
	return (NULL);
}

void	*philo_logic(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->check_mutex);
		if (*philo->dead == 1)
		{
			pthread_mutex_lock(philo->write_mutex);
			philo_write("realized ded", philo->id);
			pthread_mutex_unlock(philo->write_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(philo->check_mutex);

		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->write_mutex);
		philo_write("hast taken left fork", philo->id);
		pthread_mutex_unlock(philo->write_mutex);

		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->write_mutex);
		philo_write("hast taken right fork", philo->id);
		pthread_mutex_unlock(philo->write_mutex);

		pthread_mutex_lock(philo->write_mutex);
		philo_write("is eating", philo->id);
		pthread_mutex_unlock(philo->write_mutex);

		usleep(philo->time_to_eat);
		philo->times_eaten++;
		philo->time_last_meal = get_time();
	
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);

		pthread_mutex_lock(philo->check_mutex);
		if (*philo->dead == 1)
		{
			pthread_mutex_lock(philo->write_mutex);
			philo_write("realized ded", philo->id);
			pthread_mutex_unlock(philo->write_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(philo->check_mutex);
		

		pthread_mutex_lock(philo->write_mutex);
		philo_write("is sleeping", philo->id);
		pthread_mutex_unlock(philo->write_mutex);
		usleep(philo->time_to_sleep);

		pthread_mutex_lock(philo->write_mutex);
		philo_write("is thinking", philo->id);
		pthread_mutex_unlock(philo->write_mutex);



		
	}
	return (NULL);
}

void	*monitor_logic(void *arg)
{
	t_main *main = (t_main *)arg;
	int	i;
	while (1)
	{
		i = 0;
		while (i < main->n_philo)
		{
			if (get_time() - main->philo[i].time_last_meal >= main->time_to_die)
			{
				pthread_mutex_lock(&main->check_mutex);
				main->dead = 1;
				pthread_mutex_unlock(&main->check_mutex);
				pthread_mutex_lock(&main->write_mutex);
				philo_write("died", i);
				pthread_mutex_unlock(&main->write_mutex);
				return (NULL);
			}
			if (main->philo[i].times_eaten == main->n_times_must_eat)
			{
				pthread_mutex_lock(&main->check_mutex);
				main->dead = 1;
				pthread_mutex_unlock(&main->check_mutex);
				pthread_mutex_lock(&main->write_mutex);
				philo_write("done", i);
				pthread_mutex_unlock(&main->write_mutex);
				return (NULL);
			}
			i++;
		}
	}
}
