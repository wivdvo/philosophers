/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:42:24 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/31 14:10:27 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*lonely_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->write_mutex);
	printf("%zu 0 has taken a fork\n", get_time() - philo->start_time);
	pthread_mutex_unlock(philo->write_mutex);
	better_usleep(philo->time_to_die, philo);
	pthread_mutex_lock(philo->write_mutex);
	printf("%zu 0 died\n", get_time() - philo->start_time);
	pthread_mutex_unlock(philo->write_mutex);
	return (NULL);
}

int	pick_fork(t_philo *philo, size_t count)
{
	if (count == 0)
	{
		if (philo->id % 2 == 0)
			return (case_even(philo));
		else
			return (better_usleep(philo->time_to_eat - 5, philo), 2);
	}
	(void)count;
	if (philo->id % 2 == 0)
		return (case_even(philo));
	else
		return (case_odd(philo));
}

void	pick_l_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
}

void	pick_r_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
}
