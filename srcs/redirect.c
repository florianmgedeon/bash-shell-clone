/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:36:49 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/23 13:25:36 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fac_last(char **tokens, char *str, int index)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], str, 1) == 0)
			last = i;
		i++;
	}
	if (last == index)
		return (1);
	else
		return (-1);
}

void	update_redirs(t_parser *p, t_prompt *prompt, int fd, int i_m[2])
{
	if (i_m[1] == 1)
	{
		p->fd_in = fd;
		p->infile = ft_strdup(p->tokens[i_m[0] + 1]);
		if (!p->infile)
			malloc_fail(prompt);
	}
	else if (i_m[1] == 2)
	{
		p->fd_out = fd;
		if (p->outfile)
			free(p->outfile);
		p->outfile = ft_strdup(p->tokens[i_m[0] + 1]);
		if (!p->outfile)
			malloc_fail(prompt);
	}
	else if (i_m[1] == 3)
	{
		p->fd_out = fd;
		p->outfile = ft_strdup(p->tokens[i_m[0] + 1]);
		if (!p->outfile)
			malloc_fail(prompt);
	}
}

int	redirect_2(t_parser *p, t_prompt *prompt, t_parser *p1)
{
	int	i;

	i = 0;
	while (p->tokens[i])
	{
		if (ft_strncmp(p->tokens[i], "<<", 2) == 0)
		{
			if (redir_heredoc(p, prompt, i) == 1)
				return (-1);
		}
		else if (ft_strncmp(p->tokens[i], ">>", 2) == 0)
			redir_append(p, prompt, i);
		else if (ft_strncmp(p->tokens[i], "<", 1) == 0)
		{
			if (redir_in(p, prompt, i, p1) == 1)
				return (-1);
		}
		else if (ft_strncmp(p->tokens[i], ">", 1) == 0)
			redir_out(p, prompt, i);
		i++;
	}
	return (1);
}

int	redirect(t_parser *p, t_prompt *prompt)
{
	t_parser	*tmp;

	tmp = p;
	while (tmp)
	{
		if (redirect_2(tmp, prompt, p) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (1);
}
