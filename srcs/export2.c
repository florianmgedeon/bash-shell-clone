/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgedeon <fgedeon@student.42vienna.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-12 15:42:02 by fgedeon           #+#    #+#             */
/*   Updated: 2024-04-12 15:42:02 by fgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	process_env_var(t_env **c, char ***envp, int i, int *equ_nul)
{
	bool	has_value_flag;

	has_value_flag = false;
	*equ_nul = 0;
	while ((*envp)[i][(*equ_nul)] != '=' && (*envp)[i][(*equ_nul)] != '\0'
		&& (*envp)[i][(*equ_nul)] != '\n')
		(*equ_nul)++;
	if ((*envp)[i][(*equ_nul)] == '=')
		has_value_flag = true;
	(*c)->var = (char *)malloc(sizeof(char) * ((*equ_nul) + 1));
	if ((*c)->var == NULL)
		return (false);
	ft_strlcpy((*c)->var, (*envp)[i], (*equ_nul) + 1);
	return (has_value_flag);
}

bool	assign_value(t_env **c, char ***envp, int i, int equ_nul)
{
	int	env_len;

	equ_nul++;
	env_len = ft_strlen((*envp)[i]);
	(*c)->value = malloc(sizeof(char) * (env_len - equ_nul + 1));
	if ((*c)->value == NULL)
		return (false);
	env_len = ft_strlen((*envp)[i]);
	ft_strlcpy((*c)->value, (*envp)[i] + equ_nul, env_len - equ_nul + 1);
	return (true);
}

void	init_vars(int *i, int *equ_nul, bool *flag, t_env **ee)
{
	*i = 0;
	*equ_nul = 0;
	*flag = false;
	*ee = (t_env *)malloc(sizeof(t_env));
}

t_env	*init_env_export(char ***envp)
{
	int		i;
	int		equ_nul;
	t_env	*env_export;
	t_env	*c;
	bool	has_value_flag;

	init_vars(&i, &equ_nul, &has_value_flag, &env_export);
	if (env_export == NULL)
		return (NULL);
	c = env_export;
	while ((*envp)[i] != NULL)
	{
		has_value_flag = process_env_var(&c, envp, i, &equ_nul);
		if (!has_value_flag && c->var == NULL)
			return (NULL);
		c->value = NULL;
		if (has_value_flag == true)
			if (!assign_value(&c, envp, i, equ_nul))
				return (NULL);
		c->printed = false;
		if (allocate_next_env(&c, envp, i) == -1)
			return (NULL);
		i++;
	}
	return (env_export);
}

int	ft_structsize(t_env *env_export)
{
	int	i;

	i = 0;
	while (env_export != NULL)
	{
		i++;
		env_export = env_export->next;
	}
	return (i);
}
