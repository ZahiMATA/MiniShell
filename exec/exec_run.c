/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:40:57 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/01 11:40:57 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_execve_2(t_minishell *m, int pipes[][2]);

static void	exec_exit(t_minishell *m, int pipes[][2], t_cmd *l)
{
	int		i;

	i = 0;
	while (i < m->nb_cmd - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	mem_close_fds(m);
	i = 0;
	l = m->cmds;
	setup_signals_off();
	while (l)
	{
		waitpid(l->pid, &l->status_c, 0);
		l = l->next;
		i++;
	}
	setup_signals();
	exec_set_last_status(m);
}

void	exec_execve(t_minishell *m)
{
	int		pipes[MAX_PIPES][2];
	int		i;

	i = 0;
	while (i < m->nb_cmd - 1)
	{
		if (pipe(pipes[i]) == -1)
			ft_exit_fail(m, ERROR_PIPE);
		i++;
	}
	m->status_heredoc = 0;
	run_heredoc(m);
	exec_execve_2(m, pipes);
}

static void	exec_execve_2(t_minishell *m, int pipes[][2])
{
	int		i;
	t_cmd	*l;

	if (m->status_heredoc != 0)
	{
		exec_exit(m, pipes, NULL);
		printf("\n");
		m->last_status = EXIT_130;
		return ;
	}
	i = 0;
	l = m->cmds;
	while (l)
	{
		l->pid = fork();
		if (l->pid == -1)
			ft_exit_fail(m, ERROR_FORK);
		if (l->pid == 0)
			exec_launch_process(m, l, i, pipes);
		l = l->next;
		i++;
	}
	exec_exit(m, pipes, l);
	if (m->last_status)
		write(STDOUT_FILENO, "\n", 1);
}
