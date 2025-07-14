/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:31:41 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/10 10:50:25 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	const unsigned char		*a;
	const unsigned char		*b;

	i = 0;
	a = (const unsigned char *)s1;
	b = (const unsigned char *)s2;
	while (i < n)
	{
		if (a[i] < b[i])
			return (-1);
		else if (a[i] > b[i])
			return (1);
		i++;
	}
	return (0);
}
/*
int main(void)
{
	char str1[] = "Hello There";
	char str2[] = "Hella There";
	size_t n = 5;

	int res = ft_memcmp(str1, str2, n);

	if (res == 0)
			printf("The strings memory blocks are equal\n");
	else if (res < 0)
			printf("Str1's memory block is smaller than str2's\n");
	else
			printf("Str1's memory block is bigger than str2's\n");
	return (0);
}*/
