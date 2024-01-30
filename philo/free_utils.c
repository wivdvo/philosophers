/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:33:49 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/30 12:37:24 by wvan-der         ###   ########.fr       */
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
	main->dead = 1;
	while (i < main->n_philo)
		pthread_join(main->threads[i++], NULL);
	ft_free(main);
	put_error("thread create failed");
	return (1);
}

int	clean_up(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->n_philo)
		pthread_join(main->threads[i++], NULL);
	pthread_join(main->monitor, NULL);
	ft_free(main);
	return (1);
}
