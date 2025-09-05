/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_g_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:35:53 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/05 20:25:51 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_g_signal(t_minishell *m)
{
	if (g_signal)
	{
		g_signal &= ~SIG_FLAG;
		m->status_echo = 128 + SIGINT;
	}
	return (0);
}


/*
int	sig_kill_children(t_minishell *m)
{
	t_cmd    *c;
	int        got_signal;

	got_signal = GOT_NO_SIGNAL;
	if (g_signal)
	{
		g_signal = 0;
		if (m && m->cmds)
		{
			got_signal = GOT_SIGNAL; //TODO A REMOINTER ??
			m->last_status = 128 + SIGINT; //TODO A REMOINTER ??
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
}*/