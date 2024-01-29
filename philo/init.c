/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:41:29 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/29 17:41:49 by wvan-der         ###   ########.fr       */
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
	philo->time_to_die = convert_and_check_input(av[2]);
	if (philo->time_to_die == -1 || philo->time_to_die == 0)
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
	main->forks = NULL;
	philo = NULL;
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

int	handle_lonely_philo(t_main *main, size_t start_time, pthread_t **threads)
{
	main->philo[0].start_time = start_time;
	main->philo[0].time_last_meal = start_time;
	pthread_create(threads[0], NULL, &lonely_philo, &main->philo[0]);
	pthread_join(*(threads)[0], NULL);
	return (1);
}

int	give_mutexes_make_forks(t_main *main, int i)
{
	main->philo[i].write_mutex = &main->write_mutex;
	main->philo[i].check_mutex = &main->check_mutex;
	pthread_mutex_init(&(main->forks)[i], NULL);
	i++;
	return (1);
}

int	create_threads(t_main *main, size_t start_time, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < main->n_philo)	
	{
		main->philo[i].r_fork = &main->forks[i];
		main->philo[i].l_fork = &main->forks[(i + 1) % main->n_philo];
		main->philo[i].start_time = start_time;
		main->philo[i].time_last_meal = start_time;
		pthread_create(&threads[i], NULL, &philo_logic, &(main->philo)[i]);
		i++;
	}
	return (1);
}

void	ft_free(pthread_t **threads, t_main *main)
{
	int	i;

	i = 0;
	if (*threads)
	{
		free(*threads);
		*threads = NULL;
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

int	init_philos(t_main *main)
{
	pthread_t	*threads;
	pthread_t	monitor;
	size_t		start_time;
	int	i;

	i = 0;
	threads = NULL;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * main->n_philo);
	if (!threads)
		return (ft_free(&threads, main), 0);
	main->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * main->n_philo);
	if (!main->forks )
		return (ft_free(&threads, main), 0);
	pthread_mutex_init(&main->write_mutex, NULL);
	pthread_mutex_init(&main->check_mutex, NULL);
	i = 0;
	while (i < main->n_philo)
	{
		give_mutexes_make_forks(main, i++);
	}
	i  = 0;
	start_time = get_time();
	if (main->n_philo == 1)
	{
		handle_lonely_philo(main, start_time, &threads);
		return (ft_free(&threads, main), 1);
	}
	create_threads(main, start_time, threads);
	if (pthread_create(&monitor, NULL, &monitor_logic, main) != 0)
	{
		
	}
	i = 0;
	while (i < main->n_philo)
		pthread_join(threads[i++], NULL);
	pthread_join(monitor, NULL);
	ft_free(&threads, main);
	return (1);
}
