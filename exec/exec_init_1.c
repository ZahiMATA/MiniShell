/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:28:03 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/29 13:35:04 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static*/ void	exec_init_env_list(t_minishell **m, char **env)
{
	int		i;
	char	**split;
	t_env	*tmp;

	if (env == NULL || *env == NULL)
	{
		(*m)->path = NULL;
		return ;
	}

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (split == NULL)
			ft_exit_fail_status(*m, NULL, EXIT_ALLOC_ERROR);
		tmp = ft_lstnew_env(split[0], split[1]);
		if (tmp == NULL)
			ft_exit_fail_status(*m, NULL, EXIT_ALLOC_ERROR);
		ft_lstadd_back_env(&(*m)->env_list, tmp);
		i++;
	}
}

void	exec_feed_minishell(t_minishell **m, char **env)
{
	(*m)->nb_cmd = prs_lstget_nb(*m);
	(*m)->is_here_doc = 0;
	//(*m)->env = env;
	exec_init_path(m, env);
	if ((*m)->env_list == NULL)
		exec_init_env_list(m, env);
	//exec_init_cmds_and_cmd_args(m, args, nbcom);
	exec_init_cmd_path(m/*, nbcom*/);
	//(*m)->fd_in = open(args[1], O_RDONLY); // TODO pas besoin normalement on init apres
	//if ((*m)->fd_in == -1)
	//	perror(args[1]);
	//(*m)->fd_out = open(args[nbcom + OFST_FIRST_CMD], OW | OC | OT, FLAG_FIC); //TODO
	//if ((*m)->fd_out == -1)
	//	perror(args[nbcom + OFST_FIRST_CMD]);
}

void exec_init_minishell(t_minishell **m/*, t_env *last_env_list*/)
{
	*m = ft_calloc(1, sizeof(t_minishell));
	if (*m == NULL)
		ft_exit_fail_status(*m, NULL, EXIT_ALLOC_ERROR);
	// if (last_env_list)
	// 	(*m)->env_list = last_env_list;
	//(*m)->cmds = ft_calloc(1, sizeof(t_cmd));
	/*if ((*m)->cmds == NULL)
		ft_exit_fail_status(*m, NULL, EXIT_ALLOC_ERROR);*/

	/*(*m)->cmds->redirs  = ft_calloc(1, sizeof(t_redir));
	if((*m)->cmds->redirs == NULL)
		ft_exit_fail_status(*m, NULL, EXIT_ALLOC_ERROR);*/

	(*m)->fd_in = -1;
	(*m)->fd_out = -1;
	//(*m)->cmds = NULL;
	// (*m)->cmds2 = NULL;
	// (*m)->cmds2->cmd = NULL;
	// (*m)->token_list = NULL;
	// (*m)->nb_cmd = 0;
	// (*m)->is_here_doc = 0;
	// (*m)->limiter = NULL;
	// (*m)->path = NULL;
	// (*m)->env_list = NULL;
	// (*m)->last_status = 0;
	//exec_feed_pipex(m, NULL, 0, env); //TODO
}


