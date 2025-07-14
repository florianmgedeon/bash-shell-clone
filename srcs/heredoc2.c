/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:03:06 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/22 13:32:21 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	hd_quotes(t_parser *p, int i)
{
	int	j;

	j = 0;
	while (p->tokens[i + 1][j])
	{
		if (p->tokens[i + 1][j] == '\'' || p->tokens[i + 1][j] == '\"')
			p->quoted_hd = true;
		j++;
	}
	j = 0;
	if (p->tokens[i + 1][j] == '\'' && p->tokens[i + 1][j + 1] == '\'')
		p->quote_delim = true;
	else if (p->tokens[i + 1][j] == '\"' && p->tokens[i + 1][j + 1] == '\"')
		p->quote_delim = true;
}

void	setup_hd_redir(t_parser *p, t_prompt *prompt, char *file, int fd)
{
	p->fd_in = open(file, O_RDONLY);
	p->infile = ft_strdup(file);
	if (p->infile == NULL)
		malloc_fail(prompt);
	close(fd);
}

int	line_just_newline(char *line, t_parser *p)
{
	if (line == NULL)
		return (1);
	if (ft_strlen(line) == 0 && !p->quote_delim)
	{
		free(line);
		return (1);
	}
	return (0);
}

int	delim_check(char *input, t_parser *p, char *tmp)
{
	if (ft_strncmp(input, p->hd_delimiter, ft_strlen(p->hd_delimiter)) == 0
		&& ft_strlen(input) == ft_strlen(p->hd_delimiter))
	{
		free(input);
		free(tmp);
		return (1);
	}
	else
		free(input);
	return (0);
}

char	*hd_trim_join(char **in, char *tmp, char *line, t_prompt *prompt)
{
	*in = ft_strtrim(line, "\n");
	if (!*in)
		malloc_fail(prompt);
	free(line);
	tmp = ft_strjoin(*in, "\n");
	if (!tmp)
		malloc_fail(prompt);
	return (tmp);
}
