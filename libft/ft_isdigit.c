/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:39:32 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/09 14:30:31 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int n)
{
	if (n >= '0' && n <= '9')
		return (1);
	else
		return (0);
}
/*
int main(void)
{
	int n = '4';
	int b = 13;

	printf("%d", ft_isdigit(n));
	printf("%d", ft_isdigit(b));

	return (0);
}*/
