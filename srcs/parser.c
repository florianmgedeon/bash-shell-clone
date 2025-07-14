/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:55:30 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 17:23:00 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_node(t_parser *node, t_token *ptok, t_parser *p, t_prompt *pr)
{
	int	i;

	i = 1;
	(void)p;
	node->tokens[0] = ft_strdup(ptok->value);
	if (!node->tokens[0])
	{
		free_parse_node(node);
		malloc_fail(pr);
		return ;
	}
	while (ptok->next && ptok->next->type != TOKEN_PIPE)
	{
		node->tokens[i] = ft_strdup(ptok->next->value);
		if (!node->tokens[i])
		{
			free_parse_node(node);
			malloc_fail(pr);
		}
		i++;
		ptok = ptok->next;
	}
	node->tokens[i] = NULL;
}

void	add_new_2(t_parser *node, t_parser *p, t_prompt *prompt)
{
	node->cmd = remove_quotes(node->cmd);
	if (!node->cmd)
	{
		free_parse_node(node);
		malloc_fail(prompt);
	}
	node->cmd_path = get_cmd_path(node->cmd, p, prompt);
	node->cmd_args = fill_args(node->tokens, p, prompt);
}

t_parser	*add_new(t_parser *p, t_token *ptoken, t_prompt *prompt)
{
	t_parser	*new;
	t_token		*tmp;

	tmp = ptoken;
	new = alloc_new_node(p, prompt, ft_lstsize_pars(tmp) + 2);
	if (check_redir(tmp->type) && tmp->next)
	{
		fill_node(new, tmp, p, prompt);
		handle_redir(new, ptoken, p, prompt);
		new->cmd_args = fill_args(new->tokens, p, prompt);
	}
	else
	{
		fill_node(new, ptoken, p, prompt);
		new->cmd = ft_strdup(ptoken->value);
		if (!new->cmd)
		{
			free_parse_node(new);
			malloc_fail(prompt);
		}
		add_new_2(new, p, prompt);
	}
	return (new);
}

void	new_node(t_parser *p, t_parser **h, t_token *pt, t_prompt *pr)
{
	t_parser	*new;
	t_parser	*tmp;

	tmp = *h;
	new = add_new(p, pt, pr);
	new->next = NULL;
	if (*h == NULL)
	{
		*h = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

int	parsing(t_parser **p, t_prompt *prompt, t_token *token)
{
	t_token		*ptoken;

	ptoken = token;
	while (ptoken)
	{
		new_node(*p, p, ptoken, prompt);
		while (ptoken->next && ptoken->type != TOKEN_PIPE)
			ptoken = ptoken->next;
		ptoken = ptoken->next;
	}
	return (1);
}
