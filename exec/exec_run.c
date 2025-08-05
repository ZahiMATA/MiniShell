/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:24:15 by ybouroga          #+#    #+#             */
/*   Updated: 2025/07/10 16:08:29 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	launch_process(t_minishell *m, int n, int pipes[][2])
{
	char	**env_tab;
	int		i;

	if (n == 0)
		if ((m->fd_in != -1) && (dup2(m->fd_in, STDIN_FILENO) == -1))
			ft_exit_fail(m, ERROR_DUP2);
	if (n > 0)
		if (dup2(pipes[n - 1][0] , STDIN_FILENO) == -1)
			ft_exit_fail(m, ERROR_DUP2);
	if (n < m->nb_cmd - 1)
		if (dup2(pipes[n][1], STDOUT_FILENO) == -1)
			ft_exit_fail(m, ERROR_DUP2);
	if ((m->fd_out != -1) && (n == m->nb_cmd - 1))
		if (dup2(m->fd_out, STDOUT_FILENO) == -1)
			ft_exit_fail(m, ERROR_DUP2);
	i = 0;
	while (i < m->nb_cmd - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	env_tab = env_list_to_tab(m, m->env_list);
	execve(m->cmds[n].path, m->cmds[n].args, env_tab);
	mem_free_array(env_tab);
	ft_exit_error(m, m->cmds[n].path);
}

/*
static void	launch_process_begin(t_minishell *m, int n)
{
	char	**env_tab;

	if (m->cmds[n].path == NULL)
		ft_exit_with_status(m, ERROR_NOT_FOUND, 127);
	debug_show_processes(m, "PID", m->cmds[n].path, n);
	if (dup2(m->fd_in, STDIN_FILENO) == -1)
		ft_exit_fail(m, ERROR_DUP2);
	if (dup2(m->cmds[n].fd_pipe[1], STDOUT_FILENO) == -1)
		ft_exit_fail(m, ERROR_DUP2);
	mem_close_fds(m);
	if (m->fd_in == -1)
		return (debug_show_error("LPB"));
	env_tab = env_list_to_tab(m, m->env_list);
	execve(m->cmds[n].path, m->cmds[n].args, env_tab);
	mem_free_array(env_tab);
	ft_exit_error(m, m->cmds[n].path);
}

static void	launch_process_end(t_minishell *m, int n)
{
	char	**env_tab;

	if (m->cmds[n].path == NULL)
		ft_exit_with_status(m, ERROR_NOT_FOUND, 127);
	debug_show_processes(m, "PID_END", m->cmds[n].path, n);
	if (dup2(m->cmds[0].fd_pipe[0], STDIN_FILENO) == -1)
		ft_exit_fail(m, ERROR_DUP2);
	if (dup2(m->fd_out, STDOUT_FILENO) == -1)
		ft_exit_fail(m, ERROR_DUP2);
	mem_close_fds(m);
	if (m->fd_out == -1)
		return (debug_show_error("LBE"));
	env_tab = env_list_to_tab(m, m->env_list);
	execve(m->cmds[n].path, m->cmds[n].args, env_tab);
	mem_free_array(env_tab);
	ft_exit_error(m, m->cmds[n].path);
}*/

void	exec_execve(t_minishell *m)
{
	int	pipes[m->nb_cmd - 1][2];
	int	i;

	i = 0;
	while (i < m->nb_cmd - 1)
	{
		if (pipe(pipes[i]) == -1)
			ft_exit_fail(m, ERROR_PIPE);
		i++;
	}
	i = 0;
	while (i < m->nb_cmd)
	{
		m->cmds[i].pid = fork();
		if (m->cmds[i].pid == -1)
			ft_exit_fail(m, ERROR_FORK);
		if (m->cmds[i].pid == 0)
			launch_process(m, i, pipes);
		i++;
	}
	i = 0;
	while (i < m->nb_cmd - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < m->nb_cmd)
	{
		waitpid(m->cmds[i].pid, &m->cmds[i].status, 0);
		i++;
	}
//	if (pipe(m->cmds[0].fd_pipe) == -1)
//		ft_exit_fail(m, ERROR_PIPE);
	// m->cmds[0].pid = fork();
	// if (m->cmds[0].pid == -1)
	// 	ft_exit_fail(m, ERROR_FORK);
	// if (m->cmds[0].pid == 0)
	// 	launch_process_begin(m, 0);
	// m->cmds[1].pid = fork();
	// if (m->cmds[1].pid == -1)
	// 	ft_exit_fail(m, ERROR_FORK);
	// if (m->cmds[1].pid == 0)
	// 	launch_process_end(m, 1);
	////mem_close_fds(m);
	// waitpid(m->cmds[0].pid, &m->cmds[0].status, 0);
	// waitpid(m->cmds[1].pid, &m->cmds[1].status, 0);
	debug_show_processes(m, "PARENT", NULL, -1);
}

int	exec_get_last_status(t_minishell *m)
{
	int	status;

	status = m->cmds[m->nb_cmd - 1].status;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
