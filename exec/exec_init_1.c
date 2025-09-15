/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:28:03 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/15 15:52:52 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_init_env_list(t_minishell **m, char **env)
{
	int		i;
	char	*split[2];
	t_env	*tmp;

	if (env == NULL || *env == NULL)
	{
		(*m)->path = NULL;
		return ;
	}
	i = 0;
	while (env[i])
	{
		if (ft_split_first(env[i], &split[0], &split[1], '=') == NULL)
			ft_exit_fail_status(*m, NULL, EXIT_ALLOC_ERROR);
		tmp = ft_lstnew_env(split[0], split[1]);
		if (tmp == NULL)
		{
			mem_free(split[0], "exec_init_env_list", split[0]);
			mem_free(split[1], "exec_init_env_list", split[1]);
			ft_exit_fail_status(*m, NULL, EXIT_ALLOC_ERROR);
		}
		ft_lstadd_back_env(&(*m)->env_list, tmp);
		i++;
	}
}

void	exec_feed_minishell(t_minishell **m, char **env)
{
	(*m)->nb_cmd = prs_lstget_nb(*m);
	(*m)->is_here_doc = 0;
	//(*m)->env = env;
	if ((*m)->env_list == NULL)
		exec_init_env_list(m, env);
	ms_expand_all_cmds(*m);
	exec_init_path(m);
	exec_init_cmd_path(m/*, nbcom*/);
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


