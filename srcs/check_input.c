/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:34:25 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/16 15:20:04 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	isempty(t_prompt *prompt)
{
	int	i;

	i = 0;
	while (prompt->input[i])
	{
		if (prompt->input[i] != ' ' || prompt->input[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	check_quotes_input(t_prompt *prompt, t_qoutes *q)
{
	int	i;

	i = 0;
	while (prompt->input[i])
	{
		if (prompt->input[i] == '\'' && q->dq == 0)
			q->sq = alternate_qoute(*q, '\'');
		if (prompt->input[i] == '\"' && q->sq == 0)
			q->dq = alternate_qoute(*q, '\"');
		i++;
	}
}

int	check_input(t_prompt *prompt)
{
	t_qoutes	q;

	q.sq = 0;
	q.dq = 0;
	if (isempty(prompt))
	{
		free(prompt->input);
		return (1);
	}
	check_quotes_input(prompt, &q);
	if (q.sq == 1 || q.dq == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		free(prompt->input);
		prompt->exit_status = 2;
		return (1);
	}
	return (0);
}
