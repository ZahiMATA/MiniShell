/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:27:46 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/28 09:37:31 by zmata            ###   ########.fr       */
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
		ft_strcmp(s, "history") == 0
	);
}

int	exec_builtin(t_minishell *m, char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		 ft_cd(m->cmds->args, m->env_list);
	if (ft_strcmp(cmd, "echo") == 0)
		 ft_echo(m->cmds->args);
	if (ft_strcmp(cmd, "env") == 0)
		ft_env(m->cmds->args, m->env_list);
	if (ft_strcmp(cmd, "exit") == 0)
		 ft_exit(m);
	if (ft_strcmp(cmd, "export") == 0)
		 ft_export(m->cmds->args, &m->env_list);
	if (ft_strcmp(cmd, "pwd") == 0)
		 ft_pwd();
	if (ft_strcmp(cmd, "unset") == 0)
		 ft_unset(m->cmds->args, &m->env_list);
	if (ft_strcmp(cmd, "history") == 0)
		ft_history(m->cmds->args);
	return (0);
}

void	dispatch(t_minishell *m)
{
	if (m->cmds && m->cmds->args && is_builin(m->cmds->args[0]))
	{
		exec_builtin(m, m->cmds->args[0]);
	}
	else
	{
		exec_execve(m);
	}
}