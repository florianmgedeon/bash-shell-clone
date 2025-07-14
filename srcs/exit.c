/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:57:44 by fgedeon           #+#    #+#             */
/*   Updated: 2024/04/18 17:30:50 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_not_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '+' && str[i] != '-' && !(str[i] >= '0' && str[i] <= '9'))
		return (1);
	if ((str[i] == '+' || str[i] == '-') && !(str[i + 1] >= '0' && str[i
				+ 1] <= '9'))
		return (1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static void	custom_init_3(char **a, char **b, char **c)
{
	*a = "9223372036854775807";
	*b = "+9223372036854775807";
	*c = "-9223372036854775808";
}

int	check_overflow(char *av, char *llong_max_str, char *llong_max_plus_str,
		char *llong_min_str)
{
	int	av_len;

	av_len = ft_strlen(av);
	if (av[0] == '-')
	{
		if (av_len == 20 && ft_strncmp(av, llong_min_str, av_len) > 0)
			return (1);
	}
	else if (av[0] == '+')
	{
		if (av_len == 20 && ft_strncmp(av, llong_max_plus_str, av_len) > 0)
			return (1);
	}
	else
	{
		if (av_len > 19 || (av_len == 19 && ft_strncmp(av, llong_max_str,
					av_len) > 0))
			return (1);
	}
	return (0);
}

int	is_of(char *av)
{
	char	*llong_max_str;
	char	*llong_max_plus_str;
	char	*llong_min_str;
	int		av_len;

	custom_init_3(&llong_max_str, &llong_max_plus_str, &llong_min_str);
	av_len = ft_strlen(av);
	if (av_len > 20)
		return (1);
	else if (av_len < 19)
		return (0);
	else
		return (check_overflow(av, llong_max_str, llong_max_plus_str,
				llong_min_str));
	return (0);
}

int	ft_exit(t_parser *p, int prev_ex, t_prompt *prompt, t_fds *fds)
{
	long	exitcode;
	int		ac;

	ac = ft_arraylen(p->cmd_args);
	if (ac == 1)
	{
		if (p->in_child == true)
			return (prev_ex);
		else
			exit_prev(prompt, p, prev_ex, fds);
	}
	if (ac == 2)
	{
		exitcode = exit_ac2(p, prompt, fds);
		return (exitcode);
	}
	if (ac > 2)
	{
		if (is_not_num(p->cmd_args[1]) == 1
			|| is_of((p->cmd_args[1])) == 1)
			exit_with_error(prompt, p, fds);
		return (exit_args());
	}
	return (0);
}
