/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsplit_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:55:24 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 16:37:07 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**replace_cmds(char **cmds, char **subsplit, int i)
{
	char		**new_cmds;
	t_index		index;

	int_init_3(&index.i, &index.j, &index.k);
	if (!cmds || !*cmds || i < 0 || i >= ft_arrlen(cmds))
		return (NULL);
	new_cmds = ft_calloc(ft_arrlen(cmds) + ft_arrlen(subsplit), sizeof(char *));
	while (new_cmds && cmds[index.i])
	{
		if (index.i != i)
		{
			new_cmds[index.k] = ft_strdup(cmds[index.i]);
			index.k++;
		}
		else
			replace_cmds_loop(new_cmds, subsplit, &index);
		index.i++;
	}
	ft_free_strings(cmds);
	return (new_cmds);
}

static int	word_count(const char *str, char *set, int wc)
{
	int			i;
	t_qoutes	q;

	i = 0;
	q.sq = 0;
	q.dq = 0;
	while (str && str[i])
	{
		wc++;
		if (!ft_strchr(set, str[i]))
		{
			while ((!ft_strchr(set, str[i]) || q.sq || q.dq) && str[i])
			{
				q.sq = (q.sq + (!q.dq && str[i] == '\'')) % 2;
				q.dq = (q.dq + (!q.sq && str[i] == '\"')) % 2;
				i++;
			}
			if (q.sq || q.dq)
				return (0);
		}
		else
			i++;
	}
	return (wc);
}

static char	**fill_array(char **cmds, char *str, char *set, t_index index)
{
	t_qoutes	q;

	q.sq = 0;
	q.dq = 0;
	while (str && str[index.i])
	{
		index.j = index.i;
		if (!ft_strchr(set, str[index.i]))
		{
			while ((!ft_strchr(set, str[index.i]) || q.sq || q.dq)
				&& str[index.i])
			{
				q.sq = (q.sq + (!q.dq && str[index.i] == '\'')) % 2;
				q.dq = (q.dq + (!q.sq && str[index.i] == '\"')) % 2;
				index.i++;
			}
		}
		else
			index.i++;
		cmds[index.k++] = ft_substr(str, index.j, index.i - index.j);
	}
	return (cmds);
}

char	**subsplit(char *str, char *set)
{
	char	**cmds;
	int		wc;
	t_index	index;

	index.i = 0;
	index.j = 0;
	index.k = 0;
	if (!str)
		return (NULL);
	wc = word_count(str, set, 0);
	if (!wc)
		return (NULL);
	cmds = malloc(sizeof(char *) * (wc + 1));
	if (!cmds)
		return (NULL);
	cmds = fill_array(cmds, str, set, index);
	cmds[wc] = NULL;
	return (cmds);
}

char	**subsplit_cmds(char **cmds)
{
	char	**res;
	int		i;

	i = 0;
	while (cmds && cmds[i])
	{
		res = subsplit(cmds[i], "<|>");
		cmds = replace_cmds(cmds, res, i);
		i += ft_arrlen(res) - 1;
		ft_free_strings(res);
		i++;
	}
	return (cmds);
}
