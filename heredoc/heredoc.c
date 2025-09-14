/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:50:18 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/14 19:58:44 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*hd_readline(t_minishell *m)
{
	char *line;
	int	fd_tty;

	//if (isatty(STDIN_FILENO) ||  1)
	{
		fd_tty = open("/dev/tty", O_RDONLY);
		if (fd_tty == -1)
			ft_exit_fail(m, ERROR_TTY);
		line = get_next_line(fd_tty);
		close(fd_tty);
	}
	//else
	//	line = get_next_line(STDIN_FILENO);
	if (line && *line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = 0;
	return (line);
}

static	void ms_launch_read(t_minishell *m, int fd[2], char *limiter, int expand)
{
	/*
	(void)nop;
	int tmp_in = dup(STDIN_FILENO);

	//int tmp_out = dup(STDOUT_FILENO);

	int tty_fd = open("/dev/tty", O_RDONLY);
	dup2(tty_fd, STDIN_FILENO);   // tty_fd = open("/dev/tty", O_RDONLY)
	//dup2(tty_fd, STDOUT_FILENO);
	while (1)
	{
		//m->line = readline(PROMPT_HEREDOC);
		m->line = read_input(m, PROMPT_HEREDOC);

		{
			if (m->line == NULL)
			{
				ft_printm->line = hd_readline(m)f_fd( STDOUT_FILENO, WARNING_HEREDOC, limiter);
				//ft_printf_fd( STDERR_FILENO, WARNING_HEREDOC, limiter);
				break;
			}
			if ( m->line && ft_strcmp(m->line, limiter) == 0)
				break;
			ft_putstr_fd( ms_expand_word(m, m->line), fd[1]);
			ft_putchar_fd('\n', fd[1]);
			mem_free_null(&m->line, "ms_launch_child.line");
		}
	}
	if (dup2(tmp_in, STDIN_FILENO) == -1)
		ft_exit_fail(m, ERROR_DUP2);
	close(fd[1]);
	mem_free_null(&m->line, "ms_launch_child.line");
*/

/* FONCTIONNE MAIS PAS avec les tester
	(void)nop;

	int tmp_in = dup(STDIN_FILENO);
	int tty_fd = open("/dev/tty", O_RDONLY);
	dup2(tty_fd, STDIN_FILENO);

	int	dup_tmp;
		dup_tmp = dup(STDOUT_FILENO);
	if ( dup_tmp == -1)
		ft_exit_fail(m, ERROR_DUP);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	 	ft_exit_fail(m, ERROR_DUP2);
	while (1)
	{
		//m->line = readline(PROMPT_HEREDOC);
		m->line = read_input(m, PROMPT_HEREDOC);

		{
			if (m->line == NULL)
			{
				ft_printf_fd( STDOUT_FILENO, WARNING_HEREDOC, limiter);
				//ft_printf_fd( STDERR_FILENO, WARNING_HEREDOC, limiter);
				break;
			}
			if ( m->line && ft_strcmp(m->line, limiter) == 0)
				break;
			ft_putstr_fd( ms_expand_word(m, m->line), fd[1]);
			ft_putchar_fd('\n', fd[1]);
			mem_free_null(&m->line, "ms_launch_child.line");
		}
	}
	if (dup2(dup_tmp, STDOUT_FILENO) == -1)
		ft_exit_fail(m, ERROR_DUP2);
	if (dup2(tmp_in, STDIN_FILENO) == -1)
		ft_exit_fail(m, ERROR_DUP2);
	close(fd[1]);
	mem_free_null(&m->line, "ms_launch_child.line");
*/



	//  if (isatty(STDIN_FILENO))
	//  	perror("isatty");
	//  else
	//  	perror("is not a tty");

	//(void)nop;
	// int	dup_tmp;
	// 	dup_tmp = dup(STDOUT_FILENO);
	// if ( dup_tmp == -1)
	// 	ft_exit_fail(m, ERROR_DUP);
	// if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	//  	ft_exit_fail(m, ERROR_DUP2);
	while (1)
	{
		//m->line = readline(PROMPT_HEREDOC);
		//m->line = read_input(m, PROMPT_HEREDOC);
		//ft_printf_fd(STDOUT_FILENO, PROMPT_HEREDOC);
		ft_printf_fd(STDERR_FILENO, PROMPT_HEREDOC);
		m->line = hd_readline(m);

		{
			if (m->line == NULL)
			{
				//ft_printf_fd( STDOUT_FILENO, WARNING_HEREDOC, limiter);
				ft_printf_fd( STDERR_FILENO, WARNING_HEREDOC, limiter);
				break;
			}
			if ( m->line && ft_strcmp(m->line, limiter) == 0)
				break;
			if (expand)
				ft_putstr_fd( ms_expand_word(m, m->line), fd[1]);
			ft_putchar_fd('\n', fd[1]);
			mem_free_null(&m->line, "ms_launch_child.line");
		}
	}
	// if (dup2(dup_tmp, STDOUT_FILENO) == -1)
	// 	ft_exit_fail(m, ERROR_DUP2);
	close(fd[1]);
	mem_free_null(&m->line, "ms_launch_child.line");
}

char *ms_unquote(char *s)
{
	char	*ret;

	//if (/*s && *s &&*/ s[0] == '"')
	if (ft_strchr(s, '\"'))
		ret = ft_strtrim_all(s, "\"");
	//else if (/*s && *s &&*/ s[0] == '\'')
	else if (ft_strchr(s, '\''))
		ret = ft_strtrim_all(s, "'");
	else
		ret =  ft_strdup(s);
	return (ret);
}

int	ms_heredoc(t_minishell *m, char *limiter, int nop)
{
	int		fd[2];
	int		expand;
	char	*new_limiter;

	(void)nop;
	expand = 1;
	//if (limiter[0] == '"' || limiter[ft_strlen(limiter - 1)] == '"'  || limiter[0] == '\'')
	if (ft_strchr(limiter, '\'') || ft_strchr(limiter, '"'))
		expand = 0;
	new_limiter = ms_unquote(limiter);
	if (pipe(fd) == -1)
		ft_exit_fail(m, ERROR_PIPE);
	ms_launch_read(m, fd, new_limiter, expand);
	mem_free(new_limiter, "ms_heredoc", new_limiter);
	return fd[0];
}

