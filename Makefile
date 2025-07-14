# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 15:34:32 by aszabo            #+#    #+#              #
#    Updated: 2024/04/23 13:00:14 by aszabo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

VALGRIND	=	valgrind --leak-check=full --show-leak-kinds=all --suppressions=valgrind.txt --track-origins=yes #--track-fds=yes

SRCS = 	srcs/main.c \
		srcs/prompt.c \
		srcs/prompt2.c \
		srcs/check_input.c \
		srcs/check_syntax.c \
		srcs/check_syntax_2.c \
		srcs/utils.c \
		srcs/expand.c \
		srcs/expand_heredoc.c \
		srcs/expand_utils.c \
		srcs/expand_handle.c \
		srcs/expand_quotes.c \
		srcs/check_args.c \
		srcs/split_cmds.c \
		srcs/subsplit_cmds.c \
		srcs/tokenize.c \
		srcs/parser.c \
		srcs/parser_utils.c \
		srcs/parser_fill.c \
		srcs/parser_init.c \
		srcs/get_cmd_path.c \
		srcs/remove_qoutes.c \
		srcs/cd.c \
		srcs/cd2.c \
		srcs/echo.c \
		srcs/env.c \
		srcs/exit.c \
		srcs/exit1.c \
		srcs/export.c \
		srcs/export1.c \
		srcs/export2.c \
		srcs/export3.c \
		srcs/export4.c \
		srcs/export5.c \
		srcs/export6.c \
		srcs/pwd.c \
		srcs/unset.c \
		srcs/error.c \
		srcs/execute.c \
		srcs/execute_utils.c \
		srcs/execute_process.c \
		srcs/print_exec_errs.c \
		srcs/is_builtin.c \
		srcs/redirect.c \
		srcs/redirect2.c \
		srcs/heredoc.c \
		srcs/heredoc2.c \
		srcs/heredoc3.c \
		srcs/signals.c \
		srcs/signals_handle.c \
		

OBJS = $(SRCS:.c=.o)

READLINE = /Users/aszabo/.brew/opt/readline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -Iinclude -I$(READLINE)/include

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L$(READLINE)/lib -o $(NAME) -lreadline

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

valgrind: all
	$(VALGRIND) ./minishell

re: fclean all

.PHONY: all clean fclean re