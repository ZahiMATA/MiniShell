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

static void	redir_in(t_minishell *m, t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == N_REDIR_LEFT)
		{
			m->fd_in = open(redir->file, O_RDONLY);
			if (m->fd_in == -1)
			{
				m->last_status = EXIT_FAILURE;
				m->error = ft_strdup(redir->file);
			}
			else if (dup2(m->fd_in, STDIN_FILENO) == -1)
				ft_exit_fail(m, ERROR_DUP2);
			close(m->fd_in);
		}
		else if (redir->type == N_DOUBLE_REDIR_LEFT)
		{
			m->fd_in = ms_heredoc(m, redir->file, 0);
			if (m->fd_in == -1)
				return ;
			dup2(m->fd_in, STDIN_FILENO);
			close(m->fd_in);
		}
		redir = redir->next;
	}
}

static void	redir_out(t_minishell *m, t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == N_REDIR_RIGHT)
		{
			m->fd_out = open(redir->file, OW | OC | OT, FLAG_FIC);
			if (m->fd_out == -1)
			{
				m->last_status = EXIT_FAILURE; // TODO A voir si on quitte ici ou pas
				mem_free_null(&m->error, "error");
				m->error = ft_strdup(redir->file);
			}
			else if (dup2(m->fd_out, STDOUT_FILENO) == -1)
				ft_exit_fail(m, ERROR_DUP2);
			close(m->fd_out);
		}
		redir = redir->next;
	}
}

static void	launch_process(t_minishell *m, t_cmd *cmd, int n, int pipes[][2])
{
	char		**env_tab;
	int			i;
	int			status;
	struct stat	st;
	t_err		err;

	//debug_show_cmd(cmd, n);
	//printf("n=[%d],pipe.n-1.0=[%d] pipe.n.1=[%d]\n", n, pipes[n-1][0], pipes[n][1]);
	setup_signals_for_children();
	if (n > 0)
		if (dup2(pipes[n - 1][0] , STDIN_FILENO) == -1)
			ft_exit_fail(m, ERROR_DUP2);
	if (n < m->nb_cmd - 1)
		if (dup2(pipes[n][1], STDOUT_FILENO) == -1)
			ft_exit_fail(m, ERROR_DUP2);
	if (n == 0)				// TODO a enlever ?
		redir_in(m, cmd);
	if (n == m->nb_cmd - 1)	// TODO a enlever ?
		redir_out(m, cmd);
	i = 0;
	while (i < m->nb_cmd - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	if (m->last_status != 0)
	{
		ft_return_error(m, m->error, S_EMPTY, m->last_status);
		mem_free_null(&m->error, "error");
	}
	// debug_var(cmd->args[0]);
	// debug_var(cmd->args[1]);
	// debug_var_i(n);
	if (cmd->args && is_builin(cmd->args[0]))
	{
		status = exec_builtin(m, cmd/*->args[0]*/);
		//status = cmd->status;
		mem_free_all(m);
		exit(status);
	}
	else if (ft_strchr(cmd->args[0], '/') == 0 && cmd->cmd_abs == NULL)
		ft_exit_error(m, cmd->args[0], ERROR_COM, EXIT_COMMAND_NOT_FOUND);
	else if ((ft_strchr(cmd->args[0], '/') && cmd->cmd_abs == NULL) ||
		(stat(cmd->cmd_abs, &st) == -1)
	)
	{
		err.mes1 = MINISHELL;
		err.mes2 = cmd->args[0];
		err.mes3 = ERROR_NOSUCH;
		ft_exit_err(m, err, EXIT_NO_SUCH_FILE);
	}
	else if ((st.st_mode & __S_IFMT) == __S_IFDIR )
	{
		err.mes1 = MINISHELL;
		err.mes2 = cmd->cmd_abs;
		err.mes3 = ERROR_DIR;
		ft_exit_err(m, err, EXIT_IS_A_DIRECTORY);
	}
	if (access(cmd->cmd_abs, X_OK) == -1)
	{
		err.mes1 = MINISHELL;
		//err.mes2 = cmd->args[0];
		err.mes2 = cmd->cmd_abs;
		err.mes3 = ERROR_PERMISSION;
		ft_exit_err(m, err, EXIT_PERMISSION);
	}
	else
	{
		env_tab = env_list_to_tab(m, m->env_list);
		execve(cmd->cmd_abs, cmd->args, env_tab);
		mem_free_array(&env_tab, "env_tab");
		ft_exit_perror(m, cmd->cmd_abs);
	}
	/*else
	{
		ft_exit_error(m, cmd->args[0], ERROR_COM, EXIT_COMMAND_NOT_FOUND);
	}*/
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
		//printf("EX=[%s]\n", l->args[0]);
		l->pid = fork();
		if (l->pid == -1)
			ft_exit_fail(m, ERROR_FORK);
		if (l->pid == 0)
			launch_process(m, l, i, pipes);
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
		waitpid(l->pid, &l->status_c, 0);
		l = l->next;
		i++;
	}
	set_last_status(m);
	//debug_show_processes(m, "PARENT");
}

int	decompress_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	set_last_status(t_minishell *m)
{
	t_cmd	*cmd;
	cmd = m->cmds;
	if (cmd == NULL)
	{
		//printf("tail=0\n");
		return (1);
	}
	while (cmd)
	{
		cmd->status = decompress_status(cmd->status_c);
		m->last_status = cmd->status;
		cmd = cmd ->next;
	}
	return (0);
	//printf("cs=[%d]\n", tail->status);
}
