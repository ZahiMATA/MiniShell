/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_kill_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:57:47 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/31 11:29:22 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_kill_children(t_minishell *m)
{
	t_cmd	*c;
	int		got_signal;

	//printf("kill[%d]\n", g_signal);
	got_signal = GOT_NO_SIGNAL;
	if (g_signal)
	{
		//printf("kill[%d]\n", g_signal);
		g_signal = 0;
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
		if (m && m->cmds)
		{
			got_signal = GOT_SIGNAL; //TODO A REMOINTER ??
			m->status = 128 + SIGINT; //TODO A REMOINTER ??
			c = m->cmds;
			while (c)
			{
				if (c->pid > 0)
					kill(c->pid, SIGINT);
				c = c->next;
			}
		}
	}
	return got_signal;
}
