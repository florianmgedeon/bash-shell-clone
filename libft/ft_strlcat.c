/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:50:49 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/10 14:18:03 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	destl;
	unsigned int	sl;

	i = 0;
	j = 0;
	while (dst[j] != '\0')
		j++;
	destl = j;
	sl = ft_strlen(src);
	if (size == 0 || size <= destl)
		return (sl + size);
	while (src[i] != '\0' && i < size - destl - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (destl + sl);
}
