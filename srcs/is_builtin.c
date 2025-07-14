/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:10:52 by fgedeon           #+#    #+#             */
/*   Updated: 2024/04/15 13:06:48 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	is_builtin(t_prompt *prompt, t_parser *parser, t_fds *fds)
{
	int	result;

	result = 0;
	if ((ft_strncmp(parser->cmd, "echo", 4)) == 0)
		result = ft_echo(parser->cmd_args);
	if ((ft_strncmp(parser->cmd, "cd", 2)) == 0)
		result = ft_cd(ft_arraylen(parser->cmd_args), parser->cmd_args,
				prompt->envp);
	if ((ft_strncmp(parser->cmd, "pwd", 3)) == 0)
		result = ft_pwd();
	if ((ft_strncmp(parser->cmd, "export", 6)) == 0)
		result = ft_export(ft_arraylen(parser->cmd_args), parser->cmd_args,
				&prompt->envp);
	if ((ft_strncmp(parser->cmd, "unset", 5)) == 0)
		result = ft_unset(ft_arraylen(parser->cmd_args), parser->cmd_args,
				prompt->envp);
	if ((ft_strncmp(parser->cmd, "env", 3)) == 0)
		result = ft_env(prompt->envp);
	if ((ft_strncmp(parser->cmd, "exit", 4)) == 0)
		result = ft_exit(parser, prompt->exit_status, prompt, fds);
	return (result);
}
