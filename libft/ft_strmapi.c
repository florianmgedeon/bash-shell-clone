/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:20:26 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/10 12:31:09 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
static char	function(unsigned int i, char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		len;
	unsigned int		i;
	char				*res;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
int	main(void)
{
	const char *str = "hello there!";
	char *res = ft_strmapi(str, function);
	if (res)
	{
		printf("Original string: %s\n", str);
		printf("Result string: %s\n", res);
		free(res);
	}
	else
		printf("Memory alloc failed");
	return (0);
}
*/