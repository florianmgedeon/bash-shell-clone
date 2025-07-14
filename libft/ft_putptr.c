/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:56:05 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/20 10:56:08 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ptrlen(uintptr_t ptr)
{
	int	i;

	i = 0;
	while (ptr != 0)
	{
		ptr /= 16;
		i++;
	}
	return (i);
}

static void	ft_write_ptr(uintptr_t ptr)
{
	if (ptr >= 16)
	{
		ft_write_ptr(ptr / 16);
		ft_write_ptr(ptr % 16);
	}
	else
	{
		if (ptr <= 9)
			ft_putchar(ptr + '0');
		else
			ft_putchar(ptr - 10 + 'a');
	}
}

int	ft_putptr(unsigned long long ptr)
{
	int	print_length;

	print_length = 0;
	if (ptr == 0)
		print_length += write(1, "(nil)", 5);
	else
	{
		write(1, "0x", 2);
		print_length += 2;
		ft_write_ptr(ptr);
		print_length += ft_ptrlen(ptr);
	}
	return (print_length);
}
