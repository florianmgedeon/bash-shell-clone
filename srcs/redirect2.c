/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:13:47 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/23 13:30:53 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_in_error(t_parser *p, t_prompt *prompt, char *file, t_parser *p1)
{
	(void)p;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free(file);
	prompt->exit_status = 1;
	free_loop(prompt, p1);
}

int	redir_in(t_parser *p, t_prompt *prompt, int index, t_parser *p1)
{
	int		i_m[2];
	int		fd;
	char	*file_name;

	i_m[0] = index;
	file_name = remove_quotes(ft_strdup(p->tokens[index + 1]));
	if (!file_name)
		malloc_fail(prompt);
	free(p->tokens[index + 1]);
	p->tokens[index + 1] = ft_strdup(file_name);
	if (p->fd_out != STDOUT_FILENO && p->fd_out != STDERR_FILENO)
		close(p->fd_out);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (redir_in_error(p, prompt, file_name, p1), 1);
	free(file_name);
	if (fac_last(p->tokens, "<", index) == 1)
	{
		i_m[1] = 1;
		update_redirs(p, prompt, fd, i_m);
	}
	else
		close(fd);
	return (0);
}

void	redir_out(t_parser *p, t_prompt *prompt, int index)
{
	int		i_m[2];
	int		fd;
	char	*file_name;

	i_m[0] = index;
	file_name = remove_quotes(ft_strdup(p->tokens[index + 1]));
	if (!file_name)
		malloc_fail(prompt);
	free(p->tokens[index + 1]);
	p->tokens[index + 1] = ft_strdup(file_name);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	free(file_name);
	if (fac_last(p->tokens, ">", index) == 1)
	{
		i_m[1] = 2;
		update_redirs(p, prompt, fd, i_m);
	}
	else
		close(fd);
}

void	redir_append(t_parser *p, t_prompt *prompt, int index)
{
	int		i_m[2];
	int		fd;
	char	*file_name;

	i_m[0] = index;
	file_name = remove_quotes(ft_strdup(p->tokens[index + 1]));
	if (!file_name)
		malloc_fail(prompt);
	free(p->tokens[index + 1]);
	p->tokens[index + 1] = ft_strdup(file_name);
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	free(file_name);
	if (fac_last(p->tokens, ">>", index) == 1)
	{
		i_m[1] = 3;
		update_redirs(p, prompt, fd, i_m);
	}
	else
		close(fd);
}
