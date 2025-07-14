/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:58:27 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/10 16:32:55 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t					i;
	unsigned char			*dest1;
	const char				*src1;

	i = 0;
	if (!dest && !src)
		return (dest);
	dest1 = (unsigned char *)dest;
	src1 = (const char *)src;
	while (i < n)
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char src[] = "Get Schwifty in here";
	char dest[100];
	ft_memcpy(dest, src, strlen(src) + 1);
	printf("%s", dest);
	return (0);
}*/
