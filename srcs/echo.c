/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgedeon <fgedeon@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:31:42 by fgedeon           #+#    #+#             */
/*   Updated: 2024/03/21 10:50:47 by fgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_n_and_minus(char *argv)
{
	int		c;
	int		min_counter;
	int		n_counter;

	c = 0;
	min_counter = 0;
	n_counter = 0;
	while (argv[c] != '\0')
	{
		if (argv[0] != '-')
			return (false);
		if (argv[c] == '-' || argv[c] == 'n')
		{
			if (argv[c] == '-')
				min_counter++;
			if (argv[c] == 'n')
				n_counter++;
			c++;
		}
		else
			return (false);
	}
	if (min_counter != 1 || n_counter < 1)
		return (false);
	return (true);
}

bool	is_n_flag(char *argv)
{
	int	c;

	c = 0;
	if (is_n_and_minus(argv) == false)
		return (false);
	while (argv[c] != '\0')
	{
		if (argv[c] == 'n' && argv[c + 1] == '\0')
			return (true);
		c++;
	}
	return (false);
}

void	print_argv(char **argv, bool n_option)
{
	int		c;
	int		d;
	bool	first_non_flag;

	first_non_flag = false;
	c = 1 + n_option;
	d = 0;
	while (argv[c])
	{
		if (first_non_flag == false && is_n_flag(argv[c]) == false)
			first_non_flag = true;
		if (first_non_flag == true
			|| (n_option == true && is_n_flag(argv[c]) == false)
			|| n_option == false)
		{
			d = 0;
			while (argv[c][d] != '\0')
				printf("%c", argv[c][d++]);
			if (argv[c + 1])
				printf(" ");
		}
		c++;
	}
	if (n_option == false)
		printf("\n");
}

int	handle_special_cases(bool n_option, int c)
{
	if (c == 2 && n_option == true)
		return (0);
	if (c == 1)
		return (printf("\n"), 0);
	return (0);
}

int	ft_echo(char **argv)
{
	bool	n_option;
	int		c;

	c = 0;
	n_option = false;
	if (argv[1] && argv[1] != NULL)
	{
		if (is_n_flag(argv[1]) == true)
			n_option = true;
	}
	while (argv[c])
		c++;
	if (handle_special_cases(n_option, c) != 0)
		return (0);
	if (c != 1)
		print_argv(argv, n_option);
	return (0);
}
