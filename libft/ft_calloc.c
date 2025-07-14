/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:17:27 by aszabo            #+#    #+#             */
/*   Updated: 2024/02/25 20:56:18 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;

	if (nmemb <= 0 || size <= 0)
		str = (char *)malloc(1);
	else
		str = (char *)malloc(nmemb * size);
	if (!str)
		return (NULL);
	return (ft_memset(str, 0, nmemb * size));
}
/*
int	main(void)
{
	size_t nmemb = 5;
	size_t size = sizeof(int);

	int	*arr = (int*)ft_calloc(nmemb, size);
	if (arr != NULL)
	{
		int i = 0;
		while (i < nmemb)
		{
			printf("%d", arr[i]);
			i++;
		}
		printf("\n");
		free(arr);
	}
	else
			printf("Memory alloc failed;(\n");
	return (0);
}
*/