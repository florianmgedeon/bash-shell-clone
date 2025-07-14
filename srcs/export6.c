/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgedeon <fgedeon@student.42vienna.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-19 15:09:36 by fgedeon           #+#    #+#             */
/*   Updated: 2024-04-19 15:09:36 by fgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_char(char c)
{
	if (ft_isalpha(c) == 0 && ft_isdigit(c) == 0 && c != '_'
		&& c != '=' && c != ' ' && c != '|'
		&& c != '\'' && c != '\"')
	{
		return (0);
	}
	return (1);
}

int	process_quotes_ex(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		av[i] = take_out_quotes(av[i]);
		if (av[i] == NULL)
			return (1);
		i++;
	}
	return (0);
}

void	export_init(int *i, char ***tmp, int *result, char ***envp)
{
	*i = 1;
	*tmp = *envp;
	*result = 0;
}
