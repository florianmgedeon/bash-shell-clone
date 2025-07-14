/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:13:46 by fgedeon           #+#    #+#             */
/*   Updated: 2024/04/23 13:32:22 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_with_error(t_prompt *prompt, t_parser *p, t_fds *fds)
{
	close_fds(p, fds);
	free(fds);
	printf("exit\n");
	write(2, "minishell: exit: ", 17);
	write(2, p->cmd_args[1], ft_strlen(p->cmd_args[1]));
	write(2, ": numeric argument required\n", 28);
	free_fire(prompt, p);
	exit(2);
}

void	exit_prev(t_prompt *prompt, t_parser *p, int previous, t_fds *fds)
{
	close_fds(p, fds);
	free(fds);
	free_fire(prompt, p);
	printf("exit\n");
	exit(previous);
}

int	exit_args(void)
{
	printf("exit\n");
	write(2, "minishell: exit: too many arguments\n", 36);
	return (1);
}

int	exit_ac2(t_parser *p, t_prompt *prompt, t_fds *fds)
{
	int	exitcode;

	if (is_not_num(p->cmd_args[1]) == 1 || is_of((p->cmd_args[1])) == 1)
	{
		if (p->in_child == true)
		{
			write(2, "minishell: exit: ", 17);
			write(2, p->cmd_args[1], ft_strlen(p->cmd_args[1]));
			write(2, ": numeric argument required\n", 28);
			return (2);
		}
		else
			exit_with_error(prompt, p, fds);
	}
	exitcode = ft_atoi(p->cmd_args[1]);
	if (p->in_child == true)
		return (exitcode);
	close_fds(p, fds);
	free(fds);
	free_fire(prompt, p);
	printf("exit\n");
	exit(exitcode);
}
