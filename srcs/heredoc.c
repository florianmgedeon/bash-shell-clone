/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:55:59 by fgedeon           #+#    #+#             */
/*   Updated: 2024/04/22 17:43:15 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_newline(char **str, t_prompt *prompt)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\' && (*str)[i + 1] == 'n')
		{
			tmp = ft_substr(*str, 0, i);
			free(*str);
			*str = ft_strdup(tmp);
			if (!*str)
				malloc_fail(prompt);
		}
		i++;
	}
}

int	heredoc_check(char *line, t_parser *p, t_prompt *prompt)
{
	if (g_status == 1)
	{
		prompt->end_hd = 1;
		g_status = 0;
		if (line)
			free(line);
		return (1);
	}
	if (line == NULL)
	{
		g_status = 1;
		write (1, "\n", 1);
		ft_putstr_fd("minishell: warning: here-document ", 2);
		ft_putstr_fd("delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(p->hd_delimiter, 2);
		ft_putstr_fd("')\n", 2);
		g_status = 0;
		return (1);
	}
	return (0);
}

int	stop_hd(char *line, int fd, t_prompt *prompt)
{
	if (prompt->end_hd || !line)
	{
		close(fd);
		prompt->in_heredoc = false;
		return (1);
	}
	return (0);
}

int	heredoc_loop(t_parser *p, t_prompt *prompt, int fd)
{
	char	*line;
	char	*input;
	char	*tmp;
	int		res;

	res = init_hdl(&input, &tmp, &(p->hd_delimiter), prompt);
	while (!prompt->end_hd || g_status == 0)
	{
		res = read_line_and_handle_signals(fd, &line);
		if (res == 1)
			return (1);
		if (heredoc_check(line, p, prompt) == 1)
			break ;
		if (line_just_newline(line, p) == 1)
			continue ;
		tmp = hd_trim_join(&input, tmp, line, prompt);
		if (delim_check(input, p, tmp) == 1)
			break ;
		if (ft_strchr(tmp, '$') && !p->quoted_hd)
			tmp = expand_heredoc(tmp, prompt);
		write_and_free(fd, tmp);
	}
	if (stop_hd(input, fd, prompt) == 1)
		return (1);
	return (0);
}

int	redir_heredoc(t_parser *p, t_prompt *prompt, int i)
{
	char	tmp_file_name[50];
	int		fd;

	if (p->tokens[i + 1] == NULL)
	{
		write(2, "heredoc: syntax error near unexpected token `newline'\n", 54);
		return (1);
	}
	hd_quotes(p, i);
	init_delim(p, prompt, i);
	ft_strlcpy(tmp_file_name, "/tmp/heredoc4242421", 50);
	fd = open(tmp_file_name, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd < 0)
		return (perror("heredoc"), 1);
	prompt->in_heredoc = true;
	if (heredoc_loop(p, prompt, fd) == 1)
	{
		free_loop(prompt, p);
		return (1);
	}
	if (fac_last(p->tokens, "<<", i) == 1)
		setup_hd_redir(p, prompt, tmp_file_name, fd);
	else
		close(fd);
	return (0);
}
