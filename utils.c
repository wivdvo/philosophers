/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:55:19 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/29 15:17:01 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
	{
		i++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result * sign);
}

static char	*ft_itoa2(char *res, int neg)
{
	if (neg == 1)
		res[0] = '-';
	return (res);
}

static int	ft_count(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	char			*res;
	int				neg;
	int				i;

	neg = 0;
	if (n < 0)
	{
		nb = n * -1;
		neg = 1;
	}
	else
		nb = n;
	i = ft_count(nb) + neg;
	res = malloc(i + 1);
	if (res == NULL)
		return (NULL);
	res[i] = 0;
	while (i-- > 0)
	{
		res[i] = nb % 10 + '0';
		nb /= 10;
	}
	return (ft_itoa2(res, neg));
}

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
	struct timeval tv;

	if (gettimeofday(&tv, NULL) != 0)
		return(put_error("gettimeofday failded"), 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	convert_and_check_input(char *str)
{
	long long nb;

	nb = ft_atoi(str);
	if (ft_strcmp(ft_itoa(nb), str) != 0)
		return (put_error("invalid number"), -1);
	if (nb < 0)
		return (put_error("negativ number"), -1);
	//printf("nb:%lld\n", nb);
	return (nb);
}