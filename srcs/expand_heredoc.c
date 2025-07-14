/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:35:00 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/22 17:07:23 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* char	*add_char(char *str, char c)
{
	char *tmp;
	int i;

	i = 0;
	if (!str)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (tmp)
	{
		while (str[i])
		{
			tmp[i] = str[i];
			i++;
		}
		str[i] = c;
		str[i + 1] = '\0';
	}
	free(str);
	return (tmp);
}
*/

int	heredoc_len(char *input, int i)
{
	t_qoutes	q;

	q.sq = 0;
	q.dq = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	while (input[i])
	{
		if (input[i] == '\'' && q.dq == 0)
			q.sq = alternate_qoute(q, '\'');
		if (input[i] == '\"' && q.sq == 0)
			q.dq = alternate_qoute(q, '\"');
		if (ft_strchr_2("<|> \t", input[i]) && q.sq == 0 && q.dq == 0)
			break ;
		i++;
	}
	return (i);
}

char	*check_heredoc(char *input, char *res, t_prompt *prompt)
{
	t_qoutes	q;
	char		*tmp;

	q.sq = 0;
	q.dq = 0;
	tmp = ft_strdup(res);
	if (!tmp)
		malloc_fail(prompt);
	while (input[prompt->i] && (input[prompt->i] == ' '
			|| input[prompt->i] == '\t'))
		prompt->i++;
	while (input[prompt->i])
	{
		if (input[prompt->i] == '\'' && q.dq == 0)
			q.sq = alternate_qoute(q, '\'');
		if (input[prompt->i] == '\"' && q.sq == 0)
			q.dq = alternate_qoute(q, '\"');
		if (ft_strchr_2("<|> \t", input[prompt->i]) && q.sq == 0 && q.dq == 0)
			break ;
		tmp = add_char(tmp, input[prompt->i]);
		prompt->i++;
	}
	free(res);
	return (tmp);
}

char	*handle_heredoc(char *input, char *res, t_prompt *prompt)
{
	char	*tmp;

	res = handle_char(input, res, prompt);
	if (!res)
		malloc_fail(prompt);
	res = handle_char(input, res, prompt);
	if (!res)
		malloc_fail(prompt);
	res = check_heredoc(input, res, prompt);
	if (!res)
		malloc_fail(prompt);
	prompt->i = heredoc_len(input, prompt->i);
	tmp = ft_strdup(res);
	if (!tmp)
		malloc_fail(prompt);
	free(res);
	return (tmp);
}

char	*expand_heredoc_2(char *input, t_prompt *prompt, char *res, t_qoutes q)
{
	while (input[prompt->i])
	{
		check_quotes_str(input, prompt, &q);
		if (input[prompt->i] == '$' && q.sq == 0)
		{
			if (input[prompt->i + 1] == '?')
				res = handle_question(prompt, res);
			else if (input[prompt->i + 1] == '\0')
				res = handle_char(input, res, prompt);
			else if (!ft_isalpha(input[prompt->i + 1]) && q.dq == 0)
				prompt->i++;
			else if (!ft_isalpha(input[prompt->i + 1]))
				res = handle_char(input, res, prompt);
			else
				res = handle_dollar(input, res, prompt, prompt->i);
		}
		else
			res = handle_char(input, res, prompt);
	}
	return (res);
}

char	*expand_heredoc(char *input, t_prompt *prompt)
{
	t_qoutes	q;
	char		*res;
	char		*tmp;

	q.sq = 0;
	q.dq = 0;
	tmp = NULL;
	prompt->i = 0;
	res = expand_heredoc_2(input, prompt, tmp, q);
	free(input);
	if (!res)
	{
		res = ft_strdup("\0");
		if (!res)
			malloc_fail(prompt);
	}
	return (res);
}
