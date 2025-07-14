/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:50:07 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/10 12:37:50 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	function(unsigned int i, char *c)
{
	if (*c >= 'a' && *c <= 'z')
		*c = *c - 32;
}
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (*s != '\0')
	{
		f(i, s);
		s++;
		i++;
	}
}
/*
int	main(void)
{
	char str[] = "hello there!";
	printf("The Original string: %s\n", str);
	ft_striteri(str, function);
	printf("The result string: %s\n", str);
	return (0);
}
*/