/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:47:07 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/22 15:20:51 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	convert_and_check_input(char *str)
{
	long long nb;

	nb = ft_atoi(str);
	if (ft_strcmp(ft_itoa(nb), str) != 0)
		return (put_error("invalid number"), -1);
	if (nb < 0)
		return (put_error("negativ number"), -1);
	puts("good");
	return (1);
}

int	init_struct(t_philo *philo, int ac, char **av)
{
	philo->n_philo = convert_and_check_input(av[1]);
	if (philo->n_philo == -1)
		return (0);
	philo->time_to_die = convert_and_check_input(av[2]);
	if (philo->time_to_die == -1)
		return (0);
	philo->time_to_eat = convert_and_check_input(av[3]);
	if (philo->time_to_eat == -1)
		return (0);
	philo->time_to_sleep = convert_and_check_input(av[4]);
	if (philo->time_to_sleep == -1)
		return (0);
	if (ac == 6)
	{
		philo->n_times_must_eat = convert_and_check_input(av[5]);
		if (philo->n_times_must_eat == -1)
			return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo philo;
	if (ac != 5 && ac != 6)
		return (put_error("worng amount of args"), 0);
	if (init_struct(&philo, ac, av) == 0)
		return (0);
}