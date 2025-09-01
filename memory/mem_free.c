/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:18:23 by ybouroga          #+#    #+#             */
/*   Updated: 2025/07/10 16:07:22 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	mem_free(void *p, char *mes)
{
	if (DEBUG_MALLOC)
		if (p)
		{
			ft_printf_fd(STDERR_FILENO, "MALLOC[%d][%s]\n", p, mes);
			free(p);
		}
}

void	mem_free_null(char	**p, char *mes)
{
	if (p == NULL || *p == NULL)
		return ;
	mem_free(*p, mes);
	*p = NULL;
}

void	mem_free_array(char	***tab, char *mes)
{
	int	i;

	i = 0;
	if (tab == NULL || *tab == NULL)
		return ;
	while ((*tab)[i])
		mem_free_null(&(*tab)[i++], mes);
	free(*tab);
	*tab = NULL;
}
/*
static void	mem_free_cmds(t_minishell **m)
{
	int	i;

	i = 0;
	if (m == NULL || *m == NULL || (*m)->cmds == NULL)
		return ;
	while (i < (*m)->nb_cmd)
	{
		mem_free_array((*m)->cmds[i].args);
		mem_free_null(&(*m)->cmds[i].path);
		i++;
	}
	free((*m)->cmds);
	(*m)->cmds = NULL;
}*/

void	mem_free_all(t_minishell *m)
{
	if (m == NULL)
		return ;
	mem_close_fds(m);
	//mem_free_cmds(&m);
	prs_lstclear(&m->cmds);
	mem_free_null(&m->limiter, "limiter");
	mem_free_array(&m->path, "path");
	ft_lstclear_env(&m->env_list, ft_del_env_content);
	lex_lstclear(&m->token_list);
	mem_free_null(&m->line, "line");
	mem_free_null(&m->error, "error");
	ft_lstclear(&m->history, ft_del_content);
	rl_clear_history();
	free(m);
}

void	mem_reset_m(t_minishell *m)
{
	if (m == NULL)
		return ;
	mem_close_fds(m);
	prs_lstclear(&m->cmds);
	mem_free_null(&m->limiter, "limiter");
	mem_free_array(&m->path, "path");
	//ft_lstclear_env(&m->env_list, del_env_content);
	lex_lstclear(&m->token_list);
	mem_free_null(&m->line, "line");
	mem_free_null(&m->error, "error");
	//free(m);
	m->status_echo = m->status;
	m->status = 0;
}