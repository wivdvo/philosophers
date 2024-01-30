/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:45:06 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/30 14:31:43 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		i++;
	}
	return (i);
}

void	put_error(char *str)
{
	write(2, str, ft_strlen(str));
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (put_error("gettimeofday failded"), 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	convert_and_check_input(char *str)
{
	long long	nb;
	char		*itoa_str;

	nb = ft_atoi(str);
	itoa_str = ft_itoa(nb);
	if (ft_strcmp(itoa_str, str) != 0)
		return (put_error("invalid number"), free(itoa_str), 0);
	if (nb < 0)
		return (put_error("negativ number"), free(itoa_str), 0);
	free(itoa_str);
	return (nb);
}

void	better_usleep(size_t ms)
{
	size_t	i;
	size_t	start_time;

	i = 0;
	start_time = get_time();
	while (get_time() - start_time <= ms)
	{
		usleep(ms / 10);
	}
}
