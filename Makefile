# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 10:35:37 by ybouroga          #+#    #+#              #
#    Updated: 2025/07/07 21:00:55 by ybouroga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = \
	minishell.c \
	debug\debug_display.c \
	exec\exec.c \
	exec\exec_init.c \
	exec\exec_redir.c \
	exec\exec_run.c \
	input\input.c \
	libft\ft_split.c \
	libft\ft_print.c \
	libft\ft_strlen.c \
	libft\ft_strncmp.c \
	libft\ft_exit.c \
	libft\ft_strdup.c \
	libft\ft_strjoin.c \
	memory\mem_free.c \
	memory\mem_fd.c \
	

HEADER = \
	minishell.h

REP_OUT = OBJ

OBJS = $(SRCS:%.c=$(REP_OUT)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

RM = rm -rf

all: $(REP_OUT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(REP_OUT):
	mkdir -p $(REP_OUT)

$(REP_OUT)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS) $(REP_OUT)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

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

$(OBJS): | $(REP_OUT)

.PHONY: all clean fclean re print obj