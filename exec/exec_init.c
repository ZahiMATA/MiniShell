/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:50:08 by ybouroga          #+#    #+#             */
/*   Updated: 2025/07/10 16:05:14 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

static void	px_init_path(t_pipex **p, char **env)
{
	int	i;

	if (env == NULL || *env == NULL)
	{
		(*p)->path = NULL;
		return ;
	}
	i = 0;
	while (env[i] && ft_strncmp(env[i], PATH, ft_strlen(PATH)))
		i++;
	if (env[i] == NULL)
	{
		(*p)->path = NULL;
		return ;
	}
	(*p)->path = ft_split_multi(env[i] + ft_strlen(PATH), "=:");
	if ((*p)->path == NULL)
		ft_exit(ERROR_MALLOC, *p);
}

static void	px_init_cmds_and_cmd_args(t_pipex **p, char **cmd, int nbcom)
{
	int	i;

	if (cmd == NULL || *cmd == NULL)
		ft_exit(ERROR_NOCOMS, *p);
	(*p)->cmds = malloc(sizeof(t_cmd) * (nbcom + 1));
	if ((*p)->cmds == NULL)
	{
		ft_exit(ERROR_MALLOC, *p);
	}
	i = 0;
	while (i < nbcom)
	{
		(*p)->cmds[i].args = ft_split_multi(cmd[i + OFST_FIRST_CMD], "  ");
		if ((*p)->cmds[i].args == NULL)
			ft_exit(ERROR_MALLOC, *p);
		(*p)->cmds[i].fd_pipe[0] = -1;
		(*p)->cmds[i].fd_pipe[1] = -1;
		(*p)->cmds[i].pid = -1;
		(*p)->cmds[i].status = -1;
		(*p)->fd_in = -1;
		(*p)->fd_out = -1;
		i++;
	}
	(*p)->cmds[i].args = NULL;
}

static char	*px_find_command(t_pipex *p, char *cmd)
{
	char	*cmd_abs;
	int		i;

	if (cmd == NULL)
		return (NULL);
	cmd_abs = NULL;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (p->path && p->path[i])
	{
		cmd_abs = ft_strjoin_with_char(p->path[i], '/', cmd);
		if (cmd_abs == NULL)
			ft_exit(ERROR_MALLOC, p);
		if (access(cmd_abs, X_OK) == 0)
			break ;
		px_free_null(&cmd_abs);
		i++;
	}
	if (cmd_abs == NULL)
		perror(ERROR_ACCESS);
	return (cmd_abs);
}

static void	px_init_cmd_path(t_pipex **p, int nbcom)
{
	int	i;

	i = 0;
	while (i < nbcom)
	{
		(*p)->cmds[i].path = px_find_command(*p, (*p)->cmds[i].args[0]);
		i++;
	}
}

void	px_init_pipex(t_pipex **p, char **args, int nbcom, char **env)
{
	*p = malloc(sizeof(t_pipex));
	if (*p == NULL)
		ft_exit(ERROR_MALLOC, *p);
	(*p)->cmds = NULL;
	(*p)->limiter = NULL;
	(*p)->path = NULL;
	(*p)->env = NULL;
	(*p)->nb_cmd = nbcom;
	(*p)->is_here_doc = 0;
	px_init_path(p, env);
	(*p)->env = env;
	px_init_cmds_and_cmd_args(p, args, nbcom);
	px_init_cmd_path(p, nbcom);
	(*p)->fd_in = open(args[1], O_RDONLY);
	if ((*p)->fd_in == -1)
		perror("pipex on fd in");
	(*p)->fd_out = open(args[nbcom + OFST_FIRST_CMD], OW | OC | OT, FLAG_FIC);
	if ((*p)->fd_out == -1)
		perror("pipex on fd out");
}
