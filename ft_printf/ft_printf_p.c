/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:17:53 by wvan-der          #+#    #+#             */
/*   Updated: 2023/09/25 13:02:39 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_convert_address_base(unsigned long long nb, int *count)
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
		ft_convert_address_base(nb / 16, count);
	}
	ft_printf_c(base[hex], count);
}

void	ft_printf_p(void *ptr, int *count)
{
	unsigned long long	address;
	char				*prefix;

	prefix = "0x";
	address = (unsigned long long)ptr;
	if (address == 0)
		ft_printf_s("(nil)", count);
	else
	{
		ft_printf_s(prefix, count);
		ft_convert_address_base(address, count);
	}
}
