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

#include "pipex.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

void	px_free_null(char	**ptr)
{
	if (ptr == NULL || *ptr == NULL)
		return ;
	free(*ptr);
	*ptr = NULL;
}

static void	px_free_array(char	**tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
		px_free_null(&tab[i++]);
	free(tab);
	tab = NULL;
}

static void	px_free_cmds(t_pipex **p)
{
	int	i;

	i = 0;
	if (p == NULL || *p == NULL || (*p)->cmds == NULL)
		return ;
	while (i < (*p)->nb_cmd)
	{
		px_free_array((*p)->cmds[i].args);
		px_free_null(&(*p)->cmds[i].path);
		i++;
	}
	free((*p)->cmds);
	(*p)->cmds = NULL;
}

void	px_free_all(t_pipex *p)
{
	if (p == NULL)
		return ;
	px_close_fds(p);
	px_free_cmds(&p);
	px_free_null(&p->limiter);
	px_free_array(p->path);
	free(p);
	p = NULL;
}