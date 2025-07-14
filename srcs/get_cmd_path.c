/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:05:53 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 17:29:55 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(t_prompt *prompt)
{
	int		i;
	char	*path;

	i = 0;
	while (prompt->envp && prompt->envp[i])
	{
		if (ft_strncmp(prompt->envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(prompt->envp[i] + 5);
			if (!path)
				malloc_fail(prompt);
			return (path);
		}
		i++;
	}
	return (NULL);
}

void	cmd_path_fail(char **path, char *cmd, t_prompt *prompt)
{
	ft_free_strings(path);
	free(cmd);
	malloc_fail(prompt);
}

char	*get_cmd_path_2(char **path, char *cmd, t_parser *p, t_prompt *prompt)
{
	int		i;
	char	*tmp;
	char	*res;

	i = -1;
	(void)p;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			cmd_path_fail(path, cmd, prompt);
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!res)
			cmd_path_fail(path, cmd, prompt);
		if (access(res, F_OK | X_OK) == 0)
			return (res);
		free(res);
	}
	return (NULL);
}

char	*get_res(char *cmd_path, char *tmp, t_parser *p, t_prompt *prompt)
{
	char	**path;
	char	*res;

	res = NULL;
	path = ft_split(cmd_path, ':');
	if (!path)
	{
		free(cmd_path);
		free(tmp);
		malloc_fail(prompt);
	}
	free(cmd_path);
	if (!path)
	{
		free(cmd_path);
		free(tmp);
		malloc_fail(prompt);
	}
	res = get_cmd_path_2(path, tmp, p, prompt);
	ft_free_strings(path);
	return (res);
}

char	*get_cmd_path(char *cmd, t_parser *p, t_prompt *prompt)
{
	char	*tmp;
	char	*cmd_path;
	char	*res;

	cmd_path = find_path(prompt);
	tmp = ft_strdup(cmd);
	if (!tmp)
		malloc_fail(prompt);
	if (cmd_path != NULL)
	{
		res = get_res(cmd_path, tmp, p, prompt);
		free(tmp);
		if (res)
			return (res);
	}
	else
		free(tmp);
	res = ft_strdup(cmd);
	if (!res)
		malloc_fail(prompt);
	return (res);
}
