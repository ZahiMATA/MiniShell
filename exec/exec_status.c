/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:47:41 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/18 17:00:00 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	decompress_status(t_minishell *m, int status)
{
	(void)m;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	exec_set_last_status(t_minishell *m)
{
	t_cmd	*cmd;

	cmd = m->cmds;
	if (cmd == NULL)
		return (1);
	while (cmd)
	{
		cmd->status = decompress_status(m, cmd->status_c);
		m->last_status = cmd->status;
		if (cmd->next == NULL && WIFSIGNALED(cmd->status_c) && \
			WTERMSIG(cmd->status_c) == SIGQUIT)
			ft_perror(S_QUIT, NULL, NULL);
		cmd = cmd->next;
	}
	return (0);
}

void	on_ctrl_c(t_minishell *m)
{
	t_cmd	*l;

	l = m->cmds;
	if (l)
	{
		while (l->next)
			l = l->next;
		if (WIFSIGNALED(l->status_c) && WTERMSIG(l->status_c) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
}
