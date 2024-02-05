/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:35:53 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/31 12:55:33 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	handle_lonely_philo(t_main *main, size_t start_time)
{
	main->philo[0].start_time = start_time;
	main->philo[0].time_last_meal = start_time;
	if (pthread_create(&main->threads[0], NULL,
			&lonely_philo, &main->philo[0]) == 0)
	{
		pthread_join(main->threads[0], NULL);
	}
	else
		put_error("thread creation failed");
	clean_mutex(main, main->n_philo);
	ft_free(main);
	return (1);
}

int	put_input_in_main(t_main *main, int ac, char **av)
{
	main->n_philo = convert_and_check_input(av[1]);
	if (main->n_philo == 0)
		return (0);
	main->time_to_die = convert_and_check_input(av[2]);
	if (main->time_to_die == 0)
		return (0);
	main->time_to_eat = convert_and_check_input(av[3]);
	if (main->time_to_eat == 0)
		return (0);
	main->time_to_sleep = convert_and_check_input(av[4]);
	if (main->time_to_sleep == 0)
		return (0);
	if (ac == 6)
	{
		main->n_times_must_eat = convert_and_check_input(av[5]);
		if (main->n_times_must_eat == -1)
			return (0);
	}
	return (1);
}
