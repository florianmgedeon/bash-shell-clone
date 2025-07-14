/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:49:32 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 17:37:24 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	message(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
}

void	hd_alloc(char **cmds, t_prompt *prompt, t_index *index)
{
	free(cmds[index->i]);
	cmds[index->i] = ft_strdup("<<");
	new_token(cmds, prompt, index, TOKEN_HEREDOC);
	index->i++;
	index->k = 1;
}

int	ft_arrlen(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	**ft_arraycpy(char **src)
{
	char	**dst;
	int		i;

	i = 0;
	dst = malloc(sizeof(char *) * (ft_arrlen(src) + 1));
	if (!dst)
		return (NULL);
	while (src && src[i])
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

void	replace_cmds_loop(char **new_cmds, char **subsplit, t_index *index)
{
	while (subsplit && subsplit[index->j])
	{
		new_cmds[index->k++] = ft_strdup(subsplit[index->j]);
		if (!new_cmds[index->k - 1])
			malloc_fail(NULL);
		index->j++;
	}
}
