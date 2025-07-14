/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:31:32 by aszabo            #+#    #+#             */
/*   Updated: 2024/04/23 13:26:51 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/ioctl.h>

# define PROMPT "\001\e[32m\002minishell$ \001\e[0m\002"
# define HD ">"

extern int	g_status;

typedef enum e_type
{
	TOKEN_PIPE,
	TOKEN_HEREDOC,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_WORD,
	TOKEN_ARG,
	TOKEN_CMD,
}					t_type;

typedef struct s_token
{
	t_type			type;
	int				hd;
	int				cmd;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_fds
{
	int				fd_in;
	int				fd_out;
	int				pipe_fd[2];
}					t_fds;

typedef struct s_env
{
	bool			printed;
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_parser
{
	char			*cmd;
	char			*cmd_path;
	char			**cmd_args;
	char			**tokens;
	char			*infile;
	char			*outfile;
	int				fd_in;
	int				fd_out;
	char			*hd_delimiter;
	bool			quoted_hd;
	bool			quote_delim;
	bool			in_child;
	pid_t			cmdpid;
	struct s_parser	*next;
}			t_parser;

typedef struct s_prompt
{
	char		**envp;
	t_token		*token;
	t_parser	**parser;
	char		*input;
	pid_t		pid;
	int			cmd_count;
	int			exit_status;
	int			i;
	bool		in_heredoc;
	bool		in_execve;
	int			end_hd;
	int			executing;
}			t_prompt;

typedef struct s_qoutes
{
	int				sq;
	int				dq;
}					t_qoutes;

typedef struct s_index
{
	int				i;
	int				j;
	int				k;
}					t_index;

		/* PROMPT */
void		init_prompt(t_prompt *prompt, char **envp);
void		print_env(char **envp);
void		init_all(t_prompt **prompt, t_parser **parser, char **envp);
void		set_shlvl(char **envp);
char		**copy_array(char **envp);
			/*MAIN*/
int			init_and_check(char *input, t_prompt *prompt);
int			init_pars(t_prompt *prompt, t_parser *parser);
int			check_input(t_prompt *prompt);
int			check_cmds_syntax(char *cmds, t_prompt *prompt);
void		init_loop(t_prompt *prompt);

		/*SYNTAX_CHECK*/
int			check_io_syntax(char *cmd, int i, int *last);
int			check_pipe_syntax(int last);
int			find_last_redir(char *cmd, int i);
int			update_index(char *cmd, int i);
int			update_index_redir(char *cmd, int i);
		/*HELPER PRINTS*/
void		print_parser(t_parser *parser);
void		print_list(t_token *token);

		/* LEXER */
void		*check_args(char *input, t_prompt *prompt);
char		**split_cmds(const char *str, char *set);
char		**subsplit_cmds(char **cmds);
void		replace_cmds_loop(char **new_cmds, char **subsplit, t_index *index);
char		**ft_arraycpy(char **src);
int			ft_arrlen(char **str);
void		print_cmds(char **cmds);
void		tokenize(t_prompt *prompt, char **cmds);
void		new_token(char **cmds, t_prompt *prompt, t_index *i, t_type type);

			/* $ EXPANSION */
char		*expander(char *input, t_prompt *prompt);
char		*expand_vars(char *input, t_prompt *prompt, t_qoutes q, char *res);
char		*handle_dollar(char *input, char *res, t_prompt *prompt, int i);
char		*handle_dollar2(char *res, t_prompt *prompt, char *var);
char		*handle_char(char *input, char *res, t_prompt *prompt);
char		*handle_question(t_prompt *prompt, char *res);
			/*$ EXPANSION UTILS*/
void		check_quotes(t_prompt *prompt, t_qoutes *q);
void		check_quotes_str(char *input, t_prompt *prompt, t_qoutes *q);
char		*find_var(char *input, int i);
int			update_pos(char *input, int i);
char		*add_char(char *str, char c);
char		*ft_strjoin_dollar(char *s1, char *s2);
char		*ft_strjoin_dollar2(char *res, char *s1, char *s2);
char		*get_env_var(char *var, t_prompt *prompt);
int			alternate_qoute(t_qoutes q, char c);
			/* HEREDOC */
