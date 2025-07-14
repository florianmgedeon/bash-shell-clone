/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:44:44 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 15:32:52 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_parser(t_parser *parser)
{
	t_parser	*tmp;
	t_parser	*next;

	tmp = parser;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->cmd_path)
			free(tmp->cmd_path);
		free(tmp->infile);
		free(tmp->outfile);
		ft_free_strings(tmp->cmd_args);
		ft_free_strings(tmp->tokens);
		free(tmp->hd_delimiter);
		free(tmp);
		tmp = next;
	}
}

void	free_list(t_token *token)
{
	t_token	*tmp;
	t_token	*next;

	tmp = token;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
}

void	free_loop(t_prompt *prompt, t_parser *parser)
{
	free(prompt->input);
	prompt->input = NULL;
	if (prompt)
	{
		if (prompt->token)
			free_list(prompt->token);
		prompt->token = NULL;
	}
	if (parser)
	{
		free_parser(parser);
		parser = NULL;
	}
}

void	free_fire(t_prompt *prompt, t_parser *parser)
{
	(void)parser;
	if (prompt->token)
		free_list(prompt->token);
	if (parser)
		free_parser(parser);
	if (prompt->input)
		free(prompt->input);
	ft_free_strings(prompt->envp);
	free(prompt);
}

void	malloc_fail(t_prompt *prompt)
{
	ft_putstr_fd("malloc failed\n", 2);
	free_fire(prompt, *prompt->parser);
	exit(1);
}
