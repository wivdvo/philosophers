/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:49:18 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/29 16:20:26 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_write(char *s, int id, t_philo *philo)
{
	printf("%zu %d %s\n", (get_time() - philo->start_time), id, s);
}

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
	usleep(philo->time_to_eat * 1000);

	if (philo->id % 2 != 0)
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
	usleep(philo->time_to_sleep * 1000);
}

void	thinking_logic(t_philo *philo)
{
	pthread_mutex_lock(philo->write_mutex);
	philo_write("is thinking", philo->id, philo);
	pthread_mutex_unlock(philo->write_mutex);
	usleep(200);
}

void	*lonely_philo(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	pthread_mutex_lock(philo->write_mutex);
	philo_write("has taken a fork", philo->id, philo);
	pthread_mutex_unlock(philo->write_mutex);
	usleep(philo->time_to_die * 1000);
	pthread_mutex_lock(philo->write_mutex);
	philo_write("died", philo->id, philo);
	pthread_mutex_unlock(philo->write_mutex);
	return (NULL);
}

void	*philo_logic(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while (1)
	{
		if (!check_logic(philo))
			return (NULL);
		if (pick_fork(philo) == 0)
			return (NULL);
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

void	*monitor_logic(void *arg)
{
	t_main *main = (t_main *)arg;
	int	i;
	while (1)
	{
		i = 0;
		while (i < main->n_philo)
		{
			pthread_mutex_lock(&main->check_mutex);
			if (get_time() - main->philo[i].time_last_meal >= main->time_to_die)
			{
				main->dead = 1;
				pthread_mutex_unlock(&main->check_mutex);
				pthread_mutex_lock(&main->write_mutex);
				philo_write("died", i, &(main->philo)[i]);
				pthread_mutex_unlock(&main->write_mutex);
				return (NULL);
			}
			else if (main->philo[i].times_eaten == main->n_times_must_eat)
			{
				main->dead = 1;
				pthread_mutex_unlock(&main->check_mutex);
				pthread_mutex_lock(&main->write_mutex);
				philo_write("done", i, &(main->philo)[i]);
				pthread_mutex_unlock(&main->write_mutex);
				return (NULL);
			}
			else
				pthread_mutex_unlock(&main->check_mutex);
			i++;
		}
	}
}
