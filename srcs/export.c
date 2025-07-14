/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:41:43 by fgedeon           #+#    #+#             */
/*   Updated: 2024/03/28 16:54:40 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_out_quotes(int *i, bool *quote_flag, int *l, int *j)
{
	*quote_flag = false;
	*i = 0;
	*l = 0;
	*j = 0;
}

char	*take_out_quotes(char *av)
{
	int		i;
	bool	quote_flag;
	int		l;
	char	*quoteless;
	int		j;

	init_out_quotes(&i, &quote_flag, &l, &j);
	quoteless = NULL;
	quote_flag = check_for_quotes(av, &i);
	if (quote_flag == false)
		return (av);
	l = ft_strlen(av);
	quoteless = (char *)malloc(sizeof(char) * (l + 1));
	if (quoteless == NULL)
		return (perror("malloc error"), NULL);
	i = 0;
	if (quote_flag == true && av && av[i] && av[i] != '\0')
		process_quotes(av, quoteless, &i, &j);
	quoteless[j] = '\0';
	free(av);
	av = quoteless;
	return (av);
}

int	ft_export(int ac, char **av, char ***envp)
{
	char	**tmp;
	int		result;
	int		i;

	export_init(&i, &tmp, &result, envp);
	if (ac == 1)
	{
		if (print_env_vars(envp) == 1)
			return (errno);
		else
			return (0);
	}
	while (i < ac)
	{
		if (e_ft_syntax_error(av[i]) == 1)
			return (write_error_custom(av[i]), 1);
		i++;
	}
	result = process_quotes_ex(ac, av);
	if (result != 0)
		return (result);
	result = process_args(ac, av, envp, &tmp);
	if (result != 0)
		return (result);
	return (0);
}
