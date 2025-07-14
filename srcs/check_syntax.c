/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:34:52 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/22 11:58:54 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_double(char *cmd, int *i, int *first)
{
	if (cmd[*i] == '>' && cmd[*i + 1] != '>' )
	{
		if (*first == 0)
			*first = 1;
	}
	else if (cmd[*i] == '<' && cmd[*i + 1] != '<')
	{
		if (*first == 0)
			*first = 1;
	}
	else if (cmd[*i] == '<' && cmd[*i + 1] == '<')
	{
		if (*first == 0)
			*first = 1;
		*i += 1;
	}
	else if (cmd[*i] == '>' && cmd[*i + 1] == '>')
	{
		if (*first == 0)
			*first = 1;
		*i += 1;
	}
}

int	check_redir_syntax(char *cmd, int i, int *last, int *first)
{
	check_double(cmd, &i, first);
	if (cmd[i] == '|')
	{
		if (check_pipe_syntax(*last))
			return (1);
		*first = 0;
		*last = 3;
	}
	else
	{
		if (*first == 1)
		{
			*last = 2;
			*first = 2;
			return (0);
		}
		if (check_io_syntax(cmd, i, last))
			return (1);
		*last = 2;
	}
	if (cmd[i + 1] == '\0')
		return (message(), 1);
	i++;
	return (0);
}

int	syntax_loop(char *cmd, int *last, int first)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == ' ' || cmd[i] == '\t')
			continue ;
		else if (cmd[i] == '<' || cmd[i] == '|' || cmd[i] == '>')
		{
			if (check_redir_syntax(cmd, i, last, &first) == 1)
				return (1);
			i = update_index_redir(cmd, i);
		}
		else
		{
			i = update_index(cmd, i);
			*last = 1;
		}
	}
	return (0);
}

int	check_syntax(char *cmd)
{
	int	last;
	int	first;

	last = 3;
	first = 0;
	if (cmd[0] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	if (syntax_loop(cmd, &last, first) == 1)
		return (1);
	if (last == 2 || last == 3)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	return (0);
}

int	check_cmds_syntax(char *cmds, t_prompt *prompt)
{
	if (check_syntax(prompt->input) == 1)
	{
		free(cmds);
		prompt->exit_status = 2;
		return (1);
	}
	return (0);
}
