/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:50:18 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 13:40:47 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_heredoc(t_minishell *m)
{
	t_cmd	*l;

	mem_free_null(&m->line, "run_heredoc");
	l = m->cmds;
	while (l)
	{
		l->fd_in = -1;
		l->fd_out = -1;
		redir_heredoc(m, l);
		if (m->status_heredoc != 0)
			return ;
		l = l->next;
	}
}
