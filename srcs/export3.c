/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgedeon <fgedeon@student.42vienna.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-12 15:42:54 by fgedeon           #+#    #+#             */
/*   Updated: 2024-04-12 15:42:54 by fgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	e_ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	print_export_env(t_env *env_export)
{
	t_env	*scan;
	t_env	*log;

	scan = env_export;
	log = env_export;
	while (scan != NULL)
	{
		if (scan->printed == false)
		{
			if (e_ft_strcmp(scan->var, log->var) < 0 || log->printed == true)
				log = scan;
		}
		scan = scan->next;
	}
	if (ft_strncmp(log->var, "_", 2) != 0)
		printf("declare -x %s", log->var);
	if (log->value != NULL && (ft_strncmp(log->var, "_", 2) != 0))
		printf("=\"%s\"\n", log->value);
	else if (ft_strncmp(log->var, "_", 2) != 0)
		printf("\n");
	log->printed = true;
}

int	print_env_vars(char ***envp)
{
	t_env	*env_export;
	t_env	*start2;
	t_env	*next_node;
	int		i;

	i = 0;
	next_node = NULL;
	env_export = init_env_export(envp);
	if (env_export == NULL)
		return (perror("malloc error"), 1);
	start2 = env_export;
	i = ft_structsize(env_export);
	while (i-- > 0)
		print_export_env(env_export);
	while (start2 != NULL)
	{
		next_node = start2->next;
		free(start2->var);
		if (start2->value != NULL)
			free(start2->value);
		free(start2);
		start2 = next_node;
	}
	return (0);
}

bool	is_same_var(char *s1, char *s2)
{
	int	new_len;
	int	old_len;

	new_len = 0;
	old_len = 0;
	while (s1[new_len] && s1[new_len] != '=')
		new_len++;
	while (s2[old_len] && s2[old_len] != '=')
		old_len++;
	if (new_len != old_len)
		return (false);
	if (ft_strncmp(s1, s2, new_len) != 0)
		return (false);
	return (true);
}

bool	check_existing_var(char *current_arg, char **tmp)
{
	int		c;
	int		x;
	bool	same_flag;

	c = 0;
	x = 0;
	same_flag = false;
	while (current_arg[c] && current_arg[c] != '\0' && current_arg[c] != '='
		&& current_arg[c] != '\n')
		c++;
	while (tmp[x] != NULL && current_arg != NULL && same_flag == false)
	{
		if (is_same_var(current_arg, tmp[x]) == true)
			same_flag = true;
		x++;
	}
	return (same_flag);
}
