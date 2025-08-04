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

#include "pipex.h"
#include <unistd.h>
#include <stddef.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

void	launch_process_begin(t_pipex *p, int n)
{
	if (p->cmds[n].path == NULL)
		return (perror(ERROR_EXECVE), ft_exit_status(ERROR_EXECVE, p, 127));
	px_show_processes(p, "PID", p->cmds[n].path, n);
	if (dup2(p->fd_in, STDIN_FILENO) == -1)
		ft_exit(ERROR_DUP2, p);
	if (dup2(p->cmds[n].fd_pipe[1], STDOUT_FILENO) == -1)
		ft_exit(ERROR_DUP2, p);
	px_close_fds(p);
	if (p->fd_in == -1)
		return (px_show_error("LPB"));
	execve(p->cmds[n].path, p->cmds[n].args, p->env);
	ft_exit(ERROR_EXECVE, p);
}

void	launch_process_end(t_pipex *p, int n)
{
	if (p->cmds[n].path == NULL)
		return (perror(ERROR_EXECVE), ft_exit_status(ERROR_EXECVE, p, 127));
	px_show_processes(p, "PID_END", p->cmds[n].path, n);
	if (dup2(p->cmds[0].fd_pipe[0], STDIN_FILENO) == -1)
		ft_exit(ERROR_DUP2, p);
	if (dup2(p->fd_out, STDOUT_FILENO) == -1)
		ft_exit(ERROR_DUP2, p);
	px_close_fds(p);
	if (p->fd_out == -1)
		return (px_show_error("LBE"));
	execve(p->cmds[n].path, p->cmds[n].args, p->env);
	ft_exit(ERROR_EXECVE, p);
}

void	px_execve(t_pipex *p)
{
	if (pipe(p->cmds[0].fd_pipe) == -1)
		ft_exit(ERROR_PIPE, p);
	p->cmds[0].pid = fork();
	if (p->cmds[0].pid == -1)
		ft_exit(ERROR_FORK, p);
	if (p->cmds[0].pid == 0)
		launch_process_begin(p, 0);
	p->cmds[1].pid = fork();
	if (p->cmds[1].pid == -1)
		ft_exit(ERROR_FORK, p);
	if (p->cmds[1].pid == 0)
		launch_process_end(p, 1);
	px_close_fds(p);
	waitpid(p->cmds[0].pid, &p->cmds[0].status, 0);
	waitpid(p->cmds[1].pid, &p->cmds[1].status, 0);
	px_show_processes(p, "PARENT", NULL, -1);
}

int	px_get_last_status(t_pipex*p)
{
	int	status;

	status = p->cmds[p->nb_cmd - 1].status;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
