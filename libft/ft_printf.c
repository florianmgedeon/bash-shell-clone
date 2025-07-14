/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:56:42 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/19 10:56:46 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <limits.h>

static int	formats(va_list ap, const char format)
{
	int	print_length;

	print_length = 0;
	if (format == 'c')
		print_length += ft_putchar(va_arg(ap, int));
	else if (format == 's')
		print_length += ft_putstr(va_arg(ap, char *));
	else if (format == 'p')
		print_length += ft_putptr(va_arg(ap, unsigned long long));
	else if (format == 'd' || format == 'i')
		print_length += ft_putnbr(va_arg(ap, int));
	else if (format == 'u')
		print_length += ft_putunsigned(va_arg(ap, unsigned int));
	else if (format == 'x' || format == 'X')
		print_length += ft_puthex(va_arg(ap, unsigned int), format);
	else if (format == '%')
		print_length += ft_putpercent();
	return (print_length);
}

int	ft_printf(const char *str, ...)
{
	int			i;
	int			print_length;
	va_list		ap;

	i = 0;
	print_length = 0;
	va_start(ap, str);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == '\0')
			print_length += ft_putpercent();
		if (str[i] == '%')
		{
			print_length += formats(ap, str[i + 1]);
			i++;
		}
		else
			print_length += ft_putchar(str[i]);
		i++;
	}
	va_end(ap);
	return (print_length);
}
/* #include<stdio.h>
int	main(void)
{

	ft_printf("Print this number %.2d", INT_MAX);
	printf("\n");
	printf("Print this number %d fsfdsf", INT_MAX);

	printf("\n\n");

	ft_printf("This is a character: %c", CHAR_MIN);
	printf("\n");
	printf("This is a character: %c", CHAR_MIN);
	printf("\n\n");

	ft_printf("This is a string: %s", "Get schwifty in here!");
	printf("\n");
	printf("This is a string: %s", "Get schwifty in here!");
	printf("\n\n");

	ft_printf("Print this number %i", -243);
	printf("\n");
	printf("Print this number %i", -243);
	printf("\n\n");

	ft_printf("Print this number in low hex %x", UINT_MAX);
	printf("\n");
	printf("Print this number in low hex %x", UINT_MAX);
	printf("\n\n");

	ft_printf("Print this number in up hex %X", UINT_MAX);
	ft_printf("\n\n\n");
	printf("Print this number in up hex %X", UINT_MAX);
	printf("\n\n");

	ft_printf("Print a pointer: %p", (void *)0);
	printf("\n");
	printf("Print a pointer: %p", (void *)0);
	printf("\n\n");

	ft_printf(" %u ", 10);
	printf("\n");
	printf(" %u ", 10);
	printf("\n\n");

	ft_printf("Print percentage sign: %%");
	printf("\n");
	printf("Print percentage sign: %%");
	printf("\n\n");
	return (0);
} */
