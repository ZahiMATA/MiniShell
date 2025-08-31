/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:50:08 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/31 17:53:32 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

void	exec_init_path(t_minishell **m, char **env)
{
	int	i;

	if (env == NULL || *env == NULL)
	{
		(*m)->path = NULL;
		return ;
	}
	i = 0;
	while (env[i] && ft_strncmp(env[i], PATH, ft_strlen(PATH)))
		i++;
	if (env[i] == NULL)
	{
		(*m)->path = NULL;
		return ;
	}
	(*m)->path = ft_split_multi(env[i] + ft_strlen(PATH), "=:");
	if ((*m)->path == NULL)
		ft_exit_fail_status(*m, NULL, EXIT_ALLOC_ERROR);
}
/*
void	exec_init_cmds_and_cmd_args(t_minishell **m, char **cmd, int nbcom)
{
	int	i;

	if (cmd == NULL || *cmd == NULL)
		ft_exit_fail(*m, ERROR_NOCOMS); // TODO A voir comment on genere les cmd
	(*m)->cmds = malloc(sizeof(t_cmd) * (nbcom + 1));
	if ((*m)->cmds == NULL)
		ft_exit_fail_status(*m, NULL, EXIT_ALLOC_ERROR);
	i = 0;
	while (i < nbcom)
	{
		(*m)->cmds[i].args = ft_split_multi(cmd[i + OFST_FIRST_CMD], "  ");
		if ((*m)->cmds[i].args == NULL)
			ft_exit_fail_status(*m, NULL, EXIT_ALLOC_ERROR);

		(*m)->cmds[i].pid = -1;
		(*m)->cmds[i].status = -1;
		(*m)->fd_in = -1;
		(*m)->fd_out = -1;
		i++;
	}
	(*m)->cmds[i].args = NULL;
}*/

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
		mem_free_null(&cmd_abs);
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

