/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:58:55 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 18:59:03 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_strings(char **strings)
{
	int	i;

	i = 0;
	if (strings)
	{
		while (strings[i])
		{
			free(strings[i]);
			i++;
		}
		free(strings);
	}
}
