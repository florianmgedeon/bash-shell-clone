/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:45:14 by fgedeon           #+#    #+#             */
/*   Updated: 2024/04/16 15:15:46 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_error_custom(char *av)
{
	write(2, "minishell: export: `", 20);
	write(2, av, ft_strlen(av));
	write(2, "': not a valid identifier\n", 26);
}

int	process_args(int ac, char **av, char ***envp, char ***tmp)
{
	int		i;
	bool	same_flag;
	int		result;

	e_custom_init_3(&i, &same_flag, &result);
	while (i < ac)
	{
		same_flag = check_existing_var(av[i], *tmp);
		if (same_flag == false)
			if (create_new_env(av[i], envp, tmp) == NULL)
				return (perror("malloc error"), errno);
		if (same_flag == true)
		{
			result = replace_existing_var(i, av, envp, tmp);
			if (result != 0)
				return (result);
		}
		i++;
	}
	return (0);
}

bool	check_for_quotes(char *av, int *i)
{
	bool	quote_flag;

	quote_flag = false;
	while (av && av[*i] && av[*i] != '\0' && quote_flag == false)
	{
		if (av[*i] == '\"' || av[*i] == '\'')
			quote_flag = true;
		(*i)++;
	}
	return (quote_flag);
}

void	process_quotes(char *av, char *quoteless, int *i, int *j)
{
	if (av)
	{
		while (av[*i] != '\0')
		{
			if (av[*i] == '\"' || av[*i] == '\'')
			{
				(*i)++;
				if (av[*i] == '\0')
					break ;
			}
			quoteless[*j] = av[*i];
			(*i)++;
			(*j)++;
		}
	}
}

void	u_print_error_message(char *av)
{
	write(2, "minishell: unset: `", 19);
	write(2, av, ft_strlen(av));
	write(2, "': not a valid identifier\n", 26);
}
