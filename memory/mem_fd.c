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

void	mem_close_fds(t_minishell *p)
{
	/*int	i;

	i = 0;
	 while (i < p->nb_cmd)
	{
		if (p->cmds[i].fd_pipe[0] != -1)
			close(p->cmds[i].fd_pipe[0]);
		if (p->cmds[i].fd_pipe[1] != -1)
			close(p->cmds[i].fd_pipe[1]);
		i++;
	}*/
	if (p->fd_in != -1)
		close(p->fd_in);
	if (p->fd_out != -1)
		close(p->fd_out);
}
