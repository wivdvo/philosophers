/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:26:30 by wvan-der          #+#    #+#             */
/*   Updated: 2023/09/22 16:47:25 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_s(char *s, int *count)
{
	if (s == NULL)
	{
		ft_printf_s("(null)", count);
		return ;
	}
	while (*s)
	{
		ft_printf_c(*s, count);
		s++;
	}
}
