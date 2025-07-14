/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:48:19 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/10 16:29:16 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	int size = 10;
	char arr[size];
	int i = 0;

	while (i < size)
    {
        arr[i] = i;
        i++;
    }
	i = 0;
	while (i < size)
	{
		printf("%d", arr[i]);
		i++;
	}
	printf("\n");
	ft_memset(arr, 0, size);
	i = 0;
	while (i < size)
	{
		printf("%d", arr[i]);
		i++;
	}
	printf("\n");
	ft_memset(arr, 23, 3);
	ft_memset(arr+3, 46, 4);
	ft_memset(arr+7, 9, 3);
	i = 0;
    while (i < size)
    {
        printf("%d", arr[i]);
        i++;
    }
	return (0);
}
*/