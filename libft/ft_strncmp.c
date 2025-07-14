/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:41:04 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/11 17:08:15 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!s1)
		return (-1);
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	printf("%d", ft_strncmp("Hello", "Hello", 4));
	printf("\n%d", ft_strncmp("Hello21", "Hello121212121212121212121212", 7));
	printf("\n%d", ft_strncmp("HelloW", "HelloAorld", 6));
	return (0);
}
*/