/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:01:13 by aszabo            #+#    #+#             */
/*   Updated: 2024/03/06 16:54:28 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* #include <stdio.h> */
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (NULL);
}
/*
int	main(void)
{
	char tab[] = "computer program";
	char *ptr;
	char *ptr1;
	int c = 'p';

	ptr = strchr(tab, c);
	ptr1 = ft_strchr(tab, c);
	if (ptr != NULL)
			printf("%s\n", ptr);
	else
			printf("Character not found:((\n");
	if (ptr1 != NULL)
			printf("%ld\n", ptr1 - tab);
	else
			printf("No bueno");
	return (0);
}
*/