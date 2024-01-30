/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:42:24 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/30 13:49:26 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*lonely_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->write_mutex);
	philo_write("has taken a fork", philo->id, philo);
	pthread_mutex_unlock(philo->write_mutex);
	better_usleep(philo->time_to_die);
	pthread_mutex_lock(philo->write_mutex);
	philo_write("died", philo->id, philo);
	pthread_mutex_unlock(philo->write_mutex);
	return (NULL);
}

int	pick_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
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
