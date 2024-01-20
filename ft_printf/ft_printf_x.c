/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:31:27 by wvan-der          #+#    #+#             */
/*   Updated: 2023/09/22 16:50:07 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_convert_base(unsigned int nb, int *count)
{
	int		hex;
	char	*base;

	hex = 0;
	base = "0123456789abcdef";
	if (nb == 0)
		return ;
	else
	{
		hex = nb % 16;
		ft_convert_base(nb / 16, count);
	}
	ft_printf_c(base[hex], count);
}

void	ft_printf_x(unsigned int nb, int *count)
{
	if (nb == 0)
		ft_printf_c('0', count);
	else
		ft_convert_base(nb, count);
}
