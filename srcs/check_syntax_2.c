/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:47:12 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/22 11:56:39 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	update_index_redir(char *cmd, int i)
{
	if ((cmd[i] == '<' && cmd[i + 1] == '<')
		|| (cmd[i] == '>' && cmd[i + 1] == '>'))
		i++;
	return (i);
}

int	update_index(char *cmd, int i)
{
	t_qoutes	q;

	q.sq = 0;
	q.dq = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '<' || cmd[i] == '|' || cmd[i] == '>'
				|| cmd[i] == ' ' || cmd[i] == '\t') && q.sq == 0 && q.dq == 0)
			break ;
		if (cmd[i] == '\'' && q.dq == 0)
			q.sq = alternate_qoute(q, '\'');
		if (cmd[i] == '\"' && q.sq == 0)
			q.dq = alternate_qoute(q, '\"');
		i++;
	}
	return (i - 1);
}

int	find_last_redir(char *cmd, int i)
{
	if ((cmd[i] == '>' && cmd[i + 1] == '>')
		|| (cmd[i] == '>' && cmd[i + 1] == '>'))
		i--;
	while (i >= 0)
	{
		if (i >= 1)
		{
			if (cmd[i] == '<' && cmd[i - 1] == '<')
				return (3);
			else if (cmd[i] == '>' && cmd[i - 1] == '>')
				return (4);
		}
		if (cmd[i] == '>')
			return (1);
		if (cmd[i] == '<')
			return (2);
		i--;
	}
	return (0);
}

int	check_pipe_syntax(int last)
{
	if (last == 3 || last == 2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}

int	check_io_syntax(char *cmd, int i, int *last)
{
	if (*last != 1)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		if (find_last_redir(cmd, i) == 1)
			ft_putstr_fd(">'\n", 2);
		else if (find_last_redir(cmd, i) == 2)
			ft_putstr_fd("<'\n", 2);
		else if (find_last_redir(cmd, i) == 3)
			ft_putstr_fd("<<'\n", 2);
		else if (find_last_redir(cmd, i) == 4)
			ft_putstr_fd(">>'\n", 2);
		else
			ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}
