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

void	mem_close_fd(int fd)
{
	if (fd != -1)
		close(fd);
}

void mem_close_fds(t_minishell *m)
{
	t_cmd	*cmd;

	cmd = m->cmds;
	while (cmd)
	{
		mem_close_fd(cmd->fd_in);
		mem_close_fd(cmd->fd_out);
		cmd->fd_in = -1;
		cmd->fd_out = -1;
		cmd = cmd->next;
	}
	mem_close_fd(m->fd_in);
	mem_close_fd(m->fd_out);
	m->fd_in = -1;
	m->fd_out = -1;
}
