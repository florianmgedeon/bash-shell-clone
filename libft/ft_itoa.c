/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:29:37 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/10 12:28:20 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_len(long n)
{
	int	length;

	length = 0;
	if (n == 0)
		length++;
	if (n < 0)
	{
		n *= -1;
		length++;
	}
	while (n > 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	long		nb;
	char		*str;
	int			i;

	nb = n;
	i = calc_len(nb);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		str[i] = (nb % 10) + '0';
		nb /= 10;
		i--;
	}
	return (str);
}
/*
int	main(void)
{
	int	n1 = 0;
	int	n2 = -2147483648;

	char *str1 = ft_itoa(n1);
	char *str2 = ft_itoa(n2);

	if (str1 && str2)
	{
		printf("Integer1 was %d and therefore string1 is %s\n", n1, str1);
		printf("Integer2 was %d and therefore string2 is %s\n", n2, str2);
		printf("%s", str2);
		free(str1);
		free(str2);
	}
	else
			printf("Memory alloc failed\n");
	return (0);
}
*/