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
	debug_show_cmds(m);
	execve(prs_lstget(m, n)->cmd_abs, prs_lstget(m, n)->args, env_tab); // TODO Metre le tab
	mem_free_array(&env_tab);
	ft_exit_error(m, prs_lstget(m, n)->cmd_abs);
}

void	exec_execve(t_minishell *m)
{
	int		pipes[m->nb_cmd - 1][2];
	int		i;
	t_cmd	*l;

	i = 0;
	while (i < m->nb_cmd - 1)
	{
		if (pipe(pipes[i]) == -1)
			ft_exit_fail(m, ERROR_PIPE);
		i++;
	}
	i = 0;
	l = m->cmds;
	while (l)
	{
		l->pid = fork();
		if (l->pid == -1)
			ft_exit_fail(m, ERROR_FORK);
		if (l->pid == 0)
			launch_process(m, i, pipes);
		l = l->next;
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
	l = m->cmds;
	while (l)
	{
		waitpid(l->pid, &l->status, 0);
		l = l->next;
		i++;
	}
	//debug_show_processes(m, "PARENT");
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
