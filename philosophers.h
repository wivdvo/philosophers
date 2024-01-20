/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:45:28 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/20 16:55:38 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

typedef struct s_philo
{
	unsigned int	n_philo;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	unsigned int n_times_must_eat;
}	t_philo;

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

#endif