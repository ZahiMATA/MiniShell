# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 10:35:37 by ybouroga          #+#    #+#              #
#    Updated: 2025/08/08 16:30:12 by ybouroga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = \
	src/minishell.c \
	debug/debug_display.c \
	debug/debug_token.c \
	debug/debug_cmd.c \
	exec/exec_init_1.c \
	exec/exec_init_2.c \
	exec/exec_redir.c \
	exec/exec_run.c \
	input/input.c \
	libft/ft_split.c \
	libft/ft_split_multi.c \
	libft/ft_print.c \
	libft/ft_strlen.c \
	libft/ft_strncmp.c \
	libft/ft_strdup.c \
	libft/ft_strjoin.c \
	libft/ft_strchr.c \
	libft/ft_typec.c \
	libft/ft_calloc.c \
	libft/ft_bzero.c \
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
	parser/prs_lstadd_back.c \
	parser/prs_lstclear.c \
	parser/prs_lstnew.c \
	parser/prs_lstget.c \
	parser/prs_getcmd.c \


HEADER = \
	includes/minishell.h \
	includes/lexer.h \
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
	git pull && git add **/*.c **/*.h Makefile .gitignore && git commit -m "$(m)" && git push

.PHONY: all clean fclean re print obj