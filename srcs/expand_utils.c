/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:26:46 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 17:27:48 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_char(char *str, char c)
{
	char	*new;
	int		length;

	length = 0;
	if (str == NULL)
	{
		str = malloc(1 * sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	while (str[length] != '\0')
		length++;
	new = malloc ((length + 2) * (sizeof(char)));
	if (new != NULL)
	{
		length = -1;
		while (str[++length] != '\0')
			new[length] = str[length];
		new[length] = c;
		new[++length] = '\0';
	}
	free(str);
	return (new);
}

int	update_pos(char *input, int i)
{
	int	j;

	j = 0;
	while (input[i + ++j])
	{
		if (!ft_isalnum(input[i + j]) && input[i + j] != '_')
			break ;
	}
	return (j);
}

char	*find_var(char *input, int i)
{
	int		j;
	char	*var;

	j = 1;
	while (input[i + j] && (ft_isalnum(input[i + j]) || input[i + j] == '_'))
		j++;
	if (!ft_isalnum(input[i + j]) && input[i + j] != '_')
	{
		var = ft_substr(input, i + 1, j - 1);
		if (!var)
		{
			free(input);
			return (NULL);
		}
	}
	else
		var = ft_substr(input, i + 1, j);
	if (!var)
	{
		free(input);
		return (NULL);
	}
	return (var);
}

char	*ft_strjoin_dollar2(char *res, char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	free(s1);
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin_dollar(char *s1, char *s2)
{
	char	*res;

	if (!s1)
	{
		s1 = ft_strdup("");
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	res = ft_strjoin_dollar2(res, s1, s2);
	return (res);
}
/*
char	*get_env_var(char *var, t_prompt *prompt)
{
	int i;
	char *res;

	i = 0;
	while (prompt->envp[i])
	{
		if (ft_strncmp(prompt->envp[i], var, ft_strlen(var)) == 0)
		{
			res = ft_strdup(prompt->envp[i] + ft_strlen(var) + 1);
			return (res);
		}
		i++;
	}
	return (NULL);
} */
