/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:27:46 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/25 13:11:40 by ybouroga         ###   ########.fr       */
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
		ft_strcmp(s, "unset") == 0
	);
}

int	exec_builtin(t_minishell *m)
{
	if (ft_strcmp(m->line, "cd") == 0)
		 ft_cd(m->cmds->args, m->env_list);
	if (ft_strcmp(m->line, "echo") == 0)
		 ft_echo(m->cmds->args);
	if (ft_strcmp(m->line, "exit") == 0)
		 ft_exit(m->cmds->args);
	if (ft_strcmp(m->line, "export") == 0)
		 ft_export(m->cmds->args, &m->env_list);
	if (ft_strcmp(m->line, "pwd") == 0)
		 ft_pwd();
	if (ft_strcmp(m->line, "unset") == 0)
		 ft_unset(m->cmds->args, &m->env_list);
	return (0);
}

void	dispatch(t_minishell *m)
{
	if (m->cmds && m->cmds->args && is_builin(m->cmds->args[0]))
	{
		exec_builtin(m);
	}
	else
	{
		exec_execve(m);
	}
}