/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:41:43 by fgedeon           #+#    #+#             */
/*   Updated: 2024/04/15 13:31:48 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(char **envp)
{
	char	**temp;

	temp = envp;
	while (*temp != NULL)
	{
		if (ft_strchr(*temp, '=') != NULL)
			printf("%s\n", *temp);
		temp++;
	}
	return (0);
}
