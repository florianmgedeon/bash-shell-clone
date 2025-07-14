/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:20:21 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/10 10:40:13 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
/*
int main(void)
{
    char a = 'a';
    char b = 'B';
    printf("%d\n", ft_tolower(a));
    printf("%d\n", ft_tolower(b));
	printf("%d\n", tolower(a));
    printf("%d\n", tolower(b));

    return (0);
}*/
