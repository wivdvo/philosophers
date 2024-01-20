/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:20:39 by wvan-der          #+#    #+#             */
/*   Updated: 2023/09/22 16:47:42 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_d(int n, int *count)
{
	unsigned int	nb;
	char			digit;

	if (n < 0)
	{
		nb = n * -1;
		ft_printf_c('-', count);
	}
	else
		nb = n;
	if (nb > 9)
		ft_printf_d(nb / 10, count);
	digit = nb % 10 + '0';
	ft_printf_c(digit, count);
}
