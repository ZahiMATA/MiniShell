/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:50:18 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/25 18:42:23 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void ms_launch_child(t_minishell *m, int fd[2], char *limiter, int expand)
{
	(void)expand;
	char	*line;
	//signal(SIGINT, SIG_DFL);
	close(fd[0]);
	while (1)
	{
		ft_putstr(PROMPT_HEREDOC);
		line = read_input(m, STDIN_FILENO);
		{
			if (line[0] == 0)
			{
				close(fd[1]);
				mem_free_all(m);
			}

			if (ft_strcmp(line, limiter) == 0)
			{
				ft_printf_fd( STDERR_FILENO, WARNING_HEREDOC, limiter);
				mem_free_null(&line);
				break;
			}
			ft_putstr_fd(line, fd[1]);
			ft_putchar_fd('\n', fd[1]);
			//printf("ok\n");
			mem_free_null(&line);
			//printf("ok\n");
		}
	}
	close(fd[1]);
	mem_free_all(m);
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
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		m->last_status = 130;
		close(fd[0]);
		return -1;
	}
	return fd[0];
}
