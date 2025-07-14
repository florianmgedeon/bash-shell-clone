/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:31:08 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/15 16:27:12 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_fail(char **args, char **tk, t_parser *node, t_prompt *prompt)
{
	(void)prompt;
	ft_free_strings(args);
	ft_free_strings(tk);
	free_parse_node(node);
	malloc_fail(prompt);
}

int	check_redir_str(char *str)
{
	if (str)
	{
		if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0)
			return (1);
		else if (ft_strncmp(str, ">", 1) == 0 || ft_strncmp(str, "<", 1) == 0)
			return (1);
		else
			return (0);
	}
	return (0);
}

char	**alloc_arr(char **tokens, t_parser *p, t_prompt *prompt)
{
	char	**args;
	int		i;

	i = 0;
	(void)p;
	(void)prompt;
	while (tokens[i])
		i++;
	args = (char **)malloc(sizeof(char *) * (i + 1));
	if (!args)
	{
		free_parse_node(p);
		ft_free_strings(tokens);
		malloc_fail(prompt);
	}
	return (args);
}

char	**fill_args(char **tokens, t_parser *p, t_prompt *prompt)
{
	char	**args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	args = alloc_arr(tokens, p, prompt);
	while (tokens && tokens[i])
	{
		if (!tokens[i])
			break ;
		if (check_redir_str(tokens[i]))
			i += 2;
		else
		{
			args[j] = ft_strdup(tokens[i]);
			if (!args[j])
				fill_fail(args, tokens, p, prompt);
			i++;
			j++;
		}
	}
	args[j] = NULL;
	return (args);
}
