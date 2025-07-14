/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgedeon <fgedeon@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 07:55:30 by fgedeon           #+#    #+#             */
/*   Updated: 2024/03/25 16:40:57 by fgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_single_arg(char **envp, char *old_pwd)
{
	int		i;
	char	*home;

	i = 0;
	home = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
		{
			home = envp[i];
			home += 5;
			break ;
		}
		i++;
	}
	if (home == NULL)
		return (write(2, "HOME not set\n", 13), free(old_pwd), 1);
	if (chdir(home) != 0)
	{
		perror("cd");
		return (free(old_pwd), errno);
	}
	return (free(old_pwd), 0);
}

int	change_directory(char *path, char *home, char *old_pwd)
{
	if (ft_strncmp(path, "~", 1) == 0)
	{
		if (chdir(home) != 0)
		{
			perror("minishell: cd");
			return (free(old_pwd), errno);
		}
	}
	else
	{
		if (chdir(path) != 0)
		{
			write(2, "minishell: cd: ", 15);
			write(2, path, ft_strlen(path));
			write(2, ": No such file or directory\n", 28);
			return (free(old_pwd), 1);
		}
	}
	return (0);
}

int	update_envp(char **envp, char *old_pwd, char *new_pwd, char *env_var)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(env_var);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env_var, var_len) == 0)
		{
			free(envp[i]);
			if (var_len == 7)
				envp[i] = ft_strjoin(env_var, old_pwd);
			else
				envp[i] = ft_strjoin(env_var, new_pwd);
			if (!envp[i])
				return (free(old_pwd), free(new_pwd), errno);
			break ;
		}
		i++;
	}
	return (0);
}

int	update_pwd(char **envp, char *old_pwd)
{
	char	*new_pwd;
	int		result;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (free(old_pwd), errno);
	result = update_envp(envp, old_pwd, new_pwd, "OLDPWD=");
	if (result != 0)
		return (free(old_pwd), free(new_pwd), errno);
	result = update_envp(envp, old_pwd, new_pwd, "PWD=");
	if (result != 0)
		return (free(old_pwd), free(new_pwd), errno);
	free(old_pwd);
	free(new_pwd);
	return (0);
}

int	ft_cd(int ac, char **av, char **envp)
{
	char	*old_pwd;
	char	*home;
	int		result;

	init_cd(&old_pwd, &home);
	result = 0;
	if (ac > 2)
		return (write(2, "minishell: cd: too many arguments\n", 34), 1);
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
	{
		result = change_directory(av[1], home, old_pwd);
		if (result == 0)
			return (result);
		return (perror("cd: "), errno);
	}
	if (ac == 1 || (ac == 2 && !av[1][0]))
		return (handle_single_arg(envp, old_pwd));
	else if (ac == 2)
	{
		result = change_directory(av[1], home, old_pwd);
		if (result != 0)
			return (result);
	}
	return (update_pwd(envp, old_pwd));
}
