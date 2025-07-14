/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:17:49 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 19:11:57 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_in_terminal(t_prompt *prompt)
{
	prompt->exit_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_in_heredoc(t_prompt *prompt)
{
	prompt->exit_status = 130;
	g_status = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_in_execve(t_prompt *prompt)
{
	prompt->exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}
