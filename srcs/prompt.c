/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:35:12 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/22 14:03:02 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_loop(t_prompt *prompt)
{
	prompt->token = NULL;
	prompt->input = NULL;
	prompt->cmd_count = 1;
	start_signals();
}

void	init_prompt(t_prompt *prompt, char **envp)
{
	prompt->envp = copy_array(envp);
	if (!prompt->envp)
	{
		ft_putstr_fd("minishell: malloc failed\n", 2);
		exit(1);
	}
	set_shlvl(prompt->envp);
	prompt->exit_status = 0;
	start_signals();
	detour_handler(0, prompt);
}

void	init_prompt_2(t_prompt *prompt)
{
	prompt->envp = NULL;
	prompt->i = 0;
	prompt->exit_status = 0;
	prompt->executing = 0;
	prompt->end_hd = 0;
	prompt->in_heredoc = false;
	prompt->in_execve = false;
}

void	init_all(t_prompt **prompt, t_parser **parser, char **envp)
{
	*parser = NULL;
	*prompt = malloc(sizeof(t_prompt));
	if (!*prompt)
	{
		ft_putstr_fd("minishell: malloc failed\n", 2);
		exit(1);
	}
	init_prompt_2(*prompt);
	init_prompt(*prompt, envp);
	(*prompt)->parser = parser;
}
