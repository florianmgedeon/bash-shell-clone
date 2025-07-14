/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:58:17 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/23 12:37:51 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c2(int sig)
{
	(void)sig;
	g_status = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	child(t_prompt *prompt, t_parser *pars, t_fds *fds, t_parser *p)
{
	int	exit_code;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	setup_fds(pars, fds);
	if (check_builtin(prompt, pars) == 1)
	{
		pars->in_child = true;
		exit_code = is_builtin(prompt, pars, fds);
		close(fds->pipe_fd[0]);
		free_fire(prompt, p);
		free(fds);
		exit(exit_code);
	}
	if (check_builtin(prompt, pars) == 2)
		builtin_err(prompt, fds, p);
	simple_here(pars, prompt, fds, p);
	if (fds->fd_in != 0)
		close(fds->fd_in);
	if (!pars->cmd_path)
		path_err(prompt, pars, fds, p);
	if (execve(pars->cmd_path, pars->cmd_args, prompt->envp) == -1)
		execve_err(prompt, pars, fds, p);
}

void	parent(t_prompt *prompt, t_parser *pars, pid_t pid, t_fds *fds)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	start_signals();
	if (check_builtin(prompt, pars) == 2)
		prompt->exit_status = is_builtin(prompt, pars, fds);
	else
	{
		if (WIFEXITED(status))
			prompt->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			prompt->exit_status = WTERMSIG(status) + 128;
	}
}
