/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:28:03 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/04 20:24:11 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_init_env_list(char **env)
{
	(void) env;
}

void	exec_feed_pipex(t_minishell **m, char **args, int nbcom, char **env)
{
	(*m)->nb_cmd = nbcom;
	(*m)->is_here_doc = 0;
	exec_init_path(m, env);
	exec_init_env_list(env); // TODO
	exec_init_cmds_and_cmd_args(m, args, nbcom);
	exec_init_cmd_path(m, nbcom);
	(*m)->fd_in = open(args[1], O_RDONLY);
	if ((*m)->fd_in == -1)
		perror("pipex on fd in");
	(*m)->fd_out = open(args[nbcom + OFST_FIRST_CMD], OW | OC | OT, FLAG_FIC);
	if ((*m)->fd_out == -1)
		perror("pipex on fd out");
}

void exec_init_minishell(t_minishell **m)
{
	*m = malloc(sizeof(t_minishell));
	if (*m == NULL)
		ft_exit_fail_status(*m, NULL, EXIT_ALLOC_ERROR);
	(*m)->fd_in = -1;
	(*m)->fd_out = -1;
	(*m)->cmds = NULL;
	(*m)->token = NULL;
	(*m)->nb_cmd = 0;
	(*m)->is_here_doc = 0;
	(*m)->limiter = NULL;
	(*m)->path = NULL;
	(*m)->env_list = NULL;
	(*m)->last_status = 0;
	//exec_feed_pipex(m, NULL, 0, env); //TODO
}


