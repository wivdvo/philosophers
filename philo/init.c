/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:57:35 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/31 14:57:36 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philo_struct(t_philo *philo, int *dead, char **av, int i)
{
	(void)i;
	philo->dead = dead;
	philo->done = 0;
	philo->n_philo = convert_and_check_input(av[1]);
	philo->time_last_meal = 0;
	philo->times_eaten = 0;
	philo->write_mutex = NULL;
	philo->check_mutex = NULL;
	if (philo->n_philo == 0)
		return (0);
	philo->time_to_die = convert_and_check_input(av[2]);
	if (philo->time_to_die == 0)
		return (0);
	philo->time_to_eat = convert_and_check_input(av[3]);
	if (philo->time_to_eat == 0)
		return (0);
	philo->time_to_sleep = convert_and_check_input(av[4]);
	if (philo->time_to_sleep == 0)
		return (0);
	return (1);
}

int	init_main_struct(t_main *main, int ac, char **av)
{
	t_philo	*philo;
	int		i;

	i = 0;
	main->dead = 0;
	main->forks = NULL;
	philo = NULL;
	main->threads = NULL;
	main->n_times_must_eat = 0;
	if (put_input_in_main(main, ac, av) == 0)
		return (0);
	philo = (t_philo *)malloc(sizeof(t_philo) * main->n_philo);
	if (!philo)
		return (0);
	while (i < main->n_philo)
	{
		if (init_philo_struct(&philo[i], &main->dead, av, i) == 0)
			return (free(philo), 0);
		i++;
	}
	main->philo = philo;
	return (1);
}

int	give_mutexes_make_forks(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->n_philo)
	{
		main->philo[i].write_mutex = &main->write_mutex;
		main->philo[i].check_mutex = &main->check_mutex;
		if (pthread_mutex_init(&(main->forks)[i], NULL) != 0)
			return (clean_mutex(main, i), 0);
		i++;
	}
	return (1);
}

int	create_threads(t_main *main, size_t start_time)
{
	int	i;

	i = 0;
	while (i < main->n_philo)
	{
		main->philo[i].r_fork = &main->forks[i];
		main->philo[i].l_fork = &main->forks[(i + 1) % main->n_philo];
		main->philo[i].start_time = start_time;
		main->philo[i].time_last_meal = start_time;
		main->philo[i].id = i;
		if (pthread_create(&main->threads[i], NULL,
				&philo_logic, &(main->philo)[i]) != 0)
		{
			philo_threads_error(main);
			i--;
			while (i >= 0)
			{
				pthread_join(main->threads[i], NULL);
				i--;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philos(t_main *main)
{
	size_t		start_time;

	main->threads = (pthread_t *)malloc(sizeof(pthread_t) * main->n_philo);
	if (!main->threads)
		return (ft_free(main), 0);
	main->forks = malloc(sizeof(pthread_mutex_t) * main->n_philo);
	if (!main->forks)
		return (ft_free(main), 0);
	if (pthread_mutex_init(&main->write_mutex, NULL) != 0)
		return (ft_free(main), 0);
	if (pthread_mutex_init(&main->check_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&main->write_mutex), ft_free(main), 0);
	if (give_mutexes_make_forks(main) != 1)
		return (ft_free(main), 0);
	start_time = get_time();
	if (main->n_philo == 1)
		return (handle_lonely_philo(main, start_time), 1);
	if (create_threads(main, start_time) == 0)
		return (clean_mutex(main, main->n_philo), ft_free(main), 0);
	if (pthread_create(&main->monitor, NULL, &monitor_logic, main) != 0)
		return (monitor_create_failed(main), 0);
	clean_up(main);
	return (1);
}
