/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:27:50 by wvan-der          #+#    #+#             */
/*   Updated: 2023/09/22 16:47:58 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

int		ft_printf(const char *str, ...);
void	ft_printf_c(int c, int *count);
void	ft_printf_s(char *s, int *count);
void	ft_printf_d(int n, int *count);
void	ft_printf_u(unsigned int nb, int *count);
void	ft_printf_x(unsigned int nb, int *count);
void	ft_printf_x_cap(unsigned int nb, int *count);
void	ft_printf_p(void *ptr, int *count);

#endif
