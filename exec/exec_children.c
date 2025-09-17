/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:20:34 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 14:37:29 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_launch_process_2(t_minishell *m, t_cmd *cmd);
static void	exec_launch_process_3(t_minishell *m, t_cmd *cmd);

void	exec_launch_process(t_minishell *m, t_cmd *cmd, int n, int pipes[][2])
{
	int			i;

	setup_signals_for_children();
	if (n > 0)
		if (dup2(pipes[n - 1][0], STDIN_FILENO) == -1)
			ft_exit_fail(m, ERROR_DUP2);
	if (n < m->nb_cmd - 1)
		if (dup2(pipes[n][1], STDOUT_FILENO) == -1)
			ft_exit_fail(m, ERROR_DUP2);
	redir_in(m, cmd);
	redir_out(m, cmd);
	i = 0;
	while (i < m->nb_cmd - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	mem_close_fds(m);
	exec_launch_process_2(m, cmd);
}

static void	exec_launch_process_2(t_minishell *m, t_cmd *cmd)
{
	int			status;

	if (cmd->args == NULL)
		ft_exit_err(m, EXIT_SUCCESS, NULL);
	if (cmd->args && is_builin_child(cmd->args[0]))
	{
		status = exec_builtin(m, cmd);
		mem_free_all(m);
		exit(status);
	}
	else if (ft_strcmp(cmd->args[0], ".") == 0)
		ft_exit_err(m, EXIT_2, ft_perror(MINISHELL, ".", ERROR_FILE));
	else if (ft_strcmp(cmd->args[0], "~") == 0)
		ft_exit_err(m, EXIT_126, ft_perror(MINISHELL, cmd->args[0], ERROR_DIR));
	else if (cmd->cmd_abs == 0)
		ft_exit_err(m, EXIT_COMMAND_NOT_FOUND, \
			ft_perror(MINISHELL, cmd->args[0], ERROR_COM));
	else if (ft_not_dir_but_file(cmd->args[0]))
		ft_exit_err(m, EXIT_IS_NOT_A_DIRECTORY, \
			ft_perror(MINISHELL, cmd->cmd_abs, ERROR_NOT_DIR));
	else if (ft_strchr(cmd->args[0], '/') == 0 && cmd->cmd_abs == NULL)
		ft_exit_err(m, EXIT_COMMAND_NOT_FOUND, \
			ft_perror(MINISHELL, cmd->args[0], ERROR_COM));
	exec_launch_process_3(m, cmd);
}

static void	exec_launch_process_3(t_minishell *m, t_cmd *cmd)
{
	char		**env_tab;

	if ((ft_strchr(cmd->args[0], '/') && cmd->cmd_abs == NULL) || \
		(ft_stat(cmd->cmd_abs) == -1))
		ft_exit_err(m, EXIT_NO_SUCH_FILE, \
			ft_perror(MINISHELL, cmd->args[0], ERROR_NOSUCH));
	else if (ft_is_dir(cmd->cmd_abs))
		ft_exit_err(m, EXIT_IS_A_DIRECTORY, \
			ft_perror(MINISHELL, cmd->cmd_abs, ERROR_DIR));
	if (access(cmd->cmd_abs, X_OK) == -1)
		ft_exit_err(m, EXIT_PERMISSION, \
			ft_perror(MINISHELL, cmd->cmd_abs, ERROR_PERMISSION));
	else
	{
		env_tab = env_list_to_tab(m, m->env_list);
		execve(cmd->cmd_abs, cmd->args, env_tab);
		mem_free_array(&env_tab, "env_tab");
		ft_exit_perror(m, cmd->cmd_abs);
	}
}
