/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:21:40 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/10 14:42:27 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)(big));
	while (big[i] != '\0' && i < n)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (little[j] != '\0' && big[i + j] == little[j] && (i + j) < n)
				j++;
			if (little[j] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char str[] = "Did you bring a towel?";
	char find[] = "you";
	size_t size = 8;

	printf("%s\n", ft_strnstr(str, find, size));
	printf("%d\n", strnstr(str, find, size));
	return (0);
}*/
