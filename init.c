/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:41:29 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/26 17:08:30 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	put_input_in_main(t_main *main, int ac, char **av)
{
	main->n_philo = convert_and_check_input(av[1]);
	if (main->n_philo == -1 || main->n_philo == 0)
		return (0);
	main->time_to_die = convert_and_check_input(av[2]);
	if (main->time_to_die == -1 || main->time_to_die == 0)
		return (0);
	main->time_to_eat = convert_and_check_input(av[3]);
	if (main->time_to_eat == -1 || main->time_to_eat == 0)
		return (0);
	main->time_to_sleep = convert_and_check_input(av[4]);
	if (main->time_to_sleep == -1 || main->time_to_sleep == 0)
		return (0);
	if (ac == 6)
	{
		main->n_times_must_eat = convert_and_check_input(av[5]);
		if (main->n_times_must_eat == -1)
			return (0);
	}
	return (1);
}

int	init_philo_struct(t_philo *philo, int *dead, char **av, int i)
{
	philo->id = i;
	philo->dead = dead;
	philo->n_philo = convert_and_check_input(av[1]);
	if (philo->n_philo == -1 || philo->n_philo == 0)
		return (0);
	philo->time_to_eat = convert_and_check_input(av[3]);
	if (philo->time_to_eat == -1 || philo->time_to_eat == 0)
		return (0);
	philo->time_to_sleep = convert_and_check_input(av[4]);
	if (philo->time_to_sleep == -1 || philo->time_to_sleep == 0)
		return (0);
	return (1);
}

int	init_main_struct(t_main *main, int ac, char **av)
{
	t_philo *philo;
	int	i;

	i = 0;
	main->dead = 0;
	if (put_input_in_main(main, ac, av) == 0)
		return (0);
	philo = (t_philo *)malloc(sizeof(t_philo) * main->n_philo);
	if (!philo)
		return (0);
	while (i < main->n_philo)
	{
		if (init_philo_struct(&philo[i], &main->dead, av, i) == 0)
			return (0);
		i++;
	}
	main->philo = philo;
	return (1);
}

int	init_philos(t_main *main)
{
	pthread_t	*threads;
	pthread_t	monitor;
	int	i;


	i = 0;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * main->n_philo);
	if (!threads)
		return (0);
	main->forks  = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * main->n_philo);
	if (!main->forks )
		return (0);
	pthread_mutex_init(&main->write_mutex, NULL);
	pthread_mutex_init(&main->check_mutex, NULL);
	i = 0;
	while (i < main->n_philo)
	{
		main->philo[i].write_mutex = &main->write_mutex;
		main->philo[i].check_mutex = &main->check_mutex;
		pthread_mutex_init(&(main->forks)[i], NULL);
		i++;
	}
	i  = 0;
	while (i < main->n_philo)	
	{
		main->philo[i].r_fork = &main->forks[i];
		main->philo[i].l_fork = &main->forks[(i + 1) % main->n_philo];
		main->philo[i].time_last_meal = get_time();
		pthread_create(&threads[i], NULL, &philo_logic, &(main->philo)[i]);
		usleep(50);
		i++;
	}
	pthread_create(&monitor, NULL, &monitor_logic, main);
	// puts("after create threads");
	// i = 0;
	// while (i < main->n_philo)
	// {
	// 	pthread_join(threads[i], NULL);
	// 	i++;
	// }
	return (1);
}
