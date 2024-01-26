/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:47:07 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/26 17:04:45 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_main	main;
	if (ac != 5 && ac != 6)
		return (put_error("worng amount of args"), 0);
	if (init_main_struct(&main, ac, av) == 0)
		return (0);
	if (init_philos(&main) == 0)
		return (0);
	usleep(888888888);
}

//				./philosophers 5 800 200 200 7