/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:40:04 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/23 12:37:48 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	simple_here(t_parser *pars, t_prompt *pr, t_fds *fds, t_parser *p)
{
	if (pars->hd_delimiter && !pars->cmd_args[0])
	{
		close(pars->fd_in);
		free(fds);
		free_fire(pr, p);
		exit(0);
	}
}

void	close_fds(t_parser *pars, t_fds *fds)
{
	if (fds->fd_in != 0)
		close(fds->fd_in);
	if (fds->fd_out != 1)
		close(fds->fd_out);
	if (pars->fd_in != 0 && pars->fd_in != 1)
		close(pars->fd_in);
	if (pars->fd_out != 0 && pars->fd_out != 1)
		close(pars->fd_out);
	close(fds->pipe_fd[1]);
}

void	setup_redir_fds(t_parser *pars, int in_fd, int out_fd)
{
	if (pars->infile)
	{
		in_fd = pars->fd_in;
		if (in_fd == -1)
		{
			perror("minishell");
			exit(1);
		}
		dup2(in_fd, STDIN_FILENO);
		if (in_fd != -1)
			close(in_fd);
	}
	if (pars->outfile)
	{
		out_fd = pars->fd_out;
		if (out_fd == -1)
		{
			perror("minishell");
			exit(1);
		}
		dup2(out_fd, STDOUT_FILENO);
		if (out_fd != -1)
			close(out_fd);
	}
}

void	setup_fds(t_parser *pars, t_fds *fds)
{
	int	infile_fd;
	int	outfile_fd;

	infile_fd = -1;
	outfile_fd = -1;
	if (fds->fd_in != STDIN_FILENO)
	{
		dup2(fds->fd_in, STDIN_FILENO);
		close(fds->fd_in);
	}
	if (fds->fd_out != STDOUT_FILENO)
	{
		dup2(fds->fd_out, STDOUT_FILENO);
		close(fds->fd_out);
	}
	setup_redir_fds(pars, infile_fd, outfile_fd);
}

int	check_builtin(t_prompt *prompt, t_parser *pars)
{
	if (ft_strncmp(pars->cmd, "echo", 5) == 0
		|| ft_strncmp(pars->cmd, "pwd", 4) == 0
		|| ft_strncmp(pars->cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(pars->cmd, "export", 7) == 0
		&& !pars->cmd_args[1])
		return (1);
	else if (ft_strncmp(pars->cmd, "export", 7) == 0
		|| ft_strncmp(pars->cmd, "unset", 6) == 0
		|| ft_strncmp(pars->cmd, "cd", 3) == 0
		|| ft_strncmp(pars->cmd, "exit", 5) == 0)
	{
		if (prompt->cmd_count > 1)
			return (1);
		else if (prompt->cmd_count == 1)
			return (2);
	}
	return (0);
}
