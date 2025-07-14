/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:23:27 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 16:02:34 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**ft_fill_array(char **cmds, const char *str, char *set, int c)
{
	int	qouted;
	int	qt;
	int	strlen;
	int	i;
	int	j;

	int_init_4(&qouted, &qt, &i, &j);
	strlen = ft_strlen(str);
	while (str[i])
	{
		while (ft_strchr(set, str[i]) && str[i] != '\0')
			i++;
		j = i;
		while (str[i] && (!ft_strchr(set, str[i]) || qouted || qt))
		{
			qouted = (qouted + (!qt && str[i] == '\'')) % 2;
			qt = (qt + (!qouted && str[i] == '\"')) % 2;
			i++;
		}
		if (j >= strlen)
			cmds[c++] = "\0";
		else
			cmds[c++] = ft_substr(str, j, i - j);
	}
	return (cmds);
}

static int	ft_count_words(const char *str, char *set, int wc, int i)
{
	int	qouted;
	int	qt;

	int_init_2(&qouted, &qt);
	while (str[i])
	{
		if (!ft_strchr(set, str[i]))
		{
			wc++;
			while ((str[i]) && (!ft_strchr(set, str[i]) || qouted))
			{
				if (!qt && (str[i] == '\'' || str[i] == '\"'))
					qt = str[i];
				qouted = (qouted + (str[i] == qt)) % 2;
				if (qouted == 0)
					qt = 0;
				i++;
			}
			if (qouted)
				return (-1);
		}
		else
			i++;
	}
	return (wc);
}

char	**return_empty(void)
{
	char	**cmds;

	cmds = (char **)malloc(sizeof(char *) * 1);
	if (!cmds)
		return (NULL);
	cmds[0] = "\0";
	return (cmds);
}

char	**split_cmds(const char *str, char *set)
{
	char	**cmds;
	int		wc;
	int		c;
	int		i;

	int_init_3(&wc, &i, &c);
	if (str[0] == '\0')
	{
		cmds = return_empty();
		return (cmds);
	}
	if (!str)
		return (NULL);
	wc = ft_count_words(str, set, c, i);
	if (wc == -1)
	{
		cmds = return_empty();
		return (cmds);
	}
	cmds = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!cmds)
		return (NULL);
	cmds = ft_fill_array(cmds, str, set, 0);
	cmds[wc] = 0;
	return (cmds);
}
