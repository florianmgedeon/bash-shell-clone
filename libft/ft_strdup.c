/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:58:03 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/10 14:44:41 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*res;

	i = 0;
	res = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!res)
		return (0);
	while (src[i])
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
int	main(void)
{
	char *str;
	char *str1;
	char *res;

	str = "Get Schwifty In Here!";
	str1 = "Hello There!";

	res = ft_strdup(str);
	printf("%s\n", res);
	free(res);

	res = ft_strdup(str1);
	printf("%s", res);
	free(res);

	return (0);
}*/
