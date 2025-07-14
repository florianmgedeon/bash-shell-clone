/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:35:43 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/23 13:31:56 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

void	empty_input(t_prompt *prompt, t_parser *parser)
{
	int	exit_status;

	printf("exit\n");
	exit_status = prompt->exit_status;
	free_fire(prompt, parser);
	exit(exit_status);
}

int	justspaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **arg, char **envp)
{
	char		*input;
	t_prompt	*prompt;
	t_parser	*parser;

	(void)ac;
	(void)arg;
	init_all(&prompt, &parser, envp);
	while (1)
	{
		init_loop(prompt);
		input = readline(PROMPT);
		if (!input)
			empty_input(prompt, parser);
		if (justspaces(input))
		{
			free(input);
			continue ;
		}
		if (init_and_check(input, prompt))
			continue ;
		if (init_pars(prompt, parser))
			continue ;
	}
	free_fire(prompt, parser);
	return (0);
}

/* int	main(int ac, char **arg, char **envp)
{
	char		*input;
	t_prompt	*prompt;
	t_parser	*parser;
	char		*line2;
	int			exit_status;

	(void)ac;
	(void)arg;
	line2 = NULL;
	exit_status = 0;
	init_all(&prompt, &parser, envp);
	//print_minishell();
	while (1)
	{
		init_loop(prompt);
		if (isatty(fileno(stdin)))
			input = readline(PROMPT);
		else
		{
			line2 = get_next_line(fileno(stdin));
			if (!line2)
				exit(0);
			input = ft_strtrim(line2, "\n");
			free(line2);
		}
		if (!input)
		{
			printf("exit\n"); //UNCOMMENT BEFORE TURN IN!!!!
			exit_status = prompt->exit_status;
			free_fire(prompt, parser);
			exit(exit_status);
		}
		if (justspaces(input))
		{
			free(input);
			continue ;
		}
		if (init_and_check(input, prompt))
			continue ;
		if (init_pars(prompt, parser))
			continue ;
	}
	free_fire(prompt, parser);
	return (0);
} */
