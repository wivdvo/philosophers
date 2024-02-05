/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:33:49 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/31 14:49:50 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free(t_main *main)
{
	int	i;

	i = 0;
	if (main->threads)
	{
		free(main->threads);
		main->threads = NULL;
	}
	if (main->forks)
	{
		free(main->forks);
		main->forks = NULL;
	}
	if (main->philo)
	{
		free(main->philo);
		main->philo = NULL;
	}
}

int	monitor_create_failed(t_main *main)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&main->check_mutex);
	main->dead = 1;
	pthread_mutex_unlock(&main->check_mutex);
	usleep(2000);
	while (i < main->n_philo)
		pthread_join(main->threads[i++], NULL);
	clean_mutex(main, main->n_philo);
	ft_free(main);
	put_error("monitor thread create failed");
	return (1);
}

int	clean_up(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->n_philo)
		pthread_join(main->threads[i++], NULL);
	pthread_join(main->monitor, NULL);
	clean_mutex(main, main->n_philo);
	ft_free(main);
	return (1);
}

void	philo_threads_error(t_main *main)
{
	put_error("philo thread create failed\n");
	pthread_mutex_lock(&main->check_mutex);
	main->dead = 1;
	pthread_mutex_unlock(&main->check_mutex);
}
