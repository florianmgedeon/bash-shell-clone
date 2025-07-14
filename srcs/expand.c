/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:44:06 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/22 14:32:12 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_vars2(char *input, char *res, t_prompt *prompt, t_qoutes *q)
{
	if (input[prompt->i + 1] == '?')
		res = handle_question(prompt, res);
	else if (input[prompt->i + 1] == '\0')
		res = handle_char(input, res, prompt);
	else if (!ft_isalpha(input[prompt->i + 1]) && q->dq == 0)
		prompt->i++;
	else if (!ft_isalpha(input[prompt->i + 1]))
		res = handle_char(input, res, prompt);
	else
		res = handle_dollar(input, res, prompt, prompt->i);
	return (res);
}

char	*expand_vars(char *input, t_prompt *prompt, t_qoutes q, char *res)
{
	while (input[prompt->i] != '\0')
	{
		check_quotes(prompt, &q);
		if (input[prompt->i] == '<' && input[prompt->i + 1] == '<'
			&& q.sq == 0 && q.dq == 0)
			res = handle_heredoc(input, res, prompt);
		else if (input[prompt->i] == '$' && q.sq == 0)
			res = expand_vars2(input, res, prompt, &q);
		else
			res = handle_char(input, res, prompt);
	}
	if (!res)
		return (ft_strdup(""));
	return (res);
}

char	*expander(char *input, t_prompt *prompt)
{
	t_qoutes	q;
	char		*res;
	char		*tmp;

	tmp = NULL;
	prompt->i = 0;
	q.sq = 0;
	q.dq = 0;
	res = expand_vars(input, prompt, q, tmp);
	free(input);
	return (res);
}
