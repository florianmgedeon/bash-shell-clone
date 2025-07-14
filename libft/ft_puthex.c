/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 09:51:05 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/20 09:51:08 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hexlen(unsigned int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static void	ft_write_hex(unsigned int n, char format)
{
	if (n >= 16)
	{
		ft_write_hex(n / 16, format);
		ft_write_hex(n % 16, format);
	}
	else
	{
		if (n <= 9)
			ft_putchar(n + '0');
		else
		{
			if (format == 'x')
				ft_putchar(n - 10 + 'a');
			if (format == 'X')
				ft_putchar(n - 10 + 'A');
		}
	}
}

int	ft_puthex(unsigned int n, const char format)
{
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	else
		ft_write_hex(n, format);
	return (ft_hexlen(n));
}
