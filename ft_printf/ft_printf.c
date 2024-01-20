/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wvan-der <wvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:27:42 by wvan-der          #+#    #+#             */
/*   Updated: 2023/10/03 16:43:59 by wvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_format(const char *str, va_list *args, int *i, int *count)
{
	if (str[*i] == 'c')
		ft_printf_c(va_arg(*args, int), count);
	else if (str[*i] == 's')
		ft_printf_s(va_arg(*args, char *), count);
	else if (str[*i] == 'p')
		ft_printf_p(va_arg(*args, void *), count);
	else if (str[*i] == 'd' || str[*i] == 'i')
		ft_printf_d(va_arg(*args, int), count);
	else if (str[*i] == 'u')
		ft_printf_u(va_arg(*args, unsigned int), count);
	else if (str[*i] == 'x')
		ft_printf_x(va_arg(*args, unsigned long long), count);
	else if (str[*i] == 'X')
		ft_printf_x_cap(va_arg(*args, unsigned long long), count);
	else if (str[*i] == '%')
		ft_printf_c('%', count);
	else if (str[*i] == '\0')
		return (0);
	else
	{
		ft_printf_c(str[(*i) - 1], count);
		ft_printf_c(str[*i], count);
	}
	return (1);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (str == NULL)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (!(ft_check_format(str, &args, &i, &count)))
				return (-1);
		}
		else
			ft_printf_c(str[i], &count);
		i++;
	}
	return (count);
}
/*
int	main()
{
	int res = 0;
	int	cres = 0;
	char *test = "hello";
	char *test2 = "aaa";
	char *test3 = NULL;
	
	ft_printf(0);
	printf("real:\n");
	cres = printf(" %p ", test3);
	printf("\nr:%d\n", cres);
	printf("my:\n");
	res = ft_printf(" %p ", test3);
	printf("\nr:%d\n", res);
}
*/
/* int	main(void)
{
	char *format;
	char *string;
	char character;
	int num;
	int result_ft;
	int result_print;
	//ft_printf(format, 1, 2, 3);

	puts("=== Character: %c ===");
	format = "%c\n";
	character = 'A';
	result_ft = ft_printf(format, character);
	result_print = printf(format, character);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	character = 'B';
	result_ft = ft_printf(format, character);
	result_print = printf(format, character);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);

	puts("=== String: %s ===");
	format = "%s\n";
	string = NULL;
	result_ft = ft_printf(format, string);
	result_print = printf(format, string);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	string = "Hello I am a String";
	result_ft = ft_printf(format, string);
	result_print = printf(format, string);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);

	puts("\n=== Integer: %d ===");
	format = "%d\n";
	num = 0;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = 42;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = -42;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = 2147483647;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = -2147483648;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);

	puts("\n=== Hexa lower-Cased: %x ===");
	format = "%x\n";
	num = 0;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = 42;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = -42;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = 2147483647;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = -2147483648;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);

	puts("\n=== Hexa UPPER-CASED: %X ===");
	format = "%X\n";
	num = 0;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = 42;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = -42;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = 2147483647;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = -2147483648;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);

	puts("\n=== Multiple-Options (%d%s%X) ===");
	format = "%d%s%X\n";
	string = ": ";
	num = 0;
	result_ft = ft_printf(format, num, string, num);
	result_print = printf(format, num, string, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = 42;
	result_ft = ft_printf(format, num, string, num);
	result_print = printf(format, num, string, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = -42;
	result_ft = ft_printf(format, num, string, num);
	result_print = printf(format, num, string, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = 2147483647;
	result_ft = ft_printf(format, num, string, num);
	result_print = printf(format, num, string, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	num = -2147483648;
	result_ft = ft_printf(format, num, string, num);
	result_print = printf(format, num, string, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);

	puts("\n=== Percent: %% ===");
	format = "%%\n";
	result_ft = ft_printf(format);
	result_print = printf("%%\n");
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);

	puts("\n=== Pointer: %p ===");
	format = "%p\n";
	string = NULL;
	result_ft = ft_printf(format, string);
	result_print = printf(format, string);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	string = "Im a pointer";
	result_ft = ft_printf(format, string);
	result_print = printf(format, string);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	puts("\n=== Not supported Option and normal text: %y ===");
	format = "Im not supported %y\n";
	result_ft = ft_printf(format, string);
	result_print = printf(format, string);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	puts("\n=== Custom Tests ===");
	format = "%d%d\n";
	num = 42;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	format = NULL;
	num = 42;
	result_ft = ft_printf(format, num);
	result_print = printf(format, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
	format = "%c %s %p %d %i %u %x %X %%\n";
	num = 42;
	char c = '4';
	string = "printf";
	result_ft = ft_printf(format, c, string, string, num, num, num, num, num);
	result_print = printf(format, c, string, string, num, num, num, num, num);
	printf("Return: ft_printf=%d printf=%d\n\n", result_ft, result_print);
} */
