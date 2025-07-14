/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_qoutes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:19:11 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 17:12:23 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_wo_quotes(char *cmd, t_qoutes *q)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && !q->dq)
			q->sq = !q->sq;
		else if (cmd[i] == '\"' && !q->sq)
			q->dq = !q->dq;
		else
			len++;
		i++;
	}
	return (len);
}

char	*rm_quotes(char *cmd, int len, t_qoutes *q, t_index index)
{
	char	*res;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (cmd && cmd[index.i])
	{
		if (cmd[index.i] == '\'' && !q->dq)
		{
			q->sq = alternate_qoute(*q, '\'');
			index.i++;
			continue ;
		}
		else if (cmd[index.i] == '\"' && !q->sq)
		{
			q->dq = alternate_qoute(*q, '\"');
			index.i++;
			continue ;
		}
		else
			res[index.j++] = cmd[index.i++];
	}
	res[index.j] = '\0';
	return (res);
}

char	*remove_quotes(char *cmd)
{
	t_qoutes	q;
	t_index		*index;
	char		*res;
	int			len;

	if (!cmd)
		return (NULL);
	q.sq = 0;
	q.dq = 0;
	index = malloc(sizeof(t_index));
	if (!index)
		return (NULL);
	index->i = 0;
	index->j = 0;
	len = len_wo_quotes(cmd, &q);
	res = rm_quotes(cmd, len, &q, *index);
	if (!res)
		return (NULL);
	free(cmd);
	free(index);
	return (res);
}

void	remove_parser_qoutes(t_parser *parser, t_prompt *prompt)
{
	int			i;
	t_parser	*tmp;

	tmp = parser;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd_args[i])
		{
			tmp->cmd_args[i] = remove_quotes(tmp->cmd_args[i]);
			if (!tmp->cmd_args[i])
				malloc_fail(prompt);
			i++;
		}
		tmp = tmp->next;
	}
}
