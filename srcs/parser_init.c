/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:40:36 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/22 13:23:39 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_parse_node(t_parser *new)
{
	new->tokens = NULL;
	new->cmd = NULL;
	new->cmd_path = NULL;
	new->cmd_args = NULL;
	new->next = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->fd_in = 0;
	new->fd_out = 1;
	new->cmdpid = 0;
	new->quoted_hd = false;
	new->quote_delim = false;
	new->in_child = false;
	new->hd_delimiter = NULL;
}

void	free_parse_node(t_parser *node)
{
	if (!node)
		return ;
	ft_free_strings(node->tokens);
	ft_free_strings(node->cmd_args);
	if (node->cmd)
		free(node->cmd);
	if (node->cmd_path)
		free(node->cmd_path);
	if (node->infile)
		free(node->infile);
	if (node->outfile)
		free(node->outfile);
	free(node);
}

t_parser	*alloc_new_node(t_parser *p, t_prompt *prompt, int size)
{
	t_parser	*new;

	(void)p;
	(void)prompt;
	new = malloc(sizeof(t_parser));
	if (!new)
		malloc_fail(prompt);
	init_parse_node(new);
	new->tokens = malloc(sizeof(char *) * size);
	if (!new->tokens)
	{
		free(new);
		malloc_fail(prompt);
	}
	return (new);
}
