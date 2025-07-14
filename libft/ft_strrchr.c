/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:25:21 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/10 14:20:45 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (NULL);
}
/*
int	main(void)
{
	char	str[] = "Elevator Alligator";
	char	*ptr;
	char	*ptr1;
	int		c = '\0';

	ptr = ft_strrchr(str, c);
	ptr1 = strrchr(str, c);
	if (ptr != NULL)
			printf("%s\n", ptr);
	else
			printf("No bueno\n");
	if (ptr1 != NULL)
			printf("%s\n", ptr1);
	else
			printf("Houston we have a problem");
	return (0);
}
*/