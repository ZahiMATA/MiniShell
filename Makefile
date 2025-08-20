# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 10:35:37 by ybouroga          #+#    #+#              #
#    Updated: 2025/08/20 20:21:29 by ybouroga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = \
	src/minishell.c \
	builtins/ft_cd.c \
	builtins/ft_echo.c \
	builtins/ft_env.c \
	builtins/ft_exit.c \
	builtins/ft_export.c \
	builtins/ft_pwd.c \
	builtins/ft_unset.c \
	dispatcher/dispatcher.c \
	debug/debug_display.c \
	debug/debug_token.c \
	debug/debug_cmd.c \
	debug/debug_pointer.c \
	exec/exec_init_1.c \
	exec/exec_init_2.c \
	exec/exec_redir.c \
	exec/exec_run.c \
	input/input.c \
	libft/ft_atoi.c \
	libft/ft_split.c \
	libft/ft_split_multi.c \
	libft/ft_print.c \
	libft/ft_print_fd.c \
	libft/ft_strlen.c \
	libft/ft_strcmp.c \
	libft/ft_strncmp.c \
	libft/ft_strdup.c \
	libft/ft_strjoin.c \
	libft/ft_strchr.c \
	libft/ft_typec.c \
	libft/ft_calloc.c \
	libft/ft_bzero.c \
	libft/ft_strlcat.c \
	libft/ft_itoa.c \
	libft_ms/ft_exit.c \
	libft_ms/ft_return.c \
	libft_ms/ft_lstnew_env.c \
	libft_ms/ft_lstadd_back_env.c \
	libft_ms/ft_lstclear_env.c \
	libft_ms/ft_lstiter_env.c \
	libft_ms/ft_typel.c \
	libft_ms/ft_substring.c \
	memory/mem_free.c \
	memory/mem_fd.c \
	env/env_make_tab.c \
	lexer/lex_lstnew.c \
	lexer/lex_lstadd_back.c \
	lexer/lex_lstclear.c \
	lexer/lexer.c \
	parser/parser.c \
	parser/parsing/prs_string.c \
	parser/parsing/prs_redir.c \
	parser/list/cmd/prs_lstadd_back.c \
	parser/list/cmd/prs_lstclear.c \
	parser/list/cmd/prs_lstnew.c \
	parser/list/cmd/prs_lstget.c \
	parser/list/redir/prs_lstadd_back_redir.c \
	parser/list/redir/prs_lstclear_redir.c \
	parser/list/redir/prs_lstnew_redir.c \
	parser/prs_getcmd.c \

HEADER = \
	includes/minishell.h \
	includes/lexer.h \
	includes/parser.h \
	includes/libft.h \

REP_OUT = OBJ

OBJS = $(SRCS:%.c=$(REP_OUT)/%.o)

DIRS = $(sort $(dir $(OBJS)))

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

RM = rm -rf

m ?= gitadd

all: $(DIRS) $(NAME)

$(DIRS):
	mkdir -p $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(REP_OUT)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(REP_OUT)

fclean: clean
	$(RM) $(NAME)

re: fclean all

vg: all
	valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--track-fds=yes \
	--trace-children=yes \
	./$(NAME) $(ARGS)

print-%:
	@echo $* = $($*)

gitadd:
#	git pull && git add **/*.c **/*.h Makefile .gitignore && git commit -m "$(m)" && git push
#	git pull && git add $(shell find . -type f \( -name "*.c" -o -name "*.h" \)) .gitignore Makefile && git commit -m "$(m)" && git push
	git pull && git add $(shell find . -type f \( -name "*.c" -o -name "*.h" \) \
  -not -path "./test2/*" \
  -not -path "./OBJ/*" \
  -not -path "./tester/*") .gitignore Makefile && git commit -m "$(m)" && git push

.PHONY: all clean fclean re print obj
