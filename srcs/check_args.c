/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:34:40 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/22 15:17:26 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* void	print_cmds(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		printf("Token[%d]: %s\n", i, cmds[i]);
		i++;
	}
}

void	print_list(t_token *token)
{
	t_token	*tmp;
	int		i = 0;

	tmp = token;
	while (tmp != NULL && tmp->value != NULL)
	{
		printf("----------TOKEN[%d]----------\n", i);
		printf("Value: %s\n", tmp->value);
		printf("Type: %d\n", tmp->type);
		printf("In heredoc: %d\n", tmp->hd);
		printf("Command number: %d\n", tmp->cmd);
		tmp = tmp->next;
		i++;
	}
}

void	print_parser(t_parser *parser)
{
	t_parser	*tmp;
	int			i = 0;

	tmp = parser;
	while (tmp != NULL)
	{
		printf("----------PARSER[%d]----------\n", i);
		printf("Command: %s\n", tmp->cmd);
		printf("Command path: %s\n", tmp->cmd_path);
		printf("Command args: \n");
		print_cmds(tmp->cmd_args);
		printf("Infile: %s\n", tmp->infile);
		printf("Outfile: %s\n", tmp->outfile);
		printf("FD in: %d\n", tmp->fd_in);
		printf("FD out: %d\n", tmp->fd_out);
		tmp = tmp->next;
		i++;
	}
} */

int	lstsize_pars(t_parser *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	check_for_export(t_parser *p)
{
	if (ft_strncmp(p->cmd, "export", 7) == 0)
	{
		if (p->cmd_args[1] != NULL)
			return (1);
	}
	return (0);
}

void	empty(char **cmds, t_prompt *prompt)
{
	free(cmds);
	free(prompt->input);
}

int	init_and_check(char *input, t_prompt *prompt)
{
	char	**cmds;

	if (input[0])
		add_history(input);
	prompt->input = ft_strdup(input);
	free(input);
	if (!prompt->input)
		malloc_fail(prompt);
	if (check_input(prompt))
		return (1);
	if (check_cmds_syntax(prompt->input, prompt) == 1)
		return (1);
	prompt->input = expander(prompt->input, prompt);
	cmds = split_cmds(prompt->input, " \t");
	if (!cmds)
		malloc_fail(prompt);
	if (cmds[0][0] != '\0')
		cmds = subsplit_cmds(cmds);
	else
		return (empty(cmds, prompt), 1);
	if (!cmds)
		malloc_fail(prompt);
	tokenize(prompt, cmds);
	ft_free_strings(cmds);
	return (0);
}

int	init_pars(t_prompt *prompt, t_parser *parser)
{
	if (parsing(&parser, prompt, prompt->token))
	{
		if (redirect(parser, prompt) != 1)
			return (1);
	}
	else
		return (1);
	if (check_for_export(parser) != 1)
		remove_parser_qoutes(parser, prompt);
	prompt->cmd_count = lstsize_pars(parser);
	execute(prompt, parser);
	return (0);
}
