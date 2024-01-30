/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:55:19 by wvan-der          #+#    #+#             */
/*   Updated: 2024/01/30 12:45:34 by wvan-der         ###   ########.fr       */
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
