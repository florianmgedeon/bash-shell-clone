/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:56:02 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/22 13:30:33 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_var(char *var, t_prompt *prompt)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (prompt->envp[i])
	{
		j = 0;
		while (prompt->envp[i][j] != '=')
			j++;
		if (ft_strlen(var) != (size_t)j)
		{
			i++;
			continue ;
		}
		if (ft_strncmp(prompt->envp[i], var, j) == 0)
		{
			res = ft_strdup(prompt->envp[i] + ft_strlen(var) + 1);
			return (res);
		}
		i++;
	}
	return (ft_strdup("\0"));
}

char	*handle_char(char *input, char *res, t_prompt *prompt)
{
	char	*tmp;

	tmp = add_char(res, input[prompt->i]);
	if (!tmp)
	{
		free(res);
		return (NULL);
		malloc_fail(prompt);
	}
	prompt->i++;
	return (tmp);
}

char	*handle_question(t_prompt *prompt, char *res)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(prompt->exit_status);
	if (!tmp)
	{
		free(res);
		prompt->i += 2;
		malloc_fail(prompt);
	}
	tmp2 = ft_strjoin_dollar(res, tmp);
	if (!tmp2)
	{
		free(tmp);
		prompt->i += 2;
		malloc_fail(prompt);
	}
	free(tmp);
	prompt->i += 2;
	return (tmp2);
}

char	*handle_dollar2(char *res, t_prompt *prompt, char *var)
{
	char	*env_var;

	env_var = get_env_var(var, prompt);
	if (!env_var)
	{
		free(var);
		return (NULL);
		malloc_fail(prompt);
	}
	res = ft_strjoin_dollar(res, env_var);
	if (!res)
	{
		free(res);
		free(env_var);
		free(var);
		return (NULL);
		malloc_fail(prompt);
	}
	free(env_var);
	free(var);
	return (res);
}

char	*handle_dollar(char *input, char *res, t_prompt *prompt, int i)
{
	char	*tmp;
	char	*var;

	tmp = NULL;
	var = find_var(input, i);
	if (var[0])
		tmp = handle_dollar2(res, prompt, var);
	else
	{
		if (!res)
			tmp = ft_strdup("\0");
		else
			tmp = ft_strdup(res);
		if (!tmp)
		{
			free(res);
			malloc_fail(prompt);
		}
		free(res);
	}
	prompt->i += update_pos(input, i);
	return (tmp);
}
