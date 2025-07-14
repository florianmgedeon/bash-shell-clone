/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:57:28 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/10 10:49:02 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char				*str;
	unsigned char					ch;
	size_t							i;

	i = 0;
	str = (const unsigned char *)s;
	ch = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == ch)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
		char str[] = "Get Schwifty";
		int tofind = 'x';
		size_t n = 12;

		char *res = ft_memchr(str, tofind, n);
		if (res != NULL)
				printf("Found '%c' at position %ld\n", (char)tofind, res - str);
		else
				printf("'%c' not found in string\n", (char)tofind);
		return (0);
}*/
