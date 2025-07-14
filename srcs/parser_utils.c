/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:41:32 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 16:28:55 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstsize_pars(t_token *lst)
{
	unsigned int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	check_redir(t_type type)
{
	if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

void	get_type(t_parser *node, t_token *ptok, t_parser *p, t_prompt *pr)
{
	node->cmd = ft_strdup(ptok->value);
	if (!node->cmd)
	{
		free_parse_node(node);
		malloc_fail(pr);
		return ;
	}
	node->cmd_path = get_cmd_path(node->cmd, p, pr);
}

void	handle_redir(t_parser *n, t_token *ptok, t_parser *p, t_prompt *pr)
{
	while (ptok->type != TOKEN_PIPE)
	{
		if (ptok->next && ptok->next->next)
		{
			ptok = ptok->next;
			ptok = ptok->next;
		}
		else
		{
			n->cmd = NULL;
			n->cmd_path = NULL;
			break ;
		}
		if (ptok->type == TOKEN_WORD)
		{
			get_type(n, ptok, p, pr);
			break ;
		}
		else if (ptok->next == NULL || ptok->type == TOKEN_PIPE)
		{
			n->cmd = NULL;
			n->cmd_path = NULL;
			break ;
		}
	}
}
