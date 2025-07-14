/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:23:42 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 16:37:15 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_token(t_prompt	*prompt, t_token *token, t_type type)
{
	t_token	*tmp;

	token->type = type;
	if (prompt->token == NULL)
		prompt->token = token;
	else
	{
		tmp = prompt->token;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = token;
	}
}

void	new_token(char **cmds, t_prompt *prompt, t_index *i, t_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(i);
		malloc_fail(prompt);
	}
	token->value = ft_strdup(cmds[i->i]);
	if (!token->value)
	{
		free(token);
		free(i);
		malloc_fail(prompt);
	}
	token->next = NULL;
	token->cmd = i->j;
	add_token(prompt, token, type);
}

void	handle_redirect(char **cmds, t_prompt *prompt, t_index *index)
{
	if (cmds[index->i][0] == '|')
	{
		index->j++;
		new_token(cmds, prompt, index, TOKEN_PIPE);
	}
	else if (cmds[index->i][0] == '>')
	{
		if (cmds[index->i + 1] && cmds[index->i + 1][0] == '>')
		{
			free(cmds[index->i]);
			cmds[index->i] = ft_strdup(">>");
			new_token(cmds, prompt, index, TOKEN_REDIR_APPEND);
			index->i++;
		}
		else
			new_token(cmds, prompt, index, TOKEN_REDIR_OUT);
	}
	else if (cmds[index->i][0] == '<')
	{
		if (cmds[index->i + 1] && cmds[index->i + 1][0] == '<')
			hd_alloc(cmds, prompt, index);
		else
			new_token(cmds, prompt, index, TOKEN_REDIR_IN);
	}
}

void	handle_word(char **cmds, t_prompt *prompt, t_index *index)
{
	int			i;
	t_qoutes	q;

	i = 0;
	q.sq = 0;
	q.dq = 0;
	while (cmds[index->i][i] != '\0')
	{
		if (cmds[index->i][i] == '\'')
			q.sq = alternate_qoute(q, '\'');
		if (cmds[index->i][i] == '\"')
			q.dq = alternate_qoute(q, '\"');
		i++;
		if (q.sq == 0 && q.dq == 0 && ft_strchr_2(" \t|><", cmds[index->i][i]))
			break ;
	}
	new_token(cmds, prompt, index, TOKEN_WORD);
}

void	tokenize(t_prompt *prompt, char **cmds)
{
	t_index	*index;

	index = malloc(sizeof(t_index));
	if (index == NULL)
		malloc_fail(prompt);
	index->i = 0;
	index->j = 1;
	index->k = 0;
	while (cmds && cmds[index->i] != NULL)
	{
		if (cmds[index->i] != NULL && cmds[index->i][0] != '\0')
		{
			if (ft_strchr_2("<|>", cmds[index->i][0]))
				handle_redirect(cmds, prompt, index);
			else
				handle_word(cmds, prompt, index);
		}
		index->i++;
	}
	free(index);
}
/*
index->i = 0; index
index->j = 1; cmd_count
index->k = 0; hd
*/
