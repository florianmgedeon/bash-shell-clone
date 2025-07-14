/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:08:08 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 13:51:17 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_array(char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = 0;
	return (copy);
}

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	set_shlvl(char **envp)
{
	int		i;
	int		shlvl;
	char	*tmp;

	i = 0;
	while (ft_strncmp(envp[i], "SHLVL=", 6) != 0)
		i++;
	shlvl = ft_atoi(envp[i] + 6);
	shlvl++;
	tmp = ft_itoa(shlvl);
	free(envp[i]);
	envp[i] = ft_strjoin("SHLVL=", tmp);
	free(tmp);
}
