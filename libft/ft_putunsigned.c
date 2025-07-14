/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:48:30 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/20 12:48:32 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbr_len(unsigned int n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_uitoa(unsigned int n)
{
	char	*nbr;
	int		length;

	length = ft_nbr_len(n);
	nbr = (char *)malloc(sizeof(char) * (length + 1));
	if (!nbr)
		return (NULL);
	nbr[length--] = '\0';
	while (n > 0)
	{
		nbr[length] = n % 10 + '0';
		n /= 10;
		length--;
	}
	return (nbr);
}

int	ft_putunsigned(unsigned int n)
{
	int		print_length;
	char	*nbr;

	print_length = 0;
	if (n == 0)
	{
		ft_putchar('0');
		print_length++;
	}
	else
	{
		nbr = ft_uitoa(n);
		ft_putstr(nbr);
		print_length += ft_nbr_len(n);
		free(nbr);
	}
	return (print_length);
}
