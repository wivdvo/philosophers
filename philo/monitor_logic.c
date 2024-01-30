/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:39:24 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/30 19:17:57 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	case_dead(t_main *main, int i)
{
	main->dead = 1;
	pthread_mutex_unlock(&main->check_mutex);
	pthread_mutex_lock(&main->write_mutex);
	philo_write("died", i, &(main->philo)[i]);
	pthread_mutex_unlock(&main->write_mutex);
}

// int	case_done(t_main *main, int i)
// {
// 	int	j;
// 	int	count;

// 	j = 0;
// 	count = 0;
// 	main->philo[i].done = 1;
// 	while (j < main->n_philo)
// 	{
// 		count += main->philo[j].done;
// 		j++;
// 	}
// 	if (count != main->n_philo)
// 	{
// 		pthread_mutex_unlock(&main->check_mutex);
// 		return (0);
// 	}
// 	main->dead = 1;
// 	pthread_mutex_unlock(&main->check_mutex);
// 	pthread_mutex_lock(&main->write_mutex);
// 	philo_write("done", i, &(main->philo)[i]);
// 	pthread_mutex_unlock(&main->write_mutex);
// 	return (1);
// }

// void	*monitor_logic(void *arg)
// {
// 	t_main	*main;
// 	int		i;

// 	main = (t_main *)arg;
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < main->n_philo)
// 		{
// 			pthread_mutex_lock(&main->check_mutex);
// 			if (get_time() - main->philo[i].time_last_meal >= main->time_to_die)
// 				return (case_dead(main, i), NULL);
// 			else if (main->philo[i].times_eaten >= main->n_times_must_eat
// 				&& main->n_times_must_eat != 0)
// 			{
// 				if (case_done(main, i) == 1)
// 					return (NULL);
// 			}
// 			else
// 				pthread_mutex_unlock(&main->check_mutex);
// 			i++;
// 		}
// 	}
// }

int	check_done(t_main *main, int done_count)
{
	pthread_mutex_lock(&main->check_mutex);
	if (done_count >= main->n_philo)
	{
		main->dead = 1;
		pthread_mutex_unlock(&main->check_mutex);
		return (1);
	}
	pthread_mutex_unlock(&main->check_mutex);
	return (0);
}

void	*monitor_logic(void *arg)
{
	t_main	*main;
	int		i;
	int		done_count;

	main = (t_main *)arg;
	while (1)
	{
		i = 0;
		done_count = 0;
		while (i < main->n_philo)
		{
			pthread_mutex_lock(&main->check_mutex);
			if (get_time() - main->philo[i].time_last_meal >= main->time_to_die)
				return (case_dead(main, i), NULL);
			else if (main->philo[i].times_eaten >= main->n_times_must_eat
				&& main->n_times_must_eat != 0)
			{
				done_count++;
			}
			pthread_mutex_unlock(&main->check_mutex);
			i++;
		}
		if (check_done(main, done_count))
			return (NULL);
	}
}
