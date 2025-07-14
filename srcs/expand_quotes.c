/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:46:49 by aszabo            #+#    #+#             */
/*   Updated: 2024/03/20 19:48:02 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	alternate_qoute(t_qoutes q, char c)
{
	int	i;

	i = 0;
	if (c == '\'')
	{
		if (q.sq == 0)
			i = 1;
		else
			i = 0;
	}
	else if (c == '\"')
	{
		if (q.dq == 0)
			i = 1;
		else
			i = 0;
	}
	return (i);
}

void	check_quotes_str(char *input, t_prompt *prompt, t_qoutes *q)
{
	if (input[prompt->i] == '\'' && q->dq == 0)
		q->sq = alternate_qoute(*q, '\'');
	if (input[prompt->i] == '\"' && q->sq == 0)
		q->dq = alternate_qoute(*q, '\"');
}

void	check_quotes(t_prompt *prompt, t_qoutes *q)
{
	if (prompt->input[prompt->i] == '\'' && q->dq == 0)
		q->sq = alternate_qoute(*q, '\'');
	if (prompt->input[prompt->i] == '\"' && q->sq == 0)
		q->dq = alternate_qoute(*q, '\"');
}
