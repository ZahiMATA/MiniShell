/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:50:18 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/09 14:51:38 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static	void ms_launch_read(t_minishell *m, int fd[2], char *limiter, int nop)
{
	(void)nop;
	///close(fd[0]);
	// int tty_fd = open("/dev/tty", O_RDWR);
	// if (tty_fd == -1)
	// ft_exit_fail(m, "ERROR_OPEN_TTY");

	while (1)
	{
		//m->line = readline(PROMPT_HEREDOC);
		ft_printf_fd(STDERR_FILENO, "%s", PROMPT_HEREDOC);
		m->line = read_line(m, STDERR_FILENO);
		if (m->line && ft_strlen(m->line) >= 1)
			m->line[ft_strlen(m->line) - 1] = 0;
		//debug_var(m->line);
		{
			//debug_var(m->line);
			if (m->line == NULL)
			{
				ft_printf_fd( STDERR_FILENO, WARNING_HEREDOC, limiter);
				break;
			}
			//debug_var(m->line);
			if ( m->line && ft_strcmp(m->line, limiter) == 0)
			{
				break;
			}
			// ft_printf_fd(fd[1], "fd0=%d:fd1=%d:in=%d:out=%d\n", fd[0], fd[1], STDIN_FILENO, STDOUT_FILENO);
			ft_putstr_fd(m->line, fd[1]);
			ft_putchar_fd('\n', fd[1]);
			mem_free_null(&m->line, "ms_launch_child.line");
		}
	}
	close(fd[1]);
	mem_free_null(&m->line, "ms_launch_child.line");
	//rl_clear_history();
	//mem_free_all(m);
}

int	ms_heredoc(t_minishell *m, char *limiter, int nop)
{
	int		fd[2];

	if (pipe(fd) == -1)
		ft_exit_fail(m, ERROR_PIPE);
	ms_launch_read(m, fd, limiter, nop);
	// debug_var_i(fd[0]);
	// debug_var_i(fd[1]);
	//close(fd[1]);
	return fd[0];
}


/*
static	void ms_launch_child(t_minishell *m, int fd[2], char *limiter, int expand)
{
	(void)expand;
	close(fd[0]);
	while (1)
	{
		//ft_putstr(PROMPT_HEREDOC);
		//m->line = read_input(m, GOT_SIGNAL);
		m->line = readline(PROMPT_HEREDOC);
		{
			//debug_var(m->line);
			if (m->line == NULL)
			{
				ft_printf_fd( STDERR_FILENO, WARNING_HEREDOC, limiter);
				break;
			}

			if ( m->line && ft_strcmp(m->line, limiter) == 0)
			{
				break;
			}
			ft_putstr_fd(m->line, fd[1]);
			ft_putchar_fd('\n', fd[1]);
			mem_free_null(&m->line, "ms_launch_child.line");
		}
	}
	close(fd[1]);
	mem_free_null(&m->line, "ms_launch_child.line");
	//mem_free_all(m);
}

int	ms_heredoc(t_minishell *m, char *limiter, int expand)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		ft_exit_fail(m, ERROR_PIPE);

	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		ft_exit_fail(m, ERROR_FORK);
	}
	if (pid == 0)
		ms_launch_child(m, fd, limiter, expand);
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT) // A VOIR
	{
		m->last_status = 130;
		close(fd[0]);
		return -1;
	}
	return fd[0];
}*/
