/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgedeon <fgedeon@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:49:21 by fgedeon           #+#    #+#             */
/*   Updated: 2024/03/25 16:29:26 by fgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_same_flag(char **av, char **tmp, int i, int *x)
{
	int		c;
	bool	same_flag;

	c = 0;
	same_flag = false;
	while (av[i][c] && av[i][c] != '\0')
		c++;
	same_flag = false;
	*x = 0;
	while (tmp[*x] != NULL && av[i] != NULL && same_flag == false)
	{
		if (ft_strncmp(av[i], tmp[*x], c) == 0)
		{
			if (tmp[*x][c] == '=' || tmp[*x][c] == '\0')
				same_flag = true;
		}
		(*x)++;
	}
	return (same_flag);
}

void	update_envp2(char **tmp, int x)
{
	int	l;

	l = 0;
	while (tmp[x - 1][l] != '\0')
		l++;
	free(tmp[x - 1]);
	while (tmp[x] != NULL)
	{
		tmp[x - 1] = tmp[x];
		x++;
	}
	tmp[x - 1] = NULL;
}

static int	just_numbers(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
	{
		if (ft_isdigit(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	ft_syntax_error(char *av)
{
	int	j;

	j = 0;
	if (just_numbers(av) == 1)
		return (1);
	while (av[j] != '\0')
	{
		if (ft_isalpha(av[j]) == 0 && ft_isdigit(av[j]) == 0 && av[j] != '_')
			return (1);
		if (av[j] == '=')
			return (1);
		j++;
	}
	return (0);
}

int	ft_unset(int ac, char **av, char **envp)
{
	int		i;
	int		x;
	bool	same_flag;
	char	**tmp;

	i = 1;
	x = 0;
	same_flag = false;
	tmp = envp;
	if (ac == 1)
		return (0);
	i = 1;
	while (i < ac)
	{
		if (ft_syntax_error(av[i]) == 1)
		{
			u_print_error_message(av[i]);
			return (1);
		}
		same_flag = check_same_flag(av, tmp, i, &x);
		if (same_flag == true)
			update_envp2(tmp, x);
		i++;
	}
	return (0);
}
