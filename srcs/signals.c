/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:48:09 by fgedeon           #+#    #+#             */
/*   Updated: 2024/04/15 16:38:29 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_all_sigint(t_prompt *prompt)
{
	if (prompt->in_execve == true)
		handle_in_execve(prompt);
	else if (prompt->in_heredoc == true)
		handle_in_heredoc(prompt);
	else
		handle_in_terminal(prompt);
}

t_prompt	*detour_handler(int signal, t_prompt *prompt_first)
{
	static t_prompt	*prompt_ptr;

	if (prompt_first != NULL)
	{
		prompt_ptr = prompt_first;
		return (prompt_ptr);
	}
	if (prompt_ptr == NULL)
		return (NULL);
	if (signal == SIGINT)
		handle_all_sigint(prompt_ptr);
	return (prompt_ptr);
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	t_prompt	*prompt;

	(void)info;
	(void)context;
	prompt = detour_handler(signal, NULL);
	if (prompt == NULL)
		return ;
	detour_handler(signal, prompt);
}

void	start_signals(void)
{
	struct sigaction	sa_sig;

	ft_bzero(&sa_sig, sizeof(sa_sig));
	sa_sig.sa_sigaction = &signal_handler;
	sa_sig.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa_sig, NULL);
	signal(SIGQUIT, SIG_IGN);
}
