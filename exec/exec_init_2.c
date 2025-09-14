/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:50:08 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/14 15:27:01 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

void	exec_init_path(t_minishell **m)
{
	t_env	*l;

	l = (*m)->env_list;
	if (l == NULL)
	{
		(*m)->path = NULL;
		return ;
	}
	while(l && ft_strcmp(l->key, S_PATH) != 0)
		l = l->next;
	if (l && ft_strcmp(l->key, S_PATH) == 0)
	{
		(*m)->path  = ft_split(l->val, ':');
		if ((*m)->path == NULL)
			ft_exit_fail_status(*m, NULL, EXIT_ALLOC_ERROR);
	}
}

char	*exec_find_command(t_minishell *m, char *cmd)
{
	char	*cmd_abs;
	int		i;

	if (cmd == NULL)
		return (NULL);
	cmd_abs = NULL;
	if (/*access(cmd, X_OK) == 0 && */ft_strchr(cmd, '/'))
	{
		cmd_abs = ft_strdup(cmd);
		if (cmd_abs == NULL)
			ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
		return (cmd_abs);
	}
	i = 0;
	while (m->path && m->path[i])
	{
		cmd_abs = ft_strjoin_with_char(m->path[i], '/', cmd);
		if (cmd_abs == NULL)
			ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
		if (access(cmd_abs, X_OK) == 0)
			break ;
		mem_free_null(&cmd_abs, "cmd_abs");
		i++;
	}
	return (cmd_abs);
}

void	exec_init_cmd_path(t_minishell **m/*, int nbcom*/)
{
	t_cmd	*l;
	char	*cmd_abs;

	l = (*m)->cmds;

	while (l)
	{
		//cmd_abs = exec_find_command(*m, prs_getcmd(*m, l->cmd));
		cmd_abs = exec_find_command(*m, prs_getcmd_from_args(*m, l->args));
		if (cmd_abs)
			l->cmd_abs = cmd_abs;
		l = l->next;
	}
}