char		*check_heredoc(char *input, char *res, t_prompt *prompt);
char		*handle_heredoc(char *input, char *res, t_prompt *prompt);
char		*expand_heredoc(char *input, t_prompt *prompt);

			/* PARSER */
int			parsing(t_parser **p, t_prompt *prompt, t_token *token);
void		new_node(t_parser *p, t_parser **h, t_token *pt, t_prompt *pr);
t_parser	*add_new(t_parser *p, t_token *ptoken, t_prompt *prompt);
void		add_new_2(t_parser *node, t_parser *p, t_prompt *prompt);
void		fill_node(t_parser *node, t_token *ptok, t_parser *p, t_prompt *pr);
t_parser	*alloc_new_node(t_parser *p, t_prompt *prompt, int size);
void		init_node_files(t_parser *node);
void		free_parse_node(t_parser *node);
void		init_parse_node(t_parser *new);
void		init_parser(t_parser **p, t_prompt *prompt);
char		*get_cmd_path(char *cmd, t_parser *p, t_prompt *prompt);
int			check_redir(t_type type);
char		*get_cmd(char *cmd, t_prompt *prompt);
void		handle_redir(t_parser *n, t_token *ptok, t_parser *p, t_prompt *pr);
char		**fill_args(char **tokens, t_parser *p, t_prompt *prompt);
int			check_redir_str(char *str);
void		fill_fail(char **args, char **tk, t_parser *node, t_prompt *prompt);
char		*remove_quotes(char *cmd);
int			ft_lstsize_pars(t_token *lst);
void		get_type(t_parser *node, t_token *ptok, t_parser *p, t_prompt *pr);
char		**alloc_arr(char **tokens, t_parser *p, t_prompt *prompt);
void		remove_parser_qoutes(t_parser *parser, t_prompt *prompt);

			/*REDIRECT*/
int			redirect(t_parser *p, t_prompt *prompt);
int			fac_last(char **tokens, char *str, int index);
void		redir_append(t_parser *p, t_prompt *prompt, int index);
void		redir_out(t_parser *p, t_prompt *prompt, int index);
int			redir_in(t_parser *p, t_prompt *prompt, int index, t_parser *p1);
void		update_redirs(t_parser *p, t_prompt *prompt, int fd, int i_m[2]);

			/* EXECUTE */

void		execute(t_prompt *prompt, t_parser *p);
void		executor(t_prompt *prompt, t_parser *p);
void		executor_2(t_prompt *pr, t_parser *pars, t_fds *fds, t_parser *p);
void		parent(t_prompt *prompt, t_parser *pars, pid_t pid, t_fds *fds);
void		child(t_prompt *prompt, t_parser *pars, t_fds *fds, t_parser *p);
int			check_builtin(t_prompt *prompt, t_parser *pars);
void		setup_fds(t_parser *pars, t_fds *fds);
void		setup_redir_fds(t_parser *pars, int in_fd, int out_fd);
void		close_fds(t_parser *pars, t_fds *fds);
void		simple_here(t_parser *pars, t_prompt *pr, t_fds *fds, t_parser *p);
void		ctrl_c2(int sig);

			/* ERRORS */
void		malloc_fail(t_prompt *prompt);
void		free_fire(t_prompt *prompt, t_parser *parser);
void		builtin_err(t_prompt *prompt, t_fds *fds, t_parser *p);
void		execve_err(t_prompt *pr, t_parser *pars, t_fds *fds, t_parser *p);
void		path_err(t_prompt *prompt, t_parser *pars, t_fds *fds, t_parser *p);
void		free_parser(t_parser *parser);
void		free_list(t_token *token);
void		free_loop(t_prompt *prompt, t_parser *parser);

			/* BUILTINS */
