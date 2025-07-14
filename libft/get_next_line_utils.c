/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:22:55 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/25 11:22:57 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	len(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	*chr(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i++;
	}
	if (c == '\0')
		return ((char *)(str + i));
	return (NULL);
}

char	*join(char *str, char *buff)
{
	char	*res;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!str)
	{
		str = (char *)malloc(sizeof(char) * 1);
		str[0] = '\0';
	}
	if (!str || !buff)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(buff) + 1));
	if (!res)
		return (NULL);
	if (str)
		while (str[++i])
			res[i] = str[i];
	while (buff[j])
		res[i++] = buff[j++];
	res[ft_strlen(str) + ft_strlen(buff)] = '\0';
	free(str);
	return (res);
}
