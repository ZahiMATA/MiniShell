/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:27:46 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/07 12:39:16 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builin(char *s)
{
	return (
		ft_strcmp(s, "cd") == 0 ||
		ft_strcmp(s, "echo") == 0 ||
		ft_strcmp(s, "env") == 0 ||
		ft_strcmp(s, "exit") == 0 ||
		ft_strcmp(s, "export") == 0 ||
		ft_strcmp(s, "pwd") == 0 ||
		ft_strcmp(s, "unset") == 0 ||
		ft_strcmp(s, "history") == 0 ||
		ft_strcmp(s, ":") == 0
	);
}

int	exec_builtin(t_minishell *m, t_cmd *cmd)
{
	int	ret;

	if (ft_strcmp(cmd->args[0], "cd") == 0)
		 ret = ft_cd(m, cmd);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		 ret = ft_echo(m, cmd);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		ret = ft_env(m, cmd);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		 ret = ft_exit(m, cmd);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		 ret = ft_export(m->cmds->args, &m->env_list);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		 ret = ft_pwd();
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		 ret = ft_unset(m->cmds->args, &m->env_list);
	if (ft_strcmp(cmd->args[0], "history") == 0)
		ret = ft_history(m);
	if (ft_strcmp(cmd->args[0], ":") == 0)
		ret = ft_colon(m);
	return (ret);
}

void	dispatch(t_minishell *m)
{
	if (m->cmds && m->cmds->args)
		ms_expand_all_cmds(m);
	if (m->cmds && m->cmds->args && m->nb_cmd == 1 && is_builin(m->cmds->args[0]))
	{
		m->cmds->status = exec_builtin(m, m->cmds);
		m->last_status = m->cmds->status;
	}
	else if (m->cmds)
	{
		exec_execve(m);
	}
}
