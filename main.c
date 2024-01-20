/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:47:07 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/20 16:59:46 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_struct(t_philo *philo, char **av, char ac)
{
	philo->n_philo = av[1];
	philo->time_to_die = av[2];
	philo->time_to_eat = av[3];
	philo->time_to_sleep = av[4];
	if (ac == 6)
		philo->n_times_must_eat = av[5];
}

int	main(int ac, char **av)
{
	t_philo philo;
	if (ac != 5 || ac != 6)
		return (0);
	init_struct(&philo, av, ac);
}