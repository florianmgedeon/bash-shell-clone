/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:44:53 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 16:39:14 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	executor_2(t_prompt *pr, t_parser *pars, t_fds *fds, t_parser *p)
{
	pid_t	pid;

	if (!pars->next)
	{
		fds->fd_out = 1;
		close(fds->pipe_fd[1]);
		close(fds->pipe_fd[0]);
	}
	else
		fds->fd_out = fds->pipe_fd[1];
	signal(SIGINT, ctrl_c2);
	pid = fork();
	if (pid == 0)
		child(pr, pars, fds, p);
	else if (pid < 0)
	{
		ft_putstr_fd("fork failed\n", 2);
		exit(1);
	}
	pars->cmdpid = pid;
	close_fds(pars, fds);
	fds->fd_in = fds->pipe_fd[0];
}

void	execute_loop(t_prompt *prompt, t_parser *p, t_fds *fds)
{
	t_parser	*pars;

	pars = p;
	while (pars)
	{
		if (!pars->cmd_args)
		{
			if (pars->next)
				pars = pars->next;
			else
				break ;
		}
		pipe(fds->pipe_fd);
		executor_2(prompt, pars, fds, p);
		pars = pars->next;
	}
}

void	executor(t_prompt *prompt, t_parser *p)
{
	t_parser	*pars;
	t_fds		*fds;

	prompt->in_execve = true;
	fds = malloc(sizeof(t_fds));
	if (!fds)
		malloc_fail(prompt);
	fds->fd_in = 0;
	fds->fd_out = 1;
	execute_loop(prompt, p, fds);
	pars = p;
	while (pars)
	{
		parent(prompt, pars, pars->cmdpid, fds);
		pars = pars->next;
	}
	if (fds)
		free(fds);
	prompt->in_execve = false;
}

void	execute(t_prompt *prompt, t_parser *p)
{
	executor(prompt, p);
	free_loop(prompt, p);
}
