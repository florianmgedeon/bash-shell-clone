/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgedeon <fgedeon@student.42vienna.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-12 15:41:06 by fgedeon           #+#    #+#             */
/*   Updated: 2024-04-12 15:41:06 by fgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_envp(char **envp, int env_size)
{
	int	i;

	i = 0;
	while (i < env_size)
		free(envp[i++]);
	free(envp);
}

char	**add_env_var(char **envp, char *new_env)
{
	char	**copy_envp;
	int		env_size;
	int		i;

	env_size = 0;
	i = 0;
	copy_envp = NULL;
	while (envp[env_size] != NULL)
		env_size++;
	copy_envp = (char **)malloc(sizeof(char *) * (env_size + 2));
	if (copy_envp == NULL)
		return (NULL);
	while (i < env_size)
	{
		copy_envp[i] = ft_strdup(envp[i]);
		if (copy_envp[i] == NULL)
			return (free(copy_envp), NULL);
		i++;
	}
	copy_envp[env_size] = new_env;
	copy_envp[env_size + 1] = NULL;
	free_envp(envp, env_size);
	return (copy_envp);
}

int	e_just_numbers(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
	{
		if (ft_isdigit(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	e_ft_syntax_error(char *av)
{
	int	j;

	j = 0;
	if (e_just_numbers(av) == 1)
		return (1);
	if (av[0] && ft_isdigit(av[0]) == 1)
		return (1);
	while (av[j] != '\0')
	{
		if (!is_valid_char(av[j]))
			return (1);
		if (av[j] == '=')
		{
			if (j == 0)
				return (1);
			if (j > 0 && (!av[j - 1] || av[j - 1] == ' '))
				return (1);
			else if (av[j + 1] == ' ' || av[j + 1] == '=')
				return (1);
			break ;
		}
		j++;
	}
	return (0);
}

int	allocate_next_env(t_env **c, char ***envp, int i)
{
	if ((*envp)[i + 1] != NULL)
	{
		(*c)->next = (t_env *)malloc(sizeof(t_env));
		if ((*c)->next == NULL)
			return (-1);
		*c = (*c)->next;
	}
	else
		(*c)->next = NULL;
	return (0);
}
