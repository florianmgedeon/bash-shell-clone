/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exec_errs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:15:41 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 16:19:35 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_err(t_prompt *prompt, t_fds *fds, t_parser *p)
{
	free_fire(prompt, p);
	free(fds);
	exit(0);
}

void	path_err(t_prompt *prompt, t_parser *pars, t_fds *fds, t_parser *p)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(pars->cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_fire(prompt, p);
	free(fds);
	exit(127);
}

void	execve_err(t_prompt *pr, t_parser *pars, t_fds *fds, t_parser *p)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(pars->cmd, 2);
	ft_putendl_fd(": command not found", 2);
	free(fds);
	free_fire(pr, p);
	exit(127);
}
