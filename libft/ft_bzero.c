/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:05:32 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/10 16:30:06 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	char			*str;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}
/*
int	main(void)
{
	int size = 5;
	char arr[size];
	char arr1[size];
	int j = 0;
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
	bzero(arr, size);
	i = 0;
	while (i < size)
	{
		printf("%d", arr[i]);
		i++;
	}

	printf("\n\n");

	while (j < size)
    {
        arr1[j] = j;
        j++;
    }
    j = 0;
    while (j < size)
    {
        printf("%d", arr1[j]);
        j++;
    }
    printf("\n");
    ft_bzero(arr1, size);
    j = 0;
    while (j < size)
    {
        printf("%d", arr[j]);
        j++;
    }
	return (0);
}*/