int			ft_cd(int ac, char **av, char **envp);
int			ft_echo(char **argv);
int			ft_env(char **envp);
void		exit_prev(t_prompt *prompt, t_parser *p, int previous, t_fds *fds);
void		exit_with_error(t_prompt *prompt, t_parser *p, t_fds *fds);
int			exit_args(void);
int			exit_ac2(t_parser *p, t_prompt *prompt, t_fds *fds);
int			is_of(char *av);
int			is_not_num(char *str);
int			ft_exit(t_parser *p, int prev_ex, t_prompt *prompt, t_fds *fds);

void		free_envp(char **envp, int env_size);
char		**add_env_var(char **envp, char *new_env);
int			e_just_numbers(char *av);
int			e_ft_syntax_error(char *av);
int			allocate_next_env(t_env **c, char ***envp, int i);
bool		process_env_var(t_env **c, char ***envp, int i, int *equ_nul);
bool		assign_value(t_env **c, char ***envp, int i, int equ_nul);
void		init_vars(int *i, int *equ_nul, bool *flag, t_env **ee);
t_env		*init_env_export(char ***envp);
int			ft_structsize(t_env *env_export);
int			e_ft_strcmp(char *s1, char *s2);
void		print_export_env(t_env *env_export);
int			print_env_vars(char ***envp);
bool		is_same_var(char *s1, char *s2);
bool		check_existing_var(char *current_arg, char **tmp);
char		*copy_and_format_env(char *av, char *new_env);
char		*create_new_env(char *av, char ***envp, char ***tmp);
char		*create_copy_of_string(int i, char **av);
int			replace_existing_var(int i, char **av, char ***envp, char ***tmp);
void		e_custom_init_3(int *i, bool *same_flag, int *result);
void		write_error_custom(char *av);
int			process_args(int ac, char **av, char ***envp, char ***tmp);
bool		check_for_quotes(char *av, int *i);
void		process_quotes(char *av, char *quoteless, int *i, int *j);
int			is_valid_char(char c);
void		init_out_quotes(int *i, bool *quote_flag, int *l, int *j);
void		export_init(int *i, char ***tmp, int *result, char ***envp);
int			process_quotes_ex(int ac, char **av);
char		*take_out_quotes(char *av);
int			ft_export(int ac, char **av, char ***envp);
int			ft_pwd(void);
void		u_print_error_message(char *av);
int			ft_unset(int ac, char **av, char **envp);
int			is_builtin(t_prompt *prompt, t_parser *parser, t_fds *fds);
void		init_cd(char **old_pwd, char **home);

/* REDIR HEREDOC */
int			redir_heredoc(t_parser *p, t_prompt *prompt, int i);
char		*hd_trim_join(char **in, char *tmp, char *line, t_prompt *prompt);
int			delim_check(char *input, t_parser *p, char *tmp);
int			line_just_newline(char *line, t_parser *p);
void		setup_hd_redir(t_parser *p, t_prompt *prompt, char *file, int fd);
void		hd_quotes(t_parser *p, int i);
int			read_line_and_handle_signals(int fd, char **line);
int			init_hdl(char **in, char **tmp, char **hdd, t_prompt *pro);
void		init_delim(t_parser *p, t_prompt *prompt, int i);
void		write_and_free(int fd, char *tmp);
void		remove_newline(char **str, t_prompt *prompt);

/* UTILS*/
int			ft_arraylen(char **array);
void		message(void);
void		hd_alloc(char **cmds, t_prompt *prompt, t_index *index);

/* SIGNALS */
void		start_signals(void);
t_prompt	*detour_handler(int signal, t_prompt *prompt_first);
void		signal_handler(int signal, siginfo_t *info, void *context);
void		handle_in_execve(t_prompt *prompt);
void		handle_in_heredoc(t_prompt *prompt);
void		handle_in_terminal(t_prompt *prompt);

#endif