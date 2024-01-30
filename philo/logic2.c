/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:38:00 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/30 12:38:58 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_logic(t_philo *philo)
{
	pthread_mutex_lock(philo->check_mutex);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->check_mutex);
		return (0);
	}
	else
		pthread_mutex_unlock(philo->check_mutex);
	return (1);
}

int	case_odd(t_philo *philo)
{
	pick_l_fork(philo);
	if (!check_logic(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		return (0);
	}
	pick_r_fork(philo);
	if (!check_logic(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	return (1);
}

int	case_even(t_philo *philo)
{
	pick_r_fork(philo);
	if (!check_logic(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	pick_l_fork(philo);
	if (!check_logic(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	return (1);
}
