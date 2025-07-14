/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:30:26 by fgedeon           #+#    #+#             */
/*   Updated: 2024/04/22 17:37:42 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	read_line_and_handle_signals(int fd, char **line)
{
	*line = NULL;
	g_status = 0;
	start_signals();
	*line = readline(HD);
	if (g_status == 1)
	{
		if (*line)
			free(*line);
		close(fd);
		g_status = 0;
		return (1);
	}
	return (0);
}

int	init_hdl(char **in, char **tmp, char **hdd, t_prompt *pro)
{
	*in = NULL;
	*tmp = NULL;
	remove_newline(hdd, pro);
	return (0);
}

void	write_and_free(int fd, char *tmp)
{
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
}

void	init_delim(t_parser *p, t_prompt *prompt, int i)
{
	char	*tmp;
	char	*res;

	tmp = NULL;
	res = NULL;
	tmp = ft_strdup(p->tokens[i + 1]);
	if (!tmp)
		malloc_fail(prompt);
	res = remove_quotes(tmp);
	if (!res)
		malloc_fail(prompt);
	p->hd_delimiter = ft_strdup(res);
	if (!p->hd_delimiter)
	{
		free(tmp);
		free(res);
		malloc_fail(prompt);
	}
	free(res);
}
