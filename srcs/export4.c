/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgedeon <fgedeon@student.42vienna.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-12 15:44:00 by fgedeon           #+#    #+#             */
/*   Updated: 2024-04-12 15:44:00 by fgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*copy_and_format_env(char *av, char *new_env)
{
	int	j;

	j = 0;
	while (av[j] != '\0')
	{
		new_env[j] = av[j];
		j++;
	}
	new_env[j] = '\0';
	if (new_env[j - 1] != '\n' && new_env[j + 1])
	{
		new_env[j] = '\n';
		new_env[j + 1] = '\0';
	}
	return (new_env);
}

char	*create_new_env(char *av, char ***envp, char ***tmp)
{
	int		c;
	char	*new_env;
	char	**new_envp;

	c = 0;
	while (av[c] && av[c] != '\0')
		c++;
	new_env = (char *)malloc(sizeof(char) * (c + 2));
	if (new_env == NULL)
		return (NULL);
	ft_memset(new_env, '\0', c + 2);
	new_env = copy_and_format_env(av, new_env);
	new_envp = add_env_var(*envp, new_env);
	if (new_envp == NULL)
		return (free(new_env), NULL);
	*envp = new_envp;
	*tmp = *envp;
	return (new_env);
}

char	*create_copy_of_string(int i, char **av)
{
	int		j;
	int		c;
	char	*new_env;

	c = 0;
	while (av[i][c] && av[i][c] != '\0')
		c++;
	new_env = (char *)malloc(sizeof(char) * (c + 2));
	if (new_env == NULL)
		return (NULL);
	j = 0;
	while (av[i][j] != '\0')
	{
		new_env[j] = av[i][j];
		j++;
	}
	new_env[j] = '\0';
	return (new_env);
}

int	replace_existing_var(int i, char **av, char ***envp, char ***tmp)
{
	int		x;
	char	*new_env;
	bool	same_flag2;

	same_flag2 = false;
	new_env = create_copy_of_string(i, av);
	if (new_env == NULL)
		return (perror("malloc error"), errno);
	*tmp = *envp;
	x = 0;
	while ((*tmp)[x] != NULL && av[i] != NULL && same_flag2 == false)
	{
		if (is_same_var(av[i], (*tmp)[x]) == true)
			same_flag2 = true;
		x++;
	}
	free((*tmp)[x - 1]);
	(*tmp)[x - 1] = new_env;
	return (0);
}

void	e_custom_init_3(int *i, bool *same_flag, int *result)
{
	*i = 1;
	*same_flag = false;
	*result = 0;
}
