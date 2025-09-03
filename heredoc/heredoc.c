/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:50:18 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/03 18:54:31 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void ms_launch_child(t_minishell *m, int fd[2], char *limiter, int expand)
{
	(void)expand;
	//char	*line;
	//signal(SIGINT, SIG_DFL);
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
}
