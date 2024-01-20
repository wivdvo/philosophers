/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:44:55 by wvan-der          #+#    #+#             */
/*   Updated: 2023/09/22 16:47:34 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_u(unsigned int nb, int *count)
{
	char	digit;

	if (nb > 9)
		ft_printf_u(nb / 10, count);
	digit = nb % 10 + '0';
	ft_printf_c(digit, count);
}
