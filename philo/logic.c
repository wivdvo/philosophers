/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:49:18 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/31 10:55:00 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_write(char *s, int id, t_philo *philo)
{
	printf("%zu %d %s\n", (get_time() - philo->start_time), id, s);
}

void	eating_logic(t_philo *philo)
{
	pthread_mutex_lock(philo->write_mutex);
	philo_write("has taken a fork", philo->id, philo);
	philo_write("has taken a fork", philo->id, philo);
	philo_write("is eating", philo->id, philo);
	pthread_mutex_unlock(philo->write_mutex);
	pthread_mutex_lock(philo->check_mutex);
	philo->time_last_meal = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(philo->check_mutex);
	better_usleep(philo->time_to_eat, philo);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	return ;
}

void	sleeping_logic(t_philo *philo)
{
	pthread_mutex_lock(philo->write_mutex);
	philo_write("is sleeping", philo->id, philo);
	pthread_mutex_unlock(philo->write_mutex);
	better_usleep(philo->time_to_sleep, philo);
}

void	thinking_logic(t_philo *philo)
{
	pthread_mutex_lock(philo->write_mutex);
	philo_write("is thinking", philo->id, philo);
	pthread_mutex_unlock(philo->write_mutex);
	usleep(200);
}

void	*philo_logic(void *arg)
{
	t_philo	*philo;
	size_t	count;
	int		ret;

	count = 0;
	philo = (t_philo *)arg;
	while (1)
	{
		if (!check_logic(philo))
			return (NULL);
		ret = pick_fork(philo, count);
		count++;
		if (ret == 0)
			return (NULL);
		if (ret == 2)
			continue ;
		eating_logic(philo);
		if (!check_logic(philo))
			return (NULL);
		sleeping_logic(philo);
		if (!check_logic(philo))
			return (NULL);
		thinking_logic(philo);
	}
	return (NULL);
}
